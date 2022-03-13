/*
 * twi.c
 *
 *  Created on: Feb 27, 2022
 *      Author: Mohamed
 */

#include "twi.h"
#include "common_macros.h"
#include <avr/io.h>

/*
 *1- Assume That No Prescaller TWPS = 1
 *2- Select Clock Of Master
 *3 - Put Adress When Work As Slave
 *4-Enable TWI
 */
 void TWI_init(const TWI_configType * configptr)
 {
	 /*
	  * We Assume That FCPU = 8 MHZ And Prescaller Is 0
	  */
	 /* Prescaller = 0 */
	 TWSR = 0 ;
	 if (configptr->boud_rate == K_100)
	 {
		 TWBR = TWI_TWBR_CLK_100 ;
	 }
	 else if (configptr ->boud_rate == K_400)
	 {
		 TWBR = TWI_TWBR_CLK_400 ;
	 }

	 /* Adress Of Device When Work As Slave */
	 /* We Take First  7- Bits Of Ur Number */
	 TWAR = (configptr->slave_adress) << 1 ;

	 /* Enable TWI & Interrupt If TRUE */
	#if TWI_INTERRUPT_ENABLE == TRUE

	 TWCR = (1<<TWEN) | (1<<TWIE);
	#else
	 TWCR = (1<<TWEN);
	#endif
 }

 /*
  * Send Start Bit At Bus
  */

 void TWI_start(void)
 {
	#if TWI_INTERRUPT_ENABLE == TRUE
	 TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWIE);
	#else
	 TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	 /* Wait Until Bit Is Set To indicate That Start Bit Is Set To Bus */
	 while (BIT_IS_CLEAR(TWCR,TWINT));
	#endif
 }

 /* Send Stop Bit At Bus */

  void TWI_stop(void)
  {
	#if TWI_INTERRUPT_ENABLE == TRUE
	 TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN) | (1<<TWIE);
	#else
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	#endif
  }

  /* Writing Byte At Bus */

 void TWI_writeByte(uint8 data)
  {
	  /* To Avoid Writing During Transmission */
	  while (BIT_IS_SET(TWCR,TWWC));
	  /*Write Data */
	  TWDR = data ;

	#if TWI_INTERRUPT_ENABLE == TRUE
	 TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
	#else
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait Until Bit Is Set To indicate That Data Sent To Slave  */
	while (BIT_IS_CLEAR(TWCR,TWINT));
	#endif

  }

  /* Read Byte From Slave With Ack  That Mean Itsnot Last Byte */
 uint8 TWI_readByteWithACK(void)
   {
	#if TWI_INTERRUPT_ENABLE == TRUE
	   TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA) | (1<<TWIE);
	   return TWDR;
	#else
	   TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	   while(BIT_IS_CLEAR(TWCR,TWINT));
	   return TWDR;
	#endif
   }
   /*Read Byte From Slave Without ACK  taht Mean Its Last Byte */

    uint8 TWI_readByteWithNoACK(void)
    {
	#if TWI_INTERRUPT_ENABLE == TRUE
	   TWCR = (1<<TWINT) | (1<<TWEN)  | (1<<TWIE);
	   return TWDR;
	#else
	   TWCR = (1<<TWINT) | (1<<TWEN);
	   while(BIT_IS_CLEAR(TWCR,TWINT));
	   return TWDR;
	#endif
    }

    /*Get The Status Of TWI */
uint8 TWI_getStatus(void)
{
	uint8 status ;
	status = TWSR & 0xF8 ;
	return status ;
}
