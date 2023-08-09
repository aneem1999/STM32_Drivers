/*
 * led.h
 *
 *  Created on: Jan 1, 2023
 *      Author: ncm
 */

#ifndef LED_LED_H_
#define LED_LED_H_


typedef enum
{
	LED_0,
	LED_1,
	LED_2,
	LED_3,
	LED_4,
	LED_5,
	LED_6,
	LED_7,


}LED_t;

void LED_Init();
void LED_ON(LED_t led);
void LED_OFF(LED_t led);
void LED_TOGGLE(LED_t led);


#endif /* LED_LED_H_ */
