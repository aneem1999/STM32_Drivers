#ifndef KEYPAD_h
#define KEYPAD_h


#include "../LIB/stm32f103x6.h"
#include "../MCAL_STM32F103C6/GPIO_Driver/GPIO.h"
#include "../HAL/LCD_DRIVER/LCD.h"
#include "KeyPad_cfg.h"
typedef enum
{
    Keypad_1,
    keypad_2
} Keypad_t;

typedef enum
{
    KEY_NOT_PRESSED,
    KEY_PRESSED
} KeyStatus_t;

/*************************************************************
 *   @param [in]- Nothing
 *   @brief  initialization for number of 4x4 Keypads init rows as output and write
 *   		default state to it according to connection
 *   		and init columns as input
 *   @retval none
 */
void KeyPad_init();


/*************************************************************
 *   @param [in] - keypad index according to HW connection
 *   @param [out]- row and column number for pressed key
 *   @brief  Get Key pressed or not and key row and column
 *   @retval key pressing status
 */
KeyStatus_t GetKeyPressed(uint8_t *row, uint8_t *colum , Keypad_t Keypad_index);

#endif
