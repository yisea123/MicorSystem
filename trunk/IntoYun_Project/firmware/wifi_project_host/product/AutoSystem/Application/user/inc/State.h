#ifndef __STATE_H
#define __STATE_H

typedef void (*STATE_FUNC)(void *);
extern STATE_FUNC pSt_State;

void State_Machine( void );
static void State_SysActProcess( void *ptr );

#endif /* __STATE_H */