/**************************************************** **************************
* File Name          : Main.c
* Author             : Mingfei Tang
* Version            : V1.0.0
* Date               : 2018/2/10
* Description        : for wifi project host
********************************************************************************
*/
#include "Includes.h"
#include "cmsis_os.h"

osThreadId defaultTaskHandle;

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
      System.loop();
      userHandle();
  }
  /* USER CODE END 5 */ 
}

int main(void)
{
    Init_System();
    System.init();
    osThreadDef(defaultTask, 
                StartDefaultTask, 
                osPriorityNormal, 
                0, 
                128);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
    
     userInit();
    /* Start scheduler */
   // osKernelStart();
    vTaskStartScheduler();    
    while (1)
    {

    }
}

/* EOF */
