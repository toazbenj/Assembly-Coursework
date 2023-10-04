/*  LED and GPIO Functionality Integration 
 *  Lava lamp (drug trip) 
 *	// Pin PTB18 is Red
 *	// Pin PTB19 is Green
 *	// Pin PTD1  is Blue 
*/
 #include "../../Library/FRDMRGBLED.h"
 #include "../../Library/E331KIT.h"
 #include "../../Library/utils.h"



 int main (void)
 {
	 RGBLED_INIT();
	 KIT_GPIO_INIT();
	 
		 PTB->PDOR |=(1<<18);
		 PTB->PDOR |=(1<<19);
		 PTD->PDOR |=(1<<1);
	 
//	 while(1){
//		 //RED BLINK
//		 PTB->PDOR &= ~(1<<18);
//		 delay(1);
//		 PTB->PDOR |=(1<<18);
//		 delay(1);

//		 //GREEN BLINK
//		 PTB->PDOR &=~(1<<19);
//		 delay(1);
//		 PTB->PDOR |=(1<<19);
//		 delay(1);

//		 //BLUE BLINK
//		 PTD->PDOR &=~(1<<1);
//		 delay(1);
//		 PTD->PDOR |=(1<<1);
//		 delay(1);

//	 }
	 
//	 while(1){
//		 SET_RGB_BLUE();
//		 delay(1);
//		 LEDS_OFF();
//		 delay(1);
//		 
//		 SET_RGB_CYAN();
//		 delay(1);
//		 LEDS_OFF();
//		 delay(1);
//		 
//		 SET_RGB_GREEN();
//		 delay(1);
//		 LEDS_OFF();
//		 delay(1);
//		 
//		 SET_RGB_YELLOW();
//		 delay(1);
//		 LEDS_OFF();
//		 delay(1);
//		 
//		 SET_RGB_RED();
//		 delay(1);
//		 LEDS_OFF();
//		 delay(1);
//		 
//		 SET_RGB_MAGENTA();
//		 delay(1);
//		 LEDS_OFF();
//		 delay(1);
//		 
//		 SET_RGB_WHITE();
//		 delay(1);
//		 LEDS_OFF();
//		 delay(1);
//	 }

	while(1){
		SET_COLOR(White);
		delay(1);
		
		SET_COLOR(Magenta);
		delay(1);

		SET_COLOR(Blue);
		delay(1);

		SET_COLOR(Cyan);
		delay(1);

		SET_COLOR(Green);
		delay(1);

		SET_COLOR(Yellow);
		delay(1);

		SET_COLOR(Red);
		delay(1);
		
		SET_COLOR(Off);
		delay(1);
	}
	 return 0;
 }
