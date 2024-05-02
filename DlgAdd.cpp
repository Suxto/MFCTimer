// DlgAdd.cpp : implementation file
//

#include "pch.h"
#include "MFCTimer.h"
#include "afxdialogex.h"
#include "DlgAdd.h"
#include "Reminder.h"
#include "DlgRemind.h"
#include "MFCTimerDlg.h"
// DlgAdd dialog

IMPLEMENT_DYNAMIC(DlgAdd, CDialogEx)

DlgAdd::DlgAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
  
}

DlgAdd::~DlgAdd(){}

void DlgAdd::set_idx(int idx) { this->selection_idx = idx; }

void DlgAdd::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    // DDX_Control(pDX, IDC_TAB1, m_tab_ctl);
    DDX_Control(pDX, IDC_EDIT1, m_remind_content);
    DDX_Control(pDX, IDC_RADIO1, m_play_sound);
    DDX_Control(pDX, IDOK, m_bn_op);
    DDX_Control(pDX, IDOK2, m_bn_del);
    DDX_Control(pDX, IDC_RADIO3, m_delete_after_remind);
}


BEGIN_MESSAGE_MAP(DlgAdd, CDialogEx)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &DlgAdd::OnTcnSelchangeTab1)
ON_BN_CLICKED(IDOK, &DlgAdd::OnBnClickedOk)
ON_BN_CLICKED(IDOK2, &DlgAdd::OnBnClickedOk2)
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
    
    //默认播放声音为否
    ((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
    //默认提醒后删除
    ((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);

    if (selection_idx != -1) {
        CMFCTimerDlg *app =
            static_cast<CMFCTimerDlg *>(AfxGetApp()->m_pMainWnd);

        Reminder &r = app->reminders[selection_idx];
        m_remind_content.SetWindowTextW(r.get_content());
        CTime time = r.get_time();
        CTimeSpan span = time - CTime::GetCurrentTime();
        alarm_dlg.set_boxs(time.GetHour(), time.GetMinute(), time.GetSecond());

        if (span.GetTotalSeconds() > 0)
            timer_dlg.set_boxs(span.GetHours(), span.GetHours(),
                               span.GetSeconds());
        else
            timer_dlg.set_boxs(0, 0, 0);

        if (r.get_sound()) {
            ((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
            ((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
        }

        if (!r.get_delete()) {
            ((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(FALSE);
            ((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(TRUE);
        }
        m_bn_op.SetWindowTextW(_TEXT("修改"));
        m_bn_del.ShowWindow(SW_SHOW);
    }
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


void DlgAdd::OnBnClickedOk() {
    int index = m_tab_ctl.GetCurSel();
    CDialog *now = arr_dlgs[index];
    Reminder *r = nullptr;
    if (index == 0) {//闹钟
        SubDlgAlarm *here = static_cast<SubDlgAlarm *>(now);
        r = here->get_time();
        
        //MessageBoxEx(nullptr, r->get_time_as_str().GetString(), MB_OK, 0, 0);
    } else if(index == 1){//倒计时
        SubDlgTimer *here = static_cast<SubDlgTimer *>(now);
        r = here->get_time();
    }
    CString remind_text;
    m_remind_content.GetWindowTextW(remind_text);
    r->set_content(remind_text);

    int i = m_play_sound.GetCheck();
    r->set_sound(i > 0);
    i = m_delete_after_remind.GetCheck();
    r->set_delete(i > 0);
    CMFCTimerDlg *main_wnd =
        static_cast<CMFCTimerDlg *>(AfxGetApp()->m_pMainWnd);

    if (r != nullptr) {
        if (selection_idx == -1) {
            main_wnd->addReminder(*r);
        } else {
            main_wnd->reminders[selection_idx] = *r;
        }
        delete r;
    }

    CDialogEx::OnOK();
}

void DlgAdd::OnBnClickedOk2() {
    CMFCTimerDlg *main_wnd =
        static_cast<CMFCTimerDlg *>(AfxGetApp()->m_pMainWnd);
    main_wnd->removeReminder(selection_idx);
    CDialogEx::OnOK();
}
