/** \file

$Id: oled.c 40486 2018-08-12 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "I2C.h"

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "oled.h"
#include "font.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define OLED_DEBUG      1	  
#define OLED_ADDRESS    0x78

typedef enum
{
   FONT_16 = 0,
   FONT_12 = 1,
}OLED_CHARSIZE;

typedef enum
{
   PARA = 0,
   DATA = 0x40,
}OLED_PARE_REG;

typedef enum
{
   X_WIDTH = 128,
   Y_WIDTH = 64,
}OLED_SCREEN_SIZE;

static uint8_t charSize;
/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void oled_WriteRegister(uint8_t val,  uint8_t reg);

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void oled_Init(void)
{ 	
    oled_WriteRegister(0xAE,PARA);//--display off
    oled_WriteRegister(0x00,PARA);//---set low column address
    oled_WriteRegister(0x10,PARA);//---set high column address
    oled_WriteRegister(0x40,PARA);//--set start line address  
    oled_WriteRegister(0xB0,PARA);//--set page address
    oled_WriteRegister(0x81,PARA); // contract control
    oled_WriteRegister(0xFF,PARA);//--128   
    oled_WriteRegister(0xA1,PARA);//set segment remap 
    oled_WriteRegister(0xA6,PARA);//--normal / reverse
    oled_WriteRegister(0xA8,PARA);//--set multiplex ratio(1 to 64)
    oled_WriteRegister(0x3F,PARA);//--1/32 duty
    oled_WriteRegister(0xC8,PARA);//Com scan direction
    oled_WriteRegister(0xD3,PARA);//-set display offset
    oled_WriteRegister(0x00,PARA);//

    oled_WriteRegister(0xD5,PARA);//set osc division
    oled_WriteRegister(0x80,PARA);//

    oled_WriteRegister(0xD8,PARA);//set area color mode off
    oled_WriteRegister(0x05,PARA);//

    oled_WriteRegister(0xD9,PARA);//Set Pre-Charge Period
    oled_WriteRegister(0xF1,PARA);//

    oled_WriteRegister(0xDA,PARA);//set com pin configuartion
    oled_WriteRegister(0x12,PARA);//

    oled_WriteRegister(0xDB,PARA);//set Vcomh
    oled_WriteRegister(0x30,PARA);//

    oled_WriteRegister(0x8D,PARA);//set charge pump enable
    oled_WriteRegister(0x14,PARA);//

    oled_WriteRegister(0xAF,PARA);//--turn on oled panel
    
    oled_Clear();

#if OLED_DEBUG  
    oled_SetCharSize( FONT_16 );  
    oled_PrintfString(6,0,"0.96' OLED TEST");  
    
    oled_SetCharSize( FONT_12 );
    oled_PrintfString(0,6,"ASCII:");  
    oled_PrintfString(63,6,"CODE:");
#endif
    
} 

void oled_SetCharSize( uint8_t val )
{
   charSize = val;
}

void oled_SetPostion( uint8_t x, uint8_t y) 
{ 	
    oled_WriteRegister(0xb0+y,PARA);
    oled_WriteRegister(((x&0xf0)>>4)|0x10,PARA);
    oled_WriteRegister((x&0x0f),PARA); 
}   	  
 
void oled_displayOn(void)
{
    oled_WriteRegister(0X8D,PARA); 
    oled_WriteRegister(0X14,PARA); 
    oled_WriteRegister(0XAF,PARA);
}
  
void oled_DisplayOff(void)
{
    oled_WriteRegister(0X8D,PARA);
    oled_WriteRegister(0X10,PARA);
    oled_WriteRegister(0XAE,PARA);
}		   			 

void oled_Clear(void)  
{  
  uint8_t i,n;
  
  for(i=0;i<8;i++)  
  {  
      oled_WriteRegister (0xb0+i,PARA);   
      oled_WriteRegister (0x00,PARA);
      oled_WriteRegister (0x10,PARA); 
      
      for( n = 0;n < 128; n++)
      {
          oled_WriteRegister(0,DATA);
      } 
  } 
}

void oled_UpScreenOn(void)  
{  
    uint8_t i,n;
    
    for(i=0;i<8;i++)  
    {  
        oled_WriteRegister (0xb0+i,PARA);
        oled_WriteRegister (0x00,PARA); 
        oled_WriteRegister (0x10,PARA);
        
        for(n=0;n<128;n++)
        {
            oled_WriteRegister(1,DATA); 
        }
    } 
}

void oled_PrintfChar(uint8_t x,uint8_t y,uint8_t val )
{      	
    uint8_t character = 0;
    uint8_t i=0;	
    
    character = val-' ';		
    if( x > X_WIDTH-1)
    {
      x = 0;
      y += 2;
    }
    
    if( charSize == FONT_16 )
    {
          oled_SetPostion(x,y);	
          for( i = 0; i < 8; i++)
          {
              oled_WriteRegister(F8X16[character*16+i],DATA);
          }
          
          oled_SetPostion(x,y+1);
          for(i=0;i<8;i++)
          {
              oled_WriteRegister(F8X16[character*16+i+8],DATA);
          }
     }
    else 
    {	
        oled_SetPostion(x,y);
        for(i=0;i<6;i++)
        {
            oled_WriteRegister(F6x8[character][i],DATA);
        }
    }
}

void oled_PrintfString(uint8_t x,uint8_t y,u8 *str  )
{
    uint8_t index = 0;
    
    while ( str[index]!='\0' )
    {		
        oled_PrintfChar(x,y,str[index] );
       
        x += 8;
        if( x > 120 )
        {  
            x=0;
            y+=2;
        }
        index++;
    }
}

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static void oled_WriteRegister(uint8_t val,  uint8_t reg)
{  
    i2c_Start();
    
    i2c_SendByte( OLED_ADDRESS );   //Slave address,SA0=0   
    i2c_WaitAck();	
    
    i2c_SendByte( reg );            //write register 
    i2c_WaitAck();	
    
    i2c_SendByte( val );    
    i2c_WaitAck();
    
    i2c_Stop();    
}
/* End of this file */
