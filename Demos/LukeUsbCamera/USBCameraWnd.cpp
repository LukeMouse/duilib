#include "StdAfx.h"
#include "USBCameraWnd.h"



//////////////////////////////////////////////////////////////////////////
///

DUI_BEGIN_MESSAGE_MAP(CUSBCameraWnd, WindowImplBase)
DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,OnClick)
DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED,OnSelectChanged)
DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMCLICK,OnItemClick)
DUI_END_MESSAGE_MAP()

CUSBCameraWnd::CUSBCameraWnd(void)
{

}

CUSBCameraWnd::~CUSBCameraWnd(void)
{

}

void CUSBCameraWnd::OnFinalMessage( HWND hWnd)
{
    __super::OnFinalMessage(hWnd);
    delete this;
}

CDuiString CUSBCameraWnd::GetSkinFolder()
{
#ifdef _DEBUG
    return _T("skin\\LukeUsbCamera\\");
#else
    return _T("skin\\");
#endif

}

CDuiString CUSBCameraWnd::GetSkinFile()
{
    return _T("duilib.xml");
}

UILIB_RESOURCETYPE CUSBCameraWnd::GetResourceType() const
{
#ifdef _DEBUG
    return UILIB_FILE;
#else
    return UILIB_ZIP;
#endif
}

CDuiString CUSBCameraWnd::GetZIPFileName() const
{
    return _T("LukeUsbCamera.zip");
}

LPCTSTR CUSBCameraWnd::GetWindowClassName( void ) const
{
    return _T("USBCameraWnd");
}

void CUSBCameraWnd::OnClick( TNotifyUI &msg )
{
    if( msg.pSender == m_pCloseBtn ) 
    { 
        PostQuitMessage(0);
        return; 
    }else if( msg.pSender == m_pMinBtn ) 
    { 
        SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); 
        return; 
    }else if( msg.pSender == m_pMaxBtn ) 
    { 
        SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); 
        return; 
    }else if( msg.pSender == m_pRestoreBtn ) 
    {
        SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
        return;
    }
    else if( msg.pSender->GetName() == _T("quitbtn") ) 
    {
        PostQuitMessage(0);
    }
}

void CUSBCameraWnd::OnSelectChanged( TNotifyUI &msg )
{
    if(msg.pSender->GetName() == _T("down_list"))
    {
        static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_main")))->SelectItem(0);
    }
    else if(msg.pSender->GetName() == _T("down_his"))
    {
        static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_main")))->SelectItem(1);
    }
}

void CUSBCameraWnd::OnItemClick( TNotifyUI &msg )
{
    
}

void CUSBCameraWnd::Notify( TNotifyUI &msg )
{
    return WindowImplBase::Notify(msg);
}

LRESULT CUSBCameraWnd::OnMouseWheel( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    bHandled = FALSE;
    return 0;
}

LRESULT CUSBCameraWnd::OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    // 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
    if( wParam == SC_CLOSE ) {
        ::PostQuitMessage(0L);
        bHandled = TRUE;
        return 0;
    }
    BOOL bZoomed = ::IsZoomed(*this);
    LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
    if( ::IsZoomed(*this) != bZoomed ) {
        if( !bZoomed ) {
            CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
            if( pControl ) pControl->SetVisible(false);
            pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
            if( pControl ) pControl->SetVisible(true);
        }
        else {
            CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
            if( pControl ) pControl->SetVisible(true);
            pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
            if( pControl ) pControl->SetVisible(false);
        }
    }
    return lRes;
}

void CUSBCameraWnd::InitWindow()
{
    m_pCloseBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("closebtn")));
    m_pMaxBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("maxbtn")));
    m_pRestoreBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("restorebtn")));
    m_pMinBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("minbtn")));
}

LRESULT CUSBCameraWnd::OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
    CControlUI* pHover = m_PaintManager.FindControl(pt);
    if( pHover == NULL ) return 0;
    /*演示悬停在下载列表的图标上时，动态变换下载图标状态显示*/
    if(pHover->GetName() == _T("down_ico"))
    {
    }
    return 0;
}

LRESULT CUSBCameraWnd::OnChar( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    /*演示键盘消息的处理*/
    TCHAR press_char = (TCHAR)wParam;
    if(press_char == VK_BACK)
    {
        MessageBox(NULL, _T("按下了回退键"), _T("DUILIB DEMO"), MB_OK);
    }
    else
    {
        bHandled = FALSE;
    }
    return 0;
}
