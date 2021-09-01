#include "rtc-handler.h"

static RTC_DS3231 rtc;
static DateTime now;
static uint8_t currentHour, currentMinute;

void setupRTC() {
	rtc.begin();

	if (rtc.lostPower()) {
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	}

	now = rtc.now();
}

void checkTime() {
	now = rtc.now();

	uint8_t rtcHour = now.hour();
	uint8_t rtcMinute = now.minute();

	if (currentHour != rtcHour || currentMinute != rtcMinute) {
		currentHour = rtcHour;
		currentMinute = rtcMinute;

		refreshDisplay();
	}
}

void updateRtc() {
	rtc.adjust(DateTime(now.year(), now.month(), now.day(), currentHour, currentMinute, 0));

	checkTime();
}

void refreshDisplay() {
	displayCurrentTime(currentHour, currentMinute);
}

void setHours(int8_t hourOffset) {
	currentHour += hourOffset;

	if (currentHour == 24) {
		currentHour = 0;
	} else if (currentHour == 255) {
		currentHour = 23;
	}

	updateRtc();
	refreshDisplay();
}

void setMinutes(int8_t minuteOffset) {
	currentMinute += minuteOffset;

	if (currentMinute == 60) {
		currentMinute = 0;
	} else if (currentMinute == 255) {
		currentMinute = 59;
	}

	updateRtc();
	refreshDisplay();
}