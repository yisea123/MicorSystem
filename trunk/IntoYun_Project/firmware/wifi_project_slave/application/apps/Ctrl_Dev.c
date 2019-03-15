/**************************************************** **************************
* File Name          : Main.c
* Author             : Mingfei Tang
* Version            : V1.0.0
* Date               : 2018/02/25
* Description        : for wifi project slave
********************************************************************************
*/
#include "Includes.h"
#include "util.h"

/* Private typedef ------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static bool ModBus_ParserDataPacket( uint8_t *tarbuff, Ctr_Modbus_TypeDef *pCtr_Modbus);
static bool ModBus_ActionResponse(Ctr_Modbus_TypeDef *pCtr_Modbus );
/**
  * @brief 设备控制Modbus接口
  * @param id,设备控制地址
  * @retval None
  * @example ID 自定义
  */
static void ModBus_CtrInterface( Ctr_Modbus_TypeDef *pCtr_Modbus ) 
{
  uint8_t Cmd[9] = {0x01,  0x05,  0,  0,  0,  0,  0,  0, 0};
  uint8_t pkt_len;
  uint16_t crc;

  pkt_len = sizeof( Cmd );
  Cmd[0] = pCtr_Modbus->addres;
  
  //value
  Cmd[4] = pCtr_Modbus->devType;
    //result
  Cmd[5] = pCtr_Modbus->cmd;
  
  //calcrate crc16
  crc = UTL_ChkCrc16( Cmd, 6);
  
  //refres CRC16
  Cmd[6] = ((crc >> 8)&0xff);
  Cmd[7] = crc&0xff; 
  HAL_485WriteSerial( Cmd, pkt_len );
}

static bool ModBus_ParserDataPacket( uint8_t *tarbuff, Ctr_Modbus_TypeDef *pCtr_Modbus)
{
    uint16_t crc, calCrc;
    
    //Check crc
    calCrc = tarbuff[6]<<8|tarbuff[7];
    crc = UTL_ChkCrc16( tarbuff, 6);
    if( calCrc == crc )
    {
      pCtr_Modbus->addres = tarbuff[0];
      pCtr_Modbus->devType = tarbuff[4];
      pCtr_Modbus->cmd = tarbuff[5];
      return TRUE;
    }
    
    return FALSE;
}

static bool ModBus_ActionResponse(Ctr_Modbus_TypeDef *pCtr_Modbus )
{
  bool b_resp = FALSE;
  
  switch( pCtr_Modbus->addres )
  {
  case LED_1_ADD:
    b_resp = TRUE;
    break;
  case LED_2_ADD:
    b_resp = TRUE;
    break; 
  case CORRIDOR_ADD:
    b_resp = TRUE;
    break;
  case LAZYBACK_ADD:
    b_resp = TRUE;
    break;
  case DESK_ADD:
    b_resp = TRUE;
    break;
   default:
    break;
  }
  
  //Refresh result
  if( b_resp == FALSE )
  {
     pCtr_Modbus->cmd = RES_FAIL;
  }
  else
  {
     pCtr_Modbus->cmd = RES_OK;
  }
  ModBus_CtrInterface( pCtr_Modbus);
  
  return b_resp;
}


bool ModBus_ActionProcess( void )
{
    bool res = FALSE;
    Ctr_Modbus_TypeDef st_Ctr_Modbus;
    UART *pUart = &st_Uart1;
    
    if( pUart->u16_RxHead >= 8 )
    {
        res = ModBus_ParserDataPacket( pUart->u8_RxBuf, &st_Ctr_Modbus );
        pUart->u16_RxHead = 0;
        memset(&st_Uart1, 0, sizeof(UART));   
    }

   if( res == TRUE )
   {
       return ModBus_ActionResponse( &st_Ctr_Modbus );
   }

   return FALSE;
}

/* End of this file */
