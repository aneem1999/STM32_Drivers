/*
 * EXTI_interface.h
 *
 *  Created on: Jul 11, 2023
 *      Author: ncm
 */

#ifndef EXTI_EXTI_INTERFACE_H_
#define EXTI_EXTI_INTERFACE_H_


#define EXTI_0 		6
#define EXTI_1 		7
#define EXTI_2 		9
#define EXTI_3 		9
#define EXTI_4 		10

#define EXTI_5 		23
#define EXTI_6 		23
#define EXTI_7 		23
#define EXTI_8 		23
#define EXTI_9 		23

#define EXTI_10 	40
#define EXTI_11 	40
#define EXTI_12 	40
#define EXTI_13 	40
#define EXTI_14 	40
#define EXTI_15 	40





typedef enum {
	RisingEdge,
	FallingEdge,
	AnyLogicalChange
}EXTI_TriggerCase_t;

void MEXTI_vInit(uint8_t cpy_u8InterruptNum );

void MEXTI_vEnable(uint8_t cpy_u8InterruptNum);

void MEXTI_vDisable(uint8_t cpy_u8InterruptNum);

void MEXTI_vSetTriggerCase(uint8_t cpy_u8InterruptNum , EXTI_TriggerCase_t cpy_enuTriggerCase );

void MEXTI_vSWInterruptTrigger(uint8_t cpy_u8InterruptNum);


#endif /* EXTI_EXTI_INTERFACE_H_ */
