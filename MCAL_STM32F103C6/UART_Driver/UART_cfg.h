#ifndef UART_CFG_H
#define UART_CFG_H
/*************************************************************
 *    Includes
 *************************************************************/
#include "stm32f103x6.h"


/************************************************************
 -------------------  Helper Enums   ------------------------
 ***********************************************************/


/************************************************************
 -------------- UART Configuration   -----------------
 ***********************************************************/

typedef struct
{
    uint8_t Mode;       		/* mode TX or RX @ref UART_MODE_DEFINE */
    uint8_t DataLength;			/* Data length 8 , 9 */
    uint8_t Parity;     		/*even or odd or disabled  @ref UART_PARITY_DEFINE*/
    uint8_t Stopbts;    		/* 0.5, 1, 1.5 or 2 stop bits @ref UART_StopBits_define */
    uint32_t BaudRate;          /* Baud rate @ref UART_BaudRate_define */
    uint8_t flowcontrol;
    uint8_t USART_IRQ_EN;        /* Interrupt enable @ref USART_IRQ_define */
    void (*USART_Callback)();	/* Interrupt callback function */

} UART_Config_t;

/************************************************************
 ---------------     Reference Macros      ------------------
 ***********************************************************/
/* @ref UART_MODE_DEFINE */
#define UART_MODE_RX 			(uint32_t) (1<<2)
#define UART_MODE_TX 			(uint32_t) (1<<3)
#define UART_MODE_TX_RX 		(uint32_t) ((1<<3)|(1<<2))

/* @ref UART_PARITY_DEFINE */
#define UART_PARTY_Disable 		(uint32_t)(0)
#define UART_PARTY_Even 		(uint8)(1<<10)
#define UART_PARTY_Odd     		(uint8)(1<<10 | 1<<9)


/*@ref UART_StopBits_define */

#define UART_StopBits_half                  (uint32_t)(1<<12)
#define UART_StopBits_1                     (uint32_t)(0)
#define UART_StopBits_1_half                (uint32_t)(3<<12)
#define UART_StopBits_2                     (uint32_t)(2<<12)



/*USART_BaudRate_define*/

#define UART_BaudRate_2400                   2400
#define UART_BaudRate_9600                   9600
#define UART_BaudRate_19200                  19200
#define UART_BaudRate_57600                  57600
#define UART_BaudRate_115200                 (uint32_t)115200
#define UART_BaudRate_230400                 230400
#define UART_BaudRate_460800                 460800
#define UART_BaudRate_921600                 921600
#define UART_BaudRate_2250000                2250000
#define UART_BaudRate_4500000                4500000

/*USART_IRQ_define*/

#define UART_IRQ_None       (uint32_t)0
#define UART_IRQ_RXNE       (uint32_t)(1<<5) /* Recived data is ready tp be read*/
#define UART_IRQ_TC         (uint32_t)(1<<6) /* Transmit complete interrupt*/
#define UART_IRQ_TXE        (uint32_t)(1<<7) /* Transmit empty interrupt*/
#define UART_IRQ_PE         (uint32_t)(1<<8) /* Parity error interrupt*/



#endif
