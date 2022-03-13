/*
 * twi.h
 *
 *  Created on: Feb 27, 2022
 *      Author: Mohamed
 */

#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* If U Will Use  TWI With Interrupt Make It TRUE If Not Make It FALSE */
#define TWI_INTERRUPT_ENABLE FALSE
/*
 * We Assume That FCPU = 8 MHZ And Prescaller Is 0
 */
#define TWI_TWBR_CLK_100     32
#define TWI_TWBR_CLK_400     2

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Types Of Variables                                    *
 *******************************************************************************/

typedef enum {
	K_100 , K_400
}TWI_boudRate;

typedef struct {
	uint8 slave_adress ;
	TWI_boudRate boud_rate ;
}TWI_configType;

/*******************************************************************************
 *                      Description & Prototype                                *
 *******************************************************************************/
/*
 *1- Assume That No Prescaller TWPS = 1
 *2- Select Clock Of Master
 *3 - Put Adress When Work As Slave
 *4-Enable TWI
 */
 void TWI_init(const TWI_configType * configptr);

 /*
  * Send Start Bit At Bus
  */

 void TWI_start(void);


 /* Send Stop Bit At Bus */

 void TWI_stop(void);

 /* Writing Byte At Bus */

 void TWI_writeByte(uint8 data);


 /* Read Byte From Slave With Ack  That Mean Itsnot Last Byte */
 uint8 TWI_readByteWithACK(void);

 /*Read Byte From Slave Without ACK  taht Mean Its Last Byte */

 uint8 TWI_readByteWithNoACK(void);

 /*Get The Status Of TWI */
 uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
