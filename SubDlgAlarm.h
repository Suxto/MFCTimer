#pragma once
#include "afxdialogex.h"


// SubDlgAlarm dialog

class SubDlgAlarm : public CDialogEx
{
	DECLARE_DYNAMIC(SubDlgAlarm)

public:
	SubDlgAlarm(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SubDlgAlarm();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
