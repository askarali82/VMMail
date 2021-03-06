#pragma once

#include "formbuilder/BaseGUIClasses.h"
#include "wx/webview.h"
#include "EmailService.h"
#include <vector>
#include <memory>
#include <wx/animate.h>
#include <wx/activityindicator.h>

class AccountFolderViewModel;
class MessageListViewModel;

class MainFrame : public BaseMainFrame
{
public:
	MainFrame();
    void StartLoadingTimer()
    {
        m_LoadingTimer.StartOnce(1000);
    }
    void CollectEmailAddresses(const Message::EmailAddress &Address = Message::EmailAddress());
    const std::vector<Message::EmailAddress> & GetEmailAddresses() const
    {
        return EmailAddresses;
    }

protected:
    void OnLoadingTimer(wxTimerEvent& event) override;
    void OnFolderSelected(wxDataViewEvent& event) override;
    void OnAddAccountButtonClicked(wxCommandEvent& event) override;
    void OnWriteButtonClicked(wxCommandEvent& event) override;
    void OnReplyButtonClicked(wxCommandEvent& event) override;
    void OnReplyAllButtonClicked(wxCommandEvent& event) override;
    void OnForwardButtonClicked(wxCommandEvent& event) override;
    void OnMoveButtonClicked(wxCommandEvent& event) override;
    void OnDeleteButtonClicked(wxCommandEvent& event) override;
    void OnRefreshButtonClicked(wxCommandEvent& event) override;
    void OnEmailMessageSelected(wxDataViewEvent& event) override;
    void OnAttachmentsClicked(wxCommandEvent& event) override;
    void OnMenuItemSelected(wxCommandEvent& event);
    void OnSendingThreadCompletion(wxCommandEvent& event);
    void OnLoadingThreadCompletion(wxCommandEvent& event);
    void OnBodyLoadingThreadCompletion(wxCommandEvent& event);
    void OnDeletingThreadCompletion(wxCommandEvent& event);
    void OnMovingThreadCompletion(wxCommandEvent& event);
    void OnFlagsChangingThreadCompletion(wxCommandEvent& event);
    void OnAccountDoubleClicked(wxDataViewEvent& event) override;
    void OnAboutButtonClicked(wxCommandEvent& event) override;
    void OnMarkReadUnreadButtonClicked(wxCommandEvent& event) override;

private:
    AccountFolderViewModel *m_AccountsViewModel;
    MessageListViewModel *m_MessagesViewModel;
    wxWebView *m_Browser;
    std::unique_ptr<wxMenu> m_AttachmentsBtnMenu;

    wxString m_CurrentUser;
    std::shared_ptr<Folder> m_CurrentFolder;

    std::map<wxString, wxString> m_UserLastFolderMap;

    std::vector<std::shared_ptr<Folder>> m_Folders;
    std::vector<std::shared_ptr<Message>> m_CurrentMessages;
    std::vector<std::shared_ptr<Message>> m_MessagesToBeMoved;
    std::vector<Message::EmailAddress> EmailAddresses;

    wxDataViewItemArray m_ChangingItems;

    void MoveMessages(std::shared_ptr<Folder> Source, std::shared_ptr<Folder> Dest);
    wxString SelectedItemToUserName() const;
    void AddUserFoldersToList(std::vector<std::shared_ptr<Folder>> Folders);
    bool GetPasswordFromUser(const wxString &UserName) const;
    void AddColumnToAccountList();
    void AddColumnsToMessageList();
    std::shared_ptr<Folder> FindUserFolder(
        const wxString &UserName, const wxString &FolderName = wxEmptyString) const;
    void PopulateUserFolders(const bool NewFolders);
    void PopulateMessageList();
    void AutoSelectMessage(const wxDataViewItem &Item);
    void SetHeaderFieldsFromMessage(const Message &Msg);
    void PopulateAttachmentsMenu(const std::vector<Message::Attachment> &Attachments);
    void OnToolButtonUpdate(wxUpdateUIEvent& event);
    void PlayAnimation();
    void StopAnimation();

#ifdef __WXMSW__
    void SetBitmaps();
#endif

    DECLARE_EVENT_TABLE()
};