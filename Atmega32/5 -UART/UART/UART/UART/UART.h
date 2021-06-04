/*
 * UART.h
 *
 * Created: 4/14/2021 7:20:00 PM
 *  Author: Shady mamdouh
 */ 


#ifndef UART_H_
#define UART_H_
// Registers bits 
#define UCSRA_RXC 7
#define UCSRA_TXC 6
#define UCSRA_UDRE 5
#define UCSRA_FE 4
#define UCSRA_DOR 3
#define UCSRA_PE 2
#define UCSRA_U2X 1
#define UCSRA_MPCM 0

#define UCSRB_RXCIE 7
#define UCSRB_TXCIE 6
#define UCSRB_UDRIE 5
#define UCSRB_RXEN 4
#define UCSRB_TXEN 3
#define UCSRB_UCSZ2 2
#define UCSRB_RXB8 1
#define UCSRB_TXB8 0

#define UCSRC_URSEL 7
#define UCSRC_UMSEL 6
#define UCSRC_UPM1 5
#define UCSRC_UPM0 4
#define UCSRC_USBS 3
#define UCSRC_UCSZ1 2
#define UCSRC_UCSZ0 1
#define UCSRC_UCPOL 0

#define USART_BAUD 1200
#define USART_FOSC 1000000

enum USART_MOD    // asynchronous or synchronous  mode
{
	USART_async,
	USART_sync
	};
enum USART_async_speed  // according to U2X bit 
{
	USART_async_normal,
	USART_async_double
	};  
enum USART_Enable_TX   // enable transmitter
{   
	USART_tx_disable,
	USART_tx_enable
	
	};
enum USART_Enable_RX   // enable receiver
{    
	USART_rx_disable,
	USART_rx_enable
	
};
enum USART_Char_size   // number of data bits 
{
	USART_5_bit_char,
	USART_6_bit_char,
	USART_7_bit_char,
	USART_8_bit_char,
	USART_9_bit_char
	};
enum USART_Parity     // disable parity or enable with number of parity bits 
{
	USART_disable_parity,
	reserved,
	USART_even_parity,   
	USART_odd_parity   
	};
enum USART_Stop_bits // number of stop bits
{
	USART_1_stop_bit,
	USART_2_stop_bits
	};
enum USART_RX_INT   // enable receiving data interrupt
{   
	USART_RX_INT_disable,
	USART_RX_INT_enable
	
	};
enum USART_TX_INT   // enable Transmitter data interrupt
{  
	 USART_TX_INT_disable,
	USART_TX_INT_enable
	
};
enum USART_UDRIE_INT   // enable UDRE data interrupt used in transmitting to inform that UDR is empty
{   
	USART_UDR_INT_disable,
	USART_UDR_INT_enable
	
};
struct USART_configuration
{
	enum USART_MOD USART_MODE;
	enum USART_async_speed async_speed;
	enum USART_Enable_TX USART_TX;
	enum USART_Enable_RX USART_RX;
	enum USART_Char_size data_size;
	enum USART_Parity parity;
	enum USART_Stop_bits stop_bits;
	enum USART_RX_INT RXC_INT;
	enum USART_TX_INT TXC_INT;
	enum USART_UDRIE_INT UDRIE_INT;
	
	}USART_GConfiguration;
	
// APIs
extern void USART_Init(struct USART_configuration config);
extern void USART_Transmit(u16 data);
extern  u8 USART_Receive (u16 *Ptr_to_val);
extern void USART_RxInterruptEnable(void);
extern void USART_RxInterruptDiable(void);
extern void USART_TxInterruptEnable(void);
extern void USART_TxInterruptDisable(void);
extern void USART_UDRInterruptEnable(void);
extern void USART_UDRInterruptDisable(void);
extern void USART_TX_Enable(void);
extern void USART_TX_Diable(void);	
extern void USART_RX_Enable(void);
extern void USART_RX_Diable(void);

#endif /* UART_H_ */