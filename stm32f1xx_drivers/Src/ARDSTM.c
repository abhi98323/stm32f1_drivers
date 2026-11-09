/*
 * ARDSTM.C
 *
 * Created on: 19-Aug-2026
 * Author: abhis
 */

#include "stm32f1xx.h"
#include "string.h"

#define BTNPRESSED 0


void blinkLED(int times)
{
    for(int i = 0; i < times; i++)
    {
        GPIO_ToggleOutputPin(GPIOC, GPIO_PinNumber_13);
        for(volatile uint32_t d = 0; d < 300000; d++);
        GPIO_ToggleOutputPin(GPIOC, GPIO_PinNumber_13);
        for(volatile uint32_t d = 0; d < 300000; d++);
    }
}

/*
 * PB14 --> SPI2 MISO
 * PB15 -- > SPI2 MOSI
 * PB13 -> SPI2 SCLK
 * PB12 -- > SPI2 NSS
 */
void SPI2_GPIOInits(void)
{
    GPIO_Handle_t SPIPins;

    SPIPins.pGPIOx = GPIOB;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;      // Configured as Alternate Function for STM32F1
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;    // Push-Pull output type
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;  // No internal Pull-up/down needed for SPI outputs
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_10MHZ;    // 10MHz speed setting


    // SCLK (PB13)
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_13;
    GPIO_Init(&SPIPins);

    // MOSI (PB15)
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_15;
    GPIO_Init(&SPIPins);


    // SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_14;
    // SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    // GPIO_Init(&SPIPins);

    // NSS (PB12)
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_12;
    GPIO_Init(&SPIPins);
}

void SPI2_Inits(void)
{
    SPI_Handle_t SPI2handle;

    SPI2handle.pSPIx = SPI2;
    SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32; // Generates sclk of 8MHz
    SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
    SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI; // Software slave management enabled for NSS pin

    SPI_Init(&SPI2handle);
}

void GPIO_ButtonInit(void)
{
    GPIO_Handle_t GPIOBtn;

    GPIOBtn.pGPIOx = GPIOA;
    GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_8;
    GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;           // Input Mode
    GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_10MHZ;       // Speed setting ignored by driver for inputs
    GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;      // Active Internal Pull-Up Resistor

    GPIO_Init(&GPIOBtn);
}

void delay(void)
{
    for(volatile uint32_t i = 0; i < 500000/2; i++);
}

int main(void)
{


    char user_data[] = " Arduino Uno board is best suited for beginners who have just started using microcontrollers, on the other hand, Arduino Mega board is for enthusiasts who require a lot of I/O pins for their projects";


    // Initialize PA8 pin as Button input
    GPIO_ButtonInit();

    // Initialize the GPIO pins to behave as SPI2 pins
    SPI2_GPIOInits();

    // Initialize the SPI2 peripheral parameters
    SPI2_Inits();


    /*
     * making SSOE 1 does NSS output enable.
     * The NSS pin is automatically managed by the hardware.
     * i.e when SPE=1 , NSS will be pulled to low
     * and NSS pin will be high when SPE=0
     */
    SPI_SSOEConfig(SPI2, ENABLE);

    while(1)
    {
        // 1. Wait till button is pressed (PA8 goes LOW)
        while( GPIO_ReadFromInputPin(GPIOA, GPIO_PinNumber_8) != BTNPRESSED );

        // Software debouncing delay
        delay();

        // Enable SPI2 peripheral for data transmission
        SPI_PeripheralControl(SPI2, ENABLE);

        // First send length information
        uint8_t dataLen = strlen(user_data);
        SPI_SendData(SPI2, &dataLen, 1);

        // Send string data contents
        SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data));

        // Confirm SPI shift registers and buffers are completely clear
        while( SPI_GetFlagStatus(SPI2, SPI_BSY_FLAG) );

        blinkLED(3);
        // Disable SPI2 peripheral to release communication line
        SPI_PeripheralControl(SPI2, DISABLE);


    }
    return 0;
}
