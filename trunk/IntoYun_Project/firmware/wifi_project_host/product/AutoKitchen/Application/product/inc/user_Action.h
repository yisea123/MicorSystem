/**
  ******************************************************************************
  * @file    Src/user/Ctr_Action.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/04/11
  * @brief   blue tooth ctrl interface 
  *
  ******************************************************************************
  */
#ifndef _CTRL_ACTION_H
#define _CTRL_ACTION_H

typedef struct
{
  void (*vCtrlAction_Init)( void );
  void (*Set_Handler)(uint8_t dev_type,  uint8_t id, uint8_t *ctrlRes, uint8_t lenght );
  void (*Motor_Handler)( void );
}vCtrlAction_t; 

extern const vCtrlAction_t mainCtrl;    

#endif  /* _CTRL_ACTION_H */ 