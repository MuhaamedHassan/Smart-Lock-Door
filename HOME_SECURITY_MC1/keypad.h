/*
 * keypad.h
 *
 *  Created on: Feb 13, 2022
 *      Author: Mohamed
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "std_types.h"

/* Static Defintion Of KEYPAD */
/* Number Of ROWS & COLUMNS */
#define NUM_OF_ROWS  4
#define NUM_OF_COLS  4

/* Connection Of KEYPAD With MC PORT */
#define KEYPAD_PORT_ID PORTA_ID

/* Connection Of Rows & Colums PINS */
#define KEYPAD_FIRST_ROW_PIN_ID PIN0_ID
#define KEYPAD_FIRST_COL_PIN_ID PIN4_ID

/* Statues  Of KEYPAD Buttons */
#define KEYPAD_BUTTON_PRESSED LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED LOGIC_HIGH

/* Protoype & Informations Of Functions */

/* Return The Value Of  Key Pressed */

uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
