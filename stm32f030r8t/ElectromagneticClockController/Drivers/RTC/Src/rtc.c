#include "rtc.h"

void RTC_init(void) {
	DCF77_enable();
}

void RTC_update(DCF77_dateTime_t * dateTime) {
	ESSDisplay_displayTime(dateTime);
}

void RTC_checkTimeReceived() {
	if (DCF77_timeReceived()) {
		DCF77_reset();

		DCF77_dateTime_t * currentDateTime = DCF77_lastTimeValue();

		RTC_update(currentDateTime);

		DCF77_disable();
	}
}

void RTC_handleInterrupt() {
}
