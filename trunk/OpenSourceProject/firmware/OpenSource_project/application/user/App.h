#ifndef __APP_H
#define __APP_H

#define STM32RES_GOT                0x0001
#define FPGACM3_GOT                 0x0002

#define COMM_CAN1CTRLREQ            0x0001
#define COMM_CAN1CTRLRSP            0x0002
#define COMM_UART1                  0x0004
#define COMM_UART2                  0x0008
#define COMM_UART3                  0x0010
#define COMM_I2C		    0x0020
#define COMM_CAN1		    0x0040
#define COMM_UART4                  0x0080

typedef struct {
    INT16U TM_500MS_TICK	:1;
    INT16U TM_1000MS_TICK	:1;
    INT16U TM_10MS_TICK	        :1;
    INT16U TM_300MS_TICK        :1;
    INT16U TM_300MS_ACT         :1;
    INT16U TM_500MS_ACT	        :1;
    INT16U TM_1000MS_ACT	:1;
    INT16U TM_10MS_ACT	        :1;
    INT16U TM_30S_ACT          :1;
    INT16U                      :1;
    INT16U 	                :1;
    INT16U 			:1;
    INT16U 		        :1;
    INT16U 			:1;
    INT16U 			:1;
    INT16U 			:1;
} __timeFlags_bits;

typedef struct {
    INT16U 	                :1;
    INT16U 	                :1;
    INT16U CF_UART0		:1;
    INT16U CF_UART2		:1;
    INT16U CF_UART3		:1;
    INT16U CF_I2C		:1;
    INT16U WDTCTRL		:1;	
    INT16U 	                :1;
    INT16U 	                :1;	
    INT16U 	                :1;
    INT16U 	                :1;
    INT16U 			:1;
    INT16U 			:1;
    INT16U 			:1;
    INT16U 			:1;
    INT16U 			:1;
} __commFlags_bits;

typedef struct msg{
    INT16U_BIT(TimeFlags, __timeFlags_bits);
    INT16U_BIT(CommFlags, __commFlags_bits);
    INT16U :16;
    INT16U u16_CommFlag;
    INT16U u16_STM32RspFlg;
} MSG;

extern MSG st_SysMsg;


#endif /* __APP_H*/