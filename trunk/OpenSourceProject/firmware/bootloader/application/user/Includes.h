#ifndef __INCLUDES_H
#define __INCLUDES_H
/*
********************************************************************************
*                                         STANDARD LIBRARIES
********************************************************************************
*/
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "TypeDef.h"
#include "App.h"
#include "stm32f10x.h"

/*
********************************************************************************
*                        LIBRARIES
********************************************************************************
*/
#include "Util.h"
#include "TM_util.h"

/*
********************************************************************************
*                         STM32F10X_Driver
********************************************************************************
*/
#include "Stm32hal.h"
#include "USART.h"
#include "WDG.h"
#include "ADC.h"
#include "RTC.h"
#include "SPIx.h"
#include "Timer.h"
#include "IAP.h"
/*
********************************************************************************
*                        devices
********************************************************************************
*/
#include "WQ25XX.h"  

/*
********************************************************************************
*                         Application 
********************************************************************************
*/
#include "Init.h"
#include "board.h"
#include "SysCfg.h"
#include "state.h"
#include "fw_upload.h"


#endif /* __INCLUDES_H */