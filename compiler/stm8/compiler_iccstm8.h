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
 * @file       compiler_iccstm8.h                                              *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      iar arm compiler compiler files                                 *
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
#ifndef __COMPILER_ICC_STM8_H__
#define __COMPILER_ICC_STM8_H__

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
#include <intrinsics.h>
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
#ifndef __PRAGMA
#define __PRAGMA(pragma)
#endif

#ifndef __ASM
#define __ASM
#endif

#ifndef __INLINE
#define __INLINE inline
#endif

#ifndef __STATIC
#define __STATIC static
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
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
#define __CONST const
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
#define __NOP __no_operation()
#endif

/**
 *******************************************************************************
 * @brief      define compiler alignment cmd 
 *******************************************************************************
 */
#ifndef __ALIGN_HEAD
#define __ALIGN_HEAD(n)                                  __PRAGMA(pack(push, n))
#endif                                                  
                                                        
#ifndef __ALIGN_TAIL                                    
#define __ALIGN_TAIL(n)                                      __PRAGMA(pack(pop))
#endif                                                  
                                                        
#ifndef __PACKED_HEAD                                   
#define __PACKED_HEAD                                    __PRAGMA(pack(push, 1))
#endif                                                  
                                                        
#ifndef __PACKED_TAIL                                   
#define __PACKED_TAIL                                        __PRAGMA(pack(pop))
#endif

/**
 *******************************************************************************
 * @brief      define atom opera
 *******************************************************************************
 */  
#ifndef __DISABLE_ALL_ISR
#define __DISABLE_ALL_ISR()                                __disable_interrupt()
#endif

#ifndef __ENABLE_ALL_ISR
#define __ENABLE_ALL_ISR()                                  __enable_interrupt()
#endif

#ifndef __GET_ISR_FLAG
#define __GET_ISR_FLAG()                    ((uint8_t)(__get_interrupt_state()))
#endif

#ifndef __SET_ISR_FLAG
#define __SET_ISR_FLAG(x)           _st(__set_interrupt_state((__istate_t)(x));)
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
#pragma section="HEAP"

#define __HEAP_HEAD_ADDR                                 (__segment_end("HEAP"))

/**
 *******************************************************************************
 * @brief      DEFINE FRAMEOWRK MAIN FUNCTION
 *******************************************************************************
 */
extern int main(void);
extern void __iar_data_init3(void);

#define Fw_Main_Init __iar_data_init3
#define Fw_Main __low_level_init
#define User_Main main

/* Exported types ------------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* iar compiler config  */

/**********************************END OF FILE*********************************/
