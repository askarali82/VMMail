///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "BaseGUIClasses.h"

#include "../bitmaps/about.xpm"
#include "../bitmaps/addaccount.xpm"
#include "../bitmaps/aligncenter.xpm"
#include "../bitmaps/alignjustify.xpm"
#include "../bitmaps/alignleft.xpm"
#include "../bitmaps/alignright.xpm"
#include "../bitmaps/attach.xpm"
#include "../bitmaps/bgcolor.xpm"
#include "../bitmaps/bold.xpm"
#include "../bitmaps/clearformatting.xpm"
#include "../bitmaps/delattach.xpm"
#include "../bitmaps/delete.xpm"
#include "../bitmaps/fgcolor.xpm"
#include "../bitmaps/forward.xpm"
#include "../bitmaps/insertlink.xpm"
#include "../bitmaps/italic.xpm"
#include "../bitmaps/mms.xpm"
#include "../bitmaps/move.xpm"
#include "../bitmaps/ordered.xpm"
#include "../bitmaps/read.xpm"
#include "../bitmaps/refresh.xpm"
#include "../bitmaps/reply.xpm"
#include "../bitmaps/replyall.xpm"
#include "../bitmaps/send.xpm"
#include "../bitmaps/strikethrough.xpm"
#include "../bitmaps/subscript.xpm"
#include "../bitmaps/superscript.xpm"
#include "../bitmaps/underline.xpm"
#include "../bitmaps/unordered.xpm"
#include "../bitmaps/write.xpm"

///////////////////////////////////////////////////////////////////////////

BaseMainFrame::BaseMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_toolBar = this->CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL|wxTB_HORZ_TEXT|wxTB_TEXT, wxID_ANY );
	m_toolBar->SetToolBitmapSize( wxSize( 32,32 ) );
	m_AddAccountToolBtn = m_toolBar->AddTool( ID_ADDACCOUNT_BUTTON, wxT("Add Account"), wxBitmap( addaccount_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Add New Account"), wxEmptyString, NULL );

	m_toolBar->AddSeparator();

	m_WriteToolBtn = m_toolBar->AddTool( ID_WRITE_BUTTON, wxT("New Mail"), wxBitmap( write_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Write New Message"), wxEmptyString, NULL );

	m_toolBar->AddSeparator();

	m_MarkReadUnreadToolBtn = m_toolBar->AddTool( ID_MARK_RURBUTTON, wxT("Mark Read/Unread"), wxBitmap( read_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Mark Read/Unread"), wxEmptyString, NULL );

	m_ReplyToolBtn = m_toolBar->AddTool( ID_REPLY_BUTTON, wxT("Reply"), wxBitmap( reply_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Reply To Sender"), wxEmptyString, NULL );

	m_ReplyAllTooBtn = m_toolBar->AddTool( ID_REPLYALL_BUTTON, wxT("Reply All"), wxBitmap( replyall_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Reply To All"), wxEmptyString, NULL );

	m_ForwardToolBtn = m_toolBar->AddTool( ID_FORWARD_BUTTON, wxT("Forward"), wxBitmap( forward_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Forward Message"), wxEmptyString, NULL );

	m_toolBar->AddSeparator();

	m_MoveToolButton = m_toolBar->AddTool( ID_MOVE_BUTTON, wxT("Move"), wxBitmap( move_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Move Message(s)"), wxEmptyString, NULL );

	m_DeleteToolBtn = m_toolBar->AddTool( ID_DELETE_BUTTON, wxT("Delete"), wxBitmap( delete_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Delete Message(s)"), wxEmptyString, NULL );

	m_toolBar->AddSeparator();

	m_RefreshToolBtn = m_toolBar->AddTool( ID_REFRESH_BUTTON, wxT("Reload"), wxBitmap( refresh_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Reload"), wxEmptyString, NULL );

	m_toolBar->AddSeparator();

	m_AboutToolBtn = m_toolBar->AddTool( ID_ABOUT_BUTTON, wxT("About"), wxBitmap( about_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("About"), wxEmptyString, NULL );

	m_toolBar->Realize();

	m_StatusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	m_AccountsEmailsSplitterWndWindow = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_AccountsEmailsSplitterWndWindow->Connect( wxEVT_IDLE, wxIdleEventHandler( BaseMainFrame::m_AccountsEmailsSplitterWndWindowOnIdle ), NULL, this );
	m_AccountsEmailsSplitterWndWindow->SetMinimumPaneSize( 80 );

	m_AccountsEmailsSplitterWndWindow->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	m_AccountsPanel = new wxPanel( m_AccountsEmailsSplitterWndWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bAccountsSizer;
	bAccountsSizer = new wxBoxSizer( wxVERTICAL );

	m_AccountListTree = new wxDataViewCtrl( m_AccountsPanel, ID_ACC_LIST, wxDefaultPosition, wxDefaultSize, wxDV_SINGLE );
	bAccountsSizer->Add( m_AccountListTree, 1, wxALL|wxEXPAND, 2 );


	m_AccountsPanel->SetSizer( bAccountsSizer );
	m_AccountsPanel->Layout();
	bAccountsSizer->Fit( m_AccountsPanel );
	m_EmailsPanel = new wxPanel( m_AccountsEmailsSplitterWndWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bEmailsSizer;
	bEmailsSizer = new wxBoxSizer( wxVERTICAL );

	m_EmaillistBodySplitterWnd = new wxSplitterWindow( m_EmailsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_EmaillistBodySplitterWnd->Connect( wxEVT_IDLE, wxIdleEventHandler( BaseMainFrame::m_EmaillistBodySplitterWndOnIdle ), NULL, this );

	m_EmaillistBodySplitterWnd->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_EmaillistBodySplitterWnd->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	m_EmaillistPanel = new wxPanel( m_EmaillistBodySplitterWnd, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_EmailListTree = new wxDataViewCtrl( m_EmaillistPanel, ID_MSG_LIST, wxDefaultPosition, wxDefaultSize, wxDV_MULTIPLE );
	bSizer5->Add( m_EmailListTree, 1, wxALL|wxEXPAND, 2 );


	m_EmaillistPanel->SetSizer( bSizer5 );
	m_EmaillistPanel->Layout();
	bSizer5->Fit( m_EmaillistPanel );
	m_EmailListMenu = new wxMenu();
	wxMenuItem* m_MarkRUnRMenuItem;
	m_MarkRUnRMenuItem = new wxMenuItem( m_EmailListMenu, wxID_ANY, wxString( wxT("Mark Read/Unread") ) , wxEmptyString, wxITEM_NORMAL );
	m_EmailListMenu->Append( m_MarkRUnRMenuItem );

	wxMenuItem* m_ReplyMenuItem;
	m_ReplyMenuItem = new wxMenuItem( m_EmailListMenu, wxID_ANY, wxString( wxT("Reply") ) , wxEmptyString, wxITEM_NORMAL );
	m_EmailListMenu->Append( m_ReplyMenuItem );

	wxMenuItem* m_ReplyAllMenuItem;
	m_ReplyAllMenuItem = new wxMenuItem( m_EmailListMenu, wxID_ANY, wxString( wxT("Reply All") ) , wxEmptyString, wxITEM_NORMAL );
	m_EmailListMenu->Append( m_ReplyAllMenuItem );

	wxMenuItem* m_ForwardMenuItem;
	m_ForwardMenuItem = new wxMenuItem( m_EmailListMenu, wxID_ANY, wxString( wxT("Forward") ) , wxEmptyString, wxITEM_NORMAL );
	m_EmailListMenu->Append( m_ForwardMenuItem );

	m_EmailListMenu->AppendSeparator();

	wxMenuItem* m_MoveMenuItem;
	m_MoveMenuItem = new wxMenuItem( m_EmailListMenu, wxID_ANY, wxString( wxT("Move") ) , wxEmptyString, wxITEM_NORMAL );
	m_EmailListMenu->Append( m_MoveMenuItem );

	wxMenuItem* m_DeleteMenuItem;
	m_DeleteMenuItem = new wxMenuItem( m_EmailListMenu, wxID_ANY, wxString( wxT("Delete") ) , wxEmptyString, wxITEM_NORMAL );
	m_EmailListMenu->Append( m_DeleteMenuItem );

	m_EmaillistPanel->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( BaseMainFrame::m_EmaillistPanelOnContextMenu ), NULL, this );

	m_EmailBodyPanel = new wxPanel( m_EmaillistBodySplitterWnd, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_WebViewSizer = new wxBoxSizer( wxVERTICAL );

	m_HeadersSizer = new wxBoxSizer( wxVERTICAL );

	m_SubjectPanel = new wxPanel( m_EmailBodyPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_SubjectFieldSizer = new wxBoxSizer( wxHORIZONTAL );

	m_staticText25 = new wxStaticText( m_SubjectPanel, wxID_ANY, wxT("Subject:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	m_staticText25->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_staticText25->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	m_SubjectFieldSizer->Add( m_staticText25, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );

	m_SubjectField = new wxTextCtrl( m_SubjectPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 500,-1 ), wxTE_READONLY );
	m_SubjectField->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	m_SubjectFieldSizer->Add( m_SubjectField, 1, wxALL|wxEXPAND, 1 );

	m_staticText17 = new wxStaticText( m_SubjectPanel, wxID_ANY, wxT("Date:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText17->Wrap( -1 );
	m_staticText17->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_staticText17->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	m_SubjectFieldSizer->Add( m_staticText17, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );

	m_DateField = new wxTextCtrl( m_SubjectPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), wxTE_READONLY );
	m_SubjectFieldSizer->Add( m_DateField, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );


	m_SubjectPanel->SetSizer( m_SubjectFieldSizer );
	m_SubjectPanel->Layout();
	m_SubjectFieldSizer->Fit( m_SubjectPanel );
	m_HeadersSizer->Add( m_SubjectPanel, 1, wxALL|wxEXPAND, 0 );

	m_FromPanel = new wxPanel( m_EmailBodyPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_AttachBtnSizer = new wxBoxSizer( wxHORIZONTAL );

	m_staticText18 = new wxStaticText( m_FromPanel, wxID_ANY, wxT("From:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText18->Wrap( -1 );
	m_staticText18->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_staticText18->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	m_AttachBtnSizer->Add( m_staticText18, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );

	m_FromField = new wxTextCtrl( m_FromPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), wxTE_READONLY );
	m_AttachBtnSizer->Add( m_FromField, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );

	m_staticText14 = new wxStaticText( m_FromPanel, wxID_ANY, wxT("To:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText14->Wrap( -1 );
	m_staticText14->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_staticText14->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	m_AttachBtnSizer->Add( m_staticText14, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );

	m_ToField = new wxTextCtrl( m_FromPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), wxTE_READONLY );
	m_AttachBtnSizer->Add( m_ToField, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );


	m_AttachBtnSizer->Add( 0, 0, 1, wxEXPAND, 1 );

	m_AttachmentsButton = new wxButton( m_FromPanel, ID_ATTACHES_BUTTON, wxT("Attachments"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE );

	m_AttachmentsButton->SetBitmap( wxBitmap( attach_xpm ) );
	m_AttachmentsButton->Hide();

	m_AttachBtnSizer->Add( m_AttachmentsButton, 0, wxALL, 1 );


	m_FromPanel->SetSizer( m_AttachBtnSizer );
	m_FromPanel->Layout();
	m_AttachBtnSizer->Fit( m_FromPanel );
	m_HeadersSizer->Add( m_FromPanel, 1, wxEXPAND | wxALL, 0 );

	m_CCPanel = new wxPanel( m_EmailBodyPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_CCFieldsSizer = new wxBoxSizer( wxHORIZONTAL );

	m_CCFieldLabel = new wxStaticText( m_CCPanel, wxID_ANY, wxT("Cc:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_CCFieldLabel->Wrap( -1 );
	m_CCFieldLabel->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_CCFieldLabel->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	m_CCFieldsSizer->Add( m_CCFieldLabel, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );

	m_CCField = new wxTextCtrl( m_CCPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), wxTE_READONLY );
	m_CCFieldsSizer->Add( m_CCField, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );

	m_BCCFieldLabel = new wxStaticText( m_CCPanel, wxID_ANY, wxT("BCc:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_BCCFieldLabel->Wrap( -1 );
	m_BCCFieldLabel->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_BCCFieldLabel->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	m_CCFieldsSizer->Add( m_BCCFieldLabel, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );

	m_BCCField = new wxTextCtrl( m_CCPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), wxTE_READONLY );
	m_CCFieldsSizer->Add( m_BCCField, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );


	m_CCPanel->SetSizer( m_CCFieldsSizer );
	m_CCPanel->Layout();
	m_CCFieldsSizer->Fit( m_CCPanel );
	m_HeadersSizer->Add( m_CCPanel, 1, wxEXPAND | wxALL, 0 );


	m_WebViewSizer->Add( m_HeadersSizer, 0, wxEXPAND, 0 );


	m_EmailBodyPanel->SetSizer( m_WebViewSizer );
	m_EmailBodyPanel->Layout();
	m_WebViewSizer->Fit( m_EmailBodyPanel );
	m_EmaillistBodySplitterWnd->SplitHorizontally( m_EmaillistPanel, m_EmailBodyPanel, 300 );
	bEmailsSizer->Add( m_EmaillistBodySplitterWnd, 1, wxEXPAND, 5 );


	m_EmailsPanel->SetSizer( bEmailsSizer );
	m_EmailsPanel->Layout();
	bEmailsSizer->Fit( m_EmailsPanel );
	m_AccountsEmailsSplitterWndWindow->SplitVertically( m_AccountsPanel, m_EmailsPanel, 200 );
	bSizer->Add( m_AccountsEmailsSplitterWndWindow, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer );
	this->Layout();
	m_LoadingTimer.SetOwner( this, ID_LOAD_TIMER );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( m_AddAccountToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnAddAccountButtonClicked ) );
	this->Connect( m_WriteToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnWriteButtonClicked ) );
	this->Connect( m_MarkReadUnreadToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnMarkReadUnreadButtonClicked ) );
	this->Connect( m_ReplyToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnReplyButtonClicked ) );
	this->Connect( m_ReplyAllTooBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnReplyAllButtonClicked ) );
	this->Connect( m_ForwardToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnForwardButtonClicked ) );
	this->Connect( m_MoveToolButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnMoveButtonClicked ) );
	this->Connect( m_DeleteToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnDeleteButtonClicked ) );
	this->Connect( m_RefreshToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnRefreshButtonClicked ) );
	this->Connect( m_AboutToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnAboutButtonClicked ) );
	m_AccountListTree->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( BaseMainFrame::OnAccountDoubleClicked ), NULL, this );
	m_AccountListTree->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( BaseMainFrame::OnFolderSelected ), NULL, this );
	m_EmailListTree->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( BaseMainFrame::OnEmailMessageSelected ), NULL, this );
	m_EmailBodyPanel->Connect( wxEVT_SIZE, wxSizeEventHandler( BaseMainFrame::OnEmailsPanelResized ), NULL, this );
	m_AttachmentsButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::OnAttachmentsClicked ), NULL, this );
	this->Connect( ID_LOAD_TIMER, wxEVT_TIMER, wxTimerEventHandler( BaseMainFrame::OnLoadingTimer ) );
}

BaseMainFrame::~BaseMainFrame()
{
	// Disconnect Events
	this->Disconnect( m_AddAccountToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnAddAccountButtonClicked ) );
	this->Disconnect( m_WriteToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnWriteButtonClicked ) );
	this->Disconnect( m_MarkReadUnreadToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnMarkReadUnreadButtonClicked ) );
	this->Disconnect( m_ReplyToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnReplyButtonClicked ) );
	this->Disconnect( m_ReplyAllTooBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnReplyAllButtonClicked ) );
	this->Disconnect( m_ForwardToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnForwardButtonClicked ) );
	this->Disconnect( m_MoveToolButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnMoveButtonClicked ) );
	this->Disconnect( m_DeleteToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnDeleteButtonClicked ) );
	this->Disconnect( m_RefreshToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnRefreshButtonClicked ) );
	this->Disconnect( m_AboutToolBtn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseMainFrame::OnAboutButtonClicked ) );
	m_AccountListTree->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( BaseMainFrame::OnAccountDoubleClicked ), NULL, this );
	m_AccountListTree->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( BaseMainFrame::OnFolderSelected ), NULL, this );
	m_EmailListTree->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( BaseMainFrame::OnEmailMessageSelected ), NULL, this );
	m_EmailBodyPanel->Disconnect( wxEVT_SIZE, wxSizeEventHandler( BaseMainFrame::OnEmailsPanelResized ), NULL, this );
	m_AttachmentsButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseMainFrame::OnAttachmentsClicked ), NULL, this );
	this->Disconnect( ID_LOAD_TIMER, wxEVT_TIMER, wxTimerEventHandler( BaseMainFrame::OnLoadingTimer ) );

	delete m_EmailListMenu;
}

BaseAccountConfigDialog::BaseAccountConfigDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_staticText29 = new wxStaticText( this, wxID_ANY, wxT("Incoming Mail (IMAP) Server"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	bSizer9->Add( m_staticText29, 0, wxALL|wxTOP, 5 );

	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText30 = new wxStaticText( this, wxID_ANY, wxT("Server: *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer4->Add( m_staticText30, 0, wxALL, 5 );

	m_IMAPServerText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	fgSizer4->Add( m_IMAPServerText, 0, wxALL, 5 );

	m_staticText31 = new wxStaticText( this, wxID_ANY, wxT("Requires SSL:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizer4->Add( m_staticText31, 0, wxALL, 5 );

	m_IMAPRequiresSSL = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_IMAPRequiresSSL->SetValue(true);
	fgSizer4->Add( m_IMAPRequiresSSL, 0, wxALL, 5 );

	m_staticText32 = new wxStaticText( this, wxID_ANY, wxT("Port: *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer4->Add( m_staticText32, 0, wxALL, 5 );

	m_IMAPPortText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	fgSizer4->Add( m_IMAPPortText, 0, wxALL, 5 );


	bSizer9->Add( fgSizer4, 0, wxBOTTOM|wxLEFT, 20 );

	m_staticText33 = new wxStaticText( this, wxID_ANY, wxT("Outgoing Mail (SMTP) Server"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	bSizer9->Add( m_staticText33, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText34 = new wxStaticText( this, wxID_ANY, wxT("Server: *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	fgSizer5->Add( m_staticText34, 0, wxALL, 5 );

	m_SMTPServerText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	fgSizer5->Add( m_SMTPServerText, 0, wxALL, 5 );

	m_staticText35 = new wxStaticText( this, wxID_ANY, wxT("Requires SSL:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer5->Add( m_staticText35, 0, wxALL, 5 );

	m_SMTPRequiresSSL = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_SMTPRequiresSSL->SetValue(true);
	fgSizer5->Add( m_SMTPRequiresSSL, 0, wxALL, 5 );

	m_staticText36 = new wxStaticText( this, wxID_ANY, wxT("Requires TLS (if available):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	fgSizer5->Add( m_staticText36, 0, wxALL, 5 );

	m_SMTPRequiresTLS = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( m_SMTPRequiresTLS, 0, wxALL, 5 );

	m_staticText37 = new wxStaticText( this, wxID_ANY, wxT("Requires Authentication:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	fgSizer5->Add( m_staticText37, 0, wxALL, 5 );

	m_SMTPRequiresAuth = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_SMTPRequiresAuth->SetValue(true);
	fgSizer5->Add( m_SMTPRequiresAuth, 0, wxALL, 5 );

	m_staticText38 = new wxStaticText( this, wxID_ANY, wxT("Port for SSL / TLS: *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	fgSizer5->Add( m_staticText38, 0, wxALL, 5 );

	m_SMTPPortText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	fgSizer5->Add( m_SMTPPortText, 0, wxALL, 5 );


	bSizer9->Add( fgSizer5, 0, wxBOTTOM|wxLEFT, 20 );

	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText39 = new wxStaticText( this, wxID_ANY, wxT("Full Name or Display Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	fgSizer6->Add( m_staticText39, 0, wxALL, 5 );

	m_FullNameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	fgSizer6->Add( m_FullNameText, 0, wxALL, 5 );

	m_staticText40 = new wxStaticText( this, wxID_ANY, wxT("User Name / Email Address: *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	fgSizer6->Add( m_staticText40, 0, wxALL, 5 );

	m_UserNameText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	fgSizer6->Add( m_UserNameText, 0, wxALL, 5 );

	m_staticText24 = new wxStaticText( this, wxID_ANY, wxT("Password (NOT stored in FS): *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	m_staticText24->SetToolTip( wxT("Password is not stored in filesystem") );

	fgSizer6->Add( m_staticText24, 0, wxALL, 5 );

	m_PasswordText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), wxTE_PASSWORD );
	m_PasswordText->SetToolTip( wxT("Password is not stored in filesystem") );

	fgSizer6->Add( m_PasswordText, 0, wxALL, 5 );


	bSizer9->Add( fgSizer6, 0, wxEXPAND, 5 );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );

	m_OKButton = new wxButton( this, wxID_OK, wxT("&OK"), wxDefaultPosition, wxDefaultSize, 0 );

	m_OKButton->SetDefault();
	gSizer2->Add( m_OKButton, 0, wxALIGN_BOTTOM|wxALIGN_RIGHT|wxALL, 10 );

	m_CancelButton = new wxButton( this, wxID_CANCEL, wxT("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_CancelButton, 0, wxALIGN_BOTTOM|wxALIGN_LEFT|wxALL, 10 );


	bSizer9->Add( gSizer2, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer9 );
	this->Layout();
	bSizer9->Fit( this );

	this->Centre( wxBOTH );
}

BaseAccountConfigDialog::~BaseAccountConfigDialog()
{
}

BaseEmailEditorFrame::BaseEmailEditorFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 1000,-1 ), wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	wxBoxSizer* m_Sizer;
	m_Sizer = new wxBoxSizer( wxVERTICAL );

	m_Sizer->SetMinSize( wxSize( 1006,693 ) );
	m_TextFieldsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_TextFieldsPanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	m_TopPanelSizer = new wxBoxSizer( wxHORIZONTAL );

	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText21 = new wxStaticText( m_TextFieldsPanel, wxID_ANY, wxT("From:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	m_staticText21->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	fgSizer4->Add( m_staticText21, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_FromField = new wxTextCtrl( m_TextFieldsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,-1 ), 0 );
	m_FromField->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	fgSizer4->Add( m_FromField, 0, wxALL, 5 );

	m_staticText22 = new wxStaticText( m_TextFieldsPanel, wxID_ANY, wxT("To:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	m_staticText22->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	fgSizer4->Add( m_staticText22, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_ToField = new wxTextCtrl( m_TextFieldsPanel, ID_TO_FIELD, wxEmptyString, wxDefaultPosition, wxSize( 400,-1 ), wxTE_PROCESS_ENTER );
	fgSizer4->Add( m_ToField, 0, wxALL, 5 );

	m_staticText23 = new wxStaticText( m_TextFieldsPanel, wxID_ANY, wxT("Cc:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	m_staticText23->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	fgSizer4->Add( m_staticText23, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_CCField = new wxTextCtrl( m_TextFieldsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,-1 ), wxTE_PROCESS_ENTER );
	fgSizer4->Add( m_CCField, 0, wxALL, 5 );

	m_staticText24 = new wxStaticText( m_TextFieldsPanel, wxID_ANY, wxT("BCc:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	m_staticText24->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	fgSizer4->Add( m_staticText24, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_BCCField = new wxTextCtrl( m_TextFieldsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,-1 ), wxTE_PROCESS_ENTER );
	fgSizer4->Add( m_BCCField, 0, wxALL, 5 );

	m_staticText25 = new wxStaticText( m_TextFieldsPanel, wxID_ANY, wxT("Subject:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	m_staticText25->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	fgSizer4->Add( m_staticText25, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_Subject = new wxTextCtrl( m_TextFieldsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,-1 ), 0 );
	m_Subject->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	fgSizer4->Add( m_Subject, 0, wxALL, 5 );


	m_TopPanelSizer->Add( fgSizer4, 1, wxEXPAND, 5 );


	m_TopPanelSizer->Add( 0, 0, 1, wxEXPAND, 5 );

	m_AttachmentList = new wxListBox( m_TextFieldsPanel, ID_ATTACHMENTLIST, wxDefaultPosition, wxSize( 280,-1 ), 0, NULL, wxLB_HSCROLL );
	m_AttachmentList->Hide();

	m_TopPanelSizer->Add( m_AttachmentList, 0, wxALL|wxEXPAND, 5 );

	m_AttachButtonsSizer = new wxBoxSizer( wxVERTICAL );

	m_AddAttachmentButton = new wxButton( m_TextFieldsPanel, ID_ADDATTACHMENT, wxT("Add Attachment"), wxDefaultPosition, wxSize( 160,-1 ), 0 );

	m_AddAttachmentButton->SetBitmap( wxBitmap( attach_xpm ) );
	m_AttachButtonsSizer->Add( m_AddAttachmentButton, 0, wxALIGN_RIGHT|wxALL, 2 );

	m_DeleteAttachmentButton = new wxButton( m_TextFieldsPanel, ID_DELETEATTACHMENT, wxT("Delete Attachment"), wxDefaultPosition, wxSize( 160,-1 ), 0 );

	m_DeleteAttachmentButton->SetBitmap( wxBitmap( delattach_xpm ) );
	m_DeleteAttachmentButton->Hide();

	m_AttachButtonsSizer->Add( m_DeleteAttachmentButton, 0, wxALIGN_RIGHT|wxALL, 2 );


	m_TopPanelSizer->Add( m_AttachButtonsSizer, 1, wxEXPAND, 5 );


	m_TextFieldsPanel->SetSizer( m_TopPanelSizer );
	m_TextFieldsPanel->Layout();
	m_TopPanelSizer->Fit( m_TextFieldsPanel );
	m_Sizer->Add( m_TextFieldsPanel, 1, wxEXPAND | wxALL, 2 );

	m_EditorPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_EditorPanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DDKSHADOW ) );

	m_EditorSizer = new wxBoxSizer( wxVERTICAL );

	m_toolBar = new wxToolBar( m_EditorPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );
	m_toolBar->SetToolBitmapSize( wxSize( 20,20 ) );
	wxArrayString m_FontChoiceChoices;
	m_FontChoice = new wxChoice( m_toolBar, ID_FONT_SELECTOR, wxDefaultPosition, wxSize( 180,-1 ), m_FontChoiceChoices, 0 );
	m_FontChoice->SetSelection( 0 );
	m_FontChoice->SetToolTip( wxT("Font Name") );

	m_toolBar->AddControl( m_FontChoice );
	m_toolBar->AddSeparator();

	wxArrayString m_FontSizeChoiceChoices;
	m_FontSizeChoice = new wxChoice( m_toolBar, ID_FONTSIZE_SELECTOR, wxDefaultPosition, wxDefaultSize, m_FontSizeChoiceChoices, 0 );
	m_FontSizeChoice->SetSelection( 0 );
	m_FontSizeChoice->SetToolTip( wxT("Font Size") );

	m_toolBar->AddControl( m_FontSizeChoice );
	m_toolBar->AddSeparator();

	m_BoldButton = m_toolBar->AddTool( ID_BOLD_BUTTON, wxT("tool"), wxBitmap( bold_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Bold"), wxEmptyString, NULL );

	m_ItalicButton = m_toolBar->AddTool( ID_ITALIC_BUTTON, wxT("tool"), wxBitmap( italic_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Italic"), wxEmptyString, NULL );

	m_UnderlineButton = m_toolBar->AddTool( ID_UNDERLINE_BUTTON, wxT("tool"), wxBitmap( underline_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Underline"), wxEmptyString, NULL );

	m_StrikethroughButton = m_toolBar->AddTool( ID_STRIKETHROUGH, wxT("tool"), wxBitmap( strikethrough_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Strikethrough"), wxEmptyString, NULL );

	m_SubscriptButton = m_toolBar->AddTool( ID_SUBSCRIPT, wxT("tool"), wxBitmap( subscript_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Subscript"), wxEmptyString, NULL );

	m_SuperscriptButton = m_toolBar->AddTool( ID_SUPERSCRIPT, wxT("tool"), wxBitmap( superscript_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Superscript"), wxEmptyString, NULL );

	m_TextColorButton = m_toolBar->AddTool( ID_TEXT_COLOR, wxT("tool"), wxBitmap( fgcolor_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Text Color"), wxEmptyString, NULL );

	m_BckgColorButton = m_toolBar->AddTool( ID_BCKG_COLOR, wxT("tool"), wxBitmap( bgcolor_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Text Background Color"), wxEmptyString, NULL );

	m_ClearFormattingButton = m_toolBar->AddTool( ID_CLEAR_FORMATTING, wxT("tool"), wxBitmap( clearformatting_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Remove Formatting"), wxEmptyString, NULL );

	m_toolBar->AddSeparator();

	m_AlignLeftButton = m_toolBar->AddTool( ID_ALIGN_LEFT, wxT("tool"), wxBitmap( alignleft_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Align Left"), wxEmptyString, NULL );

	m_AlignCenterButton = m_toolBar->AddTool( ID_ALIGN_CENTER, wxT("tool"), wxBitmap( aligncenter_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Align Center"), wxEmptyString, NULL );

	m_AlignRightButton = m_toolBar->AddTool( ID_ALIGN_RIGHT, wxT("tool"), wxBitmap( alignright_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Align Right"), wxEmptyString, NULL );

	m_AlignJustifyButton = m_toolBar->AddTool( ID_ALIGN_JUSTIFY, wxT("tool"), wxBitmap( alignjustify_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Align Justify"), wxEmptyString, NULL );

	m_OrderListButton = m_toolBar->AddTool( ID_ORDERED_LIST, wxT("tool"), wxBitmap( ordered_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Ordered List"), wxEmptyString, NULL );

	m_UnOrderListButton = m_toolBar->AddTool( ID_UNORDERED_LIST, wxT("tool"), wxBitmap( unordered_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Unordered List"), wxEmptyString, NULL );

	m_toolBar->AddSeparator();

	m_AddImageButton = m_toolBar->AddTool( ID_ADD_IMAGE, wxT("tool"), wxBitmap( mms_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Insert Image"), wxEmptyString, NULL );

	m_InsertLinkButton = m_toolBar->AddTool( ID_INSERT_LINK, wxT("tool"), wxBitmap( insertlink_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Insert Link"), wxEmptyString, NULL );

	m_toolBar->Realize();

	m_EditorSizer->Add( m_toolBar, 0, wxEXPAND, 5 );


	m_EditorPanel->SetSizer( m_EditorSizer );
	m_EditorPanel->Layout();
	m_EditorSizer->Fit( m_EditorPanel );
	m_Sizer->Add( m_EditorPanel, 10, wxEXPAND | wxALL, 2 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );


	bSizer14->Add( 0, 0, 1, wxEXPAND, 5 );

	m_DiscardButton = new wxButton( this, ID_DISCARD_BUTTON, wxT("&Discard"), wxDefaultPosition, wxSize( 100,-1 ), 0 );

	m_DiscardButton->SetBitmap( wxBitmap( delete_xpm ) );
	bSizer14->Add( m_DiscardButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_SendButton = new wxButton( this, ID_SEND_BUTTON, wxT("&Send"), wxDefaultPosition, wxSize( 100,-1 ), 0 );

	m_SendButton->SetBitmap( wxBitmap( send_xpm ) );
	bSizer14->Add( m_SendButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	m_Sizer->Add( bSizer14, 1, wxEXPAND, 2 );


	this->SetSizer( m_Sizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_ToField->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( BaseEmailEditorFrame::OnToFieldKeyPressed ), NULL, this );
	m_ToField->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( BaseEmailEditorFrame::OnToFieldChanged ), NULL, this );
	m_ToField->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( BaseEmailEditorFrame::OnToFieldEnter ), NULL, this );
	m_CCField->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( BaseEmailEditorFrame::OnCcFieldKeyPressed ), NULL, this );
	m_CCField->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( BaseEmailEditorFrame::OnCcFieldChanged ), NULL, this );
	m_CCField->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( BaseEmailEditorFrame::OnCcFieldEnter ), NULL, this );
	m_BCCField->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( BaseEmailEditorFrame::OnBCcFieldKeyPressed ), NULL, this );
	m_BCCField->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( BaseEmailEditorFrame::OnBCcFieldChanged ), NULL, this );
	m_BCCField->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( BaseEmailEditorFrame::OnBCcFieldEnter ), NULL, this );
	m_AttachmentList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( BaseEmailEditorFrame::OnAttachmentListBoxSelected ), NULL, this );
	m_AddAttachmentButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAddAttachmentButtonClicked ), NULL, this );
	m_DeleteAttachmentButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnDeleteAttachmentButtonClicked ), NULL, this );
	m_FontChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( BaseEmailEditorFrame::OnFontChoosen ), NULL, this );
	m_FontSizeChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( BaseEmailEditorFrame::OnFontSizeChoosen ), NULL, this );
	this->Connect( m_BoldButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnBoldButtonClicked ) );
	this->Connect( m_ItalicButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnItalicButtonClicked ) );
	this->Connect( m_UnderlineButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnUnderlineButtonClicked ) );
	this->Connect( m_StrikethroughButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnStrikethroughButtonClicked ) );
	this->Connect( m_SubscriptButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnSubscriptButtonClicked ) );
	this->Connect( m_SuperscriptButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnSuperscriptButtonClicked ) );
	this->Connect( m_TextColorButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnTextColorButtonClicked ) );
	this->Connect( m_BckgColorButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnBckgColorButtonClicked ) );
	this->Connect( m_ClearFormattingButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnClearFormatButtonClicked ) );
	this->Connect( m_AlignLeftButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAlignLeftButtonClicked ) );
	this->Connect( m_AlignCenterButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAlignCenterButtonClicked ) );
	this->Connect( m_AlignRightButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAlignRightButtonClicked ) );
	this->Connect( m_AlignJustifyButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAlignJustifyButtonClicked ) );
	this->Connect( m_OrderListButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnOrderedListButtonClicked ) );
	this->Connect( m_UnOrderListButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnUnOrderedListButtonClicked ) );
	this->Connect( m_AddImageButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAddImageButtonClicked ) );
	this->Connect( m_InsertLinkButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnInsertLinkButtonClicked ) );
	m_DiscardButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnDiscardButtonClicked ), NULL, this );
	m_SendButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnSendButtonClicked ), NULL, this );
}

BaseEmailEditorFrame::~BaseEmailEditorFrame()
{
	// Disconnect Events
	m_ToField->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( BaseEmailEditorFrame::OnToFieldKeyPressed ), NULL, this );
	m_ToField->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( BaseEmailEditorFrame::OnToFieldChanged ), NULL, this );
	m_ToField->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( BaseEmailEditorFrame::OnToFieldEnter ), NULL, this );
	m_CCField->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( BaseEmailEditorFrame::OnCcFieldKeyPressed ), NULL, this );
	m_CCField->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( BaseEmailEditorFrame::OnCcFieldChanged ), NULL, this );
	m_CCField->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( BaseEmailEditorFrame::OnCcFieldEnter ), NULL, this );
	m_BCCField->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( BaseEmailEditorFrame::OnBCcFieldKeyPressed ), NULL, this );
	m_BCCField->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( BaseEmailEditorFrame::OnBCcFieldChanged ), NULL, this );
	m_BCCField->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( BaseEmailEditorFrame::OnBCcFieldEnter ), NULL, this );
	m_AttachmentList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( BaseEmailEditorFrame::OnAttachmentListBoxSelected ), NULL, this );
	m_AddAttachmentButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAddAttachmentButtonClicked ), NULL, this );
	m_DeleteAttachmentButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnDeleteAttachmentButtonClicked ), NULL, this );
	m_FontChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( BaseEmailEditorFrame::OnFontChoosen ), NULL, this );
	m_FontSizeChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( BaseEmailEditorFrame::OnFontSizeChoosen ), NULL, this );
	this->Disconnect( m_BoldButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnBoldButtonClicked ) );
	this->Disconnect( m_ItalicButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnItalicButtonClicked ) );
	this->Disconnect( m_UnderlineButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnUnderlineButtonClicked ) );
	this->Disconnect( m_StrikethroughButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnStrikethroughButtonClicked ) );
	this->Disconnect( m_SubscriptButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnSubscriptButtonClicked ) );
	this->Disconnect( m_SuperscriptButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnSuperscriptButtonClicked ) );
	this->Disconnect( m_TextColorButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnTextColorButtonClicked ) );
	this->Disconnect( m_BckgColorButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnBckgColorButtonClicked ) );
	this->Disconnect( m_ClearFormattingButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnClearFormatButtonClicked ) );
	this->Disconnect( m_AlignLeftButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAlignLeftButtonClicked ) );
	this->Disconnect( m_AlignCenterButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAlignCenterButtonClicked ) );
	this->Disconnect( m_AlignRightButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAlignRightButtonClicked ) );
	this->Disconnect( m_AlignJustifyButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAlignJustifyButtonClicked ) );
	this->Disconnect( m_OrderListButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnOrderedListButtonClicked ) );
	this->Disconnect( m_UnOrderListButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnUnOrderedListButtonClicked ) );
	this->Disconnect( m_AddImageButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnAddImageButtonClicked ) );
	this->Disconnect( m_InsertLinkButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnInsertLinkButtonClicked ) );
	m_DiscardButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnDiscardButtonClicked ), NULL, this );
	m_SendButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseEmailEditorFrame::OnSendButtonClicked ), NULL, this );

}

BaseAddressListFrame::BaseAddressListFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );

	m_AddressList = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer16->Add( m_AddressList, 1, wxALL|wxEXPAND, 1 );


	this->SetSizer( bSizer16 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_AddressList->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( BaseAddressListFrame::OnListBoxKeyDown ), NULL, this );
	m_AddressList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( BaseAddressListFrame::OnItemSelected ), NULL, this );
	m_AddressList->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( BaseAddressListFrame::OnListBoxDblClicked ), NULL, this );
}

BaseAddressListFrame::~BaseAddressListFrame()
{
	// Disconnect Events
	m_AddressList->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( BaseAddressListFrame::OnListBoxKeyDown ), NULL, this );
	m_AddressList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( BaseAddressListFrame::OnItemSelected ), NULL, this );
	m_AddressList->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( BaseAddressListFrame::OnListBoxDblClicked ), NULL, this );

}
