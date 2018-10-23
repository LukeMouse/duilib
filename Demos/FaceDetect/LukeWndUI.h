#pragma once

class CLukeWndUI :
    public DuiLib::CControlUI
{
public:
    CLukeWndUI();

    virtual void SetVisible(bool bVisible = true);

    virtual void SetInternVisible(bool bVisible = true);

    virtual void SetPos(RECT rc, bool bNeedInvalidate = true);;

    BOOL Attach(HWND hWndNew);

    HWND Detach();

    HWND GetHWND();

    LPCTSTR GetClass() const;

    LPVOID GetInterface(LPCTSTR pstrName);

protected:
    HWND m_hWnd;

};

