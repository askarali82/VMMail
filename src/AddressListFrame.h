#pragma once

#include "formbuilder/BaseGUIClasses.h"
#include "EmailService.h"
#include "wx/webview.h"
#include <functional>


class AddressListFrame : public BaseAddressListFrame
{
public:
    std::function<void(const wxString &)> OnItemSelectSignal;
    wxTextCtrl *m_TargetTextCtrl;
	AddressListFrame(wxWindow* parent);
    void FindAndSelectAddress(const wxString &AddrStr);

protected:
    void OnItemSelected(wxCommandEvent& event) override;
    void OnListBoxDblClicked(wxCommandEvent& event) override;
    void OnListBoxKeyDown(wxKeyEvent& event) override;

private:

    //DECLARE_EVENT_TABLE()
};