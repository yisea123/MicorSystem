/** \file

$Id: i2c.h 40486 2018-09-26 6:59:21Z tangmingfei2013@126.com $

Copyright (c) tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/
#ifndef __I2C_H
#define __I2C_H

/******************************************************************************
* EXTERNAL INCLUDE FILES
******************************************************************************/
#include "board.h"
#include "i2c_Init.h"

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
  
/******************************************************************************
* EXPORTED TYPES
******************************************************************************/
typedef enum
{
  I2C_OK       = 0x00U,
  I2C_ERROR,
  I2C_BUSY,
  I2C_TIMEOUT
} I2C_StatusDef;

typedef enum
{
  I2C_IRQ_EVENT       = 0x00U,
  I2C_IRQ_ERROR
} I2C_IrqDef;

typedef void (*i2c_ReadCb_t)(void *pHandler, uint8_t *pRawData,
                             uint16_t len, I2C_StatusDef status);
typedef void (*i2c_WriteCb_t)(void *pHandler, I2C_StatusDef status);
typedef void (*i2c_CustomizedIrqHandler_t)(I2C_HandleTypeDef *hi2c,
                                           I2C_IrqDef irqType);


/*!
 * @brief A I2C instance object
 */
typedef struct i2c_t
{
  board_I2cInfo_t                     *pBrdStruct;
  I2C_HandleTypeDef                   I2CHandle;
  bool                                bInit;
  bool                                usesDma;  //!< If \p true, DMA is used
  DMA_HandleTypeDef                   hdma_tx;
  DMA_HandleTypeDef                   hdma_rx;
  void                                *pUserHandler;
  i2c_ReadCb_t                        rdCb;
  i2c_WriteCb_t                       wrCb;
  uint8_t                             *pRdBuf;
  uint16_t                            rdDataLen;
  bool                                rdDone;
  uint8_t                             *pWrBuf;
  uint16_t                            wrDataLen;
  bool                                wrDone;
  bool                                usesCustomizedIrqHandler;
  i2c_CustomizedIrqHandler_t          customizedIrqHandler;
} i2c_t;

typedef struct i2c_t *I2C_HANDLE;

/******************************************************************************
* EXPORTED MACROS AND CONSTANTS
******************************************************************************/

#define I2C_INDEX1       0
#define I2C_INDEX2       1
#define I2C_INDEX3       2
#define I2C_INDEX_COUNT  3
#define DEFAULT_SLAVE_HARDWARE_ADDRESS    0xEE

/*!
 * @brief Named i2c devices
 */
#define I2C_1 &g_i2c[I2C_INDEX1]
#define I2C_2 &g_i2c[I2C_INDEX2]
#define I2C_3 &g_i2c[I2C_INDEX3]

/*!
 * @brief The list of (unnamed) i2c devices
 */
extern const i2c_peripheral_t g_i2c[];


/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void i2c_InitPort(  const board_I2cInfo_t *const pBrdStruct, bool useDma, i2c_t *pi2c_t);
I2C_StatusDef i2c_master_sync_read_with_index(i2c_t *pI2C,uint8_t devAddr,uint16_t regAddr,uint8_t  regAddrLen,uint8_t *pRdBuf,uint16_t bufRdLen);
I2C_StatusDef i2c_master_sync_write_with_index(i2c_t *pI2C,uint8_t devAddr,uint16_t regAddr,uint8_t  regAddrLen,uint8_t *pWrBuf, uint16_t bufWrLen);

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H */  
