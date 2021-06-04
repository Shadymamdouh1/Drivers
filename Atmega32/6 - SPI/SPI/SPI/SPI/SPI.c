/*
 * SPI.c
 *
 * Created: 4/16/2021 5:38:59 AM
 *  Author: Shady mamdouh
 */ 
#include "types.h"
#include "registers.h"
#include "macros.h"
#include "SPI.h"
extern void SPI_Init(struct SPI_CONFIG Config )
{
	/***************interrupt enable****************/
 SPCR |=(Config.INT_ENABLE<<SPCR_SPIE);
 /******************DATA order *******************/
 SPCR |=(Config.DORDIR<<SPCR_DOR);
 /****************MASTER or slave****************/
 SPCR |=(Config.MODE<<SPCR_MSTR);
 /***************CLOCK polarity******************/
 SPCR |=(Config.OP_EGDE<<SPCR_CPOL);
 /**************Clock phase*********************/
 SPCR |=(Config.SMAP_EDGE<<SPCR_CPHA);
 /**************pre scale in master mode**************/
 SPCR |=(Config.prescal<<SPCR_SPR0);
 /**************double speed **********************/
 SPSR |=(Config.DOUBLE_SPEED_EN<<SPSR_SPI2X);
 /******************SPI ENABLE**********************/
 SPCR |=(Config.SPI_EN<<SPCR_SPE);
}
extern u8 SPI_transmit_receive(u8 data)
{   
	SPDR = data;    // trasmit data 
	while(!(SPSR & (1<<SPSR_SPIF) ));
	return SPDR;   // received data
}
extern u8 SPI_check_for_collision(void)
{
	int SPI_collision =0;
	if (   ( (SPSR &(1<<SPSR_WCOL))>>SPSR_WCOL ) ==1  )
	{
		SPI_collision=1;
	}
 return SPI_collision;
}