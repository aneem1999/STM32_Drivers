/*
 * EXTI_prog.c
 *
 *  Created on: Jul 11, 2023
 *      Author: Ahmed Naeem
 */


#include <stdint.h>

#include "../../LIB/bitmath.h"

#include "../NVIC/NVIC_interface.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_cfg.h"


/*************************************************************
	Global callback Array
 *************************************************************/
void (* GP_IRQ_CallBack[16])();

void MEXTI_vInit(uint8_t cpy_u8InterruptNum )
{


}

void MEXTI_vEnable(uint8_t cpy_u8InterruptNum)
{
	/*
		0: Interrupt request from Line x is masked
		1: Interrupt request from Line x is not masked
	*/
	SET_BIT(EXTI->IMR , cpy_u8InterruptNum);

}


void MEXTI_vDisable(uint8_t cpy_u8InterruptNum)
{
	/*
			0: Interrupt request from Line x is masked
			1: Interrupt request from Line x is not masked
		*/
		CLR_BIT(EXTI->IMR , cpy_u8InterruptNum);
}


void MEXTI_vSetTriggerCase(uint8_t cpy_u8InterruptNum , EXTI_TriggerCase_t cpy_enuTriggerCase )
{
	switch(cpy_enuTriggerCase)
	{
	case RisingEdge:
		SET_BIT(EXTI->RTSR, cpy_u8InterruptNum);
		CLR_BIT(EXTI->FTSR, cpy_u8InterruptNum);
		break;

	case FallingEdge:
		SET_BIT(EXTI->FTSR, cpy_u8InterruptNum);
		CLR_BIT(EXTI->RTSR, cpy_u8InterruptNum);
		break;

	case AnyLogicalChange:
		SET_BIT(EXTI->FTSR, cpy_u8InterruptNum);
		SET_BIT(EXTI->RTSR, cpy_u8InterruptNum);
		break;
	}
}


void MEXTI_vSWInterruptTrigger(uint8_t cpy_u8InterruptNum)
{
	SET_BIT(EXTI->SWIER,cpy_u8InterruptNum);
}

void MEXTI_vSetCallBackFun(uint8_t cpy_u8InterruptNum , void(* cpy_ISR)(void))
{
	GP_IRQ_CallBack[cpy_u8InterruptNum] =  cpy_ISR;
}




/*************************************************************
 *  ISR Handler
 *************************************************************/
void EXTI0_IRQHandler(void)
{
	if(GP_IRQ_CallBack[0])
		{
			GP_IRQ_CallBack[0]();
		}
}

void EXTI1_IRQHandler(void)
{
	if(GP_IRQ_CallBack[1])
	{
			GP_IRQ_CallBack[1]();
	}

}

void EXTI2_IRQHandler(void)
{
	if(GP_IRQ_CallBack[2])
		{
			GP_IRQ_CallBack[2]();
		}
}

void EXTI3_IRQHandler(void)
{
	if(GP_IRQ_CallBack[3])
		{
			GP_IRQ_CallBack[3]();
		}
}

void EXTI4_IRQHandler(void)
{
	/* IRQ  Callback*/
	if(GP_IRQ_CallBack[4])
	{
		GP_IRQ_CallBack[4]();
	}
}
void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & (1<<5)) { 	GP_IRQ_CallBack[5](); }
	if(EXTI->PR & (1<<6)) {  	GP_IRQ_CallBack[6](); }
	if(EXTI->PR & (1<<7)) {  	GP_IRQ_CallBack[7](); }
	if(EXTI->PR & (1<<8)) { 	GP_IRQ_CallBack[8](); }
	if(EXTI->PR & (1<<9)) {  	GP_IRQ_CallBack[9](); }

}
void EXTI15_10_IRQHandler(void)
{

	if(EXTI->PR & (1<<11)) {  	GP_IRQ_CallBack[11](); }
	if(EXTI->PR & (1<<12)) {  	GP_IRQ_CallBack[12](); }
	if(EXTI->PR & (1<<13)) {  	GP_IRQ_CallBack[13](); }
	if(EXTI->PR & (1<<14)) {  	GP_IRQ_CallBack[14](); }
	if(EXTI->PR & (1<<15)) {  	GP_IRQ_CallBack[15](); }

}




