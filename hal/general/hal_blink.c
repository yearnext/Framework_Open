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
 * @file       hal_blink.c                                                     *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-01-16                                                      *
 * @brief      blink driver component                                          *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.2018-01-16 创建文件，增加LED闪烁功能                                      *
 * 1.2018-06-28 修改文件名为“hal_blink.c”，整合框架，统一HAL层                 *
 *******************************************************************************
 */
 
/**
 * @defgroup blink driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"

/* Private define ------------------------------------------------------------*/
#define HAL_BLINK_SLEEP_STATE 0
#define HAL_BLINK_ON_STATE    1
#define HAL_BLINK_OFF_STATE   2

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void HAL_Blink_Handle(void *param)
{
    HAL_Blink_t *blink = (HAL_Blink_t *)param;
    
    switch (blink->State)
    {
        case HAL_BLINK_ON_STATE:
            blink->Callback(blink->Param, HAL_BLINK_OFF_CMD);
            blink->State = HAL_BLINK_OFF_STATE;
        
            HAL_SuperTimer_Start(blink->Timer, blink->Timeout, 0);
            break;
        case HAL_BLINK_OFF_STATE:
            if (blink->Count == 1)
            {
                HAL_Blink_Off(blink);
            }
            else
            {
                if (blink->Count)
                {
                    blink->Count--;
                }
                
                blink->Callback(blink->Param, HAL_BLINK_ON_CMD);
                blink->State = HAL_BLINK_ON_STATE;
                
                HAL_SuperTimer_Start(blink->Timer, blink->Timeout, 0);
            }
            break;
        default:
            HAL_Blink_Off(blink);
            break;
    }
}

/* Exported functions --------------------------------------------------------*/
void HAL_Blink_Init(HAL_Blink_t *blink, char *name, HALBlinkCallback callback, void *param)
{
    blink->Count    = 0;
    blink->Timeout  = 0;
    blink->Callback = callback;
    blink->State    = HAL_BLINK_SLEEP_STATE;
    blink->Param    = param;
    blink->Name     = name;
    
    HAL_SuperTimer_Init(blink->Timer, blink->Name, HAL_Blink_Handle, blink);
    
    HAL_Blink_Off(blink);
}

void HAL_Blink_On(HAL_Blink_t *blink)
{   
    blink->Count   = 0;
    blink->Timeout = 0;
    
    HAL_SuperTimer_Stop(blink->Timer);
    blink->Callback(blink->Param, HAL_BLINK_ON_CMD);
    
    blink->State = HAL_BLINK_ON_STATE;
}

void HAL_Blink_Off(HAL_Blink_t *blink)
{
    blink->Count   = 0;
    blink->Timeout = 0;
    
    HAL_SuperTimer_Stop(blink->Timer);
    blink->Callback(blink->Param, HAL_BLINK_OFF_CMD);
    
    blink->State = HAL_BLINK_OFF_STATE;
}

void HAL_Blink_Control(HAL_Blink_t *blink, int16_t count, uint16_t tick)
{
    HAL_SuperTimer_Stop(blink->Timer);
    
    blink->Count   = count;
    blink->Timeout = tick;
    
    blink->Callback(blink->Param, HAL_BLINK_ON_CMD);
    blink->State = HAL_BLINK_ON_STATE;
    
    HAL_SuperTimer_Start(blink->Timer, blink->Timeout, 0);
}

/** @}*/     /** blink driver component */

/**********************************END OF FILE*********************************/
