#include "rtc.h"
#include "stm32f0xx_hal_rtc.h"

static RTC_HandleTypeDef rtcHandle;
static RTC_DateTypeDef rtcDate = {0};
static RTC_TimeTypeDef rtcTime = {0};

void RTC_init(RTC_HandleTypeDef * hrtc) {
	rtcHandle = *hrtc;

	__HAL_RTC_ALARM_ENABLE_IT(hrtc, RTC_IT_ALRA);

	RTC_load();
	DCF77_enable();
}

void RTC_load() {
	if (HAL_RTC_GetDate(&rtcHandle, &rtcDate, RTC_FORMAT_BCD) != HAL_OK) {
		// TODO: Error_Handler();
	}
	if (HAL_RTC_GetTime(&rtcHandle, &rtcTime, RTC_FORMAT_BCD) != HAL_OK) {
		// TODO: Error_Handler();
	}

	RTC_updateDisplay();
}

void RTC_save(DCF77_dateTime_t * dateTime) {
	rtcDate.Year = dateTime->years;
	rtcDate.Month = dateTime->months;
	rtcDate.WeekDay = dateTime->dayOfWeek;
	rtcDate.Date = dateTime->dayOfMonth;

	rtcTime.Hours = dateTime->hours;
	rtcTime.Minutes = dateTime->minutes;

	if (HAL_RTC_SetDate(&rtcHandle, &rtcDate, RTC_FORMAT_BCD) != HAL_OK) {
		// TODO: Error_Handler();
	}
	if (HAL_RTC_SetTime(&rtcHandle, &rtcTime, RTC_FORMAT_BCD) != HAL_OK) {
		// TODO: Error_Handler();
	}

	RTC_updateDisplay();
}

void RTC_updateDisplay() {
	ESSDisplay_displayTime(rtcTime.Hours, rtcTime.Minutes);
}

void RTC_checkTimeReceived() {
	if (DCF77_timeReceived()) {
		DCF77_reset();

		DCF77_dateTime_t * currentDateTime = DCF77_lastTimeValue();

		RTC_save(currentDateTime);

		DCF77_disable();
	}
}

void RTC_handleAlarmEvent(RTC_HandleTypeDef *hrtc) {
	rtcHandle = *hrtc;

	RTC_load();

	// Every hour we want to update the time using DCF77
	if (rtcTime.Minutes == 0) {
		DCF77_enable();
	}
}
