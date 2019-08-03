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
 * @file       compiler_keil8051.h                                             *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2016-05-27                                                      *
 * @brief      8051 MCU compiler files                                         *
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
 * @defgroup 8051 MCU compiler config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMPILER_8051_H__
#define __COMPILER_8051_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <intrins.h>

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define compiler macro 
 *******************************************************************************
 */
#define USE_KEIL_C51_COMPILER

/**
 *******************************************************************************
 * @brief      define 8051 macro 
 *******************************************************************************
 */
#define USE_8051_PLATFORM

/**
 *******************************************************************************
 * @brief      define function name macro 
 *******************************************************************************
 */
#ifndef __FUNCNAME__
#define __FUNCNAME__            __func__
#endif

#ifndef __PRAGMA
#define __PRAGMA(pragma)
#endif

#ifndef __ASM
#define __ASM
#endif

#ifndef __INLINE
#define __INLINE
#endif

#ifndef __STATIC
#define __STATIC static
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE
#endif

#ifndef __SECTION
#define __SECTION(x)
#endif

#ifndef __UNUSED
#define __UNUSED(x) ((x) = (x))
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

#ifndef __CODE
#define __CODE code
#endif

#ifndef __CONST
#define __CONST const
#endif

#ifndef __DATA
#define __DATA data
#endif

#ifndef __XDATA
#define __XDATA xdata
#endif

#ifndef __BIT
#define __BIT bit
#endif

#ifndef __AT
#define __AT _at_
#endif

#ifndef __NOP
#define __NOP _nop_
#endif

#ifndef SBIT
#define SBIT(name, addr, bit)  sbit  name = addr^bit
#endif

#ifndef SFR
#define SFR(name, addr)        sfr   name = addr
#endif

#ifndef SFRX
#define SFRX(name, addr)       volatile unsigned char xdata name _at_ addr
#endif

#ifndef SFR16
#define SFR16(name, addr)      sfr16 name = addr
#endif

#ifndef SFR16E
#define SFR16E(name, fulladdr)
#endif

#ifndef SFR32
#define SFR32(name, fulladdr)
#endif

#ifndef SFR32E
#define SFR32E(name, fulladdr)
#endif

#ifndef ISR_HANDLE
#define ISR_HANDLE(name,v) void name(void) interrupt v
#endif

/**
 *******************************************************************************
 * @brief      define compiler alignment cmd 
 *******************************************************************************
 */
#ifndef __ALIGN_HEAD
#define __ALIGN_HEAD(n)
#endif

#ifndef __ALIGN_TAIL
#define __ALIGN_TAIL(n)
#endif

#ifndef __PACKED_HEAD
#define __PACKED_HEAD
#endif

#ifndef __PACKED_TAIL
#define __PACKED_TAIL
#endif

/**
 *******************************************************************************
 * @brief      define atom opera
 *******************************************************************************
 */
#ifndef __DISABLE_ALL_ISR
#define __DISABLE_ALL_ISR()                                         _st(EA = 0;)
#endif

#ifndef __ENABLE_ALL_ISR
#define __ENABLE_ALL_ISR()                                          _st(EA = 1;)
#endif

#ifndef __GET_ISR_FLAG
#define __GET_ISR_FLAG()                                                    (EA)
#endif

#ifndef __SET_ISR_FLAG
#define __SET_ISR_FLAG(x)                                         _st(EA = (x);)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define int type
 *******************************************************************************
 */
typedef unsigned char           uint8_t;
typedef unsigned int            uint16_t;
typedef unsigned long           uint32_t;

typedef signed   char           int8_t;
typedef signed   short          int16_t;
typedef signed   long           int32_t;

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

/**
 *******************************************************************************
 * @brief      define bool type
 *******************************************************************************
 */
typedef enum
{
   false = 0,
   true = !false,
}bool;

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

/** @}*/     /* 8051 MCU compiler config  */

/**********************************END OF FILE*********************************/
