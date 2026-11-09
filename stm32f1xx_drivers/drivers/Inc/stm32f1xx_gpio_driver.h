/*
 * stm32f1xx_gpio_driver.h
 *
 *  Created on: 10-Aug-2026
 *      Author: abhis
 */

#ifndef INC_STM32F1XX_GPIO_DRIVER_H_
#define INC_STM32F1XX_GPIO_DRIVER_H_

#include "stm32f1xx.h"

/*
 * Configuration structure for an STM32F1 GPIO pin
 */
typedef struct
{
    uint8_t GPIO_PinNumber;      /* Pin numbers from @GPIO_PIN_NUMBERS */
    uint8_t GPIO_PinMode;        /* Modes from @GPIO_MODES */
    uint8_t GPIO_PinSpeed;       /* Speeds from @GPIO_SPEEDS (Only valid for Output/Alt-Fn) */
    uint8_t GPIO_PinOPType;      /* Output Types from @GPIO_OP_TYPES */
    uint8_t GPIO_PinPuPdControl; /* Pull-up/Pull-down from @GPIO_PUPD_MODES */
} GPIO_PinConfig_t;

/*
 * Handle structure for an STM32F1 GPIO pin
 */
typedef struct
{
    GPIO_RegDef_t *pGPIOx;       /* Holds base address of the GPIO port */
    GPIO_PinConfig_t GPIO_PinConfig; /* Holds GPIO pin configuration settings */
} GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBERS
 * GPIO pin number macros
 */
#define GPIO_PinNumber_0        0
#define GPIO_PinNumber_1        1
#define GPIO_PinNumber_2        2
#define GPIO_PinNumber_3        3
#define GPIO_PinNumber_4        4
#define GPIO_PinNumber_5        5
#define GPIO_PinNumber_6        6
#define GPIO_PinNumber_7        7
#define GPIO_PinNumber_8        8
#define GPIO_PinNumber_9        9
#define GPIO_PinNumber_10       10
#define GPIO_PinNumber_11       11
#define GPIO_PinNumber_12       12
#define GPIO_PinNumber_13       13
#define GPIO_PinNumber_14       14
#define GPIO_PinNumber_15       15

/*
 * @GPIO_MODES
 * STM32F1 Pin Modes
 */
#define GPIO_MODE_IN            0   /* Digital Input Mode */
#define GPIO_MODE_OUT           1   /* General Purpose Output Mode */
#define GPIO_MODE_ALTFN         2   /* Alternate Function Mode (No multiplexer code needed for F1) */
#define GPIO_MODE_ANALOG        3   /* Analog Mode */
#define GPIO_MODE_IT_FT         4   /* Interrupt Falling Edge */
#define GPIO_MODE_IT_RT         5   /* Interrupt Rising Edge */
#define GPIO_MODE_IT_RFT        6   /* Interrupt Rising/Falling Edge */

/*
 * @GPIO_SPEEDS
 * STM32F1 Output Max Frequency Selection
 */
#define GPIO_SPEED_10MHZ        1   /* Output mode, max speed 10 MHz */
#define GPIO_SPEED_2MHZ         2   /* Output mode, max speed 2 MHz */
#define GPIO_SPEED_50MHZ        3   /* Output mode, max speed 50 MHz */

/*
 * @GPIO_OP_TYPES
 * STM32F1 Output Configurations
 */
#define GPIO_OP_TYPE_PP         0   /* Push-Pull */
#define GPIO_OP_TYPE_OD         1   /* Open-Drain */

/*
 * @GPIO_PUPD_MODES
 * STM32F1 Pull-up / Pull-down Selection (Applied when GPIO_MODE_IN is selected)
 */
#define GPIO_NO_PUPD            0   /* Floating Input */
#define GPIO_PIN_PU             1   /* Internal Pull-Up */
#define GPIO_PIN_PD             2   /* Internal Pull-Down */


/******************************************************************************************
 *                               APIs supported by this driver
 ******************************************************************************************/

// Peripheral Clock setup
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

// Init and De-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// Read and Write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

// IRQ Configuration and ISR handling
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32F1XX_GPIO_DRIVER_H_ */
