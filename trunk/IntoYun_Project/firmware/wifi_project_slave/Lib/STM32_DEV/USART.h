#ifndef __UART_H
#define __UART_H

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


typedef struct Uart_Socket UART;
struct Uart_Socket {
   INT16U u16_RxFlag;
   INT16U u16_RxHead;
   INT16U u16_RxTail;
   INT16U u16_RxCnts;
   INT8U u8_RxBuf[UART_RXBUFFSIZE];
};
extern UART st_Uart1;
extern UART st_Uart2;
extern UART st_Uart3;

void UART_Init( UART pst_Uart, INT8U u8_port, INT32U u32_bdr );
void USART_SendByte( USART_TypeDef* USARTx,INT8U u8_Data );
INT8U USART_GetByte( USART_TypeDef* USARTx );
void USART_SendStr(USART_TypeDef* USARTx,INT8U* data,INT16U u16_len);
void UART1_Put( INT8U* pu8_buf, INT16U u16_len );

void UART2_Put( INT8U* pu8_buf, INT16U u16_len );
void UART_Puts( USART_TypeDef* USARTx, INT8U* s );
void UART_Getc( UART* pst_uart, INT8U* pu8_buf );
void UART4_Put( INT8U* pu8_buf, INT16U u16_len );
void Uart_RxHandle( USART_TypeDef* USARTx, UART* pst_uart );
void UART3_Put( INT8U* pu8_buf, INT16U u16_len );

int ser_printf (USART_TypeDef* USARTx, int c) ;
int ser_scanf (USART_TypeDef* USARTx) ;

void UART2_Get( INT8U* pu8_buf, INT8U u8_len );

void Uart1_RxHandle( void );
void Uart2_RxHandle( void );
void Uart3_RxHandle( void );

#endif   /* __UART_H */