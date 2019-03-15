#ifndef __INTOYUN_HAL_H
#define __INTOYUN_HAL_H

uint32_t HAL_Millis(void);
void HAL_Print(char *data, uint16_t len);
void HAL_SystemInit(void);
void HAL_WifWrite(uint8_t data);
void HAL_WifiModeInterrupt( void );
void userInterfaceLoop(void);

#endif /* __INTOYUN_HAL_H */