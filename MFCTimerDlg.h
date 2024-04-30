
// MFCTimerDlg.h : header file
//

#pragma once


// CMFCTimerDlg dialog
class CMFCTimerDlg : public CDialogEx
{
// Construction
public:
	CMFCTimerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTIMER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
        afx_msg HCURSOR OnQueryDragIcon();
        void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
      public:
        CStatic m_timeDisplay;
        CString m_list;
        CListBox m_list_ctl;
        afx_msg void OnBnClickedAddTimer();
};
