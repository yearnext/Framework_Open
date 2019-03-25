/**
 *******************************************************************************
 *                 Copyright (C) 2017 - 2018  Accumulate Team                  *
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
 * @file       malloc.h                                                        *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-20                                                      *
 * @brief      memory component head files                                     *
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
 * @defgroup memory component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MEMORY_COMPONENT_H__
#define __MEMORY_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_path.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_MEMORY_MANAGEMENT_COMPONENT
#define USE_MEMORY_COMPONENT                                                 (1)

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_MEMORY_COMPONENT                                                 (1)
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        memory management function api
 *******************************************************************************
 */
#if USE_MEMORY_COMPONENT
extern void  Fw_Mem_InitCmpt(void);
extern void *Fw_Mem_Alloc(uint32_t);
extern void  Fw_Mem_Free(void*);
extern bool Fw_Mem_IsIn(void*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** memory component */

/**********************************END OF FILE*********************************/
