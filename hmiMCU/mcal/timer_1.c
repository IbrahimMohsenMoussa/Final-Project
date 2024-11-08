#include "timer_1.h"
#include "atmega32_regs.h"
#include "../common/common_macros.h"
#include <avr/interrupt.h>

static volatile void (*PTR2_Timer1_CallBack)(void) = NULL_PTR;
static uint8 g_lastClockSource = TIMER1_NO_CLOCK;

void Timer1_init(const Timer1_Config *a_timerConfig) {
	// Set initial count
	TCNT1_REG.word = a_timerConfig->initialCount;

	// Set clock source and prescaler
	TCCR1B_REG.byte &= ~TIMER1_CS_BITMASK;
	TCCR1B_REG.byte |= (a_timerConfig->clockSource & TIMER1_CS_BITMASK);
	g_lastClockSource = a_timerConfig->clockSource;

	// Configure the mode
	switch (a_timerConfig->mode) {
	case TIMER1_MODE_FAST_PWM:
		TCCR1A_REG.bits.wgm10 = LOGIC_LOW;
		TCCR1A_REG.bits.wgm11 = LOGIC_HIGH;
		TCCR1B_REG.bits.wgm12 = LOGIC_HIGH;
		TCCR1B_REG.bits.wgm13 = LOGIC_HIGH;

		// Set Compare Output Mode for compare unit A
		TCCR1A_REG.bits.com1a0 = GET_BIT(a_timerConfig->compareOutputModeA,
				TIMER1_COMP_OUT_MODE_BIT_0);
		TCCR1A_REG.bits.com1a1 = GET_BIT(a_timerConfig->compareOutputModeA,
				TIMER1_COMP_OUT_MODE_BIT_1);

		// Set Compare Output Mode for compare unit B
		TCCR1A_REG.bits.com1b0 = GET_BIT(a_timerConfig->compareOutputModeA,
				TIMER1_COMP_OUT_MODE_BIT_0);
		TCCR1A_REG.bits.com1b1 = GET_BIT(a_timerConfig->compareOutputModeB,
				TIMER1_COMP_OUT_MODE_BIT_1);

		// Set intial duty cycle
		OCR1A_REG.word = a_timerConfig->tickA;
		OCR1B_REG.word = a_timerConfig->tickB;
		break;

	case TIMER1_MODE_CTC:
		TCCR1A_REG.bits.foc1a = LOGIC_HIGH;
		TCCR1B_REG.bits.wgm12 = LOGIC_HIGH;
		// Set Compare Output Mode for compare unit A
		TCCR1A_REG.bits.com1a0 = GET_BIT(a_timerConfig->compareOutputModeA,
				TIMER1_COMP_OUT_MODE_BIT_0);
		TCCR1A_REG.bits.com1a1 = GET_BIT(a_timerConfig->compareOutputModeA,
				TIMER1_COMP_OUT_MODE_BIT_1);

		// Set Compare Output Mode for compare unit B
		TCCR1A_REG.bits.com1b0 = GET_BIT(a_timerConfig->compareOutputModeA,
				TIMER1_COMP_OUT_MODE_BIT_0);
		TCCR1A_REG.bits.com1b1 = GET_BIT(a_timerConfig->compareOutputModeB,
				TIMER1_COMP_OUT_MODE_BIT_1);

		if (a_timerConfig->interruptA) {
			TIMSK_REG.bits.ocie1a = LOGIC_HIGH;
			TIMSK_REG.bits.toie1 = LOGIC_LOW;
		}
		if (a_timerConfig->interruptB) {
			TIMSK_REG.bits.ocie1b = LOGIC_HIGH;
			TIMSK_REG.bits.toie1 = LOGIC_LOW;
		}

		OCR1A_REG.word = a_timerConfig->tickA;
		OCR1B_REG.word = a_timerConfig->tickB;
		break;

	case TIMER1_MODE_NORMAL:
		TCCR1A_REG.bits.foc1a = LOGIC_HIGH;
		TCCR1B_REG.bits.wgm12 = LOGIC_LOW;
		TCCR1A_REG.bits.com1a0 = LOGIC_LOW;
		TCCR1A_REG.bits.com1a1 = LOGIC_LOW;

		if (a_timerConfig->interruptOVF) {
			TIMSK_REG.bits.toie1 = LOGIC_HIGH;
			TIMSK_REG.bits.ocie1a = LOGIC_LOW;
			TIMSK_REG.bits.ocie1b = LOGIC_LOW;
		}
		break;
	}
	sei();
}

void Timer1_setCallback(volatile void (*a_ptr2func)(void)) {
	PTR2_Timer1_CallBack = a_ptr2func;
}

void Timer1_setDutyCycleA(uint16 a_duty) {
	OCR1A_REG.word = a_duty;
}
void Timer1_setDutyCycleB(uint16 a_duty) {
	OCR1A_REG.word = a_duty;
}
void Timer1_stop(void) {
	TCCR1B_REG.byte &= ~TIMER1_CS_BITMASK;
	TCNT1_REG.word = 0;
}

void Timer1_resume(void) {
	TCCR1B_REG.byte &= ~TIMER1_CS_BITMASK;
	TCCR1B_REG.byte |= (g_lastClockSource & TIMER1_CS_BITMASK);
}

ISR(TIMER1_COMPA_vect) {
	if (PTR2_Timer1_CallBack != NULL_PTR) {
		PTR2_Timer1_CallBack();
	}
}

ISR(TIMER1_OVF_vect) {
	if (PTR2_Timer1_CallBack != NULL_PTR) {
		PTR2_Timer1_CallBack();
	}
}
