/** \file

$Id: uart_local.h 40486 2018-09-20 05:50:21Z tangmingfei2013@126.com $

Copyright (c) 2018 tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/

/******************************************************************************
* EXTERNAL INCLUDE FILES
******************************************************************************/
#ifndef __UART_LOCAL_H
#define __UART_LOCAL_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/
#include "stm32f4xx_hal.h"
#include "board.h"

/*!
 * @brief Interface to the USARTs / COM ports, abstracting from Stm32Lib
 *
 * An STM32 variant has 3 or 5 USARTs. A board can connect any of these. The
 * connected USARTs are identified by COM port numbers. E.g., a board could
 * connect only USART 2, which then would be identified by COM port 1. The
 * board-specified correspondence between COM ports and USARTs is defined in
 * boarddiv.[ch].
 */

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
  
/******************************************************************************
* EXPORTED MACROS AND CONSTANTS
******************************************************************************/
#ifdef __GNUC__
  /* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */  
  
#define USART_RX_BUF_SIZE   1
#define USART_TX_BUF_SIZE   1  
/*!
 * @brief USART channels: Tx (DMA) and/or Rx
 */
typedef enum usart_Channel_t
{
    usart_ChannelTx    = 1,     //!< Transmitter channel
    usart_ChannelRx    = 2,      //!< Receiver channel
    usart_ChannelTxDma = 4,      //!< Transmitter channel via DMA
    usart_ChannelTxComplete = 8  //!< Transmission via the Tx line physically completed
} usart_Channel_t;

/*!
 * @brief USART transmitter state
 */
typedef enum usart_TxState_t
{
    usart_TxState_Running,      //!< Transmission ongoing
    usart_TxState_Stopped,      //!< Transmission just stopped
    usart_TxState_Idle          //!< Transmission idle
} usart_TxState_t; 

/*!
 * @brief A USART instance object
 */
typedef struct usart_t
{
    const struct board_Usart_t* pBrdStruct;                         //!< Board descriptor
    void               (*isr)( uint32_t, usart_Channel_t chan );    //!< Client handler
    uint32_t            isrParam;                                   //!< Parameter into \p isr
    bool                usesDma;                                    //!< If \p true, DMA is used
    usart_TxState_t     txState;                                    //!< The transmitter state
    uint8_t             pRxBuf[USART_RX_BUF_SIZE];                  //!< Receiver buffer
    uint8_t             pTxBuf[USART_TX_BUF_SIZE];                  //!< Transmitter buffer
} usart_t;  
  
/*!
 * @brief On-chip COM peripheral descriptor
 */
typedef struct usart_Peripheral_t
{
    UART_HandleTypeDef  *peripheral;           //!< Address of peripheral
    //uint32_t          peripheralId;          //!< RCC peripheral Id
    DMA_Stream_TypeDef*    const dmaTxChannel; //!< DMA channel associated
    uint32_t            dmaRequest;
    //uint32_t          dmaBitMask;            //!< DMA interrupt bitmask
    IRQn_Type           usartIrqId;            //!< Interrupt Id of the usart
    IRQn_Type           dmaIrqId;              //!< Interrupt Id of DMA
} usart_Peripheral_t;

/******************************************************************************
* EXPORTED MACROS AND CONSTANTS
******************************************************************************/

/*!
 * @brief Descriptor for USART1
 */
extern const usart_Peripheral_t g_usart_USART1;
/*!
 * @brief Descriptor for USART2
 */
extern const usart_Peripheral_t g_usart_USART2;
/*!
 * @brief Descriptor for USART3
 */
extern const usart_Peripheral_t g_usart_USART3;

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // __UART_LOCAL_H
