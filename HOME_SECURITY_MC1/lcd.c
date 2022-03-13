/*
 * lcd.c
 *
 *  Created on: Feb 11, 2022
 *      Author: Mohamed
 */


#include "lcd.h"
#include "gpio.h"
#include <util/delay.h>



/*
 * Init Function For LCD
 */

void LCD_init(void)
{
	/*
	 * Setup The Direction Of  ( RS - RW - E ) As OUTPUT
	 */
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID, LCD_RW_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
	/***************************************************************/
	/* IF LCD_MODE IS 8 BITS Mode Setup All Data Port As OUTPUT */
	#if LCD_DATA_BITS_MODE == 8
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
	/* IF LCD_MODE IS 4 BITS MODE Setup Only 4 Connected Pins As OUTPUT */
	#elif LCD_DATA_BITS_MODE == 4
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PINS, PIN_OUTPUT);
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PINS+1, PIN_OUTPUT);
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PINS+2, PIN_OUTPUT);
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PINS+3, PIN_OUTPUT);
	LCD_sendCommand(LCD_GO_TO_HOME);
	#endif
	/* Send Command Of Your LCD MODE */
	LCD_sendCommand(LCD_MODE);

	/* Cursor Off */
	LCD_sendCommand(LCD_CURSOR_OFF);

	/* Clear LCD Screen */
	LCD_sendCommand(LCD_CLEAR_COMMAND);

}

/*
 * Send The Corresponding Command To LCD
 */

void LCD_sendCommand(uint8 command)
{
	uint8 value_of_port = 0 ;
	/* Rs = 0 To Select Command Register */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	/* RW = 0 To Write To LCD */
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);
	/* E = 1 Enable LCD */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);

	#if LCD_DATA_BITS_MODE == 4
	/* Read The Value Of All Ports */
	value_of_port = GPIO_readPort(LCD_DATA_PORT_ID);
	#ifdef LCD_LAST_PORT_PINS
	/* Get The Value Of Higher Nibble */
	value_of_port = (value_of_port & 0x0F) | (command & 0xF0);
    #else
	value_of_port = (value_of_port & 0xF0) | ((command & 0xF0) >>4 );
	#endif
	/* Write The Value Of Higher Nibble To Port */
	/* Send Higher Nibble Data To Screen  First 4 Bits */
	GPIO_writePort(LCD_DATA_PORT_ID, value_of_port);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);
	/* E = 0 Disable LCD Enable */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);
	/* E = 1  To Start Get Second Part Of Data */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	value_of_port = GPIO_readPort(LCD_DATA_PORT_ID);

	#ifdef LCD_LAST_PORT_PINS
	/* Get The Value Of Lower Nibble */
	value_of_port = (value_of_port & 0x0F) | ((command & 0x0F) << 4 );
	#else
	value_of_port = (value_of_port & 0xF0) | (command & 0x0F);
	#endif
	/* Write The Value Of Higher Nibble To Port */
	/* Send Higher Nibble Data To Screen  First 4 Bits */
	GPIO_writePort(LCD_DATA_PORT_ID, value_of_port);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);
	/* E = 0 Disable LCD Enable */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);
	#elif LCD_DATA_BITS_MODE == 8
	GPIO_writePort(LCD_DATA_PORT_ID, command);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);
	/* E = 0 Disable LCD Enable */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);
	#endif
}
void LCD_displayCharacter(uint8 character)
{
	uint8 value_of_port = 0;
	/* Rs = 1 To Select Data Register */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	/* RW = 0 To Write To LCD */
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);
	/* E = 1 Enable LCD */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);

#if LCD_DATA_BITS_MODE == 4
		/* Read The Value Of All Ports */
		value_of_port = GPIO_readPort(LCD_DATA_PORT_ID);
		#ifdef LCD_LAST_PORT_PINS
		/* Get The Value Of Higher Nibble */
		value_of_port = (value_of_port & 0x0F) | (character & 0xF0);
	    #else
		value_of_port = (value_of_port & 0xF0) | ((character & 0xF0) >>4 );
		#endif
		/* Write The Value Of Higher Nibble To Port */
		/* Send Higher Nibble Data To Screen  First 4 Bits */
		GPIO_writePort(LCD_DATA_PORT_ID, value_of_port);
		/* Delay For 1m Sec According To DataSheet Of LCD */
		_delay_ms(1);
		/* E = 0 Disable LCD Enable */
		GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
		/* Delay For 1m Sec According To DataSheet Of LCD */
		_delay_ms(1);
		/* E = 1  To Start Get Second Part Of Data */
		GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
		_delay_ms(1);

		value_of_port = GPIO_readPort(LCD_DATA_PORT_ID);

		#ifdef LCD_LAST_PORT_PINS
		/* Get The Value Of Lower Nibble */
		value_of_port = (value_of_port & 0x0F) | ((character & 0x0F) << 4 );
		#else
		value_of_port = (value_of_port & 0xF0) | (character & 0x0F);
		#endif
		/* Write The Value Of Higher Nibble To Port */
		/* Send Higher Nibble Data To Screen  First 4 Bits */
		GPIO_writePort(LCD_DATA_PORT_ID, value_of_port);
		/* Delay For 1m Sec According To DataSheet Of LCD */
		_delay_ms(1);
		/* E = 0 Disable LCD Enable */
		GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
		/* Delay For 1m Sec According To DataSheet Of LCD */
		_delay_ms(1);
		#elif LCD_DATA_BITS_MODE == 8
	GPIO_writePort(LCD_DATA_PORT_ID, character);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);
	/* E = 0 Disable LCD Enable */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* Delay For 1m Sec According To DataSheet Of LCD */
	_delay_ms(1);
#endif

}
void LCD_displayString(uint8 *string)
{
	/************************************************************************
	 uint8 i = 0;
	 while (string[i] != '\0')
	 {
	 LCD_displayCharacter(string[i]);
	 i++;
	 }
	 ***********************************************************************/
	/* Looping In String Until Null Pointer */
	while (*string != '\0')
	{
		LCD_displayCharacter(*string);
		string++;
	}
}
void LCD_moveCursor(uint8 row ,uint8 col)
{
	uint8 address_of_lcd = 0;

	switch(row)
	{
	case 0 : address_of_lcd = col ;
	break;
	case 1 : address_of_lcd = col+ 0x40;
	break;
	case 2: address_of_lcd = col + 0x10;
	break ;
	case 3: address_of_lcd = col + 0x50;
	break;
	}
	/* Move The LCD Cursor To Location */
	LCD_sendCommand(address_of_lcd | LCD_SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row, uint8 col ,uint8 *string)
{
	/* Move Cursor to corresponding row & col */
	LCD_moveCursor(row, col);
	/* Write String */
	LCD_displayString(string);
}
/*
 * Clear LCD Screen
 */
void LCD_clearScreen(void)
{
	/* Send Clear Command To Lcd */
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/*
 * Get The Value As Interger And Display As String
 */
void LCD_intgerToString(int data)
{

	char buff[16]; /* String to hold the ascii result */
	itoa(data, buff, 10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_displayString(buff); /* Display the string */
	/* Check If Data Is Negative */
//	if (data < 0)
//	{
//		/* Display Negative Character */
//		LCD_displayCharacter('-');
//		/* Make It Positive Before Iterations */
//		data *= -1 ;
//	}
//	uint8 rem = 0,result = 0,character=0 ;
//	uint8 counter = 0 , i ;
//	while (data != 0 )
//	{
//		rem = data%10 ;
//		result = (result *10) + rem ;
//		counter++;
//		data /= 10 ;
//	}

	/* Looping Until Number End Number Of Digit  */
	/*We Didnot Loop Until Zero To Avoid Numbers Like 60 / 70 */
//	for (i=0 ; i < counter ; i++)
//	{
//		character = result%10 ;
//		character += 48 ; /* Convert From Int To ASCII */
//		LCD_displayCharacter(character); /* Display ASCII */
//		result /= 10 ;
//	}
}

