/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   Dec 7, 2022
 *       @file   :   RCC.h
 *************************************************************/

#ifndef UART_H
#define UART_H

#include "UART_cfg.h"

/************************************************************
 ---------------- Baud Rate Calculation  --------------------
 ***********************************************************/
#define USARTDIV(_PCLK, _BUAD) 				(uint16_t)(_PCLK / (_BUAD * 16)) /* equal to mintssa */
#define USARTDIV_MUL100(_PCLK, _BUAD) 		(uint16_t)(25 * _PCLK / (_BUAD * 4))
#define Mintssa_MUL100(_PCLK, _BUAD) 		(uint16_t)(USARTDIV(_PCLK, _BUAD) * 100)
#define USARTDIV_Fraction(_PCLK, _BUAD) 	(uint16_t)(16 * (USARTDIV_MUL100(_PCLK, _BUAD) - Mintssa_MUL100(_PCLK, _BUAD)) / 100)
#define USART_BRR(_PCLK, _BUAD)             (uint16_t)((USARTDIV(_PCLK, _BUAD) << 4) | (USARTDIV_Fraction(_PCLK, _BUAD) & 0xf))


typedef enum
{
	Polling_Enable,
	Polling_Disable,

}PollingMachansim_t;

/************************************************************
 ----------------------- USART APIS  -----------------------
 *************************************************************/

/*************************************************************
 *   @param [in]- USARTx specify which module used USART1 , USART2 or USART3
 *   @param [in]- USARTconfgs Configurations defined by user @ref USART_cfg.c
 *   @brief      - initialize USART mode, buad rate, frame, enable/disable interrupt
 *   @retval      - none
 *   @Note - only Asynchronous mode is covered
 */
void MCAL_UART_Init(USART_t * USARTx ,UART_Config_t * UARTconfigs);



/*************************************************************
 *   @param [in]- USARTx Deinitialize
 *   @brief      - Disable Uart
 *   @retval      - none
 *   @Note - only Asynchronous mode is covered
 */
void MCAL_UART_DeInit(USART_t * USARTx );




/*************************************************************
 *   @param [in]- USARTx specify which module used USART1 , USART2 or USART3
 *   @param [in]- USARTconfgs Configurations defined by user @ref USART_cfg.c
 *   @param [in]- pollingEn --> enable polling machansim or not
 *   @param [in]- Tdata --> Data to be transmit
 *   @brief     - Transmit data via UART
 *   @retval    - none
 *   @Note - only Asynchronous mode is covered
 */
void MCAL_UART_Transmit(USART_t * USARTx ,UART_Config_t * UARTconfigs,PollingMachansim_t pollingEn , uint16_t *Tdata );



/*************************************************************
 *   @param [in]- USARTx specify which module used USART1 , USART2 or USART3
 *   @param [in]- USARTconfgs Configurations defined by user @ref USART_cfg.c
 *   @param [in]- pollingEn --> enable polling machanism or not
 *   @brief     - receive data via UART
 *   @retval    - uint16_t received data (8 or 9 data)
 *   @Note - only Asynchronous mode is covered
 */
uint16_t MCAL_UART_Receive(USART_t * USARTx ,UART_Config_t * UARTconfigs,PollingMachansim_t pollingEn );

/**================================================================
 * @Fn				-MCAL_UART_GPIO_Set_Pins
 * @brief 			- intialize GPIO Pins
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Should enable the corresponding ALT  & GPIO  in RCC clock Also called after MCAL_UART_Init()
 */
void MCAL_UART_GPIO_Set_Pins(USART_t *USARTx , UART_Config_t * UARTconfigs);








#endif
