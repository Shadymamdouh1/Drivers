/*
 * DIO.c
 *
 * Created: 3/30/2021 7:04:40 AM
 * Author : shady mamdouh
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include "stdio.h"
#include "avr/delay.h"
#include "types.h"
#include "registers.h"
#include "macros.h"
#include "DIO.h"
int main(void)
{
    DIO_SetPinDirection(a,pin0,OUTPUT);
	
    while (1) 
    {
		DIO_WritePinValue(a,pin0,HIGH);
		_delay_ms(1000);
		DIO_WritePinValue(a,pin0,LOW);
		_delay_ms(1000);
    }
}

