#pragma once
#include "afxdialogex.h"
#include "Reminder.h"

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
	virtual BOOL OnInitDialog();
    virtual void PostNcDestroy();
	DECLARE_MESSAGE_MAP()

public:
  CEdit m_remind_content;
  CStatic m_time_text;
  afx_msg void OnBnClickedOk();
  Reminder reminder;
  int idx;
  void set_reminder(int idx, Reminder &r);
};
