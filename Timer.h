#ifndef _TIMER_H_
#define _TIMER_H_

#define TIMER1_ENABLE				(T1TCR = 0x01)
#define TIMER1_INT_ENABLE		(VICIntEnable |= 1 << 5)

extern unsigned int timer_iteration;
extern int timer_flag;
extern long sum;

extern __irq void Timer1_Handler(void);

void Timer1_Init(void);
void Timer1_SetMR0(unsigned long value);

#endif
