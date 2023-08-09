/*
 * NVIC_private.h
 *
 *  Created on: Jul 10, 2023
 *      Author: Ahmed Naeem
 */

#ifndef NVIC_NVIC_PRIVATE_H_
#define NVIC_NVIC_PRIVATE_H_


#define NVIC_BASE			0xE000E100



#define   	 NVIC_ISER0   	*((uint32_t*)NVIC_BASE + 0x00)
#define 	 NVIC_ISER1		*((uint32_t*)NVIC_BASE + 0x04)
#define 	 NVIC_ISER2 	*((uint32_t*)NVIC_BASE + 0x08)
#define 	 NVIC_ICER0 	*((uint32_t*)NVIC_BASE + 0x80)
#define 	 NVIC_ICER1 	*((uint32_t*)NVIC_BASE + 0x84)
#define 	 NVIC_ICER2 	*((uint32_t*)NVIC_BASE + 0x88)
#define 	 NVIC_ISPR0		*((uint32_t*)NVIC_BASE + 0x100)
#define 	 NVIC_ISPR1		*((uint32_t*)NVIC_BASE + 0x104)
#define 	 NVIC_ISPR2		*((uint32_t*)NVIC_BASE + 0x108)
#define 	 NVIC_ICPR0		*((uint32_t*)NVIC_BASE + 0x180)
#define 	 NVIC_ICPR1		*((uint32_t*)NVIC_BASE + 0x184)
#define 	 NVIC_ICPR2		*((uint32_t*)NVIC_BASE + 0x188)
#define 	 NVIC_IABR0		*((volatile uint32_t*)NVIC_BASE + 0x200) /* Read only Registers*/
#define 	 NVIC_IABR1		*((volatile uint32_t*)NVIC_BASE + 0x204) /* Read only Registers*/
#define 	 NVIC_IABR2		*((volatile uint32_t*)NVIC_BASE + 0x208) /* Read only Registers*/

#define 	 NVIC_IPR 		((volatile uint8_t*)NVIC_BASE + 0x0B)





/*
 * 	PRIGROUP
 * 	 [2:0]
 * 	0b011 	0bxxxx 		[7:4] 	None 	16 		None
	0b100 	0bxxx.y 	[7:5] 	[4] 	8 		2
	0b101 	0bxx.yy 	[7:6] 	[5:4] 	4 		4
	0b110 	0bx.yyy 	[7] 	[6:4] 	2 		8
	0b111 	0b.yyyy 	None 	[7:4] 	None 	16
 * */

#define MNVIC_GROUP_4_SUB_0 	0x05FA0300  /* 4  bits [7:4] for group priority No ---- subpriority */
#define MNVIC_GROUP_3_SUB_1 	0x05FA0400  /* 3  bits [7:5] for group priority 1 [4]   subpriority*/
#define MNVIC_GROUP_2_SUB_2 	0x05FA0500  /* 2  bits [7:6] for group priority 2 [5:4] subpriority*/
#define MNVIC_GROUP_1_SUB_3 	0x05FA0600  /* 1  bits [7]   for group priority 3 [6:4] subpriority*/
#define MNVIC_GROUP_0_SUB_4 	0x05FA0700  /* No bits  ---- for group priority 4 [7:4] subpriority*/






#endif /* NVIC_NVIC_PRIVATE_H_ */
