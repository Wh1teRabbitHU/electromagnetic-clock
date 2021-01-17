#include "essdisplay.h"
#include "main.h"

static const uint8_t digitEnabledStates[4] = {
	LOW,  // 1. Digit's enable state
	LOW,  // 2. Digit's enable state
	LOW,  // 3. Digit's enable state
	HIGH   // 4. Digit's enable state
};

// Segment positions
//  333
// 4   2
// 4   2
//  000
// 5   1
// 5   1
//  666

static const uint8_t segmentValues[10] = {
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

uint8_t ESSDisplay_getDigitValue(uint8_t digit, uint16_t number) {
	while (digit-- > 0) {
		number /= 10;
	}

	return number % 10;
}

uint8_t ESSDisplay_getValueFromBinary(uint8_t binary, uint8_t pos) {
	return ((binary >> pos) & 1) == 1 ? 1 : 0;
}

uint8_t ESSDisplay_getClockValue(uint8_t digit, uint8_t segmentEnabled) {
	uint8_t digitEnabledState = digitEnabledStates[digit];

	if (segmentEnabled == 1) {
		return digitEnabledState;
	}

	return digitEnabledState == HIGH ? LOW : HIGH;
}

void ESSDisplay_displayDigit(uint8_t digit, uint8_t value) {
	uint8_t digitSelect0 = ESSDisplay_getValueFromBinary(digit, 0);
	uint8_t digitSelect1 = ESSDisplay_getValueFromBinary(digit, 1);

	HAL_GPIO_WritePin(DIGIT_0_GPIO_Port, DIGIT_0_Pin, digitSelect0);
	HAL_GPIO_WritePin(DIGIT_1_GPIO_Port, DIGIT_1_Pin, digitSelect1);

	for (uint8_t segmentIndex = 0; segmentIndex < SEGMENT_COUNT; segmentIndex++) {
		uint8_t segmentSelect0 = ESSDisplay_getValueFromBinary(segmentIndex, 0);
		uint8_t segmentSelect1 = ESSDisplay_getValueFromBinary(segmentIndex, 1);
		uint8_t segmentSelect2 = ESSDisplay_getValueFromBinary(segmentIndex, 2);
		uint8_t segmentEnabled = ESSDisplay_getValueFromBinary(segmentValues[value], segmentIndex);
		uint8_t clockValue = ESSDisplay_getClockValue(digit, segmentEnabled);

		HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, segmentSelect0);
		HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, segmentSelect1);
		HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, segmentSelect2);
		HAL_GPIO_WritePin(DISPLAY_VAL_GPIO_Port, DISPLAY_VAL_Pin, clockValue);
		HAL_GPIO_WritePin(CTRL_EN_GPIO_Port, CTRL_EN_Pin, HIGH);
		HAL_Delay(1);
		HAL_GPIO_WritePin(CTRL_EN_GPIO_Port, CTRL_EN_Pin, LOW);
		HAL_Delay(1);
	}
}

void ESSDisplay_displayNumber(uint16_t number) {
	ESSDisplay_powerOn();

	for (uint8_t digit = 0; digit < DIGIT_COUNT; digit++) {
		uint8_t digitValue = ESSDisplay_getDigitValue(digit, number);

		ESSDisplay_displayDigit(DIGIT_COUNT - digit - 1, digitValue);

		HAL_Delay(10);
	}

	ESSDisplay_powerOff();
}

void ESSDisplay_displayTime(uint8_t hours, uint8_t minutes) {
	ESSDisplay_powerOn();

	ESSDisplay_displayDigit(3, hours / 10);
	ESSDisplay_displayDigit(2, hours % 10);
	ESSDisplay_displayDigit(1, minutes / 10);
	ESSDisplay_displayDigit(0, minutes % 10);

	ESSDisplay_powerOff();
}

void ESSDisplay_powerOn() {
	HAL_GPIO_WritePin(PWR_EN_GPIO_Port, PWR_EN_Pin, HIGH);
}

void ESSDisplay_powerOff() {
	HAL_GPIO_WritePin(PWR_EN_GPIO_Port, PWR_EN_Pin, LOW);
}

void ESSDisplay_init() {
	HAL_GPIO_WritePin(DIGIT_0_GPIO_Port, DIGIT_0_Pin, LOW);
	HAL_GPIO_WritePin(DIGIT_1_GPIO_Port, DIGIT_1_Pin, LOW);
	HAL_GPIO_WritePin(CTRL_EN_GPIO_Port, CTRL_EN_Pin, LOW);
	HAL_GPIO_WritePin(DISPLAY_VAL_GPIO_Port, DISPLAY_VAL_Pin, LOW);
	HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, LOW);
	HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, LOW);
	HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, LOW);
	HAL_GPIO_WritePin(PWR_EN_GPIO_Port, PWR_EN_Pin, LOW);
}
