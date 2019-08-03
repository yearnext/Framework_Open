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
 * @file       compiler_icc8051.h                                              *
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
#ifndef __COMPILER_ICC_8051_H__
#define __COMPILER_ICC_8051_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <intrinsics.h>
    
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define compiler macro 
 *******************************************************************************
 */
#define USE_IAR_8051_COMPILER

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
#define __PRAGMA(x) _Pragma(#x)
#endif

#ifndef __ASM
#define __ASM
#endif

#ifndef __INLINE
#define __INLINE inline
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif

#ifndef __SECTION
#define __SECTION(x)
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

#ifndef __CONST
#define __CONST __code const
#endif

#ifndef __DATA
#define __DATA __data
#endif
  
#ifndef __XDATA
#define __XDATA __no_init __xdata
#endif

#ifndef __BIT
#define __BIT __bit __no_init bool
#endif

#ifndef __CODE
#define __CODE const __code
#endif
    
#ifndef __NOP
#define __NOP() __no_operation()
#endif
    
#ifndef __AT
#define __AT @ 
#endif

#ifndef SBIT
#define SBIT(name, addr, bit)  __bit __no_init volatile bool name @ (addr+bit)
#endif

#ifndef SFR
#define SFR(name, addr)        __sfr __no_init volatile unsigned char name @ addr
#endif

#ifndef SFRX
#define SFRX(name, addr)       __xdata __no_init volatile unsigned char name @ addr
#endif

#ifndef SFR16
#define SFR16(name, addr)      __sfr __no_init volatile unsigned int  name @ addr
#endif

#ifndef SFR16E
#define SFR16E(name, fulladdr) /* not supported */
#endif

#ifndef SFR32
#define SFR32(name, fulladdr)  __sfr __no_init volatile unsigned long name @ addr
#endif

#ifndef SFR32E
#define SFR32E(name, fulladdr) /* not supported */
#endif

#ifndef ISR_HANDLE
#define ISR_HANDLE(name,v) __PRAGMA(vector=v) __near_func __interrupt void name(void)
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
typedef signed char             int8_t;
typedef signed int              int16_t;
typedef long                    int32_t;

/* Unsigned.  */
typedef unsigned char           uint8_t;
typedef unsigned int            uint16_t;
typedef unsigned long           uint32_t;

/* Minimum of signed integral types.  */
#define INT8_MIN               (-128)
#define INT16_MIN              (-32767-1)
#define INT32_MIN              (-2147483647L-1)

/* Maximum of signed integral types.  */
#define INT8_MAX               (127)
#define INT16_MAX              (32767)
#define INT32_MAX              (2147483647L)

/* Maximum of unsigned integral types.  */
#define UINT8_MAX              (255)
#define UINT16_MAX             (65535)
#define UINT32_MAX             (4294967295UL)

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
