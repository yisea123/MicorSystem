/*******************************************************************************
** File name:	 RTC.c
** Created by:	 Mingfei Tang		
** Created date: 2016/1/20		
** Version:	  V1.00			
** Descriptions:
**
**------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*******************************************************************************/
#include "includes.h"
#include "time.h"
STRTC st_Rtc;

INT8U u8_RTCDate[11];	           //"MM/DD/YYYY "
INT8U u8_RTCTime[11];	           //"HH:MM:SSAM 

void RTC_Configuration( void )
{
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}


struct tm Time_ConvUnixToCalendar(time_t t)
{
    struct tm *t_tm;
    t_tm = localtime(&t);
    t_tm->tm_year += 1900; 
    
    return *t_tm;
}

time_t Time_ConvCalendarToUnix(struct tm t)
{
    t.tm_year -= 1900; 
    
    return mktime(&t);    
}

time_t Time_GetUnixTime(void)
{
    return (time_t)RTC_GetCounter();
}

struct tm Time_GetCalendarTime(void)
{
    time_t t_t;
    struct tm t_tm;
    
    t_t = (time_t)RTC_GetCounter();
    t_tm = Time_ConvUnixToCalendar(t_t);
    return t_tm;
}

void Time_SetUnixTime(time_t t)
{
    RTC_WaitForLastTask();
    RTC_SetCounter((u32)t);
    RTC_WaitForLastTask();
    return;
}

void Time_SetCalendarTime(struct tm t)
{
    Time_SetUnixTime(Time_ConvCalendarToUnix(t));
    return;
}

static void RTC_IARGetRTC( void )
{
    INT8U u8_buf[12]; 
    
    memset( u8_buf, ' ', 12 );
    memcpy( u8_buf, __TIME__, 9 );
    st_Rtc.u8_Second = (u8_buf[6] - 0x30)*10 + (u8_buf[7] - 0x30);
    st_Rtc.u8_Minute = (u8_buf[3] - 0x30)*10 + (u8_buf[4] - 0x30);
    st_Rtc.u8_Hour = (u8_buf[0] - 0x30)*10 + (u8_buf[1] - 0x30); 
    memcpy( u8_buf, __DATE__, 12 );
    if(u8_buf[4] > 0x30){
        st_Rtc.u8_DayMonth = (u8_buf[4] - 0x30)*10 + (u8_buf[5] - 0x30); 
    } 
    else{
        st_Rtc.u8_DayMonth =  (u8_buf[5] - 0x30); 
    }
  
    if( strncmp( (char*)u8_buf, "Jan", 3) == 0 ) {
        st_Rtc.u8_Month = 1;
    }
    else if( strncmp( (char*)u8_buf, "Feb", 3) == 0 ) {
        st_Rtc.u8_Month = 2;
    }
    else if( strncmp( (char*)u8_buf, "Mar", 3) == 0 ) {
        st_Rtc.u8_Month = 3;
    }
    else if( strncmp( (char*)u8_buf, "Apr", 3) == 0 ) {
        st_Rtc.u8_Month = 4;
    }
    else if( strncmp( (char*)u8_buf, "May", 3) == 0 ) {
        st_Rtc.u8_Month = 5;
    }
    else if( strncmp( (char*)u8_buf, "Jun", 3) == 0 ) {
        st_Rtc.u8_Month = 6;
    }
    else if( strncmp( (char*)u8_buf, "Jul", 3) == 0 ) {
        st_Rtc.u8_Month = 7;
    }
    else if( strncmp( (char*)u8_buf, "Aug", 3) == 0 ) {
        st_Rtc.u8_Month = 8;
    }
    else if( strncmp( (char*)u8_buf, "Sep", 3) == 0 ) {
        st_Rtc.u8_Month = 9;
    }
    else if( strncmp( (char*)u8_buf, "Oct", 3) == 0 ) {
        st_Rtc.u8_Month = 10;
    }
    else if( strncmp( (char*)u8_buf, "Nov", 3) == 0 ) {
        st_Rtc.u8_Month = 11;
    }
    else if( strncmp( (char*)u8_buf, "Dec", 3) == 0 ) {
        st_Rtc.u8_Month = 12;
    }   
    st_Rtc.u16_Year = (u8_buf[7] - 0x30)*1000 + (u8_buf[8] - 0x30)*100 + \
                     (u8_buf[9] - 0x30)*10 + (u8_buf[10] - 0x30);
}

void RTC_InitConfig( void )
{
    struct tm now;	
    
    if( BKP_ReadBackupRegister(BKP_DR1  ) != 0x5A5a){
        RTC_IARGetRTC();
        RTC_Configuration(); 
        now.tm_year = st_Rtc.u16_Year;
        now.tm_mon  = st_Rtc.u8_Month;
        now.tm_mday = st_Rtc.u8_DayMonth;
        now.tm_hour = st_Rtc.u8_Hour;
        now.tm_min  = st_Rtc.u8_Minute;
        now.tm_sec  = st_Rtc.u8_Second; 
        Time_SetCalendarTime(now);
        BKP_WriteBackupRegister(  BKP_DR1,  0x5A5a );
    }
    else
    {
      if( RCC_GetFlagStatus(RCC_FLAG_PORRST)==SET )
      {
      }
      else if(  RCC_GetFlagStatus(RCC_FLAG_PINRST)==SET )
      {
      }
      RCC_ClearFlag();
      RCC_RTCCLKCmd(ENABLE);     
      RTC_WaitForSynchro(); 
      RTC_ITConfig(RTC_IT_SEC,ENABLE);
      RTC_WaitForLastTask();     
    }
#ifdef RTCClockOutput_Enable 
    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);   
    /* Disable the Tamper Pin */
    BKP_TamperPinCmd(DISABLE);
    /* To output RTCCLK/64 on Tamper pin, the tamper functionality must be disabled */
    /* Enable RTC Clock Output on Tamper Pin */
    BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
#endif     
    RCC_ClearFlag();    /* Clear reset flags */
}

void RTC_ResetRTC( STRTC* st_Rtc, INT8U *u8_TimBuff)
{
    struct tm now;

    now   = Time_GetCalendarTime();	  //Get RTC Time and date 
    st_Rtc->u16_Year = now.tm_year;
    st_Rtc->u8_Month = now.tm_mon ;
    st_Rtc->u8_DayMonth =  now.tm_mday;
    st_Rtc->u8_Hour  =  now.tm_hour +1;
    st_Rtc->u8_Minute  = now.tm_min ;
    st_Rtc->u8_Second  = now.tm_sec;
    if( st_Rtc->u8_Hour  == 24 )
        st_Rtc->u8_Hour = 0;
    
    sprintf( (char*)u8_TimBuff,"%2d/%2d/%4d %2d:%2d:%2d", st_Rtc->u8_Month,     \
                                                          st_Rtc->u8_DayMonth,  \
                                                          st_Rtc->u16_Year,     \
                                                          st_Rtc->u8_Hour,      \
                                                          st_Rtc->u8_Minute,    \
                                                          st_Rtc->u8_Second);
}

void RTC_GetRTC( STRTC* st_Rtc)
{
    struct tm now;

    now  = Time_GetCalendarTime();	   //Get RTC Time and date 
    st_Rtc->u16_Year = now.tm_year;
    st_Rtc->u8_Month = now.tm_mon ;
    st_Rtc->u8_DayMonth =  now.tm_mday;
    st_Rtc->u8_Hour  =  now.tm_hour +1;
    st_Rtc->u8_Minute  = now.tm_min ;
    st_Rtc->u8_Second  = now.tm_sec;

    if( st_Rtc->u8_Hour  == 24 )
      st_Rtc->u8_Hour = 0; 
    
}

/* PC 与采集仪之间时间同步运算 */
void RTC_Match_WithFPGA( INT32U NetRTC )
{
   RTC_Configuration(); 
  /*
    struct tm now;
    
    RTC_Configuration(); 
    
    NetRTC += RTCDELAY_TIME;      
    now = Time_ConvUnixToCalendar(NetRTC);
    now.tm_mon += 1;
    now.tm_hour += 7;
    
    Time_SetCalendarTime(now); 
   */

    Time_SetUnixTime( NetRTC );
    RCC_ClearFlag();    // Clear reset flags
    BKP_WriteBackupRegister(  BKP_DR1,  0x5A5a );
}

/* 采集仪时间转换为上位机（支持采集仪数据格式）可使用的时间*/
void RTC_Convert2UnitTime( STRTC  *pst_Rtc, INT32U *unixTime)
{
  
  /*
    struct tm now;

    RTC_GetRTC( pst_Rtc);  //获取系统RTC
    now.tm_year = pst_Rtc->u16_Year-1900;
    now.tm_mon  = pst_Rtc->u8_Month-1;
    now.tm_mday = pst_Rtc->u8_DayMonth;
    now.tm_hour = pst_Rtc->u8_Hour-8;
    now.tm_min  = pst_Rtc->u8_Minute;
    now.tm_sec  = pst_Rtc->u8_Second; 
    now.tm_isdst  = -1; 

    *unixTime =  mktime( &now)-RTCDELAY_TIME; 
 */ 
 
    *unixTime = RTC_GetCounter();
}



/* EOF */  

