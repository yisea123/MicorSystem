#ifndef USER_INTOYUN_H_
#define USER_INTOYUN_H_

#ifdef __cplusplus
extern "C" {
#endif

void userInit(void);
void userHandle (void);
void Intoyun_SetAction( uint8_t id );
void vCloud_RefreshCtrlStatus( uint8_t DevType, uint8_t *buff,  uint8_t lenght );

#ifdef __cplusplus
}
#endif

#endif   /* USER_INTERFACE_H_ */