#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "board.h"
#include "usart.h"
#include "platform_assert.h"
#include "hal.h"
#include "console.h"
#include "spiflash.h"
#include "veml6030.h"
#include "hts221.h"

osThreadId defaultTaskHandle;

void SystemClock_Config(void);
void StartDefaultTask(void const * argument);

void armfly_Init( void )
{
   board_Init();
   board_LedSetup();
   board_LedSet( board_LedIndicator_1, true );
   board_LedSet( board_LedIndicator_2, true );
   console_Init();
   spiflash_Init(); 
   hts221_Init();
   veml6030_Init();
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
    osDelay(1000);
  }
}

/* End of this file */
