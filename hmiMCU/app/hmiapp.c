/**
 * @file hmiapp.c
 * @brief Main application for managing password-protected door access with an HMI interface.
 *
 * This application uses an HMI (Human-Machine Interface) to handle door operations,
 * including setting and changing passwords, opening and closing the door, and initiating
 * a lockdown if access attempts exceed the limit. It uses a combination of LCD, Keypad,
 * Motor, and Buzzer peripherals.
 *
 * @date Novemeber 5, 2024
 * @author [Your Name]
 */

#include "../hal/lcd.h"              /**< LCD for user feedback */
#include "../hal/keypad.h"           /**< Keypad for password input */
#include <util/delay.h>              /**< Delay functions */
#include "../hal/interfaceHmi.h"     /**< Interface for communication with CTRL MCU */
#include "../mcal/timer_1.h"         /**< Timer for timeout handling */

/* Function Prototypes */
void Get_password(uint8 a_pass[]);
void Reset_Timer1Counter();
uint8 Check_password();
void Timer1_ISR();
void Reset_Timer1Counter();
void alert();
/* Global Variables */
static volatile uint32 g_sec; /**< Global counter to track seconds elapsed */
typedef enum {
    SET_PASSWORD, OPEN_DOOR, CLOSEDOOR, ALERT, IDLE, CHANGE_PASSWORD
} STATEMACHINE;
uint8 g_stateMachine = SET_PASSWORD; /**< Current state of the system */






int main() {
    uint8 trys = 0;   /**< Counter for invalid access attempts */
    LCD_init();
    CTRL_init();

    /* Configure and initialize Timer1 for 1-second intervals */
    Timer1_Config timer1Config = {
        .mode = TIMER1_MODE_CTC,
        .clockSource = TIMER1_PRESCALER_1024,
        .compareOutputModeA = TIMER1_COMPARE_NORMAL,
        .compareOutputModeB = TIMER1_COMPARE_CLEAR,
        .interruptA = TRUE,
        .interruptB = FALSE,
        .interruptOVF = FALSE,
        .tickA = 6250
    };
    Timer1_init(&timer1Config);
    Timer1_setCallback(Timer1_ISR);
    Reset_Timer1Counter();

    /* Main application loop */
    for (;;) {
    	/**
    	 * @brief State machine handling different operational states for the HMI door access system.
    	 *
    	 * This state machine cycles through various states, allowing the user to set a password, change it,
    	 * open the door, and manage security lockout. Each state is processed within a `switch` block.
    	 */

    	switch (g_stateMachine) {

    	    /**
    	     * @brief Initial password setup state.
    	     *
    	     * Prompts the user to enter a new password and confirm it. If both entries match,
    	     * the state machine proceeds to the idle state. Otherwise, the user is prompted to retry.
    	     */
    	    case SET_PASSWORD:
    	        LCD_clearScreen();
    	        LCD_displayStringRowColumn(0, 0, "Enter Pass:");

    	        uint8 l_1stInpass[6] = {0};   /**< Buffer to store the first entered password */
    	        uint8 l_2ndInpass[6] = {0};   /**< Buffer to store the confirmation password */

    	        Get_password(l_1stInpass);    /**< Capture first password entry */

    	        LCD_clearScreen();
    	        LCD_displayStringRowColumn(0, 0, "Re-enter Pass:");
    	        Get_password(l_2ndInpass);    /**< Capture confirmation password */

    	        if (CTRL_checkPassMatch(l_1stInpass, l_2ndInpass) == HMI_PASSMATCH) {
    	            g_stateMachine = IDLE;
    	            LCD_displayString("Pass match!"); /**< Successful match feedback */
    	        } else {
    	            LCD_clearScreen();
    	            LCD_displayString("Pass Mismatch!");
    	            LCD_displayStringRowColumn(0, 0, "Retry"); /**< Mismatch feedback */
    	        }
    	        break;

    	    /**
    	     * @brief Idle state for user to select actions.
    	     *
    	     * Displays options to either open the door or change the password.
    	     * User's input updates the state to the appropriate action.
    	     */
    	    case IDLE:
    	        LCD_clearScreen();
    	        LCD_displayStringRowColumn(0, 0, "+ : Open Door");
    	        LCD_displayStringRowColumn(1, 0, "- : Change Pass");

    	        uint8 idle_key = KEYPAD_getPressedKey(10000); /**< Capture keypad input */
    	        if (idle_key == '+') {
    	            g_stateMachine = OPEN_DOOR; /**< Transition to OPEN_DOOR state */
    	        } else if (idle_key == '-') {
    	            g_stateMachine = CHANGE_PASSWORD; /**< Transition to CHANGE_PASSWORD state */
    	        }
    	        break;

    	    /**
    	     * @brief Change password state with retry limit.
    	     *
    	     * Verifies the current password before allowing the user to set a new password.
    	     * If retries exceed limit, initiates alert/lockdown state.
    	     */
    	    case CHANGE_PASSWORD:
    	        if (trys >= 3) {             /**< Lockdown if max retries are reached */
    	            g_stateMachine = ALERT;
    	            trys = 0;
    	            break;
    	        }

    	        if (Check_password() == HMI_PASSMATCH) {
    	            LCD_clearScreen();
    	            LCD_displayStringRowColumn(0, 0, "Enter New Pass:");

    	            uint8 l_1stInCpass[6] = {0}; /**< Buffer for first new password entry */
    	            uint8 l_2ndInCpass[6] = {0}; /**< Buffer for confirmation of new password */

    	            Get_password(l_1stInCpass);
    	            LCD_clearScreen();
    	            LCD_displayStringRowColumn(0, 0, "Re-enter Pass:");
    	            Get_password(l_2ndInCpass);

    	            if (CTRL_checkPassMatch(l_1stInCpass, l_2ndInCpass) == HMI_PASSMATCH) {
    	                g_stateMachine = IDLE;
    	                LCD_displayString("Pass match!"); /**< New password successfully set */
    	            } else {
    	                LCD_clearScreen();
    	                LCD_displayString("Pass Mismatch!");
    	                LCD_displayStringRowColumn(0, 0, "Retry");
    	                _delay_ms(500); /**< Retry prompt for mismatch */
    	            }

    	            trys = 0;
    	            g_stateMachine = IDLE;
    	        } else {
    	            LCD_clearScreen();
    	            LCD_displayString("WRONG PASSWORD");
    	            trys++; /**< Increment retry counter on incorrect entry */
    	        }
    	        break;

    	    /**
    	     * @brief Door opening sequence with security check.
    	     *
    	     * Verifies password before allowing access to door opening sequence. On successful entry,
    	     * the system waits for user passage via PIR sensor and then closes the door.
    	     */
    	    case OPEN_DOOR:
    	        if (trys >= 3) {             /**< Lockdown if max retries are reached */
    	            g_stateMachine = ALERT;
    	            trys = 0;
    	            break;
    	        }

    	        if (Check_password() == HMI_PASSMATCH) {
    	            LCD_clearScreen();
    	            LCD_displayString("OPENING DOOR!");
    	            CTRL_openDoor();         /**< Trigger door opening mechanism */

    	            LCD_moveCursor(0, 0);
    	            LCD_displayString("WAIT FOR PEOPLE");
    	            CTRL_waitForPir();       /**< Wait for PIR sensor trigger */

    	            LCD_clearScreen();
    	            LCD_displayString("CLOSING DOOR");
    	            CTRL_closeDoor();        /**< Trigger door closing mechanism */

    	            trys = 0;
    	            g_stateMachine = IDLE;
    	        } else {
    	            LCD_clearScreen();
    	            LCD_displayString("WRONG PASSWORD");
    	            _delay_ms(500);          /**< Delay for user feedback */
    	            trys++;
    	        }
    	        break;

    	    /**
    	     * @brief Alert state triggered after multiple incorrect password attempts.
    	     *
    	     * Locks down the system for 60 seconds and activates a buzzer.
    	     * After the lockdown period, returns to the IDLE state.
    	     */
    	    case ALERT:
    	        alert(); /**< Executes a 60-second lockdown and buzzer alert */
    	        g_stateMachine = IDLE;
    	        break;

    	    /**
    	     * @brief Default state handler for unexpected states.
    	     *
    	     * Returns the system to the IDLE state if an invalid state is encountered.
    	     */
    	    default:
    	        LCD_displayStringRowColumn(0, 0, "Invalid State");
    	        g_stateMachine = IDLE;
    	        break;
    	}

    }
}

/**
 * @brief Captures a 5-character password and stores it in `a_pass`.
 *
 * This function reads five characters from the keypad and displays '*' for each entry on the LCD.
 *
 * @param a_pass Array to store the password characters.
 */
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

/**
 * @brief Prompts the user to enter a password and verifies it.
 *
 * This function captures a password from the keypad and checks it against the stored password.
 *
 * @return HMI_PASSMATCH if passwords match, otherwise returns a mismatch code.
 */
uint8 Check_password() {
    uint8 l_pass[6];
    LCD_clearScreen();
    LCD_displayStringRowColumn(0, 0, "Enter Pass:");
    Get_password(l_pass);
    return CTRL_checkPass(l_pass);
}


/**
 * @brief Timer1 ISR to increment seconds counter.
 *
 * This function increments the `g_sec` counter every time the timer ISR is triggered.
 */
void Timer1_ISR() {
    g_sec++;
}

/**
 * @brief Resets Timer1 and the elapsed time counter.
 *
 * This function stops Timer1, resets the global seconds counter `g_sec` to zero,
 * and then resumes Timer1.
 */
void Reset_Timer1Counter() {
    Timer1_stop();
    g_sec = 0;
}
/**
 * @brief Initiates an alert mode with a 60-second lockdown.
 *
 * During lockdown, the LCD displays a countdown, the buzzer is turned on, and
 * Timer1 counts 60 seconds before allowing any further access attempts.
 */
void alert() {
    LCD_clearScreen();
    LCD_displayString("====LOCKDOWN====");
    LCD_displayStringRowColumn(1, 0, "TRY AFTER");

    Reset_Timer1Counter();
    Timer1_resume();
    CTRL_buzzer_on();

    LCD_moveCursor(1, 10);
    while (g_sec < 60) {
        LCD_moveCursor(1, 10);
        LCD_intgerToString(60 - g_sec);

        if ((60 - g_sec) == 10) {
            LCD_displayStringRowColumn(1, 10, "    ");
        }
    }

    Reset_Timer1Counter();
    CTRL_buzzer_off();
    LCD_clearScreen();
}
