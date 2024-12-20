/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/
#include "keypad.h"
#include "../mcal/gpio.h"
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/
static uint8 g_row_pins[4] = { KEYPAD_ROW_1_PIN_ID, KEYPAD_ROW_2_PIN_ID,
KEYPAD_ROW_3_PIN_ID, KEYPAD_ROW_4_PIN_ID };

#if (KEYPAD_NUM_COLS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
static uint8 g_col_pins[3]={KEYPAD_COL_1_PIN_ID,KEYPAD_COL_2_PIN_ID,KEYPAD_COL_3_PIN_ID};
#elif (KEYPAD_NUM_COLS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
static uint8 g_col_pins[4] = { KEYPAD_COL_1_PIN_ID, KEYPAD_COL_2_PIN_ID,
KEYPAD_COL_3_PIN_ID, KEYPAD_COL_4_PIN_ID };

#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


static uint8 KEYPAD_getPressedKeyPrivate (uint16 a_noChecks) {
	uint8 col, row;
	/* Configure all rows and columns as input initially */
	    for (row = 0; row < KEYPAD_NUM_ROWS; row++) {
	        GPIO_ARR_setPinDirection(g_row_pins[row], PIN_INPUT);
	    }
	    for (col = 0; col < KEYPAD_NUM_COLS; col++) {
	        GPIO_ARR_setPinDirection(g_col_pins[col], PIN_INPUT);
	    }
	for (uint16 l_checkCount = 0; l_checkCount < a_noChecks; l_checkCount++) {
		for (row = 0; row < KEYPAD_NUM_ROWS; row++) /* loop for rows */
		{
			/* 
			 * Each time setup the direction for all keypad port as input pins,
			 * except this row will be output pin
			 */
			GPIO_ARR_setPinDirection(g_row_pins[row], PIN_OUTPUT);

			/* Set/Clear the row output pin */
			GPIO_ARR_setPinState(g_row_pins[row],
			KEYPAD_BUTTON_PRESSED);

			for (col = 0; col < KEYPAD_NUM_COLS; col++) /* loop for columns */
			{
				/* Check if the switch is pressed in this column */
				if (GPIO_ARR_readPin(g_col_pins[col]) == KEYPAD_BUTTON_PRESSED) {
#if (KEYPAD_NUM_COLS == 3)
				return KEYPAD_4x3_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);
#elif (KEYPAD_NUM_COLS == 4)
					return KEYPAD_4x4_adjustKeyNumber(
							(row * KEYPAD_NUM_COLS) + col + 1);
#endif
				}
			}
			GPIO_ARR_setPinDirection(g_row_pins[row], PIN_INPUT);

			_delay_ms(10); /* Add small delay to fix CPU load issue in proteus */
		}
	}
	return 'N';
}

uint8 KEYPAD_getPressedKey(uint16 a_noChecks){

	 static uint8 lastPressedKey = 'N'; // Track last pressed key
	    uint8 currentKey = KEYPAD_getPressedKeyPrivate(a_noChecks);

	    /* If a key is detected and it's different from the last pressed key */
	    if (currentKey != 'N' && currentKey != lastPressedKey) {
	        lastPressedKey = currentKey;
	        return currentKey;
	    } else if (currentKey == 'N') {
	        /* If no key is pressed, reset lastPressedKey to detect new press */
	        lastPressedKey = 'N';
	    }

	    /* Return 'N' if no new key press is detected */
	    return 'N';
}


#if (KEYPAD_NUM_COLS == 3)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
		case 10: keypad_button = '*'; // ASCII Code of *
				 break;
		case 11: keypad_button = 0;
				 break;
		case 12: keypad_button = '#'; // ASCII Code of #
				 break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
} 

#elif (KEYPAD_NUM_COLS == 4)

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number) {
	uint8 keypad_button = 0;
	switch (button_number) {
	case 1:
		keypad_button = 7;
		break;
	case 2:
		keypad_button = 8;
		break;
	case 3:
		keypad_button = 9;
		break;
	case 4:
		keypad_button = '%'; // ASCII Code of %
		break;
	case 5:
		keypad_button = 4;
		break;
	case 6:
		keypad_button = 5;
		break;
	case 7:
		keypad_button = 6;
		break;
	case 8:
		keypad_button = '*'; /* ASCII Code of '*' */
		break;
	case 9:
		keypad_button = 1;
		break;
	case 10:
		keypad_button = 2;
		break;
	case 11:
		keypad_button = 3;
		break;
	case 12:
		keypad_button = '-'; /* ASCII Code of '-' */
		break;
	case 13:
		keypad_button = 13; /* ASCII of Enter */
		break;
	case 14:
		keypad_button = 0;
		break;
	case 15:
		keypad_button = '='; /* ASCII Code of '=' */
		break;
	case 16:
		keypad_button = '+'; /* ASCII Code of '+' */
		break;
	default:
		keypad_button = button_number;
		break;
	}
	return keypad_button;
}

#endif
