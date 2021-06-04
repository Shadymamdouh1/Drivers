/*
 * keypad.c
 *
 * Created: 4/25/2021 8:52:08 PM
 * Author : shady mamdouh
 */ 

#define F_CPU 1000000ul
#include "macros.h"
#include "types.h"
#include "registers.h"
#include "DIO.h"
#include "LCD.h"
#include "keypad.h"
#include "util/delay.h"
u16 password =1234;
u8 string_pass[5];
int main(void)
{    int i;
	 keyPad_init();
	LCD_init();
	int key_value;
	u16 entered_pass;
LCD_display_String("enter password");
LCD_GoTo_xy(1,0);      
	while (1)
	{   key_value=keyPad_GetKey();
		switch(key_value)
		{
			case 'A' :
			break;
			
			case '?' :
			LCD_clear_screen();
			break;
			case '=' :
			entered_pass=atoi(string_pass);
			if (entered_pass==password)
			{
				LCD_clear_screen();
				LCD_display_String("correct pass");
			}
			else
			{
				LCD_clear_screen();
				LCD_display_String("incorrect pass");
			}
			for(i=0;i<5;i++)
			{
				string_pass[i]=0;
			}
			i=0;
			break;
			default :
			LCD_display_charcter(key_value);
			string_pass[i++]=key_value;
		}
		_delay_ms(50);
	}
}

