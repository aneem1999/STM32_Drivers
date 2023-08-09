/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   1/12/2022
 *       @file   :   EXTI.h
 *************************************************************/

#ifndef EXTI_H
#define EXTI_H

/*************************************************************
includes
*************************************************************/
#include "../LIB/stm32f103x6.h"
#include "../MCAL_STM32F103C6/GPIO_Driver/GPIO.h"


/*************************************************************
EXTI configuration structure
*************************************************************/

typedef enum {
	RisingEdge,
	FallingEdge,
	RisingFallingEdge

}EXTI_TriggerCase_t;

typedef enum {
	EXTI_Enabled,
	EXTI_Disabled

}EXTI_Status_t;

typedef struct {

	uint16_t            PinNum; 		  /* EXTI Mapping Pin  @ref GPIO_PIN_DEFINE */
	GPIOx_t *          GPIO_Port;		  /* EXTI Mapping Port */
	EXTI_TriggerCase_t TriggerCase ;      /* Trigger Case Rising , falling or rising falling */
	EXTI_Status_t      IRQ_Status;        /* IRQ line Enabled or disabled */
	void (*EXTI_CallBack)(void);          /* Call back function */

}EXTI_Config_t;


/*************************************************************
EXTI APIs
*************************************************************/
void MCAL_EXTI_Intit(EXTI_Config_t* EXTI_Config);
void MCAL_EXTI_DeIntit(void);


#endif
