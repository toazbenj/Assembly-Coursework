/*  ECE 331, BBK library
 *  Michigan State University
 *  Solution file, RGB_LED.c
 *  Created by Sina Parsnejad
 *  Summer 2020
 */
 
#ifndef __BBK_lib__GUARD
#define __BBK_lib__GUARD

#include <MKL25Z4.h>    // Device header for PRC


/****************************API********************************/


void KIT_GPIO_INIT
	(void);
void KIT_LED_OFF
	(void);
void KIT_WHITE_LED
	(int LED_command); 
void KIT_GREEN_LED
	(int LED_command);
int KIT_READ_SWITCH
	(int switch_no);


/*******************************END**************************/

#endif /* __BBK_lib__GUARD */

