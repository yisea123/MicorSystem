/**************************************************** **************************
* File Name          : Main.c
* Author             : Mingfei Tang
* Version            : V1.0.0
* Date               : 2018/02/25
* Description        : for wifi project slave
********************************************************************************
*/
#include "Includes.h"

static uint32_t timer50msID;
static uint32_t timer1000msID;

static void userHandle (void)
{ 
   if( timerIsEnd(timer50msID, 50))
   {
      timer50msID = timerGetId();
      ModBus_ActionProcess();
   }
   
   if( timerIsEnd(timer1000msID, 1000))
   {
      timer1000msID = timerGetId();
      Board_LedBlink();
   }
}
   
int main(void)
{
    Init_System();
    while (1)
    {
        userHandle();
    }
}
/* EOF */
