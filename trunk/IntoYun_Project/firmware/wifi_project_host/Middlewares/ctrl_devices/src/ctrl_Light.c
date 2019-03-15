/**
  ******************************************************************************
  * @file    Src/user/Ctrl_Light.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/05/05
  * @brief   light control interface for rs485 
  * @documents 
  ******************************************************************************
  */
/* Includes -------------------------------------------------------------------*/
#include "ctrl_Def.h"
#include "ctrl_Light.h"
#include "Util.h"
#include "platform_def.h"

/* Private typedef ------------------------------------------------------------*/
/* Private define -------------------------------------------------------------*/
#define LIGHT_RETRY                         10
#define RETRY                               3  
/* Private macro --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
CtrlLight_lib st_CtrlLight_lib;

/* Private function prototypes ------------------------------------------------*/
static CTRL_RESULT_ENUM vLight_CheckUIDAction(  CtrlLight_typedef *pCtrlLight );
static void vLight_ContrlCmd( CtrlLight_typedef *pCtrlLight);


void vLight_CtrlReset( CtrL_typedef *pCtrL_typedef )
{
    pCtrL_typedef->step = 0;
    pCtrL_typedef->retry = 0;  
    pCtrL_typedef->addres = NULL_ADDR;
}

void vLight_Init( void )
{
    CtrlLight_typedef *pCtrlLight_typedef;
    uint8_t i;

    for( i = 0; i < MAX_LIGHT_SUPPORT; i++ )
    {
       pCtrlLight_typedef = &st_CtrlLight_lib.st_LightCtr[i]; 
       memset( pCtrlLight_typedef->uid, 0, 5);
       pCtrlLight_typedef->uid[0] = 0x1a;
       pCtrlLight_typedef->uid[4] = i+1;
    }
}

void vLight_ContrlTurnOff( CtrlLight_typedef *pCtrlLight )
{
    pCtrlLight->lightCtrlWhiteCmd.mode = LIGHT_ONLY_OFF;
    pCtrlLight->lightCtrlYellowCmd.mode = LIGHT_ONLY_OFF;

    pCtrlLight->lightCtrlWhiteCmd.b_ctrlres = LIGHT_CTRL_ENABLE;
    pCtrlLight->lightCtrlYellowCmd.b_ctrlres = LIGHT_CTRL_ENABLE;

    pCtrlLight->lightCtrlWhiteCmd.luminance = 0;
    pCtrlLight->lightCtrlYellowCmd.luminance = 0;

    vLight_ContrlCmd( pCtrlLight );
}

void vLight_ContrlTurnOn( CtrlLight_typedef *pCtrlLight )
{
    pCtrlLight->lightCtrlWhiteCmd.mode = LIGHT_DIMMING;
    pCtrlLight->lightCtrlYellowCmd.mode = LIGHT_DIMMING;

    pCtrlLight->lightCtrlWhiteCmd.b_ctrlres = LIGHT_CTRL_ENABLE;
    pCtrlLight->lightCtrlYellowCmd.b_ctrlres = LIGHT_CTRL_ENABLE;

    //pCtrlLight->lightCtrlWhiteCmd.luminance = LIGHT_DEFAULT_LUM;
    //pCtrlLight->lightCtrlYellowCmd.luminance = LIGHT_DEFAULT_LUM;

    vLight_ContrlCmd( pCtrlLight );
}

void vLight_CheckStatus( CtrlLight_typedef *pCtrlLight )
{
    uint8_t buff[16];
    uint8_t length = 0;

    for( uint8_t j = 0; j < 5; j++ )
    {
        buff[length++] = pCtrlLight->uid[j];
    }

    buff[length++] = LIGHT_CHECK_STATUS;
    buff[length++] = LIGHT_CHECK_STATUS;
    buff[length++] = LIGHT_CHECK_STATUS;

    buff[length++] = LIGHT_END_PACKET;

    st_CtrlLight_lib.pf_SendPut( buff , length );
}

bool vLight_ScanUID( void )
{
    CTRL_RESULT_ENUM res;
    uint8_t cnt;
    CtrlLight_typedef *pCtrlLight_typedef;

    if( st_CtrlLight_lib.scanActionCnt < MAX_LIGHT_SUPPORT)
    {
        cnt = st_CtrlLight_lib.scanActionCnt;
        pCtrlLight_typedef = &st_CtrlLight_lib.st_LightCtr[cnt]; 
        res = vLight_CheckUIDAction( pCtrlLight_typedef );
        if( res == CTRL_OK || res == CTRL_FAIL)
        {
            st_CtrlLight_lib.scanActionCnt++;
            if(res == CTRL_OK)
              st_CtrlLight_lib.totalLightEnable++;
        }
    }

    return true;
}

CTRL_RESULT_ENUM eLight_CtrlInterface( CtrL_typedef *pCtrL_typedef )
{
    CtrlLight_typedef *pCtrlLight_typedef;
    uint8_t index = 0;

    index = pCtrL_typedef->deviceID;
    pCtrlLight_typedef = &st_CtrlLight_lib.st_LightCtr[index];
    
    if( pCtrL_typedef->b_ctrlres[0] )
    {
        /*
          white light
        */
        if(pCtrL_typedef->b_ctrlres[1] == 0)
        {
            pCtrlLight_typedef->lightCtrlWhiteCmd.luminance= LIGHT_DEFAULT_LUM;
        }
        else
        {
            pCtrlLight_typedef->lightCtrlWhiteCmd.luminance= pCtrL_typedef->b_ctrlres[1];
        }

        /*
          yellow light
        */
        if(pCtrL_typedef->b_ctrlres[2] == 0)
        {
            pCtrlLight_typedef->lightCtrlYellowCmd.luminance= LIGHT_DEFAULT_LUM;
        }
        else
        {
            pCtrlLight_typedef->lightCtrlYellowCmd.luminance= pCtrL_typedef->b_ctrlres[2];
        }
        
        vLight_ContrlTurnOn( pCtrlLight_typedef );
    }
    else
    {
        vLight_ContrlTurnOff( pCtrlLight_typedef );
    }
    
    if(pCtrL_typedef->retry < LIGHT_RETRY)
    {
        pCtrL_typedef->retry ++;
    }
    else
    {
        return CTRL_OK;
    }    

    return CTRL_IDLE;
}

static CTRL_RESULT_ENUM vLight_CheckUIDAction(  CtrlLight_typedef *pCtrlLight )
{
    bool res;
    uint8_t UID[5];

    if( *st_CtrlLight_lib.length >= 8 )
    {
        //Check crc
        *st_CtrlLight_lib.length = 0;
        memcpy( UID , st_CtrlLight_lib.datapacket, 5);
        res = Utils_CharArrayCmp( UID,pCtrlLight->uid, 5);
        if( res )
        {
            pCtrlLight->enable = true;
            return CTRL_OK;
        }
    }
    else
    { 
        if( pCtrlLight->retry > RETRY)
        {
            pCtrlLight->retry = 0;
            return CTRL_FAIL;
        }
        
        vLight_CheckStatus( pCtrlLight );
        pCtrlLight->retry++;    
    }

    return CTRL_IDLE;
}

static void vLight_ContrlCmd( CtrlLight_typedef *pCtrlLight)
{
    uint8_t buff[16];
    uint8_t length = 0;

    for( uint8_t j = 0; j < 5; j++ )
    {
      buff[length++] = pCtrlLight->uid[j];
    }

    buff[length++] = pCtrlLight->lightCtrlWhiteCmd.mode;
    buff[length++] = pCtrlLight->lightCtrlWhiteCmd.luminance;
    buff[length++] = pCtrlLight->lightCtrlWhiteCmd.b_ctrlres;

    buff[length++] = pCtrlLight->lightCtrlYellowCmd.mode;
    buff[length++] = pCtrlLight->lightCtrlYellowCmd.luminance;
    buff[length++] = pCtrlLight->lightCtrlYellowCmd.b_ctrlres;

    buff[length++] = LIGHT_END_PACKET;

    st_CtrlLight_lib.pf_SendPut( buff , length );
}

/* End of this file */

