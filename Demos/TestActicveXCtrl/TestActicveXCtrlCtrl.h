#pragma once

//#include "DuiLib_Dialog.h"

// TestActicveXCtrlCtrl.h : Declaration of the CTestActicveXCtrlCtrl ActiveX Control class.


// CTestActicveXCtrlCtrl : See TestActicveXCtrlCtrl.cpp for implementation.

class CTestActicveXCtrlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CTestActicveXCtrlCtrl)

// Constructor
public:
	CTestActicveXCtrlCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CTestActicveXCtrlCtrl();

	DECLARE_OLECREATE_EX(CTestActicveXCtrlCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CTestActicveXCtrlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CTestActicveXCtrlCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CTestActicveXCtrlCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	};


private:
    CDuiFrameWnd *  m_udiFrameWnd;
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
};

