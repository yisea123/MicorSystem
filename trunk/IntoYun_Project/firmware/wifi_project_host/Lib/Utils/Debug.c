/*
*********************************************************************************************************
*
*                            THE LIBRARY OF DEBUG     
*
* Filename      : DEBUG.c
* Version       : V1.00
* Programmer(s) : Mingfei Tang
* DATE          : 09/05/2011
*********************************************************************************************************
*/
#include "includes.h"

#if ( DEBUG_EN > 0)

void (*_db_msg)(USART_TypeDef *UARTx, const void *s);
void (*_db_msg_)(USART_TypeDef *UARTx, const void *s);
void (*_db_char)(USART_TypeDef *UARTx, INT8U ch);
void (*_db_dec)(USART_TypeDef *UARTx, INT8U decn);
void (*_db_dec_16)(USART_TypeDef *UARTx, INT16U decn);
void (*_db_dec_32)(USART_TypeDef *UARTx, INT32U decn);
void (*_db_hex)(USART_TypeDef *UARTx, INT8U hexn);
void (*_db_hex_16)(USART_TypeDef *UARTx, INT16U hexn);
void (*_db_hex_32)(USART_TypeDef *UARTx, INT32U hexn);
INT8U (*_db_get_char)(USART_TypeDef *UARTx);


void UARTPutChar ( USART_TypeDef* USARTx, INT8U u8_Data )
{
    USART_SendData( USARTx, ( INT8U )u8_Data );
    while( USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET ){}	
}


INT8U UARTGetChar (USART_TypeDef *USARTx)
{
    while( USART_GetFlagStatus( USARTx,USART_FLAG_RXNE )==RESET ){}
    return( USART_ReceiveData( USARTx ) );   
}

void UARTPuts(USART_TypeDef *UARTx, const void *str)
{
    INT8U *s = (INT8U *) str;
    
    while (*s){
        UARTPutChar(UARTx, *s++);
    }
}

void UARTPuts_(USART_TypeDef *UARTx, const void *str)
{
    UARTPuts (UARTx, str);
    UARTPuts (UARTx, "\n\r");
}

void UARTPutDec(USART_TypeDef *UARTx, INT8U decnum)
{
    INT8U c1=decnum%10;
    INT8U c2=(decnum/10)%10;
    INT8U c3=(decnum/100)%10;
    
    UARTPutChar(UARTx, '0'+c3);
    UARTPutChar(UARTx, '0'+c2);
    UARTPutChar(UARTx, '0'+c1);
}

void UARTPutDec16(USART_TypeDef *UARTx, INT16U decnum)
{
    INT8U c1=decnum%10;
    INT8U c2=(decnum/10)%10;
    INT8U c3=(decnum/100)%10;
    INT8U c4=(decnum/1000)%10;
    INT8U c5=(decnum/10000)%10;
    
    UARTPutChar(UARTx, '0'+c5);
    UARTPutChar(UARTx, '0'+c4);
    UARTPutChar(UARTx, '0'+c3);
    UARTPutChar(UARTx, '0'+c2);
    UARTPutChar(UARTx, '0'+c1);
}

void UARTPutDec32(USART_TypeDef *UARTx, INT32U decnum)
{
    INT8U c1=decnum%10;
    INT8U c2=(decnum/10)%10;
    INT8U c3=(decnum/100)%10;
    INT8U c4=(decnum/1000)%10;
    INT8U c5=(decnum/10000)%10;
    INT8U c6=(decnum/100000)%10;
    INT8U c7=(decnum/1000000)%10;
    INT8U c8=(decnum/10000000)%10;
    INT8U c9=(decnum/100000000)%10;
    INT8U c10=(decnum/100000000)%10;
    
    UARTPutChar(UARTx, '0'+c10);
    UARTPutChar(UARTx, '0'+c9);
    UARTPutChar(UARTx, '0'+c8);
    UARTPutChar(UARTx, '0'+c7);
    UARTPutChar(UARTx, '0'+c6);
    UARTPutChar(UARTx, '0'+c5);
    UARTPutChar(UARTx, '0'+c4);
    UARTPutChar(UARTx, '0'+c3);
    UARTPutChar(UARTx, '0'+c2);
    UARTPutChar(UARTx, '0'+c1);
}

void UARTPutHex (USART_TypeDef *UARTx, INT8U hexnum)
{
    INT8U nibble, i;

    UARTPuts(UARTx, "0x");
    i = 1;
    do {
        nibble = (hexnum >> (4*i)) & 0x0F;
        UARTPutChar(UARTx, (nibble > 9) ? ('A' + nibble - 10) : ('0' + nibble));
    } while (i--);
}

void UARTPutHex16 (USART_TypeDef *UARTx, INT16U hexnum)
{
    INT8U nibble, i;

    UARTPuts(UARTx, "0x");
    i = 3;
    do {
        nibble = (hexnum >> (4*i)) & 0x0F;
        UARTPutChar(UARTx, (nibble > 9) ? ('A' + nibble - 10) : ('0' + nibble));
    } while (i--);
}

void UARTPutHex32 (USART_TypeDef *UARTx, INT32U hexnum)
{
    INT8U nibble, i;
    
    UARTPuts(UARTx, "0x");
    i = 7;
    do {
        nibble = (hexnum >> (4*i)) & 0x0F;
        UARTPutChar(UARTx, (nibble > 9) ? ('A' + nibble - 10) : ('0' + nibble));
    } while (i--);
}

void DebugInit( void )
{
    _db_msg    = UARTPuts;
    _db_msg_   = UARTPuts_;
    _db_char   = UARTPutChar;
    _db_hex    = UARTPutHex;
    _db_hex_16 = UARTPutHex16;
    _db_hex_32 = UARTPutHex32;
    _db_dec    = UARTPutDec;
    _db_dec_16 = UARTPutDec16;
    _db_dec_32 = UARTPutDec32;
    _db_get_char = UARTGetChar;
}

#endif 

