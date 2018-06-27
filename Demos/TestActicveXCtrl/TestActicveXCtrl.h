#pragma once

// TestActicveXCtrl.h : main header file for TestActicveXCtrl.DLL

#if !defined( __AFXCTL_H__ )
#error "include 'afxctl.h' before including this file"
#endif

#include "resource.h"       // main symbols


// CTestActicveXCtrlApp : See TestActicveXCtrl.cpp for implementation.

class CTestActicveXCtrlApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

