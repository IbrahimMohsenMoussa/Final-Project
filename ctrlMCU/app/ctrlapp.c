/**
 * @file main.c
 * @brief Main application to control a door system using LCD, EEPROM, Motor, Buzzer, and PIR sensor.
 *
 * This application manages door access through password verification. The program
 * interacts with an HMI (Human-Machine Interface) to receive commands and respond accordingly.
 * It also handles door control (open/close), password storage and retrieval, and
 * alerts via a buzzer and PIR sensor.
 *LCD connected to CTRL MCU id for debugging purposes only
 * @date 5 Nov, 2024
 * @author Ibrahim Mohsen
 */

/* Include HAL (Hardware Abstraction Layer) files for peripherals */
#include "../hal/lcd.h"               /**< LCD control for displaying status */
#include "../hal/external_eeprom.h"    /**< External EEPROM for storing passwords */
#include "../hal/dcMotor.h"            /**< Motor control for door operation */
#include "../hal/buzzer.h"             /**< Buzzer control for alerts */
#include "../hal/interfaceCtrl.h"      /**< Interface control for HMI communication */
#include "../hal/pir.h"                /**< PIR sensor to detect movement */
#include <util/delay.h>                /**< Delay functions */

int main() {
    /* Initialize the LCD and HMI */
    LCD_init();
    HMI_init();

    /* Initialize the buzzer */
    Buzzer_init();

    /* Pointer to hold password address */
    uint8 *l_ptr2pass;

    /* Main application loop */
    for (;;) {


        /* Wait for a command from HMI */
        uint8 l_receivedCommand = HMI_ready();

        /* Process received command */
        switch (l_receivedCommand) {
            case HMI_WAIT_PASS:
                /* Wait for 2  password entries and check if they match store in the EEPROM
                 *  else signals the to the HMI  pass mismatch */
                l_ptr2pass = HMI_checkPassMatch();
                if (l_ptr2pass != NULL_PTR) {
                    MEM_savePass(l_ptr2pass);   /**< Save new password to EEPROM */
                    l_ptr2pass = NULL_PTR;      /**< Clear pointer after saving */
                }

                /* Display saved password for verification (debugging) */
                LCD_moveCursor(0, 0);
                for (uint8 i = 0; i < 5; i++) {
                    LCD_intgerToString(MEM_getPassElem(i)); /**< Display each element of the saved password */
                }
                break;

            case HMI_WAIT_PASS_MEM:
                /* Verify password using memory-stored password */
                HMI_checkPass();
                break;

            case HMI_OPEN_DOOR:
                /* Command to open the door */
                OpenDoor();
                waitForPeople();               /**< Wait if the PIR detects presence */
                break;

            case HMI_CLOSE_DOOR:
                /* Command to close the door */
                CloseDoor();
                break;

            case BUZZER_ON:
                /* Activate the buzzer */
                Buzzer_on();
                break;

            case BUZZER_OFF:
                /* Deactivate the buzzer */
                Buzzer_off();
                break;

            default:
                /* Handle unrecognized command */
                LCD_displayStringRowColumn(0, 0, "Unknown Command");
                LCD_displayChar(l_receivedCommand);
                break;
        }
    }
}
