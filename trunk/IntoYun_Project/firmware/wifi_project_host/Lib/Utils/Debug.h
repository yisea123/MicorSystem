#ifndef __DEBUG_H
#define __DEBUG_H

#define USED_UART_DEBUG_PORT	PORT_UART1

#if ( USED_UART_DEBUG_PORT == PORT_UART1 )
#define DEBUG_UART_PORT     USART1
#elif ( USED_UART_DEBUG_PORT == PORT_UART2 )
#define DEBUG_UART_PORT     USART2
#endif

#define _DBG(x)	 	_db_msg(DEBUG_UART_PORT, x)
#define _DBG_(x)	_db_msg_(DEBUG_UART_PORT, x)
#define _DBC(x)	 	_db_char(DEBUG_UART_PORT, x)
#define _DBD(x)	 	_db_dec(DEBUG_UART_PORT, x)
#define _DBD16(x)	_db_dec_16(DEBUG_UART_PORT, x)
#define _DBD32(x)	_db_dec_32(DEBUG_UART_PORT, x)
#define _DBH(x)	 	_db_hex(DEBUG_UART_PORT, x)
#define _DBH16(x)	_db_hex_16(DEBUG_UART_PORT, x)
#define _DBH32(x)	_db_hex_32(DEBUG_UART_PORT, x)
#define _DG		_db_get_char(DEBUG_UART_PORT)


extern void (*_db_msg)(USART_TypeDef *UARTx, const void *s);
extern void (*_db_msg_)(USART_TypeDef *UARTx, const void *s);
extern void (*_db_char)(USART_TypeDef *UARTx, INT8U ch);
extern void (*_db_dec)(USART_TypeDef *UARTx, INT8U decn);
extern void (*_db_dec_16)(USART_TypeDef *UARTx, INT16U decn);
extern void (*_db_dec_32)(USART_TypeDef *UARTx, INT32U decn);
extern void (*_db_hex)(USART_TypeDef *UARTx, INT8U hexn);
extern void (*_db_hex_16)(USART_TypeDef *UARTx, INT16U hexn);
extern void (*_db_hex_32)(USART_TypeDef *UARTx, INT32U hexn);
extern INT8U (*_db_get_char)(USART_TypeDef *UARTx);


void DebugInit( void );  


void  UARTPutChar ( USART_TypeDef* USARTx, INT8U u8_Data );
INT8U UARTGetChar (USART_TypeDef *UARTx);
void UARTPuts(USART_TypeDef *UARTx, const void *str);
void UARTPuts_(USART_TypeDef *UARTx, const void *str);
void UARTPutDec(USART_TypeDef *UARTx, INT8U decnum);
void UARTPutDec16(USART_TypeDef *UARTx, INT16U decnum);
void UARTPutDec32(USART_TypeDef *UARTx, INT32U decnum);
void UARTPutHex (USART_TypeDef *UARTx, INT8U hexnum);
void UARTPutHex16 (USART_TypeDef *UARTx, INT16U hexnum);
void UARTPutHex32 (USART_TypeDef *UARTx, INT32U hexnum);

#endif
