/*  Lava Lamp Continued
 *	// Pin PTB18 is Red
 *	// Pin PTB19 is Green
 *	// Pin PTD1  is Blue 
*/
 #include "../../Library/FRDMRGBLED.h"
 #include "../../Library/E331KIT.h"
 #include "../../Library/utils.h"

enum RGB_t my_state = Red;

 int main (void)
 {
	RGBLED_INIT();
	KIT_GPIO_INIT();
	 
	while(1){
			switch (my_state)
			{
			case Red:
				SET_COLOR(Red);
				delay(2);
				if(!KIT_READ_SWITCH(1)){
					my_state = Yellow;
				}
				else{
					my_state = Magenta;
				}
				break;
				
			case Yellow:
				SET_COLOR(Yellow);
				delay(2);
				if(!KIT_READ_SWITCH(1)){
					my_state = Green;
				}
				else{
					my_state = Red;
				}
				break;
			case Green:
				SET_COLOR(Green);
				delay(2);
				if(!KIT_READ_SWITCH(1)){
					my_state = Cyan;
				}
				else{
					my_state = Yellow;
				}
				break;
			case Cyan:
				SET_COLOR(Cyan);
				delay(2);
				if(!KIT_READ_SWITCH(1)){
					my_state = Blue;
				}
				else{
					my_state = Green;
				}
				break;
			case Blue:
				SET_COLOR(Blue);
				delay(2);
				if(!KIT_READ_SWITCH(1)){
					my_state = Magenta;
				}
				else{
					my_state = Cyan;
				}
				break;
			case Magenta:
				SET_COLOR(Magenta);
				delay(2);
				if(!KIT_READ_SWITCH(1)){
					my_state = Red;
				}
				else{
					my_state = Blue;
				}
				break;
		}
	}
	
	 return 0;
 }
 