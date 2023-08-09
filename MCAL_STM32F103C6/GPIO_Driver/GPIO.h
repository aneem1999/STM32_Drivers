/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   GPIO.h
 *************************************************************/
#ifndef GPIO_H
#define GPIO_H

/*************************************************************/
// Includes
#include "../LIB/stm32f103x6.h"

/*************************************************************/
/* Macros Configuration References */
/*************************************************************/

/* @ref GPIO_PIN_DEFINE
 PINs Configurations In STM32 each port has 16 pins 0 -->15 */
#define GPIO_PIN0  ((uint16_t)0x0001)
#define GPIO_PIN1  ((uint16_t)0x0002)
#define GPIO_PIN2  ((uint16_t)0x0004)
#define GPIO_PIN3  ((uint16_t)0x0008)
#define GPIO_PIN4  ((uint16_t)0x0010)
#define GPIO_PIN5  ((uint16_t)0x0020)
#define GPIO_PIN6  ((uint16_t)0x0040)
#define GPIO_PIN7  ((uint16_t)0x0080)
#define GPIO_PIN8  ((uint16_t)0x0100)
#define GPIO_PIN9  ((uint16_t)0x0200)
#define GPIO_PIN10 ((uint16_t)0x0400)
#define GPIO_PIN11 ((uint16_t)0x0800)
#define GPIO_PIN12 ((uint16_t)0x1000)
#define GPIO_PIN13 ((uint16_t)0x2000)
#define GPIO_PIN14 ((uint16_t)0x4000)
#define GPIO_PIN15 ((uint16_t)0x8000)

/*************************************************************/

/* @ref GPIO_PIN_MODE*/

/*  Input mode : MODEy[1:0] = 00 */
/*(0)-> CNFy[1:0] 00: Analog mode*/
#define GPIO_MODE_INPUT_ANALOG 0x00000000U
/*(1)-> CNFy[1:0] 01: Floating input (reset state) */
#define GPIO_MODE_INPUT_FLOAT 0x00000001U
/*(2)-> CNFy[1:0] 10: Input with pull-up / pull-down  */
#define GPIO_MODE_INPUT_PU 0x00000002U
/*(3)-> CNFy[1:0] 10: Input with pull-up / pull-down  */
#define GPIO_MODE_INPUT_PD 0x00000003U

/*  Output mode : MODEy[1:0] > 00 */
/*(4)-> CNFy[1:0] 00: General purpose output push-pull*/
#define GPIO_MODE_OUTPUT_PP 0x00000004U
/*(5)-> CNFy[1:0] 01: General purpose output Open-drain*/
#define GPIO_MODE_OUTPUT_OD 0x00000005U
/*(6)-> CNFy[1:0] 10: Alternate function output Push-pull*/
#define GPIO_MODE_AF_PP 0x00000006U
/*(7)-> CNFy[1:0] 11: Alternate function output Open-drain*/
#define GPIO_MODE_AF_OD 0x00000007U

/*************************************************************/
/* @ref GPIO_PIN_SPEED*/

/*(0) -> MODEy[1:0] 00: Input mode (reset state)*/
#define GPIO_INPUT_MOD 0x00000000U
/*(1) -> MODEy[1:0] 01: Output mode, max speed 10 MHz*/
#define GPIO_SPEED_10M 0x00000001U
/*(2) -> MODEy[1:0] 10: Output mode, max speed 2 MHz*/
#define GPIO_SPEED_2M 0x00000002U
/*(3) -> MODEy[1:0] 11: Output mode, max speed 50 MHz*/
#define GPIO_SPEED_50M 0x00000003U

/*************************************************************/
/* User type definitions (structures) */

typedef enum
{
    LOW,
    HIGH
} STATE_t;

/*************************************************************/
/* pins confugurations */
/*Struct for pins configurations*/
typedef struct
{
    uint16_t PinNum;  /* values in @ref GPIO_PIN_DEFINE*/
    GPIOx_t* GPIOx;    /* GPIO ports*/
    uint8_t PinMode;  /* values in @ref GPIO_PIN_MODE*/
    uint8_t PinSpeed; /* values in @ref GPIO_PIN_SPEED*/
} GPIO_Pinconfig_t;

extern GPIO_Pinconfig_t PINs_Config[];
extern uint8_t PinCount;

/*************************************************************/
/* APIs Supported by "MCAL GPIO DRIVER"*/

void MCAL_GPIO_Init(GPIOx_t *GPIOx, GPIO_Pinconfig_t *PinConfig);
void MCAL_GPIO_GlobalInit();
void MCAL_GPIO_DeInit(GPIOx_t *GPIOx);

STATE_t MCAL_GPIO_ReadPin(GPIOx_t *GPIOx, uint16_t PinNum);
uint16_t MCAL_GPIO_ReadPort(GPIOx_t *GPIOx);

void MCAL_GPIO_WritePin(GPIOx_t *GPIOx, uint16_t PinNum, STATE_t value);
void MCAL_GPIO_WritePort(GPIOx_t *GPIOx, uint16_t value);
void MCAL_GPIO_TogglePin(GPIOx_t *GPIOx, uint16_t PinNum);

uint8_t MCAL_GPIO_LockPin(GPIOx_t *GPIOx, uint16_t PinNum);

#endif
