/*
 * hmi.c
 *
 *  Created on: 30 Oct 2024
 *      Author: MSI
 *      CTRL MCU
 */

#include "../mcal/uart.h"
#include "hmi.h"
#include"../common/std_types.h"
#include "lcd.h"
uint8 HMI_init() {
	uint8 l_byteRecieved = 0;
	UART_ConfigType uartConfig = {
		        .baudRate = 9600,
		        .parity = UART_PARITY_DISABLED,
		        .stopBit = UART_STOP_BIT_1,
		        .charSize = UART_CHAR_SIZE_8,
		        .asyncMode = LOGIC_LOW,
				.timeoutMs=200

		    };
	UART_init(&uartConfig);


	while (1) {

		l_byteRecieved = (uint8) UART_recieveByte();

		if (l_byteRecieved == CTRL_HANDSHAKE) {
			LCD_displayChar('S');
			UART_sendByte(CTRL_HANDSHAKE);
			return CTRL_CONNECTION_SUCSSES;
		}

	}
	return CTRL_CONNECTION_FAIL;
}
void HMI_handShake() {

}
