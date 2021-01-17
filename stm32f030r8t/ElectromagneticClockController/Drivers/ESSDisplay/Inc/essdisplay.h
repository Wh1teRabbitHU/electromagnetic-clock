#ifndef ESSDISPLAY_INC_ESSDISPLAY_H_
#define ESSDISPLAY_INC_ESSDISPLAY_H_

#include <stdint.h>
#include "stm32f0xx_hal.h"

#define LOW				0
#define HIGH 			1
#define MAX_VALUE       9999
#define DIGIT_COUNT     4
#define SEGMENT_COUNT   7

void ESSDisplay_displayDigit(uint8_t digit, uint8_t value);
void ESSDisplay_displayNumber(uint16_t number);
void ESSDisplay_displayTime(uint8_t hours, uint8_t minutes);
void ESSDisplay_powerOn();
void ESSDisplay_powerOff();

void ESSDisplay_init();

#endif
