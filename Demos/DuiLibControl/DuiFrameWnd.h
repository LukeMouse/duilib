#pragma once

#include "UtilDataStruct.h"

class CDuiFrameWnd :
    public DuiLib::WindowImplBase
{
public:
    CDuiFrameWnd();
    ~CDuiFrameWnd();

public:
    virtual LPCTSTR    GetWindowClassName() const { return _T("DUIMainFrame"); }
    virtual DuiLib::CDuiString GetSkinFile() { return _T("MainWnd.xml"); }
    virtual DuiLib::CDuiString GetSkinFolder() { return _T(""); }
    virtual void InitWindow();
    virtual void Notify(DuiLib::TNotifyUI& msg);

    void setShoeImageBase64(std::string strFootImage);

    void AddItem(int Line);
    void SetShoeDeviceType(int shoesDeviceType);
    SIZE GetInitSize();
    /// ��������¼��ǰҪ�ɼ����㼣λ�á��ɼ����or�ҽš�
    void ChooseFootToSnap(const DuiLib::TNotifyUI &msg, const DuiLib::CDuiString& strName);

    /// �ش��ɼ�����ͼ��
    void SetTmpShoeImage(const std::string& imageData);

    std::map<int, TransData> GetSnapData();

    std::string m_tmpShoeImage;
    void GetControlPos();
    DuiLib::CLabelUI * m_pLabel;
    DuiLib::CVerticalLayoutUI * m_pShowPos;

    DuiLib::CButtonUI * m_pAddNew;
    DuiLib::CButtonUI * m_pCapture;
    DuiLib::CListUI * m_pListShoes;
    DuiLib::CContainerUI * m_pCantainer;
    /// ��ǰѡ�е��㼣�ؼ�
    DuiLib::CControlUI * m_pSelect;
    /// �ؼ�ԭʼ�߿���ɫ
    DWORD m_dwCorlorBackup;
    /// �㼣Ԥ���ؼ��пؼ�������tagֵ���������Ԥ������ֻ�и�������ѡ��
    UINT_PTR m_dwMaxTag;

    /// ��ǰ�ɼ����Ƿ�Ϊ���
    bool m_bLeftShoe;
    /// �ɼ��豸����
    int m_nShoesDeviceType;
    /// 0 ˫�ž�δ�ɼ���10 ��Ųɼ���ɣ� 11˫�Ųɼ����
    int m_curStatus;

    std::map<int, TransData> m_transDates;
};

