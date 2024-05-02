#pragma once
class Reminder {
    CTime remind_time;
    CString remind_content;
    bool play_sound = false;
    bool del_after_remind = true;
  public:
    Reminder();
    Reminder(CTime &time);
    Reminder(CTime &time, CString &content);
    
    void set_content(CString &str);
    void set_sound(bool sound);
    void set_delete(bool sound);
    CString get_time_as_str();
    CString get_time_left_as_str();
    CString get_content();
    CTime get_time();
    bool get_sound();
    bool get_delete();
};
