#include "stdafx.h"
#include "DuiFrameWnd.h"

CDuiFrameWnd::CDuiFrameWnd()
    : m_pSelect(NULL), m_dwMaxTag(0)
{
}


CDuiFrameWnd::~CDuiFrameWnd()
{
}

void CDuiFrameWnd::InitWindow()
{
    m_pLabel = static_cast<DuiLib::CLabelUI*>(m_PaintManager.FindControl(_T("picShow")));
    m_pShowPos = static_cast<DuiLib::CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("showPos")));
    m_pListShoes = static_cast<DuiLib::CListUI*>(m_PaintManager.FindControl(_T("shoeList")));
    m_pAddNew = static_cast<DuiLib::CButtonUI*>(m_PaintManager.FindControl(_T("addBtn")));
    m_pAddNew->SetEnabled(false);
    m_pCapture = static_cast<DuiLib::CButtonUI*>(m_PaintManager.FindControl(_T("btnCapture")));
    //m_pCapture->SetVisible(false);
	m_pCantainer = static_cast<DuiLib::CContainerUI*>(m_PaintManager.FindControl(_T("imageFresh")));

 }

void CDuiFrameWnd::setShoeImageBase64(const CStringA& strFootImage)
{
    unsigned char* data = 0;
    int dataLength = 0;


    CxImage imgHelper(data, dataLength,0);
    int imgWidth = imgHelper.GetWidth();
    int imgHeight = imgHelper.GetHeight();
    RECT windowRect = m_pSelect->GetParent()->GetPos();
    RECT destPos = GetImagePos(windowRect, imgWidth, imgHeight, TRUE, TRUE);

    DuiLib::CDuiString sCtrlKey = _T("LukeImagePos");
    HBITMAP hBmp = ChangeCxImageToBMP(GetDC(GetHWND()), &imgHelper);
    m_PaintManager.RemoveImage(sCtrlKey);
    m_PaintManager.AddImage(sCtrlKey, hBmp, imgWidth, imgHeight, false);
    m_pSelect->SetPos(destPos);
    m_pSelect->SetBkImage(sCtrlKey);
}

void CDuiFrameWnd::Notify(DuiLib::TNotifyUI& msg)
{
    static int item = 1;
    static bool isFirst = true;
    if (msg.sType == _T("click"))
    {
        DuiLib::CDuiString name = msg.pSender->GetName();

        if (name == _T("leftFoot") || name == _T("rightFoot"))
        {
            ChooseFootToSnap(msg, name);
        }

        if (name == _T("addBtn"))
        {
            AddItem(++item);
            m_pAddNew->SetEnabled(false);
        }

        if (name == _T("btnCapture"))
        {
            if (NULL == m_pSelect)
            {
                return;
            }

            CoInitialize(NULL);
            CCaputureWnd * pCapWnd = NULL;
            pCapWnd = new CCaputureWnd(0, this);
            pCapWnd->Create(this->m_hWnd, _T("eeee"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE); ///< 如果参数1是NULL, 为桌面, 子窗口就不是模态对话框  
            pCapWnd->CenterWindow();
            pCapWnd->ShowWindow();
            pCapWnd->ShowModal();  ///< 弹出的是模态窗口
            
            setShoeImageBase64(m_tmpShoeImage.c_str());

            //m_pCapture->SetVisible(false);
            //m_pOcxShoe->SetVisible();
            m_pCantainer->Invalidate();

            CxImage imgHelper;
            imgHelper.Load(_T("E:\\Backup\\李莫轩.JPG"));
            int imgWidth = imgHelper.GetWidth();
            int imgHeight = imgHelper.GetHeight();
            RECT windowRect = m_pSelect->GetParent()->GetPos();
            RECT destPos = GetImagePos(windowRect, imgWidth, imgHeight, TRUE, TRUE);

            DuiLib::CDuiString sCtrlKey = _T("LukeImagePos");
            HBITMAP hBmp = ChangeCxImageToBMP(GetDC(GetHWND()), &imgHelper);
            m_PaintManager.RemoveImage(sCtrlKey);
            m_PaintManager.AddImage(sCtrlKey, hBmp, imgWidth, imgHeight, false);
            m_pSelect->SetPos(destPos);
            m_pSelect->SetBkImage(sCtrlKey);


        }

        if (name == _T("btnDel"))
        {
            UINT_PTR tag = msg.pSender->GetParent()->GetParent()->GetTag();
            if (tag > 0)
            {
                int itemCount = m_pListShoes->GetCount();
                for (int index = 0; index < itemCount; ++index)
                {
                    if (m_pListShoes->GetItemAt(index)->GetTag() == tag)
                    {
                        m_pListShoes->RemoveAt(index);
                        if (m_dwMaxTag == tag) // 当前的tag被删除了
                        {
                            m_pSelect = NULL;
                            m_pAddNew->SetEnabled(true);
                            m_pCapture->SetVisible(false);
                        }
                        break;
                    }
                }
            }
        }
    }
}

void CDuiFrameWnd::ChooseFootToSnap(const DuiLib::TNotifyUI &msg, const DuiLib::CDuiString& strName)
{
    DuiLib::CControlUI * pControl = msg.pSender->GetParent();
    while (NULL != pControl)
    {
        DuiLib::CDuiString strPareb = pControl->GetName();
        UINT_PTR tag = pControl->GetTag();
        if (tag == m_dwMaxTag && strName.Find(_T("Foot")) > 0)
        {
            DuiLib::CVerticalLayoutUI * pItem = static_cast<DuiLib::CVerticalLayoutUI *>(pControl);
            DuiLib::CPaintManagerUI* pManager = pItem->GetManager();
            DuiLib::CControlUI * pSelect = pManager->FindControl(strName);
            if (NULL == m_pSelect)
            {
                m_dwCorlorBackup = 0xFFE9E7E1;// pSelect->GetBorderColor();
            }
            else
            {
                m_pSelect->SetBorderColor(m_dwCorlorBackup);
            }
            pSelect->SetBorderColor(0xFFFF0000);
            m_pSelect = pSelect;
            m_bLeftShoe = (strName.Find(_T("left")) > 0);

            m_pCapture->SetVisible();
        }
        pControl = pControl->GetParent();
    }
}

void CDuiFrameWnd::SetTmpShoeImage(const std::string& imageData)
{
    m_tmpShoeImage = imageData;
}

void CDuiFrameWnd::AddItem(int Line)
{
    if (NULL != m_pSelect)
    {
        m_pSelect->SetBorderColor(m_dwCorlorBackup);
        m_pSelect = NULL;
    }
    DuiLib::CDialogBuilder builder;
    DuiLib::CVerticalLayoutUI * pItem = static_cast<DuiLib::CVerticalLayoutUI *>(builder.Create(
        _T("./preView.xml"), 0, NULL, &m_PaintManager, NULL));
    pItem->SetTag(Line);
    m_dwMaxTag = Line;   

    m_pListShoes->AddAt(pItem, 0);
}

void CDuiFrameWnd::SetShoeDeviceType(int shoesDeviceType)
{
    m_nShoesDeviceType = shoesDeviceType;
}

SIZE CDuiFrameWnd::GetInitSize()
{
    return m_PaintManager.GetInitSize();
}

void CDuiFrameWnd::GetControlPos()
{

}

