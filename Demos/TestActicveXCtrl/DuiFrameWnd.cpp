#include "stdafx.h"
#include "DuiFrameWnd.h"
#include "TestActicveXCtrl.h"

CDuiFrameWnd::CDuiFrameWnd()
    : m_pSelect(NULL), m_dwMaxTag(0)
    , m_curStatus(0), m_pShowPos(NULL)
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
    unsigned char* data = 0;
    int dataLength = 0;

    //if (strFootImage.size() > 0)
    //{
    //    //base64����
    //    if (HS_BASE64_DecodeEx((char*)strFootImage.c_str(), strFootImage.size(), &data, &dataLength, 0) < 0)
    //    {
    //        AfxMessageBox(theApp.GetStringFromResource(IDS_PARSE64FAILED));
    //        return;
    //    }
    //}
    
    CxImage imgHelper(data, dataLength,0);
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
            pCapWnd->Create(this->m_hWnd, NULL, UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
            //pCapWnd->Create(this->m_hWnd, _T("eeee"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE); ///< �������1��NULL, Ϊ����, �Ӵ��ھͲ���ģ̬�Ի��� 
            
            //pCapWnd->CenterWindow(); ԭ�еľ��в����ã�ʹ�������5�д�����
            RECT rcParent = { 0 };
            ::GetWindowRect(m_hWnd, &rcParent);
            RECT rcCap = { 0 };
            ::GetWindowRect(pCapWnd->GetHWND(), &rcCap);
            MoveWindow(pCapWnd->GetHWND(), rcParent.left + 414, rcParent.top + 2, rcCap.right - rcCap.left, rcCap.bottom - rcCap.top, true);
            
            pCapWnd->ShowWindow();
            pCapWnd->ShowModal();  ///< ��������ģ̬����
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
			else
			{
				m_pCapture->SetVisible(true);
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
                        if (m_dwMaxTag == tag) // ��ǰ��tag��ɾ����
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

void CDuiFrameWnd::ResetButtonPosition()
{
    if (NULL == m_pShowPos)
    {
        return;
    }
    RECT rcCantainer = m_pShowPos->GetPos();
    int width = m_pShowPos->GetWidth();
    int height = m_pShowPos->GetHeight();
    if (width > 0 && height > 0 && m_pCapture->IsVisible())
    {
        RECT rcButton;
        rcButton.left = rcCantainer.left + static_cast<int>(0.36 * width);
        rcButton.right = rcButton.left + static_cast<int>(0.28 * width);
        rcButton.top = rcCantainer.top + static_cast<int>(0.75 * height);
        rcButton.bottom = rcButton.top + static_cast<int>(0.1 * height);
        m_pCapture->SetPos(rcButton);
        InvalidateRect(m_hWnd, &rcCantainer, TRUE);
        UpdateWindow(m_hWnd);
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
                m_dwCorlorBackup = pSelect->GetBorderColor();
            }
            else
            {
                m_pSelect->SetBorderColor(m_dwCorlorBackup);
            }
            pSelect->SetBorderColor(0xFFFF0000);
            m_pSelect = pSelect;
            m_bLeftShoe = (strName == _T("leftFoot"));
            m_pCapture->SetVisible();
            ResetButtonPosition();
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
