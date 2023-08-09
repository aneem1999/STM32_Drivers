/*
 * SYSTICK_private.h
 *
 *  Created on: Jul 12, 2023
 *      Author: ncm
 */

#ifndef SYSTICK_SYSTICK_PRIVATE_H_
#define SYSTICK_SYSTICK_PRIVATE_H_

#include <stdint.h>

#define SYSTICK_BASE		0xE000E010


typedef struct
{
	volatile uint32_t CTRL ;
	volatile uint32_t LOAD ;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;

}STK_t;

#define STK    	((STK_t *)SYSTICK_BASE)

#define SYSTICK_AHB_CLOCK				1
#define SYSTICK_AHB_CLOCK_DIVIDED_8		0





#endif /* SYSTICK_SYSTICK_PRIVATE_H_ */
