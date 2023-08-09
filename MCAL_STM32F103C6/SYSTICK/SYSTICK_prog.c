/*
 * SYSTICK_prog.c
 *
 *  Created on: Jul 12, 2023
 *      Author: ncm
 */

#include "../../LIB/bitmath.h"

#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"
#include "SYSTICK_cfg.h"

void (*SysTick_CallBack)();


void MSYSTICK_vInit()
{
#if  SYSTICK_CLOCK	 ==	SYSTICK_AHB_CLOCK_DIVIDED_8
	CLR_BIT(STK->CTRL , 2);

#elif SYSTICK_CLOCK  ==	SYSTICK_AHB_CLOCK
	SET_BIT(STK->CTRL , 2);

#endif

}

void MSYSTICK_vStart()
{
	SET_BIT(STK->CTRL , 0);
}

void MSYSTICK_vStop()
{
	CLR_BIT(STK->CTRL , 0);
}


uint32_t MSYSTICK_u32GetElapsedTime()
{
	return (0x010000 - STK->VAL);
}
uint32_t MSYSTICK_u32ReminingTime()
{
	return STK->VAL;
}


void MSYSTICK_vSetBusyWait(uint32_t cpy_u32Ticks)
{
	STK->LOAD = cpy_u32Ticks ;

	/* Start timer */
	SET_BIT(STK->CTRL , 0);

	STK->LOAD = 0 ;


	while(!GET_BIT(STK->CTRL , 16));

}

void MSYSTICK_vSetIntervalSingle(uint32_t cpy_u32Ticks , void (* cpy_CB)(void))
{
	/* Enable Interrupt */
	SET_BIT(STK->CTRL , 1);

	SysTick_CallBack = cpy_CB;

	STK->LOAD = cpy_u32Ticks ;

	/* start timer */
	SET_BIT(STK->CTRL , 0);

	/* to make a single shoot */
	STK->LOAD = 0 ;

}

void MSYSTICK_vSetIntervalPeriodic(uint32_t cpy_u32Ticks , void (* cpy_CB)(void))
{
	/* Enable Interrupt */
		SET_BIT(STK->CTRL , 1);

		SysTick_CallBack = cpy_CB;

		STK->LOAD = cpy_u32Ticks - 1 ;

		/* start timer */
		SET_BIT(STK->CTRL , 0);
}


void MSYSTICK_vEnableInterrupt()
{
	SET_BIT(STK->CTRL , 1);
}


void MSYSTICK_vDisableInterrupt()
{
	CLR_BIT(STK->CTRL , 1);
}

void MSYSTICK_vSetCallBaclFun(void (*cpy_CallBack)())
{
	SysTick_CallBack =cpy_CallBack ;
}

void MSYSTICK_vSetLoadValue(uint32_t cpy_u32Load)
{
	STK->LOAD = cpy_u32Load ;
}

/* SysTick ISR*/

void SysTick_Handler(void)
{
	SysTick_CallBack();
}


