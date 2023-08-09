/*
 * button.h
 *
 *  Created on: Jan 1, 2023
 *      Author: ncm
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#include "button_cfg.h"


typedef enum
{
	NOT_PRESSED,
	PRESSED,
}BUTTON_Status_t;

void BUTTON_Init();
BUTTON_Status_t BUTTON_GetStatus( BUTTON_t button);

#endif /* BUTTON_BUTTON_H_ */
