
// MFCTimer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCTimerApp:
// See MFCTimer.cpp for the implementation of this class
//

class CMFCTimerApp : public CWinApp
{
public:
	CMFCTimerApp();
    //CMFCTimerApp *pMain_fram;
    // Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCTimerApp theApp;
