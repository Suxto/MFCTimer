#include "pch.h"
#include "Reminder.h"

Reminder::Reminder(CTime &time) : remind_time(time) {}

Reminder::Reminder(CTime &time, CString &content)
    : remind_time(time), remind_content(content) {}

void Reminder::set_content(CString &str) { this->remind_content = str; }

CString Reminder::get_time_as_str() {
    return this->remind_time.Format(_T("%H:%M:%S"));
}
