#ifndef __UTIL_H__
#define __UTIL_H__

#define dim(x) (sizeof(x) / sizeof(x[0])) /* Returns number of elements			*/

void SoftReset( void );
INT8U UTL_CalCheckSum8(INT8U *ptr, INT32U len);
INT8U UTL_CheckSum8(INT8U *ptr, INT32U len);
INT32U UTL_CalCheckSum32(INT8U *ptr, INT32U len);
INT32U UTL_CheckSum32(INT8U *ptr, INT32U len);
INT16U UTL_CalcCrc16( INT8U u8_data );
INT16U UTL_ChkCrc16( INT8U* pu8_data, INT16U u16_len );
INT32U UTL_CalcCrc32( INT8U* pu8_data, INT32U u32_len );
INT32U UTL_FindRange( INT32U u32_Num, INT32U * u32p_Table, INT32U u32_Len );
INT32U UTL_Date2Minute( INT8U *Date );
INT8U UTL_Byte2Deci( INT8U byte, INT8U *buff );
void UTL_Byte2DeciS( INT8U byte, INT8U *buff, INT8U ch );
INT8U UTL_Word2Deci( INT16U word, INT8U *buff );
void UTL_Word2DeciS( INT16U word, INT8U *buff, INT8U ch );
INT32U UTL_Long2Deci( INT32U qbyte, INT8U *buff, INT32U mdigit );
void UTL_Long2DeciS( INT32U qbyte, INT8U *buff, INT32U mdigit, INT8U ch );
static INT8U btoh( INT8U num );
void UTL_Byte2Hex( INT8U byte, INT8U *buff );
void UTL_Word2Hex( INT16U word, INT8U *buff );
INT8U UTL_Byte2Bcd( INT8U byte );
INT8U UTL_Bcd2Byte( INT8U bcd );
void UTL_Bcd2Ascii( INT8U bcd, INT8U *buff );
INT16U UTL_WordDelta( INT16U v1, INT16U v2 );
INT8U UTL_ByteDelta( INT8U v1, INT8U v2 );
INT8U UTL_Word2Float( INT16U word, INT8U *buff, INT8U deci );
INT8U UTL_Long2Float( INT32U qbyte, INT8U *buff, INT8U deci );
INT32U UTL_StrLen( INT8U *str );
INT32U UTL_IsBCD( INT8U *buff, INT32U len );
INT16S GetTemperatureC( INT16U raw );
INT16S ConvertTempC2F( INT16S C );

void UTL_MemCpy( INT8U *d, INT8U *s, INT32U len );
INT8U UTL_CopyStr2Mem( const INT8U *s, INT8U *d );
void SensorMask2Flag( INT8U mask, INT8U flag );
void SensorFlag2Mask( INT8U flag, INT8U *mask );
void IncrementSiteID( void );
void StrUpcase( INT8S* s_str, INT8S* d_str );
INT16U StrLen( INT8S *str );
void* MemCpy( void* pv_dst, const void* pv_src, INT32U u32_len );
void MemSet( void* pv_mem, INT8U u8_data, INT32U u32_len );
INT8U Utils_FileNmChk( INT8U* str );
INT16U Utils_DateNCmp( INT8U* str1, INT8U* str2, INT16U u16_len );
int CheckCRC(uint8_t *buf, unsigned int bsize);

#endif   /* __ZBM_UTIL_H__ */

