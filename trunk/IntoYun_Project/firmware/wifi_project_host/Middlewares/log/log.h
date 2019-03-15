/** \file

$Id: log.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __LOG_H
#define __LOG_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/ 
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
 
void log_printf(char *pkt, uint8_t *buf, uint16_t len);  
void log_printstring( char *pkt, uint8_t *str );  

#ifdef __cplusplus
}
#endif

#endif   /* __LOG_H */