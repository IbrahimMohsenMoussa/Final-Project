/*
 * pir.h
 *
 *  Created on: 5 Nov 2024
 *      Author: MSI
 */

#ifndef HAL_PIR_H_
#define HAL_PIR_H_
#include"../common/std_types.h"
#define PIR_PIN GPIO_PC2
void PIR_init();
uint8 PIR_read();
#endif /* HAL_PIR_H_ */
