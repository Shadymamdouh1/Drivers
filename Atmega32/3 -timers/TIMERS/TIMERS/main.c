/*
 * TIMERS.c
 *
 * Created: 4/1/2021 5:29:36 AM
 * Author : Shady mamdouh
 */ 

//#include <avr/io.h>
#include "avr/interrupt.h"
#include "types.h"
#include "macros.h"
#include "DIO.h"
#include "TIMER0.h"
struct S_timer0_configuration TIM0_Config;
/*------------------calculations---------------
we need to make delay 5 seconds 
 overflow mood  
 clock = 1MHZ	
 timer pre-scal=1024 so timer clk = 1MHZ /1024 = 976.56 HZ
 time per clock = 1/976.56 = 1.024 msec
 time per over flow = 256*1.024 = 262.144 msec 
 for 5 seconds we need number of over flows = 5*10^3/262.144 = 19 overflow
*/
u8 volatile x=1;
u8* volatile value;
int main(void)
{    
	 TIM0_Config.tim_mode=TIMER0_OVF;  //  enable overflow mode 
	 TIM0_Config.TOVI_enable=TOVFIE0_enable ; // enable over flow interrupt enable 
	 TIM0_Config.OCIE_enable=OCIE0_disable;   // disable OCIE
	  TIM0_Config.pre_scal=PRESCAIING_CLK1024;  // divide clock by 1024
    TIM0_init(TIM0_Config);
	TIM0_Set_Overflow_number(19);
	DIO_SetPinDirection(a,pin0,OUTPUT);
	sei();
    while (1) 
    {
		
    }
	
}
ISR(TIMER0_OVF_vect)
{
	TIM0_Get_Overflow_number(value);
	if((*value)==x)
	{
		DIO_WritePinValue(a,pin0,HIGH);
		x=0;
		for(u32 y=0;y<70000;y++);
		DIO_WritePinValue(a,pin0,LOW);
		
	}
	x++;
}
