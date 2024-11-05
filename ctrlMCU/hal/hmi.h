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
#define HMI_WAIT_PASS_MEM 'U'
#define HMI_OPEN_DOOR 'D'
#define HMI_CLOSE_DOOR 'd'
uint8 HMI_init();
uint8  HMI_command();
uint8 HMI_ready();
uint8* HMI_checkPassMatch();
#define HMI_PIR 'I'
void HMI_checkPass();
uint8 MEM_getPassElem(uint8 a_passIndex);
void MEM_savePass(uint8 *a_pass);
extern uint8 g_pass[6];
void OpenDoor();
void CloseDoor();
void waitForPeople();
#endif /* HAL_HMI_H_ */
