#include "pch.h"
#include "Reminder.h"
#include <vector>

Reminder::Reminder() {}

Reminder::Reminder(CTime &time) : remind_time(time) {}

Reminder::Reminder(CTime &time, CString &content)
    : remind_time(time), remind_content(content) {}

void Reminder::set_content(CString &str) { this->remind_content = str; }

void Reminder::set_sound(bool sound) { this->play_sound = sound; }

void Reminder::set_delete(bool del) { this->del_after_remind = del; }

CString Reminder::get_time_as_str() {
    return this->remind_time.Format(_T("%H:%M:%S"));
}

CString Reminder::get_time_left_as_str() {
    CTime now = CTime::GetCurrentTime();
    CTimeSpan span = this->remind_time - now;
    if (span.GetTotalSeconds() < 0) {
        return TEXT("00:00:00");
    } else {
        return span.Format("%H:%M:%S");
    }
}

CString Reminder::get_content() { return this->remind_content; }

CTime Reminder::get_time() { return this->remind_time; }

bool Reminder::get_sound() { return this->play_sound; }

bool Reminder::get_delete() { return this->del_after_remind; }

CArchive &operator<<(CArchive &ar, const Reminder &r) {
    if (ar.IsStoring()) {
        ar << r.remind_time;
        ar << r.remind_content;
        ar << r.play_sound;
        ar << r.del_after_remind;
    }
    return ar;
}

CArchive &operator>>(CArchive &ar, Reminder &r) {
    if (!ar.IsStoring()) {
        ar >> r.remind_time;
        ar >> r.remind_content;
        ar >> r.play_sound;
        ar >> r.del_after_remind;
    }
    CTime now = CTime::GetCurrentTime();
    CTime new_remind_time = CTime(
        now.GetYear(), now.GetMonth(), now.GetDay(), r.remind_time.GetHour(),
        r.remind_time.GetMinute(), r.remind_time.GetSecond());
    return ar;
}
