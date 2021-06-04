/*
 * ADC.c
 *
 * Created: 4/4/2021 12:59:40 AM
 * Author : shady Mamdouh
 */ 

//#include <avr/io.h>
#include "types.h"
#include "DIO.h"
#define F_CPU 1000000ul
#include "avr/interrupt.h"
#include "util/delay.h"
#include "DIO.h"
#include "ADC.h"

int main(void)
{  
	DIO_SetPortDirection(a,INPUT);
	DIO_SetPortDirection(c,OUTPUT);
	DIO_SetPortDirection(d,OUTPUT);
	struct S_ADC_cofiguration config;
	config.autoTrigger_enable=autoTrigger_Disable;  // single conversion  mode 
	config.Channels=S_ADC0;    // single ended mode
	config.Clock_selector=clk_128;  // prescale dividing by 128
	config.Interrupt_Enable=interrupt_enable;  // enable ADC interrupt 
	config.Register_Shift=right;  // ADCL and ADCH 
	config.Vref_selector=internal_with_extCapacitor;  // Vref 2.56v
	ADC_enable();
	ADC_init(config);
	sei();
    
    while (1) 
    {   
		_delay_ms(500);
		DIO_WritePortValue(d,0x00);
		DIO_WritePortValue(c,0x00);
		_delay_ms(500);
		ADC_start_convertion();
		//_delay_ms(1000);
    }
	
}
ISR(ADC_vect)
{
	DIO_WritePortValue(d,ADCL);
	DIO_WritePortValue(c,ADCH);
	_delay_ms(20);
}
