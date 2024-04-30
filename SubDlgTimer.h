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
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
      public:
        CEdit m_hour_box;
        CEdit m_minute_box;
        CEdit m_second_box;
        afx_msg void OnBnClickedButton1();
        afx_msg void OnBnClickedButton2();
        afx_msg void OnBnClickedButton3();
        afx_msg void OnBnClickedButton6();
        afx_msg void OnBnClickedButton5();
        afx_msg void OnBnClickedButton4();
        afx_msg void OnBnClickedConv();
};
