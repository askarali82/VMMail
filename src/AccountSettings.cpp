#include "AccountSettings.h"
#include <wx/msgdlg.h>
#include <wx/fileconf.h>
#include <wx/log.h>


void AccountSettings::OnOKButtonClick(wxCommandEvent& event)
{
    if (m_IMAPServerText->GetValue().Length() == 0 ||
        m_IMAPPortText->GetValue().Length() == 0 ||
        m_SMTPServerText->GetValue().Length() == 0 ||
        m_SMTPPortText->GetValue().Length() == 0 ||
        m_UserNameText->GetValue().Length() == 0 ||
        m_PasswordText->GetValue().Length() == 0)
    {
        wxMessageBox(wxT("Please fill in the required fields."));
        return;
    }
    if (m_UserNameText->GetValue().Find("@") == wxNOT_FOUND)
    {
        wxMessageBox(wxT("Please provide valid email address for 'User Name'."));
        return;
    }
    EndModal(wxID_OK);
}


bool AccountSettings::HasData() const
{
    return
        m_IMAPServerText->GetValue().Length() > 0 &&
        m_IMAPPortText->GetValue().Length() > 0 &&
        m_SMTPServerText->GetValue().Length() > 0 &&
        m_SMTPPortText->GetValue().Length() > 0 &&
        m_UserNameText->GetValue().Length() > 0;
}


bool AccountSettings::Save(const wxString &UserName) const
{
    wxFileConfig File(wxEmptyString, wxEmptyString, m_FileName, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
    if (UserName == wxEmptyString && File.HasGroup(m_UserNameText->GetValue()))
    {
        return false;
    }
    File.SetPath(UserName == wxEmptyString ? m_UserNameText->GetValue() : UserName);

    bool OK = File.Write("IMAPServer", m_IMAPServerText->GetValue());
    OK = OK && File.Write("IMAPServerRequiresSSL", m_IMAPRequiresSSL->GetValue());
    OK = OK && File.Write("IMAPServerPort", m_IMAPPortText->GetValue());

    OK = OK && File.Write("SMTPServer", m_SMTPServerText->GetValue());
    OK = OK && File.Write("SMTPServerRequiresSSL", m_SMTPRequiresSSL->GetValue());
    OK = OK && File.Write("SMTPServerRequiresTLS", m_SMTPRequiresTLS->GetValue());
    OK = OK && File.Write("SMTPServerRequiresAuth", m_SMTPRequiresAuth->GetValue());
    OK = OK && File.Write("SMTPServerPortL", m_SMTPPortText->GetValue());

    OK = OK && File.Write("FullName", m_FullNameText->GetValue());
    OK = OK && File.Write("UserName", m_UserNameText->GetValue());

    return OK;
}


bool AccountSettings::Load(const wxString &UserName)
{
    wxFileConfig File(wxEmptyString, wxEmptyString, m_FileName, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);

    wxString FirstGroup;
    long FirstGroupIdx;

    if (UserName != wxEmptyString)
    {
        if (!File.HasGroup(UserName))
        {
            return false;
        }
        File.SetPath(UserName);
    }
    else if (File.GetFirstGroup(FirstGroup, FirstGroupIdx))
    {
        File.SetPath(FirstGroup);
    }

    m_IMAPServerText->SetValue(File.Read("IMAPServer", ""));
    m_IMAPRequiresSSL->SetValue(File.ReadBool("IMAPServerRequiresSSL", true));
    m_IMAPPortText->SetValue(File.Read("IMAPServerPort", ""));

    m_SMTPServerText->SetValue(File.Read("SMTPServer", ""));
    m_SMTPRequiresSSL->SetValue(File.ReadBool("SMTPServerRequiresSSL", true));
    m_SMTPRequiresTLS->SetValue(File.ReadBool("SMTPServerRequiresTLS", true));
    m_SMTPRequiresAuth->SetValue(File.ReadBool("SMTPServerRequiresAuth", true));
    m_SMTPPortText->SetValue(File.Read("SMTPServerPortL", ""));

    m_FullNameText->SetValue(File.Read("FullName", ""));
    m_UserNameText->SetValue(File.Read("UserName", ""));

    return true;
}


std::vector<wxString> AccountSettings::GetUserNames() const
{
    wxFileConfig File(wxEmptyString, wxEmptyString, m_FileName, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
    std::vector<wxString> Result;
    wxString GroupName;
    long GroupIndex;
    bool OK = File.GetFirstGroup(GroupName, GroupIndex);
    while (OK)
    {
        Result.push_back(GroupName);
        OK = File.GetNextGroup(GroupName, GroupIndex);
    }
    return Result;
}