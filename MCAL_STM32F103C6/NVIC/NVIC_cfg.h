/*
 * NVIC_cfg.h
 *
 *  Created on: Jul 10, 2023
 *      Author: ncm
 */

#ifndef NVIC_NVIC_CFG_H_
#define NVIC_NVIC_CFG_H_

/*

 MNVIC_GROUP_4_SUB_0 	0x05FA0300   4  bits [7:4] for group priority No ---- subpriority
 MNVIC_GROUP_3_SUB_1 	0x05FA0400   3  bits [7:5] for group priority 1 [4]   subpriority
 MNVIC_GROUP_2_SUB_2 	0x05FA0500   2  bits [7:6] for group priority 2 [5:4] subpriority
 MNVIC_GROUP_1_SUB_3 	0x05FA0600   1  bits [7]   for group priority 3 [6:4] subpriority
 MNVIC_GROUP_0_SUB_4 	0x05FA0700   No bits  ---- for group priority 4 [7:4] subpriority

*/
#define MNVIC_GROUP_SUB_DISTRIBUTION			MNVIC_GROUP_2_SUB_2



#endif /* NVIC_NVIC_CFG_H_ */
