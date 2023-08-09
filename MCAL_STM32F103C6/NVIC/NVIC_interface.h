/*
 * NVIC_interface.h
 *
 *  Created on: Jul 10, 2023
 *      Author: ncm
 */

#ifndef NVIC_NVIC_INTERFACE_H_
#define NVIC_NVIC_INTERFACE_H_

#include <stdint.h>




void MNVIC_vEnableInterrupt(uint8_t cpy_u8InterruptNum);

void MNVIC_vDisableInterrupt(uint8_t cpy_u8InterruptNum);

void MNVIC_vSetPendingFlag(uint8_t cpy_u8InterruptNum);

void MNVIC_vClearPendingFlag(uint8_t cpy_u8InterruptNum);

uint8_t MNVIC_u8GetActiveFlag(uint8_t cpy_u8InterruptNum);

void MNVIC_vSetPriority(int8_t cpy_s8InterruptId , uint8_t cpy_u8GroupPriority , uint8_t cpy_u8GSubPriority);




#endif /* NVIC_NVIC_INTERFACE_H_ */
