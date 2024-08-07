
// MFCTimerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCTimer.h"
#include "MFCTimerDlg.h"
#include "afxdialogex.h"
#include "DlgAdd.h"
#include "DlgRemind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCTimerDlg dialog



CMFCTimerDlg::CMFCTimerDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MFCTIMER_DIALOG, pParent) {
    //m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMFCTimerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TIME_DISPLAY, m_timeDisplay);
    DDX_Control(pDX, IDC_COMBO1, m_box_sort_type);
}

LRESULT CMFCTimerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
   /* if (message == WM_PAINT) {
        CRect rect;
        m_listCtrl.GetWindowRect(&rect);
        ScreenToClient(&rect);
        InvalidateRect(&rect, FALSE);
        return Default();
    }*/


    return CDialogEx::WindowProc(message, wParam, lParam);
}

BEGIN_MESSAGE_MAP(CMFCTimerDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
        ON_WM_TIMER()
        ON_BN_CLICKED(IDC_BUTTON1, &CMFCTimerDlg::OnBnClickedAddTimer)
        ON_BN_CLICKED(IDC_BUTTON2, &CMFCTimerDlg::OnBnClickedClearAllTimer)
        ON_BN_CLICKED(IDC_BUTTON3, &CMFCTimerDlg::OnBnClickedSaveFile)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CMFCTimerDlg::OnListClick)
    ON_MESSAGE(WM_SHOWTASK, &CMFCTimerDlg::OnShowTask)
    ON_MESSAGE(WM_SHOWINDOW, &CMFCTimerDlg::OnShowWindow)
    ON_BN_CLICKED(IDC_BUTTON4, &CMFCTimerDlg::OnBnClickedReadFile)
        ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCTimerDlg::OnCbnSelchangeSortType)
    ON_BN_CLICKED(IDC_BUTTON5, &CMFCTimerDlg::OnBnClickedButton5)
    END_MESSAGE_MAP()


// CMFCTimerDlg message handlers
BOOL CMFCTimerDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    
    m_box_sort_type.AddString(TEXT("添加顺序"));
    m_box_sort_type.AddString(TEXT("提醒时间"));
    m_box_sort_type.SetCurSel(0);

    m_nid.cbSize = sizeof(NOTIFYICONDATA);
    m_nid.hWnd = GetSafeHwnd();
    m_nid.uID = IDR_MAINFRAME;
    m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    m_nid.uCallbackMessage = WM_SHOWTASK;
    m_nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    _tcsncpy_s(m_nid.szTip, TEXT("MFCTimer"),
               sizeof(m_nid.szTip) / sizeof(m_nid.szTip[0]));
    
    

     //IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    HFONT timeFont = ::CreateFont(80,     // 字体的高度
                               0,         // 字体的宽度
                               0,         // 字体的倾斜
                               0,         // 字体的倾斜的偏移量
                               FW_NORMAL, // 字体的重量
                               FALSE,     // 是否斜体
                               FALSE,     // 是否下划线
                               0, // 字体的特定 underline 样式
                               ANSI_CHARSET,             // 字符集
                               OUT_DEFAULT_PRECIS,       // 输出精度
                               CLIP_DEFAULT_PRECIS,      // 剪裁精度
                               DEFAULT_QUALITY,          // 输出质量
                               DEFAULT_PITCH | FF_SWISS, // 字体的间距和族
                               _T("Arial")               // 字体名称
        );
    CFont *pFont = CFont::FromHandle(timeFont);


    // 获取当前时间
    CTime currentTime = CTime::GetCurrentTime();

    // 将时间显示在静态文本中
    CString strTime = currentTime.Format(_T("%H:%M:%S"));
    m_timeDisplay.SetWindowText(strTime);
    m_timeDisplay.SetFont(pFont);

    //设置定时器
    CWnd::SetTimer(1, 1000, nullptr);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here
    // 获取列表视图控件的指针
    m_listCtrl.SubclassDlgItem(IDC_LIST1, this);

    // 设置列表视图控件的样式
    DWORD dwStyle = LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS;
    m_listCtrl.ModifyStyle(0, dwStyle);

    // 添加列表视图的列
    CString header;
    CRect rect;
    m_listCtrl.GetClientRect(&rect);
        header.Format(_T("%12s%12s%16s"), TEXT("提醒时间"), TEXT("剩余时间"),
                      TEXT("提醒内容"));
    m_listCtrl.InsertColumn(0, header, LVCFMT_CENTER, rect.Width());

    CTime time(0);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCTimerDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCTimerDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CMFCTimerDlg::OnTimer(UINT_PTR nIDEvent) {
    if (nIDEvent == 1) {
        // 获取当前时间
        CTime currentTime = CTime::GetCurrentTime();

        // 将时间显示在静态文本中
        CString strTime = currentTime.Format(_T("%H:%M:%S"));
        m_timeDisplay.SetWindowText(strTime);

        refreshReminderList();

      /*  for (int i = 0; i < reminders.size();i++) {
            auto &r = reminders[i];
            CTime time = r.get_time();
            CTimeSpan span = time - currentTime;
            if (span == 0) {
                DlgRemind *dlg = new DlgRemind;
                dlg->set_reminder(i, r);
                dlg->Create(IDD_DIALOG4, this);
                dlg->ShowWindow(SW_SHOW);
            }

        }*/

    }

    CDialogEx::OnTimer(nIDEvent);
}

LRESULT CMFCTimerDlg::OnShowTask(WPARAM wParam, LPARAM lParam) {
    if (wParam != IDR_MAINFRAME) {
        return 1;
    }
    switch (lParam) {
        case WM_RBUTTONUP: {
            LPPOINT lpoint = new tagPOINT;
            ::GetCursorPos(lpoint); // 得到鼠标位置
            CMenu menu;
            menu.CreatePopupMenu(); // 声明一个弹出式菜单

            menu.AppendMenuW(MF_STRING, WM_SHOWINDOW, TEXT("显示窗口"));
            menu.AppendMenuW(MF_STRING, WM_DESTROY, TEXT("退出"));

            SetForegroundWindow();
            // 确定弹出式菜单的位置
            BOOL result = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD,
                                              lpoint->x,
                                lpoint->y, this);

            if (result == WM_SHOWINDOW) {
                OnShowWindow(IDR_MAINFRAME, WM_LBUTTONDOWN);
            }
            else if (result == WM_DESTROY) {
                AfxPostQuitMessage(0);
            }

            HMENU hmenu = menu.Detach();
            menu.DestroyMenu();
            delete lpoint;
        } break;

        case WM_LBUTTONDBLCLK: 
            //this->ShowWindow(SW_SHOW);
        case WM_LBUTTONDOWN:
            //this->ShowWindow(SW_SHOW);
            OnShowWindow(IDR_MAINFRAME, WM_LBUTTONDOWN);
            break;
    }
    return 0;
}

LRESULT CMFCTimerDlg::OnShowWindow(WPARAM wParam, LPARAM lParam) {
    if (wParam != IDR_MAINFRAME)
        return 1;

    this->ShowWindow(SW_SHOW);
    Shell_NotifyIcon(NIM_DELETE, &m_nid);
    return 0;
}



void CMFCTimerDlg::OnBnClickedAddTimer() {
    DlgAdd dlg;
    INT_PTR resp = dlg.DoModal();    
}

void CMFCTimerDlg::OnBnClickedClearAllTimer() {
    clearReminder();
}


void CMFCTimerDlg::OnListClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    // 获取点击的行和列索引
    int nItem = pNMListView->iItem;

    int nSubItem = pNMListView->iSubItem;


    if (nItem >= 0) {
        /*Reminder r = reminders[nItem];
        CString list_item;
                list_item.Format(_T("%12s%12s%16s"), r.get_time_as_str(),
                                 r.get_time_as_str(), r.get_content());
        MessageBoxW(list_item);*/
        DlgAdd dlg;
        dlg.set_idx(nItem);
        dlg.DoModal();
    }

    *pResult = 0;
}

void CMFCTimerDlg::sort_by_time() { 
    std::sort(reminders.begin(), reminders.end(), [](Reminder &a, Reminder &b) {
        return a.get_time() < b.get_time();
    });
}

void CMFCTimerDlg::sort_by_id() {
    std::sort(reminders.begin(), reminders.end(), [](Reminder &a, Reminder &b) {
        return a.get_id() < b.get_id();
    });
}

void CMFCTimerDlg::addReminder(Reminder &r) {
    reminders.push_back(r);
    if (sort_type == 1) {
        sort_by_time();
    }
    refreshReminderList();
}

//void CMFCTimerDlg::addReminder(CTime time, CString content, bool toggleSound) {
//    Reminder r(time);
//    r.set_content(content);
//    r.set_sound(toggleSound);
//    addReminder(r);
//}

void CMFCTimerDlg::removeReminder(int index) {
    reminders.erase(reminders.begin() + index);
    m_listCtrl.DeleteItem(index);
}

void CMFCTimerDlg::clearReminder() {
    reminders.clear();
    m_listCtrl.DeleteAllItems();
}

void CMFCTimerDlg::refreshReminderList() {
    m_listCtrl.DeleteAllItems();
    CTime now = CTime::GetCurrentTime();
    for (int i = 0; i < reminders.size(); i++) {
        CTime time = reminders[i].get_time();
        CTimeSpan span = time - now;
        CString time_left = TEXT("00:00:00");;
        if (span == 0) {
            DlgRemind *dlg = new DlgRemind;
            dlg->set_reminder(i, reminders[i]);
            dlg->Create(IDD_DIALOG4, this);
            dlg->ShowWindow(SW_SHOW);
        } else if(span > 0) {
            time_left = span.Format(_T("%H:%M:%S"));
        }
        CString content = reminders[i].get_content();
        CString list_item;
        list_item.Format(_T("%16s%16s  %16s"), time.Format(_T("%H:%M:%S")), time_left, content);
        int idx = m_listCtrl.GetItemCount();
        m_listCtrl.InsertItem(idx, list_item);
    }
}


void CMFCTimerDlg::OnBnClickedSaveFile() {
    CFileDialog fileDlg(FALSE, _T("dat"), nullptr, OFN_OVERWRITEPROMPT,
                        _T("Data Files (*.dat)|*.dat|"));
    if (fileDlg.DoModal() == IDOK) {
        CFile file(fileDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
        CArchive ar(&file, CArchive::store);

        int count = static_cast<int>(reminders.size());
        ar << count;
        for (const auto &reminder : reminders) {
            ar << reminder;
        }

        ar.Close();
        file.Close();
    } 
}

void CMFCTimerDlg::OnBnClickedReadFile() {
    CFileDialog fileDlg(TRUE, _T("dat"), nullptr, OFN_OVERWRITEPROMPT,
                        _T("Data Files (*.dat)|*.dat|"));
    if (fileDlg.DoModal() == IDOK) {
        CFile file(fileDlg.GetPathName(), CFile::modeRead);
        CArchive ar(&file, CArchive::load);

        int count;
        ar >> count;

        reminders.resize(count);
        for (auto &reminder : reminders) {
            ar >> reminder;
        }

        ar.Close();
        file.Close();
    } 
    OnCbnSelchangeSortType();
}

void CMFCTimerDlg::OnCbnSelchangeSortType() {
    this->sort_type = m_box_sort_type.GetCurSel();
    if (sort_type == 0) {
        sort_by_id();
    } else if (sort_type == 1) {
        sort_by_time();
    }
}

void CMFCTimerDlg::OnBnClickedButton5() {
    this->ShowWindow(SW_HIDE);
    Shell_NotifyIcon(NIM_ADD, &m_nid);
}
