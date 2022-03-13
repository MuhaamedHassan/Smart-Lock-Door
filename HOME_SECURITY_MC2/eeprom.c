/*
 * eeprom.c
 *
 *  Created on: Feb 28, 2022
 *      Author: Mohamed
 */


#include "twi.h"
#include "eeprom.h"

/*
 * 1- Select Adress Of EEPROM
 * 2- Write Data On It
 * Note
 * Adress Of EEPROM is 11 Bit So We Take Last 3 Bits And Add Them To 0101 And R/W Bit At First
 * Then Send 8 Bit Of Adress
 */
uint8 EEPROM_writeByte(uint16 u16_address , uint8 u8_data)
{
	/* Start Bit To Bus */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
	return ERROR ;

	/* Sending Device Adress */
	/*
	 * Take First 3 Bits Of 11 Bit  and | With 1010 Then Castong As uint8 + write
	 */
	TWI_writeByte((uint8)(0xA0 | ((u16_address & 0x0700)>>7)));
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR ;

	/* Sending Remaing 8 Bits Of Adress */
	TWI_writeByte((uint8)(u16_address));
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR ;

	/* Sending Data */
	TWI_writeByte(u8_data);
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR ;

	/* Sending Stop Bit */
	TWI_stop();

	return SUCCESS ;
}

/*
 *  Start Bit
 * 1- Select Adress Of EEPROM 11-BIT
 * 2- Send Last 3 Bit Of Adress + ( Write )
 * 3- Send Remaining 8 Bits
 * Start Bit
 * 4- Send Last 3 Bit Of Adress + ( Read )
 * 5- Read Byte With ACK
 */

uint8 EEPROM_readByte(uint16 u16_address ,  uint8 *u8_data)
{
	/* Start Bit */
	TWI_start();
	if(TWI_getStatus() != TWI_START)
		return ERROR ;

	/* Sending Device Adress */
	/*
	 * Take First 3 Bits Of 11 Bit  and | With 1010 Then Castong As uint8 + write
	*/
	TWI_writeByte((uint8)((0xA0) | ((u16_address & 0x0700)>>7)));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR ;

	/* Sending Remaining Adress */
	TWI_writeByte((uint8)(u16_address));
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR ;

	/* Sending Repeat Start Again */
	TWI_start();
	if(TWI_getStatus() != TWI_REP_START)
		return ERROR ;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	     * memory location address and R/W=1 (Read) */
	TWI_writeByte((uint8)((0xA0) | ((u16_address & 0x0700)>>7) | 1));
	 if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
	        return ERROR;

	/* Read Byte from Memory without send ACK */
	*u8_data = TWI_readByteWithNoACK();
	if (TWI_getStatus() != TWI_MR_DATA_NACK)
		return ERROR;

	/* Send the Stop Bit */
	TWI_stop();

	return SUCCESS;
}

/*
 * 1- Select Adress Of EEPROM
 * 2- Write Data On It
 * Note
 * Adress Of EEPROM is 11 Bit So We Take Last 3 Bits And Add Them To 0101 And R/W Bit At First
 * Then Send 8 Bit Of Adress
 */

uint8 EEPROM_writeCombinedMSG(uint16 u16_address , uint8 arr[] , uint8 data_size)
{
	uint8 i = 0 ;
	/* Start Bit To Bus */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return ERROR;

	/* Sending Device Adress */
	/*
	 * Take First 3 Bits Of 11 Bit  and | With 1010 Then Castong As uint8 + write
	 */
	TWI_writeByte((uint8)(0xA0 | ((u16_address & 0x0700)>>7)));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	/* Sending Remaing 8 Bits Of Adress */
	TWI_writeByte((uint8) (u16_address));
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* Sending All The Array */
	for (i = 0 ; i < data_size ; i++)
	{
		/* Sending Data */
		TWI_writeByte(arr[i]);
		if (TWI_getStatus() != TWI_MT_DATA_ACK)
			return ERROR;
	}

	/* Sending Stop Bit */
	TWI_stop();

	return SUCCESS;
}

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
uint8 EEPROM_readCombinedMSG(uint16 u16_address , uint8 *ptr , uint8 data_size)
{
	uint8 i = 0 ;
	/* Start Bit */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return ERROR;

	/* Sending Device Adress */
	/*
	 * Take First 3 Bits Of 11 Bit  and | With 1010 Then Castong As uint8 + write
	 */
	TWI_writeByte((uint8)((0xA0) | ((u16_address & 0x0700)>>7)));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	/* Sending Remaining Adress */
	TWI_writeByte((uint8) (u16_address));
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* Sending Repeat Start Again */
	TWI_start();
	if (TWI_getStatus() != TWI_REP_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=1 (Read) */
	TWI_writeByte((uint8)((0xA0) | ((u16_address & 0x0700)>>7) | 1));
	if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
		return ERROR;

	for (i=0 ; i < data_size -1 ; i++)
	{
		/* Read Byte from Memory with send ACK */
		ptr[i] = TWI_readByteWithACK();
		if (TWI_getStatus() != TWI_MR_DATA_ACK)
			return ERROR;
	}

	/* Read Byte from Memory without send ACK */
	ptr[data_size-1] = TWI_readByteWithNoACK();
	if (TWI_getStatus() != TWI_MR_DATA_NACK)
		return ERROR;

	/* Sending Stop Bit */
	TWI_stop();

	return SUCCESS;

}
