#pragma once
class Reminder {
    static int num;
    int id;
    CTime remind_time;
    CString remind_content;
    bool play_sound = false;
    bool del_after_remind = true;
  public:
    Reminder();
    Reminder(CTime &time);
    Reminder(CTime &time, CString &content);
    //setter
    void set_content(CString &str);
    void set_sound(bool sound);
    void set_delete(bool sound);
    void set_id(int id);
    //getter
    CString get_time_as_str();
    CString get_time_left_as_str();
    CString get_content();
    CTime get_time();
    bool get_sound();
    bool get_delete();
    int get_id();
    //etc.
    friend CArchive &operator<<(CArchive &ar, const Reminder &r);
    friend CArchive &operator>>(CArchive &ar, Reminder &r);
    
};
