#include "stdafx.h"
#include "DuiFrameWnd.h"
#include "CaputureWnd.h"
#include "Base64Tool.h"
#include "UtilDataStruct.h"


CDuiFrameWnd::CDuiFrameWnd()
    : m_pSelect(NULL), m_dwMaxTag(0)
    , m_curStatus(0)
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
    m_pCapture->SetVisible(false);
	m_pCantainer = static_cast<DuiLib::CContainerUI*>(m_PaintManager.FindControl(_T("imageFresh")));

 }

void CDuiFrameWnd::setShoeImageBase64(std::string strFootImage)
{
    
    std::string strImageRaw = CBase64Tool::Decode(strFootImage);
    
    CxImage imgHelper((uint8_t *)strImageRaw.c_str(), strImageRaw.size(), 0);
    int imgWidth = imgHelper.GetWidth();
    int imgHeight = imgHelper.GetHeight();
    RECT windowRect = m_pSelect->GetParent()->GetPos();
    RECT destPos = GetImagePos(windowRect, imgWidth, imgHeight, TRUE, TRUE);

    static int seeds = 1;
    TCHAR imgKey[20] = {};
    _stprintf_s(imgKey, 20, _T("ImageIndex%d"), seeds++);
    HBITMAP hBmp = ChangeCxImageToBMP(GetDC(GetHWND()), &imgHelper);
    m_PaintManager.AddImage(imgKey, hBmp, imgWidth, imgHeight, false);
    m_pSelect->SetPos(destPos);
    m_pSelect->SetBkImage(imgKey);

    windowRect = m_pShowPos->GetPos();
    destPos = GetImagePos(windowRect, imgWidth, imgHeight, TRUE, TRUE);
    m_pLabel->SetPos(destPos);
    m_pLabel->SetBkImage(imgKey);
}

void CDuiFrameWnd::Notify(DuiLib::TNotifyUI& msg)
{
    if (msg.sType == _T("dbclick"))
    {
        // 此处会传递很多次双击消息，所以只获取父类控件的消息
        if (!msg.pSender->GetParent())
        {
            Close(IDOK);
        }
    }
    static int item = 1;
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

            m_pCapture->SetVisible(false);
            CCaputureWnd * pCapWnd = NULL;
            pCapWnd = new CCaputureWnd(m_bLeftShoe ? 0 : 1, this);
            pCapWnd->Create(this->m_hWnd, _T("eeee"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE); ///< 如果参数1是NULL, 为桌面, 子窗口就不是模态对话框 
            
            //pCapWnd->CenterWindow(); 原有的居中不好用，使用下面的5行代码解决
            RECT rcParent = { 0 };
            ::GetWindowRect(m_hWnd, &rcParent);
            RECT rcCap = { 0 };
            ::GetWindowRect(pCapWnd->GetHWND(), &rcCap);
            MoveWindow(pCapWnd->GetHWND(), rcParent.left + 414, rcParent.top + 2, rcCap.right - rcCap.left, rcCap.bottom - rcCap.top, true);
            
            pCapWnd->ShowWindow();
            pCapWnd->ShowModal();  ///< 弹出的是模态窗口
            pCapWnd = NULL;
            if (m_tmpShoeImage.size() > 50)
            {
                setShoeImageBase64(m_tmpShoeImage);            
                if (m_bLeftShoe)
                {
                    if(m_curStatus < 9)            
                    {
                        m_curStatus += 10;
                    }
                    m_transDates[m_dwMaxTag].leftBase64 = m_tmpShoeImage;
                }
                else
                {
                    if (m_curStatus % 10 == 0)
                    {
                        m_curStatus += 1;
                    }
                    m_transDates[m_dwMaxTag].rightBase64 = m_tmpShoeImage;
                }
                m_tmpShoeImage.clear();
                if (11 == m_curStatus)
                {
                    m_pAddNew->SetEnabled();
                    m_curStatus = 0;
                }
            }
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
                m_transDates.erase(tag);
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
            m_bLeftShoe = (strName == _T("leftFoot"));

            m_pCapture->SetVisible();
        }
        pControl = pControl->GetParent();
    }
}

void CDuiFrameWnd::SetTmpShoeImage(const std::string& imageData)
{
    m_tmpShoeImage.clear();
    m_tmpShoeImage = imageData;
}

std::map<int, TransData> CDuiFrameWnd::GetSnapData()
{
    return m_transDates;
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
        _T("./capSnail.xml"), 0, NULL, &m_PaintManager, NULL));
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
