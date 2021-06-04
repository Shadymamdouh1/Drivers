/*
 * registers.h
 *
 * Created: 3/30/2021 7:20:38 AM
 *  Author: shady mamdouh
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_
#define PORTA *((u8*)0x3B)
#define DDRA *(( u8*)0x3A)
#define PINA *((volatile u8*)0x39)

#define PORTB *(( u8*)0x38)
#define DDRB *(( u8*)0x37)
#define PINB *((volatile u8*)0x36)

#define PORTC *(( u8*)0x35)
#define DDRC *(( u8*)0x34)
#define PINC *((volatile u8*)0x33)

#define PORTD *(( u8*)0x32)
#define DDRD *(( u8*)0x31)
#define PIND *((volatile u8*)0x30)

#define SREG *((volatile u8*)0x5F)
#define MCUCR *((volatile u8*)0x55)
#define MCUCSR *((volatile u8*)0x54)
#define GICR *((volatile u8*)0x5B)


#define TCNT0 *((volatile u16*)0x52)
#define TCCR0 *((volatile u16*)0x53)
#define OCR0 *((volatile u16*)0x5C)
#define TIMSK *((volatile u16*)0x59)
#define TIFR *((volatile u16*)0x58)

#define ADMUX *((volatile u8*)0x27)
#define ADCSRA *((volatile u8*)0x26)
#define ADC *((volatile u8*)0x24)
#define ADCH *((volatile u8*)0x0x25)
#define SFIOR *((volatile u8*)0x50)
//USART Registers
#define UBRRL *((volatile u8*)0x29)
#define UCSRB *((volatile u8*)0x2A)
#define UCSRA *((volatile u8*)0x2B)
#define UDR *((volatile u8*)0x2C)
#define UBBRH *((volatile u8*)0x40)
#define UCSRC *((volatile u8*)0x40)

#define SPCR *((volatile u8*)0x2D)
#define SPSR *((volatile u8*)0x2E)
#define SPDR *((volatile u8*)0x2F)
// I2C Registers 
#define TWCR *((volatile u8*)0x56)
#define TWDR *((volatile u8*)0x23)
#define TWAR *((volatile u8*)0x22)
#define TWSR *((volatile u8*)0x21)
#define TWBR *((volatile u8*)0x20)
#endif /* REGISTERS_H_ */