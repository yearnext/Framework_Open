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
 * @file       compiler_8051.h                                                 *
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
#include <stdint.h>
#include <stdbool.h>

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define function name macro 
 *******************************************************************************
 */
#ifndef __FUNCNAME__
#define __FUNCNAME__            __func__
#endif

#if defined(__CX51__) || defined(__C51__)
#define _PRAGMA(x)
#define MCU_ISR(f,v)   void f(void) interrupt v

#define _const  code
#define _xdata  xdata
#define _bit    bit
#define _at     _at_
    
#elif defined(__ICC8051__)
#include <stdbool.h>
#define _PRAGMA(x) _Pragma(#x)
#define MCU_ISR_HANDLE(f,v)   _PRAGMA(vector=v) __near_func __interrupt void f(void)

#define _const   __code const
#define _xdata   __no_init __xdata
#define _bit     __bit __no_init bool
#define _at      @
#else
    #error NOT Support Device
#endif

/**
 *******************************************************************************
 * @brief      define compiler pragma cmd
 *******************************************************************************
 */
#ifndef __PRAGMA
#define __PRAGMA(pragma)
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

#ifndef __XDATA
#define __XDATA __xdata
#endif

#ifndef __BIT
#define __BIT __bit
#endif

#ifndef __AT
#define __AT __at
#endif

#ifndef SBIT
#define SBIT(name, addr, bit)  __sbit  __at(addr+bit)                    name
#endif

#ifndef SFR
#define SFR(name, addr)        __sfr   __at(addr)                        name
#endif

#ifndef SFRX
#define SFRX(name, addr)       __xdata volatile unsigned char __at(addr) name
#endif

#ifndef SFR16
#define SFR16(name, addr)      __sfr16 __at(((addr+1U)<<8) | addr)       name
#endif

#ifndef SFR16E
#define SFR16E(name, fulladdr) __sfr16 __at(fulladdr)                    name
#endif

#ifndef SFR32
#define SFR32(name, fulladdr)  __sfr32 __at(((addr+3UL)<<24) | ((addr+2UL)<<16) | ((addr+1UL)<<8) | addr) name
#endif

#ifndef SFR32E
#define SFR32E(name, fulladdr) __sfr32 __at(fulladdr)                    name
#endif

#ifndef ISR_HANDLE
#define ISR_HANDLE(name,VECTOR) void name(void);\
                                void name(void) __interrupt VECTOR
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
#define __DISABLE_ALL_ISR()
#endif

#ifndef __ENABLE_ALL_ISR
#define __ENABLE_ALL_ISR()
#endif

#ifndef __ATOM_ACTIVE_BEGIN
#define __ATOM_ACTIVE_BEGIN()          __DISABLE_ALL_ISR()
#endif

#ifndef __ATOM_ACTIVE_END
#define __ATOM_ACTIVE_END()            __ENABLE_ALL_ISR()
#endif

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
