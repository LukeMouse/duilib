#pragma once

//#include "capture.tlh"
#import "F:\FingerPrint\一体化采集设备\足迹\恒锐\20180511\2.0版本驱动\ocx_new_20170505\Capture.ocx"
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

    DuiLib::CDuiString GetShoeImage();

public:
    DuiLib::CPaintManagerUI m_pm;
    DuiLib::CButtonUI* m_pButton;
    DuiLib::CActiveXUI * m_pActiveX;
    CaptureLib::_DCapture *m_hrCaptureCtrl;
    bstr_t m_showImage;
    short m_foorDirect;
    CDuiFrameWnd* m_pParent;

};
