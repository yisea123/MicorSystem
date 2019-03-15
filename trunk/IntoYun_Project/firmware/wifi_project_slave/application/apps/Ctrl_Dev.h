#ifndef __CTRL_DEV_H
#define __CTRL_DEV_H

#define RES_OK        0x01
#define RES_FAIL      0x02

typedef enum
{
  MOROT_ADD = 1,                  // MOTOR
  CORRIDOR_ADD = 11,
  LAZYBACK_ADD = 12,
  DESK_ADD = 13,
  LED_1_ADD = 21,                 // led 1
  LED_2_ADD = 22,                 // led 2
  NULL_ADDR = 0XFF
}device_addr_enum;

typedef struct
{
  uint8_t cmdID;       /* devices add */
  bool b_ctrlres;     /* control status */
}Ctr_Device;

typedef struct
{
  uint8_t addres;       /* devices add */
  uint8_t devType;      /* devices type */
  uint8_t cmd;          /* control cmd */
}Ctr_Modbus_TypeDef;

bool ModBus_ActionProcess( void );
#endif /*  __CTRL_DEV_H */