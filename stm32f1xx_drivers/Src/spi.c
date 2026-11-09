/*
 * spi.c
 *
 *  Created on: 18-Aug-2026
 *      Author: abhis
 */

#include "stm32f1xx.h"
#include "string.h"
/*
*
* PB14 --> SPI2 MISO
* PB15 -- > SPI2 MOSI
* PB13 -> SPI2 SCLK
* PB12 -- > SPI2 NSS
* ALT function mode : 5
*/
 void SPI2_GPIOInits(void)
 {
	 GPIO_Handle_t SPIPins;

	 SPIPins.pGPIOx = GPIOB;
	 SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	 SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	 SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	 SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_10MHZ;


	 //SCLK
	 SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_13;
	 GPIO_Init(&SPIPins);

	 //MOSI
	 SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_15 ;
	 GPIO_Init(&SPIPins);

	 //MISO
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_14;
	 //GPIO_Init(&SPIPins);

	 //NSS
	// SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber_12;
	// GPIO_Init(&SPIPins);


 }





 void SPI2_Inits(void)
 {
 SPI_Handle_t SPI2handle;

 SPI2handle.pSPIx = SPI2;
 SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
 SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
 SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;//generates sclk of 8MHz
 SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
 SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
 SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
 SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_EN; //software slave management enabled for NSS pin

 SPI_Init(&SPI2handle);
 }




int main(void)
{

	char user_data[] = "Hello world";

	//this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	//This function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();

	// PULLING NSS PIN TO HIGH TO AVOID MODF ERROR
	SPI_SSIConfig(SPI2, ENABLE);

	SPI_PeripheralControl(SPI2,  ENABLE);

	SPI_SendData(SPI2,(uint8_t*)user_data,strlen(user_data));


	//lets confirm SPI is not busy
	while( SPI_GetFlagStatus(SPI2,SPI_BSY_FLAG) );

	SPI_PeripheralControl(SPI2,DISABLE);

	while(1);

return 0;


}



