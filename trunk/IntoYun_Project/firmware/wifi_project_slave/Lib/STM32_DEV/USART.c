/*******************************************************************************
** File name:	 USART.c
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

UART st_Uart1; 
UART st_Uart2; 
UART st_Uart3;

#if OS_EN
OS_CPU_SR  cpu_sr = 0;
#define ENTER_CRITICAL()	OS_ENTER_CRITICAL()
#define EXIT_CRITICAL()		OS_EXIT_CRITICAL()
#endif

void UART_Init( UART pst_Uart, INT8U u8_port, INT32U u32_bdr )
{
   GPIO_InitTypeDef GPIO_InitStructure;	
   USART_InitTypeDef USART_InitStructure;
  
   USART_InitStructure.USART_BaudRate   = u32_bdr;	              
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;       
   USART_InitStructure.USART_StopBits   = USART_StopBits_1;	      
   USART_InitStructure.USART_Parity     = USART_Parity_No;	     
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    
	 
    if( u8_port > PORT_UART5 ) {
          u8_port = PORT_UART5;
    }  
  
    pst_Uart.u16_RxFlag = 0x0000;
    pst_Uart.u16_RxHead = 0;
    pst_Uart.u16_RxTail = 0;
    pst_Uart.u16_RxCnts = 0;
    MemSet( (INT8U*)&(pst_Uart.u8_RxBuf[0]), 0x00, UART_RXBUFFSIZE );
    
    switch( u8_port ){
      case PORT_UART1:
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(GPIOA, &GPIO_InitStructure);
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
       GPIO_Init(GPIOA, &GPIO_InitStructure);
            
#if 1    /* 支持偶校验 */   
       USART_InitStructure.USART_WordLength = USART_WordLength_9b;
       USART_InitStructure.USART_Parity     = USART_Parity_Even;	 
#endif   
       
       USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
       //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
       USART_Init( USART1, &USART_InitStructure );	
       USART_Cmd( USART1, ENABLE );
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
       break;
      case PORT_UART4: 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                //Config TX 
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                //Config RX
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOC, &GPIO_InitStructure);  
        
        USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
        //USART_ITConfig(UART4, USART_IT_TXE, ENABLE);
        USART_Init( UART4, &USART_InitStructure );	
        USART_Cmd( UART4, ENABLE );            
       break;
      case PORT_UART5:
       break;	
    }
}

void USART_SendByte( USART_TypeDef* USARTx,INT8U u8_Data )
{ 
    USART_SendData( USARTx, ( INT8U )u8_Data );
    while( USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET ){}	  
}

INT8U USART_GetByte( USART_TypeDef* USARTx )
{
    while( USART_GetFlagStatus( USARTx,USART_FLAG_RXNE )==RESET ){}
    return( USART_ReceiveData( USARTx ) );  
}

void USART_SendStr(USART_TypeDef* USARTx,INT8U* data,INT16U u16_len)
{
    INT8U i;

    for (i=0; i<u16_len; i++)
    {
        USART_SendByte(USARTx,data[i]);
    }	
}

void UART_Puts( USART_TypeDef* USARTx, INT8U* s )
{
    INT16U u16_i = 0;

    while ( *(s + u16_i) != '\0' ) 
    {
          USART_SendByte( USARTx, *(s + u16_i) );
          u16_i++;
    }
}


void UART1_Put( INT8U* pu8_buf, INT16U u16_len )
{
    INT16U u16_i;
   
    for( u16_i=0; u16_i<u16_len; u16_i++ ) {
        USART_SendByte( USART1, *(pu8_buf + u16_i));
    }
}

void UART2_Put( INT8U* pu8_buf, INT16U u16_len )
{
    INT16U u16_i;
   
    for( u16_i=0; u16_i<u16_len; u16_i++ ) {
        USART_SendByte( USART2, *(pu8_buf + u16_i)); 
    }
}

void UART3_Put( INT8U* pu8_buf, INT16U u16_len )
{
    INT16U u16_i;
   
    for( u16_i=0; u16_i<u16_len; u16_i++ ) {
        USART_SendByte( USART3, *(pu8_buf + u16_i));
    }
}

void UART4_Put( INT8U* pu8_buf, INT16U u16_len )
{
    INT16U u16_i;
   
    for( u16_i=0; u16_i<u16_len; u16_i++ ) {
        USART_SendByte( UART4, *(pu8_buf + u16_i));
    }
}


void UART_Getc( UART* pst_uart, INT8U* pu8_buf )
{
    if( pst_uart->u16_RxCnts ) {
        *pu8_buf = pst_uart->u8_RxBuf[ pst_uart->u16_RxTail++ ];
        if( pst_uart->u16_RxTail >= UART_RXBUFFSIZE ) {
                pst_uart->u16_RxTail = 0;
        }
        pst_uart->u16_RxCnts--;
    }
    if( pst_uart->u16_RxTail == pst_uart->u16_RxHead ) {
        pst_uart->u16_RxFlag &= ~UART_IQDIRTY;
    }
}

void UART2_Get( INT8U* pu8_buf, INT8U u8_len )
{
    UART* pst_uart = &st_Uart2;
    
    if( pst_uart->u16_RxCnts ) {
        *pu8_buf = pst_uart->u8_RxBuf[ pst_uart->u16_RxTail++ ];
        if( pst_uart->u16_RxTail >= u8_len ) {
                pst_uart->u16_RxTail = 0;
        }
        pst_uart->u16_RxCnts--;
    }
    if( pst_uart->u16_RxTail == pst_uart->u16_RxHead ) {
        pst_uart->u16_RxFlag &= ~UART_IQDIRTY;
    }
}


void Uart_RxHandle( USART_TypeDef* USARTx, UART* pst_uart )
{
    if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET){
          pst_uart->u8_RxBuf[ pst_uart->u16_RxHead++ ] = USART_ReceiveData(USARTx);
          if( pst_uart->u16_RxHead >= UART_RXBUFFSIZE ) {
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
  USART_SendData(USART1, ( INT8U ) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

void Uart1_RxHandle( void )
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
          st_Uart1.u8_RxBuf[ st_Uart1.u16_RxHead++ ] = USART_ReceiveData(USART1);
          if( st_Uart1.u16_RxHead >= UART_RXBUFFSIZE ) {
              st_Uart1.u16_RxHead = 0;
              USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
          }
          st_Uart1.u16_RxCnts++;     
   }        
}

void Uart2_RxHandle( void )
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
          st_Uart2.u8_RxBuf[ st_Uart2.u16_RxHead++ ] = USART_ReceiveData(USART2);
          if( st_Uart2.u16_RxHead >= UART_RXBUFFSIZE ) {
              st_Uart2.u16_RxHead = 0;
              USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
          }
          st_Uart2.u16_RxCnts++;  
  }        
}

void Uart3_RxHandle( void )
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){
          st_Uart3.u8_RxBuf[ st_Uart3.u16_RxHead++ ] = USART_ReceiveData(USART3);
          if( st_Uart3.u16_RxHead >= UART_RXBUFFSIZE ) {
              st_Uart3.u16_RxHead = 0;
              USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
          }
          st_Uart3.u16_RxCnts++;  
  }        
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

/***********************************EOF****************************************/  