#include <Arduino.h>

#define DIGIT_SEL_0_PIN 3
#define DIGIT_SEL_1_PIN 4
#define PWR_EN_PIN      5
#define CTRL_EN_PIN     6
#define CLOCK_VAL_PIN   7
#define SEG_SEL_0_PIN   8
#define SEG_SEL_1_PIN   9
#define SEG_SEL_2_PIN   10

#define MAX_VALUE       9999
#define DIGIT_COUNT     4
#define SEGMENT_COUNT   7

const uint8_t digitEnabledStates[4] = {
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
		digitalWrite(CTRL_EN_PIN, HIGH);
		delay(1);
		digitalWrite(CTRL_EN_PIN, LOW);
		delay(1);
	}
}

void displayNumber(uint16_t number) {
	Serial.print("Current value: ");

	for (uint8_t digit = 0; digit < DIGIT_COUNT; digit++) {
		uint8_t digitValue = getDigitValue(digit, number);
		Serial.print(digitValue);

		displayDigit(DIGIT_COUNT - digit - 1, digitValue);

		delay(10);
	}
}

void setup() {
	Serial.begin(9600);

	digitalWrite(DIGIT_SEL_0_PIN, LOW);
	digitalWrite(DIGIT_SEL_1_PIN, LOW);
	digitalWrite(PWR_EN_PIN, LOW);
	digitalWrite(CTRL_EN_PIN, LOW);
	digitalWrite(CLOCK_VAL_PIN, LOW);
	digitalWrite(SEG_SEL_0_PIN, LOW);
	digitalWrite(SEG_SEL_1_PIN, LOW);
	digitalWrite(SEG_SEL_2_PIN, LOW);

	pinMode(DIGIT_SEL_0_PIN, OUTPUT);
	pinMode(DIGIT_SEL_1_PIN, OUTPUT);
	pinMode(PWR_EN_PIN, OUTPUT);
	pinMode(CTRL_EN_PIN, OUTPUT);
	pinMode(CLOCK_VAL_PIN, OUTPUT);
	pinMode(SEG_SEL_0_PIN, OUTPUT);
	pinMode(SEG_SEL_1_PIN, OUTPUT);
	pinMode(SEG_SEL_2_PIN, OUTPUT);

	digitalWrite(CTRL_EN_PIN, HIGH);
}

uint16_t currentValue = 0;

void loop() {
	if (currentValue == MAX_VALUE) {
		currentValue = 0;
	}

	digitalWrite(PWR_EN_PIN, HIGH);
	displayNumber(currentValue++);
	digitalWrite(PWR_EN_PIN, LOW);

	delay(1000);
}