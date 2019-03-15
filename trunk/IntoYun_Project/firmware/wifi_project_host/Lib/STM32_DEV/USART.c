/** \file

$Id: uart.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "usart.h"
#include "Util.h"

#if WIFI_ENABLE
#include "intoyun_interface.h"
#endif

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
UART st_Uart1; 
UART st_Uart2; 
UART st_Uart3;
UART st_Uart4;
UART st_Uart5;

#if OS_EN
OS_CPU_SR  cpu_sr = 0;
#define ENTER_CRITICAL()  OS_ENTER_CRITICAL()
#define EXIT_CRITICAL()   OS_EXIT_CRITICAL()
#endif

/******************************************************************************
* EXPORT FUNCTION DECLARATIONS
******************************************************************************/
void UART_Init( UART pst_Uart, uint8_t u8_port, uint32_t u32_bdr )
{
   NVIC_InitTypeDef NVIC_InitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;
   USART_InitTypeDef USART_InitStructure;
  
   USART_InitStructure.USART_BaudRate   = u32_bdr;            
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;       
   USART_InitStructure.USART_StopBits   = USART_StopBits_1;   
   USART_InitStructure.USART_Parity     = USART_Parity_No;  
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    
 
    if( u8_port > PORT_UART5 ) 
    {
          u8_port = PORT_UART5;
    }  
  
    pst_Uart.u16_RxFlag = 0x0000;
    pst_Uart.u16_RxHead = 0;
    pst_Uart.u16_RxTail = 0;
    pst_Uart.u16_RxCnts = 0;
    MemSet( (uint8_t*)&(pst_Uart.u8_RxBuf[0]), 0x00, UART_RXBUFFSIZE );
    
    switch( u8_port )
    {
      case PORT_UART1:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
#if 1    
        /* disable even */   
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;
        USART_InitStructure.USART_Parity     = USART_Parity_Even;	 
#endif
        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
        //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
        USART_Init( USART1, &USART_InitStructure );	
        USART_Cmd( USART1, ENABLE );

        // Enable the USART1 Interrupt 
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);        
       break;
       
      case PORT_UART2:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);     

        USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
        //USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
        USART_Init( USART2, &USART_InitStructure );	
        USART_Cmd( USART2, ENABLE ); 

        // Enable the USART2 Interrupt 
        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure) ;      
       break;
       
      case PORT_UART3:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                 //tx 
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                 //rx 
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOB, &GPIO_InitStructure);     
        
        /* Enable the USART3 Pins Software Remapping */
        //GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE); 
        USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
        //USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
        USART_Init( USART3, &USART_InitStructure );
        USART_Cmd( USART3, ENABLE ); 

        // Enable the USART3 Interrupt 
        NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);        
       break;
       
      case PORT_UART4: 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                // TX 
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                // RX
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOC, &GPIO_InitStructure);  

        USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
        //USART_ITConfig(UART4, USART_IT_TXE, ENABLE);
        USART_Init( UART4, &USART_InitStructure );	
        USART_Cmd( UART4, ENABLE );  

        // Enable the USART4 Interrupt 
        NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);          
       break;
       
      case PORT_UART5:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;                // TX 
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                // RX
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOD, &GPIO_InitStructure);  
        
        USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
        //USART_ITConfig(UART5, USART_IT_TXE, ENABLE);
        USART_Init( UART5, &USART_InitStructure );
        USART_Cmd( UART5, ENABLE ); 
        // Enable the USART5 Interrupt 
        NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);          
       break;
    }
}

void USART_SendByte( USART_TypeDef* USARTx,uint8_t u8_Data )
{ 
    USART_SendData( USARTx, ( uint8_t )u8_Data );
    while( USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET ){}
}

uint8_t USART_GetByte( USART_TypeDef* USARTx )
{
    while( USART_GetFlagStatus( USARTx,USART_FLAG_RXNE )==RESET ){}
    return( USART_ReceiveData( USARTx ) );  
}

void USART_SendStr(USART_TypeDef* USARTx,uint8_t* data,uint16_t u16_len)
{
    uint8_t i;

    for (i=0; i<u16_len; i++)
    {
        USART_SendByte(USARTx,data[i]);
    }
}

void UART_Puts( USART_TypeDef* USARTx, uint8_t* s )
{
    uint16_t u16_i = 0;

    while ( *(s + u16_i) != '\0' ) 
    {
        USART_SendByte( USARTx, *(s + u16_i) );
        u16_i++;
    }
}

void UART1_Put( uint8_t* pu8_buf, uint16_t u16_len )
{
    uint16_t u16_i;
   
    for( u16_i=0; u16_i<u16_len; u16_i++ ) 
    {
        USART_SendByte( USART1, *(pu8_buf + u16_i));
    }
}

void UART2_Put( uint8_t* pu8_buf, uint16_t u16_len )
{
    uint16_t u16_i;
   
    for( u16_i=0; u16_i<u16_len; u16_i++ ) 
    {
        USART_SendByte( USART2, *(pu8_buf + u16_i)); 
    }
}

void UART3_Put( uint8_t* pu8_buf, uint16_t u16_len )
{
    uint16_t u16_i;
   
    for( u16_i=0; u16_i<u16_len; u16_i++ ) 
    {
        USART_SendByte( USART3, *(pu8_buf + u16_i));
    }
}

void UART4_Put( uint8_t* pu8_buf, uint16_t u16_len )
{
    uint16_t u16_i;
   
    for( u16_i=0; u16_i<u16_len; u16_i++ ) 
    {
        USART_SendByte( UART4, *(pu8_buf + u16_i));
    }
}

void UART5_Put( uint8_t* pu8_buf, uint16_t u16_len )
{
    uint16_t u16_i;
   
    for( u16_i=0; u16_i<u16_len; u16_i++ ) 
    {
        USART_SendByte( UART5, *(pu8_buf + u16_i));
    }
}


void UART_Getc( UART* pst_uart, uint8_t* pu8_buf )
{
    if( pst_uart->u16_RxCnts ) 
    {
        *pu8_buf = pst_uart->u8_RxBuf[ pst_uart->u16_RxTail++ ];
        if( pst_uart->u16_RxTail >= UART_RXBUFFSIZE ) 
        {
           pst_uart->u16_RxTail = 0;
        }
        pst_uart->u16_RxCnts--;
    }
    
    if( pst_uart->u16_RxTail == pst_uart->u16_RxHead ) 
    {
        pst_uart->u16_RxFlag &= ~UART_IQDIRTY;
    }
}

void UART2_Get( uint8_t* pu8_buf, uint8_t u8_len )
{
    UART* pst_uart = &st_Uart2;
    
    if( pst_uart->u16_RxCnts ) 
    {
        *pu8_buf = pst_uart->u8_RxBuf[ pst_uart->u16_RxTail++ ];
        if( pst_uart->u16_RxTail >= u8_len ) 
        {
           pst_uart->u16_RxTail = 0;
        }
        pst_uart->u16_RxCnts--;
    }
    
    if( pst_uart->u16_RxTail == pst_uart->u16_RxHead ) 
    {
        pst_uart->u16_RxFlag &= ~UART_IQDIRTY;
    }
}


void Uart_RxHandle( USART_TypeDef* USARTx, UART* pst_uart )
{
    if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
          pst_uart->u8_RxBuf[ pst_uart->u16_RxHead++ ] = USART_ReceiveData(USARTx);
          if( pst_uart->u16_RxHead >= UART_RXBUFFSIZE ) 
          {
              pst_uart->u16_RxHead = 0;
              USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
          }
          pst_uart->u16_RxCnts++;  
    }        
}

/*******************************************************************************
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  *****************************************************************************/
PUTCHAR_PROTOTYPE
{
  USART_SendData(DEBUG_UART, ( uint8_t ) ch);
  while (USART_GetFlagStatus(DEBUG_UART, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

void Uart1_RxHandle( void )
{
    Uart_RxHandle( USART1, &st_Uart1);  
}

void Uart2_RxHandle( void )
{
    Uart_RxHandle( USART2, &st_Uart2);  
}

void Uart3_RxHandle( void )
{
    Uart_RxHandle( USART3, &st_Uart3);
}

void Uart4_RxHandle( void )
{
    Uart_RxHandle( UART4, &st_Uart4);
}

void Uart5_RxHandle( void )
{
    Uart_RxHandle( UART5, &st_Uart5);
}

/*******************************************************************************
* Function Name  : ser_printf
* Description    : Write character to Serial Port.
* Input          : character, USART used
* Output         : None
* Return         : Return character
*******************************************************************************/
int ser_printf (USART_TypeDef* USARTx, int c) 
{

  while (!(USARTx->SR & USART_FLAG_TXE));
  USARTx->DR = (c & 0x1FF);

  return (c);
}

/*******************************************************************************
* Function Name  : ser_scanf
* Description    : Read character from Serial Port   (blocking read).
* Input          : USART used
* Output         : None
* Return         : Return int
*******************************************************************************/
int ser_scanf (USART_TypeDef* USARTx) 
{
  while (!(USARTx->SR & USART_FLAG_RXNE));

  return ((int)(USARTx->DR & 0x1FF));
}

void USART1_IRQHandler( void )
{  
    Uart1_RxHandle();
}

void USART2_IRQHandler( void )
{
    Uart2_RxHandle();
}

void USART3_IRQHandler( void )
{
    Uart3_RxHandle();
}

void UART4_IRQHandler( void )
{
#if WIFI_ENABLE
   HAL_WifiModeInterrupt();
#else
   Uart4_RxHandle();
#endif
}

void UART5_IRQHandler( void )
{
    Uart5_RxHandle();
}

/* End of this file */  