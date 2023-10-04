/*  ECE 331, Lab9
 *  Michigan State University
 *  Created by Yousef Gtat, 2016
 *	Modified by Sina Parsnejad, 2020
 *	Modified by DraM, 2021
 *  Contains skeleton functions to configure FRDM KL25Z on-board RGB LED
 *	and set the RGB LED to all color options
 *	/////// FRDM KL25Z on-board LED pins ///////
 *	// Pin PTB18 is Red
 *	// Pin PTB19 is Green
 *	// Pin PTD1  is Blue 
 */

#include "FRDMRGBLED.h"

/******************Configuration for FRDM KL25Z RGB LED*********************/
////////////// Set RGBLED pins to GPIO function
void RGBLED_to_GPIO	(void)
{
	// Implements read-modify-write by only changing bits in MUX field
	// First, clear (000) MUX, then set MUX to 001, for each pin
	PORTB->PCR[18] &= ~(7UL <<  8);  // clear MUX
	PORTB->PCR[18] |= (1UL <<  8);  // Pin PTB18 is GPIO
	PORTB->PCR[19] &= ~(7UL <<  8);  // clear MUX
  PORTB->PCR[19] |= (1UL <<  8);  // Pin PTB19 is GPIO  
	PORTD->PCR[1]  &= ~(7UL <<  8);  // clear MUX
	PORTD->PCR[1]  |= (1UL <<  8);  // Pin PTD1  is GPIO
}

////////////// Initialize RGBLED GPIO pins
void RGBLED_INIT (void) 
{
  /* 1- CLOCK ENABLE
	 *    Enable the System Clock to PORT B 
	 *    Enable the systim clock to PORT D 
	 *    Use read-modify-write to not overwrite the other port clocks
	 */
	/*********** YOUR CODE HERE *************/
	SIM->SCGC5 = (1<<10)|(1<<12);

	
  /* 2- SET GPIO FUNCTION
	 *    Define Port B & D specific pin function to act as GPIO 
	 */
	/*********** YOUR CODE HERE *************/
	RGBLED_to_GPIO();
 
 
 /* 3- DATA DIRECTION 
	*    Configure Port B Data Direction to be outputs
	*    Configure Port D Data Direction to be outputs
	*/  	
	/*********** YOUR CODE HERE *************/

	PTB->PDDR |= (3<<18);
	PTD->PDDR |= (1<<1);

}

/********************API for FRDM KL25Z RGB LED***********************/
////////////// Use to turn Red LED on
void RED_LED_ON (void) 
{
  // Turn the red LED on -- Clear Pin B18
		 PTB->PDOR &= ~(1<<18);

}

////////////// Use to turn Green LED on/off
void GREEN_LED_ON (void) 
{
  // Turn the green LED on -- Clear Pin B19
		 PTB->PDOR &=~(1<<19);

}

////////////// Use to turn Blue LED on/off
void BLUE_LED_ON (void) 
{
  // Turn the blue LED on -- Clear Pin D1 
		 PTD->PDOR &=~(1<<1);
}

////////////// Use to turn ALL LEDs off
void LEDS_OFF (void) 
{
  // Turn the red, green and blue LEDs off -- Set Pins B18, B19, D1  
  // Turn the red LED off -- Set Pin B18
  	PTB->PDOR |=(1<<18);
  // Turn the green LED off -- Set Pin B19
		 PTB->PDOR |=(1<<19);
  // Turn the blue LED off -- Set Pin D1
		 PTD->PDOR |=(1<<1);

}

////////////// Use to set the RGB LED to red
void SET_RGB_RED (void) 
{
  // Turn All off, Turn Red on
		LEDS_OFF();
		RED_LED_ON();	
}

////////////// Use to set the RGB LED to green
void SET_RGB_GREEN (void) 
{
   // Turn All off, Turn Green on	
		LEDS_OFF();
		GREEN_LED_ON();  
}

////////////// Use to set the RGB LED to blue
void SET_RGB_BLUE (void) 
{
  // Turn All off, Turn Blue on	
		LEDS_OFF();
		BLUE_LED_ON();	
}
////////////// Use to set the RGB LED to yellow
void SET_RGB_YELLOW (void) 
{
  // Turn ONLY the red and green LEDs on
	GREEN_LED_ON();
	RED_LED_ON();
}

////////////// Use to set the RGB LED to cyan
void SET_RGB_CYAN (void) 
{
  // Turn ONLY the green and blue LEDs on
	GREEN_LED_ON();
	BLUE_LED_ON();
}

////////////// Use to set the RGB LED to magenta
void SET_RGB_MAGENTA (void) 
{
  // Turn ONLY the red and blue LEDs on
	RED_LED_ON();
	BLUE_LED_ON();
}

////////////// Use to set the RGB LED to white
void SET_RGB_WHITE (void) 
{
  // Turn the red, green and blue LEDs on
	GREEN_LED_ON();
	BLUE_LED_ON();
	RED_LED_ON();
}

////////////// Use to set RGB LED color using RGB_t enum
void SET_COLOR (enum RGB_t RGB_STATE)
{
	switch (RGB_STATE)
	{
		case Red:
			SET_RGB_RED();
		break;
		case White:
			SET_RGB_WHITE();
		break;
		case Magenta:
			SET_RGB_MAGENTA();
		break;
		case Blue:
			SET_RGB_BLUE();
		break;
		case Cyan:
			SET_RGB_CYAN();
		break;
		case Green:
			SET_RGB_GREEN();
		break;
		case Yellow:
			SET_RGB_YELLOW();
		break;
		case Off:
			LEDS_OFF();
		break;
		
	}
}
/***********************end***********************/

/*****************************************************************************
     A D V A N C E D   L E D   F U N C T I O N S
*****************************************************************************/	 
/****************************************************************************
 Functions for fractional color control of RGB LEDs
 KL25Z defaults to 20971520 Hz clock (~21M cycles per second)
 Human vision speed ~60Hz, so each color is composed within 1/100th sec
   thus, for 100 color spectrum, each color "piece" should hold for 1/10,000th sec
	 each color is composed of R/G/B fractions within the 100 "pieces" of spectrum
 Assume minimum time to hold any color is 1/10sec, 10 cycles of a color-fraction
 */

////// colorfract, Set fractional color of 2 RGB LEDs for Time tenths of sec
// Colorx defined by enumb RGB_t {Red, Green, Blue, Yellow, Cyan, Magenta, White, Off}
// Frac1 = fraction of cycle (0-100) at color1
// fraction of cycle at color2 = 100 - frac1
// Time = time at color fraction, in units of 10ths of seconds
void colorfrac
	(enum RGB_t Color1, enum RGB_t Color2, int Frac1, int Time) 
{
	int y=0; //cycles at same color
	int tt = 10*Time;
	int j; //loops per color fraction
	volatile int  i; //delay loop variable	
	
	LEDS_OFF();
  
	while (y<tt)  //hold each color Time x 10 cycles, 10 cycles take 1/10sec
		{	
				SET_COLOR (Color1);
				for (j=0; j<Frac1; j++) 								 	//hold color1 for frac1
						{ for (i= 20971520/50000; i>0; i--); //delay for 1/10000 seconds		
						}
				LEDS_OFF(); //turn off first color
				SET_COLOR (Color2);
				for (j=Frac1; j<100; j++) 								 	//hold color2 for 100-frac1
						{ for (i= 20971520/50000; i>0; i--); //delay for 1/10000 seconds		
						}
				LEDS_OFF();
				y=y+1;
		}
}

///// colorsweept, Sweeps fractionally from RGB color1 to RGB color2 over Time (in tenths of seconds)
// Colorx defined by enumb RGB_t {Red, Green, Blue, Yellow, Cyan, Magenta, White, Off}
// Each color held for 1/10sec by colorfrac function, so miniumu time is 1/10 sec
// Max sweep time is 10 sec (Time = 100)
void colorsweep (enum RGB_t Color1, enum RGB_t Color2, int Time)
{
	int j; //steps at variable color fractions
	int tt = 100/Time;

	LEDS_OFF();
	for (j=100; j>0; j=j-tt) 				//vary color fraction from tt to 0, steps of 2
			{ colorfrac (Color1, Color2, j, 1);  		
			}
}



