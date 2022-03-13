/*
 * buzzer.h
 *
 *  Created on: Mar 12, 2022
 *      Author: Mohamed
 */

#ifndef BUZZER_H_
#define BUZZER_H_


#include "std_types.h"

/******************************************************************************
 *                     			Definations                                   *
 *****************************************************************************/

#define BUZZER_PORT_ID PORTA_ID
#define BUZZER_PIN_ID  PIN2_ID

/******************************************************************************
 *                  Prototype & Descriptions                                   *
 *****************************************************************************/

/*
 * Initialize Buzzer
 * ( Set The Direction Of Pi Is Output )
 */
void BUZZER_init(void);


/*
 * Turn On Buzzer
 */
void BUZZER_on(void);



/*
 * Turn Off Buzzer
 */
void BUZZER_off(void);

#endif /* BUZZER_H_ */
