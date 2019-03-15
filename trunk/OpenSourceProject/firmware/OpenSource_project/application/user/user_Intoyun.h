#ifndef USER_INTOYUN_H_
#define USER_INTOYUN_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DPID_BOOL_LIGHT_1                         1 
#define DPID_BOOL_LIGHT_2                         2

#define DPID_DOUBLE_TEMPERATURE                   10  //数值型           温度值
#define DPID_DOUBLE_HUMINITY                      11  //数值型           湿度值

  
void userInit(void);
void IntoYunuserHandle (void);


#ifdef __cplusplus
}
#endif

#endif   /* USER_INTERFACE_H_ */