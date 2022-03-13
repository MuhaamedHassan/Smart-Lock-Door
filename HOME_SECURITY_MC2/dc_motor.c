/*
 * dc_motor.c
 *
 *  Created on: Feb 22, 2022
 *      Author: Mohamed
 */


#include "dc_motor.h"
#include "gpio.h"
#include "timer.h"


/*
 * Configure Motor Pins As Output
 * And Make Dc Motor Stop At Begin
 */
void DCMOTOR_init(void)
{
	/*
	 * IN1 = OUTPUT
	 * IN2 = OUTPUT
	 * E = OUTPUT
	 */
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_IN_1,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_IN_2,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_E_PORT_ID, DC_MOTOR_E,PIN_OUTPUT);

	/*
	 * Stop Motor
	 */
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN_1, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN_2, LOGIC_LOW);

}

/*
 *  Select The Direction Of Rotation
 *  Select Speed Of Rotation
 */
void DCMOTOR_rotate(uint8 speed ,DCMOTOR_state state)
{
	uint8 duty_cycle = 0 ;

	if (state == CW_MOTOR)
	{
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN_1, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN_2, LOGIC_HIGH);

	}
	else if (state == CCW_MOTOR)
	{
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN_1, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN_2, LOGIC_LOW);

	}
	else
	{
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN_1, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN_2, LOGIC_LOW);
	}

	duty_cycle = (((float) speed /100) * TIMER2_MAX_VALUE);

	TIMER2_generatePWM(duty_cycle, PWM_NON_INVERTING);

}
