#include "StdAfx.h"
#include "DuiLib_Dialog.h"

DuiLib_Dialog::DuiLib_Dialog(void)
{
}

DuiLib_Dialog::~DuiLib_Dialog(void)
{
}

LPCTSTR DuiLib_Dialog::GetWindowClassName() const
{
	return (LPCTSTR)"test";
}

void	DuiLib_Dialog::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("click") ) 
	{  
		if( msg.pSender->GetName() == _T("closebtn") ) 
		{  
			ShowWindow(false);
		}  
	}  
}

LRESULT DuiLib_Dialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if( uMsg == WM_CREATE ) 
	{  
		CPaintManagerUI::SetInstance(AfxGetInstanceHandle());//加载XML的时候，需要使用该句柄去定位EXE的路径，才能加载XML的路径
		CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));//定位图片等资源的位置

		m_pm.Init(m_hWnd);  
		CDialogBuilder builder;  
		CControlUI *pRoot = builder.Create(_T("ui.xml"), (UINT)0, NULL, &m_pm); //加载的XML文件的名称
		ASSERT(pRoot && "Failed to parse XML");  
		m_pm.AttachDialog(pRoot);  
		m_pm.AddNotifier(this);  

		return 0;  
	}  
	else if( uMsg == WM_DESTROY ) 
	{  
		::PostQuitMessage(0);  
	}  
	LRESULT lRes = 0;  
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;  
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);

}