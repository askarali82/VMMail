///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/toolbar.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/dataview.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/menu.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/splitter.h>
#include <wx/timer.h>
#include <wx/frame.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/choice.h>

///////////////////////////////////////////////////////////////////////////

#define ID_ADDACCOUNT_BUTTON 1000
#define ID_WRITE_BUTTON 1001
#define ID_MARK_RURBUTTON 1002
#define ID_REPLY_BUTTON 1003
#define ID_REPLYALL_BUTTON 1004
#define ID_FORWARD_BUTTON 1005
#define ID_MOVE_BUTTON 1006
#define ID_DELETE_BUTTON 1007
#define ID_REFRESH_BUTTON 1008
#define ID_ABOUT_BUTTON 1009
#define ID_ACC_LIST 1010
#define ID_MSG_LIST 1011
#define ID_ATTACHES_BUTTON 1012
#define ID_LOAD_TIMER 1013
#define ID_TO_FIELD 1014
#define ID_ATTACHMENTLIST 1015
#define ID_ADDATTACHMENT 1016
#define ID_DELETEATTACHMENT 1017
#define ID_FONT_SELECTOR 1018
#define ID_FONTSIZE_SELECTOR 1019
#define ID_BOLD_BUTTON 1020
#define ID_ITALIC_BUTTON 1021
#define ID_UNDERLINE_BUTTON 1022
#define ID_STRIKETHROUGH 1023
#define ID_SUBSCRIPT 1024
#define ID_SUPERSCRIPT 1025
#define ID_TEXT_COLOR 1026
#define ID_BCKG_COLOR 1027
#define ID_CLEAR_FORMATTING 1028
#define ID_ALIGN_LEFT 1029
#define ID_ALIGN_CENTER 1030
#define ID_ALIGN_RIGHT 1031
#define ID_ALIGN_JUSTIFY 1032
#define ID_ORDERED_LIST 1033
#define ID_UNORDERED_LIST 1034
#define ID_ADD_IMAGE 1035
#define ID_INSERT_LINK 1036
#define ID_DISCARD_BUTTON 1037
#define ID_SEND_BUTTON 1038

///////////////////////////////////////////////////////////////////////////////
/// Class BaseMainFrame
///////////////////////////////////////////////////////////////////////////////
class BaseMainFrame : public wxFrame
{
	private:

	protected:
		wxToolBar* m_toolBar;
		wxToolBarToolBase* m_AddAccountToolBtn;
		wxToolBarToolBase* m_WriteToolBtn;
		wxToolBarToolBase* m_MarkReadUnreadToolBtn;
		wxToolBarToolBase* m_ReplyToolBtn;
		wxToolBarToolBase* m_ReplyAllTooBtn;
		wxToolBarToolBase* m_ForwardToolBtn;
		wxToolBarToolBase* m_MoveToolButton;
		wxToolBarToolBase* m_DeleteToolBtn;
		wxToolBarToolBase* m_RefreshToolBtn;
		wxToolBarToolBase* m_AboutToolBtn;
		wxStatusBar* m_StatusBar;
		wxSplitterWindow* m_AccountsEmailsSplitterWndWindow;
		wxPanel* m_AccountsPanel;
		wxDataViewCtrl* m_AccountListTree;
		wxPanel* m_EmailsPanel;
		wxSplitterWindow* m_EmaillistBodySplitterWnd;
		wxPanel* m_EmaillistPanel;
		wxDataViewCtrl* m_EmailListTree;
		wxMenu* m_EmailListMenu;
		wxPanel* m_EmailBodyPanel;
		wxBoxSizer* m_WebViewSizer;
		wxBoxSizer* m_HeadersSizer;
		wxPanel* m_SubjectPanel;
		wxBoxSizer* m_SubjectFieldSizer;
		wxStaticText* m_staticText25;
		wxTextCtrl* m_SubjectField;
		wxStaticText* m_staticText17;
		wxTextCtrl* m_DateField;
		wxPanel* m_FromPanel;
		wxBoxSizer* m_AttachBtnSizer;
		wxStaticText* m_staticText18;
		wxTextCtrl* m_FromField;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_ToField;
		wxButton* m_AttachmentsButton;
		wxPanel* m_CCPanel;
		wxBoxSizer* m_CCFieldsSizer;
		wxStaticText* m_CCFieldLabel;
		wxTextCtrl* m_CCField;
		wxStaticText* m_BCCFieldLabel;
		wxTextCtrl* m_BCCField;
		wxTimer m_LoadingTimer;

		// Virtual event handlers, overide them in your derived class
		virtual void OnAddAccountButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWriteButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMarkReadUnreadButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReplyButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReplyAllButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnForwardButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMoveButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRefreshButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAboutButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAccountDoubleClicked( wxDataViewEvent& event ) { event.Skip(); }
		virtual void OnFolderSelected( wxDataViewEvent& event ) { event.Skip(); }
		virtual void OnEmailMessageSelected( wxDataViewEvent& event ) { event.Skip(); }
		virtual void OnEmailsPanelResized( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnAttachmentsClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadingTimer( wxTimerEvent& event ) { event.Skip(); }


	public:

		BaseMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("VMMail"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1179,679 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~BaseMainFrame();

		void m_AccountsEmailsSplitterWndWindowOnIdle( wxIdleEvent& )
		{
			m_AccountsEmailsSplitterWndWindow->SetSashPosition( 200 );
			m_AccountsEmailsSplitterWndWindow->Disconnect( wxEVT_IDLE, wxIdleEventHandler( BaseMainFrame::m_AccountsEmailsSplitterWndWindowOnIdle ), NULL, this );
		}

		void m_EmaillistBodySplitterWndOnIdle( wxIdleEvent& )
		{
			m_EmaillistBodySplitterWnd->SetSashPosition( 300 );
			m_EmaillistBodySplitterWnd->Disconnect( wxEVT_IDLE, wxIdleEventHandler( BaseMainFrame::m_EmaillistBodySplitterWndOnIdle ), NULL, this );
		}

		void m_EmaillistPanelOnContextMenu( wxMouseEvent &event )
		{
			m_EmaillistPanel->PopupMenu( m_EmailListMenu, event.GetPosition() );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class BaseAccountConfigDialog
///////////////////////////////////////////////////////////////////////////////
class BaseAccountConfigDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText29;
		wxStaticText* m_staticText30;
		wxStaticText* m_staticText31;
		wxStaticText* m_staticText32;
		wxStaticText* m_staticText33;
		wxStaticText* m_staticText34;
		wxStaticText* m_staticText35;
		wxStaticText* m_staticText36;
		wxStaticText* m_staticText37;
		wxStaticText* m_staticText38;
		wxStaticText* m_staticText39;
		wxStaticText* m_staticText40;
		wxStaticText* m_staticText24;
		wxButton* m_OKButton;
		wxButton* m_CancelButton;

	public:
		wxTextCtrl* m_IMAPServerText;
		wxCheckBox* m_IMAPRequiresSSL;
		wxTextCtrl* m_IMAPPortText;
		wxTextCtrl* m_SMTPServerText;
		wxCheckBox* m_SMTPRequiresSSL;
		wxCheckBox* m_SMTPRequiresTLS;
		wxCheckBox* m_SMTPRequiresAuth;
		wxTextCtrl* m_SMTPPortText;
		wxTextCtrl* m_FullNameText;
		wxTextCtrl* m_UserNameText;
		wxTextCtrl* m_PasswordText;

		BaseAccountConfigDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Adding New Account"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~BaseAccountConfigDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class BaseEmailEditorFrame
///////////////////////////////////////////////////////////////////////////////
class BaseEmailEditorFrame : public wxFrame
{
	private:

	protected:
		wxPanel* m_TextFieldsPanel;
		wxBoxSizer* m_TopPanelSizer;
		wxStaticText* m_staticText21;
		wxTextCtrl* m_FromField;
		wxStaticText* m_staticText22;
		wxTextCtrl* m_ToField;
		wxStaticText* m_staticText23;
		wxTextCtrl* m_CCField;
		wxStaticText* m_staticText24;
		wxTextCtrl* m_BCCField;
		wxStaticText* m_staticText25;
		wxTextCtrl* m_Subject;
		wxListBox* m_AttachmentList;
		wxBoxSizer* m_AttachButtonsSizer;
		wxButton* m_AddAttachmentButton;
		wxButton* m_DeleteAttachmentButton;
		wxPanel* m_EditorPanel;
		wxBoxSizer* m_EditorSizer;
		wxToolBar* m_toolBar;
		wxChoice* m_FontChoice;
		wxChoice* m_FontSizeChoice;
		wxToolBarToolBase* m_BoldButton;
		wxToolBarToolBase* m_ItalicButton;
		wxToolBarToolBase* m_UnderlineButton;
		wxToolBarToolBase* m_StrikethroughButton;
		wxToolBarToolBase* m_SubscriptButton;
		wxToolBarToolBase* m_SuperscriptButton;
		wxToolBarToolBase* m_TextColorButton;
		wxToolBarToolBase* m_BckgColorButton;
		wxToolBarToolBase* m_ClearFormattingButton;
		wxToolBarToolBase* m_AlignLeftButton;
		wxToolBarToolBase* m_AlignCenterButton;
		wxToolBarToolBase* m_AlignRightButton;
		wxToolBarToolBase* m_AlignJustifyButton;
		wxToolBarToolBase* m_OrderListButton;
		wxToolBarToolBase* m_UnOrderListButton;
		wxToolBarToolBase* m_AddImageButton;
		wxToolBarToolBase* m_InsertLinkButton;
		wxButton* m_DiscardButton;
		wxButton* m_SendButton;

		// Virtual event handlers, overide them in your derived class
		virtual void OnToFieldKeyPressed( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnToFieldChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToFieldEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCcFieldKeyPressed( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnCcFieldChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCcFieldEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBCcFieldKeyPressed( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnBCcFieldChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBCcFieldEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAttachmentListBoxSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddAttachmentButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteAttachmentButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFontChoosen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFontSizeChoosen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBoldButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnItalicButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUnderlineButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStrikethroughButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSubscriptButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSuperscriptButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextColorButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBckgColorButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClearFormatButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAlignLeftButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAlignCenterButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAlignRightButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAlignJustifyButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOrderedListButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUnOrderedListButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddImageButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnInsertLinkButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDiscardButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSendButtonClicked( wxCommandEvent& event ) { event.Skip(); }


	public:

		BaseEmailEditorFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,700 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~BaseEmailEditorFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class BaseAddressListFrame
///////////////////////////////////////////////////////////////////////////////
class BaseAddressListFrame : public wxFrame
{
	private:

	protected:

		// Virtual event handlers, overide them in your derived class
		virtual void OnListBoxKeyDown( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnItemSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListBoxDblClicked( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxListBox* m_AddressList;

		BaseAddressListFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,200 ), long style = wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxFRAME_SHAPED|wxFRAME_TOOL_WINDOW|wxTAB_TRAVERSAL );

		~BaseAddressListFrame();

};

