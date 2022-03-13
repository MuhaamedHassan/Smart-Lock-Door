/*
 * timer.h
 *
 *  Created on: Mar 3, 2022
 *      Author: Mohamed
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                            Preprocessor Macros                               *
********************************************************************************/
/* IF U Want To Enable Interrupt Make It TRUE ifnot Make It FALSE */

#define TIMER0_CTC_INTERRUPT_ENABLE  FALSE
#define TIMER0_OVF_INTERRUPT_ENABLE  FALSE
#define TIMER1_OVF_INTERRUPT_ENABLE  FALSE
#define TIMER1_CTCA_INTERRUPT_ENABLE FALSE
#define TIMER1_CTCB_INTERRUPT_ENABLE FALSE
#define TIMER1_ICU_INTERRUPT_ENABLE  FALSE
#define TIMER2_CTC_INTERRUPT_ENABLE  FALSE
#define TIMER2_OVF_INTERRUPT_ENABLE  FALSE



/* Maximum Value Of TIMERS Register To Avoid Select Over Value */
#define TIMER0_MAX_VALUE 255
#define TIMER1_MAX_VALUE 65535
#define TIMER2_MAX_VALUE 255
/*******************************************************************************
 *                            Types Of Variables                                *
********************************************************************************/
/*
 * Type To Select Timer_ID
 * (TIMER0 / TIMER1 / TIMER2 )
 */
typedef enum {
	TIMER0 , TIMER1 ,TIMER2
}TIMER_timerID;

/*
 * Types To Select Mode Of Timer
 * (NORMAL / CTC / FAST_PWM / TIMER1_ICU )
 */
typedef enum {
	NORMAL ,  CTC = 2 , FAST_PWM , TIMER1_ICU
}TIMER_mode;

/*
 * Type To Select CTC MODE
 * ( NORMAL / TOGGLE / CLEAR / SET )
 */
typedef enum {
	CTC_NORMAL , CTC_TOGGLE , CTC_CLEAR , CTC_SET
}TIMER_ctcMode;

/*
 * Type To Select PWM MODE
 * (NORMAL / NON-INVERTING / INVERTING )
 */
typedef enum {
	PWM_NORMAL , PWM_NON_INVERTING = 2 , PWM_INVERTING
}TIMER_pwmMode;

/*
 * type to Select Edge Detection Of  TIMER1_ICU
 * (TIMER1_FALLING_EDGE / TIMER1_RISING_EDGE )
 *  Note
 *  If U Use TIMER0 or TIMER2 So It Will Dont Care About Edge Detection
 *  Beacouse They Dont Support ICU
 */

typedef enum {
	TIMER1_FALLING_EDGE , TIMER1_RISING_EDGE
}TIMER1_icuDetectionEdge;

/*
 * type To Select Prescalling
 * ( NO_CLK , FCPU , FCPU_8 , FCPU_64 , FCPU_256 , FCPU_1024 , EXT_CLK_FALLING , EXT_CLK_RISING)
 */
typedef enum {
	NO_CLK , FCPU , FCPU_8 , FCPU_64 , FCPU_256 , FCPU_1024 , EXT_CLK_FALLING , EXT_CLK_RISING
}TIMER_prescaler;


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

typedef struct {
	TIMER_timerID timer_id ;
	TIMER_mode    timer_mode ;
	TIMER_ctcMode ctc_mode ;
	TIMER_pwmMode pwm_mode ;
	TIMER1_icuDetectionEdge  detection_edge ;
	TIMER_prescaler timer_prescaler ;
	uint16 initial_value ;
	uint16 compare_value ;

}TIMER_configType;


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
void TIMER_init(const TIMER_configType * configptr);


/*Description */
/*
 * 1- Deinit Any Timer
 */
/* Input : Variable Of TIMER_timerID */
/* Output : None */
void TIMER_deinit(TIMER_timerID timer_id);

/*Description */
/*
 * Call Back Function For Timers
 */
/* Input : 1- Variable Of TIMER_timerID
 * 			2- Ptr2Func
 */
/*Output : None */

void TIMER_SetCallBack(TIMER_timerID timer_id ,void (*ptr2func)(void));


/*DESCRIPTION
 * Change TIMER1_Icu Detectig Edge */
/* INPUT : 1- Variable Of TIMER1_icuDetectionEdge */
/* OUTPUT : NONE */
void TIMER1_icuChangeEdgeDetection(TIMER1_icuDetectionEdge edge);

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 TIMER1_icuGetInputCaptureValue(void);

/*
 * Description: Function to clear the Initial Value Of Timer1
 */
void TIMER1_clearInitialValue(void);

/*
 * Change Compare Value Of Timer
 */
/* Input : Timer_id , Compare Value */
/* OUTPUT : NONE */
void TIMER_changeCompareValue(TIMER_timerID timer_id , uint16 compare_value);

/*
 * Change Initial Value
 */
/* Input : Timer_id , Initial  Value */
/* OUTPUT : NONE */
void TIMER_changeInitialValue(TIMER_timerID timer_id , uint16 initial_value);


/*
 * Timer0 Delay Function in Mile Seconds
 * We Assume Freq Timer = FCPU_64
 *  1- Change Freq Of Timer To FCPU_64 ( Enable Timer )
 *  2- Disable Timer After Delay
 */
#if TIMER0_CTC_INTERRUPT_ENABLE == FASLE
void TIMER0_delay_ms(uint64 time_in_ms);
#endif

#endif /* TIMER_H_ */
