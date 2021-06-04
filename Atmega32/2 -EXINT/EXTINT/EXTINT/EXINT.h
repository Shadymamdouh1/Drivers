/*
 * EXINT.h
 *
 * Created: 3/31/2021 12:21:59 PM
 *  Author: shady mamdouh
 */ 


#ifndef EXINT_H_
#define EXINT_H_

#define LOW_LEVEL 0
#define Any_logic 1
#define Rising 2
#define Failing 3
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
#define ISC2 6
#define INT1 7
#define INT0 6
#define INT2 5
#define I 7

extern void EXTINT0_init(u8 trigger);
extern void EXTINT1_init(u8 trigger);
extern void EXTINT2_init(u8 trigger); // only rising and failing trigger
extern void EXTINT_Stop(u8 INT_NUM);  // stop all external interrupts
//extern void EXTINT_clr_INTFlag(u8 INT_NUM);  // stop all external interrupts

#endif /* EXINT_H_ */