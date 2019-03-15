/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    rtc.h
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
#ifndef __RTC_H
#define __RTC_H

#define RTC_DEBUG                       1
#define DATE_MMDDYYYY			0
#define DATE_DDMMYYYY			1
#define DATE_YYYYMMDD			2
#define DATE_MMDDYY		        3

#define TIME_12HOUR			0
#define TIME_24HOUR			1
#define CLOCK_AM			0
#define CLOCK_PM			1
#define CLOCK_24H			2
#define RTCDELAY_TIME		        946659661		//2000/1/1 1:1:1  
#define STM32_UNIT                      2530800

extern INT8U u8_RTCDate[11];	 //"MM/DD/YYYY "
extern INT8U u8_RTCTime[11];	 //"HH:MM:SSAM "

typedef struct Real_Time_Clock STRTC;
struct Real_Time_Clock{
    INT8U  u8_ClockMod;
    INT8U  u8_Second;
    INT8U  u8_Minute;
    INT8U  u8_Hour;
    INT8U  u8_Month;
    INT8U  u8_DayMonth;
    INT16U u16_Year;    /* start from 2000 */
};
extern STRTC st_Rtc;

void RTC_Configuration( void );
void RTC_InitConfig( void );
void RTC_ResetRTC( STRTC* st_Rtc, INT8U *u8_TimBuff);
void RTC_GetRTC( STRTC* st_Rtc);
void RTC_Set( INT8U *buff );


#endif /* __RTC_H */