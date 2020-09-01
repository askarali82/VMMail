#pragma once

#include "formbuilder/BaseGUIClasses.h"
#include "EmailService.h"
#include "wx/webview.h"
#include <wx/arrstr.h>
#include <vector>
#include "AddressListFrame.h"
#include <memory>

enum class EmailType {New, Reply, ReplyAll, Forward};

class EmailEditorFrame : public BaseEmailEditorFrame
{
public:
	EmailEditorFrame(
        const wxString &Username, const Message &AMessage, const EmailType AEmailType = EmailType::New);

protected:
    void OnFontChoosen( wxCommandEvent& event ) override;
    void OnFontSizeChoosen( wxCommandEvent& event ) override;
    void OnBoldButtonClicked( wxCommandEvent& event ) override;
    void OnItalicButtonClicked( wxCommandEvent& event ) override;
    void OnUnderlineButtonClicked( wxCommandEvent& event ) override;
    void OnTextColorButtonClicked( wxCommandEvent& event ) override;
    void OnBckgColorButtonClicked( wxCommandEvent& event ) override;
    void OnAlignLeftButtonClicked( wxCommandEvent& event ) override;
    void OnAlignCenterButtonClicked( wxCommandEvent& event ) override;
    void OnAlignRightButtonClicked( wxCommandEvent& event ) override;
    void OnAlignJustifyButtonClicked( wxCommandEvent& event ) override;
    void OnClearFormatButtonClicked( wxCommandEvent& event )override;
    void OnAddImageButtonClicked( wxCommandEvent& event ) override;
    void OnDiscardButtonClicked( wxCommandEvent& event ) override;
    void OnSendButtonClicked( wxCommandEvent& event ) override;
    void OnKeyPressed( wxKeyEvent& event );
    void OnOrderedListButtonClicked( wxCommandEvent& event ) override;
    void OnUnOrderedListButtonClicked( wxCommandEvent& event ) override;
    void OnInsertLinkButtonClicked( wxCommandEvent& event ) override;
    void OnAddAttachmentButtonClicked( wxCommandEvent& event ) override;
    void OnDeleteAttachmentButtonClicked( wxCommandEvent& event ) override;
    void OnAttachmentListBoxSelected( wxCommandEvent& event ) override;
    void OnStrikethroughButtonClicked( wxCommandEvent& event ) override;
    void OnSubscriptButtonClicked( wxCommandEvent& event ) override;
    void OnSuperscriptButtonClicked( wxCommandEvent& event ) override;
    void OnToFieldChanged( wxCommandEvent& event ) override;
    void OnToFieldKeyPressed( wxKeyEvent& event ) override;
    void OnToFieldEnter( wxCommandEvent& event ) override;
    void OnCcFieldChanged( wxCommandEvent& event ) override;
    void OnCcFieldKeyPressed( wxKeyEvent& event ) override;
    void OnCcFieldEnter( wxCommandEvent& event ) override;
    void OnBCcFieldChanged( wxCommandEvent& event ) override;
    void OnBCcFieldKeyPressed( wxKeyEvent& event ) override;
    void OnBCcFieldEnter( wxCommandEvent& event ) override;

private:
    struct HTMLInlineObject
    {
        wxString ContentType;
        wxString Encoding;
        wxString Data;
        bool IsValid() const
        {
            return !ContentType.IsEmpty() && Encoding.Lower() == "base64" && !Data.IsEmpty();
        }
    };
    
    const Message m_Message;
    const EmailType m_EmailType;
    const wxString m_Username;
    wxWebView *m_Editor;
    std::unique_ptr<AddressListFrame> m_AddressListFrame;
    wxString GetTypedString(long *_From = nullptr, long *_To = nullptr) const;

    void PopulateHeaderFields();
    void SetBodyToEditor();
    void SetFocusToNeededControl();
    void PopulateFontData();
    void ExtractEmbeddedImagesDataFromPage(std::vector<HTMLInlineObject> &Objects);
    void SetEmbeddedImagesIDs(const std::vector<wxString> &ObjectIDs);
    void Extract_FROM_and_TO_Fields(Message::EmailAddress &From, std::vector<Message::EmailAddress> &To);
    wxString ExtractFirstNameOfReceiver() const;
    void AddHeaders(vmime::messageBuilder &mb);
    void AddBody(vmime::messageBuilder &mb);
    void AddAttachments(vmime::messageBuilder &mb);
    void OnAddressSelected(const wxString &Address);
    void SplitBase64wxString(wxString &Str) const;
    
#ifdef __WXMSW__
    void SetBitmaps();
#endif

    DECLARE_EVENT_TABLE()
};