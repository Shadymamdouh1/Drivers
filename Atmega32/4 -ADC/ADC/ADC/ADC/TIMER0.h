/*
 * TIMER0.h
 *
 * Created: 4/1/2021 5:43:43 AM
 *  Author: shady mamdouh
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_
//------------------------- timer configuration----------------------------
enum TIMER0_Mode
{
	TIMER0_OVF,
	TIMER0_CTC
};
enum TOVFIE0  // over flow interrupt enable
{
	TOVFIE0_enable,
	TOVFIE0_disable
};
enum OCMIE0  // compare match interrupt enable
{
	OCIE0_enable,
	OCIE0_disable
};
enum TIMER0_pre_scale
{
	NO_CLK_SRC,  // timer disabled
	NO_PRESCAIING,
	PRESCAIING_CLK8,
	PRESCAIING_CLK64,
	PRESCAIING_CLK256,
	PRESCAIING_CLK1024,
	EXT_CLK_FALLING,
	EXT_CLK_RISING
	};
struct S_timer0_configuration
{
	enum TIMER0_Mode tim_mode;
	enum TOVFIE0 TOVI_enable;
	enum OCMIE0 OCIE_enable;
	enum TIMER0_pre_scale pre_scal;
	
	};
// -------------------------------functions-------------------------------------
extern void TIM0_init(struct S_timer0_configuration configuration); // basic configuration
extern void TIM0_read_counter_val(u8* num_of_ticks);        //
extern void TIM0_Set_compareMatch_value(u8 value);         
extern void TIM0_Set_Counter_value(u8 value);
extern void TIM0_Set_Overflow_number(u8 value);
extern void TIM0_Get_Overflow_number(u8* value);
//SW Counter
extern void TIM0_Get_ticks_ofSWCounter(u32* value);
//---------------------------registers bits------------------------------------
#define TCCR0_CS00 0
#define TCCR0_CS01 1
#define TCCR0_CS02 2
#define TCCR0_WGM01 3
#define TCCR0_COM00 4
#define TCCR0_COM01 5
#define TCCR0_WGM00 6
#define TCCR0_FOC0 7

#define TIMSK_TOIE0 0
#define TIMSK_OCIE0 1

#define TIFR_TOV0 0
#define TIFR_OCF0 1
#endif /* TIMER0_H_ */