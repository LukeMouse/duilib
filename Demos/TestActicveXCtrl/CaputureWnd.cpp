#include "StdAfx.h"
#include "CaputureWnd.h"
#include "DuiFrameWnd.h"
#include <algorithm>

CCaputureWnd::CCaputureWnd(short foorDirect, CDuiFrameWnd* pParent)
: m_hrCaptureCtrl(NULL), m_foorDirect(foorDirect), m_pParent(pParent), m_bStartMove(false)
{

}

CCaputureWnd::~CCaputureWnd()
{
    DestroyWindow(GetParent(this->GetHWND()));
}

void CCaputureWnd::OnFinalMessage(HWND /*hWnd*/)
{
    m_pm.RemovePreMessageFilter(this);
    delete this;
}

void CCaputureWnd::Init()
{
    m_pBtnClose = static_cast<DuiLib::CButtonUI*>(m_pm.FindControl(_T("btnClose")));
    m_pBtnSnap = static_cast<DuiLib::CButtonUI*>(m_pm.FindControl(_T("btnSnap")));
    m_pActiveX = static_cast<DuiLib::CActiveXUI *>(m_pm.FindControl(_T("ocxShoe")));
    if (m_pActiveX)
    {
        m_pActiveX->SetDelayCreate(false);
        HRESULT hr = m_pActiveX->GetControl(__uuidof(CaptureLib::_DCapture), (LPVOID*)&m_hrCaptureCtrl);
        if (SUCCEEDED(hr))
        {
            m_hrCaptureCtrl->InitEquipment();
        }

        m_pActiveX->SetVisible(true);
    }
}

void CCaputureWnd::Notify(DuiLib::TNotifyUI& msg)
{
    DuiLib::CDuiString name = msg.pSender->GetName();
    if (msg.sType == _T("click"))
    {
        if (name.CompareNoCase(_T("btnSnap")) == 0)
        {
            m_hrCaptureCtrl->SetFootDirect(m_foorDirect);
            m_hrCaptureCtrl->PickFootImage();
            std::string tmpImg = m_hrCaptureCtrl->GetFootImage();
            m_pParent->SetTmpShoeImage(tmpImg);
            Close(IDOK);
        }
        if (name.CompareNoCase(_T("btnClose")) == 0)
        {
            Close(IDOK);
        }
    }
}

LRESULT CCaputureWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
    ::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    m_pm.Init(m_hWnd);
    m_pm.AddPreMessageFilter(this);
    DuiLib::CDialogBuilder builder;
    DuiLib::CControlUI* pRoot = builder.Create(_T("CaptureWnd.xml"), (UINT)0, NULL, &m_pm);
    ASSERT(pRoot && "Failed to parse XML");
    m_pm.AttachDialog(pRoot);
    m_pm.AddNotifier(this);

    Init();
    return 0;
}

LRESULT CCaputureWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (::IsIconic(*this)) bHandled = FALSE;
    return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CCaputureWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
    ::ScreenToClient(*this, &pt);

    RECT rcClient;
    ::GetClientRect(*this, &rcClient);
    if( !::IsZoomed(*this) ) {
        RECT rcSizeBox = m_pm.GetSizeBox();    // GetSizeBox用来获取xml中Window标签的sizebox属性，该属性指示你的鼠标移动到窗口边框多少个像素会变成指示符（这个指示符表示可以改变窗口大小的指示符）
        if( pt.y < rcClient.top + rcSizeBox.top ) {
            if( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
            if( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
            return HTTOP;
        }
        else if( pt.y > rcClient.bottom - rcSizeBox.bottom ) {
            if( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
            if( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
            return HTBOTTOM;
        }
        if( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
        if( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
    }

    // bottom为-1时，则整个窗口的高度都可以拖动
    RECT rcCaption = m_pm.GetCaptionRect();
    if (-1 == rcCaption.bottom)
    {
        rcCaption.bottom = rcClient.bottom;
    }

    if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right
        && pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) 
    {
        DuiLib::CControlUI* pControl = m_pm.FindControl(pt);
        if (IsInStaticControl(pControl))
        {
            return HTCAPTION;
        }
    }

    return HTCLIENT;
}

// 包含头文件#include <algorithm>
BOOL CCaputureWnd::IsInStaticControl(DuiLib::CControlUI *pControl)
{
    BOOL bRet = FALSE;
    if (!pControl)
    {
        return bRet;
    }

    DuiLib::CDuiString strClassName;
    std::vector<DuiLib::CDuiString> vctStaticName;

    vctStaticName.push_back(_T("control"));
    vctStaticName.push_back(_T("text"));
    vctStaticName.push_back(_T("label"));
    vctStaticName.push_back(_T("container"));
    vctStaticName.push_back(_T("horizontallayout"));
    vctStaticName.push_back(_T("verticallayout"));
    vctStaticName.push_back(_T("tablayout"));
    vctStaticName.push_back(_T("childlayout"));
    vctStaticName.push_back(_T("dialoglayout"));

    std::vector<DuiLib::CDuiString>::iterator it = std::find(vctStaticName.begin(), vctStaticName.end(), strClassName);
    if (vctStaticName.end() != it)
    {
        DuiLib::CControlUI* pParent = pControl->GetParent();
        while (pParent)
        {
            strClassName = pParent->GetClass();
            strClassName.MakeLower();
            it = std::find(vctStaticName.begin(), vctStaticName.end(), strClassName);
            if (vctStaticName.end() == it)
            {
                return bRet;
            }

            pParent = pParent->GetParent();
        }

        bRet = TRUE;
    }

    return bRet;
}

BOOL CCaputureWnd::IsDragRect(POINT pt)
{
    RECT rcWnd;
    ::GetWindowRect(m_hWnd, &rcWnd);
    int captionHeight = 60; //caption heigth.

    if (pt.y < captionHeight)
    {
        return TRUE;
    }
    return FALSE;
}

LRESULT CCaputureWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    SIZE szRoundCorner = m_pm.GetRoundCorner();
    if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) {
        DuiLib::CDuiRect rcWnd;
        ::GetWindowRect(*this, &rcWnd);

        rcWnd.Offset(-rcWnd.left, -rcWnd.top);
        rcWnd.right++; rcWnd.bottom++;
        HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
        ::SetWindowRgn(*this, hRgn, TRUE);
        ::DeleteObject(hRgn);
    }

    bHandled = FALSE;
    return 0;
}

LRESULT CCaputureWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lRes = 0;
    BOOL bHandled = TRUE;
    switch (uMsg) {
    case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
    case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
    case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
    case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
    case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
    case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
    default:
        bHandled = FALSE;
    }
    if (bHandled) return lRes;
    if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
    return DuiLib::CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CCaputureWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
    if (uMsg == WM_KEYDOWN) {
        if (wParam == VK_RETURN) {
            DuiLib::CEditUI* pEdit = static_cast<DuiLib::CEditUI*>(m_pm.FindControl(_T("accountedit")));
            if (pEdit->GetText().IsEmpty()) pEdit->SetFocus();
            else {
                pEdit = static_cast<DuiLib::CEditUI*>(m_pm.FindControl(_T("pwdedit")));
                if (pEdit->GetText().IsEmpty()) pEdit->SetFocus();
                else Close();
            }
            return true;
        }
        else if (wParam == VK_ESCAPE) {
            PostQuitMessage(0);
            return true;
        }
    }

    if (uMsg == WM_MOUSEMOVE) {
        if (::GetAsyncKeyState(VK_LBUTTON) != 0 && m_bStartMove)
        {
            POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            if (!IsDragRect(pt)) return 0;
            int dx = pt.x - m_StartPt.x;
            int dy = pt.y - m_StartPt.y;
            RECT curRect;
            ::GetWindowRect(m_hWnd, &curRect);
            int cx = curRect.left + dx;
            int cy = curRect.top + dy;

            int  w = curRect.right - curRect.left;
            int  h = curRect.bottom - curRect.top;

            SetWindowPos(m_hWnd, NULL, cx, cy, w, h, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

        }
    }
    else if (uMsg == WM_LBUTTONDOWN)
    {
        POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        m_bStartMove = TRUE;
        m_StartPt = pt;
    }
    else if (uMsg == WM_LBUTTONUP)
    {
        m_bStartMove = FALSE;
    }

    return false;
}
