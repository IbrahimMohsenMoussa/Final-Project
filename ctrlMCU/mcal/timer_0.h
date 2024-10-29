/**
 * @file timer_0.h
 * @brief Header file for Timer 0 driver for ATmega32 microcontroller.
 *
 * This file contains the function declarations, macros, and data structures
 * used to control and configure Timer 0 on the ATmega32. The timer can be
 * configured in various modes, including Normal, CTC (Clear Timer on Compare Match),
 * and Fast PWM, with different prescaler options and output modes.
 *
 * @date 4 Oct 2024
 * @author Ibrahim Mohsen
 */

#ifndef TIMER_0_H_
#define TIMER_0_H_

#include "../common/std_types.h"

/**
 * @def TIMER0_CS_BITMASK
 * @brief A bitmask to clear the clock source bits in the TCCR0 register.
 *
 * This macro defines a bitmask that is used to clear the clock selection bits
 * (CS02, CS01, CS00) in the TCCR0 register before setting the desired prescaler.
 */
#define TIMER0_CS_BITMASK 0x07

/**
 * @def TIMER_COMP_OUT_MODE_BIT_0
 * @brief The bit index for the first Compare Output Mode bit in the TCCR0 register.
 *
 * This macro defines the bit position of the first Compare Output Mode (COM00)
 * bit in the TCCR0 register. It is used when configuring the output mode of
 * the timer in CTC or PWM mode.
 */
#define TIMER_COMP_OUT_MODE_BIT_0 0

/**
 * @def TIMER_COMP_OUT_MODE_BIT_1
 * @brief The bit index for the second Compare Output Mode bit in the TCCR0 register.
 *
 * This macro defines the bit position of the second Compare Output Mode (COM01)
 * bit in the TCCR0 register. It is used to configure the output mode of
 * the timer in CTC or PWM mode.
 */
#define TIMER_COMP_OUT_MODE_BIT_1 1

/**
 * @brief Timer 0 configuration structure.
 *
 * This structure defines the configuration parameters for Timer 0. It includes
 * the timer mode (Normal, CTC, Fast PWM), the clock source, the compare output mode,
 * and options for enabling or disabling interrupts. The user must fill this structure
 * before passing it to the `Timer0_init()` function to initialize the timer.
 */
typedef struct {

    /**
     * @brief Enumeration for Timer 0 modes.
     *
     * This enum defines the possible modes for Timer 0:
     * - TIMER0_MODE_NORMAL: Normal mode.
     * - TIMER0_MODE_CTC: Clear Timer on Compare Match (CTC) mode.
     * - TIMER0_MODE_FAST_PWM: Fast Pulse Width Modulation (PWM) mode.
     */
    enum {
        TIMER0_MODE_NORMAL, /**< Normal mode */
        TIMER0_MODE_CTC,    /**< Clear Timer on Compare Match (CTC) mode */
        TIMER0_MODE_FAST_PWM /**< Fast PWM mode */
    } mode;

    /**
     * @brief Enumeration for Timer 0 clock sources.
     *
     * This enum defines the available clock sources and prescaler values for Timer 0:
     * - TIMER0_NO_CLOCK: Timer is disabled (no clock source).
     * - TIMER0_PRESCALER_1: No prescaling, clock source is the system clock.
     * - TIMER0_PRESCALER_8: Prescaler of 8.
     * - TIMER0_PRESCALER_64: Prescaler of 64.
     * - TIMER0_PRESCALER_256: Prescaler of 256.
     * - TIMER0_PRESCALER_1024: Prescaler of 1024.
     * - TIMER0_EXTERNAL_CLOCK_FALLING: External clock source, triggered on the falling edge.
     * - TIMER0_EXTERNAL_CLOCK_RISING: External clock source, triggered on the rising edge.
     */
    enum {
        TIMER0_NO_CLOCK,              /**< No clock source (Timer is stopped) */
        TIMER0_PRESCALER_1,           /**< No prescaler (system clock) */
        TIMER0_PRESCALER_8,           /**< Prescaler of 8 */
        TIMER0_PRESCALER_64,          /**< Prescaler of 64 */
        TIMER0_PRESCALER_256,         /**< Prescaler of 256 */
        TIMER0_PRESCALER_1024,        /**< Prescaler of 1024 */
        TIMER0_EXTERNAL_CLOCK_FALLING, /**< External clock on falling edge */
        TIMER0_EXTERNAL_CLOCK_RISING   /**< External clock on rising edge */
    } clockSource;

    /**
     * @brief Enumeration for Timer 0 Compare Output Mode.
     *
     * This enum defines the possible compare output modes for Timer 0:
     * - TIMER0_COMPARE_NORMAL: Normal port operation (OC0 disconnected).
     * - TIMER0_RESERVED: Reserved for future use (not used).
     * - TIMER0_COMPARE_CLEAR: Clear OC0 on compare match.
     * - TIMER0_COMPARE_SET: Set OC0 on compare match.
     */
    enum {
        TIMER0_COMPARE_NORMAL, /**< Normal port operation, OC0 disconnected */
        TIMER0_RESERVED,       /**< Reserved for future use */
        TIMER0_COMPARE_CLEAR,  /**< Clear OC0 on compare match */
        TIMER0_COMPARE_SET     /**< Set OC0 on compare match */
    } compareOutputMode;

    /**
     * @brief Interrupt enable/disable flag.
     *
     * If this boolean is set to `TRUE`, interrupts for Timer 0 will be enabled.
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
     * This field sets the initial value of the Timer 0 counter (TCNT0).
     * The timer will start counting from this value.
     */
    uint8 intialCount;

} Timer0_Config;

/**
 * @brief Initializes Timer 0 with the specified configuration.
 *
 * This function initializes Timer 0 using the settings provided in the
 * `Timer0_Config` structure. The user must set the timer mode, clock source,
 * compare output mode, interrupt enable/disable, compare match value (tick),
 * and the initial timer count before calling this function.
 *
 * @param a_timerConfig Pointer to `Timer0_Config` structure containing the desired settings.
 */
void Timer0_init(Timer0_Config *a_timerConfig);

/**
 * @brief Sets the callback function for Timer 0 interrupts.
 *
 * This function allows the user to set a callback function that will be executed
 * when a Timer 0 interrupt (either Output Compare Match or Overflow) occurs.
 *
 * @param a_ptr2func Pointer to the callback function to be executed on interrupt.
 */
void Timer0_setCallback(volatile void (a_ptr2func)(void));

/**
 * @brief Sets the duty cycle for Fast PWM mode in Timer 0.
 *
 * This function allows the user to set the duty cycle of Timer 0 in Fast PWM mode
 * by writing the duty cycle value to the OCR0 register.
 *
 * @param a_duty Duty cycle value (0-255).
 */
void Timer0_setDutyCycle(uint8 a_duty);

#endif /* TIMER_0_H_ */
