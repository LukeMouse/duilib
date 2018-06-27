// TestActicveXCtrlCtrl.cpp : Implementation of the CTestActicveXCtrlCtrl ActiveX Control class.

#include "stdafx.h"
#include "TestActicveXCtrl.h"
#include "TestActicveXCtrlCtrl.h"
#include "TestActicveXCtrlPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CTestActicveXCtrlCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CTestActicveXCtrlCtrl, COleControl)
	ON_MESSAGE(OCM_COMMAND, &CTestActicveXCtrlCtrl::OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CTestActicveXCtrlCtrl, COleControl)
	DISP_FUNCTION_ID(CTestActicveXCtrlCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CTestActicveXCtrlCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CTestActicveXCtrlCtrl, 1)
	PROPPAGEID(CTestActicveXCtrlPropPage::guid)
END_PROPPAGEIDS(CTestActicveXCtrlCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CTestActicveXCtrlCtrl, "TESTACTICVEXCTRL.TestActicveXCtrlCtrl.1",
	0x648573ad, 0x951f, 0x415f, 0x8f, 0xbd, 0xf4, 0x1f, 0x73, 0, 0xcb, 0x99)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CTestActicveXCtrlCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DTestActicveXCtrl =
		{ 0xB38B780A, 0x1291, 0x400C, { 0x88, 0xB2, 0x0, 0x48, 0xAB, 0x62, 0x9F, 0x77 } };
const IID BASED_CODE IID_DTestActicveXCtrlEvents =
		{ 0xA4633AC6, 0x1B7D, 0x4B63, { 0xB8, 0xED, 0x1C, 0x6F, 0xB2, 0x64, 0xBB, 0x74 } };



// Control type information

static const DWORD BASED_CODE _dwTestActicveXCtrlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CTestActicveXCtrlCtrl, IDS_TESTACTICVEXCTRL, _dwTestActicveXCtrlOleMisc)



// CTestActicveXCtrlCtrl::CTestActicveXCtrlCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CTestActicveXCtrlCtrl

BOOL CTestActicveXCtrlCtrl::CTestActicveXCtrlCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_TESTACTICVEXCTRL,
			IDB_TESTACTICVEXCTRL,
			afxRegApartmentThreading,
			_dwTestActicveXCtrlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CTestActicveXCtrlCtrl::CTestActicveXCtrlCtrl - Constructor

CTestActicveXCtrlCtrl::CTestActicveXCtrlCtrl(): m_dlgDuilib(NULL)
{
	InitializeIIDs(&IID_DTestActicveXCtrl, &IID_DTestActicveXCtrlEvents);
	// TODO: Initialize your control's instance data here.
}



// CTestActicveXCtrlCtrl::~CTestActicveXCtrlCtrl - Destructor

CTestActicveXCtrlCtrl::~CTestActicveXCtrlCtrl()
{
	// TODO: Cleanup your control's instance data here.
    if (NULL != m_dlgDuilib)
    {
        delete m_dlgDuilib;
        m_dlgDuilib = NULL;
    }
}



// CTestActicveXCtrlCtrl::OnDraw - Drawing function

void CTestActicveXCtrlCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	DoSuperclassPaint(pdc, rcBounds);
}



// CTestActicveXCtrlCtrl::DoPropExchange - Persistence support

void CTestActicveXCtrlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CTestActicveXCtrlCtrl::OnResetState - Reset control to default state

void CTestActicveXCtrlCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CTestActicveXCtrlCtrl::AboutBox - Display an "About" box to the user

void CTestActicveXCtrlCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_TESTACTICVEXCTRL);
	dlgAbout.DoModal();
}



// CTestActicveXCtrlCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CTestActicveXCtrlCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("STATIC");
	return COleControl::PreCreateWindow(cs);
}



// CTestActicveXCtrlCtrl::IsSubclassedControl - This is a subclassed control

BOOL CTestActicveXCtrlCtrl::IsSubclassedControl()
{
	return TRUE;
}



// CTestActicveXCtrlCtrl::OnOcmCommand - Handle command messages

LRESULT CTestActicveXCtrlCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}



// CTestActicveXCtrlCtrl message handlers

int CTestActicveXCtrlCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (COleControl::OnCreate(lpCreateStruct) == -1)
        return -1;

    //DuiLib::CPaintManagerUI::SetInstance(AfxGetInstanceHandle());//加载XML的时候，需要使用该句柄去定位EXE的路径，才能加载XML的路径
    //DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + _T("skin"));//定位图片等资源的位置
    //DuiLib::CPaintManagerUI::SetResourcePath(_T("F:\\UpSync\\RuralMouseSVN\\LMXLib\\DuiLib\\Unicode\\Win32\\bin\\skin\\"));//定位图片等资源的位置
	if (NULL == m_dlgDuilib)
	{
		m_dlgDuilib = new CDuiFrameWnd();
		m_dlgDuilib->Create(this->m_hWnd, NULL, UI_WNDSTYLE_CHILD & (~(WS_BORDER | WS_CAPTION)), 0, 0, 0, 0);
		m_dlgDuilib->AddItem(1);
	}
	SIZE wndSize = m_dlgDuilib->GetInitSize();
    m_dlgDuilib->GetControlPos();
	MoveWindow(0, 0, wndSize.cx, wndSize.cy);

    return 0;
}

void CTestActicveXCtrlCtrl::OnSize(UINT nType, int cx, int cy)
{
    COleControl::OnSize(nType, cx, cy);
    
    if (NULL != m_dlgDuilib)
    {
        m_dlgDuilib->ResizeClient(cx, cy);
        m_dlgDuilib->ShowWindow(TRUE); //显示窗体
    }
}
