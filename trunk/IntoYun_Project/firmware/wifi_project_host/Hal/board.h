/** \file

$Id: board.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __BOARD_H
#define __BOARD_H

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "stm32f10x.h"
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
     power IO configuration 
********************************************************************************/
#define PERI_3V3_CTRL_PORT               GPIOC             
#define PERI_3V3_CTRL_PIN                GPIO_Pin_9   
#define PERI_3V3_CTRL_RCC_APBCLOCK       RCC_APB2Periph_GPIOC

#define PERI_3V3_CTRL_PortConfig() {\
                              RCC_APB2PeriphClockCmd(PERI_3V3_CTRL_RCC_APBCLOCK, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              GPIO_InitStructure.GPIO_Pin   = PERI_3V3_CTRL_PIN;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
                              GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                              GPIO_Init( PERI_3V3_CTRL_PORT, &GPIO_InitStructure );\
                            }

#define  PERI_3V3_CTRL_POWER_OFF         GPIO_SetBits(PERI_3V3_CTRL_PORT, PERI_3V3_CTRL_PIN) 	
#define  PERI_3V3_CTRL_POWER_ON          GPIO_ResetBits(PERI_3V3_CTRL_PORT, PERI_3V3_CTRL_PIN) 

/*******************************************************************************
     Blue tooth IO configuration 
********************************************************************************/
/*
    MCU PORT
*/
#define BLUETOOTH_CTRL_PORT                   GPIOB
#define BLUETOOTH_CTRL_RCC_APBCLOCK           RCC_APB2Periph_GPIOB

/*
  PB4: BLUE TOOTH   REST
  PB8: BLUE TOOTH   CAST
  PB9: BLUE TOOTH   CONN
*/
#define BLUETOOTH_RST_CTRL_PIN                GPIO_Pin_4   
#define BLUETOOTH_CAST_CTRL_PIN               GPIO_Pin_8
#define BLUETOOTH_CONN_CTRL_PIN               GPIO_Pin_9  

#define  BLUETOOTH_RST_CTRL_HIGH              GPIO_SetBits(BLUETOOTH_CTRL_PORT, BLUETOOTH_RST_CTRL_PIN) 	
#define  BLUETOOTH_RST_CTRL_LOW               GPIO_ResetBits(BLUETOOTH_CTRL_PORT, BLUETOOTH_RST_CTRL_PIN) 


#define BLUETOOTH_CTRLRST_PortConfig() {\
                              RCC_APB2PeriphClockCmd(BLUETOOTH_CTRL_RCC_APBCLOCK, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              \
                              GPIO_InitStructure.GPIO_Pin   = BLUETOOTH_RST_CTRL_PIN;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
                              GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                              GPIO_Init( BLUETOOTH_CTRL_PORT, &GPIO_InitStructure );\
                              BLUETOOTH_RST_CTRL_HIGH;\
                            }

#define BLUETOOTH_CTRL_PortConfig() {\
                              RCC_APB2PeriphClockCmd(BLUETOOTH_CTRL_RCC_APBCLOCK, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                                                                   \
                              GPIO_InitStructure.GPIO_Pin   = BLUETOOTH_CAST_CTRL_PIN|BLUETOOTH_CONN_CTRL_PIN;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING; \
                              GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);\
                              GPIO_Init( BLUETOOTH_CTRL_PORT, &GPIO_InitStructure ); \
                              BLUETOOTH_CTRLRST_PortConfig();  \
                            }




/*******************************************************************************
     LED IO configuration 
********************************************************************************/
#define LED_WORK_GPIO_PORT          GPIOB
#define LED_WORK_PIN                GPIO_Pin_0
#define LED_WORK_RCC_APBCLOCK       RCC_APB2Periph_GPIOB

#define LED1_CTR_PIN                GPIO_Pin_1

#define HW_LED_PortConfig() {\
                              RCC_APB2PeriphClockCmd(LED_WORK_RCC_APBCLOCK, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              GPIO_InitStructure.GPIO_Pin   = LED_WORK_PIN|LED1_CTR_PIN;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
                              GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                              GPIO_Init( LED_WORK_GPIO_PORT, &GPIO_InitStructure );\
                            }

#define  LED_ON             GPIO_SetBits(LED_WORK_GPIO_PORT, LED_WORK_PIN) 	
#define  LED_OFF            GPIO_ResetBits(LED_WORK_GPIO_PORT, LED_WORK_PIN) 

#define  LED1_ON            GPIO_SetBits(LED_WORK_GPIO_PORT, LED1_CTR_PIN) 	
#define  LED1_OFF           GPIO_ResetBits(LED_WORK_GPIO_PORT, LED1_CTR_PIN) 


#define LED_SystemRun( ctrl ){\
                            if( ctrl )   \
                               LED_ON;   \
                             else        \
                               LED_OFF;  \
                         }

#define LED1_SystemDebug( ctrl ){\
                            if( ctrl )   \
                               LED1_ON;   \
                             else        \
                               LED1_OFF;  \
                         }

/*******************************************************************************
     wifi IO configuration 
********************************************************************************/
/*
  PB3: WIFI   REST
*/
#define WIFI_REST_GPIO_PORT     GPIOB
#define WIFI_REST_PIN           GPIO_Pin_3
#define WIFI_RCC_APBCLOCK       RCC_APB2Periph_GPIOB

#define WIFI_REST_HIGH          GPIO_SetBits(WIFI_REST_GPIO_PORT, WIFI_REST_PIN) 
#define WIFI_REST_LOW           GPIO_ResetBits(WIFI_REST_GPIO_PORT, WIFI_REST_PIN) 

#define WIFI_REST_PortConfig() {\
                              RCC_APB2PeriphClockCmd(WIFI_RCC_APBCLOCK, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              GPIO_InitStructure.GPIO_Pin   = WIFI_REST_PIN;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
                              GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                              GPIO_Init( WIFI_REST_GPIO_PORT, &GPIO_InitStructure );\
                            }

/*
  PB3: WIFI MODE
*/
#define WIFI_SETMODE_GPIO_PORT          GPIOA
#define WIFI_SETMODE_PIN                GPIO_Pin_15
#define WIFI_SETMODE_RCC_APBCLOCK       RCC_APB2Periph_GPIOA

#define WIFI_SETMODE_HIGH               GPIO_SetBits(WIFI_SETMODE_GPIO_PORT, WIFI_SETMODE_PIN) 
#define WIFI_SETMODE_LOW                GPIO_ResetBits(WIFI_SETMODE_GPIO_PORT, WIFI_SETMODE_PIN) 

#define WIFI_SETMODE_PortConfig() {\
                              RCC_APB2PeriphClockCmd(WIFI_SETMODE_RCC_APBCLOCK, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              GPIO_InitStructure.GPIO_Pin   = WIFI_SETMODE_PIN;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
                              GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                              GPIO_Init( WIFI_SETMODE_GPIO_PORT, &GPIO_InitStructure );\
                            }


/*
********************************************************************************
     485 port IO configuration 
********************************************************************************/
/*
   485 port -1 
*/
#define CTR_1_485_DIR_GPIO_PORT          GPIOA
#define CTR_1_485_DIR_PIN                GPIO_Pin_8
#define CTR_1_485_DIR_RCC_APBCLOCK       RCC_APB2Periph_GPIOA

#define CTR_1_485_DIR_ENABLE             GPIO_SetBits(CTR_1_485_DIR_GPIO_PORT, CTR_1_485_DIR_PIN) 
#define CTR_1_485_DIR_DISABLE            GPIO_ResetBits(CTR_1_485_DIR_GPIO_PORT, CTR_1_485_DIR_PIN) 

#define CTR_1_485_DIR_PortConfig() {\
                              RCC_APB2PeriphClockCmd(CTR_1_485_DIR_RCC_APBCLOCK, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              GPIO_InitStructure.GPIO_Pin   = CTR_1_485_DIR_PIN;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
                              GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                              GPIO_Init( CTR_1_485_DIR_GPIO_PORT, &GPIO_InitStructure );\
                              CTR_1_485_DIR_DISABLE;\
                            }


/*
   485 port -2 
*/
#define CTR_2_485_DIR_GPIO_PORT          GPIOA
#define CTR_2_485_DIR_PIN                GPIO_Pin_1
#define CTR_2_485_DIR_RCC_APBCLOCK       RCC_APB2Periph_GPIOA

#define CTR_2_485_DIR_ENABLE             GPIO_SetBits(CTR_2_485_DIR_GPIO_PORT, CTR_2_485_DIR_PIN) 
#define CTR_2_485_DIR_DISABLE            GPIO_ResetBits(CTR_2_485_DIR_GPIO_PORT, CTR_2_485_DIR_PIN) 

#define CTR_2_485_DIR_PortConfig() {\
                              RCC_APB2PeriphClockCmd(CTR_2_485_DIR_RCC_APBCLOCK, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              GPIO_InitStructure.GPIO_Pin   = CTR_2_485_DIR_PIN;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
                              GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                              GPIO_Init( CTR_2_485_DIR_GPIO_PORT, &GPIO_InitStructure );\
                              CTR_2_485_DIR_DISABLE;\
                            }


void Board_Init( void );
void HAL_485WriteSerial_Port1( uint8_t* buf, uint8_t len );
void HAL_485WriteSerial_Port2( uint8_t* buf, uint8_t len );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */


