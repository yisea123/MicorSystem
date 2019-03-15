/**************************************************** **************************
* File Name          : Main.c
* Author             : Mingfei Tang
* Version            : V1.0.0
* Date               : 2018/2/10
* Description        : for wifi project host
********************************************************************************
*/
#include "Includes.h"

int main(void)
{
    Init_System();
    System.init();
    userInit();
    while (1)
    {
        System.loop();
        userHandle();
    }
}

/* EOF */
