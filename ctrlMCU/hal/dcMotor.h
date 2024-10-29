/*
 * dcMotor.h
 *
 *  Created on: 6 Oct 2024
 *      Author: MSI
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_
#include"../common/std_types.h"
#define DCMOTOR_IN_1 GPIO_PB0
#define DCMOTOR_IN_2 GPIO_PB1
#define DCMOTOR_E1 GPIO_PB3

typedef enum {
	CW, ACW, STOP
} DCMOTOR_STATE;

void DcMotor_init();

void DcMotor_rotate( DCMOTOR_STATE, uint8 speed);
#endif /* DCMOTOR_H_ */
