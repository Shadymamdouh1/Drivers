/*
 * macros.h
 *
 * Created: 3/31/2021 12:57:01 AM
 *  Author: shady mamdouh
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#define set_bit(value,bit)  value|=(1<<bit)
#define clr_bit(value,bit)  value&=~(1<<bit)
#define toggle_bit(value,bit)  value^=(1<<bit)
#define get_bit(value,bit)  (1&(value>>bit))



#endif /* MACROS_H_ */