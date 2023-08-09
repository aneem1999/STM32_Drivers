/*
 * AFIO_interface.h
 *
 *  Created on: Jul 11, 2023
 *      Author: ncm
 */

#ifndef AFIO_AFIO_INTERFACE_H_
#define AFIO_AFIO_INTERFACE_H_

#include <stdint.h>

typedef enum
{
	EXTI_PORTA_MAP,
	EXTI_PORTB_MAP,
	EXTI_PORTC_MAP,
	EXTI_PORTD_MAP
}PortMap_EXTI_t;



void MAFIO_vSetEXTIConfiguration(uint8_t cpy_u8LineNum , PortMap_EXTI_t cpy_enuPortMap);




#endif /* AFIO_AFIO_INTERFACE_H_ */
