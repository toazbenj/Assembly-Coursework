/*  ECE 331, Lab9, starter file
 *  Michigan State University
 *  Created by Yousef Gtat, 2016
 *	Modified by Sina Parsnejad, 2020
 *	Modified by DraM, 2021
 */
 
#ifndef __RGB_LED__GUARD
#define __RGB_LED__GUARD

#include <MKL25Z4.h>    // Device header for PRC

/* Declaring enum RGB type */
enum RGB_t
{
	Red,
	Green,
	Blue,
	Yellow,
	Cyan,
	Magenta,
	White,
	Off
};

/****************************INIT*******************************/
void RGBLED_INIT
	(void);
/****************************API********************************/
void RED_LED_ON
	(void);
void GREEN_LED_ON
	(void);
void BLUE_LED_ON
	(void);
void LEDS_OFF
    (void);
void SET_RGB_RED
    (void);
void SET_RGB_GREEN
    (void);
void SET_RGB_BLUE
    (void);
void SET_RGB_YELLOW
    (void);
void SET_RGB_CYAN
    (void);
void SET_RGB_MAGENTA
    (void);
void SET_RGB_WHITE
    (void);
void SET_COLOR (enum RGB_t RGB_STATE);
/*****************************************************************************
     A D V A N C E D   L E D   F U N C T I O N S
*****************************************************************************/	 
void colorfrac
	(enum RGB_t Color1, enum RGB_t Color2, int Frac1, int Time); 
void colorsweep 
	(enum RGB_t Color1, enum RGB_t Color2, int Time);

/*******************************END**************************/

#endif /* __RGB_LED__GUARD */

