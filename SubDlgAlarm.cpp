// SubDlgAlarm.cpp : implementation file
//

#include "pch.h"
#include "MFCTimer.h"
#include "afxdialogex.h"
#include "SubDlgAlarm.h"


// SubDlgAlarm dialog

IMPLEMENT_DYNAMIC(SubDlgAlarm, CDialogEx)

SubDlgAlarm::SubDlgAlarm(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG2, pParent) {

}
BOOL SubDlgAlarm::OnInitDialog() {
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
    SubDlgAlarm::~SubDlgAlarm()
{
}

void SubDlgAlarm::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_hour_box);
    DDX_Control(pDX, IDC_EDIT2, m_minute_box);
    DDX_Control(pDX, IDC_EDIT3, m_second_box);
}


BEGIN_MESSAGE_MAP(SubDlgAlarm, CDialogEx)
    ON_EN_KILLFOCUS(IDC_EDIT1, &SubDlgAlarm::OnEnKillfocusHourBox)
    ON_EN_KILLFOCUS(IDC_EDIT2, &SubDlgAlarm::OnEnKillfocusMinuteBox)
    ON_EN_KILLFOCUS(IDC_EDIT3, &SubDlgAlarm::OnEnKillfocusSecondBox)
    ON_BN_CLICKED(IDC_BUTTON1, &SubDlgAlarm::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON4, &SubDlgAlarm::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON2, &SubDlgAlarm::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON5, &SubDlgAlarm::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON3, &SubDlgAlarm::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON6, &SubDlgAlarm::OnBnClickedButton6)
END_MESSAGE_MAP()


// SubDlgAlarm message handlers

void box_filter(CEdit& box, int l, int r) {
    CString strText;
    box.GetWindowText(strText);

    // 遍历文本,删除非数字字符
    CString strFilteredText;
    for (int i = 0; i < strText.GetLength(); i++) {
        if (isdigit(strText[i])) {
            strFilteredText += strText[i];
        }
    }
    int nValue = _ttoi(strText);

    if (nValue < l || nValue > r) {
        strFilteredText.Format(_T("%d"), r);
    }
    // 设置过滤后的文本
    box.SetWindowText(strFilteredText);
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

void modify_box(CEdit &box, int val, int l, int r) {
    CString strText;
    box.GetWindowText(strText);
    int nValue = _ttoi(strText);
    int new_val = nValue + val;
    if (new_val < l || new_val > r)
        return;
    strText.Format(_T("%d"), new_val);
    box.SetWindowTextW(strText);
}

void SubDlgAlarm::OnEnKillfocusHourBox() { box_filter(m_hour_box, 0, 23); }

void SubDlgAlarm::OnEnKillfocusMinuteBox() { box_filter(m_minute_box, 0, 59); }

void SubDlgAlarm::OnEnKillfocusSecondBox() { box_filter(m_second_box, 0, 59); }

void SubDlgAlarm::OnBnClickedButton1() { modify_box(m_hour_box, 1, 0, 23); }

void SubDlgAlarm::OnBnClickedButton4() { modify_box(m_hour_box, -1, 0, 23); }

void SubDlgAlarm::OnBnClickedButton2() { modify_box(m_minute_box, 1, 0, 59); }

void SubDlgAlarm::OnBnClickedButton5() { modify_box(m_minute_box, -1, 0, 59); }

void SubDlgAlarm::OnBnClickedButton3() { modify_box(m_second_box, 1, 0, 59); }

void SubDlgAlarm::OnBnClickedButton6() { modify_box(m_second_box, -1, 0, 59); }

void SubDlgAlarm::set_boxs(int h, int m, int s) { 
    CString tmp;
    
    tmp.Format(_T("%d"), h);
    m_hour_box.SetWindowTextW(tmp);

    tmp.Format(_T("%d"), m);
    m_minute_box.SetWindowTextW(tmp);

    tmp.Format(_T("%d"), s);
    m_second_box.SetWindowTextW(tmp);
}



Reminder *SubDlgAlarm::get_time() {
    int hour = get_box(m_hour_box);
    int minute = get_box(m_minute_box);
    int second = get_box(m_second_box);
    CTime time(2024, 5, 1, hour, minute, second);
    return new Reminder(time);
}
