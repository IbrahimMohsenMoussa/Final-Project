#include"../hal/hmi.h"
#include "../hal/lcd.h"
#include "../hal/external_eeprom.h"
#include "../hal/dcMotor.h"
#include<util/delay.h>

int main() {
	LCD_init();
	HMI_init();
	DcMotor_init();
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
		case HMI_OPEN_DOOR:
			OpenDoor();
			break;
		case HMI_CLOSE_DOOR:
			CloseDoor();
			break;
		default:
			LCD_displayStringRowColumn(0, 0, "Unknown Command");
			break;
		};
	}
}

