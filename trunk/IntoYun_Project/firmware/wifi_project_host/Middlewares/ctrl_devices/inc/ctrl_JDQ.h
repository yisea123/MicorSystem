/**
  ******************************************************************************
  * @file    Src/user/Ctr_JDQ.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/05/09
  * @brief   JDQ ctrl interface 
  *
  ******************************************************************************
  */
#ifndef _CTRL_JDQ_H
#define _CTRL_JDQ_H

#include "platform_def.h"

typedef enum
{
  JDQ_H = 0xFF,
  JDQ_L = 0,
}JDQ_CTRL_ENUM;

typedef enum
{
  JDQ_DOWN = 0,
  JDQ_UP = 1,
  JDQ_STOP = 2,
}JDQ_STATUS_ENUM;


CTRL_RESULT_ENUM eJDQ_CtrlInterface( CtrlJDQ_typedef *pJDQ_typedef );
void vJDQ_ContrlReset( CtrlJDQ_typedef *pJDQ_typedef );

#endif  /* _CTRL_JDQ_H */ 