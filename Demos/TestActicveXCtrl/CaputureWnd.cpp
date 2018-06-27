#include "StdAfx.h"
#include "CaputureWnd.h"
#include "DuiFrameWnd.h"


CCaputureWnd::CCaputureWnd(short foorDirect, CDuiFrameWnd* pParent) : m_hrCaptureCtrl(NULL), m_foorDirect(foorDirect), m_pParent(pParent)
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
    m_pButton = static_cast<DuiLib::CButtonUI*>(m_pm.FindControl(_T("btnOK")));
    m_pActiveX = static_cast<DuiLib::CActiveXUI *>(m_pm.FindControl(_T("ocxShoe")));
    if (m_pActiveX)
    {
        m_pActiveX->SetDelayCreate(false);
        CaptureLib::_DCapture * pCap = NULL;
        HRESULT hr = m_pActiveX->GetControl(__uuidof(CaptureLib::_DCapture), (LPVOID*)&m_hrCaptureCtrl);
        //m_hrCaptureCtrl->InitEquipment();
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
            HRESULT hr = m_hrCaptureCtrl->InitEquipment();
            hr = m_hrCaptureCtrl->SetFootDirect(m_foorDirect);
            VARIANT_BOOL bSuc = m_hrCaptureCtrl->PickFootImage();
            std::string tmpImg = m_hrCaptureCtrl->GetFootImage();
            m_pParent->SetTmpShoeImage(tmpImg);
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
    styleValue &= ~WS_CAPTION;
    ::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    m_pm.Init(m_hWnd);
    m_pm.AddPreMessageFilter(this);
    DuiLib::CDialogBuilder builder;
    //CDialogBuilderCallbackEx cb;
    DuiLib::CControlUI* pRoot = builder.Create(_T("showPrinter.xml"), (UINT)0, NULL, &m_pm);
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

    RECT rcCaption = m_pm.GetCaptionRect();
    if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
        && pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
        DuiLib::CControlUI* pControl = static_cast<DuiLib::CControlUI*>(m_pm.FindControl(pt));
        if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0)
            return HTCAPTION;
    }

    return HTCLIENT;
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
    return false;
}

DuiLib::CDuiString CCaputureWnd::GetShoeImage()
{
    return m_showImage.GetBSTR();
}
