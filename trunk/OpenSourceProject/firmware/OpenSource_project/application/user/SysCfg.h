#ifndef __SYSCFG_H
#define __SYSCFG_H

/***** Firmware Version Number *************************************************
   Version Number Format
   [VER_MAJOR].[VER_MINOR][VER_BUILD].[VER_TEST][VER_PATCH]
   Example: V1.00A
*******************************************************************************/
#define VER_MAJOR						1        //¹Ì¼þ°æ±¾
#define VER_MINOR						20
#define VER_BUILD						0
#define VER_PATCH						' '

#define  WDG_EN                                                 0u
#define  TIM2_EN                                                0u 
#define  TIM3_EN                                                0u 
#define  TIM4_EN                                                0u 
#define  UART1_EN                                               1u
#define  UART2_EN                                               1u
#define  UART3_EN                                               1u
#define  UART4_EN                                               0u


#endif /* __SYSCFG_H */
