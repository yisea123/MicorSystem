#ifndef __APPS_DEF_H
#define __APPS_DEF_H

/*******************************************************************************
     System configuration 
********************************************************************************/
typedef enum
{
  PROJECT_ID = 0x01,
  PROJECT_SECRET = 0x02,
  DEVICES_ID = 0x03,
  WIFI_SSID = 0x04,
  WIFI_SECRET = 0x05,
}SYS_CONFIG_TYPE_ENUM;

typedef struct
{
  uint8_t uid[5][12];
  uint8_t total;
}light_Infor;

typedef struct
{
  uint8_t productID[32];
  uint8_t productSecret[64];
  uint8_t deviceID[32];
}product_Infor;

typedef struct
{
  uint8_t wifissid[32];
  uint8_t wifiPwd[32];
}wifi_Infor;

typedef struct
{
  uint8_t productID[32];
  uint8_t productSecret[64];
  uint8_t deviceID[32];
  
  uint8_t wifissid[32];
  uint8_t wifiPwd[32];
  
  light_Infor st_LightInfor;
  product_Infor st_ProductInfor;
  wifi_Infor st_wifiInfor;
}systemConfig_struct;

extern systemConfig_struct st_systemConfig_struct;

#endif  /* __APPS_DEF_H */