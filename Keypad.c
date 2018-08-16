/* Keypad scan code for 4x4 keypad
	r1		1		2		3		A
	r2		4		5		6		B
	r3		7		8		9		C
	r4		*		0		#		D
		   c1		c2	c3 	c4
	Written by Sarah Ngo
	April 2017 */

#include <LPC23xx.H>                    /* LPC23xx definitions */
#include "Keypad.h"

char key;

void GPIO4_init (void)
{
	PINSEL8 = 0;					//setting P4.15 ... P4.0 as GPIO
	FIO4DIR0 = 0xF0;			//setting P4.7 ... P4.4 as output, P4.3 ... P4.0 as input
	FIO4PIN0 = 0x00;			//output low to P4.7 ... P4.0
}

void delay (void)			/*delay function*/
{
	int delay = 20;
	while (delay > 0)
	{
		delay--;
	}
}

void get_key (void)
{
	int row;
	int column; 
	
	int d = 2000;
	
	while (d > 0)
	{d--;}
	
	column = FIO4PIN0;		//read the columns
	
	switch (column)
	{
		case 0x07: 	//column 1 cases
			FIO4PIN0 = 0xE0; delay();	//check row 1
			row = FIO4PIN0;
			if (row == 0xE7){ key = '1'; break;}
				
			FIO4PIN0 = 0xD0; delay(); //check row 2
			row = FIO4PIN0;
			if (row == 0xD7){ key = '4'; break;}
			
			FIO4PIN0 = 0xB0; delay();  //check row 3
			row = FIO4PIN0;
			if (row == 0xB7){ key = '7'; break;}
			
			FIO4PIN0 = 0x70; delay();	//check row 4
			row = FIO4PIN0;
			if (row == 0x77){ key = '*'; break;}
			
		case 0x0B: 	//column 2 cases
			FIO4PIN0 = 0xE0; delay();	//check row 1
			row = FIO4PIN0;
			if (row == 0xEB){ key = '2'; break;}
				
			FIO4PIN0 = 0xD0; delay(); //check row 2
			row = FIO4PIN0;
			if (row == 0xDB){ key = '5'; break;}
			
			FIO4PIN0 = 0xB0; delay();  //check row 3
			row = FIO4PIN0;
			if (row == 0xBB){ key = '8'; break;}
			
			FIO4PIN0 = 0x70; delay();	//check row 4
			row = FIO4PIN0;
			if (row == 0x7B){ key = '0'; break;}
		
		case 0x0D: 	//column 3 cases
			FIO4PIN0 = 0xE0; delay();	//check row 1
			row = FIO4PIN0;
			if (row == 0xED){ key = '3'; break;}
				
			FIO4PIN0 = 0xD0; delay(); //check row 2
			row = FIO4PIN0;
			if (row == 0xDD){ key = '6'; break;}
			
			FIO4PIN0 = 0xB0; delay();  //check row 3
			row = FIO4PIN0;
			if (row == 0xBD){ key = '9'; break;}
			
			FIO4PIN0 = 0x70; delay();	//check row 4
			row = FIO4PIN0;
			if (row == 0x7D){ key = '#'; break;}
		
		case 0x0E: 	//column 4 cases
			FIO4PIN0 = 0xE0; delay();	//check row 1
			row = FIO4PIN0;
			if (row == 0xEE){ key = 'A'; break;}
				
			FIO4PIN0 = 0xD0; delay(); //check row 2
			row = FIO4PIN0;
			if (row == 0xDE){ key = 'B'; break;}
			
			FIO4PIN0 = 0xB0; delay();  //check row 3
			row = FIO4PIN0;
			if (row == 0xBE){ key = 'C'; break;}
			
			FIO4PIN0 = 0x70; delay();	//check row 4
			row = FIO4PIN0;
			if (row == 0x7E){ key = 'D'; break;}
		}

		FIO4PIN0 = 0;
}
