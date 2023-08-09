/*
 * USART.c
 *
 *  Created on: Dec 6, 2022
 *      Author: ncm
 */

#include "UART_cfg.h"
#include "UART.h"
#include "../MCAL_STM32F103C6/RCC_Driver/RCC.h"
#include "../MCAL_STM32F103C6/GPIO_Driver/GPIO.h"
/************* Global array of callback functions *************/

void (*G_Arr_USART_Callback[3])();


/*************************************************************
 *   @param [in]- USARTx specify which module used USART1 , USART2 or USART3
 *   @param [in]- USARTconfgs Configurations defined by user @ref USART_cfg.c
 *   @brief - initialize USART mode, buad rate, frame, enable/disable interrupt
 *   @retval - none
 *   @Note - only Asynchronous mode is covered
 */
void MCAL_UART_Init(USART_t * USARTx ,UART_Config_t * UARTconfigs)
{

	uint16_t pclk , BUAD ;
	/*------ enable USART specified --------*/
	/*enable USARTx clock*/
	if (USARTx == USART1)
	{
		USART1_RCC_CLK_EN();
		pclk = MCAL_RCC_Get_APB2CLK_Freq();
	}
	else if (USARTx == USART2)
	{
		USART2_RCC_CLK_EN();
		pclk = MCAL_RCC_Get_APB1CLK_Freq();

	}
	else if (USARTx == USART3)
	{
		pclk = MCAL_RCC_Get_APB1CLK_Freq();

		USART3_RCC_CLK_EN();
	}

	/* USART_CR1  Bit 13 UE: USART enable  */
	USARTx->CR1 |= (1<<13);


	/* ------configure mode--------*/
	USARTx->CR1 |=( UARTconfigs->Mode );



	/*--------- configure frame ----------*/
	/* payload length M bit  */
	switch(UARTconfigs->DataLength)
	{
	case 8:
		CLR_BIT(USARTx->CR1 , 11);
		break;
	case 9:
		SET_BIT(USARTx->CR1 , 11);
		break;
	}

	/* configure parity */
	USARTx->CR1 |=( UARTconfigs->Parity );
	/*Stop bits  */
	USARTx->CR2 |=( UARTconfigs->Stopbts );

	/*------- Baud rate -------- */
	/*get pclk*/
	BUAD = UARTconfigs->BaudRate;
	USARTx->BRR = USART_BRR(pclk, BUAD);


	/* Enable USART interrupt */

	if(UARTconfigs->USART_IRQ_EN != UART_IRQ_None )
	{
		/* Enable NVIC for USARTx Module */
		if(USARTx == USART1)
		{
			NVIC_IRQ37_USART1_Enable;
			G_Arr_USART_Callback[0]= UARTconfigs->USART_Callback;

		}

		else if(USARTx == USART1)
		{
			NVIC_IRQ38_USART2_Enable;
			G_Arr_USART_Callback[1]= UARTconfigs->USART_Callback;

		}
		else if(USARTx == USART1)
		{
			NVIC_IRQ39_USART3_Enable;
			G_Arr_USART_Callback[2]= UARTconfigs->USART_Callback;

		}

		/* Enable Interrupt source for USART */
		USARTx->CR1 |=( UARTconfigs->USART_IRQ_EN );

	}

}




/*************************************************************
 *   @param [in]- USARTx Deinitialize
 *   @brief      - initialize USART mode, buad rate, frame, enable/disable interrupt
 *   @retval      - none
 *   @Note - only Asynchronous mode is covered
 */
void MCAL_UART_DeInit(USART_t * USARTx )
{


	if(USARTx == USART1)
	{
		USART1_RCC_CLK_Reset();
		/* Disable NVIC for USARTx Module */
		NVIC_IRQ37_USART1_Disable;

	}

	else if(USARTx == USART1)
	{
		USART2_RCC_CLK_Reset();
		NVIC_IRQ38_USART2_Disable;

	}
	else if(USARTx == USART1)
	{
		USART3_RCC_CLK_Reset();
		NVIC_IRQ39_USART3_Disable;

	}


}




/*************************************************************
 *   @param [in]- USARTx specify which module used USART1 , USART2 or USART3
 *   @param [in]- USARTconfgs Configurations defined by user @ref USART_cfg.c
 *   @param [in]- pollingEn --> enable polling machansim or not
 *   @param [in]- Tdata --> Data to be transmit
 *   @brief     - Transmit data via UART
 *   @retval    - none
 *   @Note - only Asynchronous mode is covered
 */
void MCAL_UART_Transmit(USART_t * USARTx ,UART_Config_t * UARTconfigs,PollingMachansim_t pollingEn , uint16_t *Tdata )
{
	/* Check polling */
	if(pollingEn == Polling_Enable)
		while(!(USARTx->SR &(1<<7)));
	if(UARTconfigs->DataLength == 9)
	{
		USARTx->DR |= (uint16_t)(*Tdata & 0x01ff);
	}
	else if(UARTconfigs->DataLength == 8)
	{
		USARTx->DR |= (uint8_t)(*Tdata & 0xff);
	}
}


/*************************************************************
 *   @param [in]- USARTx specify which module used USART1 , USART2 or USART3
 *   @param [in]- USARTconfgs Configurations defined by user @ref USART_cfg.c
 *   @param [in]- pollingEn --> enable polling machanism or not
 *   @brief     - receive data via UART
 *   @retval    - uint16_t received data (8 or 9 data)
 *   @Note - only Asynchronous mode is covered
 */
uint16_t MCAL_UART_Receive(USART_t * USARTx ,UART_Config_t * UARTconfigs,PollingMachansim_t pollingEn )
{
	uint16_t Sdata;
	/* Check polling */
	if(pollingEn == Polling_Enable)
		while(!(USARTx->SR &(1<<7)));


	if(UARTconfigs->DataLength == 9)
	{
		if(UARTconfigs->Parity == UART_PARTY_Disable )
			Sdata = (USARTx->DR & 0x01ff);
		else
			Sdata = (USARTx->DR & (uint8_t)0xff);

	}
	else if(UARTconfigs->DataLength == 8)
	{
		if(UARTconfigs->Parity == UART_PARTY_Disable )
			Sdata =(USARTx->DR & (uint8_t)0xff);
		else
			Sdata =(USARTx->DR &  (uint8_t)0x7f);
	}

	return Sdata;
}




/**================================================================
 * @Fn				-MCAL_UART_GPIO_Set_Pins
 * @brief 			- intialize GPIO Pins
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Should enable the corresponding ALT  & GPIO  in RCC clock Also called after MCAL_UART_Init()
 */
void MCAL_UART_GPIO_Set_Pins(USART_t *USARTx , UART_Config_t * UARTconfigs)
{
	GPIO_Pinconfig_t PinCfg;

	if (USARTx == USART1)
	{
		// PA9 TX
		// PA10 RX
		// PA11 CTS
		// PA12 RTS

		// PA9 TX
		PinCfg.PinNum =GPIO_PIN9 ;
		PinCfg.GPIOx = GPIOA ;
		PinCfg.PinMode = GPIO_MODE_AF_PP ;
		PinCfg.PinSpeed= GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		// PA10 RX
		PinCfg.PinNum = GPIO_PIN10;
		PinCfg.PinMode = GPIO_MODE_INPUT_FLOAT;
		PinCfg.PinSpeed= GPIO_INPUT_MOD;
		MCAL_GPIO_Init(GPIOA, &PinCfg);
		//
		//		if (UARTconfigs->flowcontrol == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		//		{
		//			// PA11 CTS
		//			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		//			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		//			MCAL_GPIO_Init(GPIOA, &PinCfg);
		//		}
		//
		//		if (Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		//		{
		//			// PA12 RTS
		//			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
		//			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		//			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		//			MCAL_GPIO_Init(GPIOA, &PinCfg);
		//		}
	}
	else if (USARTx == USART2)
	{
		// PA2 TX
		// PA3 RX
		// PA0 CTS
		// PA1 RTS

		// PA2 TX
		PinCfg.PinNum =GPIO_PIN2 ;
		PinCfg.GPIOx = GPIOA ;
		PinCfg.PinMode = GPIO_MODE_AF_PP ;
		PinCfg.PinSpeed= GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		// PA3 RX
		PinCfg.PinNum = GPIO_PIN3;
		PinCfg.PinMode = GPIO_MODE_INPUT_FLOAT;
		PinCfg.PinSpeed= GPIO_INPUT_MOD;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//

		//		if (Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		//		{
		//			// PA0 CTS
		//			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
		//			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		//			MCAL_GPIO_Init(GPIOA, &PinCfg);
		//		}
		//
		//		if (Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		//		{
		//			// PA1 RTS
		//			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
		//			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		//			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		//			MCAL_GPIO_Init(GPIOA, &PinCfg);
		//		}
	}
	else if (USARTx == USART3)
	{
		// PB10 TX
		// PB11 RX
		// PB13 CTS
		// PA14 RTS

		// PB10 TX
		PinCfg.PinNum =GPIO_PIN10 ;
		PinCfg.GPIOx = GPIOA ;
		PinCfg.PinMode = GPIO_MODE_AF_PP ;
		PinCfg.PinSpeed= GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		// PA11 RX
		PinCfg.PinNum = GPIO_PIN11;
		PinCfg.PinMode = GPIO_MODE_INPUT_FLOAT;
		PinCfg.PinSpeed= GPIO_INPUT_MOD;

		MCAL_GPIO_Init(GPIOA, &PinCfg);
		//

//		if (Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
//		{
//			// PB13 CTS
//			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
//			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
//			MCAL_GPIO_Init(GPIOB, &PinCfg);
//		}
//		if (Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
//		{
//			// PA14 RTS
//			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
//			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
//			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
//			MCAL_GPIO_Init(GPIOB, &PinCfg);
//		}
	}
}

// ISR
void USART1_IRQHandler(void)
{

	G_Arr_USART_Callback[0]();

}

void USART2_IRQHandler(void)
{
	G_Arr_USART_Callback[1]();
}
void USART3_IRQHandler(void)
{
	G_Arr_USART_Callback[2]();
}





