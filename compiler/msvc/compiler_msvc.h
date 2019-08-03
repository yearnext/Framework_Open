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
 * @file       compiler_msvc.h                                                 *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      msvc compiler files                                             *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 MSVC                                                        *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/**
 * @defgroup msvc compiler config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMPILER_MSVC_H__
#define __COMPILER_MSVC_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

#pragma warning(disable:4100)
#pragma warning(disable:4101)
#pragma warning(disable:4189)
#pragma warning(disable:4244)
#pragma warning(disable:4819)
#pragma warning(disable:26495)

/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "fw_conf.h"

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
#define __CODE
#endif

#ifndef __CONST
#define __CONST
#endif

#ifndef __DATA
#define __DATA
#endif

#ifndef __XDATA
#define __XDATA
#endif

#ifndef __BIT
#define __BIT
#endif

#ifndef __AT
#define __AT
#endif

#ifndef __NOP
#define __NOP
#endif

#ifndef SBIT
#define SBIT(name, addr, bit)
#endif

#ifndef SFR
#define SFR(name, addr)
#endif

#ifndef SFRX
#define SFRX(name, addr)
#endif

#ifndef SFR16
#define SFR16(name, addr)
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
#define ISR_HANDLE(name, v) void CALLBACK SystemTickHandle(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
#endif

#ifndef FwTick_Irq_Handler
#define FwTick_Irq_Handler(v) CALLBACK SystemTickHandle(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
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

#ifndef __packed
#define __packed
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
 * @brief      define atom option
 *******************************************************************************
 */
#ifndef __DISABLE_ALL_ISR
#define __DISABLE_ALL_ISR()
#endif

#ifndef __ENABLE_ALL_ISR
#define __ENABLE_ALL_ISR()
#endif

#ifndef __GET_ISR_FLAG
#define __GET_ISR_FLAG()                                                    (0)
#endif

#ifndef __SET_ISR_FLAG
#define __SET_ISR_FLAG(x)
#endif

/* Exported types ------------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** armcc5 compiler config */

/**********************************END OF FILE*********************************/
