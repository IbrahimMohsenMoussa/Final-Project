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
#include"../common/std_types.h"

#include<util/delay.h>
char g_pass1[6];
char g_pass2[6];
uint8 HMI_handShake(uint8 a_command) {
    uint8 l_byteReceived = 0;
    l_byteReceived = UART_receiveByte(1000);  // Wait for command with timeout
    if (l_byteReceived == a_command) {
        UART_sendByte(HMI_CONNECTION_SUCSSES); // Send acknowledgment
        return HMI_CONNECTION_SUCSSES;
    }
    return HMI_CONNECTION_FAIL;
}

uint8 HMI_command() {
	uint8 byte = UART_recieveByte();

	return byte;
}
uint8 HMI_init() {

	UART_ConfigType uartConfig = { .baudRate = 9600, .parity =
			UART_PARITY_DISABLED, .stopBit = UART_STOP_BIT_1, .charSize =
			UART_CHAR_SIZE_8, .asyncMode = LOGIC_LOW, .timeoutMs = 200

	};
	UART_init(&uartConfig);

	return HMI_handShake(HMI_HANDSHAKE);
}
uint8 HMI_ready(){
	uint8 byte=UART_recieveByte() ;
while (byte==-1){
UART_sendByte(HMI_READY);
byte=UART_recieveByte() ;
}
return byte;

}
void HMI_checkPass() {
    uint8 l_pass1[6] = {0};
    uint8 l_pass2[6] = {0};

    /* Signal readiness to receive passwords */
    UART_sendByte(HMI_READY);

    /* Wait for CTRL_WAIT_PASS signal */
    if (UART_receiveByte(1000) != CTRL_WAIT_PASS) return;
    UART_sendByte(HMI_ACK);

    /* Receive the first password */
    UART_receiveString(l_pass1);
    UART_sendByte(HMI_ACK);  // Acknowledge receipt of first password

    /* Receive the second password */
    UART_receiveString(l_pass2);
    UART_sendByte(HMI_ACK);  // Acknowledge receipt of second password

    /* Check if passwords match */
    for (uint8 i = 0; i < 5; i++) {
        if (l_pass1[i] != l_pass2[i]) {
            UART_sendByte(HMI_PASSNOTMATCH);
            return;  // Exit early if passwords don't match
        }
    }


    /* If passwords match, confirm success */
    UART_sendByte(HMI_PASSMATCH);
    for (uint8 i = 0; i < 6; i++) {
          g_pass1[i] = l_pass1[i];
          g_pass2[i] = l_pass2[i];
      }
}

