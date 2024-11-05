/*
 * ctrl.c
 *
 *  Created on: 30 Oct 2024
 *      Author: MSI
 */

#include "../mcal/uart.h"
#include "ctrl.h"
#include"../common/std_types.h"
#include<util/delay.h>
static uint8 UART_sendPass(uint8 *a_pass) {
	uint8 i = 0;
	while (i < 5) {
		UART_sendByte(a_pass[i]);
		if (UART_receiveByte() != HMI_ACK)
			return COMM_ERROR;
		i++;
	}
	return COMM_SUCSSES;
}

uint8 CTRL_init() {

	UART_ConfigType uartConfig = { .baudRate = 9600, .parity =
			UART_PARITY_DISABLED, .stopBit = UART_STOP_BIT_1, .charSize =
			UART_CHAR_SIZE_8, .asyncMode = LOGIC_LOW, .timeoutMs = 200

	};
	UART_init(&uartConfig);

	//return CTRL_handShake(CTRL_HANDSHAKE);
	/*	if (UART_receiveByte() == HMI_READY) {

	 UART_sendByte(HMI_READY);
	 return CTRL_CONNECTION_SUCSSES;

	 }
	 return CTRL_CONNECTION_FAIL;*/
}
uint8 CTRL_checkPassMatch(uint8 *a_pass1, uint8 *a_pass2) {

	/* Inform HMI of password transmission */
	UART_sendByte(CTRL_WAIT_PASS);
	if (UART_receiveByte() != HMI_ACK)
		return COMM_ERROR;
	//_delay_ms(1);
	/* Send first password */
	UART_sendPass(a_pass1);
	if (UART_receiveByte() != HMI_ACK)
		return COMM_ERROR;

	/* Send second password */
	UART_sendPass(a_pass2);
	if (UART_receiveByte() != HMI_ACK)
		return COMM_ERROR;

	/* Receive the result from HMI */
	return UART_receiveByte();  // Expect HMI_PASSMATCH or HMI_PASSNOTMATCH
}
uint8 CTRL_checkPass(uint8 *a_pass) {
	UART_sendByte(CTRL_WAIT_PASS_MEM);
	if (UART_receiveByte() != HMI_ACK)
		return COMM_ERROR;
	UART_sendPass(a_pass);
	if (UART_receiveByte() != HMI_ACK)
		return COMM_ERROR;
	return UART_receiveByte();
}

uint8 CTRL_openDoor() {
	UART_sendByte(CTRL_OPEN_DOOR);
	if (UART_receiveByte() != HMI_ACK)
		return COMM_ERROR;
	return COMM_SUCSSES;
}
uint8 CTRL_closeDoor() {
	UART_sendByte(CTRL_OPEN_DOOR);
	if (UART_receiveByte() != HMI_ACK)
		return COMM_ERROR;
	if (UART_receiveByte() != CTRL_OPEN_DOOR)
		return COMM_ERROR;
	return COMM_SUCSSES;

}
uint8 CTRL_waitForPir(){
	if (UART_receiveByte() != HMI_PIR)
			return COMM_ERROR;
}
