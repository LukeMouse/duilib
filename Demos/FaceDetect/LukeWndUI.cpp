#include "stdafx.h"
#include "LukeWndUI.h"


const TCHAR kLukeWndUIClassName[] = _T("LukeWndUI");
const TCHAR kLukeWndUIInterface[] = _T("LukeWnd");



CLukeWndUI::CLukeWndUI() : m_hWnd(NULL)
{

}

void CLukeWndUI::SetVisible(bool bVisible /*= true*/)
{
    __super::SetVisible(bVisible);
    ::ShowWindow(m_hWnd, bVisible);
}

void CLukeWndUI::SetInternVisible(bool bVisible /*= true*/)
{
    __super::SetInternVisible(bVisible);
    ::ShowWindow(m_hWnd, bVisible);
}

void CLukeWndUI::SetPos(RECT rc, bool bNeedInvalidate)
{
    CControlUI::SetPos(rc, bNeedInvalidate);


    ::MoveWindow(m_hWnd, m_rcItem.left, m_rcItem.top,
        m_rcItem.right - m_rcItem.left, m_rcItem.bottom - m_rcItem.top, TRUE);

    //__super::SetPos(rc);
    //::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left,
    //    rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
}

BOOL CLukeWndUI::Attach(HWND hWndNew)
{
    if (!::IsWindow(hWndNew))
    {
        return FALSE;
    }
    m_hWnd = hWndNew;
    return TRUE;
}

HWND CLukeWndUI::Detach()
{
    HWND hWnd = m_hWnd;
    m_hWnd = NULL;
    return hWnd;
}

HWND CLukeWndUI::GetHWND()
{
    return m_hWnd;
}

LPCTSTR CLukeWndUI::GetClass() const
{
    return kLukeWndUIClassName;
}

LPVOID CLukeWndUI::GetInterface(LPCTSTR pstrName)
{
    if (_tcscmp(pstrName, kLukeWndUIInterface) == 0)
        return static_cast<CLukeWndUI*>(this);
    return CControlUI::GetInterface(pstrName);
}
