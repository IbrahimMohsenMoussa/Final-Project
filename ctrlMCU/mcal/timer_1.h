/**
 * @file timer_1.h
 * @brief Header file for Timer 1 driver for ATmega32 microcontroller.
 *
 * This file contains function declarations, macros, and data structures
 * for controlling and configuring Timer 1 on the ATmega32. It supports
 * Normal, CTC, and Fast PWM modes, with various prescaler options and
 * output configurations.
 *
 * @date 8 Nov 2024
 * @author Ibrahim Mohsen
 */

#ifndef TIMER_1_H_
#define TIMER_1_H_

#include "../common/std_types.h"

#define TIMER1_CS_BITMASK 0x07   /**< Bitmask to clear clock source bits */
#define TIMER1_COMP_OUT_MODE_BIT_0 0
#define TIMER1_COMP_OUT_MODE_BIT_1 1

typedef struct {
    enum {
        TIMER1_MODE_NORMAL,
        TIMER1_MODE_CTC,
        TIMER1_MODE_FAST_PWM
    } mode;

    enum {
        TIMER1_NO_CLOCK,
        TIMER1_PRESCALER_1,
        TIMER1_PRESCALER_8,
        TIMER1_PRESCALER_64,
        TIMER1_PRESCALER_256,
        TIMER1_PRESCALER_1024,
    } clockSource;

    enum {
        TIMER1_COMPARE_NORMAL,
        TIMER1_RESERVED,
        TIMER1_COMPARE_CLEAR,
        TIMER1_COMPARE_SET
    } compareOutputModeA,compareOutputModeB;

    boolean interruptA;
    boolean interruptB;
    boolean interruptOVF;

    uint16 tickA;
    uint16 tickB;
    uint16 initialCount;
} Timer1_Config;

/**
 * @brief Initializes Timer 1 with specified configurations.
 * @param a_timerConfig Pointer to Timer1_Config structure.
 */
void Timer1_init(const Timer1_Config *a_timerConfig);

/**
 * @brief Sets the callback function for Timer 1 interrupts.
 * @param a_ptr2func Pointer to callback function.
 */
void Timer1_setCallback(volatile void (*a_ptr2func)(void));

/**
 * @brief Sets the duty cycle for Fast PWM mode in Timer 1.
 * @param a_duty Duty cycle value (0-65535).
 */
void Timer1_setDutyCycleA(uint16 a_duty);
/**
 * @brief Sets the duty cycle for Fast PWM mode in Timer 1.
 * @param a_duty Duty cycle value (0-65535).
 */
void Timer1_setDutyCycleB(uint16 a_duty);

/**
 * @brief Stops Timer 1 by clearing clock source bits.
 */
void Timer1_stop(void);

/**
 * @brief Resumes Timer 1 with previously configured clock source.
 */
void Timer1_resume(void);

#endif /* TIMER_1_H_ */
