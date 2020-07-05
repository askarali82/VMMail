#include "EmailClientApp.h"
#include "MainFrame.h"
#include <vmime/vmime.hpp>
#include <utility>

#ifdef WIN32
#include <vmime/platforms/windows/windowsHandler.hpp>
#include <wx/msw/registry.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#else
#include <vmime/platforms/posix/posixHandler.hpp>
#endif


EmailClient *TheApp;
IMPLEMENT_APP(EmailClient);


bool EmailClient::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }

#ifdef WIN32
    vmime::platform::setHandler<vmime::platforms::windows::windowsHandler>();
    const wxFileName ExecPath(wxStandardPaths::Get().GetExecutablePath());
    wxRegKey key(wxRegKey::HKCU, "Software\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION");
    key.SetValue(ExecPath.GetName() + "." + ExecPath.GetExt(), 11001);
#else
    vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
#endif

    SetAppName("VMMail");
    m_LogStream.open(wxTheApp->GetAppName().ToStdString() + ".log", std::ios::app | std::ios::out);
    TheApp = dynamic_cast<EmailClient*>(wxTheApp);
    m_MainFrame = new MainFrame();
    m_MainFrame->Show(true);
    m_MainFrame->StartLoadingTimer();

    return true;
}