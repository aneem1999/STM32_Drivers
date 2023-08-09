/********************************************************************************/
/*      Author      : Ahmed Naeem                                               */
/*      Date        : 28 APRIL 2023                                             */
/*      Module      : RCC                                                       */
/*      File        : RCC_prg.c                                                 */
/*      Description : RCC program file                                          */
/*      Version     :  V0.1                                                     */
/********************************************************************************/

/********************************************************************************
 *  Includes
 */

#include "../../LIB/bitmath.h"

#include "RCC_int.h"
#include "RCC_cfg.h"
#include "RCC_private.h"

/*********************************************************************************
 *   Functions
 **********************************************************************************/

/**
 * @brief Init System Clock
 *
 */
void RCC_voidInitSysClock(void)
{
    uint8_t u8CloclSourceVal = CLOCK_SRC_SELECT;

#if CLOCK_SRC_SELECT == PLL_CLOCK
    /* Set MUL value */
    RCC->CFGR &= ~(0xf << 18);
    RCC->CFGR |= ((PLL_MUL_FACTOR - 2) << 18) & (0xf << 18);

#if PLL_ENTERY_CLOCK_SRC == 1
    /* Set HSE divider*/
    RCC->CFGR &= ~(1 << 17);
    RCC->CFGR |= (PLL_HSE_DIVIDER << 17) & (1 << 17);

#endif

    /*PLL ENTERY CLOCK SCR*/
    RCC->CFGR &= ~(1 << 16);
    RCC->CFGR |= (PLL_ENTERY_CLOCK_SRC << 16) & (1 << 16);

#elif CLOCK_SRC_SELECT == HSE_CRYSTAL_CLOCK
    SET_BIT(RCC->CR, 16); /* Enable HSE with No Bypass*/

#elif CLOCK_SRC_SELECT == HSE_RC_CLOCK
    SET_BIT(RCC->CR, 18); /* Enable HSE with  Bypass*/
    uint8_tCloclSourceVal = 1;

#elif CLOCK_SRC_SELECT == HSI_CLOCK
    SET_BIT(RCC->CR, 0);

#else
#error("Wrong Clock Source Selection")

#endif

    /* define the clock source HSI, HSE , PLL */
    RCC->CFGR |= (u8CloclSourceVal & 3);

    /* Define Busses Clock  */

    /* AHB clock */
    RCC->CFGR &= ~(0x0f << 4);
    RCC->CFGR |= ((AHB_CLK_PRESCALER & 0x0f) << 4);

    /* APB1 clock */
    RCC->CFGR &= ~(0x07 << 8);
    RCC->CFGR |= ((APB1_CLK_PRESCALER & 0x07) << 8);

    /* APB2 clock */
    RCC->CFGR &= ~(0x07 << 11);
    RCC->CFGR |= ((APB1_CLK_PRESCALER & 0x07) << 11);
}

/**
 * @brief                  Enable Prepheral Clock
 *
 * @param Copy_enuBusId    Bus ID @ref BusId_t enum
 * @param Copy_u8PrephId   Bit Num at RCC_APB2ENR/RCC_APB1ENR/RCC_AHBENR Register
 */
void RCC_voidEnableClock(BusId_t Copy_enuBusId, uint8_t Copy_u8PrephId)
{

    if (Copy_u8PrephId < 32)
    {
        switch (Copy_u8PrephId)
        {
        case AHB_BUS:
            SET_BIT(RCC->AHBENR, Copy_u8PrephId);
            break;
        case APB1_BUS:
            SET_BIT(RCC->APB1ENR, Copy_u8PrephId);
            break;
        case APB2_BUS:
            SET_BIT(RCC->APB2ENR, Copy_u8PrephId);
            break;
        }
    }
}

/**
 * @brief   Disable Prepheral clock
 *
 * @param Copy_enuBusId     Bus ID @ref BusId_t enum
 * @param Copy_u8PrephId    Bit Num at RCC_APB2ENR/RCC_APB1ENR/RCC_AHBENR Register
 */
void RCC_voidDisableClock(BusId_t Copy_enuBusId, uint8_t Copy_u8PrephId)
{
    if (Copy_u8PrephId < 32)
    {
        switch (Copy_u8PrephId)
        {
        case AHB_BUS:
           CLR_BIT(RCC->AHBENR, Copy_u8PrephId);
            break;
        case APB1_BUS:
           CLR_BIT(RCC->APB1ENR, Copy_u8PrephId);
            break;
        case APB2_BUS:
           CLR_BIT(RCC->APB2ENR, Copy_u8PrephId);
            break;
        }
    }
}

/* Helper arrayes*/
const uint32_t HCLK_PrescalerTable[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint32_t APBCLK_PrescalerTable[] = {0, 0, 0, 0, 1, 2, 3, 4};

/**
 * @brief GET system clock frequency
 *
 * @return uint32_t
 */
uint32_t RCC_u32GetSYSCLK_Freq(void)
{
    /*	Bits 3:2 SWS[1:0]: System clock switch status */

    switch ((RCC->CFGR >> 2) & (0b11))
    {
    case 0:
        /* 00: HSI oscillator used as system clock */
        return HSI_CLK_FREQ;
        break;
    case 1:
        //	01: HSE oscillator used as system clock
        return HSE_CLK_FREQ;
        break;
    case 2:
        //	10: PLL used as system clock
        return 16000000;
        break;
    }

    return 0;
}

/**
 * @brief GET AHB Bus clock frequency
 *
 * @return uint32_t
 */
uint32_t RCC_u32GetHCLK_Freq(void)
{
    /*
     Bits 7:4 HPRE[3:0]: AHB prescaler
    Set and cleared by software to control AHB clock division factor.
    0xxx: SYSCLK not divided
    1000: SYSCLK divided by 2
    1001: SYSCLK divided by 4
    1010: SYSCLK divided by 8
    1011: SYSCLK divided by 16
    1100: SYSCLK divided by 64
    1101: SYSCLK divided by 128
    1110: SYSCLK divided by 256
    1111: SYSCLK divided by 512
     */
    return (RCC_u32GetSYSCLK_Freq() >> (HCLK_PrescalerTable[(RCC->CFGR >> 4) & 0xf]));
}

/**
 * @brief GET APB1 Bus clock frequency
 *
 * @return uint32_t
 */
uint32_t RCC_u32GetAPB1CLK_Freq(void)
{
    /*PPRE1[2:0]: APB Low-speed prescaler (APB1)
    Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
    0xx: HCLK not divided
    100: HCLK divided by 2
    101: HCLK divided by 4
    110: HCLK divided by 8
    111: HCLK divided by 16
     */
    return (RCC_u32GetHCLK_Freq() >> APBCLK_PrescalerTable[(RCC->CFGR >> 8) & 0b111]);
}

/**
 * @brief GET APB2 Bus clock frequency
 *
 * @return uint32_t
 */
uint32_t RCC_u32GetAPB2CLK_Freq(void)
{
    /*Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
        Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
        0xx: HCLK not divided
        100: HCLK divided by 2
        101: HCLK divided by 4
        110: HCLK divided by 8
        111: HCLK divided by 16
     */
    return RCC_u32GetHCLK_Freq() >> (APBCLK_PrescalerTable[(RCC->CFGR >> 11) & 0b111]);
}
