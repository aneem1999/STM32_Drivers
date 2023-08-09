/*
 * AFIO_private.h
 *
 *  Created on: Jul 11, 2023
 *      Author: ncm
 */

#ifndef AFIO_AFIO_PRIVATE_H_
#define AFIO_AFIO_PRIVATE_H_
#include <stdint.h>

#define AFIO_BASE 0x40010000UL


/*AFIO*/
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	uint32_t RESERVED0;
	volatile uint32_t MAPR2;

} AFIO_t;

#define AFIO	((AFIO_t *)AFIO_BASE)

#endif /* AFIO_AFIO_PRIVATE_H_ */
