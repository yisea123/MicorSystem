/*******************************************************************************
** File name:	 ADC.c
** Created by:	 Mingfei Tang		
** Created date: 2016/1/20		
** Version:	  V1.00			
** Descriptions:
**
**------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*******************************************************************************/
#include "includes.h"

__IO uint16_t ADC1ConvertedValue = 0;

void ADC_GPIOInit( void )
{
    RCC_AHBPeriphClockCmd(  RCC_AHBPeriph_DMA1|RCC_AHBPeriph_DMA2,  ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1| \
                            RCC_APB2Periph_AFIO, ENABLE );    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);    
}

void ADC_DMAInit( void )
{
    DMA_InitTypeDef DMA_InitStructure;
    ADC_InitTypeDef   ADC_InitStructure;
   
    ADC_GPIOInit();
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC1ConvertedValue;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);  
    DMA_Cmd(DMA1_Channel1, ENABLE); 

    /* ADC1 configuration */
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_TempSensorVrefintCmd( ENABLE );
    ADC_Init(ADC1, &ADC_InitStructure);  
}

void ADC_InitModel( INT8U Cehoos_Ch )
{
    ADC_DMAInit();
    
    ADC_RegularChannelConfig(ADC1, Cehoos_Ch, 1, ADC_SampleTime_55Cycles5);
    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);   
}

INT16U ADC_GetADCValue( INT8U Cehoos_Ch )
{
    FP32   f32_SumADC=0;
    INT16U  u16_adcResult = 0;
    INT32U  AdcData = 0;
    INT8U i;
 
    ADC_InitModel( Cehoos_Ch );
    for(  i=10;i>0;i--)
    {
        AdcData = ADC1ConvertedValue;
        f32_SumADC += AdcData;
    }
    
    u16_adcResult = ( INT16U)(f32_SumADC * 0.1);
    
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); 
   
    return u16_adcResult;
}

/*
 * Sample 12 times and discard 4 of Max and Min.
 * - do the sample in this routine
 */
INT16U ADC_GetAverageRaw( INT16U data )
{
   INT8U u8_i;
   INT32U temp, max1, max2, min1, min2, sum;

   sum = 0L;
   min1 = 0xFFFFFFFF;
   max1 = 0L;
   min2 = 0xFFFFFFFF;
   max2 = 0L;
	
   for ( u8_i=0; u8_i<12; u8_i++ )
   {
      temp = data;
		
      if ( temp > max1 )
      {
         max2 = max1;
         max1 = temp;
      }
      else {
          if ( temp > max2 ) {
                  max2 = temp;
          }
      }
		
      if ( temp < min1 )
      {
         min2 = min1;
         min1 = temp;
      }
      else {
	  if ( temp < min2 ) {
         	min2 = temp;
      	  }
      }
      sum += temp;
   }
    temp = (sum - max2 - max1 - min2 - min1)>>3;
	
    return ( (INT16U)temp );
}

/* EOF */