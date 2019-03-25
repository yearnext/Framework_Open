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
 * @file       hal_dma.h                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-09-13                                                      *
 * @brief      hal dma driver component head file                              *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 2018-09-13 从“hal_device.h”分离出DMA驱动                                  *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DRIVER_DMA_H__
#define __HAL_DRIVER_DMA_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        HAL DMA PORT
 *******************************************************************************
 */
enum HAL_DMA_PORT
{
    HAL_DMA_CH0,  HAL_DMA_CH1,  HAL_DMA_CH2,  HAL_DMA_CH3,
    HAL_DMA_CH4,  HAL_DMA_CH5,  HAL_DMA_CH6,  HAL_DMA_CH7,
    HAL_DMA_CH8,  HAL_DMA_CH9,  HAL_DMA_CH10, HAL_DMA_CH11,
    HAL_DMA_CH12, HAL_DMA_CH13, HAL_DMA_CH14, HAL_DMA_CH15,
    HAL_DMA_CH16, HAL_DMA_CH17, HAL_DMA_CH18, HAL_DMA_CH19,
    HAL_DMA_CH20, HAL_DMA_CH21, HAL_DMA_CH22, HAL_DMA_CH23,
    HAL_DMA_CH24, HAL_DMA_CH25, HAL_DMA_CH26, HAL_DMA_CH27,
    HAL_DMA_CH28, HAL_DMA_CH29, HAL_DMA_CH30, HAL_DMA_CH31,
    
    HAL_DMA_CH_MAX,
};

enum HAL_DMA_CMD
{
    HAL_DMA_CHANNEL_NORMAL = HAL_SPECIAL_CMD,
    HAL_DMA_CHANNEL_NEGATION,
};

/**
 *******************************************************************************
 * @brief        HAL DMA OPTION
 *******************************************************************************
 */
#define HAL_DMA_READ                                                           0
#define HAL_DMA_WRITE                                                          1

/**
 *******************************************************************************
 * @brief        HAL DMA EVENT
 *******************************************************************************
 */
#define HAL_DMA_EVENT_TX_DONE                                                  2
#define HAL_DMA_EVENT_RX_DONE                                                  3

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
