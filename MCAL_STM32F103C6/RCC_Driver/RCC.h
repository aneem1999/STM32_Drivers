
/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   Dec 6, 2022
 *       @file   :   RCC.c
 *************************************************************/

#ifndef RCC_H
#define RCC_H

/************************************************************
 * Includes
 ***********************************************************/

#include "../LIB/stm32f103x6.h"


/************************************************************
 * Input Clocks
 ***********************************************************/
#define HSE_CLK 	 (uint32_t)16000000
#define HSI_RC_CLK   (uint32_t)8000000



/************************************************************
 ----------------------- RCC APIS  -----------------------
 ***********************************************************/
void RCC_voidInit(void);
void RCC_voidEnable(void);

uint32_t MCAL_RCC_Get_SYSCLK_Freq(void);
uint32_t MCAL_RCC_Get_HCLK_Freq(void);
uint32_t MCAL_RCC_Get_APB1CLK_Freq(void);
uint32_t MCAL_RCC_Get_APB2CLK_Freq(void);


#endif /* INCLUDES_RCC_H_ */
