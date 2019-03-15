/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    spi.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/25
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
*/
#include "includes.h"


void SPIx_Init( INT8U SPIXN )
{
      SPI_InitTypeDef  SPI_InitStructure;
      GPIO_InitTypeDef GPIO_InitStructure;
      /* SPI configuration */
      SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
      SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
      SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
      SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
      SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
      SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
      SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
      SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
      SPI_InitStructure.SPI_CRCPolynomial = 7;
      
      switch ( SPIXN ){
      case SPIX1:
            RCC_APB1PeriphClockCmd( RCC_APB2Periph_SPI1, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);         
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1, ENABLE );
            SPI_Init( SPI1, &SPI_InitStructure );
            SPI_Cmd(SPI1, ENABLE);
            SPI1_ReadWriteByte( 0xff );
        break;
      case SPIX2:
          RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE );
          SPI_Init( SPI2, &SPI_InitStructure);
          SPI_Cmd( SPI2, ENABLE);   
          SPI2_ReadWriteByte( 0xff );

          GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
          GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
          GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
          GPIO_Init(GPIOB, &GPIO_InitStructure); 
        break;
      case SPIX3:
          RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI3, ENABLE );
          SPI_Init( SPI3, &SPI_InitStructure);
          SPI_Cmd( SPI3, ENABLE);  
          SPI3_ReadWriteByte( 0xff );
      default:
        break;
      }     
}

/*
********************************************************************************
* Argument(s) : The maximal SPI speed is  392314 Byte/S
* Notes:
*   Prescaler_128, 59592 Byte/S
*   Prescaler_64, 104617 Byte/S
*   prescaler_32, 168134 Byte/S    162337 Byte/S
*   Prescaler_16, 261543 Byte/S    247777 Byte/S
*   Prescaler_8,  313851 Byte/S    336269 Byte/S
*   Prescaler_4,  392314 Byte/S    392314 Byte/S
*   Prescaler_2,  392314 Byte/S
********************************************************************************
*/
void SPIX_SetSpeed( INT8U SPIXN ,INT8U SpeedSet )
{
    SPI_InitTypeDef SPI_InitStructure ;
    
    SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex ;
    SPI_InitStructure.SPI_Mode=SPI_Mode_Master ;
    SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b ;
    SPI_InitStructure.SPI_CPOL=SPI_CPOL_High ;
    SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge ;
    SPI_InitStructure.SPI_NSS=SPI_NSS_Soft ;
    
    if( SpeedSet == SPI_SPEED_LOW ){
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;
    }
    else{
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_32;
    }
    SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB ;
    SPI_InitStructure.SPI_CRCPolynomial=7 ;
    
    switch ( SPIXN ){
      case 1:
          SPI_Init(SPI1,&SPI_InitStructure); 
          SPI1_ReadWriteByte( 0xff );
          break;
      case 2:
          SPI_Init(SPI2,&SPI_InitStructure); 
           SPI2_ReadWriteByte( 0xff );
          break;
      case 3:
          SPI_Init(SPI3,&SPI_InitStructure); 
          SPI1_ReadWriteByte( 0xff );
          break;
    }
}


INT8U SPI1_ReadWriteByte( INT8U TxData )
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, TxData);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI1);
}

INT8U SPI2_ReadWriteByte( INT8U TxData )
{
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI2, TxData);
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI2);
}

INT8U SPI3_ReadWriteByte( INT8U TxData )
{
    while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI3, TxData);
    while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI3);
}

/* EOF */  