/*
 * led_cfg.c
 *
 *  Created on: Jan 1, 2023
 *      Author: ncm
 */



/*
Led Configurations
@note : Pin and Port must not be used by another resources
LED_t mapped to led index
i.e LED_0 --> LedConfigs[0]
*/

#include "led_cfg.h"

LEDConfig_t LedConfigs[]={

	{{GPIO_PIN13, GPIOA, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_10M} , HIGH},

};



uint8_t LedConfigCount = sizeof(LedConfigs)/sizeof(LEDConfig_t);
