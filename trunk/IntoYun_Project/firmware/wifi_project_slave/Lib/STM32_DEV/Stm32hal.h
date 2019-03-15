#ifndef __STM32HAL_H
#define __STM32HAL_H

void HAL_IncTick(void);
uint32_t HAL_GetTick(void);
void HAL_Delay(__IO uint32_t Delay);
uint32_t timerGetId(void);
bool timerIsEnd(uint32_t timerID, uint32_t time);

#endif /* __STM32HAL_H */