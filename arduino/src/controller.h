#ifndef CONTROLLER_H
#define CONTROLLER_H

enum editState_t {
	NO_EDIT,
	EDIT_HOURS,
	EDIT_MINUTES
};

#include "Arduino.h"
#include "display-handler.h"
#include "rtc-handler.h"

#define DIGIT_SEL_0_PIN 5
#define DIGIT_SEL_1_PIN 6
#define PWR_EN_PIN      7
#define CTRL_EN_PIN     8
#define CLOCK_VAL_PIN   3
#define SEG_SEL_0_PIN   2
#define SEG_SEL_1_PIN   10
#define SEG_SEL_2_PIN   9

#define PREV_BTN_PIN    A1
#define SEL_BTN_PIN    	A2
#define NEXT_BTN_PIN    A3
#define STATUS_LED_PIN	13

#define RTC_INT			A7
#define RTC_RST			A0

void initGPIO();
void checkButtons();
void prevPressed();
void selectPressed();
void nextPressed();

#endif