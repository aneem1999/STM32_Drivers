#include "keyPad.h"
#include "keypad_cfg.h"

#include "../LIB/stm32f103x6.h"
#include "../MCAL_STM32F103C6/GPIO_Driver/GPIO.h"

/* Available keypads and its pins, ports and default state*/
KeypadConfg_t Keypads[] =
{
		{
				{
						{GPIO_PIN0, GPIOB, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_10M},
						{GPIO_PIN1, GPIOB, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_10M},
						{GPIO_PIN3, GPIOB, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_10M},
						{GPIO_PIN4, GPIOB, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_10M}
				},

				{
						{GPIO_PIN5, GPIOB, GPIO_MODE_INPUT_FLOAT, GPIO_INPUT_MOD},
						{GPIO_PIN6, GPIOB, GPIO_MODE_INPUT_FLOAT, GPIO_INPUT_MOD},
						{GPIO_PIN7, GPIOB, GPIO_MODE_INPUT_FLOAT, GPIO_INPUT_MOD},
						{GPIO_PIN8, GPIOB, GPIO_MODE_INPUT_FLOAT, GPIO_INPUT_MOD},

				},

				LOW
		}
};

 uint8_t KeypadChars[4][4] = {
										{'7' ,'8' ,'9' ,'A'},
										{'4', '5', '6', 'B'},
										{'1', '2', '3', 'C'},
										{'#' , '=', '0' , 'D'}
};

uint8_t KeypadsCount = sizeof(Keypads) / sizeof(KeypadConfg_t);
