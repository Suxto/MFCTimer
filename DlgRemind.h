#pragma once
#include "afxdialogex.h"


// DlgRemind dialog

class DlgRemind : public CDialogEx
{
	DECLARE_DYNAMIC(DlgRemind)

public:
	DlgRemind(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgRemind();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
