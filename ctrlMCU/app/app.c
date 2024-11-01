/*
 * app.c
 *CTRL
 *  Created on: 28 Oct 2024
 *      Author: MSI
 */

#include"../hal/hmi.h"
#include "../hal/lcd.h"
int main(){
LCD_init();
HMI_init();
for(;;);
}


