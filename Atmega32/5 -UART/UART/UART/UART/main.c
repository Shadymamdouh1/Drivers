/*
 * UART.c
 *
 * Created: 4/14/2021 7:16:54 PM
 * Author : Shady mamdouh
 */ 

//#include <avr/io.h>
#include "registers.h"
#include "types.h"
#include "macros.h"
#include "DIO.h"
#include "UART.h"

int main(void)
{     
    USART_GConfiguration.USART_MODE=USART_async;
	USART_GConfiguration.async_speed=USART_async_normal;
	USART_GConfiguration.data_size=USART_8_bit_char;
	USART_GConfiguration.USART_TX=USART_tx_enable;
	USART_GConfiguration.parity=USART_disable_parity;
	USART_GConfiguration.stop_bits=USART_1_stop_bit;
	USART_Init(USART_GConfiguration);
	USART_Transmit(10);
    while (1) 
    {
    }
}

