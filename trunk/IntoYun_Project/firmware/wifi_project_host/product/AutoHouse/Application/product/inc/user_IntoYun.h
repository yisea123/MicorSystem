/** \file

$Id: user_IntoYun.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef USER_INTOYUN_H_
#define USER_INTOYUN_H_
/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
 
/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/  
void userInit(void);
void userHandle (void);
void Intoyun_SetAction( uint8_t id );
void vCloud_RefreshCtrlStatus( uint8_t DevType, uint8_t *buff,  uint8_t lenght );

#ifdef __cplusplus
}
#endif

#endif   /* USER_INTERFACE_H_ */