/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../common/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
//#define KEYPAD_ROW_PORT_ID                PORTB_ID
#define KEYPAD_ROW_1_PIN_ID          GPIO_PB0
#define KEYPAD_ROW_2_PIN_ID          GPIO_PB1
#define KEYPAD_ROW_3_PIN_ID          GPIO_PB2
#define KEYPAD_ROW_4_PIN_ID          GPIO_PB3

#define KEYPAD_COL_1_PIN_ID          GPIO_PB4
#define KEYPAD_COL_2_PIN_ID          GPIO_PB5
#define KEYPAD_COL_3_PIN_ID          GPIO_PB6
#if (KEYPAD_NUM_COLS == 4)
#define KEYPAD_COL_4_PIN_ID          GPIO_PB7
#endif
/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(uint);

#endif /* KEYPAD_H_ */

