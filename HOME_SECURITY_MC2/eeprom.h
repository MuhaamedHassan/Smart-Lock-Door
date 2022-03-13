/*
 * eeprom.h
 *
 *  Created on: Feb 28, 2022
 *      Author: Mohamed
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* Check If The Function Is Happen Or No */
#define ERROR  FALSE
#define SUCCESS TRUE


/*******************************************************************************
 *                     Description & Prototypes                                *
 *******************************************************************************/

/*
 * 1- Select Adress Of EEPROM
 * 2- Write Data On It
 * Note
 * Adress Of EEPROM is 11 Bit So We Take Last 3 Bits And Add Them To 0101 And R/W Bit At First
 * Then Send 8 Bit Of Adress
 */
uint8 EEPROM_writeByte(uint16 u16_address , uint8 u8_data);

/*
 *  Start Bit
 * 1- Select Adress Of EEPROM 11-BIT
 * 2- Send Last 3 Bit Of Adress + ( Write )
 * 3- Send Remaining 8 Bits
 * Start Bit
 * 4- Send Last 3 Bit Of Adress + ( Read )
 * 5- Read Byte With ACK
 */

uint8 EEPROM_readByte(uint16 u16_address ,  uint8 *u8_data);


/*
 * 1- Select Adress Of EEPROM
 * 2- Write Data On It
 * Note
 * Adress Of EEPROM is 11 Bit So We Take Last 3 Bits And Add Them To 0101 And R/W Bit At First
 * Then Send 8 Bit Of Adress
 */

uint8 EEPROM_writeCombinedMSG(uint16 u16_address , uint8 arr[] , uint8 data_size);



/*
 *  Start Bit
 * 1- Select Adress Of EEPROM 11-BIT
 * 2- Send Last 3 Bit Of Adress + ( Write )
 * 3- Send Remaining 8 Bits
 * Start Bit
 * 4- Send Last 3 Bit Of Adress + ( Read )
 * 5- Read Byte With ACK until last  Byte
 * 6- Read Last Byte With NACK
 */
uint8 EEPROM_readCombinedMSG(uint16 u16_address , uint8 *ptr , uint8 data_size);


#endif /* EEPROM_H_ */
