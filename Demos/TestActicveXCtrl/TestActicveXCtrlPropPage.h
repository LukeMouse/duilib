#pragma once

// TestActicveXCtrlPropPage.h : Declaration of the CTestActicveXCtrlPropPage property page class.


// CTestActicveXCtrlPropPage : See TestActicveXCtrlPropPage.cpp for implementation.

class CTestActicveXCtrlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CTestActicveXCtrlPropPage)
	DECLARE_OLECREATE_EX(CTestActicveXCtrlPropPage)

// Constructor
public:
	CTestActicveXCtrlPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_TESTACTICVEXCTRL };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

