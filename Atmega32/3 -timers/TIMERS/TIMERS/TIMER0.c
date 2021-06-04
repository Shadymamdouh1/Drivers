/*
 * TIMER0.c
 *
 * Created: 4/1/2021 5:43:22 AM
 *  Author: shady mamdouh
 */ 
#include "types.h"
#include "DIO.h"
#include "registers.h"
#include "macros.h"
#include "TIMER0.h"
u8 TIM0_TOV_Number;  
extern void TIM0_init(struct S_timer0_configuration configuration) // basic configuration
{  
//-----------------Adjust mode---------------------------------------------
	switch(configuration.tim_mode)
	{
		case TIMER0_OVF :                // normal overflow mode WGM01:00  00
		clr_bit(TCCR0,TCCR0_WGM00);
		clr_bit(TCCR0,TCCR0_WGM01);
		break;
		case TIMER0_CTC :              // compare match mode WGM01:00  10
	    clr_bit(TCCR0,TCCR0_WGM00);
		set_bit(TCCR0,TCCR0_WGM01);
		break;
		case TIMER0_PWM_PhaseCorrect :              // PWM Phase correct (slow) WGM01:00  01
		set_bit(TCCR0,TCCR0_WGM00);
		clr_bit(TCCR0,TCCR0_WGM01);
		break;
		case TIMER0_PWM_Fast :              // PWM Phase correct (slow) WGM01:00  01
		set_bit(TCCR0,TCCR0_WGM00);
		set_bit(TCCR0,TCCR0_WGM01);
		break;
	}
//--------------Adjust prescaler----------------------

TCCR0 &=0b11111000;   // clear first 3 bit associated to prescaling

TCCR0 |=configuration.pre_scal;      // according to prescale enum arrangement for ex pre_scal=PRESCAIING_CLK8
									// thats mean TCCR0 OR  2
									
//-----------------over flow interrupt Enable/Disable-----------------------------------------
	switch(configuration.TOVI_enable)
	{
	case TOVFIE0_enable :
	set_bit(TIMSK,TIMSK_TOIE0);
	break;
	case TOVFIE0_disable :
	clr_bit(TIMSK,TIMSK_TOIE0);
	break;
	}
//-----------------Output compare Enable/Disable -----------------------------------------
switch(configuration.OCIE_enable)
{
	case OCIE0_enable :
	set_bit(TIMSK,TIMSK_OCIE0);
	break;
	case OCIE0_disable :
	clr_bit(TIMSK,TIMSK_OCIE0);
	break;
}
//-----------------CO inverting & non inverting -----------------------------------------
switch(configuration.CO_mode)
	{   
		 case CO_Disconected :       // COM10:00 -> 00
		 clr_bit(TCCR0,TCCR0_COM01);
		 clr_bit(TCCR0,TCCR0_COM00);
		 break; 
		case CO_Non_inverting :       // COM10:00 -> 10
		set_bit(TCCR0,TCCR0_COM01);
		clr_bit(TCCR0,TCCR0_COM00);
		break;
		case CO_inverting :       // COM10:00 -> 11
		set_bit(TCCR0,TCCR0_COM01);
		set_bit(TCCR0,TCCR0_COM00);
		break;
	}
}
extern void TIM0_read_counter_val(u8* num_of_ticks)
{
	*num_of_ticks=TCNT0;
}
extern void TIM0_Set_compareMatch_value(u8 value)
{
	OCR0=value;
}
extern void TIM0_Set_Counter_value(u8 value)    // TCNT0
{
	TCNT0=value;
}
extern void TIM0_Set_Overflow_number(u8 value)  // used in SW to take action after a number of TOV occur
{
	TIM0_TOV_Number=value;
}
extern void TIM0_Get_Overflow_number(u8* value)
{
	*value=TIM0_TOV_Number;
}
extern void TIM0_Get_ticks_ofSWCounter(u32* value) // total number of tick contains the number of iterate on TOV and the value of TCNT0
{
	*value= 256*TIM0_TOV_Number + TCNT0;
} 