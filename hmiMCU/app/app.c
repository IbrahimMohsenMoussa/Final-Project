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
uint8 g_stateMachine=0;
int main(){

	LCD_init();
	CTRL_init();
	uint8 l_key;
	   LCD_displayString("plz enter pass");
for(;;){


	l_key=KEYPAD_getPressedKey(1);
	LCD_moveCursor(1,0);
	l_key!='N'? LCD_intgerToString (l_key): LCD_intgerToString(10);

}
}


