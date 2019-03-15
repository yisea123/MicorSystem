/** \file

$Id: uart.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __UART_H
#define __UART_H

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "stm32f10x.h"
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "Stm32hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/  
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif                                 /* __GNUC__ */

/********************* Number of Uart port on the chip ************************/
#define UART_MAX_PORTS           4
#define PORT_UART1               1
#define PORT_UART2               2
#define PORT_UART3               3
#define PORT_UART4               4
#define PORT_UART5               5

#define UART_BDR2400             2400
#define UART_BDR4800             4800
#define UART_BDR9600             9600
#define UART_BDR14400            14400
#define UART_BDR19200            19200
#define UART_BDR28800	         28800
#define UART_BDR38400            38400
#define UART_BDR50000	         50000
#define UART_BDR57600            57600
#define UART_BDR76800            76800
#define UART_BDR100000           100000
#define UART_BDR115200           115200

#define UART_IQOVERRUN           0x01             // Rx buffer overrun
#define UART_CTI		 0x02              // a packet received
#define UART_IQDIRTY		 0x20              // data in Rx buffer
#define UART_OQDIRTY		 0x40              // data in Tx buffer

#define UART_RXBUFFSIZE	         256


/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/  
typedef struct Uart_Socket UART;
struct Uart_Socket {
   uint16_t u16_RxFlag;
   uint16_t u16_RxHead;
   uint16_t u16_RxTail;
   uint16_t u16_RxCnts;
   uint8_t u8_RxBuf[UART_RXBUFFSIZE];
};
extern UART st_Uart1;
extern UART st_Uart2;
extern UART st_Uart3;
extern UART st_Uart4;
extern UART st_Uart5;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/ 
void UART1_Put( uint8_t* pu8_buf, uint16_t u16_len );
void UART3_Put( uint8_t* pu8_buf, uint16_t u16_len );
void UART2_Put( uint8_t* pu8_buf, uint16_t u16_len );
void UART4_Put( uint8_t* pu8_buf, uint16_t u16_len );
void UART5_Put( uint8_t* pu8_buf, uint16_t u16_len );

void UART_Init( UART pst_Uart, uint8_t u8_port, uint32_t u32_bdr );
void USART_SendByte( USART_TypeDef* USARTx,uint8_t u8_Data );
uint8_t USART_GetByte( USART_TypeDef* USARTx );
void USART_SendStr(USART_TypeDef* USARTx,uint8_t* data,uint16_t u16_len);

void Uart_RxHandle( USART_TypeDef* USARTx, UART* pst_uart );
void UART_Puts( USART_TypeDef* USARTx, uint8_t* s );
void UART_Getc( UART* pst_uart, uint8_t* pu8_buf );

int ser_printf (USART_TypeDef* USARTx, int c) ;
int ser_scanf (USART_TypeDef* USARTx) ;

void UART2_Get( uint8_t* pu8_buf, uint8_t u8_len );

void Uart1_RxHandle( void );
void Uart2_RxHandle( void );
void Uart3_RxHandle( void );
void Uart2_RxHandleExt( uint8_t byte );
void Uart4_RxHandle( void );
void Uart5_RxHandle( void );

#ifdef __cplusplus
}
#endif

#endif   /* __UART_H */