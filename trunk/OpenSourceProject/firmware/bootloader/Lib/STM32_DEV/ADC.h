/**
  ******************************************************************************
  *                     (c) Copyright 2015, tangmingfei2013@126.com
  *                           All Rights Reserved
  * @file    adc.c
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
#ifndef __ADC_H
#define __ADC_H

typedef enum{
    CH_0 = 0,
    CH_1,
    CH_2,
    CH_3,
    CH_4,
    CH_5,
    CH_6,
    CH_7,
}ADC_CH_ENUM;

#define ADC1_DR_Address   ((u32)0x4001244C)
#define ADC_CH5           ADC_Channel_5
#define ADC_CH6           ADC_Channel_6
#define ADC_CH7           ADC_Channel_7

void ADC_DMAInit( void );
void ADC_InitModel( INT8U Choose_Ch );
INT16U ADC_GetADCValue( INT8U Cehoos_Ch );
void ADC_AddADCValue( void  );
INT16U ADC_GetAverageRaw( INT16U data );
INT16U ADC_GetAverageRawBuf( INT16U *pu16_buf );

#endif       /* __ADC_H */