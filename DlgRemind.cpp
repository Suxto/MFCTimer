// DlgRemind.cpp : implementation file
//

#include "pch.h"
#include "MFCTimer.h"
#include "afxdialogex.h"
#include "mmsystem.h"
#include "DlgRemind.h"
#include "MFCTimerDlg.h"

// DlgRemind dialog

IMPLEMENT_DYNAMIC(DlgRemind, CDialogEx)

DlgRemind::DlgRemind(CWnd *pParent /*= nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

DlgRemind::~DlgRemind()
{}

void DlgRemind::set_reminder(int idx, Reminder &r) {
    this->reminder = r;
    this->idx = idx;
}

void DlgRemind::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_remind_content);
    DDX_Control(pDX, IDC_TIME_TEXT, m_time_text);
}

BOOL DlgRemind::OnInitDialog() {
    //设置时间字体
    HFONT timeFont = ::CreateFont(30,        // 字体的高度
                                  0,         // 字体的宽度
                                  0,         // 字体的倾斜
                                  0,         // 字体的倾斜的偏移量
                                  FW_NORMAL, // 字体的重量
                                  FALSE,     // 是否斜体
                                  FALSE,     // 是否下划线
                                  0,         // 字体的特定 underline 样式
                                  ANSI_CHARSET,             // 字符集
                                  OUT_DEFAULT_PRECIS,       // 输出精度
                                  CLIP_DEFAULT_PRECIS,      // 剪裁精度
                                  DEFAULT_QUALITY,          // 输出质量
                                  DEFAULT_PITCH | FF_SWISS, // 字体的间距和族
                                  _T("Arial")               // 字体名称
    );
    CFont *pFont = CFont::FromHandle(timeFont);


    //设置提醒事项
    CDialogEx::OnInitDialog();
    CString str_time = this->reminder.get_time_as_str();
    m_time_text.SetFont(pFont);
    m_time_text.SetWindowTextW(str_time);
    m_remind_content.SetWindowTextW(this->reminder.get_content());
    if (this->reminder.get_sound()) {
        PlaySound(nullptr, AfxGetResourceHandle(), SND_PURGE);
        PlaySound(MAKEINTRESOURCE(IDR_WAVE1), AfxGetResourceHandle(),
                  SND_ASYNC | SND_RESOURCE | SND_NODEFAULT | SND_LOOP);
    }
    return 0;
}


void DlgRemind::PostNcDestroy() {
    CDialogEx::PostNcDestroy();
    delete this;
}


BEGIN_MESSAGE_MAP(DlgRemind, CDialogEx)
ON_BN_CLICKED(IDOK, &DlgRemind::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgRemind message handlers

void DlgRemind::OnBnClickedOk() {
    // TODO: Add your control notification handler code here
    PlaySound(nullptr, AfxGetResourceHandle(), SND_PURGE);
    if (reminder.get_delete()) {
        CMFCTimerDlg *app =
            static_cast<CMFCTimerDlg *>(AfxGetApp()->m_pMainWnd);
        app->removeReminder(idx);
    }
    CDialogEx::OnOK();
}
