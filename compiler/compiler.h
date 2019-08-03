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
 * @file       compiler.h                                                      *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      compiler head files                                             *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. xxxxx                                                                    *
 *******************************************************************************
 */

/**
 * @defgroup compiler config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_COMPILER_H__
#define __FRAMEWORK_COMPILER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#if defined(__CC_ARM)
#include "arm\compiler_armcc5.h"
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#include "arm\compiler_armcc6.h"
#elif defined(__ICCARM__)
#include "arm\compiler_iccarm.h"
#elif defined (__GNUC__)
#include "arm\compiler_gccarm.h"
#elif defined(__CX51__) || defined(__C51__)
#include "8051\compiler_keilc51.h"
#elif defined(__ICC8051__)
#include "8051\compiler_icc8051.h"
#elif defined (SDCC) || defined (__SDCC)
#include "8051\compiler_sdcc51.h"
#elif defined(__XC8) || defined(__PICC__)
#include "..\compiler\picc\compiler_picc.h"
#elif defined(__ICCSTM8__)
#include "..\compiler\stm8\compiler_iccstm8.h"
#elif defined (_MSC_VER)
#include "msvc\compiler_msvc.h"
#else
#endif

/**
 *******************************************************************************
 * @brief       MACRO
 *******************************************************************************
 */
#ifndef NULL
#define NULL ((void *)0)
#endif

/**
 *******************************************************************************
 * @brief       MACRO
 *******************************************************************************
 */
#define _unused(a)                                               _st((a) = (a);)

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _connect(a, b)                                                    (a##b)

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _sizeof(type)                     (sizeof(type) / sizeof(unsigned char))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _dimof(arr)                             (sizeof(arr) / sizeof((arr)[0]))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _align(num, align)              (((num) + (align) - 1) & ~((align) - 1))
#define _align_down(num, align)                         ((num) & ~((align) - 1))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _mem_bit_set(buf, align, pos) \
                           _st((buf)[(pos)/(align)] |=  (1 << ((pos)%(align)));)
#define _mem_bit_clr(buf, align, pos) \
                           _st((buf)[(pos)/(align)] &= ~(1 << ((pos)%(align)));)
#define _mem_bit_get(buf, align, pos) \
                   (((buf)[(pos)/(align)] & (1 << ((pos)%(align)))) ? (1) : (0))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _container_of(ptr, type, member) \
               ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _min(a, b)                                     (((a) < (b)) ? (a) : (b))
#define _max(a, b)                                     (((a) > (b)) ? (a) : (b))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _to_str(name)                                                     #name

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define IS_PTR_NULL(ptr)                                  ((ptr) == ((void *)0))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define IS_PARAM_ZERO(param)                                      ((param) == 0)

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _assert(logic)

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _st(active)                                                     {active}

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _bv(BIT)                                                    (1 << (BIT))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _set_bit(REG, BIT)                               ((REG) |= (1 << (BIT)))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _clr_bit(REG, BIT)                              ((REG) &= ~(1 << (BIT)))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _xor_bit(REG, BIT)                               ((REG) ^= (1 << (BIT)))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _read_bit(REG, BIT)                               ((REG) & (1 << (BIT)))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _set_reg(REG, VAL)                                      ((REG) |= (VAL))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _clr_reg(REG, VAL)                                    ((REG) &= ~(VAL))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _xor_reg(REG, VAL)                                      ((REG) ^= (VAL))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _get_reg(REG, VAL)                                       ((REG) & (VAL))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _rst_reg(REG)                                              ((REG) = (0))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _write_reg(REG, VAL)                                     ((REG) = (VAL))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _read_reg(REG)                                                     (REG)

/**
 *******************************************************************************
 * @brief       MACRO
 * @note        移植于RTTHREAD
 *******************************************************************************
 */
#ifdef ENABLE_FRAMEWORK_COMPONENT_INIT
/* initialization export */
typedef int (*init_fn_t)(void);

#ifdef _MSC_VER /* we do not support MS VC++ compiler */
#define INIT_EXPORT(fn, level)
#else
#define INIT_EXPORT(fn, level)  \
        const init_fn_t f_##fn __SECTION(".fw_init_fn."level) = fn
#endif
#else
#define INIT_EXPORT(fn, level)
#endif

/* board init routines will be called in board_init() function */
#define INIT_COMPONENT_EXPORT(fn)       INIT_EXPORT(fn, "1")
#define INIT_HAL_EXPORT(fn)             INIT_EXPORT(fn, "2")
#define INIT_BOARD_EXPORT(fn)           INIT_EXPORT(fn, "3")
#define INIT_APP_EXPORT(fn)             INIT_EXPORT(fn, "4")

/* Exported types ------------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework compiler config */

/**********************************END OF FILE*********************************/
