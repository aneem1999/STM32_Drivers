/*
 * DIO_cfg.c
 *
 *  Created on: Jul 25, 2023
 *      Author: Ahmed Naeem
 */


/*************************************************************/

/* PinMode			@ref GPIO_PIN_MODE*/

				/*  Input mode : MODEy[1:0] = 00 */
/* GPIO_MODE_INPUT_ANALOG 			(0)-> CNFy[1:0] 00: Analog mode 					*/
/* GPIO_MODE_INPUT_FLOAT			(1)-> CNFy[1:0] 01: Floating input (reset state) 	*/
/* GPIO_MODE_INPUT_PU				(2)-> CNFy[1:0] 10: Input with pull-up / pull-down  */
/* GPIO_MODE_INPUT_PD				(3)-> CNFy[1:0] 10: Input with pull-up / pull-down  */
				/*  Output mode : MODEy[1:0] > 00 */
/* GPIO_MODE_OUTPUT_PP				(4)-> CNFy[1:0] 00: General purpose output push-pull*/
/* GPIO_MODE_OUTPUT_OD				(5)-> CNFy[1:0] 01: General purpose output Open-drain*/
/* GPIO_MODE_AF_PP					(6)-> CNFy[1:0] 10: Alternate function output Push-pull*/
/* GPIO_MODE_AF_OD					(7)-> CNFy[1:0] 11: Alternate function output Open-drain*/

/*************************************************************/


/*************************************************************/
/* PinSpeed				 @ref GPIO_PIN_SPEED*/

/* GPIO_INPUT_MOD			(0) -> MODEy[1:0] 00: Input mode (reset state)*/
/* GPIO_SPEED_10M			(1) -> MODEy[1:0] 01: Output mode, max speed 10 MHz*/
/* GPIO_SPEED_2M 			(2) -> MODEy[1:0] 10: Output mode, max speed 2 MHz*/
/* GPIO_SPEED_50M			(3) -> MODEy[1:0] 11: Output mode, max speed 50 MHz*/


#include "DIO_cfg.h"
 DIO_PinConfig_t DIO_Config[] = {

		 {.PinNum = DIO_PIN_13 , .GPIOx = GPIOA , .PinMode = GPIO_MODE_OUTPUT_PP , .PinSpeed =GPIO_SPEED_2M }
 };



 uint8_t DIOCount = sizeof(DIO_Config) / sizeof(DIO_PinConfig_t) ;
