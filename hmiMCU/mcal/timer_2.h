/**
 * @file timer_2.h
 * @brief Header file for Timer 2 driver for ATmega32 microcontroller.
 *
 * This file contains the function declarations, macros, and data structures
 * used to control and configure Timer 2 on the ATmega32. The timer can be
 * configured in various modes, including Normal, CTC (Clear Timer on Compare Match),
 * and Fast PWM, with different prescaler options and output modes.
 *
 * @date 4 Oct 2024
 * @author Ibrahim Mohsen
 */

#ifndef TIMER_2_H_
#define TIMER_2_H_

#include "../common/std_types.h"

/**
 * @def TIMER2_CS_BITMASK
 * @brief A bitmask to clear the clock source bits in the TCCR2 register.
 *
 * This macro defines a bitmask that is used to clear the clock selection bits
 * (CS22, CS21, CS20) in the TCCR2 register before setting the desired prescaler.
 */
#define TIMER2_CS_BITMASK 0x07

/**
 * @def TIMER_COMP_OUT_MODE_BIT_0
 * @brief The bit index for the first Compare Output Mode bit in the TCCR2 register.
 *
 * This macro defines the bit position of the first Compare Output Mode (COM20)
 * bit in the TCCR2 register. It is used when configuring the output mode of
 * the timer in CTC or PWM mode.
 */
#define TIMER_COMP_OUT_MODE_BIT_0 0

/**
 * @def TIMER_COMP_OUT_MODE_BIT_1
 * @brief The bit index for the second Compare Output Mode bit in the TCCR2 register.
 *
 * This macro defines the bit position of the second Compare Output Mode (COM21)
 * bit in the TCCR2 register. It is used to configure the output mode of
 * the timer in CTC or PWM mode.
 */
#define TIMER_COMP_OUT_MODE_BIT_1 1

/**
 * @brief Timer 2 configuration structure.
 *
 * This structure defines the configuration parameters for Timer 2. It includes
 * the timer mode (Normal, CTC, Fast PWM), the clock source, the compare output mode,
 * and options for enabling or disabling interrupts. The user must fill this structure
 * before passing it to the `Timer2_init()` function to initialize the timer.
 */
typedef struct {

    /**
     * @brief Enumeration for Timer 2 modes.
     *
     * This enum defines the possible modes for Timer 2:
     * - TIMER2_MODE_NORMAL: Normal mode.
     * - TIMER2_MODE_CTC: Clear Timer on Compare Match (CTC) mode.
     * - TIMER2_MODE_FAST_PWM: Fast Pulse Width Modulation (PWM) mode.
     */
    enum {
        TIMER2_MODE_NORMAL, /**< Normal mode */
        TIMER2_MODE_CTC,    /**< Clear Timer on Compare Match (CTC) mode */
        TIMER2_MODE_FAST_PWM /**< Fast PWM mode */
    } mode;

    /**
     * @brief Enumeration for Timer 2 clock sources.
     *
     * This enum defines the available clock sources and prescaler values for Timer 2:
     * - TIMER2_NO_CLOCK: Timer is disabled (no clock source).
     * - TIMER2_PRESCALER_1: No prescaling, clock source is the system clock.
     * - TIMER2_PRESCALER_8: Prescaler of 8.
     * - TIMER2_PRESCALER_64: Prescaler of 64.
     * - TIMER2_PRESCALER_256: Prescaler of 256.
     * - TIMER2_PRESCALER_1024: Prescaler of 1024.
     * - TIMER2_EXTERNAL_CLOCK_FALLING: External clock source, triggered on the falling edge.
     * - TIMER2_EXTERNAL_CLOCK_RISING: External clock source, triggered on the rising edge.
     */
    enum {
        TIMER2_NO_CLOCK,              /**< No clock source (Timer is stopped) */
        TIMER2_PRESCALER_1,           /**< No prescaler (system clock) */
        TIMER2_PRESCALER_8,           /**< Prescaler of 8 */
        TIMER2_PRESCALER_64,          /**< Prescaler of 64 */
        TIMER2_PRESCALER_256,         /**< Prescaler of 256 */
        TIMER2_PRESCALER_1024,        /**< Prescaler of 1024 */

    } clockSource;

    /**
     * @brief Enumeration for Timer 2 Compare Output Mode.
     *
     * This enum defines the possible compare output modes for Timer 2:
     * - TIMER2_COMPARE_NORMAL: Normal port operation (OC2 disconnected).
     * - TIMER2_RESERVED: Reserved for future use (not used).
     * - TIMER2_COMPARE_CLEAR: Clear OC2 on compare match.
     * - TIMER2_COMPARE_SET: Set OC2 on compare match.
     */
    enum {
        TIMER2_COMPARE_NORMAL, /**< Normal port operation, OC2 disconnected */
        TIMER2_RESERVED,       /**< Reserved for future use */
        TIMER2_COMPARE_CLEAR,  /**< Clear OC2 on compare match */
        TIMER2_COMPARE_SET     /**< Set OC2 on compare match */
    } compareOutputMode;

    /**
     * @brief Interrupt enable/disable flag.
     *
     * If this boolean is set to `TRUE`, interrupts for Timer 2 will be enabled.
     * If it is set to `FALSE`, interrupts will be disabled.
     */
    boolean interrupt;

    /**
     * @brief The compare match value or PWM tick count.
     *
     * In CTC mode, this represents the value to which the timer will count
     * before triggering the compare match event. In Fast PWM mode, this value
     * is used to set the duty cycle.
     */
    uint8 tick;

    /**
     * @brief Initial timer count.
     *
     * This field sets the initial value of the Timer 2 counter (TCNT2).
     * The timer will start counting from this value.
     */
    uint8 intialCount;

} Timer2_Config;

/**
 * @brief Initializes Timer 2 with the specified configuration.
 *
 * This function initializes Timer 2 using the settings provided in the
 * `Timer2_Config` structure. The user must set the timer mode, clock source,
 * compare output mode, interrupt enable/disable, compare match value (tick),
 * and the initial timer count before calling this function.
 *
 * @param a_timerConfig Pointer to `Timer2_Config` structure containing the desired settings.
 */
void Timer2_init(Timer2_Config *a_timerConfig);

/**
 * @brief Sets the callback function for Timer 2 interrupts.
 *
 * This function allows the user to set a callback function that will be executed
 * when a Timer 2 interrupt (either Output Compare Match or Overflow) occurs.
 *
 * @param a_ptr2func Pointer to the callback function to be executed on interrupt.
 */
void Timer2_setCallback(volatile void (*a_ptr2func)(void));

/**
 * @brief Sets the duty cycle for Fast PWM mode in Timer 2.
 *
 * This function allows the user to set the duty cycle of Timer 2 in Fast PWM mode
 * by writing the duty cycle value to the OCR2 register.
 *
 * @param a_duty Duty cycle value (0-255).
 */
void Timer2_setDutyCycle(uint8 a_duty);

/**
 * @brief Stops Timer 2 by clearing the clock source bits.
 *
 * This function stops the timer by clearing the clock source bits in the TCCR2 register.
 */
void Timer2_stop(void);
void Timer2_resume(void);

#endif /* TIMER_2_H_ */
