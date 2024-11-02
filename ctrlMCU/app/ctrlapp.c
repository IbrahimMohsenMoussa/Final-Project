#include"../hal/hmi.h"
#include "../hal/lcd.h"
#include "../hal/external_eeprom.h"

#include<util/delay.h>

int main() {
	LCD_init();
	HMI_init();
	uint8 *l_ptr2pass;
	for (;;) {
		/* Wait for command from HMI */
		uint8 l_receivedCommand = HMI_ready();

		switch (l_receivedCommand) {
		case HMI_WAIT_PASS:
			l_ptr2pass = HMI_checkPassMatch();
			if (l_ptr2pass != NULL_PTR) {
				MEM_savePass(l_ptr2pass);
				l_ptr2pass = NULL_PTR;
			}
			LCD_moveCursor(0, 0);
			for (uint8 i = 0; i < 5; i++)

			{
				LCD_intgerToString(MEM_getPassElem(i));

			}

			break;
		case HMI_WAIT_PASS_MEM:
			HMI_checkPass();

			break;

		default:
			LCD_displayStringRowColumn(0, 0, "Unknown Command");
			break;
		};
	}
}

