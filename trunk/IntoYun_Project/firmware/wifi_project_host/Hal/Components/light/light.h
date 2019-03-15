/** \file

$Id: light.h 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __LIGHT_H
#define __LIGHT_H

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/

#include "platform_def.h"

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 
#define MAX_LIGHT_SUPPORT                     12
#define LIGHT_DEFAULT_LUM                     100

typedef enum
{
    LIGHT_ONLY_OFF = 0,
    LIGHT_ONLY_ON = 1,
    LIGHT_OFF_ON = 2,
    LIGHT_BRIGHT = 3,
    LIGHT_DARK = 4,
    LIGHT_DIMMING = 0XFF,
}LIGHT_CTRL_MODE_ENUM;

typedef enum
{
    LIGHT_CTRL_DISABLE = 0,
    LIGHT_CTRL_ENABLE = 1,
    LIGHT_CHECK_STATUS = 0x86,
    LIGHT_END_PACKET = 0x0f,
}LIGHT_CTRL_ENUM;

typedef struct
{
    uint8_t mode;       //����ģʽ: 0x00��ֻ�أ�0x01��ֻ����0xff������
                        //          0x02�����أ�0x03��������0x04������    
    uint8_t luminance;  //���ȣ�0x25~0xf0
    uint8_t CurrentLuminance;
    bool b_ctrlres;     //����ʹ�ܣ�0x01����Ч��0x00����Ч
}LightCmd_typedef;

typedef struct
{
    uint8_t uid[5];
    uint8_t retry;      // try ����
    bool enable;        // uidʹ�ܣ�0x01����Ч��0x00����Ч
    LightCmd_typedef lightCtrlWhiteCmd;
    LightCmd_typedef lightCtrlYellowCmd;
}LightStatus_typedef;

typedef struct
{
    LightStatus_typedef  st_LightCtr[MAX_LIGHT_SUPPORT];
    int totalLightEnable;
    int scanActionCnt;

    uint16_t *length;
    uint8_t *datapacket;
    void (*pf_SendPut)(uint8_t*, uint8_t);  
}CtrlLight_lib;

typedef struct
{
  bool bStatus;  
  uint8_t id;
  uint8_t retry;      // try ����
  uint8_t wLuminance;
  uint8_t yLuminance;
}CtrlLight_typedef;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/  
void vLight_Init( CtrlLight_lib *pCtrlLight );
void vLight_ContrlCmd( CtrlLight_lib *pCtr, int index );  
void vLight_ContrlTurnOff( CtrlLight_lib *pCtr, int index );
void vLight_ContrlTurnOn( CtrlLight_lib *pCtr, int index );
void vLight_CheckStatus( CtrlLight_lib *pCtr, int index );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __LIGHT_H */  