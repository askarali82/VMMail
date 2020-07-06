#include "MainFrame.h"
#include "AccountFolderViewModel.h"
#include "MessageListViewModel.h"
#include "EmailClientApp.h"
#include "AccountSettings.h"
#include <wx/log.h>
#include <wx/textdlg.h>
#include "wx/webviewarchivehandler.h"
#include "wx/webviewfshandler.h"
#include "wx/filesys.h"
#include "wx/fs_arc.h"
#include "wx/fs_mem.h"
#include <fstream>
#include <functional>
#include "EmailEditorFrame.h"

#ifdef WIN32
    #include "mingw-std-threads/mingw.thread.h"
#else
    #include <thread>
#endif

#ifndef __WXMSW__
    #include "bitmaps/email.xpm"
#endif

#define ID_MENU_ITEMS 1100

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_TIMER(ID_LOAD_TIMER, MainFrame::OnLoadingTimer)
    EVT_DATAVIEW_SELECTION_CHANGED(ID_ACC_LIST, MainFrame::OnFolderSelected)
    EVT_DATAVIEW_SELECTION_CHANGED(ID_MSG_LIST, MainFrame::OnEmailMessageSelected)
    EVT_COMMAND(ID_ADDACCOUNT_BUTTON, wxEVT_COMMAND_TOOL_CLICKED, MainFrame::OnAddAccountButtonClicked)
    EVT_COMMAND(ID_WRITE_BUTTON, wxEVT_COMMAND_TOOL_CLICKED, MainFrame::OnWriteButtonClicked)
    EVT_COMMAND(ID_MARK_RURBUTTON, wxEVT_COMMAND_TOOL_CLICKED, MainFrame::OnMarkReadUnreadButtonClicked)
    EVT_COMMAND(ID_REPLY_BUTTON, wxEVT_COMMAND_TOOL_CLICKED, MainFrame::OnReplyButtonClicked)
    EVT_COMMAND(ID_REPLYALL_BUTTON, wxEVT_COMMAND_TOOL_CLICKED, MainFrame::OnReplyAllButtonClicked)
    EVT_COMMAND(ID_FORWARD_BUTTON, wxEVT_COMMAND_TOOL_CLICKED, MainFrame::OnForwardButtonClicked)
    EVT_COMMAND(ID_DELETE_BUTTON, wxEVT_COMMAND_TOOL_CLICKED, MainFrame::OnDeleteButtonClicked)
    EVT_COMMAND(ID_REFRESH_BUTTON, wxEVT_COMMAND_TOOL_CLICKED, MainFrame::OnRefreshButtonClicked)
    EVT_COMMAND(ID_ATTACHES_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, MainFrame::OnAttachmentsClicked)
    EVT_COMMAND(EmailService::ID_SENDING_THREAD, wxEVT_THREAD, MainFrame::OnSendingThreadCompletion)
    EVT_COMMAND(EmailService::ID_LOADING_THREAD, wxEVT_THREAD, MainFrame::OnLoadingThreadCompletion)
    EVT_COMMAND(EmailService::ID_BODYLOADING_THREAD, wxEVT_THREAD, MainFrame::OnBodyLoadingThreadCompletion)
    EVT_COMMAND(EmailService::ID_DELETING_THREAD, wxEVT_THREAD, MainFrame::OnDeletingThreadCompletion)
    EVT_COMMAND(EmailService::ID_MOVING_THREAD, wxEVT_THREAD, MainFrame::OnMovingThreadCompletion)
    EVT_COMMAND(EmailService::ID_FLAGSCHANGING_THREAD, wxEVT_THREAD, MainFrame::OnFlagsChangingThreadCompletion)
    EVT_UPDATE_UI_RANGE(ID_ADDACCOUNT_BUTTON, ID_REFRESH_BUTTON, MainFrame::OnToolButtonUpdate)
    EVT_DATAVIEW_ITEM_ACTIVATED(ID_ACC_LIST, MainFrame::OnAccountDoubleClicked)
END_EVENT_TABLE()


MainFrame::MainFrame() :
    BaseMainFrame(nullptr), m_AccountsViewModel(nullptr), m_MessagesViewModel(nullptr),
    m_Browser(wxWebView::New(m_EmailBodyPanel, wxID_ANY, wxWebViewDefaultURLStr)),
    m_AnimationForm(NULL),  m_AnimationCtrl(new wxAnimationCtrl(&m_AnimationForm, wxID_ANY))
{
    SetIcon(wxICON(email));
#ifdef __WXMSW__
    SetBitmaps();
#endif
    AddColumnToAccountList();
    AddColumnsToMessageList();
    m_WebViewSizer->Add(m_Browser, wxSizerFlags().Expand().Proportion(1));
    m_WebViewSizer->Fit(m_EmailBodyPanel);
    const int Widths[] = {100, 400, 300, 300};
    m_StatusBar->SetFieldsCount(4, Widths);
    m_AnimationForm.m_Sizer->Add(m_AnimationCtrl, wxSizerFlags().Expand());
    m_AnimationFileLoaded = m_AnimationCtrl->LoadFile("throbber.gif");
    SetHeaderFieldsFromMessage(Message());
}


#ifdef __WXMSW__
void MainFrame::SetBitmaps()
{
    m_AddAccountToolBtn->SetNormalBitmap(wxICON(addaccount));
    m_WriteToolBtn->SetNormalBitmap(wxICON(write));
    m_MarkReadUnreadToolBtn->SetNormalBitmap(wxICON(read));
    m_ReplyToolBtn->SetNormalBitmap(wxICON(reply));
    m_ReplyAllTooBtn->SetNormalBitmap(wxICON(replyall));
    m_ForwardToolBtn->SetNormalBitmap(wxICON(forward));
    m_MoveToolButton->SetNormalBitmap(wxICON(move));
    m_DeleteToolBtn->SetNormalBitmap(wxICON(delete));
    m_RefreshToolBtn->SetNormalBitmap(wxICON(refresh));
    m_AboutToolBtn->SetNormalBitmap(wxICON(about));
    m_toolBar->Realize();
    m_AttachmentsButton->SetBitmap(wxIcon(wxT("attach"), wxBITMAP_TYPE_ICO_RESOURCE, 16, 16));
}
#endif


std::shared_ptr<Folder> MainFrame::FindUserFolder(const wxString &UserName, const wxString &FolderName) const
{
    std::vector<std::shared_ptr<Folder>> *Folders = nullptr;
    for (auto &F : m_Folders)
    {
        if (F->m_Name != UserName)
        {
            continue;
        }
        Folders = &F->m_Childs;
        for (auto &Ch : F->m_Childs)
        {
            if ((FolderName == wxEmptyString && Ch->m_Default) || Ch->m_Name == FolderName)
            {
                return Ch;
            }
        }
    }
    return (Folders != nullptr && !Folders->empty()) ? Folders->front() : std::shared_ptr<Folder>();
}


void MainFrame::AddColumnToAccountList()
{
    wxDataViewTextRenderer *render = new wxDataViewTextRenderer("string");
    wxDataViewColumn *column =
        new wxDataViewColumn("Accounts", render, 0, 100, wxAlignment(wxALIGN_LEFT | wxALIGN_TOP), wxDATAVIEW_COL_RESIZABLE);
    m_AccountListTree->AppendColumn(column);
    m_AccountsViewModel = new AccountFolderViewModel(m_Folders);
    m_AccountListTree->AssociateModel(m_AccountsViewModel);
}


void MainFrame::AddColumnsToMessageList()
{
    wxDataViewTextRenderer* render = new wxDataViewTextRenderer("string");
    wxDataViewColumn* column0 =
        new wxDataViewColumn("From", render, 0, 200, wxAlignment(wxALIGN_LEFT | wxALIGN_TOP), wxDATAVIEW_COL_RESIZABLE);
    m_EmailListTree->AppendColumn(column0);
    render = new wxDataViewTextRenderer("string");
    wxDataViewColumn* column1 =
        new wxDataViewColumn("Subject", render, 1, 500, wxAlignment(wxALIGN_LEFT | wxALIGN_TOP), wxDATAVIEW_COL_RESIZABLE);
    m_EmailListTree->AppendColumn(column1);  
    render = new wxDataViewTextRenderer("string");
    wxDataViewColumn* column2 =
        new wxDataViewColumn("Date", render, 2, 40, wxAlignment(wxALIGN_LEFT | wxALIGN_TOP), wxDATAVIEW_COL_RESIZABLE);
    m_EmailListTree->AppendColumn(column2);
    m_MessagesViewModel = new MessageListViewModel(m_CurrentMessages);
    m_EmailListTree->AssociateModel(m_MessagesViewModel);
}


void MainFrame::AddUserFoldersToList(std::vector<std::shared_ptr<Folder>> Folders)
{
    bool Added = false;
    for (auto &UF : Folders)
    {
        if (UF->m_Parent != nullptr)
        {
            continue;
        }
        for (auto &CF : m_Folders)
        {
            if (*UF == *CF && CF->m_Parent == nullptr)
            {
                CF = UF;
                CF->m_Childs = UF->m_Childs;
                Added = true;
            }
        }
    }
    if (!Added)
    {
        m_Folders.insert(
            m_Folders.end(), std::make_move_iterator(Folders.begin()), std::make_move_iterator(Folders.end()));
    }
}


void MainFrame::PopulateUserFolders(const bool NewFolders)
{
    if (!NewFolders)
    {
        return;
    }
    auto UserFolders = TheApp->GetEmailService()->GetUserFolders(m_CurrentUser);
    if (UserFolders.empty())
    {
        return;
    }
    AddUserFoldersToList(UserFolders);
    m_AccountsViewModel->Cleared();
    const wxDataViewItem DefFolderItem = m_AccountsViewModel->GetDefaultFolderItem(m_CurrentUser);
    if (DefFolderItem.IsOk())
    {
        m_AccountListTree->Select(DefFolderItem);
        m_AccountListTree->EnsureVisible(DefFolderItem, 0);
    }
}


wxString MainFrame::SelectedItemToUserName() const
{
    const wxDataViewItem Item = m_AccountListTree->GetCurrentItem();
    if (!Item.IsOk())
    {
        return "";
    }
    Folder* folder = reinterpret_cast<Folder*>(Item.GetID());
    return folder->m_Parent == nullptr ? folder->m_Name : folder->m_Parent->m_Name;
}


void MainFrame::PopulateMessageList()
{
    if (m_CurrentFolder.get() == nullptr)
    {
        m_CurrentMessages.clear();
    }
    else
    {
        m_CurrentMessages = m_CurrentFolder->m_Messages;
    }
    m_StatusBar->SetStatusText(std::to_string(m_CurrentMessages.size()) + " messages");
    m_MessagesViewModel->Cleared();
}


void MainFrame::OnLoadingTimer(wxTimerEvent& event)
{
    EmailService *EmailSvc = TheApp->GetEmailService();
    if (EmailSvc->LoadFromCache())
    {
        return;
    }
    AccountSettings AcctSettings(TheApp->GetAppName() + ".cfg");
    const std::vector<wxString> Usernames = AcctSettings.GetUserNames();
    for (const auto &Username : Usernames)
    {
        if (AcctSettings.Load(Username) && AcctSettings.HasData() && EmailSvc->AddAccount(AcctSettings))
        {
            m_Folders.push_back(std::make_shared<Folder>(Username));
        }
    }
    if (m_Folders.empty())
    {
        if (AcctSettings.ShowModal() != wxID_OK)
        {
            return;
        }
        if (!AcctSettings.Save())
        {
            wxMessageBox("Cannot save to config file.", "Error", wxICON_ERROR);
            return;
        }
        if (!EmailSvc->AddAccount(AcctSettings))
        {
            return;
        }
        m_CurrentUser = AcctSettings.m_UserNameText->GetValue();
    }
    else
    {
        m_CurrentUser = m_Folders.front()->m_Name;
        m_AccountsViewModel->Cleared();
    }
    if (!GetPasswordFromUser(m_CurrentUser))
    {
        return;
    }
    std::thread LoadingThread(
        &EmailService::LoadMessagesFromServer, EmailSvc, m_CurrentUser, wxEmptyString);
    LoadingThread.detach();
    PlayAnimation();
}


bool MainFrame::GetPasswordFromUser(const wxString &UserName) const
{
    if (UserName.IsEmpty())
    {
        wxMessageBox("Username is empty.", "Error", wxICON_ERROR);
        return false;
    }
    EmailService *EmailSvc = TheApp->GetEmailService();
    if (!EmailSvc->PasswordExists(UserName))
    {
        wxPasswordEntryDialog PwdDlg(nullptr, wxT("Password for ") + UserName);
        if (PwdDlg.ShowModal() != wxID_OK)
        {
            return false;
        }
        if (!EmailSvc->SetPassword(UserName, PwdDlg.GetValue()))
        {
            wxMessageBox("Cannot set password.", "Error", wxICON_ERROR);
            return false;
        }
    }
    return true;
}


void MainFrame::OnFolderSelected(wxDataViewEvent& event)
{
    m_StatusBar->SetStatusText("", 3);
    wxDataViewItem Item = event.GetItem();
    if (!Item.IsOk())
    {
        return;
    }
    Folder* folder = reinterpret_cast<Folder*>(Item.GetID());
    if (m_CurrentFolder.get() == folder)
    {
        return;
    }
    else if (folder->m_Parent == nullptr)
    {
        m_StatusBar->SetStatusText("Double click to change account settings", 3);
        if (!folder->m_Childs.empty())
        {
            return;
        }
        m_CurrentUser = folder->m_Name;
        m_CurrentFolder = FindUserFolder(m_CurrentUser);
        if (!GetPasswordFromUser(m_CurrentUser))
        {
            return;
        }
    }
    else
    {
        if (!m_MessagesToBeMoved.empty())
        {
            MoveMessages(m_CurrentFolder, FindUserFolder(folder->m_Parent->m_Name, folder->m_Name));
            return;
        }
        m_CurrentUser = folder->m_Parent->m_Name;
        m_CurrentFolder = FindUserFolder(m_CurrentUser, folder->m_Name);
    }
    m_CurrentMessages.clear();
    wxString FolderName = wxEmptyString;
    if (m_CurrentFolder.get() != nullptr)
    {
        m_CurrentMessages = m_CurrentFolder->m_Messages;
        FolderName = m_CurrentFolder->m_Name;
    }
    m_MessagesViewModel->Cleared();
    SetHeaderFieldsFromMessage(Message());
    m_StatusBar->SetStatusText(std::to_string(m_CurrentMessages.size()) +" messages");
    m_StatusBar->SetStatusText("Current User: " + m_CurrentUser, 1);
    m_StatusBar->SetStatusText("Current Folder: " + FolderName, 2);
    if (!m_CurrentMessages.empty())
    {
        StopAnimation();
        AutoSelectMessage(m_MessagesViewModel->GetFirstItem());
        return;
    }
    std::thread LoadingThread(
        &EmailService::LoadMessagesFromServer, TheApp->GetEmailService(), m_CurrentUser, FolderName);
    LoadingThread.detach();
    PlayAnimation();
}


void MainFrame::MoveMessages(std::shared_ptr<Folder> Source, std::shared_ptr<Folder> Dest)
{
    if (Source.get() == nullptr)
    {
        wxMessageBox("Source folder not selected.", "Error", wxICON_ERROR);
        return;
    }
    if (Dest.get() == nullptr)
    {
        wxMessageBox("Destination folder not selected.", "Error", wxICON_ERROR);
        return;
    }
    if (Source->m_Parent != Dest->m_Parent)
    {
        wxMessageBox("Please select a folder in the same account.", "Error", wxICON_ERROR);
        return;
    }
    for (const auto &M : m_MessagesToBeMoved)
    {
        auto it = std::find(Dest->m_Messages.begin(), Dest->m_Messages.end(), M);
        if (it == Dest->m_Messages.end())
        {
            Dest->m_Messages.push_back(M);
        }
        it = std::find(Source->m_Messages.begin(), Source->m_Messages.end(), M);
        if (it != Source->m_Messages.end())
        {
            Source->m_Messages.erase(it);
        }
    }
    TheApp->GetEmailService()->ResetMessagesPartners(Source->m_Messages);
    std::sort(
        Dest->m_Messages.begin(),
        Dest->m_Messages.end(),
        [](std::shared_ptr<Message> a, std::shared_ptr<Message> b) {return a->m_Date > b->m_Date;});
    TheApp->GetEmailService()->ResetMessagesPartners(Dest->m_Messages);
    m_CurrentMessages = Source->m_Messages;
    m_MessagesViewModel->Cleared();
    std::thread MovingThread(&EmailService::MoveMessages, TheApp->GetEmailService(), Source, Dest, m_MessagesToBeMoved);
    MovingThread.detach();
    const auto FirstMsg = m_MessagesToBeMoved.front();
    m_MessagesToBeMoved.clear();
    const wxDataViewItem Item = FirstMsg->m_Prev != nullptr ?
        m_MessagesViewModel->FindItemByMessage(*(FirstMsg->m_Prev)) :
        m_MessagesViewModel->GetFirstItem();
    AutoSelectMessage(Item);
}


void MainFrame::AutoSelectMessage(const wxDataViewItem &Item)
{
    m_EmailListTree->Select(Item);
    m_EmailListTree->EnsureVisible(Item);
    wxDataViewEvent MsgEvent(wxEVT_DATAVIEW_SELECTION_CHANGED, m_EmailListTree, 0, Item);
    OnEmailMessageSelected(MsgEvent);
}


void MainFrame::OnLoadingThreadCompletion(wxCommandEvent& event)
{
    StopAnimation();
    std::unique_ptr<LoadNotificationData> NotificationData(
        reinterpret_cast<LoadNotificationData*>(event.GetClientData()));
    if (NotificationData->m_Result)
    {
        PopulateUserFolders(NotificationData->m_RequstedFolderName == wxEmptyString);
        const wxDataViewItem CurrentItem = m_AccountListTree->GetCurrentItem();
        const wxDataViewItem RequstedItem = m_AccountsViewModel->FindItemByUserFolder(
            NotificationData->m_RequstedUserName, NotificationData->m_ResultedFolderName);
        Folder *CurFolder = reinterpret_cast<Folder*>(CurrentItem.GetID());
        Folder *ReqFolder = reinterpret_cast<Folder*>(RequstedItem.GetID());
        m_StatusBar->SetStatusText("", 3);
        if (CurFolder != ReqFolder)
        {
            return;
        }
        m_StatusBar->SetStatusText("Current User: " + NotificationData->m_RequstedUserName, 1);
        m_StatusBar->SetStatusText("Current Folder: " + NotificationData->m_ResultedFolderName, 2);
        m_CurrentFolder = FindUserFolder(NotificationData->m_RequstedUserName, NotificationData->m_ResultedFolderName);
        PopulateMessageList();
        AutoSelectMessage(m_MessagesViewModel->GetFirstItem());
    }
    else
    {
        wxMessageBox(NotificationData->m_ErrorMessage, "Error", wxICON_ERROR);
    }
}


void MainFrame::OnAddAccountButtonClicked(wxCommandEvent& event)
{
    AccountSettings AcctSettings(TheApp->GetAppName() + ".cfg");
    if (AcctSettings.ShowModal() != wxID_OK)
    {
        return;
    }
    if (!AcctSettings.Save())
    {
        wxMessageBox("Cannot save to config file.", "Error", wxICON_ERROR);
        return;
    }
    EmailService *EmailSvc = TheApp->GetEmailService();
    if (!EmailSvc->AddAccount(AcctSettings))
    {
        return;
    }
    m_CurrentUser = AcctSettings.m_UserNameText->GetValue();
    std::thread LoadingThread(
        &EmailService::LoadMessagesFromServer, EmailSvc, m_CurrentUser, wxEmptyString);
    LoadingThread.detach();
    PlayAnimation();
}


void MainFrame::OnWriteButtonClicked(wxCommandEvent& event)
{
    EmailEditorFrame *editor = new EmailEditorFrame(m_CurrentUser, Message());
    editor->Show(true);
}


void MainFrame::OnReplyButtonClicked(wxCommandEvent& event)
{
    const wxDataViewItem Item = m_EmailListTree->GetCurrentItem();
    if (!Item.IsOk())
    {
        wxMessageBox("Please select an email.");
        return;
    }
    Message *Msg = reinterpret_cast<Message*>(Item.GetID());
    EmailEditorFrame *editor = new EmailEditorFrame(m_CurrentUser, *Msg, EmailType::Reply);
    editor->Show(true);
}


void MainFrame::OnReplyAllButtonClicked(wxCommandEvent& event)
{
    const wxDataViewItem Item = m_EmailListTree->GetCurrentItem();
    if (!Item.IsOk())
    {
        wxMessageBox("Please select an email.");
        return;
    }
    Message *Msg = reinterpret_cast<Message*>(Item.GetID());
    EmailEditorFrame *editor = new EmailEditorFrame(m_CurrentUser, *Msg, EmailType::ReplyAll);
    editor->Show(true);
}


void MainFrame::OnForwardButtonClicked(wxCommandEvent& event)
{
    const wxDataViewItem Item = m_EmailListTree->GetCurrentItem();
    if (!Item.IsOk())
    {
        wxMessageBox("Please select an email.");
        return;
    }
    Message *Msg = reinterpret_cast<Message*>(Item.GetID());
    EmailEditorFrame *editor = new EmailEditorFrame(m_CurrentUser, *Msg, EmailType::Forward);
    editor->Show(true);
}


void MainFrame::OnDeleteButtonClicked(wxCommandEvent& event)
{
    wxDataViewItemArray ItemArray;
    m_EmailListTree->GetSelections(ItemArray);
    std::vector<std::shared_ptr<Message>> Msgs;
    for (int i = 0; i < ItemArray.GetCount(); i++)
    {
        if (ItemArray.Item(i).IsOk())
        {
            Msgs.push_back(m_MessagesViewModel->FindMessageByItem(ItemArray.Item(i)));
        }
    }
    if (Msgs.empty() || wxMessageBox(
        std::to_string(Msgs.size()) + " message(s) will be deleted. Are you sure?", "Confirm", wxYES_NO) != wxYES)
    {
        return;
    }
    for (const auto &M : Msgs)
    {
        std::vector<std::shared_ptr<Message>>::iterator it =
            std::find(m_CurrentFolder->m_Messages.begin(), m_CurrentFolder->m_Messages.end(), M);
        if (it != m_CurrentFolder->m_Messages.end())
        {
            m_CurrentFolder->m_Messages.erase(it);
        }
    }
    TheApp->GetEmailService()->ResetMessagesPartners(m_CurrentFolder->m_Messages);
    m_CurrentMessages = m_CurrentFolder->m_Messages;
    m_MessagesViewModel->Cleared();
    m_StatusBar->SetStatusText(std::to_string(m_CurrentMessages.size()) + " messages");
    const wxDataViewItem Item = Msgs[0]->m_Prev != nullptr ?
        m_MessagesViewModel->FindItemByMessage(*(Msgs[0]->m_Prev)) :
        m_MessagesViewModel->GetFirstItem();
    AutoSelectMessage(Item);
    std::thread DeletingThread(&EmailService::DeleteMessages, TheApp->GetEmailService(), m_CurrentFolder, Msgs);
    DeletingThread.detach();
}


void MainFrame::OnMovingThreadCompletion(wxCommandEvent& event)
{
    if (m_CurrentFolder.get() != nullptr)
    {
        const wxDataViewItem Item =
            m_AccountsViewModel->FindItemByUserFolder(m_CurrentFolder->m_Parent->m_Name, m_CurrentFolder->m_Name);
        if (Item.IsOk())
        {
            m_AccountListTree->Select(Item);
        }
    }
    if (!event.GetInt())
    {
        wxMessageBox(event.GetString(), "Error", wxICON_ERROR);
    }
}


void MainFrame::OnDeletingThreadCompletion(wxCommandEvent& event)
{
    if (!event.GetInt())
    {
        wxMessageBox(event.GetString(), "Error", wxICON_ERROR);
    }
}


void MainFrame::OnRefreshButtonClicked(wxCommandEvent& event)
{
    if (!GetPasswordFromUser(m_CurrentUser))
    {
        return;
    }
    const wxDataViewItem CurrentItem = m_AccountListTree->GetCurrentItem();
    if (!CurrentItem.IsOk())
    {
        wxMessageBox("Please select a folder or user name (email address).");
        return;
    }
    Folder* folder = reinterpret_cast<Folder*>(CurrentItem.GetID());
    wxString FolderName = wxEmptyString;
    if (folder->m_Parent != nullptr && m_CurrentFolder.get() != nullptr)
    {
        FolderName = m_CurrentFolder->m_Name;
    }
    std::thread LoadingThread(&EmailService::LoadMessagesFromServer, TheApp->GetEmailService(), m_CurrentUser, FolderName);
    LoadingThread.detach();
    PlayAnimation();
}


void MainFrame::OnEmailMessageSelected(wxDataViewEvent& event)
{
    SetHeaderFieldsFromMessage(Message());
    m_MessagesToBeMoved.clear();
    const wxDataViewItem Item = event.GetItem();
    if (!Item.IsOk())
    {
        return;
    }
    Message *Msg = reinterpret_cast<Message*>(Item.GetID());
    SetHeaderFieldsFromMessage(*Msg);
    if (Msg->m_Body.IsEmpty())
    {
        std::thread BodyLoadingThread(
            &EmailService::GetHTMLPartOfMessage, TheApp->GetEmailService(), m_CurrentFolder, Msg);
        BodyLoadingThread.detach();
        PlayAnimation();
    }
}


void MainFrame::OnBodyLoadingThreadCompletion(wxCommandEvent& event)
{
    StopAnimation();
    if (event.GetInt())
    {
        Message *UIMsg = reinterpret_cast<Message*>(event.GetExtraLong());
        const wxDataViewItem MsgItem = m_MessagesViewModel->FindItemByMessage(*UIMsg);
        if (MsgItem.IsOk())
        {
            m_MessagesViewModel->ItemChanged(MsgItem);
        }
        const wxDataViewItem CurrItem = m_EmailListTree->GetCurrentItem();
        if (m_MessagesViewModel->FindMessageByItem(CurrItem).get() == UIMsg)
        {
            SetHeaderFieldsFromMessage(*UIMsg);
        }
    }
    else
    {
        m_Browser->LoadURL(wxWebViewDefaultURLStr);
        wxMessageBox(event.GetString(), "Error", wxICON_ERROR);
    }
}


void MainFrame::SetHeaderFieldsFromMessage(const Message &Msg)
{
    m_SubjectField->SetValue(Msg.m_Subject);
    m_DateField->SetValue(Msg.GetDateTimeStr());
    m_FromField->SetValue(Msg.m_From.m_Text);
    m_FromField->SetToolTip(Msg.m_From.m_Text);
    wxString ToList;
    for (const auto &To : Msg.m_To)
    {
        ToList = ToList.IsEmpty() ? To.m_Text : (ToList + ";" + To.m_Text);
    }
    m_ToField->SetValue(ToList);
    m_ToField->SetToolTip(ToList);
    wxString CcList;
    for (const auto &Cc : Msg.m_Cc)
    {
        CcList = CcList.IsEmpty() ? Cc.m_Text : (CcList + ";" + Cc.m_Text);
    }
    m_CCField->SetValue(CcList);
    m_CCField->SetToolTip(CcList);
    wxString BCcList;
    for (const auto &BCc : Msg.m_BCc)
    {
        BCcList = BCcList.IsEmpty() ? BCc.m_Text : (BCcList + ";" + BCc.m_Text);
    }
    m_BCCField->SetValue(BCcList);
    m_BCCField->SetToolTip(BCcList);

    m_CCPanel->Show(!CcList.IsEmpty() || !BCcList.IsEmpty());
    m_CCFieldLabel->Show(!CcList.IsEmpty());
    m_CCField->Show(!CcList.IsEmpty());
    m_BCCFieldLabel->Show(!BCcList.IsEmpty());
    m_BCCField->Show(!BCcList.IsEmpty());
    m_AttachmentsButton->Show(!Msg.m_Attachments.empty());
    m_SubjectFieldSizer->Layout();
    m_CCFieldsSizer->Layout();
    m_AttachBtnSizer->Layout();
    m_HeadersSizer->Layout();
    m_WebViewSizer->Layout();
    PopulateAttachmentsMenu(Msg.m_Attachments);
    m_Browser->SetPage(Msg.m_Body.IsEmpty() ? wxString("<html></html>") : Msg.m_Body, "");
}


void MainFrame::PopulateAttachmentsMenu(const std::vector<Message::Attachment> &Attachments)
{
    for (size_t i = 0; i < m_AttachmentsBtnMenu->GetMenuItemCount(); i++)
    {
        wxMenuItem *MI = m_AttachmentsBtnMenu->FindItemByPosition(i);
        m_AttachmentsBtnMenu->Delete(MI);
    }
    m_AttachmentsBtnMenu->GetMenuItems().Clear();
    for (auto &Attachment : Attachments)
    {
	    wxMenuItem* MenuItem = new wxMenuItem(
            m_AttachmentsBtnMenu,
            ID_MENU_ITEMS,
            (Attachment.m_Name.IsEmpty() ? wxString("No Name") : Attachment.m_Name),
            wxEmptyString,
            wxITEM_NORMAL);
	    m_AttachmentsBtnMenu->Append(MenuItem);
        m_AttachmentsBtnMenu->Bind(
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(MainFrame::OnMenuItemSelected),
            this,
            MenuItem->GetId(),
            wxID_ANY,
            reinterpret_cast<wxObject*>(new Message::Attachment(Attachment)));
    }
}


void MainFrame::OnMenuItemSelected(wxCommandEvent& event)
{
    Message::Attachment* Attachment =
        reinterpret_cast<Message::Attachment*>(event.GetEventUserData());
    wxFileDialog SaveFileDialog(
        this,
        "Save attachment",
        wxEmptyString,
        Attachment->m_Name,
        wxFileSelectorDefaultWildcardStr, wxFD_SAVE);
    if (SaveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    std::ofstream File(SaveFileDialog.GetPath().ToStdString(), std::ios::binary);
    File.write(reinterpret_cast<char*>(Attachment->m_Content.data()), Attachment->m_Content.size());
}


void MainFrame::OnAttachmentsClicked(wxCommandEvent& event)
{
    wxPoint P = m_AttachmentsButton->GetPosition();
    P.y += m_AttachmentsButton->GetSize().GetHeight();
    m_FromPanel->PopupMenu(m_AttachmentsBtnMenu, P);
}


void MainFrame::OnSendingThreadCompletion(wxCommandEvent& event)
{
    if (!event.GetInt())
    {
        wxMessageBox(event.GetString(), "Error", wxICON_ERROR);
    }
}


void MainFrame::OnToolButtonUpdate(wxUpdateUIEvent& event)
{
    if (event.GetId() == m_WriteToolBtn->GetId())
    {
        event.Enable(!m_Folders.empty() && !m_CurrentUser.IsEmpty());
    }
    else if (event.GetId() == m_MarkReadUnreadToolBtn->GetId())
    {
        event.Enable(m_EmailListTree->GetSelectedItemsCount() > 0);
    }
    else if (event.GetId() == m_ReplyToolBtn->GetId())
    {
        event.Enable(m_EmailListTree->GetSelectedItemsCount() > 0);
    }
    else if (event.GetId() == m_ReplyAllTooBtn->GetId())
    {
        event.Enable(m_EmailListTree->GetSelectedItemsCount() > 0);
    }
    else if (event.GetId() == m_ForwardToolBtn->GetId())
    {
        event.Enable(m_EmailListTree->GetSelectedItemsCount() > 0);
    }
    else if (event.GetId() == m_MoveToolButton->GetId())
    {
        event.Enable(m_EmailListTree->GetSelectedItemsCount() > 0);
    }
    else if (event.GetId() == m_DeleteToolBtn->GetId())
    {
        event.Enable(m_EmailListTree->GetSelectedItemsCount() > 0);
    }
    else if (event.GetId() == m_RefreshToolBtn->GetId())
    {
        event.Enable(!m_CurrentUser.IsEmpty());
    }
}


void MainFrame::PlayAnimation()
{
    if (!m_AnimationFileLoaded)
    {
        return;
    }
    m_AnimationForm.m_Sizer->Fit(&m_AnimationForm);
    m_AnimationForm.Fit();
    const wxSize AS = m_AnimationForm.GetSize();
    const wxSize BS = m_Browser->GetSize();
    wxPoint P((BS.GetWidth() - AS.GetWidth()) / 2, (BS.GetHeight() - AS.GetHeight()) / 2);
    m_Browser->ClientToScreen(&P.x, &P.y);
    m_AnimationForm.SetPosition(P);
    m_AnimationForm.Show(true);
    m_AnimationCtrl->Play();
}


void MainFrame::StopAnimation()
{
    if (m_AnimationFileLoaded)
    {
        m_AnimationCtrl->Stop();
        m_AnimationForm.Show(false);
    }
}


void MainFrame::OnAccountDoubleClicked(wxDataViewEvent& event)
{
    wxDataViewItem Item = event.GetItem();
    if (!Item.IsOk())
    {
        return;
    }
    Folder* folder = reinterpret_cast<Folder*>(Item.GetID());
    if (folder->m_Parent != nullptr)
    {
        return;
    }
    AccountSettings AcctSettings(TheApp->GetAppName() + ".cfg", "Editing Account Settings");
    if (!AcctSettings.Load(folder->m_Name))
    {
        wxMessageBox("Cannot load account settings.", "Error", wxICON_ERROR);
        return;
    }
    const wxString PWD("PPPPPPPPPPPPPP");
    AcctSettings.m_PasswordText->SetValue(PWD);
    if (AcctSettings.ShowModal() != wxID_OK)
    {
        return;
    }
    if (!AcctSettings.Save(folder->m_Name) || !TheApp->GetEmailService()->AddAccount(AcctSettings, false))
    {
        wxMessageBox("Cannot save account settings.", "Error", wxICON_ERROR);
        return;
    }
    if (AcctSettings.m_PasswordText->GetValue() != PWD &&
        !TheApp->GetEmailService()->SetPassword(folder->m_Name, AcctSettings.m_PasswordText->GetValue()))
    {
        wxMessageBox("Cannot set password.", "Error", wxICON_ERROR);
    }
}


void MainFrame::OnMoveButtonClicked(wxCommandEvent& event)
{
    m_MessagesToBeMoved.clear();
    wxDataViewItemArray ItemArray;
    m_EmailListTree->GetSelections(ItemArray);
    for (int i = 0; i < ItemArray.GetCount(); i++)
    {
        if (ItemArray.Item(i).IsOk())
        {
            m_MessagesToBeMoved.push_back(m_MessagesViewModel->FindMessageByItem(ItemArray.Item(i)));
        }
    }
    if (!m_MessagesToBeMoved.empty())
    {
        m_StatusBar->SetStatusText("Please select a folder to move to", 3);
    }
}


void MainFrame::OnAboutButtonClicked(wxCommandEvent& event)
{
    AboutDialog Dlg(NULL);
    Dlg.ShowModal();
}


void MainFrame::OnMarkReadUnreadButtonClicked(wxCommandEvent& event)
{
    m_ChangingItems.Clear();
    m_EmailListTree->GetSelections(m_ChangingItems);
    std::vector<std::shared_ptr<Message>> Msgs;
    for (int i = 0; i < m_ChangingItems.GetCount(); i++)
    {
        if (m_ChangingItems.Item(i).IsOk())
        {
            Msgs.push_back(m_MessagesViewModel->FindMessageByItem(m_ChangingItems.Item(i)));
        }
    }
    if (Msgs.empty())
    {
        return;
    }
    std::thread MarkReadUnreadThread(
        &EmailService::MarkMessageReadUnread, TheApp->GetEmailService(), m_CurrentFolder, Msgs);
    MarkReadUnreadThread.detach();
}


void MainFrame::OnFlagsChangingThreadCompletion(wxCommandEvent& event)
{
    if (!event.GetInt())
    {
        wxMessageBox(event.GetString(), "Error", wxICON_ERROR);
    }
    else
    {
        const wxDataViewItem CurrentItem = m_AccountListTree->GetCurrentItem();
        Folder *CurFolder = reinterpret_cast<Folder*>(CurrentItem.GetID());
        if (CurFolder == m_CurrentFolder.get())
        {
            m_MessagesViewModel->ItemsChanged(m_ChangingItems);
        }
    }
    m_ChangingItems.Clear();
}
