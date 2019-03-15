#ifndef __TYPEDEF_H
#define __TYPEDEF_H

#ifndef OS_EN

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned int   INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   int   INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */
typedef unsigned char  *STRING;		
typedef unsigned int   OS_STK;                   /* Each stack entry is 32-bit wide                    */
typedef unsigned int   OS_CPU_SR;                /* Define size of CPU status register (PSR = 32 bits) */
typedef void           (*PFNCT)(void);	         /* function pointer */
typedef void           (*CPU_FNCT_VOID)(void);
typedef void           (*CPU_FNCT_PTR )(void *);

#endif 

/***********************************************
 * Define NAME as an variable
 * Access of 8/16/32 bit variable:  NAME
 * Access of bit(s):           		NAME_bit.xxx
 ***********************************************/
#define INT8U_BIT(NAME, BIT_STRUCT)								\
								union {									\
									INT8U NAME;							\
									BIT_STRUCT NAME ## _bit;		\
								}
#define INT16U_BIT(NAME, BIT_STRUCT)							\
								union {									\
									INT16U NAME;						\
									BIT_STRUCT NAME ## _bit;		\
								}
#define INT32U_BIT(NAME, BIT_STRUCT)							\
								union {									\
									INT32U NAME;						\
									BIT_STRUCT NAME ## _bit;		\
								}

/***********************************************
 * Define NAME as an variable
 * Access of 8/16/32 bit variable:  NAME
 * Access of enum variable:         NAME_enum
 ***********************************************/
#define INT8U_ENUM(NAME, ENUM_STRUCT)							\
								union {									\
									INT8U NAME;							\
									ENUM_STRUCT NAME ## _enum;		\
								}
#define INT16U_ENUM(NAME, ENUM_STRUCT)							\
								union {									\
									INT16U NAME;						\
									ENUM_STRUCT NAME ## _enum;		\
								}
#define INT32U_ENUM(NAME, ENUM_STRUCT)							\
								union {									\
									INT32U NAME;						\
									ENUM_STRUCT NAME ## _enum;		\
								}


#endif  /*  __TYPEDEF_H */