/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmingfei2013@126.com
  *                                      All Rights Reserved
  * @file    iic.c
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
/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#define GPIO_PORT_I2C              GPIOC
#define I2C_SCL_PIN                GPIO_Pin_12                        
#define I2C_SDA_PIN                GPIO_Pin_11

#define I2C_SCL_1()  GPIO_SetBits(GPIO_PORT_I2C, I2C_SCL_PIN) 	        /* SCL = 1 */
#define I2C_SCL_0()  GPIO_ResetBits( GPIO_PORT_I2C, I2C_SCL_PIN)        /* SCL = 0 */

#define I2C_SDA_1()  GPIO_SetBits( GPIO_PORT_I2C, I2C_SDA_PIN)          /* SDA = 1 */
#define I2C_SDA_0()  GPIO_ResetBits( GPIO_PORT_I2C, I2C_SDA_PIN)        /* SDA = 0 */

#define I2C_SDA_READ()  ((GPIO_PORT_I2C->IDR & I2C_SDA_PIN) != 0)       /* read SDA status */
#define I2C_SCL_READ()  ((GPIO_PORT_I2C->IDR & I2C_SCL_PIN) != 0)       /* read SCLs tatus */


void  board_i2cInit( void )
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin   = I2C_SCL_PIN|I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIO_PORT_I2C, &GPIO_InitStructure );
}

static void i2c_Delay(void)
{
    uint8_t i;
    for (i = 0; i < 30; i++);
}

void i2c_Init(void)
{
    board_i2cInit();  /* i2c port init */
    i2c_Stop();
}

void i2c_Start(void)
{
    I2C_SDA_1();
    I2C_SCL_1();
    i2c_Delay();
    I2C_SDA_0();
    i2c_Delay();
    I2C_SCL_0();
    i2c_Delay();
}


void i2c_Stop(void)
{
    I2C_SDA_0();
    I2C_SCL_1();
    i2c_Delay();
    I2C_SDA_1();
}

void i2c_SendByte(uint8_t _ucByte)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
          if (_ucByte & 0x80)
          {
                  I2C_SDA_1();
          }
          else
          {
                  I2C_SDA_0();
          }
          i2c_Delay();
          I2C_SCL_1();
          i2c_Delay();
          I2C_SCL_0();
          if (i == 7)
          {
                   I2C_SDA_1(); 
          }
          _ucByte <<= 1;
          i2c_Delay();
    }
}


uint8_t i2c_ReadByte(void)
{
    uint8_t i;
    uint8_t value;

    value = 0;
    for (i = 0; i < 8; i++)
    {
        value <<= 1;
        I2C_SCL_1();
        i2c_Delay();
        if (I2C_SDA_READ())
        {
                value++;
        }
        I2C_SCL_0();
        i2c_Delay();
    }

    return value;
}

/**
  * @brief  wait for i2c ack.
* @retval result:
  */
i2c_TypeDef i2c_WaitAck(void)
{
    i2c_TypeDef re = I2C_OK;

    I2C_SDA_1();	
    i2c_Delay();
    I2C_SCL_1();	
    i2c_Delay();
    if (I2C_SDA_READ())
    {
        re = I2C_FAIL;
    }
    I2C_SCL_0();
    i2c_Delay();
    
    return re;
}

void i2c_Ack(void)
{
    I2C_SDA_0();
    i2c_Delay();
    I2C_SCL_1();
    i2c_Delay();
    I2C_SCL_0();
    i2c_Delay();
    I2C_SDA_1();
}


void i2c_NAck(void)
{
    I2C_SDA_1();	
    i2c_Delay();
    I2C_SCL_1();
    i2c_Delay();
    I2C_SCL_0();
    i2c_Delay();
}

i2c_TypeDef i2c_CheckDevice(uint8_t _Address)
{
    i2c_TypeDef ucAck = I2C_FAIL;

    if (I2C_SDA_READ() && I2C_SCL_READ())
    {
        i2c_Start();		

        i2c_SendByte(_Address | I2C_WR);
        ucAck = i2c_WaitAck();	

        i2c_Stop();
    }
    
    return ucAck;
}

/* End of this file */