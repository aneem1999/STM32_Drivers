/*
 * EXTI_private.h
 *
 *  Created on: Jul 11, 2023
 *      Author: ncm
 */

#ifndef EXTI_EXTI_PRIVATE_H_
#define EXTI_EXTI_PRIVATE_H_


/*External Interrupt*/
#define EXTI_BASE		 0x40010400UL



/*External Interrupt*/
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

} EXTI_t;


#define EXTI 		((EXTI_t *)EXTI_BASE)







#endif /* EXTI_EXTI_PRIVATE_H_ */
