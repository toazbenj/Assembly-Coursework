/*  ECE 331, BBK library
 *  Michigan State University
 *  Solution file, RGB_LED.c
 *  Created by Sina Parsnejad
 *  Summer 2020
 */

#include "E331KIT.h"
//#include "../../Library/utils.h"  

//initialize GPIOs
void KIT_GPIO_INIT
	(void) 
{ 	
	//initialize port C, D
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	// LED Green
	PORTC->PCR[12] |= PORT_PCR_MUX(1);
	// LED White
	PORTC->PCR[13] |= PORT_PCR_MUX(1);
	//Piezo Buzzer
	PORTD->PCR[0]  |= PORT_PCR_MUX(1);
	// switch 1
	PORTD->PCR[2]  |= PORT_PCR_MUX(1);
	// switch 2
	PORTD->PCR[3]  |= PORT_PCR_MUX(1);
	// IR receiver
	PORTD->PCR[5]  |= PORT_PCR_MUX(1);
	
	// Set up output/input
	PTC->PDDR |= (1UL << 12) | (1UL << 13);  //Port C: 0001 1000 0000 0000 = 1800, outputs on PTC 12 and 13
	PTD->PDDR &= ~0x002C; //Port D: 0000 0000 0000 0010 1100 = 0x0002C, inputs	
	PTD->PDDR |= 0x0001;  //Port D: 0000 0000 0000 0000 0001 = 0x00001, outputs	

}


void KIT_LED_OFF //turn every LED off
	(void) 
{ 	
	PTC->PDOR = 0; // a little too agressive, just nukes the whole Port C PDOR to zero
}
void KIT_WHITE_LED
	(int LED_command) 
{ 
	if (LED_command!=0) //LED_Command determines if we are to set or reset the LED, in this case if it is not 0, we set
	{
	PTC->PDOR |= (1ul << 13); //White LED is on bit 13
	}
	else // LED_command was zero, we turn of white LED
	{
		PTC->PDOR &= ~(1ul << 13);
	}
}
void KIT_GREEN_LED
	(int LED_command) 
{ 
	if (LED_command) //LED_Command determines if we are to set or reset the LED, in this case if it is not 0, we set
	{
	PTC->PDOR |= (1ul << 12);
	}
	else // LED_command was zero, we turn of Green LED
	{
		PTC->PDOR &= ~(1ul << 12);
	}
}

int KIT_READ_SWITCH (int switch_no) //read the switches
{
	if ( PTD->PDIR & (1ul << (1 + switch_no))) //use (1ul << (1 + switch_no)) as a mask. if we are looking for switch 1, then the mask is (1ul << 2), and if we are looking for switch 2, then the mask is (1ul << 3)
	{
		return 1; //PDIR at the mask value is high
	}	
	else
	{
		return 0; //PDIR at the mask value is high
	}
	
	
}



