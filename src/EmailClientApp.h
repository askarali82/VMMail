#pragma once

#include <wx/wx.h>
#include "MainFrame.h"
#include "EmailService.h"
#include <fstream>
#include <memory>
#include <wx/log.h>
#include <wx/thread.h>

class EmailClient : public wxApp
{
public:
    virtual bool OnInit();
    EmailService *GetEmailService()
    {
        return &m_EmailService;
    }
    MainFrame *GetMainFrame()
    {
        return m_MainFrame;
    }
    void Log(const wxString &Msg)
    {
        wxCriticalSectionLocker Locker(m_CritSect);
        if (m_LogStream.is_open())
        {
            m_LogStream << Msg.ToStdString() << std::endl;
            m_LogStream.flush();
        }
    }

private:
    wxCriticalSection m_CritSect;
    MainFrame* m_MainFrame;
    EmailService m_EmailService;
    std::ofstream m_LogStream;
};

extern EmailClient *TheApp;
