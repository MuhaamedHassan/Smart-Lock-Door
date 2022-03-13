/*
 * gpio.c
 *
 *  Created on: Feb 13, 2022
 *      Author: Mohamed
 */

#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>

/* Declration  & Descrition Of Function */

/*
 * Setup The Direction Of Pin
 * input : (port_number - pint_number - Direction Of Pin (PIN_INPUT/PIN_OUTPUT))
 * output : non
 * Note : If Input Pin Or Port Number Isnot Invalide It Does Nothing
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,
		GPIO_PinDirectionType direction) {
	if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {
		/* Do Nothing */
	} else {
		switch (port_num) {
		case PORTA_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRA, pin_num);
			} else {
				CLEAR_BIT(DDRA, pin_num);
			}
			break;
		case PORTB_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRB, pin_num);
			} else {
				CLEAR_BIT(DDRB, pin_num);
			}
			break;
		case PORTC_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRC, pin_num);
			} else {
				CLEAR_BIT(DDRC, pin_num);
			}
			break;
		case PORTD_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRD, pin_num);
			} else {
				CLEAR_BIT(DDRD, pin_num);
			}
			break;
		}
	}
}

/*
 * Write The Value To Coressponding Pin
 * input:(port_number - pin_number - Value Of Pin (LOGIC_HIGH / LOGIC_LOW ))
 * output :None
 * Note : If The Input Pin Or Port Isnot invalde it Does Nothing
 * note : The Function Will Enable/Disable Pull up Resistor depends on direction
 */

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value) {
	if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {
		/* Do Nothing */
	} else {
		switch (port_num) {
		case PORTA_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTA, pin_num);
			} else {
				CLEAR_BIT(PORTA, pin_num);
			}
			break;
		case PORTB_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTB, pin_num);
			} else {
				CLEAR_BIT(PORTB, pin_num);
			}
			break;
		case PORTC_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTC, pin_num);
			} else {
				CLEAR_BIT(PORTC, pin_num);
			}
			break;
		case PORTD_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTD, pin_num);
			} else {
				CLEAR_BIT(PORTD, pin_num);
			}
			break;
		}
	}
}

/*
 * Read The Value Of Corresponding Pi
 * input :(port_number - pin_number )
 * output: Value Of Pin (LOGIC_HIGH/LOGIC_LOW )
 * note : If The Input Port Or Pin Isnot Invalde It Returns (LOGIC_LOW)
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num) {
	if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {
		return LOGIC_LOW;
	} else {
		switch (port_num) {
		case PORTA_ID:
			return GET_BIT(PINA, pin_num);
		case PORTB_ID:
			return GET_BIT(PINB, pin_num);
		case PORTC_ID:
			return GET_BIT(PINC, pin_num);
		case PORTD_ID:
			return GET_BIT(PIND, pin_num);
		}
	}
}

/*
 * Setup The Direction Of Port
 * input :(port_num,The Direction Of Port (PORT_INPUT/PORT_OUTPUT))
 * output: None
 * Note : If The Input Port Isnot Correct It Handle Nothing
 */

void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction) {
	if (port_num >= NUM_OF_PORTS) {
		/* Do Nothing */
	} else {
		switch (port_num) {
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;

		}
	}
}

/*
 * Write The Corresponding Value At Port
 * input : (port_number,value Of Port )
 * output : None
 * Note : If The PortNumber Is Invalide The Function Handle Nothing
 */
void GPIO_writePort(uint8 port_num, uint8 value) {
	if (port_num >= NUM_OF_PORTS) {
		/* Do Nothing */
	} else {
		switch (port_num) {
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

/*
 * Read The Corresponding Value From Port
 * input : (port_number )
 * output: The Value Of Port
 * Note : If The Port Number Is Invalide  It Return (Zero )
 */
uint8 GPIO_readPort(uint8 port_num) {
	if (port_num >= NUM_OF_PORTS) {
		return 0;
	} else {
		switch (port_num) {
		case PORTA_ID:
			return PINA;
		case PORTB_ID:
			return PINB;
		case PORTC_ID:
			return PINC;
		case PORTD_ID:
			return PIND;
		}
	}
}

