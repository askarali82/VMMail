#include "EmailService.h"
#include "EmailClientApp.h"
#include <vmime/vmime.hpp>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <vmime/net/imap/IMAPMessage.hpp>
#include <vmime/net/imap/IMAPMessagePartContentHandler.hpp>

using namespace vmime;

std::vector <shared_ptr <security::cert::X509Certificate> >
	interactiveCertificateVerifier::m_trustedCerts;

void Message::SetHeadersFromIMAPMessage(shared_ptr<net::message> IMAPMessage)
{
    charset ch(charsets::UTF_8);
    shared_ptr<const header> Header = IMAPMessage->getHeader();

    if (Header->hasField("From"))
    {
        m_From.m_Name = wxString::FromUTF8(Header->From()->getValue<mailbox>()->getName().getConvertedText(ch).c_str());
        m_From.m_Address = Header->From()->getValue<mailbox>()->getEmail().toString();
        m_From.GenerateText();
    }

    if (Header->hasField("To"))
    {
        const std::vector<shared_ptr<const address>> ToAddrList =
            Header->To()->getValue<const addressList>()->getAddressList();
        for (size_t i = 0; i < ToAddrList.size(); i++)
        {
            const shared_ptr<const mailbox> MBox =
                dynamicCast<const mailbox>(ToAddrList[i]);
            EmailAddress To(wxString::FromUTF8(MBox->getName().getConvertedText(ch).c_str()), MBox->getEmail().toString());
            m_To.push_back(To);
        }
    }

    if (Header->hasField("CC"))
    {
        const std::vector<shared_ptr<const address>> CcAddrList =
            Header->Cc()->getValue<const addressList>()->getAddressList();
        for (size_t i = 0; i < CcAddrList.size(); i++)
        {
            const shared_ptr<const mailbox> MBox =
                dynamicCast<const mailbox>(CcAddrList[i]);
            EmailAddress CC(wxString::FromUTF8(MBox->getName().getConvertedText(ch).c_str()), MBox->getEmail().toString());
            m_Cc.push_back(CC);
        }
    }

    if (Header->hasField("BCC"))
    {
        const std::vector<shared_ptr<const address>> BCcAddrList =
            Header->Bcc()->getValue<const addressList>()->getAddressList();
        for (size_t i = 0; i < BCcAddrList.size(); i++)
        {
            const shared_ptr<const mailbox> MBox =
                dynamicCast<const mailbox>(BCcAddrList[i]);
            EmailAddress BCC(wxString::FromUTF8(MBox->getName().getConvertedText(ch).c_str()), MBox->getEmail().toString());
            m_BCc.push_back(BCC);
        }
    }

    if (Header->hasField("Sender"))
    {
        m_Sender.m_Name = wxString::FromUTF8(Header->Sender()->getValue<mailbox>()->getName().getConvertedText(ch).c_str());
        m_Sender.m_Address = Header->Sender()->getValue<mailbox>()->getEmail().toString();
        m_Sender.GenerateText();
    }

    if (Header->hasField("Subject"))
    {
        m_Subject = wxString::FromUTF8(Header->Subject()->getValue<text>()->getConvertedText(ch).c_str());
    }

    if (Header->hasField("Original-Message-Id"))
    {
        m_OriginalMessageId = Header->OriginalMessageId()->getValue<messageId>()->getId();
    }

    if (Header->hasField("Message-Id"))
    {
        m_MessageId = Header->MessageId()->getValue<messageId>()->getId();
    }

    if (Header->hasField("In-Reply-To"))
    {
        const std::vector<shared_ptr<const messageId>> MsgIdList =
            Header->InReplyTo()->getValue<messageIdSequence>()->getMessageIdList();
        for (size_t i = 0; i < MsgIdList.size(); i++)
        {
            m_InReplyTo.push_back(MsgIdList[i]->getId());
        }
    }

    if (Header->hasField("References"))
    {
        const std::vector<shared_ptr<const messageId>> MsgIdList =
            Header->References()->getValue<messageIdSequence>()->getMessageIdList();
        for (size_t i = 0; i < MsgIdList.size(); i++)
        {
            m_References.push_back(MsgIdList[i]->getId());
        }
    }

    if (Header->hasField("Date"))
    {
        m_Date = *(Header->Date()->getValue<datetime>());
    }

    m_Seen = (IMAPMessage->getFlags() & net::message::FLAG_SEEN) != 0;

    m_Number = IMAPMessage->getNumber();

    m_UID = (string)IMAPMessage->getUID();
}


bool EmailService::LoadFromCache(const wxString &Username)
{
    // Not implemented yet. Maybe in future
    return false;
}


bool EmailService::LoadMessagesFromServer(const wxString &Username, const wxString &Foldername)
{
    wxCriticalSectionLocker Locker(m_CritSect);
    try
    {
        m_LastErrorMessage = "";
        CheckError(!Username.IsEmpty(), "Username is empty.");
        m_CurrentUser = Username;
        m_CurrentFolder = Foldername;
        ConnectToUserIMAPStore();
        if (Foldername == wxEmptyString)
        {
            GetUserFolders();
        }
        OpenCurrentIMAPFolder(true);
        FetchMessages();
    }
    catch (const exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    catch (const std::exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    const bool Result = m_LastErrorMessage.IsEmpty();
    wxCommandEvent evt (wxEVT_THREAD, ID_LOADING_THREAD);
    LoadNotificationData *lnd = new LoadNotificationData(
        Result, Username, Foldername, m_CurrentFolder, ("Failed to load email messages: " + m_LastErrorMessage).c_str());
    evt.SetClientData(lnd);
    TheApp->GetMainFrame()->GetEventHandler()->QueueEvent(evt.Clone());
    return Result;
}


void EmailService::ConnectToUserIMAPStore()
{
    shared_ptr<net::session> &Session = m_Sessions[m_CurrentUser];
    if (Session.get() == nullptr)
    {
        Session = net::session::create();
    }
    Account &Acct = m_Accounts[m_CurrentUser];
    shared_ptr<net::store> &IMAPStore = m_IMAPStores[m_CurrentUser];
    if (IMAPStore.get() == nullptr || m_CurrentFolder == wxEmptyString)
    {        
        const wxString URL((Acct.m_IMAPRequiresSSL ? "imaps://" : "imap://") + Acct.m_IMAPServerName);
        IMAPStore = Session->getStore(utility::url(URL.ToStdString()));
    }
    IMAPStore->setProperty("server.port", Acct.m_IMAPServerPort);
    IMAPStore->setProperty("auth.username", m_CurrentUser);
    IMAPStore->setProperty("auth.password", Acct.m_Password);
    if (Acct.m_IMAPRequiresSSL)
    {
        IMAPStore->setProperty("connection.tls", true);
        IMAPStore->setProperty("connection.tls.required", true);
        IMAPStore->setCertificateVerifier(make_shared<interactiveCertificateVerifier>());
    }
    try
    {
        IMAPStore->connect();
    }
    catch (vmime::exceptions::already_connected &)
    {
    }
    catch (vmime::exception &)
    {
        m_Accounts[m_CurrentUser].m_Password.Clear();
    }
}


void EmailService::GetUserFolders()
{
    auto &UserFolder = m_Folders[m_CurrentUser];
    UserFolder.clear();
    UserFolder.push_back(std::make_shared<Folder>());
    auto &RootF = UserFolder.back();
    RootF->m_Name = m_CurrentUser;
    shared_ptr<net::store> &IMAPStore = m_IMAPStores[m_CurrentUser];
    std::vector<shared_ptr<net::folder>> Folders = IMAPStore->getRootFolder()->getFolders(true);
    for (auto &folder : Folders)
    {
        if (!FolderCanBeDisplayed(folder))
        {           
            continue;
        }
        RootF->m_Childs.push_back(std::make_shared<Folder>());
        auto &ChildF = RootF->m_Childs.back();
        ChildF->m_Name = wxString::FromUTF8(folder->getName().getConvertedText(charset(charsets::UTF_8)).c_str());
        ChildF->m_Default = ChildF->m_Name.Lower().Find("inbox") != wxNOT_FOUND;
        ChildF->m_Parent = RootF.get();
        ChildF->m_IMAPFolder = folder;
        ChildF->m_FullPath = folder->getFullPath();
        if (ChildF->m_Default)
        {
            m_CurrentFolder = ChildF->m_Name;
        }
    }
    if (m_CurrentFolder == wxEmptyString && !Folders.empty())
    {
        m_CurrentFolder = wxString::FromUTF8(Folders[0]->getName().getConvertedText(charset(charsets::UTF_8)).c_str());
        if (!RootF->m_Childs.empty())
        {
            RootF->m_Childs[0]->m_Default = true;
        }
    }
}


void EmailService::OpenCurrentIMAPFolder(const bool InReadOnlyMode)
{
    CheckError(m_CurrentFolder != wxEmptyString, "Folder name is empty.");
    std::shared_ptr<Folder> FolderToOpen = FindFolder();
    static const int MODES[] = {net::folder::MODE_READ_WRITE, net::folder::MODE_READ_ONLY};
    try
    {
        const int CurMode = FolderToOpen->m_IMAPFolder->getMode();
        if (CurMode != MODES[int(InReadOnlyMode)])
        {
            FolderToOpen->m_IMAPFolder->close(CurMode == net::folder::MODE_READ_ONLY ? false : true);
        }
    }
    catch (vmime::exception &)
    {
    }

    try
    {
        FolderToOpen->m_IMAPFolder->open(MODES[int(InReadOnlyMode)]);
    }
    catch (vmime::exceptions::folder_already_open &)
    {
    }
}


std::shared_ptr<Folder> EmailService::FindFolder(wxString Username, wxString FolderName)
{
    if (Username == wxEmptyString)
    {
        Username = m_CurrentUser;
    }
    if (FolderName == wxEmptyString)
    {
        FolderName = m_CurrentFolder;
    }
    auto &Folders = m_Folders[Username];
    for (const auto &F : Folders)
    {
        if (F->m_Name != Username)
        {
            continue;
        }
        for (auto &Ch : F->m_Childs)
        {
            if (Ch->m_Name == FolderName)
            {
                return Ch;
            }
        }
    }
    return std::shared_ptr<Folder>();
}


bool EmailService::FolderCanBeDisplayed(shared_ptr<net::folder> folder) const
{
    const net::folderAttributes Attr = folder->getAttributes();
    const int Type = Attr.getType();
    return (Type & net::folderAttributes::TYPE_CONTAINS_MESSAGES) != 0;
}


bool EmailService::AddAccount(const AccountSettings &Settings, const bool IsNewAccount)
{
    {
        wxCriticalSectionLocker Locker(m_CritSect);
        auto it = m_Accounts.find(Settings.m_UserNameText->GetValue());
        if ((!IsNewAccount && it != m_Accounts.end()) || (IsNewAccount && it == m_Accounts.end()))
        {
            Account &Acct = m_Accounts[Settings.m_UserNameText->GetValue()];
            Acct.m_IMAPServerName = Settings.m_IMAPServerText->GetValue();
            Acct.m_IMAPServerPort = Settings.m_IMAPPortText->GetValue();
            Acct.m_IMAPRequiresSSL = Settings.m_IMAPRequiresSSL->GetValue();

            Acct.m_SMTPServerName = Settings.m_SMTPServerText->GetValue();
            Acct.m_SMTPServerPort = Settings.m_SMTPPortText->GetValue();
            Acct.m_SMTPRequiresSSL = Settings.m_SMTPRequiresSSL->GetValue();
            Acct.m_SMTPRequiresTLS = Settings.m_SMTPRequiresTLS->GetValue();
            Acct.m_SMTPRequiresAuth = Settings.m_SMTPRequiresAuth->GetValue();

            Acct.m_FullName = Settings.m_FullNameText->GetValue();
            Acct.m_UserName = Settings.m_UserNameText->GetValue();
            if (IsNewAccount)
            {
                Acct.m_Password = Settings.m_PasswordText->GetValue();
            }
            return true;
        }
    }
    wxMessageBox("Account with this user name already exists.", "Error", wxICON_ERROR);
    return false;
}


void EmailService::FetchMessages()
{
    std::shared_ptr<Folder> CurFolder = FindFolder();
    CurFolder->m_Messages.clear();
    const size_t MCount = CurFolder->m_IMAPFolder->getMessageCount();
    if (MCount == 0)
    {
        return;
    }
    const size_t StartNumber = MCount <= 200 ? 1 : MCount - 200;
    IMAPMessageList IMAPMessages = CurFolder->m_IMAPFolder->getMessages(net::messageSet::byNumber(StartNumber, -1));
    if (!IMAPMessages.empty())
    {
        net::fetchAttributes FetchAttributes;
        FetchAttributes.add(
            net::fetchAttributes::ENVELOPE |
            net::fetchAttributes::FLAGS |
            net::fetchAttributes::UID);
        FetchAttributes.add("Original-Message-Id");
        FetchAttributes.add("Message-Id");
        FetchAttributes.add("In-Reply-To");
        FetchAttributes.add("References");
        CurFolder->m_IMAPFolder->fetchMessages(IMAPMessages, FetchAttributes);
        for (int i = IMAPMessages.size() - 1; i >= 0; i--)
        {
            CurFolder->m_Messages.push_back(std::make_shared<Message>());
            CurFolder->m_Messages.back()->SetHeadersFromIMAPMessage(IMAPMessages[i]);
        }
        std::sort(
            CurFolder->m_Messages.begin(),
            CurFolder->m_Messages.end(),
            [](std::shared_ptr<Message> a, std::shared_ptr<Message> b) {return a->m_Date > b->m_Date;});
        ResetMessagesPartners(CurFolder->m_Messages);
        OpenCurrentIMAPFolder(false);
    }
}


void EmailService::ResetMessagesPartners(std::vector<std::shared_ptr<Message>> &FolderMessages)
{
    for (size_t i = 0; i < FolderMessages.size(); i++)
    {
        auto &Msg = FolderMessages[i];
        Msg->m_Prev = nullptr;
        Msg->m_Next = nullptr;
        if (i > 0)
        {
            Msg->m_Prev = FolderMessages[i - 1].get();
            FolderMessages[i - 1]->m_Next = Msg.get();
        }
        for (size_t j = 0; j < Msg->m_Childs.size(); j++)
        {
            auto &Ch = Msg->m_Childs[j];
            Ch->m_Prev = nullptr;
            Ch->m_Next = nullptr;
            if (j == 0)
            {
                Ch->m_Prev = Msg->m_Prev;
            }
            else
            {
                Ch->m_Prev = Msg->m_Childs[j - 1].get();
                Msg->m_Childs[j - 1]->m_Next = Ch.get();
                if (j == Msg->m_Childs.size() - 1 && (i + 1) < FolderMessages.size())
                {
                    Ch->m_Next = FolderMessages[i + 1].get();
                }
            }
        }
    }
}


bool EmailService::GetHTMLPartOfMessage(std::shared_ptr<Folder> Fldr, Message *UIMsg)
{
    wxCriticalSectionLocker Locker(m_CritSect);
    try
    {
        m_LastErrorMessage = "";
        CheckError(Fldr.get() != nullptr && Fldr->m_Parent != nullptr && UIMsg != nullptr,
            "Folder and/or message doesn't exist.");
        if (UIMsg->m_Body.IsEmpty())
        {
            std::shared_ptr<Folder> CurFolder = FindFolder(Fldr->m_Parent->m_Name, Fldr->m_Name);
            shared_ptr<net::message> IMAPMessage = CurFolder->m_IMAPFolder->getMessage(UIMsg->m_Number);
            shared_ptr<message> ParsedMsg = IMAPMessage->getParsedMessage();
            UIMsg->m_Body = ParseBodyPart(ParsedMsg, UIMsg);
            if (!UIMsg->m_Seen)
            {
                MarkMessageAsSeenUnseen(CurFolder, UIMsg);
            }
        }
    }
    catch (const exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    catch (const std::exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    const bool Result = m_LastErrorMessage.IsEmpty();
    wxCommandEvent *evt = new wxCommandEvent(wxEVT_THREAD, ID_BODYLOADING_THREAD);
    evt->SetInt(Result);
    evt->SetExtraLong(reinterpret_cast<long>(UIMsg));
    evt->SetString(Result ? wxString("") : "Failed to load message body: " + m_LastErrorMessage);
    TheApp->GetMainFrame()->GetEventHandler()->QueueEvent(evt);
    return Result;
}


void EmailService::MarkMessageAsSeenUnseen(std::shared_ptr<Folder> Fldr, Message *UIMessage, const bool Throw)
{
    try
    {
        Fldr->m_IMAPFolder->setMessageFlags(
            net::messageSet::byNumber(UIMessage->m_Number),
            net::message::FLAG_SEEN,
            UIMessage->m_Seen ? net::message::FLAG_MODE_REMOVE : net::message::FLAG_MODE_ADD);
        UIMessage->m_Seen = !UIMessage->m_Seen;
    }
    catch (exception &)
    {
        if (Throw)
        {
            throw;
        }
    }
}


wxString EmailService::ParseBodyPart(shared_ptr<message> VMimeMessage, Message *UIMessage)
{
    UIMessage->m_Attachments.clear();
    messageParser MessageParser(VMimeMessage);
    const std::vector<shared_ptr<const attachment>> AttachmentList = MessageParser.getAttachmentList();
    for (size_t i = 0; i < AttachmentList.size(); i++)
    {
        auto Attach = AttachmentList[i];
        if (Attach->getName().getBuffer().empty())
        {
            continue;
        }
        UIMessage->m_Attachments.push_back(Message::Attachment());
        auto &Attachment = UIMessage->m_Attachments.back();
        Attachment.m_Name = wxString::FromUTF8(Attach->getName().getConvertedText(charset(charsets::UTF_8)).c_str());
        utility::outputStreamByteArrayAdapter osb(Attachment.m_Content);
        Attach->getData()->extract(osb);
    }
    wxString HTMLTextPart;
    wxString PlainTextPart;
    for (size_t i = 0; i < MessageParser.getTextPartCount(); i++)
    {
        shared_ptr<const textPart> TextPart = MessageParser.getTextPartAt(i);
        if (TextPart->getType().getSubType() == mediaTypes::TEXT_HTML)
        {
            std::ostringstream stream;
            utility::outputStreamAdapter os(stream);
            TextPart->getText()->extract(os);
            HTMLTextPart =
                TextPart->getCharset() == charset(charsets::UTF_8) ?
                wxString::FromUTF8(stream.str().c_str()) : wxString(stream.str());
            shared_ptr<const htmlTextPart> HTML =
                dynamicCast<const htmlTextPart>(TextPart);
            for (size_t j = 0; j < HTML->getObjectCount(); j++)
            {
                shared_ptr<const htmlTextPart::embeddedObject> Object = HTML->getObjectAt(j);
                ParseHTMLObject(Object, HTMLTextPart);
            }
        }
        else if (TextPart->getType().getSubType() == mediaTypes::TEXT_PLAIN)
        {
            std::ostringstream stream;
            utility::outputStreamAdapter os(stream);
            TextPart->getText()->extract(os);
            PlainTextPart =
                TextPart->getCharset() == charset(charsets::UTF_8) ?
                wxString::FromUTF8(stream.str().c_str()) : wxString(stream.str());
        }
    }
    return HTMLTextPart.IsEmpty() ? PlainTextPart : HTMLTextPart;
}


void EmailService::ParseHTMLObject(
    shared_ptr<const htmlTextPart::embeddedObject> Object, wxString &HTMLTextPart)
{
    byteArray bar;
    utility::outputStreamByteArrayAdapter osb(bar);
    Object->getData()->extract(osb);
    utility::inputStreamByteBufferAdapter isb(bar.data(), bar.size());
    if (Object->getReferenceType() == htmlTextPart::embeddedObject::REFERENCED_BY_ID)
    {
        if (Object->getEncoding().getName() == "base64")
        {
            std::string str;
            utility::outputStreamStringAdapter oss(str);
            utility::encoder::b64Encoder b64;
            b64.encode(isb, oss);
            SplitBase64StdString(str);
            const wxString NewStr =
                "data:" + Object->getType().getType() + "/" +
                Object->getType().getSubType() + ";" + Object->getEncoding().getName() + "," + str;
            HTMLTextPart.Replace(Object->getReferenceId(), NewStr);
        }
    }
}


bool EmailService::SendVMimeMessage(const wxString &Username, shared_ptr<message> VMimeMessage)
{
    wxCriticalSectionLocker Locker(m_CritSect);
    try
    {
        m_LastErrorMessage.Clear();
        shared_ptr<net::session> Session = net::session::create();
        Account &Acct = m_Accounts[Username];
        const wxString URL{
            (Acct.m_SMTPRequiresSSL ? "smtps://" : "smtp://") + Acct.m_SMTPServerName};
        shared_ptr<net::transport> SMTPTransport =
            Session->getTransport(utility::url(URL.ToStdString()));
        SMTPTransport->setProperty("server.port", Acct.m_SMTPServerPort);
        SMTPTransport->setProperty("auth.username", Username);
        SMTPTransport->setProperty("auth.password", Acct.m_Password);
        if (Acct.m_SMTPRequiresAuth)
        {
            SMTPTransport->setProperty("options.need-authentication", true);
        }
        if (Acct.m_IMAPRequiresSSL || Acct.m_SMTPRequiresTLS)
        {
            SMTPTransport->setCertificateVerifier(make_shared<interactiveCertificateVerifier>());
            if (Acct.m_SMTPRequiresTLS)
            {
                SMTPTransport->setProperty("connection.tls", true);
                SMTPTransport->setProperty("connection.tls.required", true);
            }
        }
        SMTPTransport->connect();
        SMTPTransport->send(VMimeMessage);
        SMTPTransport->disconnect();
    }
    catch (const exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    catch (const std::exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    const bool Result = m_LastErrorMessage.IsEmpty();
    wxCommandEvent *evt = new wxCommandEvent(wxEVT_THREAD, ID_SENDING_THREAD);
    evt->SetInt(Result);
    evt->SetString(Result ? wxString("") : "Failed to load email messages: " + m_LastErrorMessage);
    TheApp->GetMainFrame()->GetEventHandler()->QueueEvent(evt);
    return Result;
}


bool EmailService::MoveMessages(
    std::shared_ptr<Folder> Source, std::shared_ptr<Folder> Dest, const std::vector<std::shared_ptr<Message>> &Msgs)
{
    wxCriticalSectionLocker Locker(m_CritSect);
    try
    {
        m_LastErrorMessage.Clear();
        CheckError(!Msgs.empty(), "No message to move.");
        std::vector<size_t> Numbers;
        for (const auto &M : Msgs)
        {
            Numbers.push_back(M->m_Number);
        }
        Source->m_IMAPFolder->copyMessages(Dest->m_FullPath, net::messageSet::byNumber(Numbers));
        Source->m_IMAPFolder->deleteMessages(net::messageSet::byNumber(Numbers));
    }
    catch (const exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    catch (const std::exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    const bool Result = m_LastErrorMessage.IsEmpty();
    wxCommandEvent *evt = new wxCommandEvent(wxEVT_THREAD, ID_MOVING_THREAD);
    evt->SetInt(Result);
    evt->SetString(Result ? wxString("") : "Failed to move message(s): " + m_LastErrorMessage);
    TheApp->GetMainFrame()->GetEventHandler()->QueueEvent(evt);
    return Result;
}


bool EmailService::DeleteMessages(std::shared_ptr<Folder> Fldr, const std::vector<std::shared_ptr<Message>> &Msgs)
{
    wxCriticalSectionLocker Locker(m_CritSect);
    try
    {
        m_LastErrorMessage.Clear();
        CheckError(!Msgs.empty(), "No message to delete.");
        std::vector<size_t> Numbers;
        for (const auto &M : Msgs)
        {
            Numbers.push_back(M->m_Number);
        }
        Fldr->m_IMAPFolder->deleteMessages(net::messageSet::byNumber(Numbers));
    }
    catch (const exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    catch (const std::exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    const bool Result = m_LastErrorMessage.IsEmpty();
    wxCommandEvent *evt = new wxCommandEvent(wxEVT_THREAD, ID_DELETING_THREAD);
    evt->SetInt(Result);
    evt->SetString(Result ? wxString("") : "Failed to delete message(s): " + m_LastErrorMessage);
    TheApp->GetMainFrame()->GetEventHandler()->QueueEvent(evt);
    return Result;
}


bool EmailService::MarkMessageReadUnread(
    std::shared_ptr<Folder> Fldr, const std::vector<std::shared_ptr<Message>> &Msgs)
{
    wxCriticalSectionLocker Locker(m_CritSect);
    try
    {
        m_LastErrorMessage.Clear();
        CheckError(!Msgs.empty(), "No message to mark read/unread.");
        std::shared_ptr<Folder> CurFolder = FindFolder(Fldr->m_Parent->m_Name, Fldr->m_Name);
        for (const auto &M : Msgs)
        {
            if (CurFolder->MessageExists(M))
            {
                MarkMessageAsSeenUnseen(CurFolder, M.get(), true);
            }
        }
    }
    catch (const exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    catch (const std::exception &e)
    {
        m_LastErrorMessage = e.what();
    }
    const bool Result = m_LastErrorMessage.IsEmpty();
    wxCommandEvent *evt = new wxCommandEvent(wxEVT_THREAD, ID_FLAGSCHANGING_THREAD);
    evt->SetInt(Result);
    evt->SetString(Result ? wxString("") : "Cannot mark message(s) Read/Unread: " + m_LastErrorMessage);
    TheApp->GetMainFrame()->GetEventHandler()->QueueEvent(evt);
    return Result;
}


void EmailService::SplitBase64StdString(std::string &Str) const
{
    size_t I = 0;
    for (size_t i = I; i < Str.length(); i++)
    {
        if (i > 0 && (i % 75) == 0)
        {
            Str.insert(i, "\n");
            I + i + 1;
        }
    }
}