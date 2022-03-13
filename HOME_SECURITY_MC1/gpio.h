/*
 * gpio.h
 *
 *  Created on: Feb 13, 2022
 *      Author: Mohamed
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"


/* Definations Of Microcontrollers */
/* This Defination Wont Chnage In Run Time */
/* Ports ID */
#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

/* PINS ID */
#define PIN0_ID 0
#define PIN1_ID 1
#define PIN2_ID 2
#define PIN3_ID 3
#define PIN4_ID 4
#define PIN5_ID 5
#define PIN6_ID 6
#define PIN7_ID 7


/* Number Of Ports & Pins Per Port */
#define NUM_OF_PORTS  4
#define NUM_OF_PINS_PER_PORT 8

/***************************************************************************/

/* Types Of Data Which Will Use At Functions  As Input Argument */
/* Type Of PinDirectionType */

typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

/* Type Of PortDirectionType */
typedef enum {
	PORT_INPUT,PORT_OUTPUT= 0xFF
}GPIO_PortDirectionType;

/*****************************************************************************/

/*
 *  Prototype  & Description Of Each Function
 */

/*
 * Setup The Direction Of Pin
 * input : (port_number - pint_number - Direction Of Pin (PIN_INPUT/PIN_OUTPUT))
 * output : non
 * Note : If Input Pin Or Port Number Isnot Invalide It Does Nothing
 */
void GPIO_setupPinDirection(uint8 port_num , uint8 pin_num ,GPIO_PinDirectionType direction);


/*
 * Write The Value To Coressponding Pin
 * input:(port_number - pin_number - Value Of Pin (LOGIC_HIGH / LOGIC_LOW ))
 * output :None
 * Note : If The Input Pin Or Port Isnot invalde it Does Nothing
 * note : The Function Will Enable/Disable Pull up Resistor depends on direction
 */

void GPIO_writePin(uint8 port_num,uint8 pin_num,uint8 value);


/*
 * Read The Value Of Corresponding Pi
 * input :(port_number - pin_number )
 * output: Value Of Pin (LOGIC_HIGH/LOGIC_LOW )
 * note : If The Input Port Or Pin Isnot Invalde It Returns (LOGIC_LOW)
 */
uint8 GPIO_readPin(uint8 port_num,uint8 pin_num);

/*
 * Setup The Direction Of Port
 * input :(port_num,The Direction Of Port (PORT_INPUT/PORT_OUTPUT))
 * output: None
 * Note : If The Input Port Isnot Correct It Handle Nothing
 */

void GPIO_setupPortDirection(uint8 port_num,GPIO_PortDirectionType direction);

/*
 * Write The Corresponding Value At Port
 * input : (port_number,value Of Port )
 * output : None
 * Note : If The PortNumber Is Invalide The Function Handle Nothing
 */
void GPIO_writePort(uint8 port_num,uint8 value);

/*
 * Read The Corresponding Value From Port
 * input : (port_number )
 * output: The Value Of Port
 * Note : If The Port Number Is Invalide  It Return (Zero )
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
