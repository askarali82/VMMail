#include "AddressListFrame.h"
#include "MainFrame.h"
#include "EmailClientApp.h"
#include <wx/arrstr.h>

AddressListFrame::AddressListFrame(wxWindow* parent):
    BaseAddressListFrame(parent), m_TargetTextCtrl(nullptr)
{
    const std::vector<Message::EmailAddress> &Addresses =
        TheApp->GetMainFrame()->GetEmailAddresses();
    if (Addresses.empty())
    {
        return;
    }
    wxArrayString StrArray;
    for (const auto &Addr : Addresses)
    {
        StrArray.Add(Addr.m_Text.IsEmpty() ? Addr.m_Address : Addr.m_Text);
    }
    m_AddressList->InsertItems(StrArray, 0);
}


void AddressListFrame::OnItemSelected(wxCommandEvent& event)
{
    if (OnItemSelectSignal)
    {
        //OnItemSelectSignal(event.GetString());
    }
}


void AddressListFrame::OnListBoxDblClicked(wxCommandEvent& event)
{
    OnItemSelectSignal(event.GetString());
    Show(false);
}


void AddressListFrame::OnListBoxKeyDown(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_RETURN)
    {
        const int I = m_AddressList->GetSelection();
        if (I != wxNOT_FOUND)
        {
            OnItemSelectSignal(m_AddressList->GetString(I));
            Show(false);
        }
    }
    else if (event.GetKeyCode() == WXK_ESCAPE)
    {
        Show(false);
    }
    else if (event.GetKeyCode() == WXK_TAB && m_TargetTextCtrl != nullptr)
    {
        m_TargetTextCtrl->SetFocus();
    }
    event.Skip();
}


void AddressListFrame::FindAndSelectAddress(const wxString &AddrStr)
{
    for (int i = 0; i < m_AddressList->GetCount(); i++)
    {
        const wxString Address = m_AddressList->GetString(i).Lower().Trim(false);
        if (!AddrStr.IsEmpty() && Address.Find(AddrStr.Lower()) == 0)
        {
            m_AddressList->Select(i);
            return;
        }
    }
    m_AddressList->SetSelection(wxNOT_FOUND);
}