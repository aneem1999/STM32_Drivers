/*
 * DIO_int.h
 *
 *  Created on: Jul 25, 2023
 *      Author: Ahmed Naeem
 */

#ifndef DIO_DIO_INT_H_
#define DIO_DIO_INT_H_

/*
 * ===================================================================
 * 				Includes
 *  ===================================================================
 */
#include "stdint.h"
#include "DIO_private.h"
#include "DIO_types.h"
#include "DIO_cfg.h"



/*
 * ===================================================================
 * 				DIO APIs
 *  ===================================================================
 */


void DIO_vInit();

void DIO_vInitPin(GPIOx_t* GPIOx, DIO_Pin_Num_t cpy_enuPinNum ,  uint8_t cpy_u8PinMode, uint8_t cpy_u8PinSpeed);

void DIO_vSetPin( GPIOx_t* GPIOx , DIO_Pin_Num_t cpy_enuPinNum );

void DIO_vClearPin( GPIOx_t * GPIOx , DIO_Pin_Num_t cpy_enuPinNum );

void DIO_vTogglePin( GPIOx_t * GPIOx, DIO_Pin_Num_t cpy_enuPinNum );

void DIO_vWritePin( GPIOx_t * GPIOx , DIO_Pin_Num_t cpy_enuPinNum , DIO_Level_t cpy_enuLevel);


void DIO_vWriteGroup(GPIOx_t * GPIOx , uint16_t cpy_u16Mask , uint16_t cpy_u16Value );



DIO_Level_t DIO_enuReadPin(DIO_Pin_Num_t PinNum , GPIOx_t * GPIOx);

uint16_t DIO_u16ReadGroup(GPIOx_t * GPIOx , uint16_t cpy_u16Mask );



uint8_t GPIO_u8LockPin(GPIOx_t *GPIOx, DIO_Pin_Num_t PinNum);






#endif /* DIO_DIO_INT_H_ */
