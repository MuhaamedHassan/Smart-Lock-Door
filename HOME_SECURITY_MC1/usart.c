/*
 * usart.c
 *
 *  Created on: Feb 21, 2022
 *      Author: Mohamed
 */


#include "common_macros.h"
#include "usart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#if RX_INTERRUPT_ENABLE == TRUE
ISR (USART_RXC_vect)
{

}
#endif
#if TX_INTERRUPT_ENABLE == TRUE
ISR (USART_TXC_vect)
{

}
#endif
#if EMPTY_INTERRUPT_ENABLE == TRUE
ISR (USART_UDRE_vect)
{

}
#endif
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void USART_init( const USART_configType *configptr)
{
	uint16 ubrr_value = 0;
	/* Using Double Trasmission Speed */
	UCSRA = (1<<U2X);

	/*
	 * Check If U Use One Of Interrupt Mode
	 * 1 - RX_INTERRUPT
	 * 2- TX_INTERRUPT
	 * 3- EMPTY_ITERRUPT
	 */
	#if RX_INTERRUPT_ENABLE == TRUE
	SET_BIT(UCSRA,RXCIE);
	#endif
	#if TX_INTERRUPT_ENABLE == TRUE
	SET_BIT(UCSRA,TXCIE);
	#endif
	#if EMPTY_INTERRUPT_ENABLE == TRUE
	SET_BIT(UCSRA,UDRIE);
	#endif

	/* Enable TX & RX */
	UCSRB |= (1<<RXEN) | (1<<TXEN);

	/* To Write In  UCSRC Register  Should Set USRSEL */
	SET_BIT(UCSRC,URSEL);

	/* USART MODE (SYNCHRONOUS , ASYNCHRONOUS ) */
	/*
	 * Clock  Polarity At Synchronous Mode only
	 * Is Rising In Tx Falling In Rx
	 * if U Want to Change It Change UCPOL Bit
	 */

	if (configptr ->mode == SYNCHRONOUS)
	{
		SET_BIT(UCSRC,UMSEL);
		CLEAR_BIT(UCSRC,UCPOL);

	}
	else
	{
		CLEAR_BIT(UCSRC,UMSEL);
		CLEAR_BIT(UCSRC,UCPOL);
	}

	/* Parity Mode Selection */

	UCSRC = (UCSRC & 0xCF) | ((configptr->parity_mode) << 4);

	/* Select Number Of Stop Bits */

	if (configptr->stop_bit == BIT_1)
	{
		CLEAR_BIT(UCSRC,USBS);
	}
	else
	{
		SET_BIT(UCSRC,USBS);
	}

	/* Character Size Of Data */

	if (configptr->data_size == BIT_9)
	{
		SET_BIT(UCSRB,UCSZ2);
		UCSRC = (UCSRC & 0xF9) | (0x3<<1);
	}
	else
	{
		CLEAR_BIT(UCSRB,UCSZ2);
		UCSRC = (UCSRC & 0xF9) | ((configptr->data_size) << 1);
	}
	/* Calculate the UBRR register value */
	ubrr_value = (uint16) (((F_CPU / (configptr->baud_rate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value >> 8;
	UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void USART_sendByte(const uint8 data)
{
	#if TX_INTERRUPT_ENABLE == TRUE
	UDR = data ;
	#else
	while (BIT_IS_CLEAR(UCSRA,UDRE));
	UDR = data ;
	/***********************************************************************
	 UDR = data ;
	 while(BIT_IS_CLEAR(UCSRA,TXC));
	 SET_BIT(UCSRA,TXC);
	 ***********************************************************************/
	#endif
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 * if there are Any Frame Or Priority Error This Function Will Return 0
 */
uint8 USART_recieveByte(void)
{
	/* Check For Frame Error */
	if (BIT_IS_SET(UCSRA,FE))
	{
		return 0 ;
	}
	else
	{
		/* Do Nothing */
	}
	/* Check For Parity Error */
	if (BIT_IS_SET(UCSRA,PE))
	{
		return 0 ;
	}
	else
	{
		/* Do Nothing */
	}
#if RX_INTERRUPT_ENABLE == TRUE
	return UDR ;
#else
	while (BIT_IS_CLEAR(UCSRA,RXC));
	return UDR ;
#endif
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void USART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		USART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void USART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = USART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = USART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
