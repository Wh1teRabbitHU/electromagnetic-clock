/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DCF77_SIGNAL_Pin GPIO_PIN_3
#define DCF77_SIGNAL_GPIO_Port GPIOA
#define DCF77_SIGNAL_EXTI_IRQn EXTI2_3_IRQn
#define DIGIT_0_Pin GPIO_PIN_7
#define DIGIT_0_GPIO_Port GPIOC
#define DIGIT_1_Pin GPIO_PIN_8
#define DIGIT_1_GPIO_Port GPIOC
#define PWR_EN_Pin GPIO_PIN_9
#define PWR_EN_GPIO_Port GPIOC
#define CTRL_EN_Pin GPIO_PIN_8
#define CTRL_EN_GPIO_Port GPIOA
#define DISPLAY_VAL_Pin GPIO_PIN_9
#define DISPLAY_VAL_GPIO_Port GPIOA
#define SEG_0_Pin GPIO_PIN_10
#define SEG_0_GPIO_Port GPIOA
#define SEG_1_Pin GPIO_PIN_11
#define SEG_1_GPIO_Port GPIOA
#define SEG_2_Pin GPIO_PIN_12
#define SEG_2_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
