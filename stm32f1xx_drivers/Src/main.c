/*
 * main.c
 *
 * Created on: 12-Aug-2026
 * Author: abhis
 */

#include "stm32f1xx_gpio_driver.h"


void delay(void)
{
    for(volatile uint32_t i = 0; i < 1000000; i++);
}





    int main(void)
    {
        GPIO_Handle_t GpioLed;

        /* GPIOC Pin 13 configuration */

        GpioLed.pGPIOx = GPIOC;

        GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_13;

        GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;

        GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_10MHZ;

        GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD ;

        GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


        /* Initialize GPIO */

        GPIO_Init(&GpioLed);


        /* Infinite loop */

        while(1)
        {
            GPIO_ToggleOutputPin(GPIOC, GPIO_PinNumber_13);

            delay();
        }
    }



