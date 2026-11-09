
/*
 * toggle.c
 *
 *  Created on: 15-Aug-2026
 *      Author: abhis
 */









#include "stm32f1xx_gpio_driver.h"

#define LOW 0
#define BTN_PRESSED LOW

void delay(void)
{
    for(volatile uint32_t i = 0; i < 500000/2; i++);
}

int main(void)
{
    GPIO_Handle_t GpioLed;
    GPIO_Handle_t GPIOBtn;


    GpioLed.pGPIOx = GPIOA;

    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_12;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_10MHZ;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GpioLed);



    GPIOBtn.pGPIOx = GPIOA;

    GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_8;
    GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_10MHZ;
    GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

    GPIO_Init(&GPIOBtn);



    while(1)
    {

    if(GPIO_ReadFromInputPin(GPIOA,GPIO_PinNumber_8) == BTN_PRESSED)
    {

    delay();
    GPIO_ToggleOutputPin(GPIOA,GPIO_PinNumber_12);

}
}
    return 0;
}
