#include "stdafx.h"
#include "DuiFrameWnd.h"
#include "LukeWndUI.h"

IDshowUSBDevice * g_pUSBDevice = NULL;
BOOL g_isFaceDetecting = TRUE;
HANDLE g_hThreadMutex; // 主线程与人脸检测线程互斥

CDuiFrameWnd::CDuiFrameWnd(IDshowUSBDevice *& pUSBDevice)
    : m_curStatus(0), m_pVideRender(0)
{
    g_pUSBDevice = pUSBDevice;
}


CDuiFrameWnd::~CDuiFrameWnd()
{
    delete m_pVideRender;
    m_pVideRender = NULL;
}

void CDuiFrameWnd::InitWindow()
{
    //m_pVideRender = static_cast<CLukeWndUI*>(m_PaintManager.FindControl(_T("videoRender")));
    m_pBtnClose = static_cast<DuiLib::CButtonUI*>(m_PaintManager.FindControl(_T("btnClose")));
    g_hThreadMutex = CreateMutex(NULL, FALSE, _T("FaceDetectMutex"));
 }


void CDuiFrameWnd::Notify(DuiLib::TNotifyUI& msg)
{
    static int item = 1;
    if (msg.sType == _T("click"))
    {
        DuiLib::CDuiString name = msg.pSender->GetName();

        if (name == _T("btnClose"))
        {
            g_isFaceDetecting = FALSE;
            WaitForSingleObject(g_hThreadMutex, INFINITE);
            CloseHandle(g_hThreadMutex);
            Close(IDOK);
        }
    }
}


DuiLib::CControlUI* CDuiFrameWnd::CreateControl(LPCTSTR pstrClass)
{
    if (_tcscmp(pstrClass, _T("LukeWnd")) == 0)
    {
        //CLukeImageRender * pVideoWnd = new CLukeImageRender;
        m_imgVideoWnd.Create(NULL, _T("test"), WS_CHILD | WS_VISIBLE ,
            CRect(0, 0, 0, 0), CWnd::FromHandle(m_PaintManager.GetPaintWindow()), 0);
        m_imgVideoWnd.ShowWindow(SW_SHOW);
        m_pVideRender = new CLukeWndUI();
        m_pVideRender->Attach(m_imgVideoWnd.GetSafeHwnd());
        return m_pVideRender;
    }

    return NULL;
}

void CDuiFrameWnd::SetTmpShoeImage(const std::string& imageData)
{
    m_tmpShoeImage.clear();
    m_tmpShoeImage = imageData;
}

unsigned WINAPI faceDetectThread(void* pParam)
{
    CDuiFrameWnd * pFeame = (CDuiFrameWnd *)pParam;
    int imageSize = g_pUSBDevice->GetCurrentDIBSize();
    BYTE * pImageBUffer = new BYTE[imageSize];
    BOOL bSuc = FALSE;
    while (true)
    {
        WaitForSingleObject(g_hThreadMutex, INFINITE);
        if (!g_isFaceDetecting)
        {
            break;
        }
        if (!SUCCEEDED(g_pUSBDevice->GetCurrentDIBImage(pImageBUffer)))
        {
            Sleep(10);
            continue;
        }
        pFeame->m_imgVideoWnd.RenderImage(pImageBUffer, imageSize);
        ReleaseMutex(g_hThreadMutex);
        Sleep(40);
    }
    delete[]pImageBUffer;
    pImageBUffer = 0;
    return 0;
}

HANDLE CDuiFrameWnd::InitUsbCamera()
{
    g_pUSBDevice->ConfigUSBDeviceRender(m_pVideRender->GetHWND());
    g_pUSBDevice->ConnectSpecifiedUSB(0);
    g_pUSBDevice->StartPreviewVideo();

    unsigned threadID;
    HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, faceDetectThread, this, 0, &threadID);

    return hThread;
}

void CDuiFrameWnd::SetShoeDeviceType(int shoesDeviceType)
{
    m_nShoesDeviceType = shoesDeviceType;
}

