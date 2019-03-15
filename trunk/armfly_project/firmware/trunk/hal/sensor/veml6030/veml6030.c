/** \file

$Id: veml6030.c 40486 2018-10-03 07:58:21Z tangmingfei2013@126.com $

Copyright (c) tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "veml6030.h"

/*******************************************************************************
* EXTENT INCLUDE FILES
*******************************************************************************/
#include "i2c.h"
#include "cmsis_os.h"
#include "boarddiv.c"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define I2C_BOARD        board_I2c_2

static uint16_t commands[4] = { VEML6030_ALS_CONF_DEFAULT | VEML6030_ALS_CONF_PERS_1 |VEML6030_ALS_CONF_IT_200MS | VEML6030_ALS_CONF_SM_x2,
                         315, 
                         285,
                         0 };

static uint16_t als_code = 300;
static uint16_t u16Gain = VEML6030_ALS_CONF_SM_x2;
static const float change_sensitivity = 5;           // in percent
static float calibration_factor = 0.0144;             //0.286;
static float lux;

static I2C_HandleTypeDef hi2c2;
static i2c_t st_i2c_t;
static osThreadId   veml6030TaskHandle = NULL;
static xSemaphoreHandle xSemaphore;

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static bool veml6030_EnableSensor(void);
static uint16_t veml6030_ReadAlsData(void);
static I2C_StatusDef veml6030_SetAlsThreshold(void);
static void veml6030_task(void *pParm);

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
float veml6030_ReadLux(uint16_t *rawLux)
{
    als_code = veml6030_ReadAlsData();
    *rawLux = als_code;
    
    switch (u16Gain)
    {
      case VEML6030_ALS_CONF_SM_x1:
        calibration_factor = 0.0288;
        break;
      case VEML6030_ALS_CONF_SM_x2:
        calibration_factor = 0.0144;
        break;
      case VEML6030_ALS_CONF_SM_x1_8:
        calibration_factor = 0.2304;
        break;
      case VEML6030_ALS_CONF_SM_x1_4:
        calibration_factor = 0.1152;
        break;
    }
    lux = als_code * calibration_factor;

    return lux;
}

void veml6030_Init(void)
{
    board_I2cInfo_t board_I2cInfo_t = s_i2c[I2C_BOARD];

    // Delay some time after sensor is configured
    i2c_InitPort( &board_I2cInfo_t, true, &st_i2c_t);
    veml6030_EnableSensor();
    osDelay(250);
    
    xSemaphore = xSemaphoreCreateMutex();
    xTaskCreate( veml6030_task,     
                 "VEML6030Task",   
                 500,        
                 NULL,
                 4,          
                 NULL );   
}

static void veml6030_task(void *pParm)
{
    (void)pParm;
    while ( true )
    {
         veml6030_test();
         osDelay(1000);
    }
}

void veml6030_test( void )
{
    float lux;
    uint16_t rawLux;
    
    xSemaphoreTake( xSemaphore, portMAX_DELAY);
    lux = veml6030_ReadLux(&rawLux);
    printf("Lux=%.2f, raw_lux=%d\n", lux, rawLux);
    xSemaphoreGive( xSemaphore );
}

/******************************************************************************
* LOCAL FUNCTION IMPLEMENTS
******************************************************************************/
static I2C_StatusDef veml6030_i2c_Read( uint8_t devAddr,uint16_t regAddr,
                                         uint8_t  regAddrLen,uint8_t *pRdBuf,uint16_t bufRdLen)
{
  return i2c_master_sync_read_with_index(&st_i2c_t, devAddr,
                                          regAddr,regAddrLen,
                                          pRdBuf, bufRdLen );
}

static I2C_StatusDef veml6030_i2c_Write(   uint8_t devAddr, uint16_t regAddr, 
                                           uint8_t  regAddrLen,uint8_t *pWrBuf,
                                           uint16_t bufWrLen)
{
   return i2c_master_sync_write_with_index(&st_i2c_t, devAddr,
                                           regAddr, regAddrLen,
                                           pWrBuf, bufWrLen );
}


static uint16_t veml6030_ReadAlsData(void)
{
    uint8_t value[2];
    
    veml6030_i2c_Read( VEML6030_ADDR_ALS, ALS_DATA, 1, value, 2 );
    
    return value[0] | (value[1] << 8);
}

static I2C_StatusDef veml6030_SetAlsThreshold(void)
{
    I2C_StatusDef result;
    uint8_t data[2];
    int threshold_high;
    
    // Set ALS high threshold
    threshold_high = (int)(als_code * (100 + change_sensitivity) / 100);
    
    if (threshold_high > 65535)
    {
      commands[ALS_THDH] = 65535;
    }
    else
    {
      commands[ALS_THDH] = threshold_high;
    }

    data[0] = (uint8_t)(commands[ALS_THDH] & 0xFF);
    data[1] = (uint8_t)((commands[ALS_THDH] & 0xFF00) >> 8);
    result = veml6030_i2c_Write(VEML6030_ADDR_ALS, ALS_THDH, 1, data, 2);
   
    // Set ALS low threshold
    commands[ALS_THDL] = (uint16_t)(als_code * (100 - change_sensitivity) / 100);
    data[0] = (uint8_t)(commands[ALS_THDL] & 0xFF);
    data[1] = (uint8_t)((commands[ALS_THDL] & 0xFF00) >> 8);
    result = veml6030_i2c_Write(VEML6030_ADDR_ALS, ALS_THDL, 1, data, 2);  
    
    return result;
}

static bool veml6030_disable_interrupt(void)
{
    I2C_StatusDef result;
    uint8_t data[2];

    commands[ALS_CONF] &= ~VEML6030_ALS_CONF_INT_EN;
    data[0] = (uint8_t)(commands[ALS_CONF] & 0xFF);
    data[1] = (uint8_t)((commands[ALS_CONF] & 0xFF00) >> 8);
    result = veml6030_i2c_Write(VEML6030_ADDR_ALS, ALS_CONF, 1, data, 2);

    if (I2C_OK != result)
    {
      return false;
    }

    return true;
}

static bool veml6030_EnableSensor(void)
{
    I2C_StatusDef result;
    uint8_t data[2];

    commands[ALS_CONF] &= ~VEML6030_ALS_CONF_SD;
    data[0] = (uint8_t)(commands[ALS_CONF] & 0xFF);
    data[1] = (uint8_t)((commands[ALS_CONF] & 0xFF00) >> 8);
    result = veml6030_i2c_Write(VEML6030_ADDR_ALS, ALS_CONF, 1, data, 2);

    if (I2C_OK != result)
    {
        return false;
    }

    return true;
}

static bool veml6030_DisableSensor(void)
{
    I2C_StatusDef result;
    uint8_t data[2];

    commands[ALS_CONF] |= VEML6030_ALS_CONF_SD;
    data[0] = (uint8_t)(commands[ALS_CONF] & 0xFF);
    data[1] = (uint8_t)((commands[ALS_CONF] & 0xFF00) >> 8);
    result = veml6030_i2c_Write(VEML6030_ADDR_ALS, ALS_CONF, 1, data, 2);

    if (I2C_OK != result)
    {
        return false;
    }

    return true;
}

static bool veml6030_EnableInterrupt(void)
{
    I2C_StatusDef result;
    uint8_t data[2];

    commands[ALS_CONF] |= VEML6030_ALS_CONF_INT_EN;
    data[0] = (uint8_t)(commands[ALS_CONF] & 0xFF);
    data[1] = (uint8_t)((commands[ALS_CONF] & 0xFF00) >> 8);

    result = veml6030_i2c_Write(VEML6030_ADDR_ALS, ALS_CONF, 1, data, 2);

    if (I2C_OK != result)
    {
        return false;
    }

    return true;
}

static void veml6030_ClearInterrupt(void)
{
    uint8_t value[2];
    // Read ALS_STATUS register to clear interrupt
    veml6030_i2c_Read(VEML6030_ADDR_ALS, ALS_STATUS, 1, value, 2);
}

bool veml6030_SetGain(uint8_t gain)
{
    I2C_StatusDef result;
    uint8_t data[2];

#if 0
    /* shut down first */
    commands[ALS_CONF] |= VEML6030_ALS_CONF_SD;
    data[0] = (uint8_t)(commands[ALS_CONF] & 0xFF);
    data[1] = (uint8_t)((commands[ALS_CONF] & 0xFF00) >> 8);
    result = veml6030_i2c_Write(VEML6030_ADDR_ALS, ALS_CONF, 1, data, 2);

    if (HAL_OK != result)
    {
        return false;
    }
#endif

    switch (gain)
    {
      case 0:
        u16Gain = VEML6030_ALS_CONF_SM_x1;
        break;
      case 1:
        u16Gain = VEML6030_ALS_CONF_SM_x2;
        break;
      case 2:
        u16Gain = VEML6030_ALS_CONF_SM_x1_8;
        break;
      case 3:
        u16Gain = VEML6030_ALS_CONF_SM_x1_4;
        break;
    }

    commands[ALS_CONF] &= ~VEML6030_ALS_CONF_SM_MASK;
    commands[ALS_CONF] |= VEML6030_ALS_CONF_SD;
    commands[ALS_CONF] |= u16Gain;
    data[0] = (uint8_t)(commands[ALS_CONF] & 0xFF);
    data[1] = (uint8_t)((commands[ALS_CONF] & 0xFF00) >> 8);
    result = veml6030_i2c_Write(VEML6030_ADDR_ALS, ALS_CONF, 1, data, 2 );

    if (I2C_OK != result)
    {
       return false;
    }

    /* power on */
    commands[ALS_CONF] &= ~VEML6030_ALS_CONF_SD;
    data[0] = (uint8_t)(commands[ALS_CONF] & 0xFF);
    data[1] = (uint8_t)((commands[ALS_CONF] & 0xFF00) >> 8);
    result = veml6030_i2c_Write(VEML6030_ADDR_ALS, ALS_CONF, 1, data, 2);

    if (I2C_OK != result)
    {
        return false;
    }

    return true;
}

/* End of this file */
