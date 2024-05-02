
// MFCTimerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCTimer.h"
#include "MFCTimerDlg.h"
#include "afxdialogex.h"
#include "DlgAdd.h"

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
	: CDialogEx(IDD_MFCTIMER_DIALOG, pParent), m_list(_T("")) {
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMFCTimerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TIME_DISPLAY, m_timeDisplay);
    DDX_LBString(pDX, IDC_LIST1, m_list);
    DDX_Control(pDX, IDC_LIST1, m_list_ctl);
}

BEGIN_MESSAGE_MAP(CMFCTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
        ON_WM_TIMER()
        ON_BN_CLICKED(IDC_BUTTON1, &CMFCTimerDlg::OnBnClickedAddTimer)
        END_MESSAGE_MAP()


// CMFCTimerDlg message handlers
BOOL CMFCTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
    
	
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
    }

    CDialogEx::OnTimer(nIDEvent);
}



void CMFCTimerDlg::OnBnClickedAddTimer() {
    DlgAdd dlg;
    INT_PTR resp = dlg.DoModal();    
}
