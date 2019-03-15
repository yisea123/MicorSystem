/** \file

$Id: I2C.c 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __I2C_H
#define __I2C_H

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "stm32f10x.h"

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/


/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/  
#define I2C_WR	0		/* Writing bit */
#define I2C_RD	1		/* read bit */

// measurement i2c status
typedef enum{
  I2C_OK = 0,
  I2C_FAIL = 1,
}i2c_TypeDef;
  
/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/  
void i2c_Init(void);
void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
i2c_TypeDef i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
i2c_TypeDef i2c_CheckDevice(uint8_t _Address);


/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H */  