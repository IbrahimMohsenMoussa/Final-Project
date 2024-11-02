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
#define CTRL_WAIT_PASS 'p'
#define HMI_PASSMATCH 'M'
#define CTRL_PASSMATCH 'M'
#define CTRL_PASSNOTMATCH 'm'
#define HMI_ACK 0xf
#define HMI_READY 0xe
#define COMM_ERROR 0xee
uint8 CTRL_checkPass(uint8 *a_pass1, uint8 *a_pass2);
uint8 CTRL_init();
#endif /* HAL_CTRL_H_ */
