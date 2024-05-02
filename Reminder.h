#pragma once
class Reminder {
    CTime remind_time;
    CString remind_content;
    bool remind_sound = false;
  public:
    Reminder();
    Reminder(CTime &time);
    Reminder(CTime &time, CString &content);
    
    void set_content(CString &str);
    void set_sound(bool sound);
    CString get_time_as_str();
    CString get_time_left_as_str();
    CString get_content();
    bool get_sound();
};
