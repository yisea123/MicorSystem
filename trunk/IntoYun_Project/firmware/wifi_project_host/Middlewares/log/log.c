/** \file

$Id: log.c 40486 2018-08-28 20:50:21 tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "includes.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "log.h"

#define DEBUG_ENABLE                      0

void log_failed(const char *file, uint16_t line) 
{
    printf("Program failed in file: %s, line: %d\r\n", file, line);
    while(1) 
    {
      
    }
}

void log_printf(char *pkt, uint8_t *buf, uint16_t len)
{
#if DEBUG_ENABLE
    uint8_t i;
    
    printf(pkt);
    printf(": ");
    if( len > 0 )
    {
        for(i = 0; i < len; i++) 
        {
            printf("%02x ", buf[i]);
        }
        printf("\r\n");
    }
#endif
}

void log_printstring( char *pkt, uint8_t *str )
{
#if DEBUG_ENABLE
    printf(pkt);
    printf(": ");
    printf((char*)str);
    printf("\r\n");
 #endif   
}


/* End of this file */