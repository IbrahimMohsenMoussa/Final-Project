/*
 * ctrl.h
 *
 *  Created on: 30 Oct 2024
 *      Author: MSI
 */

#ifndef HAL_CTRL_H_
#define HAL_CTRL_H_
#include"../common/std_types.h"
#define CTRL_HANDSHAKE 'L'
#define CTRL_CONNECTION_SUCSSES 'O'
#define CTRL_CONNECTION_FAIL 'q'

uint8 CTRL_init();
#endif /* HAL_CTRL_H_ */
