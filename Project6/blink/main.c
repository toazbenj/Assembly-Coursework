/* Blinking LED functions
 */

#include <MKL25Z4.h>    // holds KL25Z struct declarations
#include "../../Library/utils.h"
//#include "../Library/utils.h"

void Blue_init (void);

void Blue_init (void) 
{ 	
	// FRDM-KL25Z onboard RGB Blue light is on PTD1
	// Enable Clock to PTD, bit 12 of SCGCS5 Register
  	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
  //MUX set PTD1 pins to GPIO function
		PORTD->PCR[1]  = (1U << PORT_PCR_MUX_SHIFT);  // Pin PTD1  is GPIO
	
		PTD->PDDR |= (1U << 1);
}

int main (void)
{
	Blue_init();
	while (1)
	{
	//Set PTD1 output to 1; turns LED Off
	PTD->PSOR |=  (1U << 1);

	delay(1);
		
	//Set PTD1 output to 0; turns LED On
	PTD->PCOR |=  (1U << 1);
	delay(1);
	
	}
		return 0;
}
	
