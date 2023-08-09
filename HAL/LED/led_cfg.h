/*
 * led_cfg.h
 *
 *  Created on: Jan 1, 2023
 *      Author: ncm
 */

#ifndef LED_LED_CFG_H_
#define LED_LED_CFG_H_

#include "../MCAL_STM32F103C6/GPIO_Driver/GPIO.h"
typedef struct
{
	GPIO_Pinconfig_t LedPin;

	STATE_t activestate;
}LEDConfig_t;

extern LEDConfig_t LedConfigs[];
extern uint8_t LedConfigCount ;

#endif /* LED_LED_CFG_H_ */
