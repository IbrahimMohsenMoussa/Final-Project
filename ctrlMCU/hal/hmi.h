/*
 * ctrl.h
 *
 *  Created on: 30 Oct 2024
 *      Author: MSI
 */

#ifndef HAL_HMI_H_
#define HAL_HMI_H_
#include"../common/std_types.h"
#define CTRL_HANDSHAKE 'L'
#define CTRL_CONNECTION_SUCSSES 'O'
#define CTRL_CONNECTION_FAIL 'Q'

uint8 HMI_init();
#endif /* HAL_HMI_H_ */
