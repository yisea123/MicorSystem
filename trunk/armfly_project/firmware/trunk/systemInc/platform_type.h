#ifndef __PLATFORM_TYPE_H
#define __PLATFORM_TYPE_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
  
/*!
 * @brief Convert \a intval to a bool_t value: false if \a intval == 0, true otherwise
 */
#define MAKE_BOOL( intval ) ((int)(intval)!=0 ? true : false)  
  
  
 
/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif    // __PLATFORM_TYPE_H
  