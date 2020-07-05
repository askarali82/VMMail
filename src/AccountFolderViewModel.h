#pragma once

#include <wx/wx.h>
#include <wx/dataview.h>
#include <vector>
#include "EmailService.h"

class AccountFolderViewModel : public wxDataViewModel
{
public:
    AccountFolderViewModel(std::vector<std::shared_ptr<Folder>>& Folders) :
        wxDataViewModel(), m_Folders(Folders)
    {
    }

    ~AccountFolderViewModel()
    {
    }

    unsigned int GetColumnCount() const override
    {
        return 1;
    }

    wxString GetColumnType(unsigned int column) const override
    {
        return "string";
    }

    void GetValue(wxVariant& val, const wxDataViewItem& item, unsigned int column) const override
    {
        if (item.IsOk())
        {
            Folder *folder = reinterpret_cast<Folder*>(item.GetID());
            val = folder->m_Name;
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
        Folder* folder = reinterpret_cast<Folder*>(item.GetID());
        if (folder->m_Parent == nullptr)
        {
            return wxDataViewItem(0);
        }
        else
        {
            return wxDataViewItem((void*)folder->m_Parent);
        }
    }

    bool IsContainer(const wxDataViewItem& item) const override
    {
        if (!item.IsOk())
        {
            return true;
        }
        Folder* folder = reinterpret_cast<Folder*>(item.GetID());
        return !folder->m_Childs.empty();
    }

    unsigned GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const override
    {
        if (!item.IsOk())
        {
            for (const auto &F : m_Folders)
            {
                children.Add(wxDataViewItem((void*)F.get()));
            }
            return children.Count();
        }
        Folder* folder = reinterpret_cast<Folder*>(item.GetID());
        for (const auto &F : folder->m_Childs)
        {
            children.Add(wxDataViewItem((void*)F.get()));
        }
        return children.Count();
    }

    wxDataViewItem GetDefaultFolderItem(const wxString &Username) const
    {
        std::vector<std::shared_ptr<Folder>> *Childs = nullptr;
        for (const auto &F : m_Folders)
        {
            if (F->m_Name != Username)
            {
                continue;
            }
            Childs = &F->m_Childs;
            for (const auto &Ch : F->m_Childs)
            {
                if (Ch->m_Default)
                {
                    return wxDataViewItem((void*)Ch.get());
                }
            }
        }
        return (Childs == nullptr || Childs->empty()) ? wxDataViewItem(0) : wxDataViewItem((void*)Childs->front().get());
    }

    wxDataViewItem FindItemByUserFolder(const wxString &Username, const wxString &Foldername) const
    {
        for (const auto &F : m_Folders)
        {
            if (F->m_Name != Username)
            {
                continue;
            }
            for (const auto &Ch : F->m_Childs)
            {
                if (Ch->m_Name == Foldername)
                {
                    return wxDataViewItem((void*)Ch.get());
                }
            }
        }
        return wxDataViewItem(0);
    }

    bool AccountExists(const wxString &Username) const
    {
        for (const auto &F : m_Folders)
        {
            if (F->m_Name == Username)
            {
                return true;
            }
        }
        return false;
    }

private:
    std::vector<std::shared_ptr<Folder>> &m_Folders;
};