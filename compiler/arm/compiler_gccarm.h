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
 * @file       compiler_gccarm.h                                               *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      gcc arm compiler compiler files                                 *
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
 * @defgroup iar compiler config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMPILER_GCC_ARM_H__
#define __COMPILER_GCC_ARM_H__

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
#include <cmsis_compiler.h>
#include "fw_conf.h"

/* Exported macro ------------------------------------------------------------*/
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
//#ifndef __NOP
//#define __NOP()                 __no_operation()
//#endif

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
#define __DISABLE_ALL_ISR()            __disable_irq()
#endif

#ifndef __ENABLE_ALL_ISR
#define __ENABLE_ALL_ISR()             __enable_irq()
#endif

#ifndef __ATOM_ACTIVE_BEGIN
#define __ATOM_ACTIVE_BEGIN()          __DISABLE_ALL_ISR()
#endif

#ifndef __ATOM_ACTIVE_END
#define __ATOM_ACTIVE_END()            __ENABLE_ALL_ISR()
#endif

/* Exported types ------------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* iar compiler config  */

/**********************************END OF FILE*********************************/
