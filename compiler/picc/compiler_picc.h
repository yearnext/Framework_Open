/**
 *******************************************************************************
 *                 Copyright (C) 2017 - 2019  Accumulate Team                  *
 *                                                                             *
 *      Licensed under the Apache License, Version 2.0 (the "License");        *
 *      you may not use this file except in compliance with the License.       *
 *      You may obtain a copy of the License at                                *
 *                 http://www.apache.org/licenses/LICENSE-2.0                  *
 *                                                                             *
 *   Unless required by applicable law or agreed to in writing, software       *
 *   distributed under the License is distributed on an "AS IS" BASIS,         *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *   See the License for the specific language governing permissions and       *
 *   limitations under the License.                                            *
 *******************************************************************************
 * @file       compiler_picc.h                                                 *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      pic compiler compiler files                                     *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
 
/**
 * @defgroup pic compiler config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMPILER_PIC_H__
#define __COMPILER_PIC_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define function name macro 
 *******************************************************************************
 */
#ifndef __FUNCNAME__
#define __FUNCNAME__            __FUNC__
#endif

/**
 *******************************************************************************
 * @brief      define compiler pragma cmd
 *******************************************************************************
 */
#ifndef __PRAGMA
#define __PRAGMA(pragma)          _Pragma(#pragma)
#endif

#ifndef __ASM
#define __ASM                   
#endif

#ifndef __INLINE
#define __INLINE                
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE        
#endif

#ifndef __SECTION
#define __SECTION(x)            @ x
#endif

#ifndef __UNUSED
#define __UNUSED
#endif

#ifndef __USED
#define __USED
#endif

#ifndef __WEAK
#define __WEAK
#endif

#ifndef __IMPORT_API
#define __IMPORT_API
#endif

#ifndef __EXPORT_API
#define __EXPORT_API
#endif

/**
 *******************************************************************************
 * @brief      define compiler alignment cmd 
 *******************************************************************************
 */
#ifndef __ALIGN_HEAD
#define __ALIGN_HEAD(n)         __PRAGMA(pack(push, n))
#endif

#ifndef __ALIGN_TAIL
#define __ALIGN_TAIL(n)         __PRAGMA(pack(pop))
#endif

#ifndef __PACKED_HEAD
#define __PACKED_HEAD           __PRAGMA(pack(push, 1))
#endif

#ifndef __PACKED_TAIL
#define __PACKED_TAIL           __PRAGMA(pack(pop))
#endif
   
/**
 *******************************************************************************
 * @brief      define compiler critical cmd
 *******************************************************************************
 */
#ifndef __NOP
#define __NOP()                 __no_operation() 
#endif

#ifndef __CONST
#define __CONST                 const
#endif

// #ifndef __WFI
// #define __WFI()                 __ASM ("wfi")
// #endif

// #ifndef __WFE
// #define __WFE()                 __ASM ("wfe")
// #endif

// #ifndef __SEV
// #define __SEV()                 __ASM ("sev")
// #endif

// #ifndef __CLREX
// #define __CLREX()               __ASM ("clrex")
// #endif

/**
 *******************************************************************************
 * @brief      define atom opera
 *******************************************************************************
 */    
#ifndef __DISABLE_ALL_ISR
#define __DISABLE_ALL_ISR()            __disable_interrupt()
#endif

#ifndef __ENABLE_ALL_ISR
#define __ENABLE_ALL_ISR()             __enable_interrupt()
#endif

#ifndef __ATOM_ACTIVE_BEGIN
#define __ATOM_ACTIVE_BEGIN()          __DISABLE_ALL_ISR()
#endif

#ifndef __ATOM_ACTIVE_END
#define __ATOM_ACTIVE_END()            __ENABLE_ALL_ISR()
#endif
/**
 *******************************************************************************
 * @brief      size the end mode detection
 *******************************************************************************
 */
#if 0
    #define COMPILER_USE_BIG_ENDIAN
//    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
//    #warning The byte order of the compiler uses little endian mode!
#endif
    
/**
 *******************************************************************************
 * @brief      DEFINE MCU HEAP ADDRESS
 *******************************************************************************
 */
//#pragma section="HEAP"
//
//#define __HEAP_HEAD_ADDR                                 (__segment_end("HEAP"))

/**
 *******************************************************************************
 * @brief      DEFINE FRAMEOWRK MAIN FUNCTION
 *******************************************************************************
 */
#define Fw_Main_Init
#define Fw_Main
#define User_Main main

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define int type
 *******************************************************************************
 */
//#ifndef _STDINT
//typedef unsigned char           uint8_t;
//typedef unsigned short          uint16_t;
//typedef unsigned int            uint32_t;
//typedef unsigned long long      uint64_t;
//
//typedef char                    int8_t;
//typedef short                   int16_t;
//typedef int                     int32_t;
//typedef long long               int64_t;
//
///**
// *******************************************************************************
// * @brief      define int max value and min value
// *******************************************************************************
// */
//#define INT8_MAX                (127)
//#define INT16_MAX               (32767)
//#define INT32_MAX               (2147483647U)
//#define INT64_MAX               (9223372036854775807LL)
//
//#define INT8_MIN                (-128)
//#define INT16_MIN               (-32768)
//#define INT32_MIN               (-2147483647 - 1)
//#define INT64_MIN               (-9223372036854775807LL - 1)
//
//#define UINT8_MAX               (0xFF)
//#define UINT16_MAX              (0xFFFF)
//#define UINT32_MAX              (0xFFFFFFFFU)
//#define UINT64_MAX              (0xFFFFFFFFFFFFFFFFULL)
//
//#define UINT8_MIN               (0)
//#define UINT16_MIN              (0)
//#define UINT32_MIN              (0U)
//#define UINT64_MIN              (0ULL)
//#endif

/**
 *******************************************************************************
 * @brief      define bool type
 *******************************************************************************
 */
//#ifndef _STDBOOL
//typedef enum
//{
//    false = 0,
//    true = !false,
//}bool;
//#endif

/**
 *******************************************************************************
 * @brief      include config file
 *******************************************************************************
 */
#include "fw_conf.h"

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* pic compiler config  */

/**********************************END OF FILE*********************************/
