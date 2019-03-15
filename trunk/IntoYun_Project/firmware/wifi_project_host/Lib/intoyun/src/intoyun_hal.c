/*******************************************************************************
** File name:	 intoyun_hal.c
** Created by:	 Mingfei Tang		
** Created date: 2018/2/21		
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
#include "Includes.h"
#include "intoyun_interface.h"
#include "intoyun_protocol.h"
#include "intoyun_hal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define Wifi_Printf              UART4_Put
#define WIFI_UART                UART4

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Public functions ---------------------------------------------------------*/
uint32_t HAL_Millis(void)
{
    return HAL_GetTick();
}

void HAL_WifiReset( void )
{
    WIFI_REST_LOW;
    HAL_Delay( 300 );
    WIFI_REST_HIGH;
    HAL_Delay( 300 );
}

//for debug
void HAL_Print(char *data, uint16_t len)
{
   Debug_Printf( (INT8U*)data, len);
}

void HAL_SystemInit(void)
{
    HAL_WifiReset();
}

void HAL_WifWrite(uint8_t data)
{
    Wifi_Printf( &data, 1);
}

void HAL_WifiModeInterrupt( void )
{
    uint8_t data;
    
    if(USART_GetITStatus(WIFI_UART, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(WIFI_UART);
        System.putPipe(data);
    }  
}

void userInterfaceLoop(void)
{
    // Key.loop();
    Timer.loop();
}

/* End of this file */
