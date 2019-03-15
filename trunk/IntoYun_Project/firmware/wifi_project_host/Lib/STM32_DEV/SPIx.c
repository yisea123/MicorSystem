/** \file

$Id: SPIX.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "stm32f10x.h"
#include "spix.h"

/******************************************************************************
* EXTERN FUNCTION IMPLEMENTS
******************************************************************************/
void SPIx_Init( uint8_t SPIXN )
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
void SPIX_SetSpeed( uint8_t SPIXN ,uint8_t SpeedSet )
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

uint8_t SPI1_ReadWriteByte( uint8_t TxData )
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, TxData);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI1);
}

uint8_t SPI2_ReadWriteByte( uint8_t TxData )
{
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI2, TxData);
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI2);
}

uint8_t SPI3_ReadWriteByte( uint8_t TxData )
{
    while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI3, TxData);
    while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI3);
}

/* EOF */  