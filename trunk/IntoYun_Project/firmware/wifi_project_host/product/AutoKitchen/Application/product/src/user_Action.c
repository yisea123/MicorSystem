/**
********************************************************************************
  * @file    Src/user/Ctrl_Action.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/04/11
  * @brief   system ctrl interface
  * @documents
  ******************************************************************************
  */
/* Includes -------------------------------------------------------------------*/
#include "includes.h"
#include "user_Action.h"
#include "platform_def.h"
#include "Interface_kitchen.h"

/* Private typedef ------------------------------------------------------------*/
/* Private define -------------------------------------------------------------*/ 
/* Private macro --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
static CtrL_typedef st_CtrlTypdef;

/* Private function prototypes ------------------------------------------------*/

void vCtrlAction_Init( void )
{
    Ctrl_MotorKitchenInit();
}

void vCtrlAction_SetPara(uint8_t dev_type ,uint8_t id, uint8_t *ctrlRes, uint8_t length )
{
    CtrL_typedef *pCtrlTypdef;

    pCtrlTypdef = &st_CtrlTypdef;
    memcpy( pCtrlTypdef->b_ctrlres, ctrlRes, length);
    pCtrlTypdef->addres = 0xff;
    vCloud_RefreshCtrlStatus( id, ctrlRes, length);
    
    switch( id )
    {
        case DPID_YUN_ID_1:
           pCtrlTypdef->addres = MOROT_LEVEL_ADD; 
           Ctrl_MotorKitchenStart( pCtrlTypdef->b_ctrlres[0]);
        break;
    }

    pCtrlTypdef->dev_type = dev_type;
}

/* 100 ms action */
void vCtrlMotorAction_Process( void )
{
    CTRL_RESULT_ENUM e_res;
    
    if(st_CtrlTypdef.addres == NULL_ADDR ||
       st_CtrlTypdef.addres == 0)
      return;
    
    /* control motor */
    if( st_CtrlTypdef.addres == MOROT_LEVEL_ADD ) 
    {
        e_res = Ctrl_MotorKitchenInterface();
        if( e_res == CTRL_OK )
        {
            st_CtrlTypdef.addres = NULL_ADDR;
        }
    }  
}

const vCtrlAction_t mainCtrl =
{
    vCtrlAction_Init,
    vCtrlAction_SetPara,
    vCtrlMotorAction_Process,
};

/*End of this file */
