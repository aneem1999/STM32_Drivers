/*
 * SYSTICK_interface.h
 *
 *  Created on: Jul 12, 2023
 *      Author: ncm
 */

#ifndef SYSTICK_SYSTICK_INTERFACE_H_
#define SYSTICK_SYSTICK_INTERFACE_H_

#include <stdint.h>

void MSYSTICK_vInit();

void MSYSTICK_vStart();
void MSYSTICK_vStop();
uint32_t MSYSTICK_u32GetElapsedTime();
uint32_t MSYSTICK_u32ReminingTime();

void MSYSTICK_vSetBusyWait(uint32_t cpy_u32Ticks);
void MSYSTICK_vSetIntervalSingle(uint32_t cpy_u32Ticks , void (* cpy_CB)(void));
void MSYSTICK_vSetIntervalPeriodic(uint32_t cpy_u32Peroid , void (* cpy_CB)(void));

void MSYSTICK_vEnableInterrupt();

void MSYSTICK_vDisableInterrupt();

void MSYSTICK_vSetCallBaclFun(void (*cpy_CallBack)());

void MSYSTICK_vSetLoadValue(uint32_t cpy_u32Load);



#endif /* SYSTICK_SYSTICK_INTERFACE_H_ */
