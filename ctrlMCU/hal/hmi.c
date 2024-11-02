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
	uint8 byte = UART_receiveByte(10000);

	return byte;
}
uint8 HMI_init() {

	UART_ConfigType uartConfig = { .baudRate = 9600, .parity =
			UART_PARITY_DISABLED, .stopBit = UART_STOP_BIT_1, .charSize =
			UART_CHAR_SIZE_8, .asyncMode = LOGIC_LOW, .timeoutMs = 200

	};
	UART_init(&uartConfig);

UART_sendByte(HMI_READY);
return (UART_receiveByte(7)==HMI_READY)? HMI_CONNECTION_SUCSSES: HMI_CONNECTION_FAIL;
}
uint8 HMI_ready(){
	//UART_sendByte(HMI_READY);
	LCD_displayString("wait com");
	uint8 byte=UART_receiveByte(10000) ;

return byte;

}
void HMI_checkPass() {
    uint8 l_pass1[6] = {0};
    uint8 l_pass2[6] = {0};

    /* Signal readiness to receive passwords */
   // UART_sendByte(HMI_READY);

    /* Wait for CTRL_WAIT_PASS signal */
  /*  while (UART_receiveByte(1000) != HMI_WAIT_PASS){
    	LCD_displayString("wait CP");
    } ;*/
    UART_sendByte(HMI_ACK);
    LCD_displayStringRowColumn(0,0,"ACK comm ");
    /* Receive the first password */

    UART_receiveString(l_pass1);

    UART_sendByte(HMI_ACK);  // Acknowledge receipt of first password
    LCD_displayStringRowColumn(0,0,"pass1");
    /* Receive the second password */
    UART_receiveString(l_pass2);
    UART_sendByte(HMI_ACK);  // Acknowledge receipt of second password
    LCD_displayStringRowColumn(0,0,"pass2");
    /* Check if passwords match */
    for (uint8 i = 0; i < 5; i++) {
    	LCD_moveCursor(1,0);
    	LCD_intgerToString(l_pass1[i]);
        if (l_pass1[i] != l_pass2[i]) {

            UART_sendByte(HMI_PASSNOTMATCH);
            LCD_displayStringRowColumn(0,0,"passMiss");
            return;  // Exit early if passwords don't match
        }
    }


    /* If passwords match, confirm success */
    UART_sendByte(HMI_PASSMATCH);
    LCD_displayStringRowColumn(0,0,"success");
    for (uint8 i = 0; i < 6; i++) {
          g_pass1[i] = l_pass1[i];
          g_pass2[i] = l_pass2[i];
      }
}

