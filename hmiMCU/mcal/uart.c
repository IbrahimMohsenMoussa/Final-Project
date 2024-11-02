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
	g_timeOutCount =  a_config->timeoutMs;
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
sint16 UART_receiveByte(uint32 timeout_us) {
    uint32 count = 0;
    while (!UCSRA_REG.bits.rxc) {
        /*if (count++ >= timeout_us) {
            return -1;  // Return -1 on timeout
        }
        _delay_us(1); */ // Delay in microseconds to avoid busy looping
    }
    return UDR_REG.byte;  // Return the received byte
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
	UART_sendByte('#');
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
	Str[i] = UART_receiveByte(10000);

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte(10000);
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}

