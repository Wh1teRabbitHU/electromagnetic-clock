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

static ESSDisplay_conf_t* conf;

void ESSDisplay_writeGPIO(ESSDisplay_GPIO_t * gpio, uint8_t state) {

}

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

	ESSDisplay_writeGPIO(conf->digitSel0_GPIO, digitSelect0);
	ESSDisplay_writeGPIO(conf->digitSel1_GPIO, digitSelect1);

	for (uint8_t segmentIndex = 0; segmentIndex < SEGMENT_COUNT; segmentIndex++) {
		uint8_t segmentSelect0 = ESSDisplay_getValueFromBinary(segmentIndex, 0);
		uint8_t segmentSelect1 = ESSDisplay_getValueFromBinary(segmentIndex, 1);
		uint8_t segmentSelect2 = ESSDisplay_getValueFromBinary(segmentIndex, 2);
		uint8_t segmentEnabled = ESSDisplay_getValueFromBinary(segmentValues[value], segmentIndex);
		uint8_t clockValue = ESSDisplay_getClockValue(digit, segmentEnabled);

		ESSDisplay_writeGPIO(conf->segSel0_GPIO, segmentSelect0);
		ESSDisplay_writeGPIO(conf->segSel1_GPIO, segmentSelect1);
		ESSDisplay_writeGPIO(conf->segSel2_GPIO, segmentSelect2);
		ESSDisplay_writeGPIO(conf->clockVal_GPIO, clockValue);
		ESSDisplay_writeGPIO(conf->ctrlEn_GPIO, HIGH);
		HAL_Delay(1);
		ESSDisplay_writeGPIO(conf->ctrlEn_GPIO, LOW);
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

void ESSDisplay_powerOn() {
	ESSDisplay_writeGPIO(conf->pwrEn_GPIO, HIGH);
}

void ESSDisplay_powerOff() {
	ESSDisplay_writeGPIO(conf->pwrEn_GPIO, LOW);
}

void ESSDisplay_init(ESSDisplay_conf_t * essdisplay_conf) {
	conf = essdisplay_conf;

	ESSDisplay_writeGPIO(conf->digitSel0_GPIO, LOW);
	ESSDisplay_writeGPIO(conf->digitSel1_GPIO, LOW);
	ESSDisplay_writeGPIO(conf->pwrEn_GPIO, LOW);
	ESSDisplay_writeGPIO(conf->ctrlEn_GPIO, LOW);
	ESSDisplay_writeGPIO(conf->clockVal_GPIO, LOW);
	ESSDisplay_writeGPIO(conf->segSel0_GPIO, LOW);
	ESSDisplay_writeGPIO(conf->segSel1_GPIO, LOW);
	ESSDisplay_writeGPIO(conf->segSel2_GPIO, LOW);

	ESSDisplay_writeGPIO(conf->ctrlEn_GPIO, HIGH);
}
