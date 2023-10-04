/*Main source file
* Proximity sensor with indicator light and alarm
*/
#include "../../Library/E331KIT.h"
#include "../../Library/utils.h"

int sensor_state = 0;

int main()
{
	/* We Initialize ECE331Kit and PORTC and PORTD GPIOs here */
	KIT_GPIO_INIT();
	
	while (1)
	{

//		KIT_WHITE_LED(1);
//		delay_ms(1);
//		KIT_WHITE_LED(0);
//		delay_ms(1);
		
//		KIT_WHITE_LED(1);
//	  	delay_us(1);
//		KIT_WHITE_LED(0);
//		delay_us(1);



//		sensor_state = PTD->PDIR;
//		sensor_state &= ~00100000;
		if(~(PTD->PDIR)&(1<<5)){
		KIT_WHITE_LED(1);
		}
		else{
		KIT_WHITE_LED(0);
		}

// 		PTD->PDOR &= 0;
//		delay_ms(10); 
//		PTD->PDOR |= 1;
// 		delay_ms(10); 

// 		//IR transceiver high when inactive, low when sensing
// 		sensor_state = PTD->PDIR;
// 		sensor_state &= 0010000;

		//buzz-sensor low
			if(~(PTD->PDIR)&(1<<5)){
			KIT_GREEN_LED(1);
			KIT_WHITE_LED(1);

			PTD->PDOR &= 0;
			delay_ms(10); 
			PTD->PDOR |= 1;
			delay_ms(10); 
		}
		//no buzz-sensor high
 		else{
 			PTD->PDOR |= 1;
 			KIT_GREEN_LED(1);
 			KIT_WHITE_LED(0);
 			delay_ms(50);
 			KIT_GREEN_LED(0);
 			KIT_WHITE_LED(1);
 			delay_ms(50);
 		}

	}
		
}
