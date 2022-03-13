/*
 * timer.c
 *
 *  Created on: Mar 3, 2022
 *      Author: Mohamed
 */


#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*g_timer0_callBackPtr)(void) = NULL_PTR ;
static volatile void (*g_timer1_callBackPtr)(void) = NULL_PTR ;
static volatile void (*g_timer2_callBackPtr)(void) = NULL_PTR ;


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if (g_timer0_callBackPtr != NULL_PTR)
	{
		(*g_timer0_callBackPtr)();
	}
	else
	{
		/*Do Nothing */
	}
}
ISR(TIMER0_COMP_vect)
{
	if (g_timer0_callBackPtr != NULL_PTR)
	{
		(*g_timer0_callBackPtr)();
	}
	else
	{
		/*Do Nothing */
	}
}
ISR(TIMER1_OVF_vect)
{
	if (g_timer1_callBackPtr != NULL_PTR)
	{
		(*g_timer1_callBackPtr)();
	}
	else
	{
		/*Do Nothing */
	}
}
ISR(TIMER1_COMPA_vect)
{
	if (g_timer1_callBackPtr != NULL_PTR)
	{
		(*g_timer1_callBackPtr)();
	}
	else
	{
		/*Do Nothing */
	}
}
ISR(TIMER1_COMPB_vect)
{
	if (g_timer1_callBackPtr != NULL_PTR)
	{
		(*g_timer1_callBackPtr)();
	}
	else
	{
		/*Do Nothing */
	}
}
ISR(TIMER1_CAPT_vect)
{
	if (g_timer1_callBackPtr != NULL_PTR)
	{
		(*g_timer1_callBackPtr)();
	}
	else
	{
		/* Do Nothing */
	}

}
ISR(TIMER2_OVF_vect)
{
	if (g_timer2_callBackPtr != NULL_PTR)
		{
			(*g_timer2_callBackPtr)();
		}
		else
		{
			/* Do Nothing */
		}
}
ISR(TIMER2_COMP_vect)
{
	if (g_timer2_callBackPtr != NULL_PTR)
		{
			(*g_timer2_callBackPtr)();
		}
		else
		{
			/* Do Nothing */
		}
}

/*******************************************************************************
 *                       Functions & Descriptions                               *
********************************************************************************/
/* Description */
/*
 * 1 - Select Timer ID
 * 2- Select Timer Mode
 * 3- Select CTC MODE if Timer Mode Is CTC
 * 4- Select PWM Mode If Timer Mode Is PWM
 * 5- Select ICU Detection If  TimerId = TIMER1  & TimerMode = TIMER1_ICU
 * 6- Select Prescaler
 * 7- Initial Value
 * 8- Compare Value
 */
/* INPUT : Structure Of TIMER_configType */
/* OUTPUT : NONE */
void TIMER_init(const TIMER_configType *configptr)
{
	/* Select TIMER ID */
	switch (configptr->timer_id)
	{
	case TIMER0 :
		/* Select Timer0_Modes */
		if ( configptr->timer_mode == NORMAL)
		{
			/*Enable OverFlow Interrupt */
			#if TIMER0_OVF_INTERRUPT_ENABLE == TRUE
			SET_BIT(TIMSK,TOIE0)
			#endif
			/* SET Non-PWM Pin */
			SET_BIT(TCCR0,FOC0);
			/*CLEAR Waveform Generations Pins */
			CLEAR_BIT(TCCR0,WGM00);
			CLEAR_BIT(TCCR0,WGM01);
		}
		else if (configptr->timer_mode == CTC)
		{
			/* Enable Compare  Interrupt */
			#if TIMER0_CTC_INTERRUPT_ENABLE == TRUE
			SET_BIT(TIMSK,OCIE0);
			#endif
			/* Set PB3 Timer0 PIN As Output */
			SET_BIT(DDRB,PB3);
			/* SET Non-PWM Pin */
			SET_BIT(TCCR0, FOC0);
			/*Configure Waveform Generation Pins */
			CLEAR_BIT(TCCR0,WGM00);
			SET_BIT(TCCR0,WGM01);
			/* Check Operation Of CTC Mode */
			TCCR0 = (TCCR0 & 0xCF) | ((configptr->ctc_mode) << COM00);
		}
		else if (configptr->timer_mode == FAST_PWM)
		{
			/* Set PB3 Timer0 PIN As Output */
			SET_BIT(DDRB, PB3);
			/*Configure Waveform Generation Pins */
			SET_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			/* Check Operation Of PWM Mode */
			TCCR0 = (TCCR0 & 0xCF) | ((configptr->pwm_mode) << COM00);
		}
		else
		{
			/* Do Nothing */
		}

		/* Select Initial Value Of Timer0 */
		/* To Be Sure That Wont Add Value More Than TIMER0_MAX_VALUE */
		if (configptr->initial_value > TIMER0_MAX_VALUE)
		{
			/* Do Nothing */
		}
		else
		{
			/* Insert Initila Value To TCNT0 Register */
			TCNT0 = configptr->initial_value ;
		}

		/* Select Compare Value Of Timer0 */
		/* To Be Sure That Wont Add Value More Than TIMER0_MAX_VALUE */
		if(configptr->compare_value > TIMER0_MAX_VALUE)
		{
			/* Do Nothing */
		}
		else
		{
			/* Insert Compare Value To OCR0 Register */
			OCR0 = configptr->compare_value ;
		}

		/*Select Prescaler Value */
		TCCR0 = (TCCR0 & 0xF8) | (configptr->timer_prescaler) ;

		break;

	case TIMER1 :
		/*Select Timer1_Mode */
		if (configptr->timer_mode == NORMAL)
		{
			#if TIMER1_OVF_INTERRUPT_ENABLE == TRUE
			SET_BIT(TIMSK,TOIE1)
            #endif
			/*SET Non-PWM Pins & Select Normal Mode */
			TCCR1A = (1<<FOC1A) | (1<<FOC1B) ;
			CLEAR_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
		}
		else if (configptr->timer_mode == CTC)
		{
			#if TIMER1_CTCA_INTERRUPT_ENABLE == TRUE
			SET_BIT(TIMSK,OCIE1A);
			#endif
			#if TIMER1_CTCB_INTERRUPT_ENABLE == TRUE
			SET_BIT(TIMSK,OCIE1B);
			#endif
			/* SET Timer1 Pins As Output */
			SET_BIT(DDRD,PD4); /* OC1B */
			SET_BIT(DDRD,PD5); /* OC1A */
			/*Clear All TCCR1A Register
			 * 1-Assume Its Normal CTC Mode
			 * 2- Non Pwm Signal
			 */
			TCCR1A = (1<<FOC1A) | (1<<FOC1B);

			/* Configure As CTC Mode */
			SET_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);
			if(configptr->ctc_mode == CTC_NORMAL)
			{
				/* Do Nothing */
			}
			else if (configptr->ctc_mode == CTC_TOGGLE)
			{
				SET_BIT(TCCR1A,COM1A0);
				SET_BIT(TCCR1A,COM1B0);
			}
			else if ( configptr->ctc_mode == CTC_CLEAR)
			{
				SET_BIT(TCCR1A,COM1A1);
				SET_BIT(TCCR1A,COM1B1);
			}
			else
			{
				SET_BIT(TCCR1A, COM1A0);
				SET_BIT(TCCR1A, COM1B0);
				SET_BIT(TCCR1A, COM1A1);
				SET_BIT(TCCR1A, COM1B1);
			}
		}
		else if (configptr->timer_mode == FAST_PWM)
		{
			/* SET Timer1 Pins As Output */
			SET_BIT(DDRD, PD4); /* OC1B */
			SET_BIT(DDRD, PD5); /* OC1A */

			/*Configure TCCR1A & TCCR1B Registers */
			/* Assume We Use FAST_PWM_NORMAL MODE */
			TCCR1A = (1<<WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);

			if (configptr->pwm_mode  == PWM_NORMAL)
			{
				/* Do Nothing */
			}
			else if (configptr->pwm_mode == PWM_NON_INVERTING)
			{
				SET_BIT(TCCR1A,COM1A1);
				SET_BIT(TCCR1A,COM1B1);
			}
			else
			{
				SET_BIT(TCCR1A, COM1A1);
				SET_BIT(TCCR1A, COM1B1);
				SET_BIT(TCCR1A, COM1A0);
				SET_BIT(TCCR1A, COM1B0);
			}

		}
		/*Timer1 ICU Mode */
		else
		{
			#if TIMER1_ICU_INTERRUPT_ENABLE == TRUE
			SET_BIT(TIMSK,TICIE1);
			#endif
			/* Configure ICU Pin As Input */
			CLEAR_BIT(DDRD,PD6); /*PD6 PIN */

			/* ICU Mode Always Run In Normal Mode Non Pwm */
			TCCR1A = (1<<FOC1A) | (1<<FOC1B) ;
			CLEAR_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);

			/*Edge Detection */
			TCCR1B = (TCCR1B & 0xBF) | ((configptr->detection_edge)<<6);
		}
		/* Select Initial Value Of Timer1 */
		/* To Be Sure That Wont Add Value More Than TIMER0_MAX_VALUE */
		if (configptr->initial_value > TIMER1_MAX_VALUE) {
			/* Do Nothing */
		} else {
			/* Insert Initila Value To TCNT0 Register */
			TCNT1 = configptr->initial_value;
		}

		/* Select Compare Value Of Timer1 */
		/* To Be Sure That Wont Add Value More Than TIMER1_MAX_VALUE */
		if (configptr->compare_value > TIMER1_MAX_VALUE) {
			/* Do Nothing */
		} else {
			/* Insert Compare Value To ICR1 Register */
			ICR1 = configptr->compare_value;
		}

		/* Prescaler Of Timer */
		TCCR1B = (TCCR1B & 0xF8) | (configptr->timer_prescaler);

		break;

	case TIMER2:
		/* Select Timer2_Modes */
		if (configptr->timer_mode == NORMAL) {
			/*Enable OverFlow Interrupt */
#if TIMER2_OVF_INTERRUPT_ENABLE == TRUE
					SET_BIT(TIMSK,TOIE2)
					#endif
			/* SET Non-PWM Pin */
			SET_BIT(TCCR2, FOC2);
			/*CLEAR Waveform Generations Pins */
			CLEAR_BIT(TCCR2, WGM20);
			CLEAR_BIT(TCCR2, WGM21);
		} else if (configptr->timer_mode == CTC) {
			/* Enable Compare  Interrupt */
#if TIMER2_CTC_INTERRUPT_ENABLE == TRUE
					SET_BIT(TIMSK,OCIE2);
					#endif
			/* Set PD7 Timer2 PIN As Output */
			SET_BIT(DDRD, PD7);
			/* SET Non-PWM Pin */
			SET_BIT(TCCR2, FOC2);
			/*Configure Waveform Generation Pins */
			CLEAR_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);
			/* Check Operation Of CTC Mode */
			TCCR2 = (TCCR2 & 0xCF) | ((configptr->ctc_mode) << COM20);
		} else if (configptr->timer_mode == FAST_PWM) {
			/* Set PD7 Timer2 PIN As Output */
			SET_BIT(DDRD, PD7);
			/*Configure Waveform Generation Pins */
			SET_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);
			/* Check Operation Of PWM Mode */
			TCCR2 = (TCCR2 & 0xCF) | ((configptr->pwm_mode) << COM20);
		} else {
			/* Do Nothing */
		}

		/* Select Initial Value Of Timer2 */
		/* To Be Sure That Wont Add Value More Than TIMER2_MAX_VALUE */
		if (configptr->initial_value > TIMER2_MAX_VALUE) {
			/* Do Nothing */
		} else {
			/* Insert Initila Value To TCNT2 Register */
			TCNT2 = configptr->initial_value;
		}

		/* Select Compare Value Of Timer2 */
		/* To Be Sure That Wont Add Value More Than TIMER2_MAX_VALUE */
		if (configptr->compare_value > TIMER2_MAX_VALUE) {
			/* Do Nothing */
		} else {
			/* Insert Compare Value To OCR0 Register */
			OCR2 = configptr->compare_value;
		}

		/*Select Prescaler Value */
		TCCR2 = (TCCR2 & 0xF8) | (configptr->timer_prescaler);

		break;

	}
}


/*Description */
/*
 * 1- Deinit Any Timer
 */
/* Input : Variable Of TIMER_timerID */
/* Output : None */
void TIMER_deinit(TIMER_timerID timer_id)
{
	switch (timer_id)
	{
	case TIMER0 :
		TCCR0 = 0 ;
		TCNT0 = 0 ;
		OCR0 = 0 ;
		break ;
	case TIMER1 :
		TCCR1A = 0 ;
		TCCR1B = 0 ;
		TCNT1 = 0 ;
		ICR1 = 0 ;
		CLEAR_BIT(TIMSK,TICIE1);
		break;
	case TIMER2 :
		TCCR2 = 0 ;
		TCNT2 = 0 ;
		OCR2 = 0 ;
		break ;
	}
}


/*Description */
/*
 * Call Back Function For Timers
 */
/* Input : 1- Variable Of TIMER_timerID
 * 			2- Ptr2Func
 */
/*Output : None */

void TIMER_SetCallBack(TIMER_timerID timer_id ,void (*ptr2func)(void))
{
	switch(timer_id)
	{
	case TIMER0 :
		g_timer0_callBackPtr = ptr2func ;
		break ;
	case TIMER1 :
		g_timer1_callBackPtr = ptr2func ;
		break;
	case TIMER2 :
		g_timer2_callBackPtr = ptr2func ;
		break ;
	}
}

/*DESCRIPTION
 * Change TIMER1_Icu Detectig Edge */
/* INPUT : 1- Variable Of TIMER1_icuDetectionEdge */
/* OUTPUT : NONE */
void TIMER1_icuChangeEdgeDetection(TIMER1_icuDetectionEdge edge)
{
	TCCR1B = (TCCR1B & 0xBF) | (edge<<6) ;
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 TIMER1_icuGetInputCaptureValue(void)
{
	return ICR1 ;
}
/*
 * Description: Function to clear the Initial Value Of Timer1
 */
void TIMER1_clearInitialValue(void)
{
	TCNT1 = 0;
}

/*
 * Change Compare Value Of Timer
 */
/* Input : Timer_id , Compare Value */
/* OUTPUT : NONE */
void TIMER_changeCompareValue(TIMER_timerID timer_id , uint16 compare_value)
{
	switch(timer_id)
	{
	case TIMER0 :
		if (compare_value > TIMER0_MAX_VALUE)
		{
			/* Do Nothing */
		}
		else
		{
			OCR0 = compare_value ;
		}
		break ;
	case TIMER1 :
		if (compare_value > TIMER1_MAX_VALUE) {
			/* Do Nothing */
		} else {
			ICR1 = compare_value;
		}
		break;
	case TIMER2 :
		if (compare_value > TIMER2_MAX_VALUE) {
			/* Do Nothing */
		} else {
			OCR2 = compare_value;
		}
		break;
	}
}

/*
 * Change Initial Value
 */
/* Input : Timer_id , Initial  Value */
/* OUTPUT : NONE */
void TIMER_changeInitialValue(TIMER_timerID timer_id , uint16 initial_value)
{
	switch(timer_id)
		{
		case TIMER0 :
			if (initial_value > TIMER0_MAX_VALUE)
			{
				/* Do Nothing */
			}
			else
			{
				TCNT0 = initial_value ;
			}
			break ;
		case TIMER1 :
			if (initial_value > TIMER1_MAX_VALUE) {
				/* Do Nothing */
			} else {
				TCNT1 = initial_value;
			}
			break;
		case TIMER2 :
			if (initial_value > TIMER2_MAX_VALUE) {
				/* Do Nothing */
			} else {
				TCNT2 = initial_value;
			}
			break;
		}
}

/*
 * Timer0 Delay Function in Mile Seconds
 * We Assume Freq Timer = FCPU_64
 *  1- Change Freq Of Timer To FCPU_8 ( Enable Timer )
 *  2- Disable Timer After Delay
 *  3- We Should Initialize Timer0 To Be CTC Mode 0CO Disable
 */
#if TIMER0_CTC_INTERRUPT_ENABLE == FALSE
void TIMER0_delay_ms(uint64 time_in_ms)
{
	uint64 i = 0;

	/* Set Initial Value */
	TCNT0 = 0 ;
	/* Set Compare Value As  125-1 = 124*/
	OCR0 = 124 ;

	/* Change Clock To Be FCPU_64 */
	TCCR0 = (TCCR0 & 0xF8) | (0x03);

	for (i=0 ; i <time_in_ms ; i++)
	{
		while(BIT_IS_CLEAR(TIFR,OCF0));
		SET_BIT(TIFR,OCF0);
	}

	/* Disbale Clock */
	TCCR0  &= 0xF8 ;
}
#endif

