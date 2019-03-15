#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "board.h"
#include "usart.h"
#include "platform_assert.h"
#include "hal.h"
#include "console.h"

osThreadId defaultTaskHandle;

void SystemClock_Config(void);
void StartDefaultTask(void const * argument);

void armfly_Init( void )
{
   board_Init();
   board_LedSetup();
   board_LedSet( board_LedIndicator_1, false );
   console_Init();
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  armfly_Init();
  
  osThreadDef(defaultTask, 
              StartDefaultTask, 
              osPriorityNormal, 
              0, 
              128);
  
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
 
  /* Start scheduler */
  osKernelStart();
  while (1)
  {

  }
}


/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{
  for(;;)
  {
    osDelay(100);
  }
}

