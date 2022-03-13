/*
 * main.c
 *
 *  Created on: Mar 7, 2022
 *      Author: Mohamed
 */



#include "gpio.h"
#include "keypad.h"
#include "timer.h"
#include "lcd.h"
#include "usart.h"

uint8 str_compare(uint8 *str1 , uint8 *str2);

#define MC1_READY 0x10

uint8 g_firsttimepasswrod = 0 ;
uint8 g_faulttimes = 0 ;


int main(void)
{
	uint8 str[20] = {0};
	/*  ( Initilization Of Timer To Use It As Delay To Our Functions )
	 * (TIMER0 ) - (CTC_MODE) - (CTC_NORMAL OC0 Disconnected )
	 * (No Pwm) - (No ICU) - (FCPU_64)- Initial val = 0 - comapre val = 0
	 */
	TIMER_configType timer_config = {TIMER0 ,CTC ,CTC_NORMAL ,PWM_NORMAL,TIMER1_FALLING_EDGE,
			FCPU_64,0,0
	};
	/*(Initialization Of USART )
	 * Baudrate - Synchrounization - parity - stopbit - size of data
	 */
	USART_configType usart_config = {9600 ,ASYNCHRONOUS,OFF,BIT_1,BIT_8};

	LCD_init();

	TIMER_init(&timer_config);

	USART_init(&usart_config);

	while(1)
	{
		if (g_firsttimepasswrod == 0)
		{
		LCD_displayString("Enter Pw : ");
		SendPassword();
		LCD_displayString("Reenter Pw : ");
		SendPassword();
		/* Tell MC2 That MC1 Ready To Know The Result Of 2 Pw */
		USART_sendByte(MC1_READY);
		/* Receive String */
		USART_receiveString(str);

			if (str_compare(str, "MATCH"))
			{
			g_firsttimepasswrod = 1 ;
			MainOptions();
			}
			else
			{
			g_firsttimepasswrod = 0;
			}
		}
		else
		{
			if (g_faulttimes == 3)
			{
				LCD_clearScreen();
				LCD_displayString("Wrong Pw");
				LCD_moveCursor(1, 0);
				LCD_displayString("For 3 Times");
				TIMER0_delay_ms(60000);
				g_faulttimes = 0;
			}
			MainOptions();
		}
	}

}

/* Sending Password To MC2 Until We Press = */
void SendPassword(void)
{
	uint8 key = 0 ;
	/* Move Cursor To Row 1 Col 0 */
	LCD_moveCursor(1,0);
	while(1)
	{
		/* Get Key From Keypad */
		key = KEYPAD_getPressedKey();
		if ( key == '=')
		{
			USART_sendByte(key);
			break ;
		}
		else
		{

			LCD_intgerToString(key);
			 //LCD_displayCharacter('*');
			USART_sendByte(key);
		}
		/* Delay For 1 Sec */
		TIMER0_delay_ms(500);
	}
	LCD_clearScreen();
	TIMER0_delay_ms(500);
}

/* Second Option After Get Pw For 1st Time */
void MainOptions (void)
{
	uint8 key = 0 ;
	uint8 str1[20]={0};
	LCD_clearScreen();
	LCD_displayString("+:Open Door : ");
	/* Move Cursor */
	LCD_moveCursor(1, 0);
	LCD_displayString("-:Change PW : ");

	while(1)
	{
		/* Get Key From Keypad */
		key = KEYPAD_getPressedKey();
		if (key == '+')
		{
			TIMER0_delay_ms(1000);
			LCD_clearScreen();
			LCD_displayString("Enter PW : ");
			SendPassword();
			/* Send The User Selection */
			USART_sendByte('+');
			/* Delay To Let MC2 Can Receive it */
			TIMER0_delay_ms(50);
			/* Tell MC2 That MC1 Ready To Know The Result Of 2 Pw */
			USART_sendByte(MC1_READY);
			/* Receive String */
			USART_receiveString(str1);

			if (str_compare(str1,"MATCH"))
			{
				LCD_clearScreen();
				LCD_displayString("Door Opened");
				TIMER0_delay_ms(30000);
				g_faulttimes = 0;
				break;
			}
			else if (str_compare(str1,"UNMATCH"))
			{
				LCD_displayString("Wrong PW ");
				TIMER0_delay_ms(1000);
				g_faulttimes++;
				break;
			}


		}
		else if (key == '-')
		{
			TIMER0_delay_ms(1000);
			LCD_clearScreen();
			LCD_displayString("Enter PW : ");
			SendPassword();
			/* Send The User Selection */
			USART_sendByte('-');
			/* Delay To Let MC2 Can Receive it */
			TIMER0_delay_ms(50);
			/* Tell MC2 That MC1 Ready To Know The Result Of 2 Pw */
			USART_sendByte(MC1_READY);
			/* Receive String */
			USART_receiveString(str1);

			if(str_compare(str1,"MATCH"))
			{
				LCD_displayString("Add New Pw ");
				TIMER0_delay_ms(1000);
				LCD_clearScreen();
				g_firsttimepasswrod = 0;
				g_faulttimes =0 ;
				break;
			}
			else if (str_compare(str1,"UNMATCH"))
			{
				LCD_displayString("Wrong Pw ");
				TIMER0_delay_ms(1000);
				g_faulttimes++;
				break;
			}
		}
		else
		{
			/* Do Nothing */
		}
	}
}

uint8 str_compare(uint8 *str1 , uint8 *str2)
{
	uint8 i = 0 ;
	while (str1[i] != '\0')
	{
		if ( str1[i] != str2 [i])
		{
			return 0 ;
		}
		i++ ;
	}
	return 1 ;
}
