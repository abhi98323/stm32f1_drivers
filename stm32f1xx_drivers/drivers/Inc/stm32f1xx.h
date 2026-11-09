/*
 * stm32f1xx.h
 *
 * Created on: 09-Aug-2026
 * Author: abhis
 */

#ifndef INC_STM32F1XX_H_
#define INC_STM32F1XX_H_

#include<stddef.h>
#include<stdint.h>

#define _vo volatile
#define __weak __attribute__((weak))

/* ARM Cortex Mx Processor NVIC ISERx register Addresses
*/


#define NVIC_ISER0      ((_vo uint32_t*)0xE000E100 )
#define NVIC_ISER1		((_vo uint32_t*)0xE000E104 )
#define NVIC_ISER2		((_vo uint32_t*)0xE000E108 )
#define NVIC_ISER3		((_vo uint32_t*)0xE000E10c )



/*ARM Cortex Mx Processor NVIC ICERx register Addresses*/


#define NVIC_ICER0		((_vo uint32_t*)0XE000E180)
#define NVIC_ICER1		((_vo uint32_t*)0XE000E184)
#define NVIC_ICER2		((_vo uint32_t*)0XE000E188)
#define NVIC_ICER3		((_vo uint32_t*)0XE000E18C)


/*
* ARM Cortex Mx Processor Priority Register Address Calculation
*/
#define NVIC_PR_BASE_ADDR ((_vo uint32_t*)0xE000E400)


/*
* ARM Cortex Mx Processor Priority Register Address Calculation
*/
/*
* ARM Cortex Mx Processor number of priority bits implemented in Priority Register*/

#define NO_PR_BITS_IMPLEMENTED 4



/* SRAM AND ROM BASE ADDRESSES */

#define FLASH_BASEADDR           0x08000000U
#define SRAM1_BASEADDR           0x20000000U
#define SRAM                     SRAM1_BASEADDR
#define ROM                      0x1FFFF000U

/* AHB AND APB BASE ADDRESSES */
#define PERIPH_BASEADDR          0x40000000U
#define APB1PERIPH_BASEADDR      PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR      0x40010000U
#define AHBPERIPH_BASEADDR       0x40018000U


/* RCC BASE ADDRESS */
#define RCC_BASEADDR             0x40021000U // Absolute base for STM32F1 RCC

/* BASE ADDRESSES OF PERIPHERALS ON APB1 */
#define SPI2_BASEADDR            (APB1PERIPH_BASEADDR + 0x3800U)
#define SPI3_BASEADDR            (APB1PERIPH_BASEADDR + 0x3C00U)
#define USART2_BASEADDR          (APB1PERIPH_BASEADDR + 0x4400U)
#define USART3_BASEADDR          (APB1PERIPH_BASEADDR + 0x4800U)
#define UART4_BASEADDR           (APB1PERIPH_BASEADDR + 0x4C00U)
#define UART5_BASEADDR           (APB1PERIPH_BASEADDR + 0x5000U)
#define I2C1_BASEADDR            (APB1PERIPH_BASEADDR + 0x5400U)
#define I2C2_BASEADDR            (APB1PERIPH_BASEADDR + 0x5800U)

/* BASE ADDRESSES OF PERIPHERALS ON APB2 */
#define GPIOA_BASEADDR           (APB2PERIPH_BASEADDR + 0x0800U)
#define GPIOB_BASEADDR           (APB2PERIPH_BASEADDR + 0x0C00U)
#define GPIOC_BASEADDR           (APB2PERIPH_BASEADDR + 0x1000U)
#define GPIOD_BASEADDR           (APB2PERIPH_BASEADDR + 0x1400U)
#define GPIOE_BASEADDR           (APB2PERIPH_BASEADDR + 0x1800U)
#define GPIOF_BASEADDR           (APB2PERIPH_BASEADDR + 0x1C00U)
#define GPIOG_BASEADDR           (APB2PERIPH_BASEADDR + 0x2000U)
#define EXTI_BASEADDR            (APB2PERIPH_BASEADDR + 0x0400U)
#define SPI1_BASEADDR            (APB2PERIPH_BASEADDR + 0x3000U)
#define USART1_BASEADDR          (APB2PERIPH_BASEADDR + 0x3800U)
#define AFIO_BASEADDR            (APB2PERIPH_BASEADDR + 0x0000U)

/* GPIO REGISTER DEFINITION STRUCT */
typedef struct {
    _vo uint32_t CRL;
    _vo uint32_t CRH;
    _vo uint32_t IDR;
    _vo uint32_t ODR;
    _vo uint32_t BSRR;
    _vo uint32_t BRR;
    _vo uint32_t LCKR;
} GPIO_RegDef_t;

/* PERIPHERAL MACRO DEFINITIONS FOR GPIO */
#define GPIOA                 ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB                 ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC                 ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD                 ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE                 ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF                 ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG                 ((GPIO_RegDef_t*)GPIOG_BASEADDR)

/* RCC REGISTER DEFINITION STRUCT */
typedef struct {
    _vo uint32_t CR;
    _vo uint32_t CFGR;
    _vo uint32_t CIR;
    _vo uint32_t APB2RSTR;
    _vo uint32_t APB1RSTR;
    _vo uint32_t AHBENR;
    _vo uint32_t APB2ENR;
    _vo uint32_t APB1ENR;
    _vo uint32_t BDCR;
    _vo uint32_t CSR;
} RCC_RegDef_t;

/* PERIPHERAL MACRO DEFINITION FOR RCC */
#define RCC           ((RCC_RegDef_t*)RCC_BASEADDR)



/* EXTI REGISTER DEFINITION STRUCT */
typedef struct
{
_vo uint32_t IMR;			/* Interrupt mask register	Address offset: 0x00 */
_vo uint32_t EMR;			/* Event mask register Address offset: 0x04 */
_vo uint32_t RTSR;			/* Rising trigger selection register Address offset: 0x08 */
_vo uint32_t FTSR;			/* Falling trigger selection register Address offset: 0x0C */
_vo uint32_t SWIER;			/* Software interrupt event register Address offset: 0x10 */
_vo uint32_t PR;			/* pending register Address offset: 0x14 */

}EXTI_RegDef_t;


/* PERIPHERAL MACRO DEFINITION FOR EXTI */
#define EXTI          ((EXTI_RegDef_t*)EXTI_BASEADDR)


/* AFIO REGISTER DEFINITION STRUCT */
typedef struct
{
_vo uint32_t EVCR;				/* event control register Address offset: 0x00 */
_vo uint32_t MAPR[3];			/* AF remap and debug config. Address offset: 0x04*/
_vo uint32_t EXTICR[4];			/* external interrupt config. regAddress offset: 0x08-0x14 */
_vo uint32_t MAPR2[2];			/* AF remap and debug config. 2Address offset: 0x1C */

}AFIO_RegDef_t;

//spi register struct

typedef struct
{
	_vo uint32_t CR1;
	_vo uint32_t CR2;
	_vo uint32_t SR;
	_vo uint32_t DR;
	_vo uint32_t CRCPR;
	_vo uint32_t RXCRCR;
	_vo uint32_t TXCRCR;
	_vo uint32_t I2SCFGR;
	_vo uint32_t I2SPR;
}SPI_RegDef_t;

#define SPI1 			((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2 			((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3			((SPI_RegDef_t*)SPI3_BASEADDR)

/* PERIPHERAL MACRO DEFINITION FOR AFIO */
#define AFIO          ((AFIO_RegDef_t*)AFIO_BASEADDR)



typedef struct
{
	_vo uint32_t CR1;
	_vo uint32_t CR2;
	_vo uint32_t OAR1;
	_vo uint32_t OAR2;
	_vo uint32_t DR;
	_vo uint32_t SR1;
	_vo uint32_t SR2;
	_vo uint32_t CCR;
	_vo uint32_t TRISE;
} I2C_RegDef_t;

#define I2C1 			((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2 			((I2C_RegDef_t*)I2C2_BASEADDR)



typedef struct
{
	_vo uint32_t SR;         /*!< TODO,     										Address offset: 0x00 */
	_vo uint32_t DR;         /*!< TODO,     										Address offset: 0x04 */
	_vo uint32_t BRR;        /*!< TODO,     										Address offset: 0x08 */
	_vo uint32_t CR1;        /*!< TODO,     										Address offset: 0x0C */
	_vo uint32_t CR2;        /*!< TODO,     										Address offset: 0x10 */
	_vo uint32_t CR3;        /*!< TODO,     										Address offset: 0x14 */
	_vo uint32_t GTPR;       /*!< TODO,     										Address offset: 0x18 */
} USART_RegDef_t;


#define USART1 			((USART_RegDef_t*)USART1_BASEADDR)
#define USART2 			((USART_RegDef_t*)USART2_BASEADDR)
#define USART3			((USART_RegDef_t*)USART3_BASEADDR)
#define UART4 			((USART_RegDef_t*)UART4_BASEADDR)
#define UART5 			((USART_RegDef_t*)UART5_BASEADDR)





// ==============================================================================
// CLOCK ENABLE MACROS
// ==============================================================================

// Clock Enable Macros for GPIOx peripherals (APB2 Register)
#define GPIOA_PCLK_EN()     ( RCC->APB2ENR |= (1 << 2) )
#define GPIOB_PCLK_EN()     ( RCC->APB2ENR |= (1 << 3) )
#define GPIOC_PCLK_EN()     ( RCC->APB2ENR |= (1 << 4) )
#define GPIOD_PCLK_EN()     ( RCC->APB2ENR |= (1 << 5) )
#define GPIOE_PCLK_EN()     ( RCC->APB2ENR |= (1 << 6) )
#define GPIOF_PCLK_EN()     ( RCC->APB2ENR |= (1 << 7) )
#define GPIOG_PCLK_EN()     ( RCC->APB2ENR |= (1 << 8) )

// Clock Enable Macros for AFIO peripheral (APB2 Register)
#define AFIO_PCLK_EN()      ( RCC->APB2ENR |= (1 << 0) )

// Clock Enable Macros for SPIx peripherals
#define SPI1_PCLK_EN()      ( RCC->APB2ENR |= (1 << 12) ) // Fixed from bit 21 to 12
#define SPI2_PCLK_EN()      ( RCC->APB1ENR |= (1 << 14) )
#define SPI3_PCLK_EN()      ( RCC->APB1ENR |= (1 << 15) ) // Fixed from bit 12 to 15

// Clock Enable Macros for I2Cx peripherals (APB1 Register)
#define I2C1_PCLK_EN()      ( RCC->APB1ENR |= (1 << 21) )
#define I2C2_PCLK_EN()      ( RCC->APB1ENR |= (1 << 22) )

// Clock Enable Macros for USARTx/UARTx peripherals
#define USART1_PCLK_EN()    ( RCC->APB2ENR |= (1 << 14) )
#define USART2_PCLK_EN()    ( RCC->APB1ENR |= (1 << 17) )
#define USART3_PCLK_EN()    ( RCC->APB1ENR |= (1 << 18) )
#define UART4_PCLK_EN()     ( RCC->APB1ENR |= (1 << 19) )
#define UART5_PCLK_EN()     ( RCC->APB1ENR |= (1 << 20) )


// ==============================================================================
// CLOCK DISABLE MACROS
// ==============================================================================

// Clock DISABLE Macros for GPIO Peripherals (APB2 Register)
#define GPIOA_PCLK_DI()     ( RCC->APB2ENR &= ~(1 << 2) )
#define GPIOB_PCLK_DI()     ( RCC->APB2ENR &= ~(1 << 3) )
#define GPIOC_PCLK_DI()     ( RCC->APB2ENR &= ~(1 << 4) )
#define GPIOD_PCLK_DI()     ( RCC->APB2ENR &= ~(1 << 5) )
#define GPIOE_PCLK_DI()     ( RCC->APB2ENR &= ~(1 << 6) )
#define GPIOF_PCLK_DI()     ( RCC->APB2ENR &= ~(1 << 7) )
#define GPIOG_PCLK_DI()     ( RCC->APB2ENR &= ~(1 << 8) )

// Clock DISABLE Macros for Alternate Function I/O (APB2 Register)
#define AFIO_PCLK_DI()      ( RCC->APB2ENR &= ~(1 << 0) )

// Clock DISABLE Macros for SPI Peripherals
#define SPI1_PCLK_DI()      ( RCC->APB2ENR &= ~(1 << 12) )
#define SPI2_PCLK_DI()      ( RCC->APB1ENR &= ~(1 << 14) )
#define SPI3_PCLK_DI()      ( RCC->APB1ENR &= ~(1 << 15) )

// Clock DISABLE Macros for I2C Peripherals (APB1 Register)
#define I2C1_PCLK_DI()      ( RCC->APB1ENR &= ~(1 << 21) )
#define I2C2_PCLK_DI()      ( RCC->APB1ENR &= ~(1 << 22) )

// Clock DISABLE Macros for USART/UART Peripherals
#define USART1_PCLK_DI()    ( RCC->APB2ENR &= ~(1 << 14) )
#define USART2_PCLK_DI()    ( RCC->APB1ENR &= ~(1 << 17) )
#define USART3_PCLK_DI()    ( RCC->APB1ENR &= ~(1 << 18) )
#define UART4_PCLK_DI()     ( RCC->APB1ENR &= ~(1 << 19) )
#define UART5_PCLK_DI()     ( RCC->APB1ENR &= ~(1 << 20) )


//reset macro for gpio

#define GPIOA_REG_RESET()							do{(RCC->APB2RSTR |=(1 << 2)); (RCC->APB2RSTR &= ~(1 << 2)); }while(0)
#define GPIOB_REG_RESET()							do{(RCC->APB2RSTR |=(1 << 3)); (RCC->APB2RSTR &= ~(1 << 3)); }while(0)
#define GPIOC_REG_RESET()							do{(RCC->APB2RSTR |=(1 << 4)); (RCC->APB2RSTR &= ~(1 << 4)); }while(0)
#define GPIOD_REG_RESET()							do{(RCC->APB2RSTR |=(1 << 5)); (RCC->APB2RSTR &= ~(1 << 5)); }while(0)
#define GPIOE_REG_RESET()							do{(RCC->APB2RSTR |=(1 << 6)); (RCC->APB2RSTR &= ~(1 << 6)); }while(0)
#define GPIOF_REG_RESET()							do{(RCC->APB2RSTR |=(1 << 7)); (RCC->APB2RSTR &= ~(1 << 7)); }while(0)
#define GPIOG_REG_RESET()							do{(RCC->APB2RSTR |=(1 << 8)); (RCC->APB2RSTR &= ~(1 << 8)); }while(0)


#define SPI1_REG_RESET()							do{(RCC->APB2RSTR |=(1 << 12)); (RCC->APB2RSTR &= ~(1 << 12)); }while(0)
#define SPI2_REG_RESET()							do{(RCC->APB1RSTR |=(1 << 14)); (RCC->APB1RSTR &= ~(1 << 14)); }while(0)
#define SPI3_REG_RESET()							do{(RCC->APB1RSTR |=(1 << 15)); (RCC->APB1RSTR &= ~(1 << 15)); }while(0)



#define I2C1_REG_RESET()							do{(RCC->APB1RSTR |=(1 << 21)); (RCC->APB1RSTR &= ~(1 << 21)); }while(0)
#define I2C2_REG_RESET()							do{(RCC->APB1RSTR |=(1 << 22)); (RCC->APB1RSTR &= ~(1 << 22)); }while(0)



#define USART1_REG_RESET() 							do{(RCC->APB2RSTR |=(1 << 14)); (RCC->APB2RSTR &= ~(1 << 14)); }while(0)
#define USART2_REG_RESET() 							do{(RCC->APB1RSTR |=(1 << 17)); (RCC->APB1RSTR &= ~(1 << 17)); }while(0)
#define USART3_REG_RESET() 							do{(RCC->APB1RSTR |=(1 << 18)); (RCC->APB1RSTR &= ~(1 << 18)); }while(0)
#define UART4_REG_RESET() 							do{(RCC->APB1RSTR |=(1 << 19)); (RCC->APB1RSTR &= ~(1 << 19)); }while(0)
#define UART5_REG_RESET() 							do{(RCC->APB1RSTR |=(1 << 20)); (RCC->APB1RSTR &= ~(1 << 20)); }while(0)






/*
* This macro returns a code( between 0 to 7) for a given GPIO base address(x)
*/
#define GPIO_BASEADDR_TO_CODE(x)	( (x == GPIOA)?0:\
									(x == GPIOB) ?1:\
								    (x == GPIOC)?2:\
									(x == GPIOB) ?3:\
									(x == GPIOA) ?4:\
									(x == GPIOB)?5:\
									(x == GPIOA) ?6:\
						  			(x == GPIOB)?7:0 )



/*IRQ(Interrupt Request) Number of STM32F407x MCU
* NOTE: update these macros with valid values according to your MCU
*
*/


#define IRQ_NO_EXTIO 6
#define IRQ_NO_EXTI1 7
#define IRQ_NO_EXTI2 8
#define IRQ_NO_EXTI3 9
#define IRQ_NO_EXTI4 10
#define IRQ_NO_EXTI9_5 23
#define IRQ_NO_EXTI15_10 40
#define IRQ_NO_I2C1_EV      31
#define IRQ_NO_I2C1_ER      32
#define IRQ_NO_SPI1			35
#define IRQ_NO_SPI2         36
#define IRQ_NO_SPI3         51
#define IRQ_NO_USART1	    37
#define IRQ_NO_USART2	    38
#define IRQ_NO_USART3	    39
#define IRQ_NO_UART4	    52
#define IRQ_NO_UART5	    53



/*
 * macros for all the possible priority levels
 */
#define NVIC_IRQ_PRI0    0
#define NVIC_IRQ_PRI15    15

#define ENABLE	1
#define DISABLE 0
#define SET		ENABLE
#define RESET	DISABLE
#define GPIO_SET_PIN SET
#define GPIO_RESET_PIN RESET
#define FLAG_RESET RESET
#define FLAG_SET SET


/*Bit position definitions of SPI peripheral
*/

/* Bit position definitions SPI_CR1 */

#define SPI_CR1_CPHA	0
#define SPI_CR1_CPOL	1
#define SPI_CR1_MSTR	2
#define SPI_CR1_BR		3
#define SPI_CR1_SPE		6
#define SPI_CR1_LSBFIRST	7
#define SPI_CR1_SSI			8
#define SPI_CR1_SS			9
#define SPI_CR1_RXONLY		10
#define SPI_CR1_DFF			11
#define SPI_CR1_CRCNEXT		12
#define SPI_CR1_CRCEN		13
#define SPI_CR1_BIDIOE		14
#define SPI_CR1_BIDIMODE	15



// BIT POSTION FOR CR2 REGISTER


#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXDMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_ERRIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_TXEIE		7



/*Bit position definitions SPI_SR
*
*/
#define SPI_SR_RXNE			0
#define SPI_SR_TXE			1
#define SPI_SR_CHSIDE		2
#define SPI_SR_UDR			3
#define SPI_SR_CRCERR		4
#define SPI_SR_MODF			5
#define SPI_SR_OVR			6
#define SPI_SR_BSY			7


/******************************************************************************************
 *Bit position definitions of I2C peripheral
 ******************************************************************************************/
/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE						0
#define I2C_CR1_NOSTRETCH  				7
#define I2C_CR1_START 					8
#define I2C_CR1_STOP  				 	9
#define I2C_CR1_ACK 				 	10
#define I2C_CR1_SWRST  				 	15

/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ				 	0
#define I2C_CR2_ITERREN				 	8
#define I2C_CR2_ITEVTEN				 	9
#define I2C_CR2_ITBUFEN 			    10

/*
 * Bit position definitions I2C_OAR1
 */
#define I2C_OAR1_ADD0    				 0
#define I2C_OAR1_ADD71 				 	 1
#define I2C_OAR1_ADD98  			 	 8
#define I2C_OAR1_ADDMODE   			 	15

/*
 * Bit position definitions I2C_SR1
 */

#define I2C_SR1_SB 					 	0
#define I2C_SR1_ADDR 				 	1
#define I2C_SR1_BTF 					2
#define I2C_SR1_ADD10 					3
#define I2C_SR1_STOPF 					4
#define I2C_SR1_RXNE 					6
#define I2C_SR1_TXE 					7
#define I2C_SR1_BERR 					8
#define I2C_SR1_ARLO 					9
#define I2C_SR1_AF 					 	10
#define I2C_SR1_OVR 					11
#define I2C_SR1_TIMEOUT 				14

/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY 					1
#define I2C_SR2_TRA 					2
#define I2C_SR2_GENCALL 				4
#define I2C_SR2_DUALF 					7

/*
 * Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR 					 0
#define I2C_CCR_DUTY 					14
#define I2C_CCR_FS  				 	15


/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK					0
#define USART_CR1_RWU 					1
#define USART_CR1_RE  					2
#define USART_CR1_TE 					3
#define USART_CR1_IDLEIE 				4
#define USART_CR1_RXNEIE  				5
#define USART_CR1_TCIE					6
#define USART_CR1_TXEIE					7
#define USART_CR1_PEIE 					8
#define USART_CR1_PS 					9
#define USART_CR1_PCE 					10
#define USART_CR1_WAKE  				11
#define USART_CR1_M 					12
#define USART_CR1_UE 					13



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD   				0
#define USART_CR2_LBDL   				5
#define USART_CR2_LBDIE  				6
#define USART_CR2_LBCL   				8
#define USART_CR2_CPHA   				9
#define USART_CR2_CPOL   				10
#define USART_CR2_STOP   				12
#define USART_CR2_LINEN   				14


/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE   				0
#define USART_CR3_IREN   				1
#define USART_CR3_IRLP  				2
#define USART_CR3_HDSEL   				3
#define USART_CR3_NACK   				4
#define USART_CR3_SCEN   				5
#define USART_CR3_DMAR  				6
#define USART_CR3_DMAT   				7
#define USART_CR3_RTSE   				8
#define USART_CR3_CTSE   				9
#define USART_CR3_CTSIE   				10

/*
 * Bit position definitions USART_SR
 */

#define USART_SR_PE        				0
#define USART_SR_FE        				1
#define USART_SR_NE        				2
#define USART_SR_ORE       				3
#define USART_SR_IDLE       			4
#define USART_SR_RXNE        			5
#define USART_SR_TC        				6
#define USART_SR_TXE        			7
#define USART_SR_LBD        			8
#define USART_SR_CTS        			9


#include "stm32f1xx_gpio_driver.h"
#include "stm32f1xx_spi_driver.h"
#include "stm32f1xx_i2c_driver.h"
#include "stm32f1xx_usart_driver.h"
#include "stm32f1xx_rcc_driver.h"



#endif /* INC_STM32F1XX_H_ */
