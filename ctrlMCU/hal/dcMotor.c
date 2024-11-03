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
#include"../mcal/timer_2.h"
static uint8 g_ticks;
static uint32 g_sec;
Timer0_Config timer0_config = { .mode = TIMER0_MODE_FAST_PWM, .clockSource =
		TIMER0_PRESCALER_1024, .compareOutputMode = TIMER0_COMPARE_CLEAR,.interrupt= FALSE , .tick =
		255, .intialCount = 0

};
Timer2_Config timer2_config = { .mode = TIMER2_MODE_CTC, .clockSource =
		TIMER2_PRESCALER_1024, .compareOutputMode = TIMER2_COMPARE_CLEAR,.interrupt= TRUE , .tick =
		255, .intialCount = 0

};
volatile void  DcMotor_Timer2_ISR(){
if (g_ticks<64)
	g_ticks++;
else {
	g_ticks=0;
	g_sec++;
}

}
static  void Reset_Timer2Conter(){
    Timer2_stop();
	g_ticks=0;
	g_sec=0;

}

void DcMotor_init() {
	Timer0_init(&timer0_config);
	Timer2_init(&timer2_config);
	Timer2_setCallback(DcMotor_Timer2_ISR);
	Timer2_stop();
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
void DcMotor_OnForTime(DCMOTOR_STATE a_state, uint8 a_speed,uint16 a_time){
	Reset_Timer2Conter();
	Timer2_resume();
	while (g_sec<=a_time){
		DcMotor_rotate(a_state,a_speed);
	}
	DcMotor_rotate(STOP,0);
	Reset_Timer2Conter();
}
