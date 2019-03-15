#ifndef __TIMER_H
#define __TIMER_H

typedef enum {
    TIMER0 = 0,
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
}TIMER_ENUM;


void Timer_Init( INT8U u8_Timer_EN );
INT32U  Timer_TmrRd ( INT8U u8_TIMER_EN );

#endif   /* __TIMER_H */