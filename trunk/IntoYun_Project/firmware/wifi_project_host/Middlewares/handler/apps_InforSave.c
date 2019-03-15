/** \file

$Id: apps_InforSave.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

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
#include "Includes.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
systemConfig_struct st_systemConfig_struct;

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static uint8_t Sys_ParmaterLength_Checked( uint8_t *str,  uint8_t length);


/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void sys_InformationSaved( void )
{
    W25QXX_Write( 0, (uint8_t*)&st_systemConfig_struct, sizeof(systemConfig_struct));
}

void Sys_InformationInit( void )
{
    W25QXX_Read( 0, (uint8_t*)&st_systemConfig_struct, sizeof(systemConfig_struct));
}

void sys_InformationConfig( uint8_t *buff, uint8_t length )
{
  uint8_t type;
  uint8_t *pBuff;

  type = buff[0];
  switch( type )
  {
  case PROJECT_ID:
   if( length != 17 )
       return;

   memset(st_systemConfig_struct.productID, 
          0, 
          sizeof(st_systemConfig_struct.productID));
   pBuff = st_systemConfig_struct.productID;
   memcpy(pBuff, buff+1, length-1);
   break;
   
  case PROJECT_SECRET:
  if( length != 33 )
      return;

   memset(st_systemConfig_struct.productSecret, 
          0, 
          sizeof(st_systemConfig_struct.productSecret));
   pBuff = st_systemConfig_struct.productSecret;
   memcpy(pBuff, buff+1, length-1);
   break;
   
  case DEVICES_ID:
   if( length != 25 ) 
       return;

   memset(st_systemConfig_struct.deviceID, 
          0, 
          sizeof(st_systemConfig_struct.deviceID));
   pBuff = st_systemConfig_struct.deviceID;
   memcpy(pBuff, buff+1, length-1); 
   break;
   
  case WIFI_SSID:
   if(length > 32 )
     return;

   memset(st_systemConfig_struct.wifissid, 
          0, 
          sizeof(st_systemConfig_struct.wifissid));
   pBuff = st_systemConfig_struct.wifissid;
   memcpy(pBuff, buff+1, length-1);
   break;
   
  case WIFI_SECRET:
   if(length > 32 )
     return;

   memset(st_systemConfig_struct.wifiPwd, 
          0, 
          sizeof(st_systemConfig_struct.wifiPwd));
   pBuff = st_systemConfig_struct.wifiPwd;
   memcpy(pBuff, buff+1, length-1);
   break;
   
   default:
   return;
  }
  sys_InformationSaved();
}

void Sys_InformationRead(  uint8_t type, uint8_t *buff, uint8_t *length)
{
  uint8_t *pBuff;
  uint8_t u8_length = 0;
  uint8_t u8_calLenght = 0;

  buff[0] = type;
  switch( type )
  {
  case PROJECT_ID:
   pBuff = st_systemConfig_struct.productID;
   u8_calLenght = sizeof(st_systemConfig_struct.productID);
   break;
   
  case PROJECT_SECRET:
   pBuff = st_systemConfig_struct.productSecret;
   u8_calLenght = sizeof(st_systemConfig_struct.productSecret);
   break;
   
  case DEVICES_ID:
   pBuff = st_systemConfig_struct.deviceID;
   u8_calLenght = sizeof(st_systemConfig_struct.deviceID);
   break;
   
  case WIFI_SSID:
   pBuff = st_systemConfig_struct.wifissid;
   u8_calLenght = sizeof(st_systemConfig_struct.wifissid);
   break;
   
  case WIFI_SECRET:
   pBuff = st_systemConfig_struct.wifiPwd;
   u8_calLenght = sizeof(st_systemConfig_struct.wifiPwd);
   break;
   
  default:
   buff[1] = ERROR_UN_RECONGNITION >>8;
   buff[2] = ERROR_UN_RECONGNITION;
   *length = 3;
   return;
  }

  if(pBuff[0] == 0 )
  {
     buff[1] = ERROR_PARAMATER_NOT_ESIXIT >>8;
     buff[2] = ERROR_PARAMATER_NOT_ESIXIT;
     *length = 3;
  }
  else
  {  
     u8_length = Sys_ParmaterLength_Checked( pBuff , u8_calLenght);
     memcpy(buff+1, pBuff,u8_length);
     *length = u8_length+1;
  }   
}

/* Private functions ---------------------------------------------------------*/
static uint8_t Sys_ParmaterLength_Checked( uint8_t *str,  uint8_t length)
{
  uint8_t lenght = 0;

  for( uint8_t i = 0; i < length; i++ )
  {
     if(str[i] != 0)
     {
       lenght++;
     }
     else
       break;
  }

  return lenght;
}

/* End fo this file */
