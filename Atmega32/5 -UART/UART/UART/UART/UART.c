/*
 * UART.c
 *
 * Created: 4/14/2021 7:19:28 PM
 *  Author: Shady mamdouh
 */ 
#include "registers.h"
#include "types.h"
#include "macros.h"
#include "DIO.h"
#include "UART.h"
extern void USART_Init(struct USART_configuration config)
{    
	u16 UBBR_VAL;
	/************BAUD RATE Configuration according to mode of operation*************/
	
	if ((config.USART_MODE ==USART_async)&&(config.async_speed==USART_async_normal)) // Normal Asynchronous mode
	{
		UBBR_VAL = (u16)((USART_FOSC/(16*USART_BAUD))-1);
		clr_bit(UCSRA,UCSRA_U2X);
		
	}
	else if ((config.USART_MODE ==USART_async)&&(config.async_speed==USART_async_double)) // Double speed Asynchronous mode
	{
		UBBR_VAL = (u16)((USART_FOSC/(8*USART_BAUD))-1);
		set_bit(UCSRA,UCSRA_U2X);
	}
	else if (config.USART_MODE ==USART_sync) // synchronous mode
	{
		UBBR_VAL = (u16)((USART_FOSC/(2*USART_BAUD))-1);
	}
	UBRRL = (u8)UBBR_VAL;
	UBBRH = (u8)(UBBR_VAL>>8);
/*************************Enable transmitter**************************/
if (config.USART_TX == USART_tx_enable)
{
	set_bit(UCSRB,UCSRB_TXEN);
}
else if (config.USART_TX==USART_tx_disable)
{
	clr_bit(UCSRB,UCSRB_TXEN);
}
/*******************Enable receiver **********************************/
 if (config.USART_RX == USART_rx_enable)
 {
	 set_bit(UCSRB,UCSRB_RXEN);
 }
 else if (config.USART_RX==USART_rx_disable)
 {
	 clr_bit(UCSRB,UCSRB_RXEN);
 }
/****************Set charachter size**********************************/
if (config.data_size==USART_9_bit_char)    //UCSZ2:0 ---> 111
{
	set_bit(UCSRB,UCSRB_UCSZ2);
	UCSRC |=(1<<UCSRC_URSEL)|(1<<UCSRC_UCSZ0)|(1<<UCSRC_UCSZ1);
}
else 
{
	UCSRC |=(1<<UCSRC_URSEL)|(config.data_size<<UCSRC_UCSZ0);
}
/**************************parity mode******************************/
UCSRC |=(1<<UCSRC_URSEL)|(config.parity<<UCSRC_UPM0);
/*************************stop bits********************************/
UCSRC |=(1<<UCSRC_URSEL)|(config.stop_bits<<UCSRC_USBS);
/**************************synch or asynch mode****************************/

UCSRC |=(1<<UCSRC_URSEL)|(config.USART_MODE<<UCSRC_UMSEL);
/********************** RX interupt  *************************************/
UCSRB |=(config.RXC_INT<<UCSRB_RXCIE);
/********************** tx interupt  *************************************/
UCSRB |=(config.TXC_INT <<UCSRB_TXCIE);
/********************** UDRIE interupt  *************************************/
UCSRB |=(config.UDRIE_INT<<UCSRB_UDRIE);



}
extern void USART_Transmit(u16 data)
{
	while(!(UCSRA &(1<<UCSRA_UDRE)));
	if(USART_GConfiguration.data_size==USART_9_bit_char)
	{
		UCSRB |=((data>>8)&1);
	}
	UDR=(u8)data;
}
extern u8 USART_Receive (u16 *Ptr_to_val)
{    
	*Ptr_to_val=0;
     u8	parity_error=0;  // 0 means there is parity error
	while(!(UCSRA&(1<<UCSRA_RXC)));
	if(((UCSRA>>UCSRA_PE)&1)==0)    // if no parity error
	{
	if(USART_GConfiguration.data_size==USART_9_bit_char)
	{
		*Ptr_to_val=(((UCSRB>>UCSRB_RXB8)&1)<<8);
	}
	*Ptr_to_val |=UDR;
	parity_error=1; // NO ERROR
	}
	return parity_error;
}
extern void USART_RxInterruptEnable(void)
{
	set_bit(UCSRB,UCSRB_RXCIE);
}
extern void USART_RxInterruptDiable(void)
{
	clr_bit(UCSRB,UCSRB_RXCIE);
}
extern void USART_TxInterruptEnable(void)
{
	set_bit(UCSRB,UCSRB_TXCIE);
}
extern void USART_TxInterruptDisable(void)
{
	clr_bit(UCSRB,UCSRB_TXCIE);
}
extern void USART_UDRInterruptEnable(void)
{
	set_bit(UCSRB,UCSRB_UDRIE);
}
extern void USART_UDRInterruptDisable(void)
{
	clr_bit(UCSRB,UCSRB_UDRIE);
}
extern void USART_TX_Enable(void)
{
	set_bit(UCSRB,UCSRB_TXEN);
}
extern void USART_TX_Diable(void)
{
	clr_bit(UCSRB,UCSRB_TXEN);
}
extern void USART_RX_Enable(void)
{
	set_bit(UCSRB,UCSRB_RXEN);
}
extern void USART_RX_Diable(void)
{
	clr_bit(UCSRB,UCSRB_RXEN);
}
