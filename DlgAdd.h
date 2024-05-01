#pragma once
#include "afxdialogex.h"
#include "afxcmn.h"
#include "SubDlgAlarm.h"
#include "SubDlgTimer.h"

// DlgAdd dialog

class DlgAdd : public CDialogEx {
	DECLARE_DYNAMIC(DlgAdd)

public:
	DlgAdd(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgAdd();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
      public:
        CTabCtrl m_tab_ctl;
        SubDlgAlarm alarm_dlg;
        SubDlgTimer timer_dlg;
        CDialog *arr_dlgs[2];
        afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
        afx_msg void OnBnClickedOk();
};
