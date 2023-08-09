/*
 * NVIC_prog.c
 *
 *  Created on: Jul 10, 2023
 *      Author: Ahmed Naeem
 */



/****************************************************
 *  	Includes
 ****************************************************/

#include "../../LIB/bitmath.h"


#include "NVIC_private.h"
#include "NVIC_cfg.h"
#include "NVIC_interface.h"

void MNVIC_vInit()
{
#define		 SCB_AIRCR		*((volatile uint32_t*)0xE000ED90 + 0x0C)

	SCB_AIRCR = MNVIC_GROUP_SUB_DISTRIBUTION;

}
void MNVIC_vEnableInterrupt(uint8_t cpy_u8InterruptNum)
{

	if(cpy_u8InterruptNum <= 31)
	{
		NVIC_ISER0 = 1 << cpy_u8InterruptNum;
		//	SET_BIT(NVIC_ISER0,cpy_u8InterruptNum);
	}
	else if(cpy_u8InterruptNum <= 59)
	{
		cpy_u8InterruptNum -=32;

		// Writing 0 has No effect
		NVIC_ISER1 = 1 << cpy_u8InterruptNum;
		//SET_BIT(NVIC_ISER1,cpy_u8InterruptNum);
	}
	else
	{
		// Do nothing
	}

}



void MNVIC_vDisableInterrupt(uint8_t cpy_u8InterruptNum)
{

	if(cpy_u8InterruptNum <= 31)
	{
		NVIC_ICER0 = 1 << cpy_u8InterruptNum;
		//	SET_BIT(->NVIC_ISER0,cpy_u8InterruptNum);
	}
	else if(cpy_u8InterruptNum <= 59)
	{
		cpy_u8InterruptNum -=32;

		// Writing 0 has No effect
		NVIC_ICER1 = 1 << cpy_u8InterruptNum;
	}
	else
	{
		// Do nothing
	}

}



void MNVIC_vSetPendingFlag(uint8_t cpy_u8InterruptNum)
{

	if(cpy_u8InterruptNum <= 31)
	{
		NVIC_ISPR0 = 1 << cpy_u8InterruptNum;
		//	SET_BIT(->NVIC_ISER0,cpy_u8InterruptNum);
	}
	else if(cpy_u8InterruptNum <= 59)
	{
		cpy_u8InterruptNum -=32;

		// Writing 0 has No effect
		NVIC_ISPR1 = 1 << cpy_u8InterruptNum;
	}
	else
	{
		// Do nothing
	}

}


void MNVIC_vClearPendingFlag(uint8_t cpy_u8InterruptNum)
{

	if(cpy_u8InterruptNum <= 31)
	{
		NVIC_ICPR0 = 1 << cpy_u8InterruptNum;
		//	SET_BIT(->NVIC_ISER0,cpy_u8InterruptNum);
	}
	else if(cpy_u8InterruptNum <= 59)
	{
		cpy_u8InterruptNum -=32;

		// Writing 0 has No effect
		NVIC_ICPR1 = 1 << cpy_u8InterruptNum;
	}
	else
	{
		// Do nothing
	}

}



uint8_t MNVIC_u8GetActiveFlag(uint8_t cpy_u8InterruptNum)
{
	uint8_t localResult ;
	if(cpy_u8InterruptNum <= 31)
	{
		localResult = GET_BIT(NVIC_IABR0 , cpy_u8InterruptNum);
	}
	else if(cpy_u8InterruptNum <= 59)
	{
		cpy_u8InterruptNum -=32;
		localResult = GET_BIT(NVIC_IABR0 , cpy_u8InterruptNum);
	}
	else
	{
		// Do nothing
	}


	return localResult ;

}

void MNVIC_vSetPriority(int8_t cpy_s8InterruptId , uint8_t cpy_u8GroupPriority , uint8_t cpy_u8GSubPriority)
{
	uint32_t shifts = (uint8_t) 0xFA050300 - MNVIC_GROUP_SUB_DISTRIBUTION / 0x100UL;

	uint8_t local_u8Priorty = (cpy_u8GroupPriority << shifts ) | cpy_u8GSubPriority ;

	/* negative  cpy_s8InterruptId for core Peripherals */

	/* Positive  cpy_s8InterruptId for External Peripherals */
	if(cpy_s8InterruptId > 0)
	{
		NVIC_IPR[cpy_s8InterruptId] = local_u8Priorty << 4;
	}

}



