/*
 * DIO_types.h
 *
 *  Created on: Jul 25, 2023
 *      Author: Ahmed Naeem
 */

#ifndef DIO_DIO_TYPES_H_
#define DIO_DIO_TYPES_H_



typedef enum
{
	DIO_PIN_0,
	DIO_PIN_1,
	DIO_PIN_2,
	DIO_PIN_3,
	DIO_PIN_4,
	DIO_PIN_5,
	DIO_PIN_6,
	DIO_PIN_7,
	DIO_PIN_8,
	DIO_PIN_9,
	DIO_PIN_10,
	DIO_PIN_11,
	DIO_PIN_12,
	DIO_PIN_13,
	DIO_PIN_14,
	DIO_PIN_15

}DIO_Pin_Num_t;


typedef enum
{
    STD_LOW,
    STD_HIGH
} DIO_Level_t;


/*************************************************************/
/* pins confugurations */
/*Struct for pins configurations*/
typedef struct
{
	DIO_Pin_Num_t PinNum;
    GPIOx_t* GPIOx;    /* GPIO ports*/
    uint8_t PinMode;  /* values in @ref GPIO_PIN_MODE*/
    uint8_t PinSpeed; /* values in @ref GPIO_PIN_SPEED*/
} DIO_PinConfig_t;




#endif /* DIO_DIO_TYPES_H_ */
