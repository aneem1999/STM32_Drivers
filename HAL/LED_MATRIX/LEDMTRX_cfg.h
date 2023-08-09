/*
 * LEDMTRX_cfg.h
 *
 *  Created on: Jul 30, 2023
 *      Author: Ahmed Naeem
 */

#ifndef LED_MATRIX_LEDMTRX_CFG_H_
#define LED_MATRIX_LEDMTRX_CFG_H_

#include "../../MCAL_STM32F103C6/DIO/DIO_int.h"

#define LEDMTRX_NUM_OF_ROWS 			8
#define LEDMTRX_NUM_OF_COLS 			8

typedef struct
{
	DIO_Pin_Num_t	LEDMTRX_RowPin[LEDMTRX_NUM_OF_ROWS];
	GPIOx_t	*		LEDMTRX_RowPort;
	DIO_Pin_Num_t	LEDMTRX_ColPin[LEDMTRX_NUM_OF_COLS];
	GPIOx_t	*		LEDMTRX_ColPort;
}LEDMTRX_cfg_t;

extern LEDMTRX_cfg_t LEDMTX_ConfigurationArr ;

/* ==========================================================
 * 			Pins Mapping
 * ==========================================================
 */

/* Pins values from 0 - 15 */
#define LEDMTRX_ROW0_PIN     0
#define LEDMTRX_ROW1_PIN     1
#define LEDMTRX_ROW2_PIN     2
#define LEDMTRX_ROW3_PIN     3
#define LEDMTRX_ROW4_PIN     4
#define LEDMTRX_ROW5_PIN     5
#define LEDMTRX_ROW6_PIN     6
#define LEDMTRX_ROW7_PIN     7

#define LEDMTRX_ROW_MASK     0x000ff
#define LEDMTRX_ROW_PORT     GPIOA  /* GPIOA , GPIOB, GPIOC .. */

/* Pins values from 0 - 15 */
#define LEDMTRX_COL0_PIN     7
#define LEDMTRX_COL1_PIN     8
#define LEDMTRX_COL2_PIN     9
#define LEDMTRX_COL3_PIN     10
#define LEDMTRX_COL4_PIN     11
#define LEDMTRX_COL5_PIN     12
#define LEDMTRX_COL6_PIN     13
#define LEDMTRX_COL7_PIN     14

#define LEDMTRX_COL_MASK     0xff00
#define LEDMTRX_COL_PORT     GPIOA  /* GPIOA , GPIOB, GPIOC .. */



/* ==========================================================
 * 		  Assume That Led Matrix is Column Control
 * ==========================================================
 */

#endif /* LED_MATRIX_LEDMTRX_CFG_H_ */
