/*
 * AFIO_prog.c
 *
 *  Created on: Jul 11, 2023
 *      Author: Ahmed Naeem
 */
#include "AFIO_private.h"
#include "AFIO_cfg.h"
#include "AFIO_interface.h"




void MAFIO_vSetEXTIConfiguration(uint8_t cpy_u8LineNum , PortMap_EXTI_t cpy_enuPortMap)
{
	uint8_t Local_u8RegNum  = cpy_u8LineNum / 4 ;

	AFIO->EXTICR[Local_u8RegNum] &= ~(0x0f << ( (cpy_u8LineNum % 4) * 4 )) ;
	AFIO->EXTICR[Local_u8RegNum] |= (cpy_enuPortMap << ( (cpy_u8LineNum % 4) * 4 )) ;
}
