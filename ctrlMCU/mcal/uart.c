/*
 * uart.c
 *
 *  Created on: 29 Oct 2024
 *      Author: MSI
 */
#include"uart.h"
#include "atmega32_regs.h"
#include"../common/common_macros.h"
#include <util/delay.h>

static uint16 g_timeOutCount = 0;
static uint16 g_elapsedCount = 0;
void UART_init(const UART_ConfigType *const a_config) {

	uint16 l_ubbrVal = 0;
	g_timeOutCount = 2 * a_config->timeoutMs;
	/* Calculate the UBRR value for 2x transmission speed */
	l_ubbrVal = (uint16) (((F_CPU / (a_config->baudRate * 8UL))) - 1);

	/* Enable 2x transmission speed for asynchronous communication */
	UCSRA_REG.bits.u2x = LOGIC_HIGH;

	/* Set UCSRC_REG and select it with URSEL set to 1 */
	UCSRC_REG.byte = 0x80;

	/* Configure character size */
	UCSRC_REG.bits.ucsz0 = GET_BIT(a_config->charSize, 0);
	UCSRC_REG.bits.ucsz1 = GET_BIT(a_config->charSize, 1);
	UCSRB_REG.bits.ucsz2 = GET_BIT(a_config->charSize, 2);

	/* Configure parity settings */
	UCSRC_REG.bits.upm0 = GET_BIT(a_config->parity, 0);
	UCSRC_REG.bits.upm1 = GET_BIT(a_config->parity, 1);
	/* configure stop bit 1 or 2 */
	UCSRC_REG.bits.usbs = a_config->stopBit;
	/* Select synchronous or asynchronous mode */
	UCSRC_REG.bits.umsel = a_config->asyncMode;

	/* Enable the UART transmitter and receiver */
	UCSRB_REG.bits.rxen = LOGIC_HIGH;
	UCSRB_REG.bits.txen = LOGIC_HIGH;

	/* Set baud rate in UBRR registers */
	UBRRH_REG.byte = (uint8) (l_ubbrVal >> 8);  // High byte
	UBRRL_REG.byte = (uint8) l_ubbrVal;         // Low byte
}
void UART_sendByte(const uint8 a_data) {
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while (!UCSRA_REG.bits.udre) {

	}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */

	UDR_REG.byte = a_data;

}
sint16 UART_recieveByte(void) {
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */

	while (!UCSRA_REG.bits.rxc) {
		/*_delay_us(500);
		g_elapsedCount++;
		if (g_elapsedCount >= g_timeOutCount) {
			return UART_TIMEOUT_ERROR_CODE;
		}*/

	}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR_REG.byte;
}

void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}

