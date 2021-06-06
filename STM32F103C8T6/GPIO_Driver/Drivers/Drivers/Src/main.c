/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Shady mamdpuh
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
#include "stm32f103c8.h"
#include "GPIO.h"

void clock_init()
{
	RCC_GPIOA_CLK_EN();
	RCC_AFIO_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_GPIOC_CLK_EN();
}
void GPIO_init()
{
	GPIO_PinConfig_t Pincfg;
	//PA0 floating input
	Pincfg.GPIO_PinNumber = GPIO_PIN_1;
	Pincfg.GPIO_MODE =GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(GPIOA, &Pincfg);
	//PB1 OUTPUT push pull

	Pincfg.GPIO_PinNumber = GPIO_PIN_1;
	Pincfg.GPIO_MODE =GPIO_MODE_OUTPUT_PP;
	Pincfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_init(GPIOB, &Pincfg);

	//PA13 floating input
	Pincfg.GPIO_PinNumber = GPIO_PIN_13;
	Pincfg.GPIO_MODE =GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(GPIOA, &Pincfg);

	//PB13 OUTPUT push pull

		Pincfg.GPIO_PinNumber = GPIO_PIN_13;
		Pincfg.GPIO_MODE =GPIO_MODE_OUTPUT_PP;
		Pincfg.GPIO_Output_Speed=GPIO_SPEED_10M;
		MCAL_GPIO_init(GPIOB, &Pincfg);
}
void my_wait(uint32_t x)
{
	uint32_t y,z;
	for(y=0;y<x;y++)
		for(z=0;z<255;z++);

}
int main(void)
{
	clock_init();
	GPIO_init();
	while(1)
	{
		//PA1 >>> is connected to PUll up Resistor
		//if(((GPIOA_IDR & (1<<1)) >>1 ) == 0) // button pressed
		if(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1 ) == 0)
		{
			//GPIOB_ODR ^=(1<<1); // toggle led on PB1
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);

			//while((((GPIOA_IDR & (1<<1))>>1)==0)); // for single pressing we wait for release button
			while(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1 ) == 0);
		}
		//PA13 >>> is connected to Pull Down Resistance
		//if(((GPIOA_IDR & (1<<13)) >>13 ) ==1 ) // button pressed
		if(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_13 ) == 1)
		{
			//GPIOB_ODR ^=(1<<13); // toggle led on PB13 multipressing
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
		}
		my_wait(300);
	}


}
