/*
 * DIO.h
 *
 * Created: 3/31/2021 1:06:40 AM
 *  Author: shady mamdouh
 */ 


#ifndef DIO_H_
#define DIO_H_
#define a 0
#define b 1
#define c 2
#define d 3
#define pin0 0
#define pin1 1
#define pin2 2
#define pin3 3
#define pin4 4
#define pin5 5
#define pin6 6
#define pin7 7
#define INPUT 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0

extern void DIO_SetPinDirection(u8 port,u8 pin,u8 Dir);
extern void DIO_WritePinValue(u8 port,u8 pin,u8 value);
extern u8 DIO_GetPinValue(u8 port,u8 pin);
extern void DIO_SetPortDirection(u8 port,u8 Dir);
extern void DIO_WritePortValue(u8 port,u8 value);
extern u8 DIO_GetPortValue(u8 port);
#endif /* DIO_H_ */