/*
 * app.c
 *
 *  Created on: 28 Oct 2024
 *      Author: MSI
 *      HMI
 */
#include"../hal/ctrl.h"
#include "../hal/lcd.h"
int main(){
	LCD_init();
	LCD_displayChar('H');
	LCD_displayChar( CTRL_init());
for(;;);
}


