/*
 * keypad.c
 *
 * Created: 4/25/2021 8:52:56 PM
 *  Author: Shady mamdouh
 */ 
#include "macros.h"
#include "types.h"
#include "registers.h"
#include "keypad.h"
#include "DIO.h"
u8 keypad_row[]={R0,R1,R2,R3};
u8 keypad_col[]={C0,C1,C2,C3};
extern void keyPad_init(void)
{  
	// first 4 pins are inputs (rows)
	DIO_SetPinDirection(keypad_port,R0,INPUT);
	DIO_SetPinDirection(keypad_port,R1,INPUT);
	DIO_SetPinDirection(keypad_port,R2,INPUT);
	DIO_SetPinDirection(keypad_port,R3,INPUT);
	// second 4 pins are output 
	DIO_SetPinDirection(keypad_port,C0,OUTPUT);
	DIO_SetPinDirection(keypad_port,C1,OUTPUT);
    DIO_SetPinDirection(keypad_port,C2,OUTPUT);
	DIO_SetPinDirection(keypad_port,C3,OUTPUT);
	// pull up port
	DIO_WritePortValue(keypad_port,0XFF);
}
extern u8 keyPad_GetKey(void)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		DIO_WritePinValue(keypad_port,C0,HIGH);
		DIO_WritePinValue(keypad_port,C1,HIGH);
		DIO_WritePinValue(keypad_port,C2,HIGH);
		DIO_WritePinValue(keypad_port,C3,HIGH);
		
		DIO_WritePinValue(keypad_port,keypad_col[i],LOW);
		for(j=0;j<4;j++)
		{
			if((DIO_GetPinValue(keypad_port,keypad_row[j]))==0)
			{
				while((DIO_GetPinValue(keypad_port,keypad_row[j]))==0) ;  //single pressed
				switch(i)
				{
					case 0 :
						{
							if(j == 0) return '7';
							else if(j == 1) return '4';
							else if(j == 2) return '1';
							else if(j == 3) return '?';
							break;
						}
					case 1 :
					   {
						    if(j == 0) return '8';
						    else if(j == 1) return '5';
						    else if(j == 2) return '2';
						    else if(j == 3) return '0';
						    break;
					    }
					case 2 :
					   {
						    if(j == 0) return '9';
						    else if(j == 1) return '6';
						    else if(j == 2) return '3';
						    else if(j == 3) return '=';
						    break;
					   }
					case 3 :
					{
						if(j == 0) return '/';
						else if(j == 1) return '*';
						else if(j == 2) return '-';
						else if(j == 3) return '+';
						break;
					}
					
				}
			}
		}
	}
	return 'A';  // return A if no key is pressed 
}