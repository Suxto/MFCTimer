#include "pch.h"
#include "Reminder.h"

Reminder::Reminder() {}

Reminder::Reminder(CTime &time) : remind_time(time) {}

Reminder::Reminder(CTime &time, CString &content)
    : remind_time(time), remind_content(content) {}

void Reminder::set_content(CString &str) { this->remind_content = str; }

void Reminder::set_sound(bool sound) { this->remind_sound = sound; }

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

bool Reminder::get_sound() { return this->remind_sound; }
