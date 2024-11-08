 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/ 

#ifndef TWI_H_
#define TWI_H_

#include "../common/std_types.h"


#include "../common/std_types.h"

typedef enum {
    TWI_PRESCALER_1 = 1,   // No prescaling
    TWI_PRESCALER_4,       // Prescaler of 4
    TWI_PRESCALER_16,      // Prescaler of 16
    TWI_PRESCALER_64       // Prescaler of 64
} TWI_Prescaler;

typedef struct {
    uint32 clock;               /**< TWI clock frequency in Hz (e.g., 100000 for 100kHz) */
    TWI_Prescaler prescaler;    /**< TWI prescaler selection */
    uint8 address;              /**< TWI address in slave mode (7-bit address) */
    boolean enableGeneralCall;  /**< Enable or disable general call recognition */
} TWI_Config;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(TWI_Config*);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);


#endif /* TWI_H_ */
