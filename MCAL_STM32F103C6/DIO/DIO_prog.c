/*
 * DIO_prog.c
 *
 *  Created on: Jul 25, 2023
 *      Author: Ahmed Naeem
 */

#include "../../LIB/bitmath.h"

#include "DIO_int.h"



/*
 * ===================================================================
 * 				DIO APIs
 *  ===================================================================
 */


void DIO_vInit()
{
	uint8_t Pin_CNF_MOD;
	uint8_t count = 0;
	volatile uint32_t *ConfigRegister;
	uint8_t PosInConfigRegister;


	for(count = 0; count < DIOCount; count++)
	{

		/* check Low or high configuration register*/

		if(DIO_Config[count].PinNum < DIO_PIN_7)
		{
			(ConfigRegister = &DIO_Config[count].GPIOx->CRL)  ;
			PosInConfigRegister = DIO_Config[count].PinNum * 4;
		}
		else
		{
			(ConfigRegister = &DIO_Config[count].GPIOx->CRH);
			PosInConfigRegister = (DIO_Config[count].PinNum - 8) * 4;
		}

		/*Clear CNF and MOD bits */
		(*ConfigRegister) &= ~(0x0f << PosInConfigRegister);

		/*CHeck Input or Output*/
		if ((DIO_Config[count].PinMode == GPIO_MODE_OUTPUT_PP) || (DIO_Config[count].PinMode == GPIO_MODE_OUTPUT_OD) || (DIO_Config[count].PinMode == GPIO_MODE_AF_PP) || (DIO_Config[count].PinMode == GPIO_MODE_AF_OD))
		{
			/* Output */
			/*Set CNF and Mode bits*/
			Pin_CNF_MOD = ((((DIO_Config[count].PinMode - 4) << 2) | (DIO_Config[count].PinSpeed)) & 0x0f);
		}
		else
		{
			/*Input*/

			if ((DIO_Config[count].PinMode == GPIO_MODE_INPUT_FLOAT) || (DIO_Config[count].PinMode == GPIO_MODE_INPUT_ANALOG))
			{
				/*Set CNF and Mode bits*/
				Pin_CNF_MOD = (((DIO_Config[count].PinMode << 2) ) & 0x0f);
			}
			else
			{
				/*Set CNF and Mode bits as input pull up/down */
				Pin_CNF_MOD = (((GPIO_MODE_INPUT_PU << 2) ) & 0x0f);

				if (DIO_Config[count].PinMode == GPIO_MODE_INPUT_PU)
				{
					/* 1 on ODR for Pull up*/

					SET_BIT(DIO_Config[count].GPIOx->ODR , DIO_Config[count].PinNum);
				}
				if (DIO_Config[count].PinMode == GPIO_MODE_INPUT_PU)
				{
					/* 0 on ODR for Pull down*/
					CLR_BIT(DIO_Config[count].GPIOx->ODR , DIO_Config[count].PinNum);
				}
				}
			}

			(*ConfigRegister) |= (Pin_CNF_MOD << PosInConfigRegister);
	}

}



void DIO_vInitPin(GPIOx_t * GPIOx , DIO_Pin_Num_t cpy_enuPinNum , uint8_t cpy_u8PinMode, uint8_t cpy_u8PinSpeed)
{
	uint8_t Pin_CNF_MOD;
	volatile uint32_t *ConfigRegister = &GPIOx->CRL;
	uint8_t PosInConfigRegister;



		/* check Low or high configuration register*/

		if(cpy_enuPinNum < DIO_PIN_7)
		{
			*ConfigRegister = GPIOx->CRL  ;
			PosInConfigRegister = cpy_enuPinNum * 4;
		}
		else
		{
			*ConfigRegister = GPIOx->CRH;
			PosInConfigRegister = (cpy_enuPinNum - 8) * 4;
		}

		/*Clear CNF and MOD bits */
		(*ConfigRegister) &= ~(0x0f << PosInConfigRegister);

		/*CHeck Input or Output*/
		if ((cpy_u8PinMode == GPIO_MODE_OUTPUT_PP) || (cpy_u8PinMode == GPIO_MODE_OUTPUT_OD) || (cpy_u8PinMode == GPIO_MODE_AF_PP) || (cpy_u8PinMode == GPIO_MODE_AF_OD))
		{
			/* Output */
			/*Set CNF and Mode bits*/
			Pin_CNF_MOD = ((((cpy_u8PinMode - 4) << 2) | (cpy_u8PinSpeed)) & 0x0f);
		}
		else
		{
			/*Input*/

			if ((cpy_u8PinMode == GPIO_MODE_INPUT_FLOAT) || (cpy_u8PinMode == GPIO_MODE_INPUT_ANALOG))
			{
				/*Set CNF and Mode bits*/
				Pin_CNF_MOD = (((cpy_u8PinMode << 2) ) & 0x0f);
			}
			else
			{
				/*Set CNF and Mode bits as input pull up/down */
				Pin_CNF_MOD = (((GPIO_MODE_INPUT_PU << 2) ) & 0x0f);

				if (cpy_u8PinMode == GPIO_MODE_INPUT_PU)
				{
					/* 1 on ODR for Pull up*/

					SET_BIT(GPIOx->ODR , cpy_enuPinNum);
				}
				if (cpy_u8PinMode == GPIO_MODE_INPUT_PU)
				{
					/* 0 on ODR for Pull down*/
					CLR_BIT(GPIOx->ODR , cpy_enuPinNum);
				}
				}
			}

			(*ConfigRegister) |= (Pin_CNF_MOD << PosInConfigRegister);


}

void DIO_vSetPin(GPIOx_t *GPIOx , DIO_Pin_Num_t cpy_enuPinNum )
{
	if (cpy_enuPinNum < 16)
		SET_BIT(GPIOx->ODR , cpy_enuPinNum);

}

void DIO_vClearPin(GPIOx_t *GPIOx , DIO_Pin_Num_t cpy_enuPinNum )
{
	if (cpy_enuPinNum < 16)
		CLR_BIT(GPIOx->ODR , cpy_enuPinNum);

}
void DIO_vWritePin( GPIOx_t * GPIOx , DIO_Pin_Num_t cpy_enuPinNum , DIO_Level_t cpy_enuLevel)
{
	if(STD_HIGH == cpy_enuLevel)
	{
		SET_BIT(GPIOx->ODR , cpy_enuPinNum);

	}
	else
	{
		CLR_BIT(GPIOx->ODR , cpy_enuPinNum);


	}
}

void DIO_vTogglePin(GPIOx_t * GPIOx , DIO_Pin_Num_t cpy_enuPinNum )
{
	if (cpy_enuPinNum > 16)
			TOGL_BIT(GPIOx->ODR , cpy_enuPinNum);
}

void DIO_vWriteGroup(GPIOx_t * GPIOx , uint16_t cpy_u16Mask , uint16_t cpy_u16Value )
{
	GPIOx->ODR &= ~cpy_u16Mask ;

	GPIOx->ODR |= (cpy_u16Value & cpy_u16Mask);

}



DIO_Level_t DIO_enuReadPin(DIO_Pin_Num_t PinNum , GPIOx_t * GPIOx)
{
	DIO_Level_t level  = STD_LOW ;
	if(GET_BIT(GPIOx->IDR , PinNum) == 1)
	{
		level = STD_HIGH ;
	}

	return level;

}

uint16_t DIO_u16ReadGroup(GPIOx_t * GPIOx , uint16_t cpy_u16Mask )
{
	uint16_t GroupVal =0;

	GroupVal = GPIOx->IDR & cpy_u16Mask ;

	return GroupVal;

}



uint8_t GPIO_u8LockPin(GPIOx_t *GPIOx, DIO_Pin_Num_t PinNum)
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
		GPIOx->LCKR = (1<<PinNum);
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





