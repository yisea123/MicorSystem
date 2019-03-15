/**
  ******************************************************************************
  *                     (c) Copyright 2015, tangmingfei2013@126.com
  *                           All Rights Reserved
  * @file    spix.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2015/01/10
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
#ifndef __SPIX_H
#define __SPIX_H

#define EN_SPI2             1         //Enable SPI2
#define SPI2_SPEED          1         //Enable SPI2 speed controler 
#define SPI_SPEED_LOW       0
#define SPI_SPEED_HIGH      1

typedef enum{
    SPI_NULL = 0,
    SPIX1,
    SPIX2,
    SPIX3,
}SPI_ENUM;

void  SPIx_Init( INT8U SPIX );
void  SPIX_SetSpeed( INT8U SPIXN ,INT8U SpeedSet );
INT8U SPI1_ReadWriteByte( INT8U TxData );
INT8U SPI2_ReadWriteByte( INT8U TxData );
INT8U SPI3_ReadWriteByte( INT8U TxData );

#endif  /* __SPIX_H */