/*
 * keypad.c
 *
 *  Created on: Feb 13, 2022
 *      Author: Mohamed
 */

#include "keypad.h"
#include "gpio.h"
#include "common_macros.h"


/* Static Prototype For Private Functions */

#if ( NUM_OF_COLS == 3 )

static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);

#elif ( NUM_OF_COLS == 4 )

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);

#endif

/****************************************************************************/

/* Declration Of Function */
/* Return The Value Of  Key Pressed */

uint8 KEYPAD_getPressedKey(void)
{
	/* Initialization For Local Variables Which Will Us At Looping & Values */
	uint8 col , row ;
	uint8 port_value = 0 ;

	while (1)
	{
		/* Looping For Cols */
		for(col = 0 ; col < NUM_OF_COLS ; col ++)
		{
			/* Setup The Direction Of Port */
			GPIO_setupPortDirection(KEYPAD_PORT_ID, PORT_INPUT);
			/* Setup The Direction Of Corrsponidng Pin As  Output */
			GPIO_setupPinDirection(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+col, PIN_OUTPUT);
			#if KEYPAD_BUTTON_PRESSED == LOGIC_LOW
			port_value = ~(1<<(KEYPAD_FIRST_COL_PIN_ID+col));
			#else
			port_value = (1<<(KEYPAD_FIRST_COL_PIN_ID+col));
            #endif
			/* Write The Value Of Port At KEYPAD Port Id */
			GPIO_writePort(KEYPAD_PORT_ID, port_value);

			/* Looping For Rows */
			for(row=0; row < NUM_OF_ROWS ; row ++)
			{
				if (GPIO_readPin(KEYPAD_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row) == KEYPAD_BUTTON_PRESSED)
				{
					#if NUM_OF_COLS == 3
					return KEYPAD_4x3_adjustKeyNumber((row*NUM_OF_COLS)+col+1);
					#else
					return KEYPAD_4x4_adjustKeyNumber((row*NUM_OF_COLS)+col+1);
					#endif
				}
				else
				{
					/* Do Nothing */
				}
			}
		}
	}
}

/* Display The Correct KEYPAD Button As Its Real Shape */

#if NUM_OF_COLS == 3

static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	uint8 key_button = 0 ;

	switch(button_number)
	{
	case 10 :
		key_button = '*';
		break;
	case 11:
		key_button = 0 ;
		break;
	case 12 :
		key_button = '#';
		break;
	default :
		key_button = button_number ;
		break ;
	}
	return key_button;
}

#elif NUM_OF_COLS == 4

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 key_button = 0 ;

		switch(button_number)
		{
		case 1:
		key_button = 7;
		break;
	case 2:
		key_button = 8;
		break;
	case 3:
		key_button = 9;
		break;
	case 4:
		key_button = '%'; // ASCII Code of %
		break;
	case 5:
		key_button = 4;
		break;
	case 6:
		key_button = 5;
		break;
	case 7:
		key_button = 6;
		break;
	case 8:
		key_button = '*'; /* ASCII Code of '*' */
		break;
	case 9:
		key_button = 1;
		break;
	case 10:
		key_button = 2;
		break;
	case 11:
		key_button = 3;
		break;
	case 12:
		key_button = '-'; /* ASCII Code of '-' */
		break;
	case 13:
		key_button = 13; /* ASCII of Enter */
		break;
	case 14:
		key_button = 0;
		break;
	case 15:
		key_button = '='; /* ASCII Code of '=' */
		break;
	case 16:
		key_button = '+'; /* ASCII Code of '+' */
		break;
	default:
		key_button = button_number;
		break;
		}
		return key_button;

}

#endif



