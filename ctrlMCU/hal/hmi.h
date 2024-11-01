/*
 * ctrl.h
 *
 *  Created on: 30 Oct 2024
 *      Author: MSI
 */

#ifndef HAL_HMI_H_
#define HAL_HMI_H_
#include"../common/std_types.h"
#define HMI_HANDSHAKE 'L'
#define HMI_CONNECTION_SUCSSES 'O'
#define HMI_CONNECTION_FAIL 'Q'
#define HMI_HANDSHAKE 'L'
#define HMI_WAIT_PASS 'p'
#define HMI_PASSMATCH 'M'
#define HMI_PASSNOTMATCH 'm'
#define HMI_ACK 0xf
#define HMI_READY 0xe
#define COMM_ERROR 0xee
uint8 HMI_init();
uint8  HMI_command();
uint8 HMI_ready();
void HMI_checkPass();
#endif /* HAL_HMI_H_ */
