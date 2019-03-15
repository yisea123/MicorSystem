/** \file

$Id: hts221.c 40486 2018-10-20 18:58:21Z tangmingfei2013@126.com $

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
#include "hts221.h"

/*******************************************************************************
* EXTENT INCLUDE FILES
*******************************************************************************/
#include "i2c.h"
#include "cmsis_os.h"
#include "boarddiv.c"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define I2C_BOARD       board_I2c_2
#define _address        HTS221_ADDRESS

static uint8_t _h0_rH, _h1_rH;
static uint16_t  _T0_degC, _T1_degC;
static uint16_t  _H0_T0, _H1_T0;
static uint16_t  _T0_OUT, _T1_OUT;

static I2C_HandleTypeDef hi2c2;
static i2c_t st_i2c_t;
static xSemaphoreHandle xSemaphore;

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static bool readRegister(uint8_t slaveAddress, uint8_t regToRead, uint8_t *retval);
static bool writeRegister(uint8_t slaveAddress, uint8_t regToWrite, uint8_t dataToWrite);
static bool hts221_storeCalibration(void);
static bool hts221_activate(void);
static void hts221_task(void *pParm);

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
bool hts221_Init(void)
{
    uint8_t data;
    bool res;
    board_I2cInfo_t board_I2cInfo_t = s_i2c[I2C_BOARD];
    
    xSemaphore = xSemaphoreCreateMutex();
    // Delay some time after sensor is configured
    i2c_InitPort( &board_I2cInfo_t, true, &st_i2c_t);
    res = readRegister(_address, WHO_AM_I, &data);
    if (data == WHO_AM_I_RETURN && res)
    {
        if (hts221_activate())
        {
            res =  hts221_storeCalibration();
            if( res )
            {
                xTaskCreate( hts221_task,     
                             "ths221Task",   
                             500,        
                             NULL,
                             5,          
                             NULL );             
            }
        }
    }
    
    return false;
}

static void hts221_task(void *pParm)
{
  (void)pParm;
  while ( true )
  {
       hts221_test();
       osDelay(1000);
  }
}

bool hts221_readHumidity( double * _humidity)
{
    bool res = false;
    uint8_t data   = 0;
    uint16_t h_out = 0;
    double h_temp  = 0.0;
    double hum     = 0.0;

    res = readRegister(_address, STATUS_REG, &data);
    if (data & HUMIDITY_READY && res ) 
    {
        res = readRegister(_address, HUMIDITY_H_REG ,&data );
        h_out = data << 8;  // MSB
        res = readRegister(_address, HUMIDITY_L_REG ,&data);
        h_out |= data;      // LSB

        // Decode Humidity
        hum = ((int16_t)(_h1_rH) - (int16_t)(_h0_rH))/2.0;  // remove x2 multiple

        // Calculate humidity in decimal of grade centigrades i.e. 15.0 = 150.
        h_temp = (double)(((int16_t)h_out - (int16_t)_H0_T0) * hum) / 
	         (double)((int16_t)_H1_T0 - (int16_t)_H0_T0);
        hum    = (double)((int16_t)_h0_rH) / 2.0; // remove x2 multiple
        
        *_humidity = (hum + h_temp); // provide signed % measurement unit
    }
    
    return res;
}



bool hts221_readTemperature(double *_temperature )
{
    bool res = false;
    uint8_t data   = 0;
    uint16_t t_out = 0;
    double t_temp  = 0.0;
    double deg     = 0.0;

    res = readRegister(_address, STATUS_REG, &data);
    if (data & TEMPERATURE_READY && res ) 
    {
        res = readRegister(_address, TEMP_H_REG ,&data);
        t_out = data  << 8; // MSB
        res = readRegister(_address, TEMP_L_REG ,&data);
        t_out |= data;      // LSB

        // Decode Temperature
        deg    = (double)((int16_t)(_T1_degC) - (int16_t)(_T0_degC))/8.0; // remove x8 multiple

        // Calculate Temperature in decimal of grade centigrades i.e. 15.0 = 150.
        t_temp = (double)(((int16_t)t_out - (int16_t)_T0_OUT) * deg) / 
	         (double)((int16_t)_T1_OUT - (int16_t)_T0_OUT);
        deg    = (double)((int16_t)_T0_degC) / 8.0;     // remove x8 multiple
        *_temperature = deg + t_temp;   // provide signed celsius measurement unit
    }
    
    return res;
}

void hts221_test( void )
{
    double temperature;
    double humidity;
    
    xSemaphoreTake( xSemaphore, portMAX_DELAY);
    hts221_readHumidity( &humidity );
    hts221_readTemperature( &temperature );
    printf("Temp/Humid: %5.2f/%5.2f\n\r", temperature, humidity);
    xSemaphoreGive( xSemaphore );
}

bool hts221_activate(void)
{
    uint8_t data;
    bool res = false;

    res = readRegister(_address, CTRL_REG1, &data);
    if( res )
    {
      data |= POWER_UP;
      data |= ODR0_SET;    
      res = writeRegister(_address, CTRL_REG1, data);
    }

    return res;
}

bool hts221_deactivate(void)
{
    uint8_t data;
    bool res = false;

    res = readRegister(_address, CTRL_REG1, &data);
    if( res )
    {
      data &= ~POWER_UP;
      res = writeRegister(_address, CTRL_REG1, data);
    }
    
    return res;
}

bool hts221_bduActivate(void)
{
    uint8_t data;
    bool res = false;

    res = readRegister(_address, CTRL_REG1, &data);
    if( res )
    {
        data |= BDU_SET;
        return writeRegister(_address, CTRL_REG1, data);
    }

    return res;
}


bool hts221_bduDeactivate(void)
{
    uint8_t data;
    bool res = false;

    res = readRegister(_address, CTRL_REG1, &data);
    if( res )
    {
        data &= ~BDU_SET;
        return writeRegister(_address, CTRL_REG1, data);
    }
    
    return res;
}

/******************************************************************************
* LOCAL FUNCTION IMPLEMENTS
******************************************************************************/
static bool hts221_storeCalibration(void)
{
    uint8_t data;
    uint16_t tmp;
    bool res = false;

    for (int reg=CALIB_START; reg<=CALIB_END; reg++) 
    {
        if ((reg!=CALIB_START+8) && (reg!=CALIB_START+9) && (reg!=CALIB_START+4)) 
        {
            res = readRegister(_address, reg, &data);
            if( res )
            {
                switch ( reg ) 
                {
                    case CALIB_START:
                        _h0_rH = data;
                        break;
                        
                    case CALIB_START+1:
                        _h1_rH = data;
                        break;
                        
                    case CALIB_START+2:
                        _T0_degC = data;
                        break;
                        
                    case CALIB_START+3:
                        _T1_degC = data;
                        break;

                    case CALIB_START+5:
                        tmp = _T0_degC;
                        _T0_degC = (data&0x3)<<8;
                        _T0_degC |= tmp;

                        tmp = _T1_degC;
                        _T1_degC = ((data&0xC)>>2)<<8;
                        _T1_degC |= tmp;
                        break;
                        
                    case CALIB_START+6:
                      _H0_T0 = data;
                      break;
                    
                    case CALIB_START+7:
                      _H0_T0 |= data<<8;
                      break;
                    
                    case CALIB_START+0xA:
                      _H1_T0 = data;
                      break;
                    
                    case CALIB_START+0xB:
                      _H1_T0 |= data <<8;
                      break;
                    
                    case CALIB_START+0xC:
                      _T0_OUT = data;
                      break;
                    
                    case CALIB_START+0xD:
                      _T0_OUT |= data << 8;
                      break;
                    
                    case CALIB_START+0xE:
                      _T1_OUT = data;
                      break;
                    
                    case CALIB_START+0xF:
                      _T1_OUT |= data << 8;
                      break;


                    case CALIB_START+8:
                    case CALIB_START+9:
                    case CALIB_START+4:
                    //DO NOTHING
                    break;

                    // to cover any possible error
                    default:
                        return false;
                } /* switch */
            }
        } /* if */
    }  /* for */
    
    return true;
}

// Read a single uint8_t from addressToRead and return it as a uint8_t
// Abbo: 11/01/18: re-written with the STM32 I2C call methods 
static bool readRegister(uint8_t slaveAddress, uint8_t regToRead, uint8_t *retval)
{
    I2C_StatusDef res;
    
    res = i2c_master_sync_read_with_index(&st_i2c_t, slaveAddress,
                                          regToRead,I2C_MEMADD_SIZE_8BIT,
                                          retval, 1 );  
   if( res != I2C_OK)  
     return false;
     
    return true;
}

// Writes a single uint8_t (dataToWrite) into regToWrite
// Abbo: 11/01/18: re-written with the STM32 I2C call methods 
static bool writeRegister(uint8_t slaveAddress, uint8_t regToWrite, uint8_t dataToWrite)
{ 
   I2C_StatusDef res;
   
   res =  i2c_master_sync_write_with_index(&st_i2c_t, slaveAddress,
                                           regToWrite, I2C_MEMADD_SIZE_8BIT,
                                           &dataToWrite, 1 ); 
   if( res != I2C_OK)  
     return false;
     
    return true;
}

/* End of this file */
