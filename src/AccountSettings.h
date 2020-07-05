#pragma once

#include "formbuilder/BaseGUIClasses.h"
#include <vector>

class AccountSettings : public BaseAccountConfigDialog
{
public:
    AccountSettings(const wxString &FileName, const wxString &DialogTitle = wxEmptyString):
        BaseAccountConfigDialog(nullptr), m_FileName(FileName)
    {
        if (DialogTitle != wxEmptyString)
        {
            SetTitle(DialogTitle);
        }
        m_OKButton->Bind(wxEVT_BUTTON, &AccountSettings::OnOKButtonClick, this);
    }

    bool Save(const wxString &UserName = wxEmptyString) const;
    bool Load(const wxString &UserName = wxEmptyString);
    bool HasData() const;
    std::vector<wxString> GetUserNames() const;

private:
    const wxString m_FileName;
    void OnOKButtonClick(wxCommandEvent& event);
};