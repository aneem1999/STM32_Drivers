/********************************************************************************/
/*      Author      : Ahmed Naeem                                               */
/*      Date        : 27 March 2023                                             */
/*      Module      : LIB                                                       */
/*      File        : RCC_cfg.h                                                 */
/*      Description : configurations file                                       */
/*      Version     :  V0.1                                                     */
/********************************************************************************/

#ifndef RCC_CFG_H
#define RCC_CFG_H

#include "RCC_private.h"


/* ===============================================================
   --------------------- CLOCK SOURCE SELECT ---------------------
   ===============================================================
    Source                  Value
    HSI                     HSI_CLOCK 
    HSE Crystal             HSE_CRYSTAL_CLOCK
    HSE RC                  HSE_RC_CLOCK
    PLL                     PLL_CLOCK

*/

#define CLOCK_SRC_SELECT            HSI_CLOCK


/* ===============================================================
 * Input Clocks
   ===============================================================*/
#define HSE_CLK_FREQ 	 16000000UL
#define HSI_CLK_FREQ     8000000UL



/* ===============================================================
   ------------------------- PLL Configs -------------------------
   ===============================================================

    PLLMUL: PLL multiplication factor
    Range 2 -> 16

*/

#define PLL_MUL_FACTOR          2


/*
    PLLSRC: PLL entry clock source
    Set and cleared by software to select PLL clock source.
    This bit can be written only whenPLL is disabled.
    0: HSI oscillator clock / 2 selected as PLL input clock
    1: HSE oscillator clock selected as PLL input clock
*/
#define PLL_ENTERY_CLOCK_SRC    0


/*
    PLLXTPRE: HSE divider for PLL entry
    0: HSE clock not divided
    1: HSE clock divided by 2
*/
#define PLL_HSE_DIVIDER          1





/* ===============================================================
   ------------------- AHB Busses Prescalers ---------------------
   ===============================================================


0   : SYSCLK not divided
8   : SYSCLK divided by 2
9   : SYSCLK divided by 4
10  : SYSCLK divided by 8
11  : SYSCLK divided by 16
12  : SYSCLK divided by 64
13  : SYSCLK divided by 128
14  : SYSCLK divided by 256
15  : SYSCLK divided by 512

*/

#define AHB_CLK_PRESCALER         0

/* ===============================================================
   ---------------- APB1, APB2 Busses Prescalers -----------------
   ===============================================================

HCLK ==> AHB Clock

0   : HCLK not divided
4   : HCLK divided by 2
5   : HCLK divided by 4
6   : HCLK divided by 8
7   : HCLK divided by 16
   
*/


#define APB1_CLK_PRESCALER        0
#define APB2_CLK_PRESCALER        0


#endif
