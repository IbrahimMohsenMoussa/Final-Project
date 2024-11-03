#include "../hal/ctrl.h"
#include "../hal/lcd.h"
#include "../hal/keypad.h"
#include<util/delay.h>
void Get_password(uint8 a_pass[]);

typedef enum {
	SET_PASSWORD, OPEN_DOOR, CLOSEDOOR, ALERT, IDLE, CHANGE_PASSWORD
} STATEMACHINE;

uint8 g_stateMachine = SET_PASSWORD;
uint8 Check_password();
int main() {
	uint8 trys = 0;
	LCD_init();
	CTRL_init();

	for (;;) {

		switch (g_stateMachine) {
		case SET_PASSWORD:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Enter Pass:");

			uint8 l_1stInpass[6] = { 0 };
			uint8 l_2ndInpass[6] = { 0 };

			/* Capture the first password */
			Get_password(l_1stInpass);

			/* Confirm and re-enter password */
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Re-enter Pass:");
			Get_password(l_2ndInpass);

			/* Send and check passwords */
			if (CTRL_checkPassMatch(l_1stInpass, l_2ndInpass) == HMI_PASSMATCH) {
				g_stateMachine = IDLE;
				LCD_displayString("Pass match!");

			} else {
				LCD_clearScreen();
				LCD_displayString("Pass Mismatch!");
				LCD_displayStringRowColumn(0, 0, "Retry");
				_delay_ms(500);
			}
			break;
		case IDLE:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "+ : Open Door");
			LCD_displayStringRowColumn(1, 0, "- : Change Pass");
			uint8 idle_key = KEYPAD_getPressedKey(20);
			if (idle_key == '+') {
				g_stateMachine = OPEN_DOOR;
			} else if (idle_key == '-') {
				g_stateMachine = CHANGE_PASSWORD;
			}
			break;
		case OPEN_DOOR:
			if (trys >= 3) {
				g_stateMachine = ALERT;
				trys = 0;
				break;
			}
			if (Check_password() == HMI_PASSMATCH) {
				LCD_clearScreen();
				LCD_displayString("OPENING DOOR!");
				CTRL_openDoor();
				trys = 0;
				g_stateMachine = IDLE;
			} else {
				LCD_clearScreen();
				LCD_displayString("WRONG PASSWORD");
				trys++;
			}
			break;
		case ALERT:
			LCD_clearScreen();
			LCD_displayString("-----HARAMY-----");
			break;
		default:
			LCD_displayStringRowColumn(0, 0, "Invalid State");
			break;
		}
	}
}

/* Captures a 5-character password and stores it in a_pass */
void Get_password(uint8 *a_pass) {
	a_pass[5] = '\0';  // Null-terminate the password string

	uint8 l_key = 'N';
	for (uint8 i = 0; i < 5; i++) {
		/* Wait for a valid key press */
		while (l_key == 'N' || l_key > 9) {
			l_key = KEYPAD_getPressedKey(1);
		}

		/* Store the new key press and display '*' */
		a_pass[i] = l_key;
		LCD_moveCursor(1, i + 11);  // Adjust position if necessary
		LCD_displayChar('*');

		l_key = 'N';  // Reset l_key for the next input
	}
}
uint8 Check_password() {
	uint8 l_pass[6];
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Enter Pass:");
	Get_password(l_pass);
	return CTRL_checkPass(l_pass);

}
