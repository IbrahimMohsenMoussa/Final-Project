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
#define CTRL_WAIT_PASS_MEM 'U'
#define HMI_PASSMATCH 'M'
#define CTRL_PASSMATCH 'M'
#define CTRL_PASSNOTMATCH 'm'
#define HMI_ACK 'A'
#define HMI_READY 'R'
#define COMM_ERROR 'E'
#define COMM_SUCSSES 'S'
#define CTRL_OPEN_DOOR 'D'
#define CTRL_close_DOOR 'd'
#define HMI_PIR 'I'
#define BUZZER_ON 'B'
#define BUZZER_OFF 'b'
uint8 CTRL_checkPass(uint8 *a_pass);
uint8 CTRL_checkPassMatch(uint8 *a_pass1, uint8 *a_pass2);
uint8 CTRL_openDoor();
uint8 CTRL_closeDoor();
uint8 CTRL_init();
uint8 CTRL_waitForPir();
void CTRL_buzzer_on();
void CTRL_buzzer_off();
#endif /* HAL_CTRL_H_ */
