/*
 * led.c
 *
 *  Created on: Jan 1, 2023
 *      Author: ncm
 */


#include "../LIB/stm32f103x6.h"
#include "../MCAL_STM32F103C6/GPIO_Driver/GPIO.h"
#include "led.h"
#include "led_cfg.h"


/*
Initialize Led in Led configurations array as Output
with configurable pin, port , with/without internal pull up resistor
and configurable activation state depend on HW connections
 */
void LED_Init()
{
	uint8_t index=0;
	for (index = 0; index < LedConfigCount; index++)
	{
		MCAL_GPIO_Init(LedConfigs[index].LedPin.GPIOx ,&LedConfigs[index].LedPin);
	}

}

/*Write high to Led*/
void LED_ON(LED_t led)
{
	MCAL_GPIO_WritePin(LedConfigs[led].LedPin.GPIOx,LedConfigs[led].LedPin.PinNum,LedConfigs[led].activestate);
}

/*Write Low to Led*/
void LED_OFF(LED_t led)
{
	if(LedConfigs[led].activestate == HIGH)
		MCAL_GPIO_WritePin(LedConfigs[led].LedPin.GPIOx,LedConfigs[led].LedPin.PinNum,LOW);
	else
	{
		MCAL_GPIO_WritePin(LedConfigs[led].LedPin.GPIOx,LedConfigs[led].LedPin.PinNum,HIGH);

	}

}


void LED_TOGGLE(LED_t led)
{
	MCAL_GPIO_TogglePin(LedConfigs[led].LedPin.GPIOx,LedConfigs[led].LedPin.PinNum);
}
