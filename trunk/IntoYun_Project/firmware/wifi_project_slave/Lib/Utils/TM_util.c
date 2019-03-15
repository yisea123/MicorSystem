/*******************************************************************************
** File name:	 TM_util.c
** Created by:	 Mingfei Tang		
** Created date: 2016/1/20		
** Version:	 V1.00			
** Descriptions:
**
**------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*******************************************************************************/
#include "includes.h"

//#pragma optimize = s none                // no optimize for speed
void TM_Delay( INT32U delay )
{
   while ( delay-- );
}


//#pragma optimize = s none                // no optimize for speed
void TM_Delay_us( INT32U delay )
{
   while ( delay-- ){
	Delay1US();
   }
}

//#pragma optimize = s none                // no optimize for speed
void TM_Delay_ms( INT32U delay )
{
   while ( delay-- ) {
	TM_Delay_us( 1000 );
    }
}

//#pragma optimize = s none                // no optimize for speed
INT32U TM_Check( INT32U count, INT32U (*check)(void) )
{
   while ( count-- ) {
      if ( check() == 1 ) {
	  return 1;               // reach condition
      }
   }
   return 0;                          // Timeout
}

/* EOF */