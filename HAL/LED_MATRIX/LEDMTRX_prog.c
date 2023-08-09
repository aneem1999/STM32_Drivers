/*
 * LEDMTRX_prog.c
 *
 *  Created on: Jul 30, 2023
 *      Author: Ahmed Naeem
 */
#include "../../LIB/bitmath.h"

#include "../../MCAL_STM32F103C6/DIO/DIO_int.h"
#include "../../MCAL_STM32F103C6/SYSTICK/SYSTICK_interface.h"


#include "LEDMTRX_int.h"


#include "LEDMTRX_cfg.h"


void LEDMTRX_vInit()
{
	/* init all cols and row pins as output  push pull with speed 10M */
	uint8_t localPinCount = 0;
	for(localPinCount = 0 ; localPinCount < LEDMTRX_NUM_OF_ROWS; localPinCount++)
	{
		DIO_vInitPin(LEDMTX_ConfigurationArr.LEDMTRX_RowPort,
				LEDMTX_ConfigurationArr.LEDMTRX_RowPin[localPinCount],
				GPIO_MODE_OUTPUT_PP , GPIO_SPEED_10M);
	}

	for(localPinCount = 0 ; localPinCount < LEDMTRX_NUM_OF_COLS; localPinCount++)
	{
		DIO_vInitPin(LEDMTX_ConfigurationArr.LEDMTRX_ColPort,
				LEDMTX_ConfigurationArr.LEDMTRX_ColPin[localPinCount],
				GPIO_MODE_OUTPUT_PP , GPIO_SPEED_10M);
	}

	uint8_t localColCount = 0;
	/* disable all columns */
	for(localColCount = 0 ; localColCount < LEDMTRX_NUM_OF_COLS; localColCount++)
	{
		DIO_vWritePin(LEDMTX_ConfigurationArr.LEDMTRX_ColPort,
				LEDMTX_ConfigurationArr.LEDMTRX_ColPin[localColCount], STD_HIGH);
	}

}

static void LEDMTRX_vWriteRow(uint8_t cpy_u8RowVal)
{
	uint8_t localRowCount = 0;

	/* disable all columns */
	for(localRowCount = 0 ; localRowCount < LEDMTRX_NUM_OF_ROWS; localRowCount++)
	{
		DIO_vWritePin(LEDMTX_ConfigurationArr.LEDMTRX_RowPort,
				LEDMTX_ConfigurationArr.LEDMTRX_RowPin[localRowCount], GET_BIT(cpy_u8RowVal ,localRowCount));
	}

}

void LEDMTRX_vDisplay(uint8_t cpy_arrFrame[LEDMTRX_NUM_OF_COLS] )
{

	uint8_t localColCount = 0;

	for(localColCount = 0 ; localColCount < LEDMTRX_NUM_OF_COLS; localColCount++)
	{
		/* enable each col  and put rows values */
		DIO_vWritePin(LEDMTX_ConfigurationArr.LEDMTRX_ColPort,
				LEDMTX_ConfigurationArr.LEDMTRX_ColPin[localColCount], STD_LOW);

		/* Put Row value */
		LEDMTRX_vWriteRow(cpy_arrFrame[localColCount]);

		/* delay 2.5 mili second*/
		MSYSTICK_vSetBusyWait(3000);

		DIO_vWritePin(LEDMTX_ConfigurationArr.LEDMTRX_ColPort,
				LEDMTX_ConfigurationArr.LEDMTRX_ColPin[localColCount], STD_HIGH);

	}

}






