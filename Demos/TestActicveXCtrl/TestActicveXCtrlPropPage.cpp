// TestActicveXCtrlPropPage.cpp : Implementation of the CTestActicveXCtrlPropPage property page class.

#include "stdafx.h"
#include "TestActicveXCtrl.h"
#include "TestActicveXCtrlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CTestActicveXCtrlPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CTestActicveXCtrlPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CTestActicveXCtrlPropPage, "TESTACTICVEXCT.TestActicveXCtPropPage.1",
	0x593d8511, 0x8080, 0x4995, 0xb7, 0xe2, 0x8c, 0x89, 0x3c, 0x67, 0x74, 0xac)



// CTestActicveXCtrlPropPage::CTestActicveXCtrlPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CTestActicveXCtrlPropPage

BOOL CTestActicveXCtrlPropPage::CTestActicveXCtrlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_TESTACTICVEXCTRL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CTestActicveXCtrlPropPage::CTestActicveXCtrlPropPage - Constructor

CTestActicveXCtrlPropPage::CTestActicveXCtrlPropPage() :
	COlePropertyPage(IDD, IDS_TESTACTICVEXCTRL_PPG_CAPTION)
{
}



// CTestActicveXCtrlPropPage::DoDataExchange - Moves data between page and properties

void CTestActicveXCtrlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CTestActicveXCtrlPropPage message handlers
