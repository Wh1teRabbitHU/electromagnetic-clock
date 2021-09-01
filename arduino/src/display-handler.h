#ifndef DISPLAY_HANDLER_H
#define DISPLAY_HANDLER_H

#include "stdint.h"
#include "Arduino.h"
#include "rtc-handler.h"
#include "controller.h"

#define MAX_VALUE       9999
#define DIGIT_COUNT     4
#define SEGMENT_COUNT   7
#define SET_INTERVAL    2

const uint8_t digitEnabledStates[4] = {
	LOW,  // 1. Digit's enable state
	HIGH,  // 2. Digit's enable state
	LOW,  // 3. Digit's enable state
	LOW   // 4. Digit's enable state
};

// Segment positions
//  333
// 4   2
// 4   2
//  000
// 5   1
// 5   1
//  666

const uint8_t segmentValues[10] = {
	0b0111111,  // 0
	0b0110000,  // 1
	0b1011011,  // 2
	0b1111001,  // 3
	0b1110100,  // 4
	0b1101101,  // 5
	0b1101111,  // 6
	0b0111000,  // 7
	0b1111111,  // 8
	0b1111101   // 9
};

void displayCurrentTime(uint8_t hour, uint8_t minute);
void displayNumber(uint16_t number);
void displayEditState(editState_t currentState);

#endif