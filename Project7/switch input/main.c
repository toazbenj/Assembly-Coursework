/* Switch Input*/

#include "../../Library/E331KIT.h"
#include "../../Library/utils.h"

	/* Declare Global Variables Here */
int switch1_status = 0;
int switch1_last_status = 0;

int main (void)
{
	/* We Initialize ECE331Kit here */
	KIT_GPIO_INIT();
	switch1_status = KIT_READ_SWITCH (1);
	switch1_last_status = switch1_status;
	
	/* Student code goes here */
	while(1){
		switch1_status = KIT_READ_SWITCH (1);
		if (switch1_status != switch1_last_status) {
			KIT_WHITE_LED(1);
			delay(1);
			KIT_WHITE_LED(0);
			delay(1);
		}
		
		switch1_last_status = switch1_status;
	}

	return 0;
}
