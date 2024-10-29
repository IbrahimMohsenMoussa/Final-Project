/*
 * uart.h
 *
 *  Created on: 29 Oct 2024
 *      Author: MSI
 */

#ifndef MCAL_UART_H_
#define MCAL_UART_H_
#include "../common/std_types.h"
#define UART_TIMEOUT_ERROR_CODE (-1)
#define UART_NO_ERROR (-10)
typedef enum {
    UART_PARITY_DISABLED, /**< No parity */
	RESERVED,
    UART_PARITY_EVEN,     /**< Even parity */
    UART_PARITY_ODD       /**< Odd parity */
} UART_ParityType;

/**
 * @enum UART_StopBitType
 * @brief Number of stop bits in UART communication.
 */
typedef enum {
    UART_STOP_BIT_1, /**< 1 stop bit */
    UART_STOP_BIT_2  /**< 2 stop bits */
} UART_StopBitType;

/**
 * @enum UART_CharacterSize
 * @brief Character size in UART frame.
 */
typedef enum {
    UART_CHAR_SIZE_5, /**< 5-bit character size */
    UART_CHAR_SIZE_6, /**< 6-bit character size */
    UART_CHAR_SIZE_7, /**< 7-bit character size */
    UART_CHAR_SIZE_8, /**< 8-bit character size */
    UART_CHAR_SIZE_9 = 7 /**< 9-bit character size */
} UART_CharacterSize;

/**
 * @struct UART_ConfigType
 * @brief Configuration structure for UART initialization.
 */
typedef struct {
    uint32 baudRate;                /**< Baud rate for UART communication */
    UART_ParityType parity;         /**< Parity setting */
    UART_StopBitType stopBit;       /**< Number of stop bits */
    UART_CharacterSize charSize;    /**< Character size */
    boolean asyncMode;              /**< TRUE for asynchronous, FALSE for synchronous */
    uint16 timeoutMs;
} UART_ConfigType;

void UART_init(const UART_ConfigType *const a_config);
void UART_sendByte(const uint8 a_data);
sint16 UART_recieveByte(void);
void UART_receiveString(uint8 *Str);
void UART_sendString(const uint8 *Str);
#endif /* MCAL_UART_H_ */
