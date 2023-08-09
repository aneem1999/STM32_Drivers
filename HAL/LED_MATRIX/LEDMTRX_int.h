/*
 * LEDMTRX_int.h
 *
 *  Created on: Jul 30, 2023
 *      Author: Ahmed Naeem
 */

#ifndef LED_MATRIX_LEDMTRX_INT_H_
#define LED_MATRIX_LEDMTRX_INT_H_

#include "stdint.h"
#include "LEDMTRX_cfg.h"


void LEDMTRX_vInit();

void LEDMTRX_vDisplay(uint8_t cpy_arrFrame[LEDMTRX_NUM_OF_COLS] );



#endif /* LED_MATRIX_LEDMTRX_INT_H_ */
