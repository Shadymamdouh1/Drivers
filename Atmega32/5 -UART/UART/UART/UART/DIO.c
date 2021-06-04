/*
 * DIO.c
 *
 * Created: 3/31/2021 1:07:00 AM
 *  Author: shady mamdouh
 */ 
#include "types.h"
#include "DIO.h"
#include "registers.h"
#include "macros.h"
extern void DIO_SetPinDirection(u8 port,u8 pin,u8 Dir)
{
	switch(port)
	{
		case a :
		if (Dir==OUTPUT)
		{
			set_bit(DDRA,pin);	
		}
		if (Dir==INPUT)
		{
			clr_bit(DDRA,pin);
		}
		break;
		case b :
		if (Dir==OUTPUT)
		{
			set_bit(DDRB,pin);
		}
		if (Dir==INPUT)
		{
			clr_bit(DDRB,pin);
		}
		break;
		case c :
		if (Dir==OUTPUT)
		{
			set_bit(DDRC,pin);
		}
		if (Dir==INPUT)
		{
			clr_bit(DDRC,pin);
		}
		break;
		case d :
		if (Dir==OUTPUT)
		{
			set_bit(DDRD,pin);
		}
		if (Dir==INPUT)
		{
			clr_bit(DDRD,pin);
		}
		break;
	}
}
extern void DIO_WritePinValue(u8 port,u8 pin,u8 value)
{
	
switch(port)
{
	case a :
	if (value==HIGH)
	{
		set_bit(PORTA,pin);
	}
	if (value==LOW)
	{
		clr_bit(PORTA,pin);
	}
	break;
	case b :
	if (value==HIGH)
	{
		set_bit(PORTB,pin);
	}
	if (value==LOW)
	{
		clr_bit(PORTB,pin);
	}
	break;
	case c :
	if (value==HIGH)
	{
		set_bit(PORTC,pin);
	}
	if (value==LOW)
	{
		clr_bit(PORTC,pin);
	}
	break;
	case d :
	if (value==HIGH)
	{
		set_bit(PORTD,pin);
	}
	if (value==LOW)
	{
		clr_bit(PORTD,pin);
	}
	break;
}
}
extern u8 DIO_GetPinValue(u8 port,u8 pin)
{  
	u8 x;
	switch(port)
	{
		case a :
		x= get_bit(PINA,pin);
		break;
		case b :
		x= get_bit(PINB,pin);
		break;
		case c :
		x= get_bit(PINC,pin);
		break;
		case d :
		x= get_bit(PIND,pin);
		break;
	}
	return x;
}
extern void DIO_SetPortDirection(u8 port,u8 Dir)
{
	switch(port)
	{
		case a :
		if (Dir == OUTPUT)
		{
			DDRA=0XFF;	
		}
		if (Dir == INPUT)
		{
			DDRA=0X00;
		}
		break;
		case b :
		if (Dir == OUTPUT)
		{
			DDRB=0XFF;
		}
		if (Dir == INPUT)
		{
			DDRB=0X00;
		}
		break;
		case c :
		if (Dir == OUTPUT)
		{
			DDRC=0XFF;
		}
		if (Dir == INPUT)
		{
			DDRC=0X00;
		}
		break;
		case d :
		if (Dir == OUTPUT)
		{
			DDRD=0XFF;
		}
		if (Dir == INPUT)
		{
			DDRD=0X00;
		}
		break;
	}
}
extern void DIO_WritePortValue(u8 port,u8 value)
{
	switch(port)
	{
		case a :
		PORTA =value;
		break;
		case b :
		PORTB=value;
		break;
		case c :
		PORTC=value;
		break;
		case d :
		PORTD=value;
		break;
	}
}
extern u8 DIO_GetPortValue(u8 port)
{    
	u8 x;
	switch(port)
	{
		case a :
		x=PINA;
		break;
		case b :
		x=PINB;
		break;
		case c :
		x=PINC;
		break;
		case d :
		x=PIND;
		break;
	}
	return x;
}