/* Blink*/

#include "../../Library/E331KIT.h"
#include "../../Library/utils.h"

/* include utils above */

int main (void)
{
	/* Initialize ECE331 Kit */
	KIT_GPIO_INIT();
	
	while (1) {
		KIT_WHITE_LED(0);
		delay(1);
		KIT_WHITE_LED(1);
		delay(1);
	}

	return 0;
}
