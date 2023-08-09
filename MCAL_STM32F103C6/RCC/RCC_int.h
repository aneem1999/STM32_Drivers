/********************************************************************************/
/*      Author      : Ahmed Naeem                                               */
/*      Date        : 27 APRIL 2023                                             */
/*      Module      : RCC                                                       */
/*      File        : RCC_int.h                                                 */
/*      Description : RCC interface file                                        */
/*      Version     :  V0.1                                                     */
/********************************************************************************/

#ifndef RCC_INT_H
#define RCC_INT_H

#include <stdint.h>

/**********************************************************************************
 *   RCC typedefs
 */

typedef enum
{
    AHB_BUS = 0,
    APB1_BUS,
    APB2_BUS
} BusId_t;


/*********************************************************************************
 *   APIs Prototype
 **********************************************************************************/

/**
 * @brief Init System Clock
 * 
 */
void RCC_voidInitSysClock(void);

/**
 * @brief   Enable Prepheral 
 *
 * @param Copy_enuBusId    Bus ID @ref BusId_t enum
 * @param Copy_u8PrephId   Bit Num at RCC_APB2ENR/RCC_APB1ENR/RCC_AHBENR Register
 */
void RCC_voidEnableClock(BusId_t Copy_enuBusId, uint8_t Copy_u8PrephId);

/**
 * @brief   Disable Prepheral clock
 *
 * @param Copy_enuBusId     Bus ID @ref BusId_t enum
 * @param Copy_u8PrephId    Bit Num at RCC_APB2ENR/RCC_APB1ENR/RCC_AHBENR Register
 */
void RCC_voidDisableClock(BusId_t Copy_enuBusId, uint8_t Copy_u8PrephId);




/**
 * @brief GET system clock frequency
 *
 * @return u32
 */
uint32_t RCC_u32GetSYSCLK_Freq(void);

/**
 * @brief GET AHB Bus clock frequency
 *
 * @return uint32_t
 */
uint32_t RCC_u32GetHCLK_Freq(void);

/**
 * @brief GET APB1 Bus clock frequency
 *
 * @return uint32_t
 */
uint32_t RCC_u32GetAPB1CLK_Freq(void);

/**
 * @brief GET APB2 Bus clock frequency
 *
 * @return uint32_t
 */
uint32_t RCC_u32GetAPB2CLK_Freq(void);


#endif
