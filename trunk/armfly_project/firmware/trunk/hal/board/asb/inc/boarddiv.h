/** \file

$Id: boarddiv.h 40486 2018-09-15 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef _BOARDDIV_H
#define _BOARDDIV_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/  

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 
/*!
 * @brief Number of LEDs
 */
#define BOARDDIV_LED_NUM        2
  
/*!
 * @brief Number of UART
 */
#define BOARDDIV_COMPORT_NUM     3         

/*!
 * @brief Number of SPI ports
 */
#define BOARDDIV_SPI_NUM         1
  
  
/*!
 * @brief Number of I2C busses
 */
#define BOARDDIV_I2C_NUM         3

  
/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/



/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _BOARDDIV_H */ 






