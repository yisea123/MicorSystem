/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    util.h
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
#ifndef __UTIL_H__
#define __UTIL_H__

#define dim(x) (sizeof(x) / sizeof(x[0])) /* Returns number of elements			*/

void SoftReset( void );
uint8_t UTL_CalCheckSum8(uint8_t *ptr, uint32_t len);
uint8_t UTL_CheckSum8(uint8_t *ptr, uint32_t len);
uint32_t UTL_CalCheckSum32(uint8_t *ptr, uint32_t len);
uint32_t UTL_CheckSum32(uint8_t *ptr, uint32_t len);
uint16_t UTL_CalcCrc16( uint8_t u8_data );
uint16_t UTL_ChkCrc16( uint8_t* pu8_data, uint16_t u16_len );
uint32_t UTL_CalcCrc32( uint8_t* pu8_data, uint32_t u32_len );
uint32_t UTL_FindRange( uint32_t u32_Num, uint32_t * u32p_Table, uint32_t u32_Len );
uint32_t UTL_Date2Minute( uint8_t *Date );
uint8_t UTL_Byte2Deci( uint8_t byte, uint8_t *buff );
void UTL_Byte2DeciS( uint8_t byte, uint8_t *buff, uint8_t ch );
uint8_t UTL_Word2Deci( uint16_t word, uint8_t *buff );
void UTL_Word2DeciS( uint16_t word, uint8_t *buff, uint8_t ch );
uint32_t UTL_Long2Deci( uint32_t qbyte, uint8_t *buff, uint32_t mdigit );
void UTL_Long2DeciS( uint32_t qbyte, uint8_t *buff, uint32_t mdigit, uint8_t ch );
static uint8_t btoh( uint8_t num );
void UTL_Byte2Hex( uint8_t byte, uint8_t *buff );
void UTL_Word2Hex( uint16_t word, uint8_t *buff );
uint8_t UTL_Byte2Bcd( uint8_t byte );
uint8_t UTL_Bcd2Byte( uint8_t bcd );
void UTL_Bcd2Ascii( uint8_t bcd, uint8_t *buff );
uint16_t UTL_WordDelta( uint16_t v1, uint16_t v2 );
uint8_t UTL_ByteDelta( uint8_t v1, uint8_t v2 );
uint8_t UTL_Word2Float( uint16_t word, uint8_t *buff, uint8_t deci );
uint8_t UTL_Long2Float( uint32_t qbyte, uint8_t *buff, uint8_t deci );
uint32_t UTL_StrLen( uint8_t *str );
uint32_t UTL_IsBCD( uint8_t *buff, uint32_t len );
int16_t GetTemperatureC( uint16_t raw );
int16_t ConvertTempC2F( int16_t C );

void UTL_MemCpy( uint8_t *d, uint8_t *s, uint32_t len );
uint8_t UTL_CopyStr2Mem( const uint8_t *s, uint8_t *d );
void SensorMask2Flag( uint8_t mask, uint8_t flag );
void SensorFlag2Mask( uint8_t flag, uint8_t *mask );
void IncrementSiteID( void );
void StrUpcase( int8_t* s_str, int8_t* d_str );
uint16_t StrLen( int8_t *str );
void* MemCpy( void* pv_dst, const void* pv_src, uint32_t u32_len );
void MemSet( void* pv_mem, uint8_t u8_data, uint32_t u32_len );
uint8_t Utils_FileNmChk( uint8_t* str );
uint16_t Utils_DateNCmp( uint8_t* str1, uint8_t* str2, uint16_t u16_len );
bool UTL_blCheckCRC16(uint8_t *buf, uint16_t bsize);
bool Utils_CharArrayCmp( uint8_t* CharArr1, uint8_t* CharArr2, uint16_t u16_len );

#endif   /* __UTIL_H__ */

