#include <Arduino.h>

#include "controller.h"
#include "display-handler.h"
#include "rtc-handler.h"

uint16_t loopCounter = 0;

void setup() {
	setupRTC();
	initGPIO();

	delay(5000);
}

void loop() {
	if (loopCounter % 50 == 0) {
		checkButtons();
	}

	if (loopCounter % 100 == 0) {
		checkTime();
	}

	loopCounter++;

	delay(1);
}