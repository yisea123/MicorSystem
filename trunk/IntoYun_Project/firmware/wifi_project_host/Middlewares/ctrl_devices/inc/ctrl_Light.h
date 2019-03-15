/**
  ******************************************************************************
  * @file    Src/user/Ctr_Light.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/05/09
  * @brief   light ctrl interface 
  *
  ******************************************************************************
  */
#ifndef _CTRL_LIGHT_H
#define _CTRL_LIGHT_H

#include "platform_def.h"

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
  uint8_t mode;       //控制模式: 0x00：只关；0x01：只开；0xff：调光
                      //          0x02：开关；0x03：调亮；0x04：调暗    
  uint8_t luminance;  //亮度：0x25~0xf0
  uint8_t CurrentLuminance;
  bool b_ctrlres;     //控制使能：0x01：有效；0x00：无效
}LightCmd_typedef;

typedef struct
{
  uint8_t uid[5];
  uint8_t retry;      // try 计数
  bool enable;        // uid使能：0x01：有效；0x00：无效
  LightCmd_typedef lightCtrlWhiteCmd;
  LightCmd_typedef lightCtrlYellowCmd;
}CtrlLight_typedef;

typedef struct
{
    CtrlLight_typedef  st_LightCtr[MAX_LIGHT_SUPPORT];
    int totalLightEnable;
    int scanActionCnt;

    uint16_t *length;
    uint8_t *datapacket;
    void (*pf_SendPut)(uint8_t*, uint8_t);  
}CtrlLight_lib;

extern CtrlLight_lib st_CtrlLight_lib;


void vLight_Init( void );
bool vLight_ScanUID( void );
void vLight_ContrlTurnOff( CtrlLight_typedef *pCtrlLight );
void vLight_ContrlTurnOn( CtrlLight_typedef *pCtrlLight );
void vLight_CtrlReset( CtrL_typedef *pCtrL_typedef );
CTRL_RESULT_ENUM eLight_CtrlInterface( CtrL_typedef *pCtrL_typedef );
#endif  /* _CTRL_LIGHT_H */ 