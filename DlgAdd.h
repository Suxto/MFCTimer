#pragma once
#include "afxdialogex.h"
#include "afxcmn.h"
#include "SubDlgAlarm.h"
#include "SubDlgTimer.h"
// DlgAdd dialog

class DlgAdd : public CDialogEx {
	DECLARE_DYNAMIC(DlgAdd)
    int selection_idx = -1;

  public:
	DlgAdd(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgAdd();
    void set_idx(int idx);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
      public:
        CEdit m_remind_content;
        CButton m_play_sound;
        CTabCtrl m_tab_ctl;
        SubDlgAlarm alarm_dlg;
        SubDlgTimer timer_dlg;
        CDialog *arr_dlgs[2];
        afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
        afx_msg void OnBnClickedOk();
        CButton m_bn_op;
        CButton m_bn_del;
        afx_msg void OnBnClickedOk2();
        CButton m_delete_after_remind;
};
