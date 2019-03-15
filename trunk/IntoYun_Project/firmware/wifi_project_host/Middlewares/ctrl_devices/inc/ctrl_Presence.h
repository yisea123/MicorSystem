/**
  ******************************************************************************
  * @file    Src/user/Ctr_Presence.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/05/09
  * @brief   presence ctrl interface 
  *
  ******************************************************************************
  */
#ifndef _CTRL_PRESENCE_H
#define _CTRL_PRESENCE_H

typedef struct
{
   uint16_t *length;
   uint8_t *datapacket;
   void (*pf_SendPut)(uint8_t*, uint8_t);
   
   uint8_t step;
   uint8_t retry;
   uint8_t  id[16];
   bool res;
}Presence_TypeDef;

typedef enum
{
  PENSENCE_ID = 0x00,
  PENSENCE_VALUE = 0x01,
}Presence_STEP_ENUM;


CTRL_RESULT_ENUM vPresence_ActionProcess( Presence_TypeDef *pCtr_Presence );

#endif  /* _CTRL_MODBUSINTERFACE_H */ 