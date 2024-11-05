/*
 * pir.c
 *
 *  Created on: 5 Nov 2024
 *      Author: MSI
 */
#include"../mcal/gpio.h"
#include"pir.h"
void PIR_init(){
GPIO_ARR_setPinDirection(PIR_PIN,PIN_INPUT);

}
uint8 PIR_read(){
	return GPIO_ARR_readPin(PIR_PIN);
}
