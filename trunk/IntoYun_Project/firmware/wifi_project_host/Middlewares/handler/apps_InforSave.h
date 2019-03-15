/** \file

$Id: apps_InforSave.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

#ifndef __APPS_INFORSAVE_H
#define __APPS_INFORSAVE_H

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
  
/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/  
void Sys_InformationInit( void );
void sys_InformationSaved( void );
void sys_InformationConfig( uint8_t *buff, uint8_t length );
void Sys_InformationRead(  uint8_t type, uint8_t *buff, uint8_t *length);

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* __SYS_INFORSAVE_H */
