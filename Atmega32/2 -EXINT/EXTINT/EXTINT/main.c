/*
 * EXTINT.c
 *
 * Created: 3/31/2021 12:14:27 PM
 * Author : shady mamdouh
 */ 

//#include <avr/io.h>
#define F_CPU 1000000UL
#include "types.h"
#include "registers.h"
#include "macros.h"
#include "DIO.h"
#include "EXINT.h"
#include "avr/interrupt.h"
int main(void)
    
{  
	 DIO_WritePortValue(d,0XFF);       // PULL UP INT0 AND INT1
	 DIO_WritePinValue(b,pin2,HIGH);  //pull up INT2 
	 DIO_SetPortDirection(a,OUTPUT);  
    EXTINT0_init(Rising);
	EXTINT1_init(Any_logic);
	EXTINT2_init(Failing);
    while (1) 
    {
    }
}
ISR(INT0_vect)
{  
	toggle_bit(PORTA,pin0);
}
ISR(INT1_vect)
{
	toggle_bit(PORTA,pin1);
}
ISR(INT2_vect)
{
	toggle_bit(PORTA,pin2);
}

