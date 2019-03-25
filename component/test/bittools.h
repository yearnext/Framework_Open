/**
 *******************************************************************************
 *                       Copyright (C) 2017  yearnext                          *
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
 * @file       bittools.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-09-17                                                      *
 * @brief      framework bit tool component head files                         *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
 *******************************************************************************
 */
 
/**
 * @defgroup bit tool component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMPONENT_BITTOOLS_H__
#define __COMPONENT_BITTOOLS_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern uint8_t __CONST _BitMap[];
    
/* Exported functions --------------------------------------------------------*/
//< bit map operation interface
extern void BitMapClr(uint8_t, uint8_t*, uint32_t*);
extern void BitMapSet(uint8_t, uint8_t*, uint32_t*);
extern uint8_t BitMapGet(uint8_t*, uint32_t);
    
//< byte operation interface
extern uint16_t ByteExchange(uint16_t);
extern void ByteOrderExchange(uint16_t*, uint16_t);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework bit tool component */

/**********************************END OF FILE*********************************/
