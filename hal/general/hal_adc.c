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
 * @file       hal_adc.c                                                       *
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
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
 
/**
 * @defgroup adc driver application component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"
#include <string.h>

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef ENABLE_HAL_ADC_DRIVER
struct
{
    HAL_Device_t        Parent;
    HAL_ADC_Interface_t Ops;
}DeviceADC;
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#ifdef ENABLE_HAL_ADC_DRIVER
void HAL_ADC_Register(HAL_ADC_Interface_t *ops, void *userData)
{    
    memset(&DeviceADC, 0, sizeof(DeviceADC));

    DeviceADC.Ops.Config   = ops->Config;
    DeviceADC.Ops.GetValue = ops->GetValue;
    
#if defined(ENABLE_HAL_DRIVER_COMPONENT)
    DeviceADC.Parent.UserData = userData;

    HAL_Interface_t halDevOps;
    
    halDevOps.Init    = NULL;
    halDevOps.Fini    = NULL;
    halDevOps.Open    = NULL;
    halDevOps.Close   = NULL;
    halDevOps.Read    = NULL;
    halDevOps.Write   = NULL;
    halDevOps.Control = NULL;
    
    HAL_Device_Register(&DeviceADC.Parent, HAL_ADC_STR, &halDevOps, HAL_Flag_Encode(HAL_DEVICE_ADC, HAL_WRITE_FLAG|HAL_READ_FLAG));
#endif
}

void HAL_ADC_Init(HAL_ADC_t *adc, HAL_ADC_Config_t *config)
{
    memset(adc, 0, sizeof(HAL_ADC_t));
    
    adc->Atrribute.Port  = config->Atrribute.Channel;
    adc->Atrribute.Flag  = *((uint16_t *)&config->Flag);
    adc->Atrribute.State = HAL_DEVICE_INIT;
    adc->Mode            = config->Atrribute.Mode;
    
    if (!IS_PTR_NULL(DeviceADC.Ops.Config))
    {
        DeviceADC.Ops.Config(adc, config);
    }
}

uint16_t HAL_ADC_Value(HAL_ADC_t *adc)
{
    return adc->Buffer.NowValue;
}

uint16_t HAL_ADC_State(HAL_ADC_t *adc)
{
    return (adc->Atrribute.State == HAL_DEVICE_IDLE) ? (1) : (0);
}

void HAL_ADC_Filter(void *param)
{
    HAL_ADC_t *adc = (HAL_ADC_t *)param;
    
    switch (adc->Buffer.State)
    {
        case HAL_ADC_SCAN_INIT:
        {
            adc->Buffer.Count = 0;
            adc->Buffer.NowValue = 0;
            adc->Buffer.ScanValue = 0;
            adc->Buffer.TempValue = 0;

            adc->Buffer.State = HAL_ADC_SCAN_HANDLE;
            break;
        }
        case HAL_ADC_SCAN_HANDLE:
        {
            uint32_t adcValue;

            if (!IS_PTR_NULL(DeviceADC.Ops.GetValue))
            {
                adcValue = DeviceADC.Ops.GetValue(adc, adc->Atrribute.Port);
            }
            else
            {
                break;
            }

            adc->Buffer.ScanValue  = adcValue;
            adc->Buffer.TempValue += adcValue;

            if (++ adc->Buffer.Count >= 8)
            {
                adc->Buffer.NowValue  = adc->Buffer.TempValue / 8;
                adc->Buffer.TempValue = adc->Buffer.NowValue;
                
                adc->Buffer.Count     = 1;
                
                adc->Atrribute.State = HAL_DEVICE_IDLE;
            }
            
            adc->Buffer.State = HAL_ADC_SCAN_HANDLE;
            break;
        }
        case HAL_ADC_SCAN_END:
        {
            adc->Buffer.Count = 0;
            adc->Buffer.NowValue = 0;
            adc->Buffer.ScanValue = 0;
            adc->Buffer.TempValue = 0;
            break;
        }
        default:
            break;
    }
}

uint16_t HAL_ADC_Convert(HAL_ADC_t *adc, uint16_t channel)
{
    if (!IS_PTR_NULL(DeviceADC.Ops.GetValue))
    {
        return DeviceADC.Ops.GetValue(adc, channel);
    }
    
    return 0;
}

#endif

/** @}*/     /** hal adc driver component */

/**********************************END OF FILE*********************************/
