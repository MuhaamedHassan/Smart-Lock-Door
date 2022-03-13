/*
 * usart.h
 *
 *  Created on: Feb 21, 2022
 *      Author: Mohamed
 */

#ifndef USART_H_
#define USART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* If U Want To Enable Rx Interrupt Make It True Ifnot Make It FALSE */
#define RX_INTERRUPT_ENABLE   FALSE
/* If U Want To Enable TX Interrupt Make It True Ifnot Make It FALSE */
#define TX_INTERRUPT_ENABLE   FALSE
/* If U Want To Enable EMPTY Interrupt Make It True Ifnot Make It FALSE */
#define EMPTY_INTERRUPT_ENABLE   FALSE

typedef enum {
	ASYNCHRONOUS , SYNCHRONOUS
}USART_mode;

typedef enum {
	OFF , EVEN_PARITY = 2 , ODD_PARITY
}USART_parityMode;

typedef enum {
	BIT_1 , BIT_2
}USART_stopBit;

typedef enum {
	BIT_5 , BIT_6 , BIT_7 , BIT_8 , BIT_9 = 7
}USART_characterSize;


typedef struct {
	uint16 baud_rate ;
	USART_mode mode ;
	USART_parityMode parity_mode ;
	USART_stopBit stop_bit ;
	USART_characterSize data_size ;
}USART_configType;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Functional responsible for Initialize the USART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void USART_init( const USART_configType *configptr);


/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void USART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 USART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void USART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void USART_receiveString(uint8 *Str); // Receive until #

#endif /* USART_H_ */
