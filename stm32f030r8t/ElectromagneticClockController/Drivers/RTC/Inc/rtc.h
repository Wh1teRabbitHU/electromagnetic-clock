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

void RTC_init(void);
void RTC_update(DCF77_dateTime_t * dateTime);
void RTC_checkTimeReceived(void);
void RTC_handleInterrupt();


#endif /* RTC_INC_RTC_H_ */
