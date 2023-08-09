#ifndef KEYPAD_CFG_H
#define KEYPAD_CFG_H


typedef struct
{
	GPIO_Pinconfig_t rows[4]; 	 	/*Rows are outputs*/
	GPIO_Pinconfig_t cols[4]; 		/*columns are inputs*/
	STATE_t defState;			    /*default state*/
}KeypadConfg_t;



extern KeypadConfg_t Keypads[];
extern uint8_t KeypadsCount;

extern uint8_t KeypadChars[4][4];

#endif
