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
uint8 CTRL_init() {

	UART_ConfigType uartConfig = { .baudRate = 9600, .parity =
			UART_PARITY_DISABLED, .stopBit = UART_STOP_BIT_1, .charSize =
			UART_CHAR_SIZE_8, .asyncMode = LOGIC_LOW, .timeoutMs = 200

	};
	UART_init(&uartConfig);

	return CTRL_handShake();
}
uint8 CTRL_handShake() {
	uint8 l_byteRecieved = 0;
	for (uint16 i; i < 50000; i++) {
		UART_sendByte(CTRL_HANDSHAKE);

		l_byteRecieved = (uint8) UART_recieveByte();
		uint16 timeOut = 0;
		while (l_byteRecieved != CTRL_HANDSHAKE && (timeOut < 1000)) {
			l_byteRecieved = (uint8) UART_recieveByte();
			timeOut++;
		}

		if (l_byteRecieved == CTRL_HANDSHAKE)
			return CTRL_CONNECTION_SUCSSES;
	}
	return CTRL_CONNECTION_FAIL;
}
uint8 CTRL_checkPass(uint8 *a_pass1, uint8 *a_pass2) {
	UART_sendByte(CTRL_WAIT_PASS);
	if (UART_recieveByte() != CTRL_WAIT_PASS)
		return 0;
	UART_sendString
}
