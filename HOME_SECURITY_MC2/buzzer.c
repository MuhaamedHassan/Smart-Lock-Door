/*
 * buzzer.c
 *
 *  Created on: Mar 12, 2022
 *      Author: Mohamed
 */

#include "common_macros.h"
#include "gpio.h"
#include "buzzer.h"


/******************************************************************************
 *                  Prototype & Descriptions                                   *
 *****************************************************************************/

/*
 * Initialize Buzzer
 * ( Set The Direction Of Pi Is Output )
 */
void BUZZER_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
}

/*
 * Turn On Buzzer
 */
void BUZZER_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/*
 * Turn Off Buzzer
 */
void BUZZER_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
