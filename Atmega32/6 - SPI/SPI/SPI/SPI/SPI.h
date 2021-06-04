/*
 * SPI.h
 *
 * Created: 4/16/2021 5:39:51 AM
 *  Author: Shady mamdouh 
 */ 


#ifndef SPI_H_
#define SPI_H_
// bits
#define SPCR_SPIE 7
#define SPCR_SPE 6
#define SPCR_DOR 5
#define SPCR_MSTR 4
#define SPCR_CPOL 3
#define SPCR_CPHA 2
#define SPCR_SPR1 1
#define SPCR_SPR0 0

#define SPSR_SPIF 7
#define SPSR_WCOL 6
#define SPSR_SPI2X 0
// enums 
enum MASTER_SLAVE_MODE
{
	slave_mode,
	master_mode
	};
enum PRE_SCALE_FREQ
{
	SPI_Fosc4,
	SPI_Fosc16,
	SPI_Fosc64,
	SPI_Fosc128
	};
enum SPI_ENABLE
{
	SPI_disable,
	SPI_Enable
	};
enum SPI_DOUBLE_SPEED
{
	SPI_DOUBLE_SPEED_off,
	SPI_DOUBLE_SPEED_on
	};
enum SPI_SAMPLING_EDGE
{
	SPI_Falling,
	SPI_rising
	
	};
enum SPI_OPERATING_LEVEL
{
	SPI_IDLE_HIGH,
	SPI_IDLE_LOW
	
	};
enum SPI_INT_ENABLE
{
	INT_Disabled,
	INT_Enabled
	};
enum SPI_DATA_DIRECTION
{
	SPI_MSB_first,
	SPI_LSB_first
	};
struct SPI_CONFIG
{
	enum MASTER_SLAVE_MODE MODE;
	enum PRE_SCALE_FREQ   prescal;
	enum SPI_ENABLE  SPI_EN;
	enum SPI_DOUBLE_SPEED DOUBLE_SPEED_EN;
	enum SPI_SAMPLING_EDGE SMAP_EDGE;
	enum SPI_OPERATING_LEVEL OP_EGDE;
	enum SPI_INT_ENABLE INT_ENABLE;
	enum SPI_DATA_DIRECTION DORDIR;
		
	}SPI_gCongigration;
//APIs
extern void SPI_Init(struct SPI_CONFIG Config );
extern u8 SPI_transmit_receive(u8 data);
extern u8 SPI_check_for_collision(void);
#endif /* SPI_H_ */