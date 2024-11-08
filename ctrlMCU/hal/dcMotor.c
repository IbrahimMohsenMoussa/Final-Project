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
#include"../mcal/timer_1.h"
#include<util/delay.h>
#include "lcd.h"



static volatile uint32 g_sec;


 void Timer1_ISR(){


	g_sec++;


}
static  void Reset_Timer1Conter(){
    Timer1_stop();
	g_sec=0;

}

void DcMotor_init() {

	Timer1_Config timer1Config = { .mode = TIMER1_MODE_CTC, .clockSource =
				TIMER1_PRESCALER_1024, .compareOutputModeA = TIMER1_COMPARE_CLEAR,
				.compareOutputModeB = TIMER1_COMPARE_CLEAR, .interruptA = TRUE,
				.interruptB = FALSE, .interruptOVF = FALSE, .tickA = 7812 , .initialCount = 0

		};
	Timer0_Config timer0_config = { .mode = TIMER0_MODE_FAST_PWM, .clockSource =
			TIMER0_PRESCALER_1024, .compareOutputMode = TIMER0_COMPARE_CLEAR,.interrupt= FALSE , .tick =
			0, .intialCount = 0

	};
		Timer1_init(&timer1Config);
		Timer1_setCallback(Timer1_ISR);
	Timer0_init(&timer0_config);

	//GPIO_setupPinDirection(PORTD_ID,6,PIN_OUTPUT);
	//GPIO_setupPinDirection(PORTD_ID,7,PIN_OUTPUT);
	GPIO_ARR_setPinDirection(DCMOTOR_IN_1, PIN_OUTPUT);
	GPIO_ARR_setPinDirection(DCMOTOR_IN_2, PIN_OUTPUT);

	GPIO_ARR_setPinDirection(DCMOTOR_E1, PIN_OUTPUT);

}
void DcMotor_rotate(DCMOTOR_STATE a_state, uint8 a_speed) {
	switch (a_state) {
	case CW:
		LCD_clearScreen();
		LCD_displayString("cw");

		GPIO_ARR_setPinState(DCMOTOR_IN_1, HIGH);
		GPIO_ARR_setPinState(DCMOTOR_IN_2, LOW);
		/*DDRD|=(1<<6);
		DDRD|=(1<<7);
		PORTD|=(1<<6);
		PORTD&=~(1<<7);*/

		LCD_displayString("end cw");

		break;
	case ACW:
		LCD_clearScreen();
		LCD_displayString(" acw");
		GPIO_ARR_setPinState(DCMOTOR_IN_2, HIGH);
		GPIO_ARR_setPinState(DCMOTOR_IN_1, LOW);
		/*DDRD|=(1<<6);
		DDRD|=(1<<7);
		PORTD|=(1<<7);
		PORTD&=~(1<<6);*/
		LCD_displayString("end acw");
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
	Reset_Timer1Conter();
	Timer1_resume();
	DcMotor_rotate(a_state,a_speed);
	while (g_sec<a_time){
		LCD_moveCursor(1,0);
		LCD_intgerToString(g_sec);
	}
	DcMotor_rotate(STOP,0);
	Reset_Timer1Conter();
}
