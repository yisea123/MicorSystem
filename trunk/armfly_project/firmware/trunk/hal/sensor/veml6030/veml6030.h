/** \file

$Id: veml6030.h 40486 2018-09-21 14:32:21Z tangmingfei2013@126.com $

Copyright (c) tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/
#ifndef __VEML6030_H
#define __VEML6030_H

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/

/*******************************************************************************
* EXTENT INCLUDE FILES
*******************************************************************************/
#include "gpio_local.h"

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
/*
   VEML6030 slave address can be 0x20 or 0x90, determined by pin ADDR configuration
*/
#define VEML6030_ADDR_ALS                       0x20 // 7-bit: 0x10
//#define VEML6030_ADDR_ALS                      0x90 // 7-bit: 0x48

/*
  VEML6030 registers
*/
#define ALS_CONF                                0x00
#define ALS_THDH                                0x01
#define ALS_THDL                                0x02
#define ALS_PSM                                 0x03
#define ALS_DATA                                0x04
#define ALS_STATUS                              0x06

/*
  VEML6030 command code 00 register bits
*/
#define VEML6030_ALS_CONF_SD                    0x0001
#define VEML6030_ALS_CONF_INT_EN                0x0002
#define VEML6030_ALS_CONF_PERS_MASK             0x0030
#define VEML6030_ALS_CONF_PERS_1                0x0000
#define VEML6030_ALS_CONF_PERS_2                0x0010
#define VEML6030_ALS_CONF_PERS_4                0x0020
#define VEML6030_ALS_CONF_PERS_8                0x0030
#define VEML6030_ALS_CONF_IT_MASK               0x00C0
#define VEML6030_ALS_CONF_IT_100MS              0x0000
#define VEML6030_ALS_CONF_IT_200MS              0x0040
#define VEML6030_ALS_CONF_IT_400MS              0x0080
#define VEML6030_ALS_CONF_IT_800MS              0x00C0
#define VEML6030_ALS_CONF_SM_MASK               0x1800
#define VEML6030_ALS_CONF_SM_x1                 0x0000
#define VEML6030_ALS_CONF_SM_x2                 0x0800
#define VEML6030_ALS_CONF_SM_x1_8               0x1000
#define VEML6030_ALS_CONF_SM_x1_4               0x1800
#define VEML6030_ALS_CONF_DEFAULT               0x0000

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
float veml6030_ReadLux(uint16_t *rawLux);
void veml6030_Init(void);
void veml6030_test( void );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __VEML6030_H */