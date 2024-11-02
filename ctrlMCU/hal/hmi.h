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
#define HMI_ACK 'A'
#define HMI_READY 'R'
#define COMM_ERROR 'E'
uint8 HMI_init();
uint8  HMI_command();
uint8 HMI_ready();
void HMI_checkPassMatch();
extern char g_pass1[6];
extern char g_pass2[6];
#endif /* HAL_HMI_H_ */
