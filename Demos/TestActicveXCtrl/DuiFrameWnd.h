#pragma once


class CDuiFrameWnd :
    public DuiLib::WindowImplBase
{
public:
    CDuiFrameWnd();
    ~CDuiFrameWnd();

public:
    virtual LPCTSTR    GetWindowClassName() const { return _T("DUIMainFrame"); }
    virtual DuiLib::CDuiString GetSkinFile() { return _T("shoe.xml"); }
    virtual DuiLib::CDuiString GetSkinFolder() { return _T(""); }
    virtual void InitWindow();
    virtual void Notify(DuiLib::TNotifyUI& msg);

    void setShoeImageBase64(const CStringA& strFootImage);

    void AddItem(int Line);
    void SetShoeDeviceType(int shoesDeviceType);
    SIZE GetInitSize();
    /// 高亮并记录当前要采集的足迹位置【采集左脚or右脚】
    void ChooseFootToSnap(const DuiLib::TNotifyUI &msg, const DuiLib::CDuiString& strName);

    /// 回传采集到的图像
    void SetTmpShoeImage(const std::string& imageData);

    std::string m_tmpShoeImage;
    void GetControlPos();
    DuiLib::CLabelUI * m_pLabel;
    DuiLib::CVerticalLayoutUI * m_pShowPos;

    DuiLib::CButtonUI * m_pAddNew;
    DuiLib::CButtonUI * m_pCapture;
    DuiLib::CListUI * m_pListShoes;
    DuiLib::CContainerUI * m_pCantainer;
    /// 当前选中的足迹控件
    DuiLib::CControlUI * m_pSelect;
    /// 控件原始边框颜色
    DWORD m_dwCorlorBackup;
    /// 足迹预览控件中控件组的最大tag值【最上面的预览】，只有改组允许选中
    UINT_PTR m_dwMaxTag;

    /// 当前采集的是否为左脚
    bool m_bLeftShoe;
    /// 采集设备类型
    int m_nShoesDeviceType;
};

