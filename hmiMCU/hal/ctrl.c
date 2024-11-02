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
static uint8 CTRL_handShake(uint8 a_command) {
    uint8 l_byteReceived = 0;
    for (uint16 i = 0; i < 50000; i++) {
        UART_sendByte(a_command);
        l_byteReceived = UART_receiveByte(1000);  // Set a timeout in microseconds
        if (l_byteReceived == a_command) {
            UART_sendByte(CTRL_CONNECTION_SUCSSES); // Send acknowledgment
            return CTRL_CONNECTION_SUCSSES;
        }
    }
    return CTRL_CONNECTION_FAIL;
}


uint8 CTRL_init() {

	UART_ConfigType uartConfig = { .baudRate = 9600, .parity =
				UART_PARITY_DISABLED, .stopBit = UART_STOP_BIT_1, .charSize =
				UART_CHAR_SIZE_8, .asyncMode = LOGIC_LOW, .timeoutMs = 200

		};
	UART_init(&uartConfig);

	//return CTRL_handShake(CTRL_HANDSHAKE);
	if (UART_receiveByte(7)==HMI_READY){
		UART_sendByte(HMI_READY);
		return CTRL_CONNECTION_SUCSSES;

	}
	return CTRL_CONNECTION_FAIL;
}
uint8 CTRL_checkPass(uint8 *a_pass1, uint8 *a_pass2) {
    /* Wait until HMI signals readiness */
    //while (UART_receiveByte(1000) != HMI_READY);

    /* Inform HMI of password transmission */
    UART_sendByte(CTRL_WAIT_PASS);
    if (UART_receiveByte(1000) != HMI_ACK) return COMM_ERROR;

    /* Send first password */
    UART_sendString(a_pass1);
    if (UART_receiveByte(1000) != HMI_ACK) return COMM_ERROR;

    /* Send second password */
    UART_sendString(a_pass2);
    if (UART_receiveByte(1000) != HMI_ACK) return COMM_ERROR;

    /* Receive the result from HMI */
    return UART_receiveByte(1000);  // Expect HMI_PASSMATCH or HMI_PASSNOTMATCH
}


