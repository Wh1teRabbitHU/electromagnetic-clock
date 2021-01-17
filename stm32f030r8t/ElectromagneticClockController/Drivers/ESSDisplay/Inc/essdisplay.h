#ifndef ESSDISPLAY_INC_ESSDISPLAY_H_
#define ESSDISPLAY_INC_ESSDISPLAY_H_

#include <stdint.h>
#include "stm32f0xx_hal.h"

#define LOW				0
#define HIGH 			1
#define MAX_VALUE       9999
#define DIGIT_COUNT     4
#define SEGMENT_COUNT   7

typedef struct ESSDisplay_conf_t {
	GPIO_TypeDef	digitSel0_GPIO_port;
	uint16_t		digitSel0_GPIO_pin;
	GPIO_TypeDef	digitSel1_GPIO_port;
	uint16_t		digitSel1_GPIO_pin;
	GPIO_TypeDef	pwrEn_GPIO_port;
	uint16_t		pwrEn_GPIO_pin;
	GPIO_TypeDef	ctrlEn_GPIO_port;
	uint16_t		ctrlEn_GPIO_pin;
	GPIO_TypeDef	clockVal_GPIO_port;
	uint16_t		clockVal_GPIO_pin;
	GPIO_TypeDef	segSel0_GPIO_port;
	uint16_t		segSel0_GPIO_pin;
	GPIO_TypeDef	segSel1_GPIO_port;
	uint16_t		segSel1_GPIO_pin;
	GPIO_TypeDef	segSel2_GPIO_port;
	uint16_t		segSel2_GPIO_pin;
} ESSDisplay_conf_t;

void ESSDisplay_displayDigit(uint8_t digit, uint8_t value);
void ESSDisplay_displayNumber(uint16_t number);
void ESSDisplay_displayTime(uint8_t hours, uint8_t minutes);
void ESSDisplay_powerOn();
void ESSDisplay_powerOff();

void ESSDisplay_init(ESSDisplay_conf_t * essdisplay_conf);

#endif
