/*
 * ctrl.c
 *
 *  Created on: 30 Oct 2024
 *      Author: MSI
 */

#include "../mcal/uart.h"
#include "ctrl.h"

uint8 CTRL_init() {
	uint8 l_byteRecieved = 0;
	UART_ConfigType uartConfig = { .baudRate = 9600, .parity =
			UART_PARITY_DISABLED, .stopBit = UART_STOP_BIT_1, .charSize =
			UART_CHAR_SIZE_8, .asyncMode = LOGIC_LOW, .timeoutMs = 200

	};
	UART_init(&uartConfig);
	for (int i = 0; i < 50; i++) {
		UART_sendByte(CTRL_HANDSHAKE);

		l_byteRecieved = (uint8) UART_recieveByte(l_byteRecieved);
		if (l_byteRecieved == CTRL_HANDSHAKE)
			return CTRL_CONNECTION_SUCSSES;
	}
return CTRL_CONNECTION_FAIL;
}
void CTRL_handShake() {

}
