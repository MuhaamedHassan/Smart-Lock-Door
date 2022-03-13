/*
 * main.c
 *
 *  Created on: Mar 12, 2022
 *      Author: Mohamed
 */




#include "timer.h"
#include "buzzer.h"
#include "dc_motor.h"
#include "eeprom.h"
#include "usart.h"
#include "twi.h"

void get_password(uint8 *password);
uint8 password_check(uint8 *password1 , uint8 *password2);

#define PASS_SIZE   5
#define MC1_READY 0x10
#define EEPROM_ADDRESS 0x0311

uint8 g_firsttimepasswrod = 0 ;
uint8 g_faulttimes = 0 ;


int main(void)
{
	uint8 pass1[PASS_SIZE] = {0};
	uint8 pass2[PASS_SIZE] = {0};
	uint8 mainoption = 0 ;
	/*  ( Initilization Of Timer To Use It As Delay To Our Functions )
	 * (TIMER0 ) - (CTC_MODE) - (CTC_NORMAL OC0 Disconnected )
	 * (No Pwm) - (No ICU) - (FCPU_64)- Initial val = 0 - comapre val = 0
	 */
	TIMER_configType timer0_config = { TIMER0, CTC, CTC_NORMAL, PWM_NORMAL,
			TIMER1_FALLING_EDGE, FCPU_64, 0, 0 };
	/*
	 * Timer2 Of Pwm Signal Of Motor
	 */
	TIMER_configType timer2_config = { TIMER2, FAST_PWM, CTC_NORMAL, PWM_NON_INVERTING,
				TIMER1_FALLING_EDGE, FCPU_64, 0, 0 };
	/*(Initialization Of USART )
	 * Baudrate - Synchrounization - parity - stopbit - size of data
	 */
	USART_configType usart_config = { 9600, ASYNCHRONOUS, OFF, BIT_1, BIT_8 };

	/*
	 * Initilization Of TWI
	 * Speed 400K & Adress 0x02
	 */

	TWI_configType twi_config = {0x02,K_400};

	/*
	 * Initilizations Functions
	 */
	BUZZER_init();
	DCMOTOR_init();
	TWI_init(&twi_config);
	TIMER_init(&timer0_config);
	USART_init(&usart_config);
	TIMER_init(&timer2_config);

	while(1)
	{
		if (g_firsttimepasswrod == 0)
		{
			/* Get 1st Password Until ' = ' */
			get_password(pass1);
			/* Get 2nd Password Until ' = ' */
			get_password(pass2);
			/* Check If Password Is Equal */
			/* Wait Until MC1 Be Ready To Get Result */
			while (USART_recieveByte() != MC1_READY);


			if (password_check(pass1, pass2))
			{
				USART_sendString("MATCH#");
				g_firsttimepasswrod = 1 ;

				/*Save Password At EEPROM */
				EEPROM_writeCombinedMSG(EEPROM_ADDRESS, pass1, PASS_SIZE);
			}
			else
			{
				USART_sendString("UNMATCH#");
				g_firsttimepasswrod = 0 ;
			}
		}
		else
		{
			/* Get Password From User & save it in pass1 */
			get_password(pass1);
			/* Get User Option */
			mainoption = USART_recieveByte();
			/*Get Password From EEPROM  & Save It In Pass2*/
			EEPROM_readCombinedMSG(EEPROM_ADDRESS, pass2, PASS_SIZE);



			if (mainoption == '+')
			{
				/* Check Password */
				if (password_check(pass1, pass2))
				{
					/* Wait Until MC1 Be Ready To Get Result */
					while (USART_recieveByte() != MC1_READY);
					/* Tell MC1 That Pw Is Match */
					USART_sendString("MATCH#");
					/* Rotate Dc Motor For 15 Sec CW */
					DCMOTOR_rotate(100, CW_MOTOR);
					TIMER0_delay_ms(15000);
					/* Rotet Dc Motor For 15 Sec CCW */
					DCMOTOR_rotate(100, CCW_MOTOR);
					TIMER0_delay_ms(15000);
					DCMOTOR_rotate(100, OFF_MOTOR);
					g_faulttimes = 0;
				}
				else
				{
					/* Wait Until MC1 Be Ready To Get Result */
					while (USART_recieveByte() != MC1_READY);
					/*Tell MC1 That Pw Isnot Match */
					USART_sendString("UNMATCH#");
					g_faulttimes++;

					if (g_faulttimes == 3)
					{
						/* On Buzzer For 1 Mint */
						BUZZER_on();
						TIMER0_delay_ms(60000);
						BUZZER_off();
						g_faulttimes = 0;
					}
				}
			}
			else
			{
				if (password_check(pass1, pass2))
				{
					/* Wait Until MC1 Be Ready To Get Result */
					while (USART_recieveByte() != MC1_READY);
					/* Tell MC1 That Pw Is Match */
					USART_sendString("MATCH#");
					/* Repeat Step 1 Again */
					g_firsttimepasswrod = 0 ;
					g_faulttimes = 0 ;
				}
				else
				{
					/* Wait Until MC1 Be Ready To Get Result */
					while (USART_recieveByte() != MC1_READY);
					/*Tell MC1 That Pw Isnot Match */
					USART_sendString("UNMATCH#");
					g_faulttimes++;

					if (g_faulttimes == 3) {
						/* On Buzzer For 1 Mint */
						BUZZER_on();
						TIMER0_delay_ms(60000);
						BUZZER_off();
						g_faulttimes = 0;
					}
				}
			}
		}

	}

}

/*
 * Get Password Until '=' And Save It At Array
 */
void get_password(uint8 *password)
{
	uint8 i = 0;
	uint8 data = 0;
	while(1)
	{
		/* Recive Data */
		data=USART_recieveByte();
		if (data == '=')
		{
			return ;
		}
		else
		{
			password[i] = data ;
			i++ ;
		}

	}
}

/*
 *  Check Password Assurance
 *  if password Is Match Return 1
 *  if Password Isnot Match Return 0
 */
uint8 password_check (uint8 *password1 , uint8 *password2)
{
	uint8 i = 0 ;
	for ( i = 0 ; i< PASS_SIZE ; i++)
	{
		if ( password1 [i]  != password2[i])
		{
			return 0 ;
		}
		else
		{
			/* Do Nothing */
		}
	}
	return 1 ;
}
