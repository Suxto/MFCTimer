// DlgAdd.cpp : implementation file
//

#include "pch.h"
#include "MFCTimer.h"
#include "afxdialogex.h"
#include "DlgAdd.h"

// DlgAdd dialog

IMPLEMENT_DYNAMIC(DlgAdd, CDialogEx)

DlgAdd::DlgAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
  
}

DlgAdd::~DlgAdd()
{
}

void DlgAdd::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    //DDX_Control(pDX, IDC_TAB1, m_tab_ctl);
}


BEGIN_MESSAGE_MAP(DlgAdd, CDialogEx)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &DlgAdd::OnTcnSelchangeTab1)
ON_BN_CLICKED(IDOK, &DlgAdd::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL DlgAdd::OnInitDialog() {
    CDialogEx::OnInitDialog();
    m_tab_ctl.SubclassWindow(GetDlgItem(IDC_TAB1)->m_hWnd);
    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);
    
    
    CRect tabRect, itemRect;
    
    m_tab_ctl.GetClientRect(&tabRect);
    m_tab_ctl.GetItemRect(0, &itemRect);
    int nX, nY, nXc, nYc;
    nX = itemRect.left;
    nY = itemRect.bottom + 1;
    nXc = tabRect.right - itemRect.left - 2;
    nYc = tabRect.bottom - nY - 2;
    
    m_tab_ctl.InsertItem(0, TEXT("闹钟"));
    alarm_dlg.Create(IDD_DIALOG2, &m_tab_ctl);
    arr_dlgs[0] = &alarm_dlg;
    arr_dlgs[0]->ShowWindow(SW_SHOW);
    arr_dlgs[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);

    m_tab_ctl.InsertItem(1, TEXT("倒计时"));
    timer_dlg.Create(IDD_DIALOG3, &m_tab_ctl);
    arr_dlgs[1] = &timer_dlg;
    arr_dlgs[1]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
    arr_dlgs[1]->ShowWindow(SW_HIDE);

    return TRUE; // return TRUE  unless you set the focus to a control
}

void DlgAdd::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult) {
    *pResult = 0;

    // 获取当前选择索引
    int index = m_tab_ctl.GetCurSel();
    //arr_dlgs[index]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
    // 根据索引显示对应的界面
    if (index == 0) {
        arr_dlgs[0]->ShowWindow(SW_SHOW);
        arr_dlgs[1]->ShowWindow(SW_HIDE);
    } else if (index == 1) {
        arr_dlgs[0]->ShowWindow(SW_HIDE);
        arr_dlgs[1]->ShowWindow(SW_SHOW);
    }
}
//#include "mmsystem.h"

void DlgAdd::OnBnClickedOk() {
    int index = m_tab_ctl.GetCurSel();
    CDialog *now = arr_dlgs[index];
    Reminder *r = nullptr;
    if (index == 0) {//闹钟
        SubDlgAlarm *here = static_cast<SubDlgAlarm *>(now);
        r = here->get_time();
        /*PlaySound(MAKEINTRESOURCE(IDR_WAVE1), AfxGetResourceHandle(),
                  SND_ASYNC | SND_RESOURCE | SND_NODEFAULT | SND_LOOP);
        MessageBoxEx(nullptr, r->get_time_as_str().GetString(), MB_OK, 0, 0);
        PlaySound(nullptr, AfxGetResourceHandle(), SND_PURGE);*/

    } else if(index==1){//倒计时
        SubDlgTimer *here = static_cast<SubDlgTimer *>(now);
        r = here->get_time();
    }
    delete r;
    CDialogEx::OnOK();
}
