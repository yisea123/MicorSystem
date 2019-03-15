/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmingfei2013@126.com
  *                                      All Rights Reserved
  * @file    iic.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/03/25
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
#ifndef _I2C_H
#define _I2C_H

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C_WR	0		/* Writing bit */
#define I2C_RD	1		/* read bit */

// measurement i2c status
typedef enum{
  I2C_OK = 0,
  I2C_FAIL = 1,
}i2c_TypeDef;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void i2c_Init(void);
void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
i2c_TypeDef i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
i2c_TypeDef i2c_CheckDevice(uint8_t _Address);

#endif  /*  _ADAFRUIT_I2C_H */
