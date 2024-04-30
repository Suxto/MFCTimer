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
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
      public:
        CEdit m_hour_box;
        CEdit m_minute_box;
        CEdit m_second_box;
        afx_msg void OnEnKillfocusHourBox();
        afx_msg void OnEnKillfocusMinuteBox();
        afx_msg void OnEnKillfocusSecondBox();
        afx_msg void OnBnClickedButton1();
        afx_msg void OnBnClickedButton4();
        afx_msg void OnBnClickedButton2();
        afx_msg void OnBnClickedButton5();
        afx_msg void OnBnClickedButton3();
        afx_msg void OnBnClickedButton6();
};
