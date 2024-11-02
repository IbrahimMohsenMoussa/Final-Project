#include"../hal/hmi.h"
#include "../hal/lcd.h"
#include "../mcal/uart.h"
#include<util/delay.h>



int main() {
    LCD_init();
    HMI_init();

    for (;;) {
        /* Wait for command from HMI */
        uint8 l_receivedCommand = HMI_ready();

        switch (l_receivedCommand) {
            case HMI_WAIT_PASS:
                HMI_checkPassMatch();

                /* Display the first received password */
                LCD_clearScreen();
                LCD_displayStringRowColumn(0, 0, "Pass1:");
                for (uint8 i = 0; i < 5; i++) {
                    LCD_intgerToString(g_pass1[i]);
                }

                /* Display the second received password */
                LCD_moveCursor(1, 0);
                LCD_displayString("Pass2:");
                for (uint8 i = 0; i < 5; i++) {
                    LCD_intgerToString(g_pass2[i]);

                }
_delay_ms(5000);
                break;
            default:
                LCD_displayStringRowColumn(0, 0, "Unknown Command");
                break;
        };
    }
}
