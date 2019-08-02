// RichListDemo.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include <exdisp.h>
#include <comdef.h>
#include "USBCameraWnd.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("\\skin"));
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("\\skin\\LukeUsbCamera"));
	//CPaintManagerUI::SetResourceZip(_T("LukeUsbCamera.zip"));

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) return 0;

	CUSBCameraWnd* pFrame = new CUSBCameraWnd();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T("LukeUsbCamera"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 500, 400);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return 0;
}
