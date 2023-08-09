/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   1/12/2022
 *       @file   :   EXTI.c
 *************************************************************/
#include "EXTI.h"

#include "../LIB/stm32f103x6.h"
#include "../MCAL_STM32F103C6/GPIO_Driver/GPIO.h"

/*************************************************************
Global callback Array
 *************************************************************/
void (* GP_IRQ_CallBack[16])();


/*************************************************************
EXTI Generic functions
 *************************************************************/

/* mapping pin number at  @ref GPIO_PIN_DEFINE to its integer  value */
uint8_t GetLineNum(uint16_t PinNum)
{
	uint8_t num;
	while (PinNum != 0)
	{
		PinNum = PinNum >> 1;
		num++;
	}
	return (num - 1);
}

/* Enable NVIC */
void NVIC_Enable(uint8_t LineNum)
{
	switch (LineNum)
	{
	case 0 :
		EXTI0_IRQ6_Enable	;
		break;
	case 1 :
		EXTI1_IRQ7_Enable	;
		break;
	case 2 :
		EXTI2_IRQ8_Enable	;
		break;
	case 3 :
		EXTI3_IRQ9_Enable;
		break;
	case 4 :
		EXTI4_IRQ10_Enable	;
		break;
			break;
	case 5 :
	case 6 :
	case 7 :
	case 8 :
	case 9:
		EXTI5_9_IRQ23_Enable;
		break;
	case 10 :
	case 11 :
	case 12 :
	case 13:
	case 14:
	case 15:
		EXTI10_15_IRQ40_Enable ;
		break;

	}
}

/* Disable NVIC */
void NVIC_Disable(uint8_t LineNum)
{
	switch (LineNum)
	{
	case 0 :
		EXTI0_IRQ6_Disable;
		break;
	case 1 :
		EXTI1_IRQ7_Disable;
		break;
	case 2 :
		EXTI2_IRQ8_Disable;
		break;
	case 3 :
		EXTI3_IRQ9_Disable	;
		break;
	case 4 :
		EXTI4_IRQ10_Disable;
		break;
			break;
	case 5 :
	case 6 :
	case 7 :
	case 8 :
	case 9:
		EXTI5_9_IRQ23_Disable ;
		break;
	case 10 :
	case 11 :
	case 12 :
	case 13:
	case 14:
	case 15:
		EXTI10_15_IRQ40_Disable ;
		break;

	}
}

/*************************************************************
EXTI APIs
 *************************************************************/

/*************************************************************
 *   @Fun - MCAL_EXTI_Intit
 *   @brief - init EXTI
 *   @param [in] - EXTI_Config (Pin number , port , callback
 *   @retval -none
 *   @Note -
 */
void MCAL_EXTI_Intit(EXTI_Config_t* EXTI_Config)
{

	/* 1- Configure GPIO pin as input float*/
	GPIO_Pinconfig_t EXTIpin ={EXTI_Config->PinNum ,EXTI_Config->GPIO_Port ,GPIO_MODE_INPUT_FLOAT, GPIO_INPUT_MOD};

	MCAL_GPIO_Init(EXTI_Config->GPIO_Port , &EXTIpin );

	/* 2- Configure AFIO to route it for port */

	// get Line number
	uint8_t EXTI_LineNumber = GetLineNum(EXTI_Config->PinNum);

	/* Get AFIO_EXTICRx number 1,2,3,4*/
	uint8_t AFIO_EXTICR_index = EXTI_LineNumber / 4;

	/* Get AFIO_EXTICR bits position */
	uint8_t AFIO_EXTICR_pos = EXTI_LineNumber % 4;

	/* clear 4 bits of AFIO_EXTICR */
	AFIO->EXTICR[AFIO_EXTICR_index] &=~(AFIO_EXTICR_pos<<0xf);

	if(EXTI_Config->GPIO_Port == GPIOA)
	{
		//	0000: PA[x] pin
		AFIO->EXTICR[AFIO_EXTICR_index] |=(AFIO_EXTICR_pos<<0x0);
	}
	else if(EXTI_Config->GPIO_Port == GPIOB)
	{
		//	0001: PB[x] pin
		AFIO->EXTICR[AFIO_EXTICR_index] |=(AFIO_EXTICR_pos<<0x1);
	}
	else if(EXTI_Config->GPIO_Port == GPIOC)
	{
		//	0010: PC[x] pin
		AFIO->EXTICR[AFIO_EXTICR_index] |=(AFIO_EXTICR_pos<<0x2);
	}
	else if(EXTI_Config->GPIO_Port == GPIOD)
	{
		//	0011: PD[x] pin
		AFIO->EXTICR[AFIO_EXTICR_index] |=(AFIO_EXTICR_pos<<0x3);

	}

	/* 3- Configure the Trigger Selection bits of the Interrupt lines (EXTI_RTSR and EXTI_FTSR)*/

	EXTI->RTSR &= ~(EXTI_Config->PinNum);
	EXTI->FTSR &= ~(EXTI_Config->PinNum);

	switch(EXTI_Config->TriggerCase)
	{
	case RisingEdge:
	{
		EXTI->FTSR &= ~(EXTI_Config->PinNum);
		EXTI->RTSR |= EXTI_Config->PinNum;
	}
	break ;
	case FallingEdge :
	{
		EXTI->RTSR &= ~(EXTI_Config->PinNum);
		EXTI->FTSR |= EXTI_Config->PinNum;

	}
	break ;
	case RisingFallingEdge :
	{
		EXTI->RTSR |= EXTI_Config->PinNum;
		EXTI->FTSR |= EXTI_Config->PinNum;
	}
	}

	/* 4- update IRQ Callback */
	EXTI_Config->EXTI_CallBack =GP_IRQ_CallBack[EXTI_LineNumber];

	/* 5- Configure the mask bits of the 20 Interrupt lines (EXTI_IMR) and on NVIC */
	if(EXTI_Config->IRQ_Status == EXTI_Enabled)
	{
		EXTI->IMR |=  EXTI_Config->PinNum ;
		NVIC_Disable(EXTI_LineNumber);
	}
	else if(EXTI_Config->IRQ_Status == EXTI_Disabled)
	{
		EXTI->IMR &= ~(EXTI_Config->PinNum) ;
		NVIC_Disable(EXTI_LineNumber);
	}

}


/*************************************************************
 *   @Fun - MCAL_EXTI_DeInit
 *   @brief - Deinit EXTI  and return EXTI registers to reset state
 *   @Note -
 */
void MCAL_EXTI_DeIntit(void)
{
	/* Reset all EXTI registers */
	EXTI->EMR = 0x00000000 ;
	EXTI->FTSR = 0x00000000;
	EXTI->IMR =0x00000000 ;
	EXTI->PR = 0x00000000;
	EXTI->RTSR =0x00000000;

	/* Clear by 1*/
	EXTI->SWIER = 0xFFFFFFFF;

	/* Disable NVIC IRQs*/
	EXTI0_IRQ6_Disable ;
	EXTI1_IRQ7_Disable ;
	EXTI2_IRQ8_Disable ;
	EXTI3_IRQ9_Disable ;
	EXTI4_IRQ10_Disable ;
	EXTI5_9_IRQ23_Disable ;
	EXTI10_15_IRQ40_Disable ;

}
//
//
///*************************************************************
// *  ISR Handler
// *************************************************************/
//void EXTI0_IRQHandler(void)
//{
//	/* Clear pending bit for IRQ by 1 */
//	EXTI->PR |= (1<<0);
//	/* IRQ  Callback*/
//	GP_IRQ_CallBack[0]();
//}
//
//void EXTI1_IRQHandler(void)
//{
//	/* Clear pending bit for IRQ by 1 */
//	EXTI->PR |= (1<<1);
//	/* IRQ  Callback*/
//	GP_IRQ_CallBack[1]();
//}
//
//void EXTI2_IRQHandler(void)
//{
//	/* Clear pending bit for IRQ by 1 */
//	EXTI->PR |= (1<<2);
//	/* IRQ  Callback*/
//	GP_IRQ_CallBack[3]();
//}
//
//void EXTI3_IRQHandler(void)
//{
//	/* Clear pending bit for IRQ by 1 */
//	EXTI->PR |= (1<<3);
//	/* IRQ  Callback*/
//	GP_IRQ_CallBack[3]();
//}
//
//void EXTI4_IRQHandler(void)
//{
//	/* Clear pending bit for IRQ by 1 */
//	EXTI->PR |= (1<<4);
//	/* IRQ  Callback*/
//	GP_IRQ_CallBack[4]();
//}
//void EXTI9_5_IRQHandler(void)
//{
//	if(EXTI->PR & (1<<5)) { EXTI->PR |= (1<<5) ; 	GP_IRQ_CallBack[5](); }
//	if(EXTI->PR & (1<<6)) { EXTI->PR |= (1<<6); 	GP_IRQ_CallBack[6](); }
//	if(EXTI->PR & (1<<7)) { EXTI->PR |= (1<<7); 	GP_IRQ_CallBack[7](); }
//	if(EXTI->PR & (1<<8)) { EXTI->PR |= (1<<8); 	GP_IRQ_CallBack[8](); }
//	if(EXTI->PR & (1<<9)) { EXTI->PR |= (1<<9); 	GP_IRQ_CallBack[9](); }
//
//}
//void EXTI15_10_IRQHandler(void)
//{
//
//	if(EXTI->PR & (1<<11)) { EXTI->PR |= (1<<11); 	GP_IRQ_CallBack[11](); }
//	if(EXTI->PR & (1<<12)) { EXTI->PR |= (1<<12); 	GP_IRQ_CallBack[12](); }
//	if(EXTI->PR & (1<<13)) { EXTI->PR |= (1<<13); 	GP_IRQ_CallBack[13](); }
//	if(EXTI->PR & (1<<14)) { EXTI->PR |= (1<<14); 	GP_IRQ_CallBack[14](); }
//	if(EXTI->PR & (1<<15)) { EXTI->PR |= (1<<15) ; 	GP_IRQ_CallBack[15](); }
//
//}
