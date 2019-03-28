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
 * @file       compiler_armcc6.h                                               *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      armcc6 compiler files                                           *
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
 * @defgroup armcc6 compiler config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMPILER_ARMCC6_H__
#define __COMPILER_ARMCC6_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fw_conf.h"
#include <cmsis_compiler.h>

#if FRAMEWORK_COMPONENT_INIT_ENABLE
#include "EventRecorder.h"
#endif

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      disable something for compiler warning
 *******************************************************************************
 */
//#pragma clang diagnostic ignored "-Wpadded" 
//#pragma clang diagnostic ignored "-Wunused-parameter" 
//#pragma clang diagnostic ignored "-Wswitch-enum" 
//#pragma clang diagnostic ignored "-Warmcc-pragma-anon-unions"
//#pragma clang diagnostic ignored "-Wc11-extensions"
//#pragma clang diagnostic ignored "-Wunreachable-code-break"
//#pragma clang diagnostic ignored "-Wunused-value"
//#pragma clang diagnostic ignored "-Wmissing-noreturn"
//#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#pragma clang diagnostic ignored "-Wempty-body"

/**
 *******************************************************************************
 * @brief      define function name macro 
 *******************************************************************************
 */
#ifndef __FUNCNAME__
#define __FUNCNAME__            __func__
#endif

/**
 *******************************************************************************
 * @brief      define compiler pragma cmd
 *******************************************************************************
 */
#ifndef __SECTION
#define __SECTION(x)            __attribute__((section(x)))
#endif

#ifndef __UNUSED
#define __UNUSED                __attribute__((unused))
#endif

#ifndef __IMPORT_API
#define __IMPORT_API            __declspec(dllimport)
#endif

#ifndef __EXPORT_API
#define __EXPORT_API            __declspec(dllexport)
#endif

#ifndef __CODE
#define __CODE
#endif

#ifndef __CONST
#define __CONST                 const
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
#ifndef __DISABLE_ALL_ISR
#define __DISABLE_ALL_ISR()            __ASM volatile ("cpsie i" : : : "memory")
#endif

#ifndef __ENABLE_ALL_ISR
#define __ENABLE_ALL_ISR()             __ASM volatile ("cpsid i" : : : "memory")
#endif

/**
 *******************************************************************************
 * @brief      define atom opera
 *******************************************************************************
 */  
#ifndef __ATOM_ACTIVE_BEGIN
#define __ATOM_ACTIVE_BEGIN()   __DISABLE_ALL_ISR()
#endif

#ifndef __ATOM_ACTIVE_END
#define __ATOM_ACTIVE_END()     __ENABLE_ALL_ISR()
#endif

/**
 *******************************************************************************
 * @brief      size the end mode detection
 *******************************************************************************
 */
#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
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
extern unsigned int Image$$RW_IRAM1$$ZI$$Limit;

#define __HEAP_HEAD_ADDR             ((unsigned int)&Image$$RW_IRAM1$$ZI$$Limit)

/**
 *******************************************************************************
 * @brief      DEFINE FRAMEOWRK MAIN FUNCTION
 *******************************************************************************
 */
extern int $Super$$main(void);

#define Fw_Main_Init()
#define Fw_Main                                                     $Sub$$main
#define User_Main                                                   $Super$$main

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define int type
 *******************************************************************************
 */
#ifndef __stdint_h
typedef unsigned char           uint8_t;
typedef unsigned short          uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long      uint64_t;

typedef char                    int8_t;
typedef short                   int16_t;
typedef int                     int32_t;
typedef long long               int64_t;

/**
 *******************************************************************************
 * @brief      define int max value and min value
 *******************************************************************************
 */
#define INT8_MAX                (127)
#define INT16_MAX               (32767)
#define INT32_MAX               (2147483647L)
#define INT64_MAX               (9223372036854775807LL)

#define INT8_MIN                (-128)
#define INT16_MIN               (-32768)
#define INT32_MIN               (-2147483647 - 1)
#define INT64_MIN               (-9223372036854775807LL - 1)

#define UINT8_MAX               (0xFFU)
#define UINT16_MAX              (0xFFFFU)
#define UINT32_MAX              (0xFFFFFFFFUL)
#define UINT64_MAX              (0xFFFFFFFFFFFFFFFFULL)

#define UINT8_MIN               (0U)
#define UINT16_MIN              (0U)
#define UINT32_MIN              (0U)
#define UINT64_MIN              (0ULL)
#endif

/**
 *******************************************************************************
 * @brief      define bool type
 *******************************************************************************
 */
#ifndef __bool_true_false_are_defined
typedef enum
{
    false = 0,
    true = !false,
}bool;
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* armcc6 compiler config  */

/**********************************END OF FILE*********************************/
