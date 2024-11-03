/*
 * dcMotor.h
 *
 *  Created on: 6 Oct 2024
 *      Author: MSI
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_
#include"../common/std_types.h"
#define DCMOTOR_IN_1 GPIO_PD6
#define DCMOTOR_IN_2 GPIO_PD7
#define DCMOTOR_E1 GPIO_PB3

typedef enum {
	CW, ACW, STOP
} DCMOTOR_STATE;

void DcMotor_init();

void DcMotor_rotate( DCMOTOR_STATE, uint8 speed);
void DcMotor_OnForTime(DCMOTOR_STATE a_state, uint8 a_speed,uint16 a_time);
#endif /* DCMOTOR_H_ */
