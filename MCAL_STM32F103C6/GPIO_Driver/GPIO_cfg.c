/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   GPIO_cfg.c
 *************************************************************/
/*************************************************************/
// Includes
#include "stm32f103x6.h"
#include "GPIO.h"



/*************************************************************/
/*Configure pins here*/
GPIO_Pinconfig_t PINs_Config[] ={

		{GPIO_PIN0, GPIOA, GPIO_MODE_OUTPUT_PP,GPIO_SPEED_10M},
		{GPIO_PIN1, GPIOA, GPIO_MODE_OUTPUT_PP,GPIO_SPEED_10M},
		{GPIO_PIN2, GPIOA, GPIO_MODE_OUTPUT_PP,GPIO_SPEED_10M},
		{GPIO_PIN3, GPIOA, GPIO_MODE_OUTPUT_PP,GPIO_SPEED_10M},
		{GPIO_PIN4, GPIOA, GPIO_MODE_OUTPUT_PP,GPIO_SPEED_10M},
		{GPIO_PIN5, GPIOA, GPIO_MODE_OUTPUT_PP,GPIO_SPEED_10M},
		{GPIO_PIN6, GPIOA, GPIO_MODE_OUTPUT_PP,GPIO_SPEED_10M},
		{GPIO_PIN7, GPIOA, GPIO_MODE_OUTPUT_PP,GPIO_SPEED_10M},
		{GPIO_PIN8, GPIOA, GPIO_MODE_OUTPUT_PP,GPIO_SPEED_10M},
		{GPIO_PIN9, GPIOA, GPIO_MODE_OUTPUT_PP,GPIO_SPEED_10M},
		{GPIO_PIN10, GPIOA, GPIO_MODE_OUTPUT_PP,GPIO_SPEED_10M},


};

/* Count of used pins */
uint8_t PinCount = sizeof(PINs_Config)/sizeof(PINs_Config[0]);
