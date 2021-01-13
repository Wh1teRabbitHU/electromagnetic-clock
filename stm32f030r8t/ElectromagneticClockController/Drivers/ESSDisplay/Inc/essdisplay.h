#ifndef ESSDISPLAY_INC_ESSDISPLAY_H_
#define ESSDISPLAY_INC_ESSDISPLAY_H_

#include <stdint.h>
#include "stm32f0xx_hal.h"

#define LOW				0
#define HIGH 			1
#define MAX_VALUE       9999
#define DIGIT_COUNT     4
#define SEGMENT_COUNT   7

typedef struct ESSDisplay_GPIO_t {
	GPIO_TypeDef*	port;
	uint16_t		pin;
} ESSDisplay_GPIO_t;

typedef struct ESSDisplay_conf_t {
	ESSDisplay_GPIO_t*	digitSel0_GPIO;
	ESSDisplay_GPIO_t*	digitSel1_GPIO;
	ESSDisplay_GPIO_t*	pwrEn_GPIO;
	ESSDisplay_GPIO_t*	ctrlEn_GPIO;
	ESSDisplay_GPIO_t*	clockVal_GPIO;
	ESSDisplay_GPIO_t*	segSel0_GPIO;
	ESSDisplay_GPIO_t*	segSel1_GPIO;
	ESSDisplay_GPIO_t*	segSel2_GPIO;
} ESSDisplay_conf_t;

void ESSDisplay_displayDigit(uint8_t digit, uint8_t value);
void ESSDisplay_displayNumber(uint16_t number);
void ESSDisplay_powerOn();
void ESSDisplay_powerOff();

void ESSDisplay_init(ESSDisplay_conf_t * essdisplay_conf);

#endif
