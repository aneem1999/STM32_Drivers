/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   GPIO.c
 *************************************************************/
/*************************************************************
 Includes
*************************************************************/
#include "stm32f103x6.h"
#include "GPIO.h"

/*************************************************************/

/* helper functions*/

static uint8_t GET_CRLH_POSTION(uint16_t PinNum)
{
	switch (PinNum)
	{
	case GPIO_PIN0:
		return 0;
		break;
	case GPIO_PIN1:
		return 4;
		break;
	case GPIO_PIN2:
		return 8;
		break;
	case GPIO_PIN3:
		return 12;
		break;
	case GPIO_PIN4:
		return 16;
		break;
	case GPIO_PIN5:
		return 20;
		break;
	case GPIO_PIN6:
		return 24;
		break;
	case GPIO_PIN7:
		return 28;
		break;
	case GPIO_PIN8:
		return 0;
		break;
	case GPIO_PIN9:
		return 4;
		break;
	case GPIO_PIN10:
		return 8;
		break;
	case GPIO_PIN11:
		return 12;
		break;
	case GPIO_PIN12:
		return 16;
		break;
	case GPIO_PIN13:
		return 20;
		break;
	case GPIO_PIN14:
		return 24;
		break;
	case GPIO_PIN15:
		return 28;
		break;
	}

	return 1;
}

/*************************************************************/

/* APIs Supported by "MCAL GPIO DRIVER"*/
/*************************************************************
 *   @Fun - MCAL_GPIO_Init
 *   @param [in]- GPIOx where x is the port A,B,C,D
 *   @param [in]- PinConfig pin configured in GPIO_cfg.c
 *   @brief - initlize pin Mode , Speed
 *   @retval - none
 *   @Note - Port c and d are partial in stm32f10x8
 */
void MCAL_GPIO_Init(GPIOx_t *GPIOx, GPIO_Pinconfig_t *PinConfig)
{
	uint8_t Pin_CNF_MOD;

	/* check Low or high configuration register*/
	volatile uint32_t *ConfigRegister = NULL;
	(PinConfig->PinNum < GPIO_PIN8) ? (ConfigRegister = &GPIOx->CRL) : (ConfigRegister = &GPIOx->CRH);

	/*Clear CNF and MOD bits */
	(*ConfigRegister) &= ~(0x0f << GET_CRLH_POSTION(PinConfig->PinNum));

	/*CHeck Input or Output*/
	if ((PinConfig->PinMode == GPIO_MODE_OUTPUT_PP) || (PinConfig->PinMode == GPIO_MODE_OUTPUT_OD) || (PinConfig->PinMode == GPIO_MODE_AF_PP) || (PinConfig->PinMode == GPIO_MODE_AF_OD))
	{
		/* Output */
		/*Set CNF and Mode bits*/
		Pin_CNF_MOD = ((((PinConfig->PinMode - 4) << 2) | (PinConfig->PinSpeed)) & 0x0f);
	}
	else
	{
		/*Input*/

		if ((PinConfig->PinMode == GPIO_MODE_INPUT_FLOAT) || (PinConfig->PinMode == GPIO_MODE_INPUT_ANALOG))
		{
			/*Set CNF and Mode bits*/
			Pin_CNF_MOD = (((PinConfig->PinMode << 2) | 0x0) & 0x0f);
		}
		else
		{
			/*Set CNF and Mode bits as input pull up/down */
			Pin_CNF_MOD = (((GPIO_MODE_INPUT_PU << 2) | 0x0) & 0x0f);

			if (PinConfig->PinMode == GPIO_MODE_INPUT_PU)
			{
				/* 1 on ODR for Pull up*/
				GPIOx->ODR |= PinConfig->PinNum;
			}
			if (PinConfig->PinMode == GPIO_MODE_INPUT_PU)
			{
				/* 0 on ODR for Pull down*/
				GPIOx->ODR &= ~(PinConfig->PinNum);
			}
		}
	}

	(*ConfigRegister) |= (Pin_CNF_MOD << GET_CRLH_POSTION(PinConfig->PinNum));
}

/*************************************************************
 *   @Fun - MCAL_GPIO_GlobalInit
 *   @param [in]- GPIOx where x is the port A,B,C,D
 *   @param [in]- PinConfig pin configured in GPIO_cfg.c
 *   @brief - inlize all pins Mode , Speed
 *   @retval - none
 *   @Note - Port c and d are partial in stm32f10x8
 */

void MCAL_GPIO_GlobalInit()
{
	uint8_t count = 0;
	for (count = 0; count < PinCount; count++)
	{
		MCAL_GPIO_Init(PINs_Config[count].GPIOx, &PINs_Config[count]);
	}
}

/*************************************************************
 *   @Fun - MCAL_GPIO_DeInit
 *   @brief - Deinit GPIO port and return it to reset state
 *   @param [in] - GPIOx where x is the port A,B,C,D
 *   @retval -none
 *   @Note -
 */
void MCAL_GPIO_DeInit(GPIOx_t *GPIOx)
{
	/*
	IOPARST: I/O port A reset
	Set and cleared by software.
	0: No effect
	1: Reset I/O port A */
	if (GPIOx == GPIOA)
	{
		RCC->APB1RSTR |= (1 << 2);
		RCC->APB1RSTR &= ~(1 << 2);
	}
	else if (GPIOx == GPIOB)
	{
		RCC->APB1RSTR |= (1 << 3);
		RCC->APB1RSTR &= ~(1 << 3);
	}
	else if (GPIOx == GPIOC)
	{
		RCC->APB1RSTR |= (1 << 4);
		RCC->APB1RSTR &= ~(1 << 4);
	}
	else if (GPIOx == GPIOD)
	{
		RCC->APB1RSTR |= (1 << 5);
		RCC->APB1RSTR &= ~(1 << 5);
	}
}
/*************************************************************
 *   @Fun - MCAL_GPIO_ReadPin
 *   @brief - Read pin from Port
 *   @param [in] - GPIOx where x is the port A,B,C,D
 *   @param [in] - PinNum at @ref GPIO_PIN_DEFINE
 *   @retval - STATE_t value (0 or 1)
 *   @Note -
 */
STATE_t MCAL_GPIO_ReadPin(GPIOx_t *GPIOx, uint16_t PinNum)
{
	if (((GPIOx->IDR) & PinNum) != LOW)
		return HIGH;
	else
		return LOW;
}
/*************************************************************
 *   @**
 *   @fun - MCAL_GPIO_ReadPort
 *   @brief - Read a port value
 *   @param [in] - GPIOx where x is the port A,B,C,D
 *   @retval - uint16_t value
 *   @Note -
 */
uint16_t MCAL_GPIO_ReadPort(GPIOx_t *GPIOx)
{
	return ((uint16_t)GPIOx->IDR);
}

/*************************************************************
 *   @Fun - MCAL_GPIO_WritePin
 *   @brief - Write to pin on Port
 *   @param [in] - GPIOx where x is the port A,B,C,D
 *   @param [in] - PinNum at @ref GPIO_PIN_DEFINE
 *   @param [in] - value of type STATE_t
 *   @retval - none
 *   @Note -
 */
void MCAL_GPIO_WritePin(GPIOx_t *GPIOx, uint16_t PinNum, STATE_t value)
{
	if (value == HIGH)
	{
		GPIOx->ODR |= PinNum;
	}
	else if (value == LOW)
	{
		GPIOx->ODR &= ~(PinNum);
	}
}
/*************************************************************
 *   @Fun -MCAL_GPIO_WritePort
 *   @brief - Write value to port
 *   @param [in] - GPIOx where x is the port A,B,C,D
 *   @param [in] - value of type uint16_t
 *   @retval - none
 *   @Note -
 */
void MCAL_GPIO_WritePort(GPIOx_t *GPIOx, uint16_t value)
{
	GPIOx->ODR = value;
}
/*************************************************************
 *   @Fun -MCAL_GPIO_TogglePin
 *   @brief - toggle Pin
 *   @param [in] - GPIOx where x is the port A,B,C,D
 *   @param [in] - PinNum at @ref GPIO_PIN_DEFINE
 *   @retval - none
 *   @Note -
 */
void MCAL_GPIO_TogglePin(GPIOx_t *GPIOx, uint16_t PinNum)
{
	GPIOx->ODR ^= PinNum;
}

/*************************************************************
 *   @Fun -  MCAL_GPIO_LockPin
 *   @brief - lock a pin from chaninging until reset
 *   @param [in] - GPIOx where x is the port A,B,C,D
 *   @param [in] - PinNum at @ref GPIO_PIN_DEFINE
 *   @retval - sucess or not
 *   @Note -
 */
uint8_t MCAL_GPIO_LockPin(GPIOx_t *GPIOx, uint16_t PinNum)
{
	/*  LCKK[16]: Lock key
		This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
		0: Port configuration lock key not active
		1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
		LOCK key writing sequence:
		Write 1
		Write 0
		Write 1
		Read 0
		Read 1 (this read is optional but confirms that the lock is active)
	 */

	uint32_t temp = (1 << 16);

	/* LOCK pin */
	temp |= PinNum;
	/*Apply sequence on LCKK[16]: Lock key */
	/* Write 1*/
	GPIOx->LCKR |= temp;
	/* Write 0*/
	GPIOx->LCKR = PinNum;
	/* Write 1*/
	GPIOx->LCKR |= temp;
	/*Read 0*/
	temp = GPIOx->LCKR;

	/* Read 1 (this read is optional but confirms that the lock is active)*/
	if ((uint32_t)((GPIOx->LCKR) & (1 << 16)))
		return 1;
	else
		return 0;
}
