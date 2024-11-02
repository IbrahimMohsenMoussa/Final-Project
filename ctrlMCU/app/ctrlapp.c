#include"../hal/hmi.h"
#include "../hal/lcd.h"
#include "../hal/external_eeprom.h"

#include<util/delay.h>
void MEM_savePass(uint8 *a_pass);
uint8 MEM_getPassElem(uint8 a_passIndex);
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
		default:
			LCD_displayStringRowColumn(0, 0, "Unknown Command");
			break;
		};
	}
}
uint8 MEM_getPassElem(uint8 a_passIndex) {
	uint8 byte;

	EEPROM_readByte(0xf + a_passIndex, &byte);
	return byte;

}
void MEM_savePass(uint8 *a_pass) {

	for (uint8 i = 0; i < 5; i++) {
		EEPROM_writeByte(0xf + i, a_pass[i]);
		_delay_ms(10);
	}
}
