/*
 * app.c
 *
 *  Created on: 28 Oct 2024
 *      Author: MSI
 *      HMI
 */
#include"../hal/ctrl.h"
#include "../hal/lcd.h"
#include "../hal/keypad.h"

void Get_password(uint8 a_pass[]);
typedef enum {
	SET_PASSWORD, OPEN_DOOR, CLOSEDOOR, ALERT
} STATEMACHINE;
uint8 g_stateMachine = SET_PASSWORD;
int main() {

	LCD_init();
	CTRL_init();

	for (;;) {
		switch (g_stateMachine) {
		case SET_PASSWORD:
			LCD_displayStringRowColumn(0, 0, "Plz Enter Pass");
			uint8 l_1stInpass[6];
			uint8 l_2ndInpass[6];
			Get_password(l_1stInpass);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "plz re-enter the");
			LCD_displayStringRowColumn(1, 0, "same pass");
			Get_password(l_2ndInpass);

			LCD_clearScreen();
			LCD_moveCursor(0, 0);

			uint8 *ptr = l_1stInpass;
			while (*ptr!='\0') {
				LCD_intgerToString(*ptr);
				ptr++;
			}

			LCD_moveCursor(1, 0);
			 ptr = l_2ndInpass;
			while (*ptr!='\0') {
				LCD_intgerToString(*ptr);
				ptr++;
			}
			 CTRL_checkPass(l_1stInpass, l_2ndInpass);
			g_stateMachine++;

			break;
		};

	}
}

void Get_password(uint8 *a_pass) {
	a_pass[5] = '\0';
	uint8 l_key = KEYPAD_getPressedKey(1);
	while (l_key == 'N'|| l_key>9) {
		l_key = KEYPAD_getPressedKey(1);
	}
	/* Store the first pressed key in the password array */
	a_pass[0] = l_key;
	l_key = 'N'; // Reset l_key for the next input
	LCD_moveCursor(1, 11);
	LCD_displayChar('*'); // Display * for the first character
	/* Loop to capture the remaining 4 characters of the password */
	for (uint8 i = 1; i < 5; i++) {
		/* Wait until a new key is pressed */
		while (l_key == 'N'|| l_key>9) {
			l_key = KEYPAD_getPressedKey(1);
		}

		/* Store the new key press and reset l_key for the next loop iteration */
		a_pass[i] = l_key;
		LCD_moveCursor(1, i + 11);
		LCD_displayChar('*'); // Display * instead of showing the actual digit

		/* Reset l_key to prevent duplicate entries for the same key press */
		l_key = 'N';
	}
}
