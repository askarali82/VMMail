#pragma once

#include <wx/wx.h>
#include <wx/dataview.h>
#include <vector>
#include <memory>
#include "EmailService.h"

class MessageListViewModel : public wxDataViewModel
{
public:
    MessageListViewModel(std::vector<std::shared_ptr<Message>>& Messages) :
        wxDataViewModel(), m_Messages(Messages)
    {
    }

    ~MessageListViewModel()
    {
    }

    unsigned int GetColumnCount() const override
    {
        return 3;
    }

    wxString GetColumnType(unsigned int column) const override
    {
        return "string";
    }

    void GetValue(wxVariant& val, const wxDataViewItem& item, unsigned int column) const override
    {
        if (item.IsOk())
        {
            Message *Msg = reinterpret_cast<Message*>(item.GetID());
            switch (column)
            {
            case 0:
                val = !Msg->m_From.m_Name.IsEmpty() ? Msg->m_From.m_Name : Msg->m_From.m_Address;
                break;
            case 1:
                val = Msg->m_Subject;
                break;
            case 2:
                val = Msg->GetDateTimeStr();
                break;
            }
        }
    }

    bool SetValue(const wxVariant& val, const wxDataViewItem& item, unsigned int column) override
    {
        return true;
    }

    wxDataViewItem GetParent(const wxDataViewItem& item) const override
    {
        if (!item.IsOk())
        {
            return wxDataViewItem(0);
        }
        Message* Msg = reinterpret_cast<Message*>(item.GetID());
        if (Msg->m_Parent == nullptr)
        {
            return wxDataViewItem(0);
        }
        else
        {
            return wxDataViewItem((void*)Msg->m_Parent);
        }
    }

    bool IsContainer(const wxDataViewItem& item) const override
    {
        if (!item.IsOk())
        {
            return true;
        }
        Message* Msg = reinterpret_cast<Message*>(item.GetID());
        return !Msg->m_Childs.empty();
    }

    unsigned GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const override
    {
        if (!item.IsOk())
        {
            for (const auto &Msg : m_Messages)
            {
                children.Add(wxDataViewItem((void*)Msg.get()));
            }
            return children.Count();
        }
        Message* Msg = reinterpret_cast<Message*>(item.GetID());
        for (const auto & Ch : Msg->m_Childs)
        {
            children.Add(wxDataViewItem((void*)Ch.get()));
        }
        return children.Count();
    }

    bool GetAttr(const wxDataViewItem &item, unsigned int col, wxDataViewItemAttr &attr) const override
    {
        if (!item.IsOk())
        {
            return false;
        }
        Message* Msg = reinterpret_cast<Message*>(item.GetID());
        if (!Msg->m_Seen)
        {
            attr.SetBold(true);
            return true;
        }
        return false;
    }

    wxDataViewItem GetFirstItem() const
    {
        if (m_Messages.empty())
        {
            return wxDataViewItem(0);
        }
        for (const auto &M : m_Messages)
        {
            return wxDataViewItem((void*)M.get());
        }
        return wxDataViewItem(0);
    }

    wxDataViewItem FindItemByMessage(const Message &Msg) const
    {
        for (const auto &M : m_Messages)
        {
            if (*M == Msg)
            {
                return wxDataViewItem((void*)M.get());
            }
        }
        return wxDataViewItem(0);
    }

    std::shared_ptr<Message> FindMessageByItem(const wxDataViewItem &Item) const
    {
        std::shared_ptr<Message> Result;
        if (!Item.IsOk())
        {
            return Result;
        }
        Message* Msg = reinterpret_cast<Message*>(Item.GetID());
        for (auto &M : m_Messages)
        {
            for (auto &Ch : M->m_Childs)
            {
                if (*Msg == *Ch)
                {
                    return Ch;
                }
            }
            if (*Msg == *M)
            {
                return M;
            }
        }
        return Result;
    }

private:
    std::vector<std::shared_ptr<Message>> &m_Messages;
};