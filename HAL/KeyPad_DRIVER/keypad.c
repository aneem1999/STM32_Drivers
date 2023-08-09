/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   stm32f103x6.h
 *************************************************************/

/*************************************************************
 *  Includes
 */

#include "../LIB/stm32f103x6.h"
#include "../MCAL_STM32F103C6/GPIO_Driver/GPIO.h"
#include "keyPad.h"
#include "keypad_cfg.h"


/*************************************************************
 *   @param [in]- Nothing
 *   @brief  initialization for number of 4x4 Keypads init rows as output and write
 *   		default state to it according to connection
 *   		and init columns as input
 *   @retval none
 */
void KeyPad_init()
{
	uint8_t index_1 = 0,index_2 = 0;


	for (index_1 = 0; index_1 < KeypadsCount; index_1++)
	{
		for (index_2 = 0; index_2 < 4; index_2++)
		{
			/* Init rows and columns*/
			MCAL_GPIO_Init(Keypads[index_1].rows[index_2].GPIOx ,&Keypads[index_1].rows[index_2]);
			MCAL_GPIO_Init(Keypads[index_1].cols[index_2].GPIOx , &Keypads[index_1].cols[index_2]);

			/* Write default state to rows pins according to HW connections */
			MCAL_GPIO_WritePin(Keypads[index_1].rows[index_2].GPIOx ,Keypads[index_1].rows[index_2].PinNum ,Keypads[index_1].defState);
		}
	}
}


/*************************************************************
 *   @param [in] - keypad index according to HW connection
 *   @param [out]- row and column number for pressed key
 *   @brief  Get Key pressed or not and key row and column
 *   @retval key pressing status
 */
KeyStatus_t GetKeyPressed(uint8_t *row, uint8_t *colum , Keypad_t Keypad_index)
{
	KeyStatus_t pressstatus = KEY_NOT_PRESSED;
	uint8_t rowindex = 0, colindex = 0, breakFlag = 0;
	STATE_t drive_state = LOW;


	/*Check drive state by inverting default state*/
	if (LOW == Keypads[Keypad_index].defState)
	{
		drive_state = HIGH;
	}
	else if (HIGH == Keypads[Keypad_index].defState)
	{
		drive_state = LOW;
	}

	/*monitor rows by drive state and check column status */
	for (rowindex = 0; rowindex < 4; rowindex++)
	{
		/*monitor rows by drive state*/
		MCAL_GPIO_WritePin(Keypads[Keypad_index].rows[rowindex].GPIOx ,Keypads[Keypad_index].rows[rowindex].PinNum,drive_state );

		/*check column status */
		for (colindex = 0; colindex < 4; colindex++)
		{
			if (drive_state == MCAL_GPIO_ReadPin(Keypads[Keypad_index].cols[colindex].GPIOx, Keypads[Keypad_index].cols[colindex].PinNum))
			{
				pressstatus = KEY_PRESSED;
				*colum = colindex;
				*row = rowindex;
				breakFlag = 1;
				/* Wait Until Key is OFF */
				while(drive_state == MCAL_GPIO_ReadPin(Keypads[Keypad_index].cols[colindex].GPIOx, Keypads[Keypad_index].cols[colindex].PinNum));
			}
		}
		/* return row state again to default state */
		MCAL_GPIO_WritePin(Keypads[Keypad_index].rows[rowindex].GPIOx ,Keypads[Keypad_index].rows[rowindex].PinNum,Keypads[Keypad_index].defState );

		if(breakFlag == 1)
			break;
	}


	return pressstatus ;

}


