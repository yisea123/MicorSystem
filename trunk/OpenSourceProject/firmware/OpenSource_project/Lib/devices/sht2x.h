/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmingfei2013@126.com
  *                                      All Rights Reserved
  * @file    SHT2X.c
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
#ifndef __SHT2X_H
#define __SHT2X_H

/* Private typedef -----------------------------------------------------------*/
typedef enum sht2xResolution_t
{
  SHT2x_RES_12_14BIT       = 0x00, // RH=12bit, T=14bit
  SHT2x_RES_8_12BIT        = 0x01, // RH= 8bit, T=12bit
  SHT2x_RES_10_13BIT       = 0x80, // RH=10bit, T=13bit
  SHT2x_RES_11_11BIT       = 0x81, // RH=11bit, T=11bit
  SHT2x_RES_MASK           = 0x81  // Mask for res. bits (7,0) in user reg.
} sht2xResolution_t;

typedef enum sht2xStatusCode {
  SHT2x_STATUS_OK                = 0x00,
  SHT2x_STATUS_VALID_DATA        = 0x01,
  SHT2x_STATUS_NO_CHANGE         = 0x02,
  SHT2x_STATUS_ABORTED           = 0x03,
  SHT2x_STATUS_BUSY              = 0x04,
  SHT2x_STATUS_SUSPEND           = 0x05,
  SHT2x_STATUS_ERR_IO            = 0x06,
  SHT2x_STATUS_ERR_BAD_DATA      = 0x07,
  SHT2x_STATUS_ERR_TIMEOUT       = 0x08
}sht2xStatusCode;

// sensor command
typedef enum{
  TRIG_T_MEASUREMENT_HM    = 0xE3, // command trig. temp meas. hold master
  TRIG_RH_MEASUREMENT_HM   = 0xE5, // command trig. humidity meas. hold master
  TRIG_T_MEASUREMENT_POLL  = 0xF3, // command trig. temp meas. no hold master
  TRIG_RH_MEASUREMENT_POLL = 0xF5, // command trig. humidity meas. no hold master
  USER_REG_W               = 0xE6, // command writing user register
  USER_REG_R               = 0xE7, // command reading user register
  SOFT_RESET               = 0xFE  // command soft reset
}sht2xCommand_t;

typedef enum {
  SHT2x_EOB_ON             = 0x40, // end of battery
  SHT2x_EOB_MASK           = 0x40, // Mask for EOB bit(6) in user reg.
} sht2xEob_t;

typedef enum {
  SHT2x_HEATER_ON          = 0x04, // heater on
  SHT2x_HEATER_OFF         = 0x00, // heater off
  SHT2x_HEATER_MASK        = 0x04, // Mask for Heater bit(2) in user reg.
} etSHT2xHeater;

// measurement signal selection
typedef enum{
  HUMIDITY,
  TEMP
}etSHT2xMeasureType;

typedef enum{
  I2C_ADR_W                = 128,   // sensor I2C address + write bit
  I2C_ADR_R                = 129    // sensor I2C address + read bit
}etI2cHeader;

uint8_t sht2xdrv_GetTemp( int32_t *pMeasurand );
uint8_t sht2xdrv_GetRH( int32_t *pMeasurand );
uint8_t sht2xdrv_ResetSht2x( void );
uint8_t sht2xdrv_GetBatteryStatus(void);
uint8_t sht2xdrv_GetHeaterStatus(void);
uint8_t sht2xdrv_GetResolution(sht2xResolution_t *pResolution);
void sht2xdrv_Init( void );

void SHT2X_test( void );

#endif /* __SHT2X_H */
