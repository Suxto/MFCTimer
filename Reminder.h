#pragma once
class Reminder {
    CTime remind_time;
    CString remind_content;

  public:
    Reminder(CTime &time);
    Reminder(CTime &time, CString &content);
    
    void set_content(CString &str);
    CString get_time_as_str();
};
