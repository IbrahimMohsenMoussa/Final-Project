/**
 * @file timer_0.c
 * @brief Timer 2 driver for ATmega32 microcontroller.
 *
 * This file provides functionality to initialize and control Timer 2 in various modes
 * (Fast PWM, CTC, and Normal mode) on the ATmega32 microcontroller. It also allows
 * for setting a callback function for interrupt handling and adjusting the duty cycle
 * for PWM mode.
 *
 * @date 4 Oct 2024
 * @author Ibrahim Mohsen
 *
 * @see atmega32_regs.h
 * @see timer_0.h
 * @see std_types.h
 * @see common_macros.h
 */

#include "../common/common_macros.h"
#include "../common/std_types.h"
#include "atmega32_regs.h"
#include "timer_2.h"
#include <avr/interrupt.h>

/**
 * @brief Pointer to a callback function to be executed on Timer 2 interrupt.
 *
 * This static pointer is used to store the address of the callback function
 * that will be executed during Timer 2 interrupt service routines (ISR).
 */
static volatile void (*PTR2_Timer2_CallBack)(void) = NULL_PTR;


static uint8 g_lastClockSource = TIMER2_NO_CLOCK;
/**
 * @brief Initializes Timer 2 based on the provided configuration.
 *
 * This function configures Timer 2 with the specified mode, clock source,
 * initial count value, compare output mode, and interrupt settings. It
 * supports the following modes:
 * - Fast PWM
 * - CTC (Clear Timer on Compare Match)
 * - Normal Mode
 *
 * The configuration parameters are passed via a pointer to a `Timer2_Config`
 * structure, which should be properly initialized before calling this function.
 *
 * @param a_timerConfig Pointer to `Timer2_Config` structure with the desired settings.
 */
void Timer2_init(Timer2_Config *a_timerConfig) {

    /* Set initial timer count */
    TCNT2_REG.byte = (a_timerConfig)->intialCount;

    /* Set clock source and prescaler */
    TCCR2_REG.byte &= ~(TIMER2_CS_BITMASK); // Clear lower three bits for clock source
    TCCR2_REG.byte |= (a_timerConfig->clockSource&(TIMER2_CS_BITMASK));
    g_lastClockSource = a_timerConfig->clockSource;
    /* Configure the timer mode */
    switch (a_timerConfig->mode) {
        case TIMER2_MODE_FAST_PWM:
            /* Configure Fast PWM mode */
            TCCR2_REG.bits.wgm20 = LOGIC_HIGH;
            TCCR2_REG.bits.wgm21 = LOGIC_HIGH;

            /* Set Compare Output Mode */
            TCCR2_REG.bits.com20 = GET_BIT(a_timerConfig->compareOutputMode, TIMER_COMP_OUT_MODE_BIT_0);
            TCCR2_REG.bits.com21 = GET_BIT(a_timerConfig->compareOutputMode, TIMER_COMP_OUT_MODE_BIT_1);

            /* Set the duty cycle value (OCR0) */
            OCR2_REG.byte = a_timerConfig->tick;
            break;

        case TIMER2_MODE_CTC:
            /* Configure CTC mode */
            TCCR2_REG.bits.foc2 = LOGIC_HIGH;
            TCCR2_REG.bits.wgm20 = LOGIC_LOW;
            TCCR2_REG.bits.wgm21 = LOGIC_HIGH;


            /* Set Compare Output Mode */
            TCCR2_REG.bits.com20 = GET_BIT(a_timerConfig->compareOutputMode, TIMER_COMP_OUT_MODE_BIT_0);
            TCCR2_REG.bits.com21 = GET_BIT(a_timerConfig->compareOutputMode, TIMER_COMP_OUT_MODE_BIT_1);

            /* Enable interrupts if requested */
            if (a_timerConfig->interrupt) {
                TIMSK_REG.bits.ocie2 = LOGIC_HIGH;
                TIMSK_REG.bits.toie2 = LOGIC_LOW;
            }

            /* Set the compare match value (OCR0) */
            OCR2_REG.byte = a_timerConfig->tick;
            break;

        case TIMER2_MODE_NORMAL:
            /* Configure Normal mode */
            TCCR2_REG.bits.foc2 = LOGIC_HIGH; // Force Output Compare
            TCCR2_REG.bits.wgm20 = LOGIC_LOW;
            TCCR2_REG.bits.wgm21 = LOGIC_LOW;

            /* Disable Compare Output Mode */
            TCCR2_REG.bits.com20 = LOGIC_LOW;
            TCCR2_REG.bits.com21 = LOGIC_LOW;

            /* Enable overflow interrupt if requested */
            if (a_timerConfig->interrupt) {
                TIMSK_REG.bits.toie2 = LOGIC_HIGH; // Enable Overflow Interrupt
                TIMSK_REG.bits.ocie2 = LOGIC_LOW;  // Disable Output Compare Match Interrupt
            }
            break;
    }
    SREG_REG.bits.i=LOGIC_HIGH;
}

/**
 * @brief Sets the callback function for Timer 2 interrupts.
 *
 * This function allows the user to specify a callback function that will
 * be executed during Timer 2 interrupts (either Output Compare Match or
 * Overflow interrupts).
 *
 * @param a_ptr2func Pointer to the callback function to be executed.
 */
void Timer2_setCallback(volatile void (a_ptr2func)(void)) {
    PTR2_Timer2_CallBack = a_ptr2func;
}

/**
 * @brief Sets the duty cycle for PWM mode in Timer 2.
 *
 * This function allows the user to set the duty cycle in Fast PWM mode by
 * updating the OCR0 register with the desired duty cycle value.
 *
 * @param a_duty The duty cycle value to be set (0-255).
 */
void Timer2_setDutyCycle(uint8 a_duty) {
    OCR2_REG.byte = a_duty;
}

/**
 * @brief Stops Timer 2 by clearing the clock source bits.
 *
 * This function stops the timer by disabling the clock source, effectively
 * halting any counting or PWM operations.
 */
void Timer2_stop(void) {
    TCCR2_REG.byte &= ~(TIMER2_CS_BITMASK); // Clear clock source bits to stop the timer
}


void Timer2_resume(void) {
    TCCR2_REG.byte &= ~TIMER2_CS_BITMASK;       // Clear the clock source bits
    TCCR2_REG.byte |= (g_lastClockSource & TIMER2_CS_BITMASK);  // Restore last-used clock source
}
/**
 * @brief ISR for Timer 2 Compare Match interrupt (TIMER2_COMP_vect).
 *
 * This interrupt service routine is executed when a compare match occurs
 * in Timer 2. If a callback function has been registered via
 * `Timer2_setCallback`, it will be called within this ISR.
 */
ISR(TIMER2_COMP_vect) {
    if (PTR2_Timer2_CallBack != NULL_PTR) {
        PTR2_Timer2_CallBack();
    }
}

/**
 * @brief ISR for Timer 2 Overflow interrupt (TIMER2_OVF_vect).
 *
 * This interrupt service routine is executed when Timer 2 overflows
 * (i.e., the timer count rolls over from 0xFF to 0x00). If a callback
 * function has been registered via `Timer2_setCallback`, it will be called
 * within this ISR.
 */
ISR(TIMER2_OVF_vect) {
    if (PTR2_Timer2_CallBack != NULL_PTR) {
        PTR2_Timer2_CallBack();
    }
}
