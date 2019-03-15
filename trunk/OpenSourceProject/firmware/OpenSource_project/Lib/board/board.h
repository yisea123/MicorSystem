/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    board.h
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
**/
#ifndef __BOARD_H
#define __BOARD_H

/*******************************************************************************
     wifi IO configuration 
********************************************************************************/
/*
  PB3: WIFI   REST
*/
#define WIFI_REST_GPIO_PORT     GPIOC
#define WIFI_REST_PIN           GPIO_Pin_0
#define WIFI_RCC_APBCLOCK       RCC_APB2Periph_GPIOC

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


/*******************************************************************************
     LED IO configuration 
********************************************************************************/
#define LED_WORK_GPIO_PORT          GPIOA
#define LED_WORK_PIN                GPIO_Pin_4
#define LED_WORK_RCC_APBCLOCK       RCC_APB2Periph_GPIOA

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

/*
********************************************************************************
     485 IO configuration 
********************************************************************************/
/*
   
*/
#define CTR_1_485_DIR_GPIO_PORT          GPIOA
#define CTR_1_485_DIR_PIN                GPIO_Pin_8
#define CTR_1_485_DIR_RCC_APBCLOCK       RCC_APB2Periph_GPIOA

#define CTR_1_485_DIR_ENABLE     	GPIO_SetBits(CTR_1_485_DIR_GPIO_PORT, CTR_1_485_DIR_PIN) 
#define CTR_1_485_DIR_DISABLE     	GPIO_ResetBits(CTR_1_485_DIR_GPIO_PORT, CTR_1_485_DIR_PIN) 

#define CTR_1_485_DIR_PortConfig() {\
                              RCC_APB2PeriphClockCmd(CTR_1_485_DIR_RCC_APBCLOCK, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              GPIO_InitStructure.GPIO_Pin   = CTR_1_485_DIR_PIN;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
                              GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                              GPIO_Init( CTR_1_485_DIR_GPIO_PORT, &GPIO_InitStructure );\
                              CTR_1_485_DIR_DISABLE;\
                            }


void Board_Init( void );
void HAL_485WriteSerial( INT8U* pu8_buf, INT8U u8_len );
void Board_LedBlink( void );

#endif /* __BOARD_H */