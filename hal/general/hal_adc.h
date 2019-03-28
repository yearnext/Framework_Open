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
 * @file       hal_adc.h                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-01-17                                                      *
 * @brief      adc driver application component                                *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 2018-06-28 从“hal_device.h”分离出ADC驱动                                 *
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DRIVER_ADC_H__
#define __HAL_DRIVER_ADC_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        HAL ADC PORT
 *******************************************************************************
 */
enum HAL_ADC_PORT
{
    HAL_ADC_CH0,  HAL_ADC_CH1,  HAL_ADC_CH2,  HAL_ADC_CH3,
    HAL_ADC_CH4,  HAL_ADC_CH5,  HAL_ADC_CH6,  HAL_ADC_CH7,
    HAL_ADC_CH8,  HAL_ADC_CH9,  HAL_ADC_CH10, HAL_ADC_CH11,
    HAL_ADC_CH12, HAL_ADC_CH13, HAL_ADC_CH14, HAL_ADC_CH15,
    HAL_ADC_CH16, HAL_ADC_CH17, HAL_ADC_CH18, HAL_ADC_CH19,
    HAL_ADC_CH20, HAL_ADC_CH21, HAL_ADC_CH22, HAL_ADC_CH23,
    HAL_ADC_CH24, HAL_ADC_CH25, HAL_ADC_CH26, HAL_ADC_CH27,
    HAL_ADC_CH28, HAL_ADC_CH29, HAL_ADC_CH30, HAL_ADC_CH31,
    
    HAL_ADC_CH_MAX,
};

/**
 *******************************************************************************
 * @brief        HAL ADC CONVERT MODE
 *******************************************************************************
 */
//! ADC转换失能
#define HAL_ADC_DISABLE_CONVERT           0x00
//! ADC单次转换模式
#define HAL_ADC_SINGLE_CONVERT            0x01
//! ADC单次周期转换模式
#define HAL_ADC_SINGLE_PERIOD_CONVERT     0x02
//! ADC循环转换模式
#define HAL_ADC_CONTINUE_CONVERT          0x03

/**
 *******************************************************************************
 * @brief        HAL ADC CONVERT STATE
 *******************************************************************************
 */
#define HAL_ADC_SCAN_INIT                 0
#define HAL_ADC_SCAN_DOING                1
#define HAL_ADC_SCAN_WAIT                 2
#define HAL_ADC_SCAN_HANDLE               3
#define HAL_ADC_SCAN_END                  4

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint32_t TempValue;
    uint16_t ScanValue;
    uint16_t NowValue;
    uint16_t Count;
    uint16_t State;
}HAL_ADC_Buffer_t;

typedef struct
{
    HAL_Atrribute_t Atrribute;

    HAL_ADC_Buffer_t Buffer;
        
    void *Param;
    
    uint8_t  Mode;
}HAL_ADC_t;

typedef struct
{
    struct
    {
        uint16_t Channel;
        uint8_t  DataBit;
        uint8_t  Mode;
    }Atrribute;
    
    struct
    {
        uint16_t EnDMA : 1;
        uint16_t EnIrq : 1;

        uint16_t FirstBit;

        uint16_t ConverMode : 3;
    }Flag;
}HAL_ADC_Config_t;

typedef struct
{
    uint32_t (*Config)(HAL_ADC_t *adc, HAL_ADC_Config_t *config);
    uint32_t (*GetValue)(HAL_ADC_t *adc, uint16_t channel);
}HAL_ADC_Interface_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern void HAL_ADC_Register(HAL_ADC_Interface_t *ops, void *userData);

extern void HAL_ADC_Init(HAL_ADC_t *adc, HAL_ADC_Config_t *config);
extern uint16_t HAL_ADC_Value(HAL_ADC_t *adc);
extern uint16_t HAL_ADC_State(HAL_ADC_t *adc);
extern void HAL_ADC_Filter(void *param);

extern uint16_t HAL_ADC_Convert(HAL_ADC_t *adc, uint16_t channel);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
