/* Keypad header file
Written by Sarah Ngo
April 2017 */

#ifndef Keypad
#define Keypad

#include "EINT0.h"

void GPIO4_init (void);		//sets port 4 as GPIO
void get_key (void);				//scans keypad to determine key pressed
void delay (void);							//short delay to allow updating of pins
extern char key;

#endif
