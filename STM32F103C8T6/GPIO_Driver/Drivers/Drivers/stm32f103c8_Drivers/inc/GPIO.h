/*
 * GPIO.h
 *
 *  Created on: Jun 5, 2021
 *      Author: Shady mamdouh
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

//Includes
#include "stm32f103c8.h"
//----------------------------


//config structure

typedef struct
{
  uint16_t GPIO_PinNumber ;      // Specifies the GPIO pins to be configured.
                                  // this parameter must be a value of @ref GPIO_PINS_define
uint8_t GPIO_MODE         ;      // Specifies the operation mode for the selected pin.
                                 // this parameter must be a value of @ref GPIO_MODE_define


uint8_t GPIO_Output_Speed;       // specifies the speed for the selected pins
								// this parameter can be a value of @ref GPIO_SPEED_define


}GPIO_PinConfig_t;

//@ref GPIO_PIN_State
#define GPIO_PIN_SET     1
#define GPIO_PIN_RESET   0

//@ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_Enabled  				 1
#define GPIO_RETURN_LOCK_ERROR					 0
//=====================================================
//Macros configuration Reference
//=========================================================

// @ref GPIO_PINS_define
#define GPIO_PIN_0          ((uint16_t)0x0001)      /* pin 0 selected */
#define GPIO_PIN_1          ((uint16_t)0x0002)      /* pin 1 selected */
#define GPIO_PIN_2          ((uint16_t)0x0004)      /* pin 2 selected */
#define GPIO_PIN_3          ((uint16_t)0x0008)      /* pin 3 selected */
#define GPIO_PIN_4          ((uint16_t)0x0010)      /* pin 4 selected */
#define GPIO_PIN_5          ((uint16_t)0x0020)      /* pin 5 selected */
#define GPIO_PIN_6          ((uint16_t)0x0040)      /* pin 6 selected */
#define GPIO_PIN_7          ((uint16_t)0x0080)      /* pin 7 selected */
#define GPIO_PIN_8          ((uint16_t)0x0100)      /* pin 8 selected */
#define GPIO_PIN_9          ((uint16_t)0x0200)      /* pin 9 selected */
#define GPIO_PIN_10         ((uint16_t)0x0400)      /* pin 10 selected */
#define GPIO_PIN_11         ((uint16_t)0x0800)      /* pin 11 selected */
#define GPIO_PIN_12         ((uint16_t)0x1000)      /* pin 12 selected */
#define GPIO_PIN_13         ((uint16_t)0x2000)      /* pin 13 selected */
#define GPIO_PIN_14         ((uint16_t)0x4000)      /* pin 14 selected */
#define GPIO_PIN_15         ((uint16_t)0x8000)      /* pin 15 selected */
#define GPIO_PIN_All        ((uint16_t)0xFFFF)     /* All pis selected*/
#define GPIO_PIN_MASK       0x0000FFFFu           /* PIN mask for assert test */



// @ref GPIO_MODE_define

//0 : Analog mode
//1 : floating input (reset state)
//2 : input with pull-up
//3 : input with pull-down
//4 : General purpose output push-pull
//5 : General purpose output Open-drain
//6 : Alternate function output Push-pull
//7 : Alternate function output Open-drain
//8 : Alternate function input

#define GPIO_MODE_Analog					0x00000000u  //Analog mode
#define GPIO_MODE_INPUT_FLO					0x00000001u  //floating input
#define GPIO_MODE_INPUT_PU					0x00000002u  //input with pull-up
#define GPIO_MODE_INPUT_PD					0x00000003u  //input with pull-down
#define GPIO_MODE_OUTPUT_PP					0x00000004u  //General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD					0x00000005u  //General purpose output Open-drain
#define GPIO_MODE_OUTPUT_AF_PP				0x00000006u  //Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD				0x00000007u  //Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT					0x00000008u  //Alternate function input


//@ref GPIO_SPEED_define
//1 : output mode , max speed 10 MHz
//2 : output mode , max speed 2 MHz
//3 : output mode , max speed 50 MHz
#define  GPIO_SPEED_10M 					0x00000001u //1 : output mode , max speed 10 MHz
#define  GPIO_SPEED_2M						0x00000002u //2 : output mode , max speed 2 MHz
#define  GPIO_SPEED_50M						0x00000003u //3 : output mode , max speed 50 MHz

/*==========================================================================================
								APIs Supported by MCAL GPIO Driver
==========================================================================================*/


void MCAL_GPIO_init( GPIO_TypeDef *GPIOx,GPIO_PinConfig_t* PinConfig );
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx);
uint8_t MCAL_GPIO_ReadPin( GPIO_TypeDef *GPIOx,uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx,uint16_t PinNumber,uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx,uint16_t value);
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx,uint16_t PinNumbere);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx,uint16_t PinNumbere);






#endif /* INC_GPIO_H_ */
