/*******************************************************************************
** File name:	 stm32hal.c
** Created by:	 Mingfei Tang		
** Created date: 2018/2/20		
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define UINT_MAX    0xFFFFFFFF

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t uwTick;

/* Private function prototypes -----------------------------------------------*/
/* Public functions ---------------------------------------------------------*/
/**
  * @brief This function is called to increment  a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in Systick ISR.
  * @note This function is declared as __weak to be overwritten in case of other 
  *      implementations in user file.
  * @retval None
  */
void HAL_IncTick(void)
{
  uwTick++;
}

/**
  * @brief Provides a tick value in millisecond.
  * @note   This function is declared as __weak  to be overwritten  in case of other 
  *       implementations in user file.
  * @retval tick value
  */
uint32_t HAL_GetTick(void)
{
  return uwTick;
}

/**
  * @brief This function provides accurate delay (in milliseconds) based 
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note ThiS function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay: specifies the delay time length, in milliseconds.
  * @retval None
  */
void HAL_Delay(__IO uint32_t Delay)
{
  uint32_t tickstart = 0;
  tickstart = HAL_GetTick();
  while((HAL_GetTick() - tickstart) < Delay)
  {
  }
}


uint32_t timerGetId(void)
{
    return HAL_GetTick();
}

bool timerIsEnd(uint32_t timerID, uint32_t time)
{
    uint32_t current_millis = timerGetId();
    uint32_t elapsed_millis = 0;

    //Check for wrapping
    if (current_millis < timerID){
        elapsed_millis =  UINT_MAX-timerID + current_millis;
    } else {
        elapsed_millis = current_millis - timerID;
    }

    if (elapsed_millis >= time){
        return TRUE;
    }
    
    return FALSE;
}


/* End of this file */
