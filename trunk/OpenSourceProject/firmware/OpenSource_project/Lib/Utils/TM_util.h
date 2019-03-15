/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    tm_util.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/25
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
*/
#ifndef __TM_UTIL_H__
#define __TM_UTIL_H__

#define NOP 			{ __no_operation(); }  
/************************* System Delay Definiton  ****************************/
#define Delay1US()   {        \
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  \
                     }
#define Delay5US()   { Delay1US(); Delay1US(); Delay1US(); Delay1US(); Delay1US(); }
/******************************************************************************/
void TM_Delay( INT32U delay );
void TM_Delay_us( INT32U delay );
void TM_Delay_ms( INT32U delay );
INT32U TM_Check( INT32U count, INT32U (*check)(void) );


#endif  
