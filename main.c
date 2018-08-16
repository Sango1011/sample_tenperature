/* main program 
	written by Sarah Ngo
	April 2017 */
	
#include <stdio.h>
#include <LPC23xx.H>                    /* LPC23xx definitions */

#include "LED.h"
#include "Timer.h"
#include "LCD.h"
#include "Uart1Tx.h"
#include "Keypad.h"
#include "adc.h"
#include "EINT0.h"

int main ()
{
	char value[10];
	char valueF[10];
	int star_flag, LED_flag;
	short LED_1 = 0x80;
	short LED_0 = 0x7F;
	short LED = 0x00;
	float average;
	
	
	//initializtions
	adc_init();	
	LED_Init();
	GPIO4_init();
	lcd_init();
	Timer1_Init();
	Uart1_init();
	EINT0_init();

	
	lcd_clear();
	set_cursor(0,0);
	lcd_print("    ECE 323");
	set_cursor (0,1);
	lcd_print ("   Sarah Ngo");
	
	sendString("     Sarah Ngo. \n\r");
	sendString("ECE 323 - Final Project \n\r");
	sendString("------------------------- \n\r");
		
 while(1)
 {
		while (key != '#')
		{		
			if (key == '*')			//ask the user for the sampling rate
			{
					T1TCR = 0x00;			//stop timer
					star_flag = 1;
					lcd_clear();
					set_cursor (0,0);
					lcd_print (" Please select");
					set_cursor (0,1);
					lcd_print (" 1, 2, 3, or 4");
					key = '0';
			}
			if (star_flag == 1)
			{				
					if (key == '1')
					{
						T1TCR = 0x02;		//reset timer counter
						Timer1_SetMR0(50);		//match register
						TIMER1_ENABLE;				//Start timer
						key = '0';	
						star_flag = 0;
						timer_iteration = 0;
					}
					else if (key == '2')
					{
						T1TCR = 0x02;		//reset timer counter
						Timer1_SetMR0(530);		//match register
						TIMER1_ENABLE;				//Start timer
						key = '0';
						star_flag = 0;
						timer_iteration = 0;
					}
					else if (key == '3')
					{
						T1TCR = 0x02;		//reset timer counter
						Timer1_SetMR0(1130);		//match register
						TIMER1_ENABLE;				//Start timer
						//serial_char = '0';
						star_flag = 0;
						timer_iteration = 0;
					}
					else if (key == '4')
					{
						T1TCR = 0x02;		//reset timer counter
						Timer1_SetMR0(11950);		//match register
						TIMER1_ENABLE;				//Start timer
						key = '0';
						star_flag = 0;
						timer_iteration = 0;
					}
			}

			if (timer_iteration >= 10000)		//after 10,000 readings average and display
			{	
				average = sum/10000;
				lcd_clear();
				sprintf(value, "%.2fC", average*0.32226+2);
				sprintf(valueF, "%.2fF", (average*0.32226+2)*9/5 + 32);
				set_cursor(0,0);				
				lcd_print(value);
				set_cursor(0,1);
				lcd_print(valueF);
				sendString(value);
				sendString("\n\r");
				sendString(valueF);
				sendString("\n\r");
				sendString("-----------\n\r");
				LED = AD_last;
				if (LED_flag == 0)
				{
					LED |= LED_1;
					LED_flag = 1;
				}
				else
				{
					LED &= LED_0;
					LED_flag = 0;
				}
				LED_Out(LED);
				timer_iteration = timer_iteration - 10000;		//reset counter
				average = 0;
				sum = 0;
			}		
		}	
		if (key == '#')
		{
			lcd_clear();			//clear lcd
			LED_Out(0x00);		//turn off LED
			T1TCR = 0x00;			//stop timer
			T1TCR = 0x02;		//reset timer counter
			average = 0;
			sum = 0;
			timer_iteration = 0;		//reset counter
		}
	}
}
