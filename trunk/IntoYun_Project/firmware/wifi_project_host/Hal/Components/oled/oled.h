/** \file

$Id: oled.h 40486 2018-08-12 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __OLED_H
#define __OLED_H

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 


/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void oled_Clear(void) ;
void oled_Init(void);
void oled_UpScreenOn(void);

void oled_PrintfString(uint8_t x,uint8_t y,u8 *str);
void oled_PrintfChar(uint8_t x,uint8_t y,uint8_t val);
void oled_SetPostion( uint8_t x, uint8_t y) ;
void oled_SetCharSize( uint8_t val );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __OLED_H */