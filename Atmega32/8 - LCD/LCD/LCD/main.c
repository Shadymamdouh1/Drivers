/*
 * LCD.c
 *
 * Created: 4/25/2021 2:53:07 AM
 * Author : Shady mamdouh
 */ 

//#include <avr/io.h>
#define F_CPU 1000000ul
#include "macros.h"
#include "types.h"
#include "registers.h"
#include "DIO.h"
#include "LCD.h"
#include "util/delay.h"
int main(void)
{
    LCD_init();
	LCD_display_charcter('a');
	LCD_display_String("SHADY");
	LCD_display_number(10);
	LCD_display_charcter(8+48);
    while (1) 
    {
		
		_delay_ms(50);
    }
}

