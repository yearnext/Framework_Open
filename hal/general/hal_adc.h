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
