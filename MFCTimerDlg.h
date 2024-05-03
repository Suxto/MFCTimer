
// MFCTimerDlg.h : header file
//

#pragma once
#ifndef Reminder_H
#include "Reminder.h"
#endif // !Reminder_H
#include <vector>
#include <algorithm>


// CMFCTimerDlg dialog
class CMFCTimerDlg : public CDialogEx
{
    int sort_type = 0;
// Construction
public:
	CMFCTimerDlg(CWnd* pParent = nullptr);	// standard constructor
	void addReminder(Reminder &r);
	void addReminder(CTime time, CString content, bool toggleSound);
	void removeReminder(int index);
	void clearReminder();
	void refreshReminderList();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTIMER_DIALOG };
#endif
    void sort_by_time();
    void sort_by_id();
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
		afx_msg void OnBnClickedClearAllTimer();
		afx_msg void OnListClick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnBnClickedSaveFile();
                afx_msg void OnBnClickedReadFile();
        afx_msg void OnCbnSelchangeCombo1();
                CComboBox m_box_sort_type;
};
