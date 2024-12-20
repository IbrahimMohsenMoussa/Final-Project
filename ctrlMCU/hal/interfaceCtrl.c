/*
 * hmi.c
 *
 *  Created on: 30 Oct 2024
 *      Author: MSI
 *      CTRL MCU
 */

#include "interfaceCtrl.h"

#include "../mcal/uart.h"
#include "../mcal/twi.h"
#include"lcd.h"
#include"dcMotor.h"
#include<util/delay.h>
#include "../hal/external_eeprom.h"
#include"pir.h"
uint8 g_pass[6];
static uint8 Encrypt(uint8 a_num);
static uint8 Decrypt(uint8 a_num);
static void HMI_recievePassword(uint8 *a_pass) {
	uint8 i = 0;
	a_pass[i] = UART_receiveByte();
	UART_sendByte(HMI_ACK);
	i++;
	while (i < 5) {

		a_pass[i] = UART_receiveByte();
		UART_sendByte(HMI_ACK);
		i++;
	}
	a_pass[5] = '\0';
}

uint8 HMI_init() {

	UART_ConfigType uartConfig = { .baudRate = 9600, .parity =
			UART_PARITY_DISABLED, .stopBit = UART_STOP_BIT_1, .charSize =
			UART_CHAR_SIZE_8, .asyncMode = LOGIC_LOW, .timeoutMs = 200

	};

	TWI_Config twiConfig = { .clock = 400000,               // 100kHz clock
			.prescaler = TWI_PRESCALER_1,  // No prescaling
			.address = 1,               // Set device address to 1
			.enableGeneralCall = FALSE     // Disable general call recognition
			};

	TWI_init(&twiConfig);
	UART_init(&uartConfig);
	DcMotor_init();
	PIR_init();
	UART_sendByte(HMI_READY);
	return (UART_receiveByte() == HMI_READY) ?
	HMI_CONNECTION_SUCSSES :
												HMI_CONNECTION_FAIL;
}
uint8 HMI_ready() {
	//UART_sendByte(HMI_READY);
	LCD_displayString("wait com");
	uint8 byte = UART_receiveByte();
	LCD_clearScreen();
	return byte;

}
uint8* HMI_checkPassMatch() {
	uint8 l_pass1[6] = { 0 };
	uint8 l_pass2[6] = { 0 };

	UART_sendByte(HMI_ACK);

	/* Receive the first password */

	HMI_recievePassword(l_pass1);

	UART_sendByte(HMI_ACK);  // Acknowledge receipt of first password

	/* Receive the second password */
	HMI_recievePassword(l_pass2);
	UART_sendByte(HMI_ACK);  // Acknowledge receipt of second password

	/* Check if passwords match */
	for (uint8 i = 0; i < 5; i++) {

		if (l_pass1[i] != l_pass2[i]) {

			UART_sendByte(HMI_PASSNOTMATCH);
			LCD_displayStringRowColumn(0, 0, "passMiss");
			return NULL_PTR;  // Exit early if passwords don't match
		}
	}

	/* If passwords match, confirm success */
	UART_sendByte(HMI_PASSMATCH);
	for (uint8 i = 0; i < 5; i++) {
		g_pass[i] = l_pass1[i];
	}
	return g_pass;
}
void HMI_checkPass() {
	uint8 l_pass[6] = { 0 };

	UART_sendByte(HMI_ACK);
	HMI_recievePassword(l_pass);

	UART_sendByte(HMI_ACK);  // Acknowledge receipt of  password
	for (uint8 i = 0; i < 5; i++) {

		if (l_pass[i] != MEM_getPassElem(i)) {

			UART_sendByte(HMI_PASSNOTMATCH);
			LCD_displayStringRowColumn(0, 0, "passMiss");
			return;  // Exit early if passwords don't match
		}
	}
	UART_sendByte(HMI_PASSMATCH);
}

uint8 MEM_getPassElem(uint8 a_passIndex) {
	uint8 byte;

	EEPROM_readByte(0xf + a_passIndex, &byte);
	return Decrypt(byte);

}
void MEM_savePass(uint8 *a_pass) {

	for (uint8 i = 0; i < 5; i++) {
		EEPROM_writeByte(0xf + i,Encrypt(a_pass[i]));
		_delay_ms(10);
	}
}

void OpenDoor() {
	DcMotor_OnForTime(ACW, 100, 10);
	UART_sendByte(HMI_OPEN_DOOR);

}

void CloseDoor() {
	DcMotor_OnForTime(CW, 100, 10);
	UART_sendByte(HMI_CLOSE_DOOR);

}

void waitForPeople() {
	_delay_ms(500);
	while (PIR_read())
		;
	UART_sendByte(HMI_PIR);
}
static uint8 Encrypt(uint8 a_num) {
	switch (a_num) {
	case 0:
		return '%';
		break;
	case 1:
		return '*';
		break;
	case 2:
		return 'd';
		break;
	case 3:
		return '$';
		break;
	case 4:
		return ';';
		break;
	case 5:
		return 'M';
		break;
	case 6:
		return 'b';
		break;
	case 7:
		return 'f';
		break;
	case 8:
		return ']';
		break;
	case 9:
		return '&';
	default:
		return a_num;
		break;
	};
}
static uint8 Decrypt(uint8 a_num) {
	switch (a_num) {
	case '%':
		return 0;
		break;
	case '*':
		return 1;
		break;
	case 'd':
		return 2;
		break;
	case '$':
		return 3;
		break;
	case ';':
		return 4;
		break;
	case 'M':
		return 5;
		break;
	case 'b':
		return 6;
		break;
	case 'f':
		return 7;
		break;
	case ']':
		return 8;
		break;
	case '&':
		return 9;
	default:
		return a_num;
		break;
	};
}
