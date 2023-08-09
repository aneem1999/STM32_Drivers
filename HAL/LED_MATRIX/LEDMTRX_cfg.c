/*
 * LEDMTRX_cfg.c
 *
 *  Created on: Jul 30, 2023
 *      Author: Ahmed Naeem
 */

#include "LEDMTRX_cfg.h"


LEDMTRX_cfg_t LEDMTX_ConfigurationArr = {
	.LEDMTRX_ColPin  =	{DIO_PIN_0 , DIO_PIN_1, DIO_PIN_2 , DIO_PIN_3 ,DIO_PIN_4 , DIO_PIN_5 , DIO_PIN_6, DIO_PIN_7},
	.LEDMTRX_ColPort =	GPIOA,
	.LEDMTRX_RowPin  =	{ DIO_PIN_8, DIO_PIN_9 , DIO_PIN_10 ,DIO_PIN_11 , DIO_PIN_12 , DIO_PIN_13, DIO_PIN_14 , DIO_PIN_15},
	.LEDMTRX_RowPort =	GPIOA
};


