/*
 * hmi.c
 *
 *  Created on: 30 Oct 2024
 *      Author: MSI
 *      CTRL MCU
 */

#include "../mcal/uart.h"
#include "hmi.h"
#include"lcd.h"
#include"dcMotor.h"
#include<util/delay.h>
#include "../hal/external_eeprom.h"
uint8 g_pass[6];

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
	UART_init(&uartConfig);
	DcMotor_init();
	/*UART_sendByte(HMI_READY);
	 return (UART_receiveByte() == HMI_READY) ?
	 HMI_CONNECTION_SUCSSES :
	 HMI_CONNECTION_FAIL;*/
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
	return byte;

}
void MEM_savePass(uint8 *a_pass) {

	for (uint8 i = 0; i < 5; i++) {
		EEPROM_writeByte(0xf + i, a_pass[i]);
		_delay_ms(10);
	}
}

void OpenDoor() {
	DcMotor_OnForTime(ACW, 200, 15);
	UART_sendByte(HMI_OPEN_DOOR);

}

void CloseDoor() {
	DcMotor_OnForTime(CW, 200, 15);
	UART_sendByte(HMI_OPEN_DOOR);

}
