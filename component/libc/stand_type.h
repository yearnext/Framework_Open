/**
 *******************************************************************************
 * @file       stand_type.h                                                    *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-09-17                                                      *
 * @brief      std library component head files                                *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.参考自uClibc开源库                                                         *
 *******************************************************************************
 */
 
/**
 * @defgroup std library component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STDAND_C_TYPE_H__
#define __STDAND_C_TYPE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#if defined(__CX51__) || defined(__C51__)
typedef signed char   int8_t;
typedef unsigned char uint8_t;
typedef signed int    int16_t;
typedef unsigned int  uint16_t;
typedef signed long   int32_t;
typedef unsigned long uint32_t;
typedef unsigned int  size_t;
#elif defined(__ICC8051__)
typedef signed char   int8_t;
typedef unsigned char uint8_t;
typedef signed int    int16_t;
typedef unsigned int  uint16_t;
typedef signed long   int32_t;
typedef unsigned long uint32_t;

#ifndef NULL
#define NULL ((void *)0)
#endif

#elif defined(__XC8) || defined(__PICC__)
#else
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** std library component */

/**********************************END OF FILE*********************************/
