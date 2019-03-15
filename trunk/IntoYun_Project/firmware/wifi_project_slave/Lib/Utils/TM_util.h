#ifndef __TM_UTIL_H__
#define __TM_UTIL_H__

#define NOP 			{ __no_operation(); }  
/************************* System Delay Definiton  ****************************/
#define Delay1US()   {        \
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;  NOP;\
                        NOP;  NOP;  \
                     }
#define Delay5US()   { Delay1US(); Delay1US(); Delay1US(); Delay1US(); Delay1US(); }
/******************************************************************************/
void TM_Delay( INT32U delay );
void TM_Delay_us( INT32U delay );
void TM_Delay_ms( INT32U delay );
INT32U TM_Check( INT32U count, INT32U (*check)(void) );


#endif  
