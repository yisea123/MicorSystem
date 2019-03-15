/** \file

$Id: board.h 40486 2018-09-15 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef _BOARD_H
#define _BOARD_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/  
#if defined (HAL_STM32F1)
#include "stm32f10x.h"
#endif

#if defined ( HAL_STM32F4 )
#include "stm32f4xx_hal.h"
#endif

#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "boarddiv.h"
#include "gpio.h"

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
  
/******************************************************************************
* EXPORTED TYPES
******************************************************************************/
/*!
 * @brief Descriptor for a COM port which is implemented by a Usart
 */
typedef struct board_Usart_t
{
    const struct usart_Peripheral_t* pPeripheral;
    gpio_Pin_t rx;         //!< The Rx pin
    gpio_Pin_t tx;         //!< The Tx pin
    uint8_t    usartIndex; //!< USART number: 0 for USART1, 1 for USART2, etc.
} board_Usart_t;

/*!
 * @brief Descriptor for a Spi port implementation
 */
typedef struct board_SpiInfo_t
{
    gpio_Pin_t  sck;   //!< The SCK  pin
    gpio_Pin_t  miso;  //!< The MISO pin
    gpio_Pin_t  mosi;  //!< The MOSI pin
    gpio_Pin_t  nss;   //!< The NSS  pin
    
    uint32_t     remap;       //!< Alternate function mode of SPI pins
    SPI_TypeDef *peripheral;  //!< The SPI peripheral associated with this bus
    bool       hwnss;         //!< NSS pin enabled in Alternate function hardware (false means software controlled)  

} board_SpiInfo_t;

/*!
 * @brief Board information on I2C busses
 */
typedef struct board_I2cInfo_t
{
    I2C_TypeDef     *Instance;
    //! Peripheral
    //! SDA
    gpio_Pin_t sda;
    //! SCL
    gpio_Pin_t scl;
    
    uint8_t    i2cIndex; //!< i2c number: 0 for I2C1, 1 for I2C1, etc.
} board_I2cInfo_t;

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 
/*!
 * @brief LED identification
 *
 * @note Upon adding a board that has more LEDs than described here,
 *       an extra identifier must be added.
 */
typedef enum board_LedIndicator_t
{
    board_LedIndicator_1 = 0,
    board_LedIndicator_2,
    board_LedIndicator_3,
    board_LedIndicator_4,
    board_LedIndicator_5
} board_LedIndicator_t;

typedef enum board_I2c_t
{
    board_I2c_1 = 0,
    board_I2c_2,
    board_I2c_3
} board_I2c_t;

/*!
 * @brief SPI bus identification
 *
 * @note Upon adding a board that has more devices than described here,
 *       an extra identifier must be added.
 */
typedef enum board_Spi_t
{
    board_Spi_NA = 0xFF
#if BOARDDIV_SPI_NUM > 0
  , board_Spi_1 = 0
#endif
} board_Spi_t;


/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void board_Init( void );  

#if BOARDDIV_LED_NUM > 0

void board_LedSetup( void );
void board_LedSet( board_LedIndicator_t x, bool s );

#endif


#if BOARDDIV_SPI_NUM > 0

void board_SpiSetup( board_Spi_t i );
void board_SpiSlaveSelectSet( board_Spi_t i, bool s );
SPI_TypeDef* board_SpiGetPeripheral( board_Spi_t i );
#endif

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _BOARD_H */ 