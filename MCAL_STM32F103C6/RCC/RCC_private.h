

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

#include <stdint.h>

/* ===============================================================
   ---------------------- RCC Registers --------------------------
   =============================================================== */
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t AHBSTR;
    volatile uint32_t CFGR2;

} RCC_t;


#define RCC_BASE                0x40021000UL
#define RCC                     ((RCC_t *)RCC_BASE)




/* ===============================================================
   ------------------ CLOCK SOURCE SELECT Values -----------------
   =============================================================== */

#define HSI_CLOCK                0   
#define HSE_CRYSTAL_CLOCK        1
#define PLL_CLOCK                2
#define HSE_RC_CLOCK             3



#endif
