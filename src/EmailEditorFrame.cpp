#include "EmailEditorFrame.h"
#include "EmailClientApp.h"
#include "MainFrame.h"
#include <wx/fontdlg.h>
#include <wx/font.h>
#include <wx/clipbrd.h>
#include <wx/colordlg.h>
#include <wx/colourdata.h>
#include <wx/base64.h>
#include <wx/fontenum.h>
#include "EmailService.h"
#include <string>
#include <wx/tokenzr.h> 
#ifdef WIN32
#include "mingw-std-threads/mingw.thread.h"
#else
#include <thread>
#endif

#ifndef __WXMSW__
    #include "bitmaps/email.xpm"
#endif

BEGIN_EVENT_TABLE(EmailEditorFrame, wxFrame)
    EVT_COMMAND(ID_FONT_SELECTOR, wxEVT_COMMAND_CHOICE_SELECTED, EmailEditorFrame::OnFontChoosen)
    EVT_COMMAND(ID_FONTSIZE_SELECTOR, wxEVT_COMMAND_CHOICE_SELECTED, EmailEditorFrame::OnFontSizeChoosen)
    EVT_COMMAND(ID_BOLD_BUTTON, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnBoldButtonClicked)
    EVT_COMMAND(ID_ITALIC_BUTTON, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnItalicButtonClicked)
    EVT_COMMAND(ID_UNDERLINE_BUTTON, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnUnderlineButtonClicked)
    EVT_COMMAND(ID_TEXT_COLOR, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnTextColorButtonClicked)
    EVT_COMMAND(ID_BCKG_COLOR, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnBckgColorButtonClicked)
    EVT_COMMAND(ID_STRIKETHROUGH, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnStrikethroughButtonClicked)
    EVT_COMMAND(ID_SUBSCRIPT, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnSubscriptButtonClicked)
    EVT_COMMAND(ID_SUPERSCRIPT, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnSuperscriptButtonClicked)
    EVT_COMMAND(ID_ALIGN_LEFT, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnAlignLeftButtonClicked)
    EVT_COMMAND(ID_ALIGN_CENTER, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnAlignCenterButtonClicked)
    EVT_COMMAND(ID_ALIGN_RIGHT, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnAlignRightButtonClicked)
    EVT_COMMAND(ID_ALIGN_JUSTIFY, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnAlignJustifyButtonClicked)
    EVT_COMMAND(ID_CLEAR_FORMATTING, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnClearFormatButtonClicked)
    EVT_COMMAND(ID_ADD_IMAGE, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnAddImageButtonClicked)
    EVT_COMMAND(ID_INSERT_LINK, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnInsertLinkButtonClicked)
    EVT_COMMAND(ID_ORDERED_LIST, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnOrderedListButtonClicked)
    EVT_COMMAND(ID_UNORDERED_LIST, wxEVT_COMMAND_TOOL_CLICKED, EmailEditorFrame::OnUnOrderedListButtonClicked)
    EVT_COMMAND(ID_DISCARD_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, EmailEditorFrame::OnDiscardButtonClicked)
    EVT_COMMAND(ID_SEND_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, EmailEditorFrame::OnSendButtonClicked)
    EVT_COMMAND(ID_ADDATTACHMENT, wxEVT_COMMAND_BUTTON_CLICKED, EmailEditorFrame::OnAddAttachmentButtonClicked)
    EVT_COMMAND(ID_DELETEATTACHMENT, wxEVT_COMMAND_BUTTON_CLICKED, EmailEditorFrame::OnDeleteAttachmentButtonClicked)
    EVT_COMMAND(ID_ATTACHMENTLIST, wxEVT_COMMAND_LISTBOX_SELECTED, EmailEditorFrame::OnAttachmentListBoxSelected)
END_EVENT_TABLE()


EmailEditorFrame::EmailEditorFrame(const wxString &Username, const Message &AMessage, const EmailType AEmailType):
    BaseEmailEditorFrame(nullptr), m_Username(Username), m_Message(AMessage), m_EmailType(AEmailType)
{
    SetIcon(wxICON(email));
#ifdef __WXMSW__
    SetBitmaps();
#endif
    m_Editor = wxWebView::New(
        m_EditorPanel, wxID_ANY, wxWebViewDefaultURLStr);
    m_EditorSizer->Add(m_Editor, wxSizerFlags().Expand().Proportion(1));
    m_EditorSizer->Fit(m_EditorPanel);
    switch (m_EmailType)
    {
        case EmailType::New:
            SetTitle("New Email");
            break;
        case EmailType::Reply:
            SetTitle("Replying To: " + m_Message.m_From.m_Text);
            break;
        case EmailType::ReplyAll:
            SetTitle("Replying All: " + m_Message.m_From.m_Text);
            break;
        case EmailType::Forward:
            SetTitle("Forwarding To: ");
            break;
    }
    Bind(wxEVT_CHAR_HOOK, &EmailEditorFrame::OnKeyPressed, this);
    PopulateFontData();
    PopulateHeaderFields();
    SetBodyToEditor();
    SetFocusToNeededControl();
}


#ifdef __WXMSW__
void EmailEditorFrame::SetBitmaps()
{
    m_AddAttachmentButton->SetBitmap(wxIcon(wxT("attach"), wxBITMAP_TYPE_ICO_RESOURCE, 16, 16));
    m_DeleteAttachmentButton->SetBitmap(wxIcon(wxT("delattach"), wxBITMAP_TYPE_ICO_RESOURCE, 16, 16));
	m_BoldButton->SetNormalBitmap(wxIcon(wxT("bold"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_ItalicButton->SetNormalBitmap(wxIcon(wxT("italic"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_UnderlineButton->SetNormalBitmap(wxIcon(wxT("underline"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_StrikethroughButton->SetNormalBitmap(wxIcon(wxT("strikethrough"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_SubscriptButton->SetNormalBitmap(wxIcon(wxT("subscript"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_SuperscriptButton->SetNormalBitmap(wxIcon(wxT("superscript"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_TextColorButton->SetNormalBitmap(wxIcon(wxT("fgcolor"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_BckgColorButton->SetNormalBitmap(wxIcon(wxT("bgcolor"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_ClearFormattingButton->SetNormalBitmap(wxIcon(wxT("clearformatting"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_AlignLeftButton->SetNormalBitmap(wxIcon(wxT("alignleft"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_AlignCenterButton->SetNormalBitmap(wxIcon(wxT("aligncenter"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_AlignRightButton->SetNormalBitmap(wxIcon(wxT("alignright"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_AlignJustifyButton->SetNormalBitmap(wxIcon(wxT("alignjustify"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_OrderListButton->SetNormalBitmap(wxIcon(wxT("ordered"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_UnOrderListButton->SetNormalBitmap(wxIcon(wxT("unordered"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_AddImageButton->SetNormalBitmap(wxIcon(wxT("mms"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
	m_InsertLinkButton->SetNormalBitmap(wxIcon(wxT("insertlink"), wxBITMAP_TYPE_ICO_RESOURCE, 20, 20));
    m_toolBar->Realize();
    m_DiscardButton->SetBitmap(wxIcon(wxT("delete"), wxBITMAP_TYPE_ICO_RESOURCE, 32, 32));
    m_SendButton->SetBitmap(wxIcon(wxT("send"), wxBITMAP_TYPE_ICO_RESOURCE, 32, 32));
}
#endif


void EmailEditorFrame::PopulateFontData()
{
    wxArrayString fonts = wxFontEnumerator::GetFacenames();
    fonts.Sort();
    m_FontChoice->Append("Font Name");
    for (size_t i = 0; i < fonts.GetCount(); i++)
    {
        m_FontChoice->Append(fonts.Item(i));
    }
    m_FontChoice->SetSelection(m_FontChoice->GetCount() > 0 ? 0 : wxNOT_FOUND);
    m_FontSizeChoice->Append("Font Size");
    for (int i = 1; i <= 7; i++)
    {
        m_FontSizeChoice->Append("Font Size " + std::to_string(i));
    }
    m_FontSizeChoice->SetSelection(m_FontSizeChoice->GetCount() > 0 ? 0 : wxNOT_FOUND);
}


void EmailEditorFrame::Extract_FROM_and_TO_Fields(
    Message::EmailAddress &From, std::vector<Message::EmailAddress> &To)
{
    const wxString Username = m_Username.Lower();
    bool Found = false;
    // In case of incoming message
    for (size_t i = 0; i < m_Message.m_To.size() && !Found; i++)
    {
        if (m_Message.m_To[i].m_Address.Lower().Find(Username) != wxNOT_FOUND)
        {
            From = m_Message.m_To[i];
            Found = true;
        }
    }
    // In case of outgoing message
    if (!Found && m_Message.m_From.m_Address.Lower().Find(Username) != wxNOT_FOUND)
    {
        From = m_Message.m_From;
    }
    if (From.m_Address.IsEmpty())
    {
        TheApp->GetEmailService()->GetFROMFieldForUser(m_Username, From);
    }
    // In case of incoming message
    if (m_Message.m_From.m_Address.Lower().Find(Username) == wxNOT_FOUND)
    {
        To.push_back(m_Message.m_From);
    }
    // In case of outgoing message
    for (size_t i = 0; i < m_Message.m_To.size(); i++)
    {
        if (m_Message.m_To[i].m_Address.Lower().Find(Username) == wxNOT_FOUND)
        {
            To.push_back(m_Message.m_To[i]);
        }
    }
}


void EmailEditorFrame::PopulateHeaderFields()
{
    Message::EmailAddress From;
    std::vector<Message::EmailAddress> To;
    Extract_FROM_and_TO_Fields(From, To);
    m_FromField->SetValue(From.m_Text);
    const wxString Username = m_Username.Lower();
    if (m_EmailType == EmailType::Reply)
    {
        m_Subject->SetValue("RE: " + m_Message.m_Subject);
        m_ToField->SetValue(!To.empty() ? To[0].m_Text : wxString(""));
    }
    else if (m_EmailType == EmailType::ReplyAll)
    {
        m_Subject->SetValue("RE: " + m_Message.m_Subject);
        wxString ToList;
        for (const auto &to : To)
        {
            ToList = ToList.IsEmpty() ? to.m_Text : (ToList + ";" + to.m_Text);
        }
        m_ToField->SetValue(ToList);
        wxString CcList;
        for (const auto &Cc : m_Message.m_Cc)
        {
            if (Cc.m_Address.Lower().Find(Username) == wxNOT_FOUND)
            {
                CcList = CcList.IsEmpty() ? Cc.m_Text : (CcList + ";" + Cc.m_Text);
            }
        }
        m_CCField->SetValue(CcList);
        wxString BCcList;
        for (const auto &BCc : m_Message.m_BCc)
        {
            if (BCc.m_Address.Lower().Find(Username) == wxNOT_FOUND)
            {
                BCcList = BCcList.IsEmpty() ? BCc.m_Text : (BCcList + ";" + BCc.m_Text);
            }
        }
        m_BCCField->SetValue(BCcList);
    }
    else if (m_EmailType == EmailType::Forward)
    {
        m_Subject->SetValue("FWD: " + m_Message.m_Subject);
    }
}


wxString EmailEditorFrame::ExtractFirstNameOfReceiver() const
{
    static const wxString Hi = "Hi,<br><br>";
    wxString Result = m_ToField->GetValue();
    if (Result.IsEmpty())
    {
        return Hi;
    }
    Result.Trim(false).Trim();
    const int P = Result.Find(" ");
    if (P == wxNOT_FOUND)
    {
        Result = Hi;
    }
    else
    {
        Result = "Hi " + Result.Mid(0, P) + ",<br><br>";
    }
    return Result;
}


void EmailEditorFrame::SetBodyToEditor()
{
    m_Editor->SetEditable(true);
    m_Editor->SetFocus();
    const wxString Greeting = ExtractFirstNameOfReceiver();
    if (m_EmailType == EmailType::New)
    {
        m_Editor->SetPage(Greeting, "");
        return;
    }

    wxString ToList;
    for (const auto &To : m_Message.m_To)
    {
        ToList =
            ToList.IsEmpty() ?
            (To.m_Name + " &lt;" + To.m_Address + "&gt;") :
            (ToList + "; " + To.m_Name + " &lt;" + To.m_Address + "&gt;");
    }
    if (!ToList.IsEmpty())
    {
        ToList = "<b>To:</b> " + ToList + "<br>";
    }

    wxString CcList;
    for (const auto &Cc : m_Message.m_Cc)
    {
        CcList =
            CcList.IsEmpty() ?
            (Cc.m_Name + " &lt;" + Cc.m_Address + "&gt;") :
            (CcList + "; " + Cc.m_Name + " &lt;" + Cc.m_Address + "&gt;");
    }
    if (!CcList.IsEmpty())
    {
        CcList = "<b>Cc:</b> " + CcList + "<br>";
    }

    wxString BCcList;
    for (const auto &BCc : m_Message.m_BCc)
    {
        BCcList =
            BCcList.IsEmpty() ?
            (BCc.m_Name + " &lt;" + BCc.m_Address + "&gt;") :
            (BCcList + "; " + BCc.m_Name + " &lt;" + BCc.m_Address + "&gt;");
    }
    if (!BCcList.IsEmpty())
    {
        BCcList = "<b>BCc:</b> " + BCcList + "<br>";
    }

    wxString Envelope =
        m_EmailType == EmailType::Forward ?
        "<br><br><br>---- Forwarded Message ----<br>" :
        "<br><br><br>---- Original Message ----<br>";
    Envelope +=
        "<b>From:</b> " + m_Message.m_From.m_Name + " &lt;" + m_Message.m_From.m_Address + "&gt;<br>"
        "<b>Date:</b> " + m_Message.GetDateTimeStr() + "<br>" +
        ToList +
        CcList + 
        BCcList +
        "<b>Subject:</b> " + m_Message.m_Subject + "<br><br>";
    const wxString HTML = Envelope + "<blockquote>" + m_Message.m_Body + "</blockquote>";
    m_Editor->SetPage(Greeting + HTML, "");
}


void EmailEditorFrame::SetFocusToNeededControl()
{
    if (m_ToField->IsEmpty())
    {
        m_ToField->SetFocus();
    }
    else
    {
        m_Editor->SetFocus();
    }
}


void EmailEditorFrame::OnFontChoosen(wxCommandEvent& event)
{
    const int Idx = m_FontChoice->GetSelection();
    if (Idx == wxNOT_FOUND || Idx == 0)
    {
        return;
    }
    const wxString FontName = "\"" + m_FontChoice->GetString(Idx) + "\"";
    m_Editor->RunScript("document.execCommand(\"fontName\", false, " + FontName + ");");
}


void EmailEditorFrame::OnFontSizeChoosen(wxCommandEvent& event)
{
    const int Idx = m_FontSizeChoice->GetSelection();
    if (Idx == wxNOT_FOUND || Idx == 0)
    {
        return;
    }
    const wxString Size = "\"" + std::to_string(Idx) + "\"";
    m_Editor->RunScript("document.execCommand(\"fontSize\", false, " + Size + ");");
}


void EmailEditorFrame::OnBoldButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"bold\");");
}


void EmailEditorFrame::OnItalicButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"italic\");");
}


void EmailEditorFrame::OnUnderlineButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"underline\");");
}


void EmailEditorFrame::OnTextColorButtonClicked(wxCommandEvent& event)
{
    wxColourDialog dlg;
    if (dlg.ShowModal() != wxID_OK)
    {
        return;
    }
    const wxString ColorStr = "'" + dlg.GetColourData().GetColour().GetAsString(wxC2S_HTML_SYNTAX) + "'";
    m_Editor->RunScript("document.execCommand(\"foreColor\", false, " + ColorStr + ");");
}


void EmailEditorFrame::OnBckgColorButtonClicked(wxCommandEvent& event)
{
    wxColourDialog dlg;
    if (dlg.ShowModal() != wxID_OK)
    {
        return;
    }
    const wxString ColorStr = "'" + dlg.GetColourData().GetColour().GetAsString(wxC2S_HTML_SYNTAX) + "'";
    m_Editor->RunScript("document.execCommand(\"hiliteColor\", false, " + ColorStr + ");");
}


void EmailEditorFrame::OnAlignLeftButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"justifyLeft\");");
}


void EmailEditorFrame::OnAlignCenterButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"justifyCenter\");");
}


void EmailEditorFrame::OnAlignRightButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"justifyRight\");");
}


void EmailEditorFrame::OnAlignJustifyButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"justifyFull\");");
}


void EmailEditorFrame::OnClearFormatButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"removeFormat\");");
}


void EmailEditorFrame::OnAddImageButtonClicked( wxCommandEvent& event )
{
    wxFileDialog OpenFileDlg(
        this, "Insert image", "", "", "Image files|*.jpg;*.png;*.bmp;*.gif", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (OpenFileDlg.ShowModal() != wxID_OK)
    {
        return;
    }
    std::ifstream File(OpenFileDlg.GetPath().ToStdString(), std::ios::binary | std::ios::ate);
    size_t FSize;
    if (!File.is_open() || (FSize = File.tellg()) == 0)
    {
        wxMessageBox("Cannot open file.", "Error", wxICON_ERROR);
        return;
    }
    File.seekg(0);
    std::vector<std::byte> Data(FSize, std::byte(0));
    File.read(reinterpret_cast<char*>(Data.data()), Data.size());
    const wxFileName FileName(OpenFileDlg.GetPath());
    const wxString ImageStr =
        "<img src=\"data:image/" + FileName.GetExt() + ";base64," + wxBase64Encode(Data.data(), Data.size()) + "\"/>";
    bool Inserted = false;
    if (wxTheClipboard->Open())
    {
        Inserted = wxTheClipboard->SetData(new wxHTMLDataObject(ImageStr));
        if (Inserted)
        {
            m_Editor->Paste();
        }
        wxTheClipboard->Close();
    }
    if (!Inserted)
    {
        wxMessageBox("Cannot insert image.", "Error", wxICON_ERROR);
    }
}


void EmailEditorFrame::OnInsertLinkButtonClicked(wxCommandEvent& event)
{
    if (m_Editor->GetSelectedText().IsEmpty())
    {
        return;
    }
    wxTextEntryDialog Dlg(this, "Link text to insert:");
    if (Dlg.ShowModal() != wxID_OK || Dlg.GetValue().IsEmpty())
    {
        return;
    }
    const wxString Link = "\"" + Dlg.GetValue() + "\"";
    m_Editor->RunScript("document.execCommand(\"createLink\", false, " + Link + ");");
}


void EmailEditorFrame::OnDiscardButtonClicked(wxCommandEvent& event)
{
    if (wxMessageBox(
        "Are you sure you want to discard this draft?", "Discard draft?", wxYES_NO, this) == wxYES)
    {
        Close(true);
    }
}


void EmailEditorFrame::ExtractEmbeddedImagesDataFromPage(std::vector<HTMLInlineObject> &Objects)
{
    Objects.clear();
    const wxString JS = " \
        function ExtractEmbeddedImagesData() { \
            var Imgs = document.getElementsByTagName('img'); \
            var txt = ''; \
            for (i = 0; i < Imgs.length; i++) { \
	            var str = Imgs[i].getAttribute('src'); \
                if (str.search('data:') == -1) { \
                    continue; \
                } \
	            txt = txt.length == 0 ? str : txt + '{NEWLINE}' + str; \
            } \
            return txt; \
        } \
        ExtractEmbeddedImagesData();";
    wxString Res;
    if (m_Editor->RunScript(JS, &Res))
    {
        Res.Replace("{NEWLINE}", "\n");
        const wxArrayString Data = wxSplit(Res, '\n');
        for (int i = 0; i < Data.GetCount(); i++)
        {
            const wxArrayString Parts = wxStringTokenize(Data[i], ":;,");
            HTMLInlineObject Obj;
            if (Parts.GetCount() > 1)
            {
                Obj.ContentType = Parts[1];
                Obj.ContentType.Trim(false).Trim();
            }
            if (Parts.GetCount() > 2)
            {
                Obj.Encoding = Parts[2];
                Obj.Encoding.Trim(false).Trim();
            }
            if (Parts.GetCount() > 3)
            {
                Obj.Data = Parts[3];
                Obj.Data.Trim(false).Trim();
            }
            if (Obj.IsValid())
            {
                Objects.push_back(Obj);
            }
        }
    }
}


void EmailEditorFrame::SetEmbeddedImagesIDs(const std::vector<wxString> &ObjectIDs)
{
    if (ObjectIDs.empty())
    {
        return;
    }
    wxString IDs;
    for (const auto &S : ObjectIDs)
    {
        IDs = IDs.IsEmpty() ? "'"+S+"'" : IDs + ", '"+S+"'";
    }
    IDs = "var IDs = [" + IDs + "];";
    const wxString JS = " \
        function SetEmbeddedImagesIDs() { " + IDs + " \
            var j = 0; \
            var Imgs = document.getElementsByTagName('img'); \
            for (i = 0; i < Imgs.length; i++) { \
	            var str = Imgs[i].getAttribute('src'); \
                if (str.search('data:') == -1) { \
                    continue; \
                } \
                Imgs[i].setAttribute('src', IDs[j++]); \
            } \
        } \
        SetEmbeddedImagesIDs();";
    m_Editor->RunScript(JS);
}


void EmailEditorFrame::AddHeaders(vmime::messageBuilder &mb)
{
    const charset ChS(charsets::UTF_8);
    mb.setSubject(vmime::text(m_Subject->GetValue().ToUTF8().data(), ChS));
    Message::EmailAddress From(m_FromField->GetValue());
    mb.setExpeditor(vmime::mailbox(vmime::text(From.m_Name.ToUTF8().data(), ChS), From.m_Address.ToStdString()));

    const wxArrayString Tos = wxSplit(m_ToField->GetValue(), ';');
    for (size_t i = 0; i < Tos.GetCount(); i++)
    {
        Message::EmailAddress To(Tos.Item(i));
        mb.getRecipients().appendAddress(
            vmime::make_shared<vmime::mailbox>(vmime::text(To.m_Name.ToUTF8().data(), ChS), To.m_Address.ToStdString()));
    }
    const wxArrayString Ccs = wxSplit(m_CCField->GetValue(), ';');
    for (size_t i = 0; i < Ccs.GetCount(); i++)
    {
        Message::EmailAddress To(Ccs.Item(i));
        mb.getCopyRecipients().appendAddress(
            vmime::make_shared<vmime::mailbox>(vmime::text(To.m_Name.ToUTF8().data(), ChS), To.m_Address.ToStdString()));
    }
    const wxArrayString BCcs = wxSplit(m_BCCField->GetValue(), ';');
    for (size_t i = 0; i < BCcs.GetCount(); i++)
    {
        Message::EmailAddress To(BCcs.Item(i));
        mb.getBlindCopyRecipients().appendAddress(
            vmime::make_shared<vmime::mailbox>(vmime::text(To.m_Name.ToUTF8().data(), ChS), To.m_Address.ToStdString()));
    }
}


void EmailEditorFrame::AddBody(vmime::messageBuilder &mb)
{
    mb.constructTextPart(vmime::mediaType(vmime::mediaTypes::TEXT, vmime::mediaTypes::TEXT_HTML));
    vmime::shared_ptr<vmime::htmlTextPart> HTMLPart =
        vmime::dynamicCast<vmime::htmlTextPart>(mb.getTextPart());
    HTMLPart->setCharset(charset(charsets::UTF_8));
    std::vector<HTMLInlineObject> Objects;
    ExtractEmbeddedImagesDataFromPage(Objects);
    std::vector<wxString> ObjectIDs;
    for (const auto &Obj : Objects)
    {
        vmime::shared_ptr<vmime::stringContentHandler> ContentHdlr(
            vmime::make_shared<vmime::stringContentHandler>
            (Obj.Data.ToStdString(), vmime::encoding(Obj.Encoding.ToStdString())));
        vmime::shared_ptr<const vmime::htmlTextPart::embeddedObject> EmbObject =
            HTMLPart->addObject(
                ContentHdlr,
                vmime::encoding(Obj.Encoding.ToStdString()),
                vmime::mediaType(Obj.ContentType.ToStdString()));
        ObjectIDs.push_back(EmbObject->getReferenceId());
    }
    SetEmbeddedImagesIDs(ObjectIDs);
    HTMLPart->setText(
        vmime::make_shared<vmime::stringContentHandler>(m_Editor->GetPageSource().ToUTF8().data()));
    HTMLPart->setPlainText(
        vmime::make_shared<vmime::stringContentHandler>(m_Editor->GetPageText().ToUTF8().data()));
}


void EmailEditorFrame::AddAttachments(vmime::messageBuilder &mb)
{
    for (int i = 0; i < m_AttachmentList->GetCount(); i++)
    {
        vmime::shared_ptr<vmime::fileAttachment> Attach =
            vmime::make_shared<vmime::fileAttachment>(m_AttachmentList->GetString(i).ToStdString(), vmime::mediaType());
        const wxFileName FileName(m_AttachmentList->GetString(i));
        Attach->getFileInfo().setFilename(FileName.GetName().ToStdString() + "." + FileName.GetExt().ToStdString());
        mb.appendAttachment(Attach);
    }
}


void EmailEditorFrame::OnSendButtonClicked( wxCommandEvent& event )
{
    wxString ErrorMsg;
    try
    {
        EmailService::CheckError(!m_FromField->IsEmpty() && !m_ToField->IsEmpty(), "'From' field and/or 'To' field is empty.");
        EmailService::CheckError(!m_Editor->GetPageText().IsEmpty(), "Messaage's body is empty.");
        vmime::messageBuilder mb;
        AddHeaders(mb);
        AddBody(mb);
        AddAttachments(mb);
        vmime::shared_ptr<vmime::message> VMimeMessage = mb.construct();
        std::thread SendingThread(
            &EmailService::SendVMimeMessage, TheApp->GetEmailService(), m_Username, VMimeMessage);
        SendingThread.detach();
        Close(true);
    }
    catch (const vmime::exception &e)
    {
        ErrorMsg = e.what();
    }
    catch (const std::exception &e)
    {
        ErrorMsg = e.what();
    }
    if (!ErrorMsg.IsEmpty())
    {
        wxMessageBox("Cannot send the message:\r\n" + ErrorMsg, "Error", wxICON_ERROR);
        return;
    }
}


void EmailEditorFrame::OnKeyPressed(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_ESCAPE)
    {
        if (wxMessageBox(
            "Are you sure you want to discard this draft?", "Discard draft?", wxYES_NO, this) == wxYES)
        {
            Close(true);
        }
        return;
    }
    event.Skip(true);
}


void EmailEditorFrame::OnToFieldChanged(wxCommandEvent& event)
{
    if (m_EmailType == EmailType::Forward)
    {
        SetTitle("Forwarding To: " + m_ToField->GetValue());
    }
}


void EmailEditorFrame::OnOrderedListButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"insertOrderedList\");");
}


void EmailEditorFrame::OnUnOrderedListButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"insertUnorderedList\");");
}


void EmailEditorFrame::OnAddAttachmentButtonClicked(wxCommandEvent& event)
{
    wxFileDialog OpenFileDlg(
        this, "Add Attachments", "", "", "Any file|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);
    if (OpenFileDlg.ShowModal() != wxID_OK)
    {
        return;
    }
    wxArrayString Filenames;
    OpenFileDlg.GetPaths(Filenames);
    for (size_t i = 0; i < Filenames.GetCount(); i++)
    {
        if (m_AttachmentList->FindString(Filenames.Item(i)) == wxNOT_FOUND)
        {
            m_AttachmentList->Append(Filenames.Item(i));
        }
    }
    m_AttachmentList->Show(true);
    m_TopPanelSizer->Layout();
    m_DeleteAttachmentButton->Show(true);
    m_AttachButtonsSizer->Layout();
    m_AttachmentList->SetToolTip("");
}


void EmailEditorFrame::OnDeleteAttachmentButtonClicked(wxCommandEvent& event)
{
    const int Idx = m_AttachmentList->GetSelection();
    if (Idx == wxNOT_FOUND)
    {
        return;
    }
    m_AttachmentList->Delete(Idx);
    m_AttachmentList->SetToolTip("");
}


void EmailEditorFrame::OnAttachmentListBoxSelected(wxCommandEvent& event)
{
    const int Idx = m_AttachmentList->GetSelection();
    if (Idx == wxNOT_FOUND)
    {
        return;
    }
    m_AttachmentList->SetToolTip(m_AttachmentList->GetString(Idx));
}


void EmailEditorFrame::OnStrikethroughButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"strikeThrough\");");
}


void EmailEditorFrame::OnSubscriptButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"subscript\");");
}


void EmailEditorFrame::OnSuperscriptButtonClicked(wxCommandEvent& event)
{
    m_Editor->RunScript("document.execCommand(\"superscript\");");
}