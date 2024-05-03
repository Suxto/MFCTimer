// SubDlgTimer.cpp : implementation file
//

#include "pch.h"
#include "MFCTimer.h"
#include "afxdialogex.h"
#include "SubDlgTimer.h"


// SubDlgTimer dialog

IMPLEMENT_DYNAMIC(SubDlgTimer, CDialogEx)

SubDlgTimer::SubDlgTimer(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}


BOOL SubDlgTimer::OnInitDialog() {
    CDialogEx::OnInitDialog();

    HFONT timeFont = ::CreateFont(40,        // 字体的高度
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

    m_hour_box.SetWindowTextW(TEXT("0"));
    m_hour_box.SetFont(pFont);

    m_minute_box.SetWindowTextW(TEXT("0"));
    m_minute_box.SetFont(pFont);

    m_second_box.SetWindowTextW(TEXT("0"));
    m_second_box.SetFont(pFont);

    return TRUE;
}

SubDlgTimer::~SubDlgTimer()
{
}

void SubDlgTimer::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_hour_box);
    DDX_Control(pDX, IDC_EDIT2, m_minute_box);
    DDX_Control(pDX, IDC_EDIT3, m_second_box);
}


BEGIN_MESSAGE_MAP(SubDlgTimer, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON1, &SubDlgTimer::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &SubDlgTimer::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &SubDlgTimer::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON6, &SubDlgTimer::OnBnClickedButton6)
ON_BN_CLICKED(IDC_BUTTON5, &SubDlgTimer::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON4, &SubDlgTimer::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON7, &SubDlgTimer::OnBnClickedConv)
ON_BN_CLICKED(IDC_BUTTON8, &SubDlgTimer::OnBnClickedReset)
END_MESSAGE_MAP()


void modify_box1(CEdit &box, int val, int l, int r) {
    CString strText;
    box.GetWindowText(strText);
    int nValue = _ttoi(strText);
    int new_val = nValue + val;
    if (new_val < l || new_val > r)
        return;
    strText.Format(_T("%d"), new_val);
    box.SetWindowTextW(strText);
}

void SubDlgTimer::OnBnClickedButton1() {
    modify_box1(m_hour_box, 1, 0, INT_MAX);
}

void SubDlgTimer::OnBnClickedButton4() {
    modify_box1(m_hour_box, -1, 0, INT_MAX);
}

void SubDlgTimer::OnBnClickedButton2() {
    modify_box1(m_minute_box, 1, 0, INT_MAX);
}

void SubDlgTimer::OnBnClickedButton5() {
    modify_box1(m_minute_box, -1, 0, INT_MAX);
}

void SubDlgTimer::OnBnClickedButton3() {
    modify_box1(m_second_box, 1, 0, INT_MAX);
}

void SubDlgTimer::OnBnClickedButton6() {
    modify_box1(m_second_box, -1, 0, INT_MAX);
}

inline void set_box(CEdit &box, int t) {
    CString str;
    str.Format(_T("%d"), t);
    box.SetWindowTextW(str);
}

inline int get_box(CEdit &box) {
    CString str;
    box.GetWindowTextW(str);
    return _ttoi(str);
}

void SubDlgTimer::OnBnClickedConv() {
    // TODO: Add your control notification handler code here
    int seconds = 0;
    CString str;
    m_hour_box.GetWindowTextW(str);
    seconds += _ttoi(str) * 3600;
    
    m_minute_box.GetWindowTextW(str);
    seconds += _ttoi(str) * 60;

    m_second_box.GetWindowTextW(str);
    seconds += _ttoi(str);

    int hour = seconds / 3600;
    seconds %= 3600;

    int minute = seconds / 60;
    seconds %= 60;

    set_box(m_hour_box, hour);
    set_box(m_minute_box, minute);
    set_box(m_second_box, seconds);
}

void SubDlgTimer::set_boxs(int hour, int minute , int second) {
    set_box(m_hour_box, hour);
    set_box(m_minute_box, minute);
    set_box(m_second_box, second);
}

Reminder* SubDlgTimer::get_time() { 
    this->OnBnClickedConv();
    // 获取当前时间
    CTime currentTime = CTime::GetCurrentTime();
    int hour = get_box(m_hour_box);
    int minute = get_box(m_minute_box);
    int second = get_box(m_second_box);

    CTimeSpan span(0, hour, minute, second);
    currentTime += span;
    return new Reminder(currentTime); 
}

void SubDlgTimer::OnBnClickedReset() {
    set_boxs(0, 0, 0);
    // TODO: Add your control notification handler code here
}
