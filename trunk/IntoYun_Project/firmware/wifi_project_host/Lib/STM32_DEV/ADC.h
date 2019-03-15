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
void ADC_InitModel( uint8_t Choose_Ch );
uint16_t ADC_GetADCValue( uint8_t Cehoos_Ch );
void ADC_AddADCValue( void  );
uint16_t ADC_GetAverageRaw( uint16_t data );
uint16_t ADC_GetAverageRawBuf( uint16_t *pu16_buf );

#endif       /* __ADC_H */