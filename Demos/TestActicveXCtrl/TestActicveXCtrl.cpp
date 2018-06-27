// TestActicveXCtrl.cpp : Implementation of CTestActicveXCtrlApp and DLL registration.

#include "stdafx.h"
#include "TestActicveXCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTestActicveXCtrlApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x2ABD00E4, 0xF012, 0x43F4, { 0x88, 0x68, 0x3B, 0x75, 0x6A, 0x37, 0x9D, 0xD0 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CTestActicveXCtrlApp::InitInstance - DLL initialization

BOOL CTestActicveXCtrlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

    HRESULT hRes = ::OleInitialize(NULL);
	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CTestActicveXCtrlApp::ExitInstance - DLL termination

int CTestActicveXCtrlApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
