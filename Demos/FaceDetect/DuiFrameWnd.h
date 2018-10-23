#pragma once

class CLukeImageRender;
class CLukeWndUI;
class CDuiFrameWnd :
    public DuiLib::WindowImplBase
{
public:
    CDuiFrameWnd(IDshowUSBDevice *& pUSBDevice);
    ~CDuiFrameWnd();

public:
    virtual LPCTSTR    GetWindowClassName() const { return _T("DUIMainFrame"); }
    virtual DuiLib::CDuiString GetSkinFile() { return _T("MainWnd.xml"); }
    virtual DuiLib::CDuiString GetSkinFolder() { return _T(""); }
    virtual void InitWindow();
    virtual void Notify(DuiLib::TNotifyUI& msg);
    virtual DuiLib::CControlUI* CreateControl(LPCTSTR pstrClass);

    void SetShoeDeviceType(int shoesDeviceType);

    /// 回传采集到的图像
    void SetTmpShoeImage(const std::string& imageData);

    HANDLE InitUsbCamera();

    std::string m_tmpShoeImage;
    DuiLib::CLabelUI * m_pLabel;

    DuiLib::CButtonUI * m_pBtnClose;
    CLukeWndUI * m_pVideRender;

    /// 当前采集的是否为左脚
    bool m_bLeftShoe;
    /// 采集设备类型
    int m_nShoesDeviceType;
    /// 0 双脚均未采集，10 左脚采集完成， 11双脚采集完成
    int m_curStatus;
    CLukeImageRender m_imgVideoWnd;

    
};

