/*
 * DIO_private.h
 *
 *  Created on: Jul 25, 2023
 *      Author: Ahmed Naeem
 */

#ifndef DIO_DIO_PRIVATE_H_
#define DIO_DIO_PRIVATE_H_



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



/*GPIO PORTS*/
/* Ports A,B Partially included in LQFP48 */
#define GPIOA_BASE 0x40010800UL
#define GPIOB_BASE 0x40010C00UL
/* Ports C,D Partially includedU in LQFP48 */
#define GPIOC_BASE 0x40011000UL
#define GPIOD_BASE 0x40011400UL
/* Ports E,F,G are not includedU in LQFP48 */
#define GPIOE_BASE 0x40011800UL
#define GPIOF_BASE 0x40011C00UL
#define GPIOG_BASE 0x40012000UL


typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;

} GPIOx_t;



#define GPIOA ((GPIOx_t *)GPIOA_BASE)
#define GPIOB ((GPIOx_t *)GPIOB_BASE)
#define GPIOC ((GPIOx_t *)GPIOC_BASE)
#define GPIOD ((GPIOx_t *)GPIOD_BASE)



#endif /* DIO_DIO_PRIVATE_H_ */
