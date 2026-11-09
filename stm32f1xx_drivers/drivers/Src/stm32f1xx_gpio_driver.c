/*
 * stm32f1xx_gpio_driver.c
 *
 * Created on: 10-Aug-2026
 * Author: abhis
 */

#include "stm32f1xx_gpio_driver.h"


/*
 * Peripheral Clock setup
 * */


/*
 * @fn         - GPIO_PeriClockControl
 *
 * @brief      - This function enables or disables peripheral
 *              clock for the given GPIO port.
 *
 * @param[in]  - Base address of the GPIO peripheral
 * @param[in]  - ENABLE or DISABLE
 *
 * @return     - none
 *
 * @note       - none
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }

        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }

        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }

        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }

        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }

        else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }

        else if(pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }
    }

    else
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }

        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }

        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI();
        }

        else  if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI();
        }

        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_DI();
        }

        else  if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_DI();
        }

        else if(pGPIOx == GPIOG)
        {
            GPIOG_PCLK_DI();
        }
    }
}


/*
 * GPIO Init
 * */


/*
 * @fn         - GPIO_Init
 *
 * @brief      - This function initializes the given GPIO
 *              port and pin.
 *
 * @param[in]  - Handle structure
 *
 * @return     - none
 *
 * @note       - none
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;

    uint8_t pin =
        pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;

    uint8_t position = 0;

    /* Enable GPIO peripheral clock */

       GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);
    /*
     * 1. Configure GPIO pin
     *  */

    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {

        /*
         * STM32F103 GPIO configuration:
         *
         * Pin 0 - 7  -> CRL
         * Pin 8 - 15 -> CRH
         *
         * Each pin uses 4 bits:
         *
         * CNF1 CNF0 MODE1 MODE0
         */


        /* Find position of pin */

        if(pin <= 7)
        {
            position = pin * 4;
        }
        else
        {
            position = (pin - 8) * 4;
        }


        /* Clear previous configuration */

        if(pin <= 7)
        {
            pGPIOHandle->pGPIOx->CRL &= ~(0xFU << position);
        }
        else
        {
            pGPIOHandle->pGPIOx->CRH &= ~(0xFU << position);
        }


        temp = 0;


        /*
         * 2. Configure MODE / SPEED
         **/

        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_OUT ||
           pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
        {
            /*
             * STM32F103 MODE bits:
             *
             * 01 -> Output 10 MHz
             * 10 -> Output 2 MHz
             * 11 -> Output 50 MHz
             */

            if(pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed
                    == GPIO_SPEED_10MHZ)
            {
                temp |= 0x1U;
            }

            else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed
                    == GPIO_SPEED_2MHZ)
            {
                temp |= 0x2U;
            }

            else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed
                    == GPIO_SPEED_50MHZ)
            {
                temp |= 0x3U;
            }
        }


        /*
         * 3. Configure INPUT
         *  */

        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IN)
        {
            /*
             * MODE = 00
             *
             * CNF:
             *
             * 01 -> Floating input
             * 10 -> Pull-up / Pull-down
             */

            if(pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl
                    == GPIO_NO_PUPD)
            {
                /* Floating input */

                temp |= (0x1U << 2);
            }

            else
            {
                /* Pull-up / Pull-down */

                temp |= (0x2U << 2);


                /*
                 * STM32F103 uses ODR to select
                 * pull-up or pull-down.
                 */

                if(pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl
                        == GPIO_PIN_PU)
                {
                    pGPIOHandle->pGPIOx->ODR |= (1U << pin);
                }

                else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl
                        == GPIO_PIN_PD)
                {
                    pGPIOHandle->pGPIOx->ODR &= ~(1U << pin);
                }
            }
        }


        /*
         * 4. Configure ANALOG INPUT
         * */

        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode
                == GPIO_MODE_ANALOG)
        {
            /*
             * MODE = 00
             * CNF  = 00
             *
             * 0000 = Analog input
             */

            temp = 0;
        }


        /*
         * 5. Configure OUTPUT
         *  */

        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode
                == GPIO_MODE_OUT)
        {
            /*
             * MODE already configured above.
             *
             * CNF:
             *
             * 00 -> General purpose push-pull
             * 01 -> General purpose open-drain
             */

            if(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType
                    == GPIO_OP_TYPE_PP)
            {
                temp |= (0x0U << 2);
            }

            else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType
                    == GPIO_OP_TYPE_OD)
            {
                temp |= (0x1U << 2);
            }
        }


        /*
         * 6. Configure ALTERNATE FUNCTION
         * */

        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode
                == GPIO_MODE_ALTFN)
        {
            /*
             * MODE already configured above.
             *
             * CNF:
             *
             * 10 -> Alternate function push-pull
             * 11 -> Alternate function open-drain
             */

            if(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType
                    == GPIO_OP_TYPE_PP)
            {
                temp |= (0x2U << 2);
            }

            else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType
                    == GPIO_OP_TYPE_OD)
            {
                temp |= (0x3U << 2);
            }
        }


        /*
         * 7. Write configuration into CRL / CRH
         *  */

        if(pin <= 7)
        {
            pGPIOHandle->pGPIOx->CRL |=
                    (temp << position);
        }

        else
        {
            pGPIOHandle->pGPIOx->CRH |=
                    (temp << position);
        }
    }


    /*
     * INTERRUPT MODE
     *  */

    else
    {
        /*
         * Interrupt configuration will be implemented later.
         *
         * GPIO_MODE_IT_FT  -> Falling edge
         * GPIO_MODE_IT_RT  -> Rising edge
         * GPIO_MODE_IT_RFT -> Rising + Falling edge
         *
         * This requires:
         *
         * AFIO
         * EXTI
         * NVIC     */

    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT )
    {
    	 //1. configure the FTSR
    	EXTI->FTSR |=( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

    	  //Clear the corresponding RTSR bit
    	 EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    	 }


    else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT )
    {
    	 //1 . configure the RTSR
    	EXTI->RTSR |=( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    	//Clear the corresponding FTSR bit
    	EXTI->FTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }
    else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT )
    {
    	// configure the FTSR and RTSR

    	EXTI->RTSR |=( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);


    	EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

    }






    //2. configure the GPIO port selection in AFIO_EXTICR

    uint8_t temp1= pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4 ;
    uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
    uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
    AFIO_PCLK_EN();
    AFIO->EXTICR[temp1]= portcode << (temp2*4);

    //3 . enable the exti interrupt delivery using IMR|
    EXTI->IMR |=(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }
    	temp =0;


    }



/*
 * GPIO DeInit
 *  */


/*
 * @fn         - GPIO_DeInit
 *
 * @brief      - This function deinitializes GPIO peripheral.
 *
 * @param[in]  - Base address of GPIO peripheral
 *
 * @return     - none
 *
 * @note       - none
 */

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    /*
     * Will be implemented using RCC APB2 reset registers.
     */

	        if(pGPIOx == GPIOA)
	        {
	        	GPIOA_REG_RESET();
	        }

	        else if(pGPIOx == GPIOB)
	        {
	        	GPIOB_REG_RESET();
	        }

	        else  if(pGPIOx == GPIOC)
	        {
	        	GPIOC_REG_RESET();
	        }

	        else if(pGPIOx == GPIOD)
	        {
	        	GPIOD_REG_RESET();
	        }

	        else if(pGPIOx == GPIOE)
	        {
	        	GPIOE_REG_RESET();
	        }

	        else  if(pGPIOx == GPIOF)
	        {
	        	GPIOF_REG_RESET();
	        }

	        else if(pGPIOx == GPIOG)
	        {
	        	GPIOG_REG_RESET();
	        }
	    }



/*
 * Read and Write
 *  */


uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,
                              uint8_t PinNumber)
{
    uint8_t value;

    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x01U);

    return value;
}


uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    uint16_t value;

    value = (uint16_t)pGPIOx->IDR;

    return value;
}


void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,
                           uint8_t PinNumber,
                           uint8_t Value)
{
    if(Value == GPIO_SET_PIN)
    {
        pGPIOx->ODR |= (1U << PinNumber);
    }

    else
    {
        pGPIOx->ODR &= ~(1U << PinNumber);
    }
}


void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,
                            uint16_t Value)
{
    pGPIOx->ODR = Value;
}


void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,
                          uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1U << PinNumber);
}


/*
 * IRQ Configuration and ISR handling
 *  */


void GPIO_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi)
{


if(EnorDi == ENABLE)
{

	if(IRQNumber <= 31)
	{
	//program ISER0 register
		*NVIC_ISER1 |= (1<<IRQNumber);
	}


	else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
	{
		//program ISER1 register
		*NVIC_ISER2  |= ( 1 << (IRQNumber % 32) );
		}
	else if(IRQNumber >= 64 && IRQNumber < 96 )
	{
		//program ISE 2 register //64 to 95
		*NVIC_ISER3 |= ( 1 << (IRQNumber % 32) );

	}
	}
else
{

	if(IRQNumber <= 31)
	{
	//program ISER0 register
		*NVIC_ICER0 |= (1<<IRQNumber);
	}


	else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
	{
		//program ISER1 register
		*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
	else if(IRQNumber >= 64 && IRQNumber < 96 )
	{
		//program ISE 2 register //64 to 95
		*NVIC_ICER2 |= ( 1 << (IRQNumber % 32) );

	}



}
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
//1. first lets find out the ipr register
uint8_t iprx = IRQNumber / 4;
uint8_t iprx_section = IRQNumber %4 ;

uint8_t shift_amount =( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

*(NVIC_PR_BASE_ADDR+(iprx *4)) |= ( IRQPriority << shift_amount );


}

void GPIO_IRQHandling(uint8_t PinNumber)
{




	//clear the exti pr register corresponding to the pin number

	if(EXTI->PR & ( 1 << PinNumber))
	{
		//clear
			EXTI->PR |=(1 << PinNumber);

	}

}
