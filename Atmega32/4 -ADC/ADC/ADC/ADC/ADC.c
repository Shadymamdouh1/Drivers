/*
 * ADC.c
 *
 * Created: 4/4/2021 5:28:59 PM
 *  Author: SHADY MAMDOUH
 */ 
#include "types.h"
#include "registers.h"
#include "DIO.h"
#include "ADC.h"
#include "macros.h"
extern void ADC_enable(void)
{
set_bit(ADCSRA,ADCSRA_ADEN);
}
extern void ADC_disable(void)
{
	clr_bit(ADCSRA,ADCSRA_ADEN);
}
extern void ADC_start_convertion(void)
{
	set_bit(ADCSRA,ADCSRA_ADSC);
}
extern void ADC_stop_convertion(void)
{
	clr_bit(ADCSRA,ADCSRA_ADSC);
}
extern void ADC_init(struct S_ADC_cofiguration ADC_config)
{
	
	
//------ ------------clock config------------------------------------	
	ADCSRA &=0b11111000;   // clear first 3 bits  ADPS2:0
	ADCSRA |=ADC_config.Clock_selector;  // the enum is arranged with respect to selected clock 
	
	
//---------------auto triggering----------------------------------------------
ADCSRA &=0b11011111; // clear ADATE bit
ADCSRA |=(ADC_config.autoTrigger_enable<<ADCSRA_ADATE);  // enable or disable auto triggering

//-------------------ADC interrupt enable-----------------------------------------------------
ADCSRA &=0b11110111; // clear ADIE bit
ADCSRA |=(ADC_config.Interrupt_Enable<<ADCSRA_ADIE);

//--------------------select channel type and mode single ended or differential etc-----------------------------------------
ADMUX &=0b11100000;   // clear MUX4:0
ADMUX |=(ADC_config.Channels); // no need to shift they are the first 5 bits


//------------------Vref select--------------------------------------
ADMUX &=0b00111111;   // clear REFS1 and REFS0 
ADMUX |=(ADC_config.Vref_selector<<ADMUX_REFS0);  // the enum is arranged with respect to VREF and shifted lift by 6

//--------------bits positioning into ADCL and ADCH---------------------------------------
ADMUX &=0b11011111;   // clear ADLAR
ADMUX |=(ADC_config.Register_Shift<<ADMUX_ADLAR);


//-----------------------triggering source in case of auto triggering enable------------------------------
SFIOR &=0b00011111;
SFIOR |=(ADC_config.Trigger_src<<SFIOR_ADTS0);
//-------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
}
