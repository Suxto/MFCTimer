#pragma once
#include "afxdialogex.h"


// SubDlgTimer dialog

class SubDlgTimer : public CDialogEx
{
	DECLARE_DYNAMIC(SubDlgTimer)

public:
	SubDlgTimer(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SubDlgTimer();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
