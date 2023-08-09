/*
 * button_cfg.c
 *
 *  Created on: Jan 1, 2023
 *      Author: ncm
 */



#include "../LIB/stm32f103x6.h"
#include "../MCAL_STM32F103C6/GPIO_Driver/GPIO.h"

#include "button_cfg.h"

/*
Button Configurations
@note : Pin and Port must not be used by another resources
BUTTON_t mapped to button index
i.e BUTTON_0 --> ButtonConfigs[0]
 */
BUTTONConfig_t ButtonConfigs[] = {
		{GPIO_PIN1, GPIOA,GPIO_MODE_INPUT_FLOAT, LOW},
		{GPIO_PIN13, GPIOA,GPIO_MODE_INPUT_FLOAT, HIGH}


};
uint8_t ButtonConfigCount = sizeof(ButtonConfigs)/sizeof(BUTTONConfig_t) ;

