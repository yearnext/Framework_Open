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
 * @file       compiler_armcc5.h                                               *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      armcc5 compiler files                                           *
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
 * @defgroup armcc5 compiler config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMPILER_ARMCC5_H__
#define __COMPILER_ARMCC5_H__

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
#include "arch_arm.h"

#ifdef ENABLE_FRAMEWORK_DEBUG
#include "EventRecorder.h"
#endif

/* define compiler cmd -------------------------------------------------------*/
#pragma anon_unions

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define function name macro 
 *******************************************************************************
 */
#ifndef __FUNCNAME__
#define __FUNCNAME__                                                   __func__
#endif

/**
 *******************************************************************************
 * @brief      define compiler pragma cmd
 *******************************************************************************
 */
#ifndef __PRAGMA
#define __PRAGMA(pragma)        _Pragma(#pragma)
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

#ifndef __DATA
#define __DATA
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
#define __PACKED_HEAD           __packed
#endif

#ifndef __PACKED_TAIL
#define __PACKED_TAIL
#endif

/**
 *******************************************************************************
 * @brief      define NULL
 *******************************************************************************
 */
#ifndef NULL
#define NULL ((void *)0)
#endif

/**
 *******************************************************************************
 * @brief      define atom opera
 *******************************************************************************
 */
#ifndef __DISABLE_ALL_ISR
#define __DISABLE_ALL_ISR()                                _st(__disable_irq();)
#endif

#ifndef __ENABLE_ALL_ISR
#define __ENABLE_ALL_ISR()                                 _st(__enable_irq();)
#endif
 
#ifndef __ATOM_ACTIVE_BEGIN
#define __ATOM_ACTIVE_BEGIN(n)   _st(register uint32_t __regPriMask __ASM("primask"); (n) = __regPriMask; __ASM("CPSID i");)
#endif

#ifndef __ATOM_ACTIVE_END
#define __ATOM_ACTIVE_END(n)     _st(register uint32_t __regPriMask __ASM("primask"); __regPriMask = (n);)
#endif

///**
// *******************************************************************************
// * @brief      size the end mode detection
// *******************************************************************************
// */
//#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
//    #define COMPILER_USE_BIG_ENDIAN
////    #warning The byte order of the compiler uses big endian mode!
//#else
//    #define COMPILER_USE_LITTLE_ENDIAN
////    #warning The byte order of the compiler uses little endian mode!
//#endif

/**
 *******************************************************************************
 * @brief      DEFINE MCU HEAP ADDRESS
 *******************************************************************************
 */
extern unsigned int Image$$RW_IRAM1$$ZI$$Limit;

#define __HEAP_HEAD_ADDR             ((unsigned int)&Image$$RW_IRAM1$$ZI$$Limit)

#define USE_COMPILER_HEAP_ADDR                                               (1)

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
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** armcc5 compiler config */

/**********************************END OF FILE*********************************/
