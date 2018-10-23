// FaceDetect.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "FaceDetect.h"

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

#include <UIlib.h>
using namespace DuiLib;
#include "DuiFrameWnd.h"

#include <ximage.h>




int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("\\FaceDetect"));

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    CoInitialize(NULL);
    AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);

    Gdiplus::Status status = GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    IDshowUSBDevice * pUSBDevice = GetDshowUSBInterface();
    CDuiFrameWnd *pduiFrame = new CDuiFrameWnd(pUSBDevice);
    pduiFrame->Create(NULL, _T("FaceDetect"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pduiFrame->CenterWindow();
    HANDLE hThread = pduiFrame->InitUsbCamera();
    pduiFrame->ShowModal();

    ReleaseDshowUSBInterface(pUSBDevice);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    delete pduiFrame;
    pduiFrame = NULL;
    Gdiplus::GdiplusShutdown(gdiplusToken);
    return 0;
}
