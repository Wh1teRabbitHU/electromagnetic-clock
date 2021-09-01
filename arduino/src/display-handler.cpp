#include "display-handler.h"

static editState_t editState;

void setValue() {
	digitalWrite(CTRL_EN_PIN, HIGH);
	delay(SET_INTERVAL);
	digitalWrite(CTRL_EN_PIN, LOW);
	delay(SET_INTERVAL);
}

uint8_t getDigitValue(uint8_t digit, uint16_t number) {
	while (digit-- > 0) {
		number /= 10;
	}

	return number % 10;
}

uint8_t getValueFromBinary(uint8_t binary, uint8_t pos) {
	return ((binary >> pos) & 1) == 1 ? 1 : 0;
}

uint8_t getClockValue(uint8_t digit, uint8_t segmentEnabled) {
	uint8_t digitEnabledState = digitEnabledStates[digit];

	if (segmentEnabled == 1) {
		return digitEnabledState;
	}

	return digitEnabledState == HIGH ? LOW : HIGH;
}

void displayNothing(uint8_t digit) {
	uint8_t digitSelect0 = getValueFromBinary(digit, 0);
	uint8_t digitSelect1 = getValueFromBinary(digit, 1);

	digitalWrite(DIGIT_SEL_0_PIN, digitSelect0);
	digitalWrite(DIGIT_SEL_1_PIN, digitSelect1);

	for (uint8_t segmentIndex = 0; segmentIndex < SEGMENT_COUNT; segmentIndex++) {
		uint8_t segmentSelect0 = getValueFromBinary(segmentIndex, 0);
		uint8_t segmentSelect1 = getValueFromBinary(segmentIndex, 1);
		uint8_t segmentSelect2 = getValueFromBinary(segmentIndex, 2);

		digitalWrite(SEG_SEL_0_PIN, segmentSelect0);
		digitalWrite(SEG_SEL_1_PIN, segmentSelect1);
		digitalWrite(SEG_SEL_2_PIN, segmentSelect2);
		digitalWrite(CLOCK_VAL_PIN, getClockValue(digit, 0));

		setValue();
	}

	delay(10);
}

void displayDigit(uint8_t digit, uint8_t value) {
	uint8_t digitSelect0 = getValueFromBinary(digit, 0);
	uint8_t digitSelect1 = getValueFromBinary(digit, 1);

	digitalWrite(DIGIT_SEL_0_PIN, digitSelect0);
	digitalWrite(DIGIT_SEL_1_PIN, digitSelect1);

	for (uint8_t segmentIndex = 0; segmentIndex < SEGMENT_COUNT; segmentIndex++) {
		uint8_t segmentSelect0 = getValueFromBinary(segmentIndex, 0);
		uint8_t segmentSelect1 = getValueFromBinary(segmentIndex, 1);
		uint8_t segmentSelect2 = getValueFromBinary(segmentIndex, 2);
		uint8_t segmentEnabled = getValueFromBinary(segmentValues[value], segmentIndex);

		digitalWrite(SEG_SEL_0_PIN, segmentSelect0);
		digitalWrite(SEG_SEL_1_PIN, segmentSelect1);
		digitalWrite(SEG_SEL_2_PIN, segmentSelect2);
		digitalWrite(CLOCK_VAL_PIN, getClockValue(digit, segmentEnabled));

		setValue();
	}

	delay(10);
}

void displayNumber(uint16_t number) {
	for (uint8_t digit = 0; digit < DIGIT_COUNT; digit++) {
		uint8_t digitValue = getDigitValue(digit, number);

		displayDigit(DIGIT_COUNT - digit - 1, digitValue);
	}
}

void displayCurrentTime(uint8_t hour, uint8_t minute) {
	uint8_t hourDigit0 = getDigitValue(0, hour);
	uint8_t hourDigit1 = getDigitValue(1, hour);
	uint8_t minuteDigit0 = getDigitValue(0, minute);
	uint8_t minuteDigit1 = getDigitValue(1, minute);

	if (editState == NO_EDIT) {
		displayDigit(0, hourDigit1);
		displayDigit(1, hourDigit0);
		displayDigit(2, minuteDigit1);
		displayDigit(3, minuteDigit0);
	} else if (editState == EDIT_HOURS) {
		displayDigit(0, hourDigit1);
		displayDigit(1, hourDigit0);
		displayNothing(2);
		displayNothing(3);
	} else if (editState == EDIT_MINUTES) {
		displayNothing(0);
		displayNothing(1);
		displayDigit(2, minuteDigit1);
		displayDigit(3, minuteDigit0);
	}
}

void displayEditState(editState_t currentState) {
	editState = currentState;

	refreshDisplay();
}