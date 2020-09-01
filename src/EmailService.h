#pragma once

#include <wx/wx.h>
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <vmime/vmime.hpp>
#include "AccountSettings.h"
#include <wx/tokenzr.h>
#include <wx/thread.h>

using namespace vmime;

struct Account
{
    wxString m_IMAPServerName;
    wxString m_IMAPServerPort;
    bool     m_IMAPRequiresSSL;

    wxString m_SMTPServerName;
    wxString m_SMTPServerPort;
    bool     m_SMTPRequiresSSL;
    bool     m_SMTPRequiresTLS;
    bool     m_SMTPRequiresAuth;

    wxString m_FullName;
    wxString m_UserName;
    wxString m_Password;

    Account():
        m_IMAPRequiresSSL(true), m_SMTPRequiresSSL(true),
        m_SMTPRequiresTLS(true), m_SMTPRequiresAuth(true)
    {
    }
};


struct Message
{
    struct EmailAddress
    {
        wxString m_Name;
        wxString m_Address;
        wxString m_Text;

        EmailAddress() = default;

        EmailAddress(const wxString &Name, const wxString &Address):
            m_Name(Name), m_Address(Address)
        {
            GenerateText();
        }

        EmailAddress(const wxString &Text): m_Text(Text)
        {
            const int P = m_Text.Find(">");
            if (P != wxNOT_FOUND)
            {
                m_Text = m_Text.Mid(0, P);
            }
            m_Text.Trim(false).Trim();
            wxArrayString NameAddr = wxSplit(m_Text, '<');
            if (NameAddr.GetCount() > 0)
            {
                m_Name = NameAddr[0];
                m_Name.Trim(false).Trim();
            }
            if (NameAddr.GetCount() > 1)
            {
                m_Address = NameAddr[1];
                m_Address.Trim(false).Trim();
            }
            if (m_Address.IsEmpty() && m_Name.Find("@") != wxNOT_FOUND)
            {
                m_Address = m_Name;
                m_Name.Clear();
            }
        }

        EmailAddress(const EmailAddress &Other) = default;

        void GenerateText()
        {
            m_Text = m_Name.IsEmpty() ? m_Address : m_Name + " <" + m_Address + ">";
        }

        EmailAddress & operator = (const EmailAddress &Other) = default;

        bool operator == (const EmailAddress &Other) const
        {
            return m_Address == Other.m_Address;
        }

        bool operator < (const EmailAddress &Other) const
        {
            return m_Text < Other.m_Text;
        }
    };

    struct Attachment : public wxObject
    {
        wxString  m_Name;
        byteArray m_Content;
    };

    EmailAddress                          m_From;
    std::vector<EmailAddress>             m_To;
    std::vector<EmailAddress>             m_Cc;
    std::vector<EmailAddress>             m_BCc;
    EmailAddress                          m_Sender;
    datetime                              m_Date;
    wxString                              m_Subject;
    wxString                              m_OriginalMessageId;
    wxString                              m_MessageId;
    std::vector<wxString>                 m_InReplyTo;
    std::vector<wxString>                 m_References;
    wxString                              m_UID;
    int                                   m_Number;
    bool                                  m_Seen;
    Message*                              m_Parent;
    Message*                              m_Prev;
    Message*                              m_Next;
    wxString                              m_Body;
    std::vector<Attachment>               m_Attachments;
    std::vector<std::shared_ptr<Message>> m_Childs;

    Message() :
        m_Number(0), m_Seen(false), m_Parent(nullptr), m_Prev(nullptr), m_Next(nullptr)
    {
    }
    bool operator == (const std::shared_ptr<Message> &Other) const
    {
        return
            Other.get() != nullptr &&
            (m_UID == Other->m_UID && !m_UID.IsEmpty()) ||
            (m_Number == Other->m_Number && m_Number > 0) ||
            (m_MessageId == Other->m_MessageId && !m_MessageId.IsEmpty());
    }
    bool operator == (const Message &Other) const
    {
        return
            (m_UID == Other.m_UID && !m_UID.IsEmpty()) ||
            (m_Number == Other.m_Number && m_Number > 0) ||
            (m_MessageId == Other.m_MessageId && !m_MessageId.IsEmpty());
    }
    void SetHeadersFromIMAPMessage(shared_ptr<net::message> IMAPMessage);
    wxString GetDateTimeStr() const
    {
        if (m_Date == datetime())
        {
            return "";
        }
        wxString Result = m_Date.generate();
        int p = Result.Find("-");
        if (p != wxNOT_FOUND)
        {
            Result = Result.SubString(0, p - 2);
        }
        p = Result.Find("+");
        if (p != wxNOT_FOUND)
        {
            Result = Result.SubString(0, p - 2);
        }
        return Result;
    }
};


struct Folder
{
    wxString                              m_Name;
    bool                                  m_Default;
    Folder*                               m_Parent;
    shared_ptr<net::folder>               m_IMAPFolder;
    net::folder::path                     m_FullPath;
    std::vector<std::shared_ptr<Folder>>  m_Childs;
    std::vector<std::shared_ptr<Message>> m_Messages;

    Folder(const wxString &Name = "") :
        m_Name(Name), m_Default(false), m_Parent(nullptr)
    {
    }
    const bool operator == (const std::shared_ptr<Folder> &Other) const
    {
        return m_Name == Other->m_Name;
    }
    const bool operator == (const Folder &Other) const
    {
        return m_Name == Other.m_Name;
    }
    bool MessageExists(const std::shared_ptr<Message> &Msg) const
    {
        return std::find(m_Messages.begin(), m_Messages.end(), Msg) != m_Messages.end();
    }
};


class interactiveCertificateVerifier : public security::cert::defaultCertificateVerifier
{
public:
	void verify(
        const shared_ptr <security::cert::certificateChain>& chain,
        const string& hostname)
    {
		try
        {
            setX509TrustedCerts(m_trustedCerts);
            defaultCertificateVerifier::verify(chain, hostname);
	    }
        catch (const security::cert::certificateException&)
        {
            shared_ptr <security::cert::certificate> cert = chain->getAt(0);
            if (cert->getType() == "X.509")
            {
                m_trustedCerts.push_back(dynamicCast <security::cert::X509Certificate>(cert));
                setX509TrustedCerts(m_trustedCerts);
                defaultCertificateVerifier::verify(chain, hostname);
                return;
			}
            throw security::cert::certificateException("User did not accept the certificate.");
        }
    }

private:
	static std::vector<shared_ptr<security::cert::X509Certificate>> m_trustedCerts;
};


struct LoadNotificationData
{
    const bool     m_Result;
    const wxString m_RequstedUserName;
    const wxString m_RequstedFolderName;
    const wxString m_ResultedFolderName;
    const wxString m_ErrorMessage;
    LoadNotificationData(
        const bool Result = false,
        const wxString &RequstedUserName = "",
        const wxString &RequstedFolderName = "",
        const wxString &ResultedFolderName = "",
        const wxString &ErrorMessage = ""):
        m_Result(Result),
        m_RequstedUserName(RequstedUserName),
        m_RequstedFolderName(RequstedFolderName),
        m_ResultedFolderName(ResultedFolderName),
        m_ErrorMessage(ErrorMessage)
    {
    }
};


class EmailService
{
public:
    static const int ID_SENDING_THREAD        = 1150;
    static const int ID_LOADING_THREAD        = 1151;
    static const int ID_BODYLOADING_THREAD    = 1152;
    static const int ID_DELETING_THREAD       = 1153;
    static const int ID_MOVING_THREAD         = 1154;
    static const int ID_FLAGSCHANGING_THREAD  = 1155;

    wxString GetLastErrorMessage()
    {
        wxCriticalSectionLocker Locker(m_CritSect);
        return m_LastErrorMessage;
    }

    bool PasswordExists(const wxString &Username)
    {
        wxCriticalSectionLocker Locker(m_CritSect);
        return
            !Username.IsEmpty() &&
            m_Accounts.find(Username) != m_Accounts.end() &&
            !m_Accounts[Username].m_Password.IsEmpty();
    }

    bool AccountExists(const wxString &Username)
    {
        wxCriticalSectionLocker Locker(m_CritSect);
        return !Username.IsEmpty() && m_Accounts.find(Username) != m_Accounts.end();
    }

    bool SetPassword(const wxString &Username, const wxString &Password)
    {
        wxCriticalSectionLocker Locker(m_CritSect);
        if (Username.IsEmpty() || m_Accounts.find(Username) == m_Accounts.end())
        {
            return false;
        }
        m_Accounts[Username].m_Password = Password.c_str();
        return true;
    }

    bool AddAccount(const AccountSettings &Settings, const bool IsNewAccount = true);

    bool LoadFromCache(const wxString &Username = wxEmptyString);

    bool LoadMessagesFromServer(const wxString &Username, const wxString &Foldername = wxEmptyString);

    std::vector<std::shared_ptr<Folder>> GetUserFolders(const wxString &Username)
    {
        wxCriticalSectionLocker Locker(m_CritSect);
        if (!Username.IsEmpty() && m_Folders.find(Username) != m_Folders.end())
        {
            return m_Folders[Username];
        }
        else
        {
            return std::vector<std::shared_ptr<Folder>>();
        }
    }

    std::shared_ptr<Folder> GetUserFolder(const wxString &Username, const wxString &Foldername)
    {
        wxCriticalSectionLocker Locker(m_CritSect);
        if (!Username.IsEmpty() && !Foldername.IsEmpty() && m_Folders.find(Username) != m_Folders.end())
        {
            return FindFolder(Username, Foldername);
        }
        else
        {
            return std::shared_ptr<Folder>();
        }
    }

    bool MarkMessageReadUnread(std::shared_ptr<Folder> Fldr, const std::vector<std::shared_ptr<Message>> &Msgs);

    bool GetHTMLPartOfMessage(std::shared_ptr<Folder> Fldr, Message *UIMsg);

    bool SendVMimeMessage(const wxString &Username, shared_ptr<message> VMimeMessage);

    bool MoveMessages(
        std::shared_ptr<Folder> Source, std::shared_ptr<Folder> Dest, const std::vector<std::shared_ptr<Message>> &Msgs);

    bool DeleteMessages(std::shared_ptr<Folder> Fldr, const std::vector<std::shared_ptr<Message>> &Msgs);

    void ResetMessagesPartners(std::vector<std::shared_ptr<Message>> &FolderMessages);

    void GetFROMFieldForUser(const wxString &Username, Message::EmailAddress &From)
    {
        wxCriticalSectionLocker Locker(m_CritSect);
        Account &Acct = m_Accounts[Username];
        From = Message::EmailAddress(Acct.m_FullName, Acct.m_UserName);
    }

    static void CheckError(const bool IsOK, const wxString &ErrorMessage)
    {
        if (!IsOK)
        {
            throw std::runtime_error(ErrorMessage);
        }
    }

private:
    typedef std::vector<shared_ptr<net::message>> IMAPMessageList;

    wxCriticalSection m_CritSect;

    wxString m_CurrentUser;
    wxString m_CurrentFolder;

    // Objects per user
    std::map<wxString, shared_ptr<net::session>> m_Sessions;
    std::map<wxString, shared_ptr<net::store>> m_IMAPStores;
    std::map<wxString, Account> m_Accounts;
    std::map<wxString, std::vector<std::shared_ptr<Folder>>> m_Folders;
  
    wxString m_LastErrorMessage;

    void ConnectToUserIMAPStore();
    void OpenCurrentIMAPFolder(const bool InReadOnlyMode);
    void GetUserFolders();
    std::shared_ptr<Folder> FindFolder(wxString Username = wxEmptyString, wxString FolderName = wxEmptyString);
    bool FolderCanBeDisplayed(shared_ptr<net::folder> folder) const;

    void FetchMessages();

    wxString ParseBodyPart(shared_ptr<message> VMimeMessage, Message *UIMessage);
    void ParseHTMLObject(
        shared_ptr<const htmlTextPart::embeddedObject> Object, wxString &HTMLTextPart);
    void MarkMessageAsSeenUnseen(std::shared_ptr<Folder> Fldr, Message *UIMessage, const bool Throw = false);
};