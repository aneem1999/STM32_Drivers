/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************

 */


#include "../MCAL_STM32F103C6/DIO/DIO_int.h"
#include "../MCAL_STM32F103C6/RCC/RCC_int.h"
#include "../MCAL_STM32F103C6/SYSTICK/SYSTICK_interface.h"

#include "../HAL/LED_MATRIX/LEDMTRX_int.h"



void mywait(uint8_t x)
{
	for(uint8_t i=0; i<x; i++)
	{
		for(uint8_t j=0; j<255; j++);
	}

}


/* RCC initliztion */





int main(void)
{
	RCC_voidInitSysClock();


	RCC_voidEnableClock(APB2_BUS , 2);

	MSYSTICK_vInit();

	LEDMTRX_vInit();

//	DIO_vInit();



	uint8_t frame[8] = {252, 18, 17, 18, 252, 0, 0, 0};


	while(1)
	{


		LEDMTRX_vDisplay(frame);

//		DIO_vWritePin(GPIOA , DIO_PIN_13, STD_HIGH);
//		MSYSTICK_vSetBusyWait(250000);
////		mywait(200);
//		DIO_vWritePin(GPIOA , DIO_PIN_13, STD_LOW);
//		MSYSTICK_vSetBusyWait(250000);
////		mywait(200);


	}
}
