/*
 * dcMotor.c
 *
 *  Created on: 6 Oct 2024
 *      Author: MSI
 */
#include"../mcal/timer_0.h"
#include"../mcal/gpio.h"
#include"dcMotor.h"
#include"../common/std_types.h"
#include"../common/common_Macros.h"
Timer0_Config timer0_config = { .mode = TIMER0_MODE_FAST_PWM, .clockSource =
		TIMER0_PRESCALER_8, .compareOutputMode = TIMER0_COMPARE_CLEAR,.interrupt= FALSE , .tick =
		255, .intialCount = 0

};
void DcMotor_init() {
	Timer0_init(&timer0_config);
	GPIO_ARR_setPinDirection(DCMOTOR_IN_1, PIN_OUTPUT);
	GPIO_ARR_setPinDirection(DCMOTOR_IN_2, PIN_OUTPUT);
	GPIO_ARR_setPinDirection(DCMOTOR_E1, PIN_OUTPUT);

}
void DcMotor_rotate(DCMOTOR_STATE a_state, uint8 a_speed) {
	switch (a_state) {
	case CW:
		GPIO_ARR_setPinState(DCMOTOR_IN_1, LOGIC_HIGH);
		GPIO_ARR_setPinState(DCMOTOR_IN_2, LOGIC_LOW);
		break;
	case ACW:
		GPIO_ARR_setPinState(DCMOTOR_IN_2, LOGIC_HIGH);
		GPIO_ARR_setPinState(DCMOTOR_IN_1, LOGIC_LOW);
		break;
	case STOP:
		GPIO_ARR_setPinState(DCMOTOR_IN_1, LOGIC_LOW);
		GPIO_ARR_setPinState(DCMOTOR_IN_2, LOGIC_LOW);
		break;
	};
	uint8 l_duty = MAP(a_speed, 0, 100, 0, 255);
	Timer0_setDutyCycle(l_duty);

}

