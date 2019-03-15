#ifndef __HW_DEF_H
#define __HW_DEF_H


#define HW_LED_PortConfig() {\
                              RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
                              GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                              GPIO_Init( GPIOB, &GPIO_InitStructure );\
                            }

#define  LED_ON             GPIO_SetBits(GPIOB, GPIO_Pin_0) 	
#define  LED_OFF            GPIO_ResetBits(GPIOB, GPIO_Pin_0) 

#define LED_BLINK( ctrl ){\
                            if( ctrl )   \
                               LED_ON;   \
                             else        \
                               LED_OFF;  \
                         }

/*******************************************************************************/
#define HW_Ctrl_PortConfig(){\
                              RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15|GPIO_Pin_14|\
                                                              GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10|\
                                                              GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
                              GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                              GPIO_Init( GPIOB, &GPIO_InitStructure );\
                            }


#define HW_PWR_ANALOG_Config(){\
    GPIO_InitTypeDef  GPIO_InitStructure;\
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);\
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4|GPIO_Pin_3;\
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
    GPIO_Init( GPIOB, &GPIO_InitStructure );\
}


#define V_FPGA_OFF     	        GPIO_SetBits(GPIOB, GPIO_Pin_15) 
#define V_FPGA_ON     	        GPIO_ResetBits(GPIOB, GPIO_Pin_15) 

#define V_NET_OFF     	        GPIO_SetBits(GPIOB, GPIO_Pin_14) 
#define V_NET_ON     	        GPIO_ResetBits(GPIOB, GPIO_Pin_14) 

#define V_A24V_ON     	        GPIO_SetBits(GPIOB, GPIO_Pin_13) 
#define V_A24V_OFF     	        GPIO_ResetBits(GPIOB, GPIO_Pin_13) 

#define V_S24V_ON     	        GPIO_SetBits(GPIOB, GPIO_Pin_12) 
#define V_S24V_OFF     	        GPIO_ResetBits(GPIOB, GPIO_Pin_12) 

#define V_5V_2A_OFF             GPIO_SetBits(GPIOB, GPIO_Pin_11) 
#define V_5V_2A_ON             GPIO_ResetBits(GPIOB, GPIO_Pin_11) 

#define FPGA_RST_SET     	GPIO_SetBits(GPIOB, GPIO_Pin_5) 
#define FPGA_RST_CLR     	GPIO_SetBits(GPIOB, GPIO_Pin_5) 

#define V_ANALOG_OFF     	GPIO_SetBits(GPIOB, GPIO_Pin_4) 
#define V_ANALOG_ON     	GPIO_ResetBits(GPIOB, GPIO_Pin_4) 

#define V_R485_OFF     	        GPIO_SetBits(GPIOB, GPIO_Pin_3) 
#define V_R485_ON     	        GPIO_ResetBits(GPIOB, GPIO_Pin_3) 

#define M3_WDI_SET              GPIO_SetBits(GPIOB, GPIO_Pin_10)   
#define M3_WDI_CLR              GPIO_ResetBits(GPIOB, GPIO_Pin_10)   

/*******************************************************************************/
#define HW_CHRG_PortConfig() {\
                              RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;\
                              GPIO_Init( GPIOA, &GPIO_InitStructure );\
                            }

#define HW_BAT_LED_PortConfig() {\
                              RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);\
                              GPIO_InitTypeDef  GPIO_InitStructure;\
                              GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;\
                              GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;\
                              GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                              GPIO_Init( GPIOA, &GPIO_InitStructure );\
                            }

#define  BAT_LED_ON         GPIO_SetBits(GPIOA, GPIO_Pin_8) 	
#define  BAT_LED_OFF        GPIO_ResetBits(GPIOA, GPIO_Pin_8) 

#define BAT_LED_BLINK( ctrl ){\
                            if( ctrl )       \
                               BAT_LED_ON;   \
                             else            \
                               BAT_LED_OFF;  \
                         }

#define CHRG_READ           GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_8)       

#define CHRG_STATUS_CHECK        

#endif /* __HW_DEF_H */