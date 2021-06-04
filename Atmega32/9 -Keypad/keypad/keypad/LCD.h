/*
 * LCD.h
 *
 * Created: 4/25/2021 2:55:51 AM
 *  Author: Shady mamdouh
 */ 


#ifndef LCD_H_
#define LCD_H_

#define LCD_Data_Port a  // to data pins of LCD
#define LCD_Control_Port b  // to three control pins in LCD

#define LCD_RW_bit 0   
#define LCD_EN_bit 1    // you must connect the three bits in LCD_control_port to the actual pins in LCD
#define LCD_SR_bit 2

// select mode 4-bit or 8-bit by defining the mode , 
#define LCD_mode_8bit
//#define LCD_mode_4bit

// LCD COMMANDS
#define LCD_mode_8bit_1line 0x30
#define LCD_mode_8bit_2line 0x38
#define LCD_mode_4bit_1line 0x20
#define LCD_mode_4bit_2line 0x28
#define LCD_ENTRY_INC_MODE 0x06
#define LCD_DIS_OFF_CURSOR_OFF 0X08
#define LCD_DIS_ON_CURSOR_ON 0X0E
#define LCD_DIS_ON_CURSOR_OFF 0X0C
#define LCD_DIS_ON_CURSOR_BLINK 0X0F
#define LCD_DIS_SHIFT_LEFT 0X18
#define LCD_DIS_SHIFT_RIGHT 0X1C
#define LCD_MOVE_CURSOR_LEFT 0X10
#define LCD_MOVE_CURSOR_RIGHT 0X14
#define LCD_CLR_DIS_AND_DDRAM 0X01
//APIs

extern void LCD_send_command(u8 command);
extern void LCD_Kick(void);
extern void LCD_is_busy(void);
extern void LCD_init(void);
extern void LCD_display_charcter(u8 data);
extern void LCD_display_String(u8 *string);
extern void LCD_display_number(u8 number);
extern void LCD_clear_screen(void);
extern void LCD_GoTo_xy(u8 row, u8 position);

#endif /* LCD_H_ */