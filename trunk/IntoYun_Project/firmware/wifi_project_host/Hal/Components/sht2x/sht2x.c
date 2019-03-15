/** \file

$Id: sht2x.c 40486 2018-08-12 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "I2C.h"
#include "Stm32hal.h"

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "sht2x.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define I2C_ADDRESS        (0x40 << 1)
#define POLY               0x131;  //P(x)=x^8+x^5+x^4+1 = 100110001

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void i2c_Delay(uint16_t value );
static uint8_t sht2xdrv_CheckCrc(uint8_t data[], uint8_t nbrOfBytes, uint8_t checksum);
static uint8_t sht2xdrv_CheckOk(void);
static int32_t sht2xdrv_CalcTemperatureC(uint16_t u16sT);
static int32_t sht2xdrv_CalcRH(uint16_t u16sRH);

static void i2c_Delay(uint16_t value )
{
    uint16_t i;
    for (i = 0; i < value; i++);
}

static uint8_t sht2xdrv_CheckCrc(uint8_t data[], uint8_t nbrOfBytes, uint8_t checksum)
{
    uint8_t res = 0;
    uint8_t crc = 0;
    uint8_t byteCtr;
    
    //calculates 8-Bit checksum with given polynomial
    for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
    {
      crc ^= (data[byteCtr]);
      for (uint8_t bit = 8; bit > 0; --bit)
      {
        if (crc & 0x80)
        {
          crc = (crc << 1) ^ POLY;
        }
        else
        {
          crc = (crc << 1);
        }
      }
    }

    if (crc != checksum)
    {
      res = 1;
    }

    return res;
}

static uint8_t sht2xdrv_CheckOk(void)
{
    if (i2c_CheckDevice( I2C_ADDRESS ) == 0)
    {
         /* sensor is online*/
            return 1;
    }
    else
    {
          /* fail: send stop */
            i2c_Stop();
            return 0;
    }
}

static uint8_t sht2xdrv_ReadUserRegister( uint8_t *pRegisterValue )
{
    uint8_t ret = SHT2x_STATUS_OK;
    uint8_t cmd = USER_REG_R;
    i2c_Start();
    
    i2c_SendByte( I2C_ADDRESS | I2C_WR );  // Device address 
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
    i2c_SendByte( cmd);
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
    //Read 
    i2c_Start();
    i2c_SendByte(I2C_ADDRESS | I2C_RD);
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    } 
    
    *pRegisterValue = i2c_ReadByte();
    i2c_NAck();
    
    i2c_Stop();
    return ret;
    
cmd_fail:    
    i2c_Stop();
    ret = SHT2x_STATUS_ERR_BAD_DATA;
    
    return ret;
}

static int32_t sht2xdrv_CalcTemperatureC(uint16_t u16sT)
{
  int32_t temperatureC;       // variable for result

  u16sT &= ~0x0003;           // clear bits [1..0] (status bits)

  /*
     * Formula T = -46.85 + 175.72 * ST / 2^16 from data sheet 6.2,
     * optimized for integer fixed point (3 digits) arithmetic
  */

  temperatureC = (((uint32_t)17572 * u16sT) >> 16) - 4685;

  return (int32_t)temperatureC;
}

static int32_t sht2xdrv_CalcRH(uint16_t u16sRH)
{
  uint32_t humidityRH;       // variable for result

  u16sRH &= ~0x0003;          // clear bits [1..0] (status bits)

  /*
     * Formula RH = -6 + 125 * SRH / 2^16 from data sheet 6.1,
     * optimized for integer fixed point (3 digits) arithmetic
  */

  humidityRH = (((uint32_t)12500 * u16sRH) >> 16) - 600;

  return (int32_t)humidityRH;
}

uint8_t  sht2xdrv_GetTemp( int32_t *pMeasurand )
{
    uint8_t ret = SHT2x_STATUS_OK;
    uint8_t checksum;                   //checksum
    uint16_t rawdata;
    uint8_t cmd = TRIG_T_MEASUREMENT_HM;
    uint8_t data[3] = {0, 0, 0};        //data array for checksum v
    
    i2c_Start();
    i2c_SendByte( I2C_ADDRESS | I2C_WR );  // Device address 
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
    i2c_Delay( 100 );
    i2c_SendByte( cmd);
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
    //Read 
    i2c_Start();
    i2c_SendByte(I2C_ADDRESS | I2C_RD);
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
    HAL_Delay( 70 );
    data[0] = i2c_ReadByte();
    i2c_Ack();	
    data[1] = i2c_ReadByte();
    i2c_Ack();	
    data[2] = i2c_ReadByte();
    i2c_NAck();
  
    i2c_Stop();
    
    rawdata = ((uint16_t)data[0] << 8) | data[1];
    checksum = data[2];

    ret = sht2xdrv_CheckCrc(data, 2, checksum);   
    if (ret != SHT2x_STATUS_OK)
    {
        return ret;
    }
    *pMeasurand = sht2xdrv_CalcTemperatureC(rawdata);
    
cmd_fail: 
    i2c_Stop();
    
    return ret;
}

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
uint8_t  sht2xdrv_GetRH( int32_t *pMeasurand )
{
    uint8_t ret = SHT2x_STATUS_OK;
    uint8_t checksum;   //checksum
    uint16_t rawdata;
    uint8_t cmd = TRIG_RH_MEASUREMENT_POLL;
    uint8_t data[3] = {0, 0, 0}; //data array for checksum v
    
    i2c_Start();
    i2c_SendByte( I2C_ADDRESS | I2C_WR );  // Device address 
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
    i2c_SendByte( cmd);
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
    //Read 
    i2c_Start();
    HAL_Delay( 100 );
    i2c_SendByte(I2C_ADDRESS | I2C_RD);
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
    HAL_Delay( 100 );
    data[0] = i2c_ReadByte();
    i2c_Ack();	
    data[1] = i2c_ReadByte();
    i2c_Ack();	
    data[2] = i2c_ReadByte();
    i2c_NAck();
     
    i2c_Stop();
    
    rawdata = ((uint16_t)data[0] << 8) | data[1];
    checksum = data[2];

    ret = sht2xdrv_CheckCrc(data, 2, checksum);   
    if (ret != SHT2x_STATUS_OK)
    {
        return ret;
    }
    *pMeasurand = sht2xdrv_CalcRH(rawdata);
    
cmd_fail: 
    i2c_Stop();
    
    return ret;
}

uint8_t  sht2xdrv_ResetSht2x( void )
{
    uint8_t ret = SHT2x_STATUS_OK;
    uint8_t cmd = SOFT_RESET;
    
    i2c_Start();
    i2c_SendByte( I2C_ADDRESS | I2C_WR );  // Device address 
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
    i2c_SendByte( cmd);
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;
    }
    
cmd_fail: 
    i2c_Stop();
    ret = SHT2x_STATUS_ERR_TIMEOUT;
    
    return ret;
}

uint8_t  sht2xdrv_GetBatteryStatus(void)
{
  uint8_t reg;
  uint8_t error = SHT2x_STATUS_OK;

  error = sht2xdrv_ReadUserRegister(&reg);

  if (error != SHT2x_STATUS_OK)
  {
    return error;
  }

  return (reg & 0x40);
}

uint8_t sht2xdrv_GetHeaterStatus(void)
{
  uint8_t reg;
  uint8_t error = SHT2x_STATUS_OK;

  error = sht2xdrv_ReadUserRegister(&reg);

  if (error != SHT2x_STATUS_OK)
  {
    return error;
  }

  return (reg & 0x04);
}

uint8_t sht2xdrv_GetResolution(sht2xResolution_t *pResolution)
{
    uint8_t error = SHT2x_STATUS_OK;
    uint8_t reg = 0;

    error = sht2xdrv_ReadUserRegister(&reg);
    if (error != SHT2x_STATUS_OK)
    {
        return error;
    }

    *pResolution = (sht2xResolution_t)(reg & SHT2x_RES_MASK);
    return error;
}

void sht2xdrv_Init( void )
{
    sht2xResolution_t sht2xResolutionvalue;
    
    sht2xdrv_CheckOk();
    sht2xdrv_GetBatteryStatus();   
    sht2xdrv_GetResolution( &sht2xResolutionvalue );
}

static int32_t s_TempData; 
static int32_t s_RhData; 
void SHT2X_test( void )
{  
    sht2xdrv_GetTemp( &s_TempData );
    sht2xdrv_GetRH( &s_RhData );
}

/* End of this file */