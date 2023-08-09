/*
 * button_cfg.h
 *
 *  Created on: Jan 1, 2023
 *      Author: ncm
 */

#ifndef BUTTON_BUTTON_CFG_H_
#define BUTTON_BUTTON_CFG_H_



#include "../MCAL_STM32F103C6/GPIO_Driver/GPIO.h"

typedef enum
{
	BUTTON_0,
	BUTTON_1,
	BUTTON_2,
}BUTTON_t;




typedef struct
{
	uint16_t PinNum;  /* values in @ref GPIO_PIN_DEFINE*/
	GPIOx_t* GPIOx;
	uint8_t PinMode;  /* GPIO_MODE_INPUT_FLOAT , GPIO_MODE_INPUT_PU or GPIO_MODE_INPUT_PD*/
	STATE_t ActiveState;


}BUTTONConfig_t;

extern BUTTONConfig_t ButtonConfigs[];
extern uint8_t ButtonConfigCount ;


#endif /* BUTTON_BUTTON_CFG_H_ */
