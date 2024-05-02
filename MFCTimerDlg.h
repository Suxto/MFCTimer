
// MFCTimerDlg.h : header file
//

#pragma once
#ifndef Reminder_H
#include "Reminder.h"
#endif // !Reminder_H
#include<vector>


// CMFCTimerDlg dialog
class CMFCTimerDlg : public CDialogEx
{
// Construction
public:
	CMFCTimerDlg(CWnd* pParent = nullptr);	// standard constructor
	void addReminder(Reminder &r);
	void addReminder(CTime time, CString content, bool toggleSound);
	void removeReminder(int index);
	void refreshReminderList();
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
		std::vector<Reminder> reminders;
        CStatic m_timeDisplay;
        CListCtrl m_listCtrl;
        afx_msg void OnBnClickedAddTimer();
		afx_msg void OnListClick(NMHDR* pNMHDR, LRESULT* pResult);
};
