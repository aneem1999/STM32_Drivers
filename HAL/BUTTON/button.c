/*
 * button.c
 *
 *  Created on: Jan 1, 2023
 *      Author: ncm
 */

#include "button.h"
#include "button_cfg.h"



void BUTTON_Init()
{
	uint8_t index=0;
	GPIO_Pinconfig_t tempPin;
	tempPin.PinSpeed = GPIO_INPUT_MOD ;
	for(index = 0 ; index <ButtonConfigCount ; index++)
	{
		tempPin.PinNum = ButtonConfigs[index].PinNum ;
		tempPin.GPIOx =ButtonConfigs[index].GPIOx;
		tempPin.PinMode =ButtonConfigs[index].PinMode;

		MCAL_GPIO_Init(ButtonConfigs[index].GPIOx, &tempPin);
	}

}
BUTTON_Status_t BUTTON_GetStatus( BUTTON_t button)
{
	STATE_t ButtonState ;
	BUTTON_Status_t ButtonStatus;
	ButtonState = MCAL_GPIO_ReadPin(ButtonConfigs[button].GPIOx,ButtonConfigs[button].PinNum);

	/*
		ACTIVE		STATE		XOR     NOT
		-----------------------------------------
		LOW			LOW			0		1	(PRESSED)
		LOW			HIGH		1		0	(NOT_PRESSED)
		HIGH		LOW			1		0	(NOT_PRESSED)
		HIGH		HIGH		0		1   (PRESSED)
	*/


	ButtonStatus =((ButtonState ^ ButtonConfigs[button].ActiveState) == 0) ? PRESSED : NOT_PRESSED ;


	return ButtonStatus;

}
