/*
 * lcd.h
 *
 *  Created on: Feb 11, 2022
 *      Author: Mohamed
 */

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"


/* Configuration Type Of LCD Mode */
/* Eror Detect If User Used Data Number Not 4 Or 8 */
#define LCD_DATA_BITS_MODE 8

#if (LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE !=8)
#error "Number Of Bits Mode Must Be 4 Or 8"
#endif

/* Configure Mode Of LCD */
/* 4 Bits Mode */
#if LCD_DATA_BITS_MODE == 4

#define LCD_MODE LCD_TWO_LINES_FOUR_BITS_MODE

/* Check Of Which Pins Will Be Used */
#define LCD_LAST_PORT_PINS

#ifdef  LCD_LAST_PORT_PINS
#define LCD_FIRST_DATA_PINS PIN4_ID
#else
#define LCD_FIRST_DATA_PINS PIN0_ID
#endif
#elif LCD_DATA_BITS_MODE == 8  /* 8 Bits Mode */
#define LCD_MODE LCD_TWO_LINES_EIGHT_BITS_MODE
#endif


/* Static Definations & Mode Of LCD */
/* Connection Of LCD To Microcontroller */
#define LCD_RS_PORT_ID   PORTD_ID
#define LCD_RS_PIN_ID    PIN4_ID

#define LCD_RW_PORT_ID  PORTD_ID
#define LCD_RW_PIN_ID   PIN5_ID

#define LCD_E_PORT_ID PORTD_ID
#define LCD_E_PIN_ID  PIN6_ID

#define LCD_DATA_PORT_ID  PORTC_ID

/*********************************************************************/

/*LCD Commands*/
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80
#define LCD_SHIFT_DISPLAY_TO_LEFT      0x18
#define LCD_SHIFT_DISPLAY_TO_RIGHT     0x1C


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 *  Initialization For  LCD
 */
void LCD_init(void);

/*
 * Send The Corresponding Command To LCD
 */

void LCD_sendCommand(uint8 command);

/*
 * Send Corresponding Character To LCD
 */
void LCD_displayCharacter(uint8 character);

/*
 * Send Corresponding String
 */

void LCD_displayString(uint8 *string);

/*
 * Move Cursor To Location Accoreing To Rows & Cols
 */
void LCD_moveCursor(uint8 row ,uint8 col);

/*
 * Write String From STarting Col & Row
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col ,uint8 *string);

/*
 * Clear LCD Screen
 */
void LCD_clearScreen(void);

/*
 * Get The Value As Interger And Display As String
 */
void LCD_intgerToString(int data);

#endif /* LCD_H_ */
