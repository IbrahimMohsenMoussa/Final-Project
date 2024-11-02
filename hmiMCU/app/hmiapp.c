#include "../hal/ctrl.h"
#include "../hal/lcd.h"
#include "../hal/keypad.h"
#include<util/delay.h>
void Get_password(uint8 a_pass[]);

typedef enum {
    SET_PASSWORD, OPEN_DOOR, CLOSEDOOR, ALERT
} STATEMACHINE;

uint8 g_stateMachine = SET_PASSWORD;

int main() {
    LCD_init();
    CTRL_init();

    for (;;) {
        switch (g_stateMachine) {
            case SET_PASSWORD:
                LCD_displayStringRowColumn(0, 0, "Enter Pass:");

                uint8 l_1stInpass[6] = {0};
                uint8 l_2ndInpass[6] = {0};

                /* Capture the first password */
                Get_password(l_1stInpass);

                /* Confirm and re-enter password */
                LCD_clearScreen();
                LCD_displayStringRowColumn(0, 0, "Re-enter Pass:");
                Get_password(l_2ndInpass);

                /* Display passwords for debug */
                LCD_clearScreen();
                LCD_displayStringRowColumn(0, 0, "1st:");
                for (uint8 i = 0; i < 5; i++) {
                    LCD_intgerToString(l_1stInpass[i]);
                }

                LCD_moveCursor(1, 0);
                LCD_displayString("2nd:");
                for (uint8 i = 0; i < 5; i++) {
                    LCD_intgerToString(l_2ndInpass[i]);
                }

                /* Send and check passwords */
                if (CTRL_checkPassMatch(l_1stInpass, l_2ndInpass) == HMI_PASSMATCH) {
                   // g_stateMachine = OPEN_DOOR;
                    LCD_displayString("Pass match!");
                    // Passwords matched
                } else {
                    LCD_clearScreen();
                    LCD_displayString("Pass Mismatch!");
                    _delay_ms(1000);
                }
                break;
            default:
                LCD_displayStringRowColumn(0, 0, "Invalid State");
                break;
        }
    }
}

/* Captures a 5-character password and stores it in a_pass */
void Get_password(uint8 *a_pass) {
    a_pass[5] = '\0';  // Null-terminate the password string

    uint8 l_key = 'N';
    for (uint8 i = 0; i < 5; i++) {
        /* Wait for a valid key press */
        while (l_key == 'N' || l_key > 9) {
            l_key = KEYPAD_getPressedKey(1);
        }

        /* Store the new key press and display '*' */
        a_pass[i] = l_key;
        LCD_moveCursor(1, i + 11);  // Adjust position if necessary
        LCD_displayChar('*');

        l_key = 'N';  // Reset l_key for the next input
    }
}
