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

    /// �ش��ɼ�����ͼ��
    void SetTmpShoeImage(const std::string& imageData);

    HANDLE InitUsbCamera();

    std::string m_tmpShoeImage;
    DuiLib::CLabelUI * m_pLabel;

    DuiLib::CButtonUI * m_pBtnClose;
    CLukeWndUI * m_pVideRender;

    /// ��ǰ�ɼ����Ƿ�Ϊ���
    bool m_bLeftShoe;
    /// �ɼ��豸����
    int m_nShoesDeviceType;
    /// 0 ˫�ž�δ�ɼ���10 ��Ųɼ���ɣ� 11˫�Ųɼ����
    int m_curStatus;
    CLukeImageRender m_imgVideoWnd;

    
};

