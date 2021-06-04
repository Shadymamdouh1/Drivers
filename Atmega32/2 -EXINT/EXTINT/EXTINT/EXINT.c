/*
 * EXTINT.c
 *
 * Created: 3/31/2021 12:21:34 PM
 *  Author: shady mamdouh
 */ 
#include "types.h"
#include "DIO.h"
#include "registers.h"
#include "macros.h"
#include "EXINT.h"
extern void EXTINT0_init(u8 trigger)
{
	switch(trigger)	
	{
	case LOW_LEVEL :
		
		clr_bit(MCUCR,ISC00); // we need to set ISC01:00 TO 00
		clr_bit(MCUCR,ISC01);
		break;
	case Any_logic :
	
	set_bit(MCUCR,ISC00); // we need to set ISC10:00 TO 01
	clr_bit(MCUCR,ISC01);
	break;
	
	case Failing :
	
	clr_bit(MCUCR,ISC00); // we need to set ISC10:00 TO 10
	set_bit(MCUCR,ISC01);
	break;
	
	case Rising :
	
	set_bit(MCUCR,ISC00); // we need to set ISC10:00 TO 11
	set_bit(MCUCR,ISC01);
	break;
	}
	set_bit(SREG,I); // enable global interrupt
	set_bit(GICR,INT0);  // mask EXTINT0
}
extern void EXTINT1_init(u8 trigger)
{
	switch(trigger)
	{
		
	
	case LOW_LEVEL :
	
	clr_bit(MCUCR,ISC10); // we need to set ISC11:10 TO 00
	clr_bit(MCUCR,ISC11);
	break;
	case Any_logic :
	
	set_bit(MCUCR,ISC10); // we need to set ISC11:10 TO 01
	clr_bit(MCUCR,ISC11);
	break;
	
	case Failing :
	
	clr_bit(MCUCR,ISC10); // we need to set ISC11:10 TO 10
	set_bit(MCUCR,ISC11);
	break;
	
	case Rising :
	
	set_bit(MCUCR,ISC10); // we need to set ISC11:10 TO 11
	set_bit(MCUCR,ISC11);
	break;
  }
set_bit(SREG,I); // enable global interrupt
set_bit(GICR,INT1);  // mask EXTINT1
}
extern void EXTINT2_init(u8 trigger)
{
	switch(trigger)
	{
		case Failing :
		
		clr_bit(MCUCSR,ISC2); // we need to set ISC2 TO 0
		
		break;
		
		case Rising :
		
		set_bit(MCUCSR,ISC2); //we need to set ISC2 TO 1
		
		break;
	}
	set_bit(SREG,I); // enable global interrupt
	set_bit(GICR,INT2);  // mask EXTINT2
	}
extern void EXTINT_Stop(u8 INT_NUM)  // stop all external interrupts
{
	switch(INT_NUM)
	{
		case 0 :
		clr_bit(GICR,INT0);  // clear EXTINT0
		break;
		case 1 :
		clr_bit(GICR,INT1);  // clear EXTINT1
		break;
		case 2 :
		clr_bit(GICR,INT2);  // clear EXTINT2
		break;
	}
}
