/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   stm32f103x6.h
 *************************************************************/

#ifndef SYM32F103X6_H
#define SYM32F103X6_H

/*************************************************************/
// Includes
#include <stdlib.h>
#include <stdint.h>
#include "bitmath.h"

/*************************************************************/
/* Base addresses for Memories */
#define FLASH_BASE 0x80000000UL
#define SYSTEM_BASE 0x1FFFE000UL
#define PERIPHERALS_BASE 0x40000000UL
#define CORTEX_M3_INTERNAL_BASE 0xE0000000UL

/*************************************************************/
/*Base addresses for BUS Peripherals */
/************ AHB BUS ***************/
#define RCC_BASE 0x40021000

/************ APB2 BUS ************/
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

/*AFIO*/
#define AFIO_BASE 0x40010000UL

/*External Interrupt*/
#define EXTI_BASE 0x40010400UL

/* USART */
#define USART1_BASE  0x40013800
#define USART2_BASE  0x40014400
#define USART3_BASE  0x40014800


/*************************************************************/
/*NVIC at Cortex-M3*/
#define NVIC_BASE 0xE000E100UL
#define NVIC_ISER0 *((volatile uint32_t*) (NVIC_BASE +0x0))
#define NVIC_ISER1 *((volatile uint32_t*) (NVIC_BASE +0x4))
#define NVIC_ISER2 *((volatile uint32_t*) (NVIC_BASE +0x8))
#define NVIC_ICER0 *((volatile uint32_t*) (NVIC_BASE +0x80))
#define NVIC_ICER1 *((volatile uint32_t*) (NVIC_BASE +0x84))
#define NVIC_ICER2 *((volatile uint32_t*) (NVIC_BASE +0x88))


/* Peripheral register: */
/*RCC*/
typedef struct
{
	volatile uint32_t CRR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;

} RCC_t;

/* GPIOx */
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

/*AFIO*/
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	uint32_t RESERVED0;
	volatile uint32_t MAPR2;

} AFIO_t;

/*External Interrupt*/
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

} EXTI_t;


/*USART*/
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;

} USART_t;

/*************************************************************/
/* Peripheral Instants */

#define RCC ((RCC_t *)RCC_BASE)

#define GPIOA ((GPIOx_t *)GPIOA_BASE)
#define GPIOB ((GPIOx_t *)GPIOB_BASE)
#define GPIOC ((GPIOx_t *)GPIOC_BASE)
#define GPIOD ((GPIOx_t *)GPIOD_BASE)

#define AFIO ((AFIO_t *)AFIO_BASE)

#define EXTI ((EXTI_t *)EXTI_BASE)

/* USART Instants */

#define USART1 ((USART_t *)USART1_BASE)
#define USART2 ((USART_t *)USART2_BASE)
#define USART3 ((USART_t *)USART3_BASE)


/*************************************************************/
/* clock enable Macros */

/*GPIO & AFIO in APB2 BUS*/
#define GPIOA_RCC_CLK_ENABLE()	 (RCC->APB2ENR |= (1 << 2))
#define GPIOB_RCC_CLK_ENABLE()   (RCC->APB2ENR |= (1 << 3))
#define GPIOC_RCC_CLK_ENABLE()   (RCC->APB2ENR |= (1 << 4))
#define GPIOD_RCC_CLK_ENABLE()   (RCC->APB2ENR |= (1 << 5))
#define AFIO_RCC_CLK_ENABLE()    (RCC->APB2ENR |= (1 << 0))

/* USART Clock Enable */
#define USART1_RCC_CLK_EN()    	 (RCC->APB2ENR |= (1 << 14))
#define USART2_RCC_CLK_EN()   	 (RCC->APB1ENR |= (1 << 17))
#define USART3_RCC_CLK_EN()      (RCC->APB1ENR |= (1 << 18))
/* USART Clock Reset */
#define USART1_RCC_CLK_Reset()   (RCC->APB2RSTR |= (1 << 14))
#define USART2_RCC_CLK_Reset()   (RCC->APB1RSTR |= (1 << 17))
#define USART3_RCC_CLK_Reset()   (RCC->APB1RSTR |= (1 << 18))

/************************************************************
IVT :
 ************************************************************/
/* EXTI */
#define EXTI0_IRQ   6
#define EXTI1_IRQ   7
#define EXTI2_IRQ   8
#define EXTI3_IRQ   9
#define EXTI4_IRQ   10

#define EXTI5_IRQ   23
#define EXTI6_IRQ   23
#define EXTI7_IRQ   23
#define EXTI8_IRQ   23
#define EXTI9_IRQ   23

#define EXTI10_IRQ  40
#define EXTI11_IRQ  40
#define EXTI12_IRQ  40
#define EXTI13_IRQ  40
#define EXTI14_IRQ  40
#define EXTI15_IRQ  40

#define USART1_IRQ  37
#define USART2_IRQ  38
#define USART3_IRQ  39

/*************************************************************/
/* NVIC Enable/Disable Macros */

/* EXTI */
#define EXTI0_IRQ6_Enable		 		(NVIC_ISER0 |= (1<<6))
#define EXTI1_IRQ7_Enable 				(NVIC_ISER0 |= (1<<7))
#define EXTI2_IRQ8_Enable 				(NVIC_ISER0 |= (1<<8))
#define EXTI3_IRQ9_Enable 				(NVIC_ISER0 |= (1<<9))
#define EXTI4_IRQ10_Enable 				(NVIC_ISER0 |= (1<<10))
#define EXTI5_9_IRQ23_Enable 			(NVIC_ISER0 |= (1<<23))
#define EXTI10_15_IRQ40_Enable 			(NVIC_ISER1 |= (1<<8))

#define EXTI0_IRQ6_Disable 				(NVIC_ICER0 |= (1<<6))
#define EXTI1_IRQ7_Disable 				(NVIC_ICER0 |= (1<<7))
#define EXTI2_IRQ8_Disable 				(NVIC_ICER0 |= (1<<8))
#define EXTI3_IRQ9_Disable 				(NVIC_ICER0 |= (1<<9))
#define EXTI4_IRQ10_Disable 			(NVIC_ICER0 |= (1<<10))
#define EXTI5_9_IRQ23_Disable 			(NVIC_ICER0 |= (1<<23))
#define EXTI10_15_IRQ40_Disable 		(NVIC_ICER1 |= (1<<8))


/* USART IRQs */
#define NVIC_IRQ37_USART1_Enable 		(NVIC_ISER1 |= (1<<(USART1_IRQ-32)))
#define NVIC_IRQ38_USART2_Enable 		(NVIC_ISER1 |= (1<<(USART2_IRQ-32)))
#define NVIC_IRQ39_USART3_Enable 		(NVIC_ISER1 |= (1<<(USART3_IRQ-32)))

#define NVIC_IRQ37_USART1_Disable 		(NVIC_ICER1 |= (1<<(USART1_IRQ-32)))
#define NVIC_IRQ38_USART2_Disable 		(NVIC_ICER1 |= (1<<(USART2_IRQ-32)))
#define NVIC_IRQ39_USART3_Disable 		(NVIC_ICER1 |= (1<<(USART3_IRQ-32)))



/*************************************************************/
// Generic Macros:

/*************************************************************/

#endif
