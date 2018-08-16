#include <LPC23xx.H>                    /* LPC23xx definitions                */

#include "Timer.h"

unsigned int timer_iteration = 0;
int timer_flag;
short int AD_last;
long sum;
long Rsum;

void Timer1_Init(void)
{
	VICVectAddr5 = (unsigned long) Timer1_Handler;		//points to timer 1 interrupt handler
	T1MCR |= 0x01;				//Interrupt on MR0 
	TIMER1_INT_ENABLE;		//interrupt timer1 interrupt
}

void Timer1_SetMR0(unsigned long value)
{
	T1MR0 = value;
}

__irq void Timer1_Handler(void)
{
	AD_last = AD0DR0 >> 6;     //Shifting value in AD0DR0 by 6 bit 
	AD_last &= 0x000003FF;     //reading the 7th and 6th bit of AD0R0
	
	Rsum = Rsum + AD_last;
	T1TCR = 0x02;		//reset timer counter
	
	timer_iteration++;
	if (timer_iteration == 10000)
	{
		sum = Rsum;
		Rsum = 0;
	}
	AD0CR |= 0x01000000;		//start conversion
	T1IR  = 0x01;		//reset interrupt flag	
	VICVectAddr = 0;	//Acknowledge interrupt
	T1TCR = 0x01;		//Start timer
	timer_flag = 1;
}
