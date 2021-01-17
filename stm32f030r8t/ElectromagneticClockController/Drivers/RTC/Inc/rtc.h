/*
 * rtc.h
 *
 *  Created on: Jan 17, 2021
 *      Author: tom
 */

#ifndef RTC_INC_RTC_H_
#define RTC_INC_RTC_H_

#include "dcf77.h"
#include "essdisplay.h"

#define RTC_FORMAT_BCD 0x000000001U

void RTC_init(RTC_HandleTypeDef * hrtc);
void RTC_load();
void RTC_save(DCF77_dateTime_t * dateTime);
void RTC_updateDisplay();
void RTC_checkTimeReceived(void);
void RTC_handleAlarmEvent(RTC_HandleTypeDef *hrtc);


#endif /* RTC_INC_RTC_H_ */
