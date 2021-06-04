/*
 * LCD.c
 *
 * Created: 4/25/2021 2:55:25 AM
 *  Author: Shady mamdouh
 */ 
#define F_CPU 1000000UL
#include "macros.h"
#include "types.h"
#include "registers.h"
#include "DIO.h"
#include "LCD.h"
#include "util/delay.h"
extern void LCD_send_command(u8 command)
{   
	//LCD_is_busy();
	DIO_SetPortDirection(LCD_Data_Port,OUTPUT);
	DIO_WritePinValue(LCD_Control_Port,LCD_SR_bit,LOW);  // SR =0
	DIO_WritePinValue(LCD_Control_Port,LCD_RW_bit,LOW);  // R/W =0 (WRITE MODE)
	
	//8 BIT MODE
	#ifdef LCD_mode_8bit
	DIO_WritePortValue(LCD_Data_Port,command);
	LCD_Kick();
	#endif
	
	// 4 BIT MODE
	#ifdef LCD_mode_4bit
	DIO_WritePortValue(LCD_Data_Port,command);   //  first 4 MSB bits only will be taken
	LCD_Kick();
	DIO_WritePortValue(LCD_Data_Port,command<<4);   // second 4 bits after shift left
	LCD_Kick();
	#endif
}
extern void LCD_Kick(void)
{   
	DIO_WritePinValue(LCD_Control_Port,LCD_EN_bit,HIGH);
	_delay_ms(50);
	DIO_WritePinValue(LCD_Control_Port,LCD_EN_bit,LOW);
}
extern void LCD_is_busy(void)
{   
	DIO_SetPortDirection(LCD_Data_Port,INPUT);
	DIO_WritePinValue(LCD_Control_Port,LCD_SR_bit,LOW);  // SR =0
	DIO_WritePinValue(LCD_Control_Port,LCD_RW_bit,HIGH);  // R/W =1 (READ MODE)
	DIO_WritePinValue(LCD_Control_Port,LCD_EN_bit,HIGH);   // EN 
	while(DIO_GetPinValue(LCD_Data_Port,7));  // IF BIT 7 IS LOGIC 1 thats means the LCD is busy so loop till become 0
	DIO_WritePinValue(LCD_Control_Port,LCD_EN_bit,LOW);
}
extern void LCD_init(void)
{   
	_delay_ms(20);
	DIO_SetPortDirection(LCD_Data_Port,OUTPUT);
	DIO_SetPortDirection(LCD_Control_Port,OUTPUT);
	DIO_WritePinValue(LCD_Control_Port,LCD_RW_bit,LOW);
	DIO_WritePinValue(LCD_Control_Port,LCD_EN_bit,LOW);
	DIO_WritePinValue(LCD_Control_Port,LCD_SR_bit,LOW);
	#ifdef LCD_mode_8bit
	LCD_send_command(LCD_mode_8bit_2line);
	#endif
	#ifdef LCD_mode_4bit
	LCD_send_command(LCD_mode_4bit_2line);
	#endif
	LCD_clear_screen();
	LCD_send_command(LCD_ENTRY_INC_MODE);
	LCD_send_command(0x80);    // start from row 0 position 0
	LCD_send_command(LCD_DIS_ON_CURSOR_BLINK);
}
extern void LCD_display_charcter(u8 data)
{
	//LCD_is_busy();
	DIO_SetPortDirection(LCD_Data_Port,OUTPUT);
	DIO_WritePinValue(LCD_Control_Port,LCD_SR_bit,HIGH);  // SR =1
	DIO_WritePinValue(LCD_Control_Port,LCD_RW_bit,LOW);  // R/W =0 (WRITE MODE)
	
	//8 BIT MODE
	#ifdef LCD_mode_8bit
	DIO_WritePortValue(LCD_Data_Port,data);
	LCD_Kick();
	#endif
	
	// 4 BIT MODE
	#ifdef LCD_mode_4bit
	DIO_WritePortValue(LCD_Data_Port,data);   //  first 4 MSB bits only will be taken
	LCD_Kick();
	DIO_WritePortValue(LCD_Data_Port,data<<4);   // second 4 bits after shift left
	LCD_Kick();
	#endif
	//LCD_send_command(LCD_MOVE_CURSOR_RIGHT);
}
extern void LCD_display_String(u8 *string)
{
	//LCD_is_busy();
	DIO_SetPortDirection(LCD_Data_Port,OUTPUT);
	DIO_WritePinValue(LCD_Control_Port,LCD_SR_bit,HIGH);  // SR =1
	DIO_WritePinValue(LCD_Control_Port,LCD_RW_bit,LOW);  // R/W =0 (WRITE MODE)
	u8 count=0;
	while(*string > 0)
	{    
		count++;
		 LCD_display_charcter(*string++);
		if (count ==16)  // first row completed
		{
			LCD_GoTo_xy(1,0);   // row 1 position 0
			
		}
		if (count ==32)       // LCD filled and will be cleared and start again
		{   LCD_clear_screen();
			LCD_GoTo_xy(0,0);   // row 0 position 0
			count=0;
		}
	}
}
extern void LCD_display_number(u8 number)
{    
	  u8 str[7];
	 sprintf(str,"%d",number);
	 LCD_display_String(str);
}
extern void LCD_clear_screen(void)
{
	LCD_send_command(LCD_CLR_DIS_AND_DDRAM);
}
extern void LCD_GoTo_xy(u8 row, u8 position)
{
	if (row == 0)
	{
		LCD_send_command(0x80+position);
	}
	else if (row == 1)
	{
		LCD_send_command(0xC0+position);
	}
}