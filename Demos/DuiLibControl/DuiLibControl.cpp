// DuiLibControl.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DuiLibControl.h"
#include <UIlib.h>
using namespace DuiLib;
#include "DuiFrameWnd.h"

#include <ximage.h>




int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("\\skin"));

    CDuiFrameWnd *pduiFrame = new CDuiFrameWnd();
    pduiFrame->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pduiFrame->InitWindow();
    pduiFrame->AddItem(1);
    pduiFrame->CenterWindow();
    pduiFrame->ShowModal();
    return 0;
}
