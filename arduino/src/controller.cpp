#include "controller.h"

static uint8_t buttonPressed = 0;
static uint8_t lockButtons = 0;

static editState_t editState = NO_EDIT;

void initGPIO() {
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
	pinMode(STATUS_LED_PIN, OUTPUT);

	digitalWrite(CTRL_EN_PIN, LOW);
	digitalWrite(PWR_EN_PIN, HIGH);

	digitalWrite(STATUS_LED_PIN, LOW);
}

void checkButtons() {
	if (buttonPressed) {
		if (++lockButtons < 10) {
			return;
		}

		buttonPressed = 0;
		lockButtons = 0;
	}

	uint8_t prevBtnState = digitalRead(PREV_BTN_PIN);
	uint8_t selectBtnState = digitalRead(SEL_BTN_PIN);
	uint8_t nextBtnState = digitalRead(NEXT_BTN_PIN);

	if (prevBtnState || selectBtnState || nextBtnState) {
		buttonPressed = 1;
	} else {
		return;
	}

	if (prevBtnState) {
		prevPressed();
	} else if (selectBtnState) {
		selectPressed();
	} else if (nextBtnState) {
		nextPressed();
	}
}

void prevPressed() {
	switch (editState) {
		case EDIT_HOURS:
			setHours(-1);
			break;
		case EDIT_MINUTES:
			setMinutes(-1);
			break;
		default:
			break;
	}
}

void selectPressed() {
	switch (editState) {
		case NO_EDIT:
			editState = EDIT_HOURS;
			break;
		case EDIT_HOURS:
			editState = EDIT_MINUTES;
			break;
		case EDIT_MINUTES:
			editState = NO_EDIT;
			updateRtc();
			break;
		default:
			break;
	}

	displayEditState(editState);
}

void nextPressed() {
	switch (editState) {
		case EDIT_HOURS:
			setHours(1);
			break;
		case EDIT_MINUTES:
			setMinutes(1);
			break;
		default:
			break;
	}
}