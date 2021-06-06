/*
 * GPIO.c
 *
 *  Created on: Jun 5, 2021
 *      Author: Shady mamdouh
 */
#include "GPIO.h"
#include "stm32f103c8.h"

uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch (PinNumber)
	{
	case GPIO_PIN_0 :
		return 0;
		break;
	case GPIO_PIN_1 :
		return 4;
		break;
	case GPIO_PIN_2 :
		return 8 ;
		break;
	case GPIO_PIN_3 :
		return 12;
		break;
	case GPIO_PIN_4 :
		return 16;
		break;
	case GPIO_PIN_5 :
		return 20;
		break;
	case GPIO_PIN_6 :
		return 24;
		break;
	case GPIO_PIN_7 :
		return 28;
		break;
	case GPIO_PIN_8 :
		return 0;
		break;
	case GPIO_PIN_9 :
		return 4;
		break;
	case GPIO_PIN_10 :
		return 8 ;
		break;
	case GPIO_PIN_11 :
		return 12;
		break;
	case GPIO_PIN_12 :
		return 16;
		break;
	case GPIO_PIN_13 :
		return 20;
		break;
	case GPIO_PIN_14 :
		return 24;
		break;
	case GPIO_PIN_15 :
		return 28;
		break;
	}
}
/**================================================================
 * @Fn					 -MCAL_GPIO_init
 * @brief 				 -initializes the GPIOx PINy peripheral according to specified parameters in the PinConfig
 * @param [in] 			 -GPIOx : where x can be (A..D depend on device used) to select the GPIO peripheral
 * @param [in] 			 - PinConfig pointer to a GPIO_PinConfig_t structure that contains
 * 						   the configuration information for the specified GPIO PIN
 * @retval				 - none
 * Note-
 */
void MCAL_GPIO_init( GPIO_TypeDef *GPIOx,GPIO_PinConfig_t* PinConfig )
{
	//Port configuration register low (GPIOx_CRL) configure pins from 0 to 7
	//Port configuration register low (GPIOx_CRH) configure pins from 8 to 15

	volatile uint32_t *cofigregester =NULL;
	uint8_t PIN_Config = 0;
	cofigregester =(PinConfig->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL :  &GPIOx->CRH ;

	// clear CNF[1:0] MODE[1:0]
	(*cofigregester) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	//if Pin is output
	if((PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD) ||(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD) ||(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP ))
	{
		// Set CNF[1:0] MODE[1:0]
		PIN_Config =( (((PinConfig->GPIO_MODE -4) <<2 ) |(PinConfig->GPIO_Output_Speed)) & 0x0f) ;


	}
	// if Pin is Input
	// MODE will be 00
	else
	{
		if( (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO) || (PinConfig->GPIO_MODE == GPIO_MODE_Analog) )

		{   // Set CNF[1:0] MODE[1:0]
				PIN_Config =( ((PinConfig->GPIO_MODE) <<2 ) & 0x0f)  ;


		}
		else if(   PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT   ) // Consider it as input floating
		{
			PIN_Config =( ((GPIO_MODE_INPUT_FLO) <<2 ) & 0x0f)  ;
		}
		else // PU PD input
		{
			PIN_Config =( ((GPIO_MODE_INPUT_PU) <<2 ) & 0x0f)  ;

			if( PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				//Table 20. Port bit configuration table PxODR register 1
				GPIOx->ODR |=PinConfig->GPIO_PinNumber;
			}
			else
			{
				//Table 20. Port bit configuration table PxODR register 0
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}

	}
	(*cofigregester) |= ( (PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );
}
/**==================================================================================================
 * @Fn					 -MCAL_GPIO_DeInit
 * @brief 				 -reset all the GPIOx registers
 * @param [in] 			 -GPIOx : where x can be (A..D depend on device used) to select the GPIO peripheral
 * @retval				 - none
 * Note                   - none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
/*	GPIOx->CRL=0x44444444;  // reset value according TRM
	GPIOx->CRH=0x44444444;
	GPIOx->BRR=0x00000000;
	GPIOx->BSRR=0x00000000;
	//GPOIx->IDR =; (read Only)
	GPIOx->LCKR=0x00000000;
	GPIOx->ODR =0x00000000;*/

	//we can also reset using reset controller by setting then resetting
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |=(1<<2); // Bit 2 IOPARST : IO port A reset
		RCC->APB2RSTR &= ~(1<<2);

	}else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |=(1<<3); // Bit 3 IOPARST : IO port B reset
		RCC->APB2RSTR &= ~(1<<3);
	}else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |=(1<<4);  //// Bit 4 IOPARST : IO port C reset
		RCC->APB2RSTR &= ~(1<<4);
	}else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |=(1<<5);  //// Bit 5 IOPARST : IO port D reset
		RCC->APB2RSTR &= ~(1<<5);
	}
}
/**================================================================
 * @Fn					 -MCAL_GPIO_ReadPin
 * @brief 				 -Read Specific PIN
 * @param [in] 			 -GPIOx : where x can be (A..D depend on device used) to select the GPIO peripheral
 * @param [in]			 -PinNumber set pin number according to @ref GPIO_PINS_define
 * @retval				 - the input PIN value (two values based on @ref GPIO_PIN_State)
 * Note                   - none
 */

uint8_t MCAL_GPIO_ReadPin( GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{
  uint8_t bitstatus;
  if (  ( (GPIOx->IDR) & PinNumber) !=(uint32_t)GPIO_PIN_RESET)
  {
	  bitstatus =GPIO_PIN_SET ;
  }else
  {
	  bitstatus =GPIO_PIN_RESET;
  }
  return bitstatus;
}
/**================================================================
 * @Fn					 -MCAL_GPIO_ReadPort
 * @brief 				 -Read Specific Port
 * @param [in] 			 -GPIOx : where x can be (A..D depend on device used) to select the GPIO peripheral
 * @param [in]			 -PinNumber set pin number according to @ref GPIO_PINS_define
 * @retval				 - the input Port value
 * Note                   - none
 */


uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
uint16_t port_value;
port_value =(uint16_t)(GPIOx->IDR);
return port_value;

}
/**================================================================
 * @Fn					 -MCAL_GPIO_WritePin
 * @brief 				 -write on Specific output Pin
 * @param [in] 			 -GPIOx : where x can be (A..D depend on device used) to select the GPIO peripheral
 * @param [in]			 -PinNumber set pin number according to @ref GPIO_PINS_define
 * @param [in]			 -value : Pin value
 * @retval				 - none
 * Note                   - none
 */

void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx,uint16_t PinNumber,uint8_t value)
{
	 if ( value != GPIO_PIN_RESET)
	  {
		 // GPIOx->ODR |=PinNumber;
		 //or
		 GPIOx->BSRR =(uint32_t)PinNumber;
	  }else
	  {
		  GPIOx->BRR =(uint32_t)PinNumber;
	  }
}
/**================================================================
 * @Fn					 -MCAL_GPIO_WritePort
 * @brief 				 -Write on Specific output Port
 * @param [in] 			 -GPIOx : where x can be (A..D depend on device used) to select the GPIO peripheral
 *@param [in]			 -value : Port value
 *@retval				 - none
 * Note                   - none
 */


void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx,uint16_t value)
{
 GPIOx->ODR =(uint32_t)value;
}
/**================================================================
 * @Fn					 -MCAL_GPIO_TogglePin
 * @brief 				 - Toggle Specific output Pin
 * @param [in] 			 -GPIOx : where x can be (A..D depend on device used) to select the GPIO peripheral
 * @param [in]			 -PinNumber set pin number according to @ref GPIO_PINS_define
 *@retval				 - none
 * Note                   - none
 */

void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx,uint16_t PinNumbere)
{

GPIOx->ODR ^= (PinNumbere);

}
/**================================================================
 * @Fn					 -MCAL_GPIO_LockPin
 * @brief 				 -The locking mechanism allows the IO configuration to be frozen
 * @param [in] 			 -GPIOx : where x can be (A..D depend on device used) to select the GPIO peripheral
 * @param [in]			 -PinNumber set pin number according to @ref GPIO_PINS_define
 *@retval				 - Ok if pin config is locked or ERROR if pin not Loced (Ok and ERROR are defined @ref GPIO_RETURN_LOCK)
 * Note                   - none
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx,uint16_t PinNumbere)
{
	/*Bit 16 LCKK[16]: Lock key
This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
0: Port configuration lock key not active
1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
LOCK key writing sequence:
Write 1
Write 0
Write 1
Read 0
Read 1 (this read is optional but confirms that the lock is active)
Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
Any error in the lock sequence will abort the lock.
Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
These bits are read write but can only be written when the LCKK bit is 0.
0: Port configuration not locked*/

// set LCKK[16]
 volatile uint32_t tmp =1<<16;
//set specific bit  LCKy
 tmp |=PinNumbere;
 //Write 1
 GPIOx->LCKR =tmp;
 //Write 0
 GPIOx->LCKR =PinNumbere;
 //Write 1
 GPIOx->LCKR =tmp;
 //Read 0
 tmp= GPIOx->LCKR;
 //Read 1 (this read is optional but confirms that the lock is active)
 if(  (uint32_t)(GPIOx->LCKR & 1<<16 )  )
 {
	 return GPIO_RETURN_LOCK_Enabled;

 }
 else
 {
	 return GPIO_RETURN_LOCK_ERROR;
 }




}



