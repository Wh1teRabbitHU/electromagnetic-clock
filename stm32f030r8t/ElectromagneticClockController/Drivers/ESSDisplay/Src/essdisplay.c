#include "essdisplay.h"

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

static ESSDisplay_conf_t conf;

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

	HAL_GPIO_WritePin(&conf.digitSel0_GPIO_port, conf.digitSel0_GPIO_pin, digitSelect0);
	HAL_GPIO_WritePin(&conf.digitSel1_GPIO_port, conf.digitSel1_GPIO_pin, digitSelect1);

	for (uint8_t segmentIndex = 0; segmentIndex < SEGMENT_COUNT; segmentIndex++) {
		uint8_t segmentSelect0 = ESSDisplay_getValueFromBinary(segmentIndex, 0);
		uint8_t segmentSelect1 = ESSDisplay_getValueFromBinary(segmentIndex, 1);
		uint8_t segmentSelect2 = ESSDisplay_getValueFromBinary(segmentIndex, 2);
		uint8_t segmentEnabled = ESSDisplay_getValueFromBinary(segmentValues[value], segmentIndex);
		uint8_t clockValue = ESSDisplay_getClockValue(digit, segmentEnabled);

		HAL_GPIO_WritePin(&conf.segSel0_GPIO_port, conf.segSel0_GPIO_pin, segmentSelect0);
		HAL_GPIO_WritePin(&conf.segSel1_GPIO_port, conf.segSel1_GPIO_pin, segmentSelect1);
		HAL_GPIO_WritePin(&conf.segSel2_GPIO_port, conf.segSel2_GPIO_pin, segmentSelect2);
		HAL_GPIO_WritePin(&conf.clockVal_GPIO_port, conf.clockVal_GPIO_pin, clockValue);
		HAL_GPIO_WritePin(&conf.ctrlEn_GPIO_port, conf.ctrlEn_GPIO_pin, HIGH);
		HAL_Delay(1);
		HAL_GPIO_WritePin(&conf.ctrlEn_GPIO_port, conf.ctrlEn_GPIO_pin, LOW);
		HAL_Delay(1);
	}
}

void ESSDisplay_displayNumber(uint16_t number) {
	for (uint8_t digit = 0; digit < DIGIT_COUNT; digit++) {
		uint8_t digitValue = ESSDisplay_getDigitValue(digit, number);

		ESSDisplay_displayDigit(DIGIT_COUNT - digit - 1, digitValue);

		HAL_Delay(10);
	}
}

void ESSDisplay_displayTime(uint8_t hours, uint8_t minutes) {
	ESSDisplay_displayDigit(3, hours / 10);
	ESSDisplay_displayDigit(2, hours % 10);
	ESSDisplay_displayDigit(1, minutes / 10);
	ESSDisplay_displayDigit(0, minutes % 10);
}

void ESSDisplay_powerOn() {
	HAL_GPIO_WritePin(&conf.pwrEn_GPIO_port, conf.pwrEn_GPIO_pin, HIGH);
}

void ESSDisplay_powerOff() {
	HAL_GPIO_WritePin(&conf.pwrEn_GPIO_port, conf.pwrEn_GPIO_pin, LOW);
}

void ESSDisplay_init(ESSDisplay_conf_t * essdisplay_conf) {
	conf = *essdisplay_conf;

	HAL_GPIO_WritePin(&conf.digitSel0_GPIO_port, conf.digitSel0_GPIO_pin, LOW);
	HAL_GPIO_WritePin(&conf.digitSel1_GPIO_port, conf.digitSel1_GPIO_pin, LOW);
	HAL_GPIO_WritePin(&conf.ctrlEn_GPIO_port, conf.ctrlEn_GPIO_pin, LOW);
	HAL_GPIO_WritePin(&conf.clockVal_GPIO_port, conf.clockVal_GPIO_pin, LOW);
	HAL_GPIO_WritePin(&conf.segSel0_GPIO_port, conf.segSel0_GPIO_pin, LOW);
	HAL_GPIO_WritePin(&conf.segSel1_GPIO_port, conf.segSel1_GPIO_pin, LOW);
	HAL_GPIO_WritePin(&conf.segSel2_GPIO_port, conf.segSel2_GPIO_pin, LOW);
}
