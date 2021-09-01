#ifndef RTC_HANDLER_H
#define RTC_HANDLER_H

#include "stdint.h"
#include "RTClib.h"
#include "display-handler.h"

void setupRTC();
void checkTime();
void updateRtc();
void refreshDisplay();
void setHours(int8_t hourOffset);
void setMinutes(int8_t minuteOffset);

#endif