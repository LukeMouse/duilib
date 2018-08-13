#pragma once

#import "Capture.ocx"
class CDuiFrameWnd;

class CCaputureWnd:public DuiLib::CWindowWnd, public DuiLib::INotifyUI, public DuiLib::IMessageFilterUI
{
public:
    CCaputureWnd(short foorDirect, CDuiFrameWnd* pParent);
    virtual ~CCaputureWnd();;
    LPCTSTR GetWindowClassName() const { return _T("UILoginFrame"); };
    UINT GetClassStyle() const { return UI_CLASSSTYLE_DIALOG; };
    void OnFinalMessage(HWND /*hWnd*/);;

    void Init();

    void Notify(DuiLib::TNotifyUI& msg);

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        return 0;
    }

    LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        return 0;
    }

    LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    BOOL IsInStaticControl(DuiLib::CControlUI *pControl);

    BOOL IsDragRect(POINT pt);



public:
    DuiLib::CPaintManagerUI m_pm;
    DuiLib::CButtonUI* m_pBtnClose;
    DuiLib::CButtonUI* m_pBtnSnap;
    DuiLib::CActiveXUI * m_pActiveX;
    CaptureLib::_DCapture *m_hrCaptureCtrl;
    short m_foorDirect;
    CDuiFrameWnd* m_pParent;
    bool m_bStartMove;
    POINT m_StartPt;
};
