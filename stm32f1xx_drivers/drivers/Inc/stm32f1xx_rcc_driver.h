/*
 * stm32f1xx_rcc_driver.h
 *
 *  Created on: 31-Aug-2026
 *      Author: abhis
 */

#ifndef INC_STM32F1XX_RCC_DRIVER_H_
#define INC_STM32F1XX_RCC_DRIVER_H_

#include "stm32f1xx.h"

//This returns the APB1 clock value
uint32_t RCC_GetPCLK1Value(void);

//This returns the APB2 clock value
uint32_t RCC_GetPCLK2Value(void);







#endif /* INC_STM32F1XX_RCC_DRIVER_H_ */
