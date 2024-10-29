/**
 * @file timer_0.c
 * @brief Timer 0 driver for ATmega32 microcontroller.
 *
 * This file provides functionality to initialize and control Timer 0 in various modes
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
#include "timer_0.h"
#include <avr/interrupt.h>

/**
 * @brief Pointer to a callback function to be executed on Timer 0 interrupt.
 *
 * This static pointer is used to store the address of the callback function
 * that will be executed during Timer 0 interrupt service routines (ISR).
 */
static volatile void (*PTR2_Timer0_CallBack)(void) = NULL_PTR;

/**
 * @brief Initializes Timer 0 based on the provided configuration.
 *
 * This function configures Timer 0 with the specified mode, clock source,
 * initial count value, compare output mode, and interrupt settings. It
 * supports the following modes:
 * - Fast PWM
 * - CTC (Clear Timer on Compare Match)
 * - Normal Mode
 *
 * The configuration parameters are passed via a pointer to a `Timer0_Config`
 * structure, which should be properly initialized before calling this function.
 *
 * @param a_timerConfig Pointer to `Timer0_Config` structure with the desired settings.
 */
void Timer0_init(Timer0_Config *a_timerConfig) {

    /* Set initial timer count */
    TCNT0_REG.byte = (a_timerConfig)->intialCount;

    /* Set clock source and prescaler */
    TCCR0_REG.byte &= ~(TIMER0_CS_BITMASK); // Clear lower three bits for clock source
    TCCR0_REG.byte |= (a_timerConfig->clockSource&(TIMER0_CS_BITMASK));

    /* Configure the timer mode */
    switch (a_timerConfig->mode) {
        case TIMER0_MODE_FAST_PWM:
            /* Configure Fast PWM mode */
            TCCR0_REG.bits.wgm00 = LOGIC_HIGH;
            TCCR0_REG.bits.wgm01 = LOGIC_HIGH;

            /* Set Compare Output Mode */
            TCCR0_REG.bits.com00 = GET_BIT(a_timerConfig->compareOutputMode, TIMER_COMP_OUT_MODE_BIT_0);
            TCCR0_REG.bits.com01 = GET_BIT(a_timerConfig->compareOutputMode, TIMER_COMP_OUT_MODE_BIT_1);

            /* Set the duty cycle value (OCR0) */
            OCR0_REG.byte = a_timerConfig->tick;
            break;

        case TIMER0_MODE_CTC:
            /* Configure CTC mode */
            TCCR0_REG.bits.foc0 = LOGIC_HIGH;
            TCCR0_REG.bits.wgm00 = LOGIC_LOW;
            TCCR0_REG.bits.wgm01 = LOGIC_HIGH;


            /* Set Compare Output Mode */
            TCCR0_REG.bits.com00 = GET_BIT(a_timerConfig->compareOutputMode, TIMER_COMP_OUT_MODE_BIT_0);
            TCCR0_REG.bits.com01 = GET_BIT(a_timerConfig->compareOutputMode, TIMER_COMP_OUT_MODE_BIT_1);

            /* Enable interrupts if requested */
            if (a_timerConfig->interrupt) {
                TIMSK_REG.bits.ocie0 = LOGIC_HIGH;
                TIMSK_REG.bits.toie0 = LOGIC_LOW;
            }

            /* Set the compare match value (OCR0) */
            OCR0_REG.byte = a_timerConfig->tick;
            break;

        case TIMER0_MODE_NORMAL:
            /* Configure Normal mode */
            TCCR0_REG.bits.foc0 = LOGIC_HIGH; // Force Output Compare
            TCCR0_REG.bits.wgm00 = LOGIC_LOW;
            TCCR0_REG.bits.wgm01 = LOGIC_LOW;

            /* Disable Compare Output Mode */
            TCCR0_REG.bits.com00 = LOGIC_LOW;
            TCCR0_REG.bits.com01 = LOGIC_LOW;

            /* Enable overflow interrupt if requested */
            if (a_timerConfig->interrupt) {
                TIMSK_REG.bits.toie0 = LOGIC_HIGH; // Enable Overflow Interrupt
                TIMSK_REG.bits.ocie0 = LOGIC_LOW;  // Disable Output Compare Match Interrupt
            }
            break;
    }
}

/**
 * @brief Sets the callback function for Timer 0 interrupts.
 *
 * This function allows the user to specify a callback function that will
 * be executed during Timer 0 interrupts (either Output Compare Match or
 * Overflow interrupts).
 *
 * @param a_ptr2func Pointer to the callback function to be executed.
 */
void Timer0_setCallback(volatile void (a_ptr2func)(void)) {
    PTR2_Timer0_CallBack = a_ptr2func;
}

/**
 * @brief Sets the duty cycle for PWM mode in Timer 0.
 *
 * This function allows the user to set the duty cycle in Fast PWM mode by
 * updating the OCR0 register with the desired duty cycle value.
 *
 * @param a_duty The duty cycle value to be set (0-255).
 */
void Timer0_setDutyCycle(uint8 a_duty) {
    OCR0_REG.byte = a_duty;
}


/**
 * @brief ISR for Timer 0 Compare Match interrupt (TIMER0_COMP_vect).
 *
 * This interrupt service routine is executed when a compare match occurs
 * in Timer 0. If a callback function has been registered via
 * `Timer0_setCallback`, it will be called within this ISR.
 */
ISR(TIMER0_COMP_vect) {
    if (PTR2_Timer0_CallBack != NULL_PTR) {
        PTR2_Timer0_CallBack();
    }
}

/**
 * @brief ISR for Timer 0 Overflow interrupt (TIMER0_OVF_vect).
 *
 * This interrupt service routine is executed when Timer 0 overflows
 * (i.e., the timer count rolls over from 0xFF to 0x00). If a callback
 * function has been registered via `Timer0_setCallback`, it will be called
 * within this ISR.
 */
ISR(TIMER0_OVF_vect) {
    if (PTR2_Timer0_CallBack != NULL_PTR) {
        PTR2_Timer0_CallBack();
    }
}
