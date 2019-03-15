/*******************************************************************************

 	            Error Reporting System

   (C) Copyright 2006, RAE Systems Inc. 	 All rights reserved

--------------------------------------------------------------------------------

     File name: ERR_sys.C
      Hardware: ARM7TDMI
     Reference:

--------------------------------------------------------------------------------

   == Important Note ==

   . ERR_Code is a 4-byte variable and has bit definition shown below
        b0~b7: error flags
       b8~b15: MCU error source
      b16~b31: app-defined error flags

--------------------------------------------------------------------------------
*******************************************************************************/


#include "Includes.h"

static INT32U ERR_Code = ERROR_NONE;


INT32U ERR_GetCode( void )
{
   INT32U temp;

   temp = ERR_Code;
   ERR_Code = ERROR_NONE;
   return temp;
}

INT32U ERR_PeekCode( void )
{
   return ERR_Code;
}

void ERR_SetCode( INT32U error )
{
   ERR_Code = error;
}



