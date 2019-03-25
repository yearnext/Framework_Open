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
 * @file       hal_timer.h                                                     *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-08-16                                                      *
 * @brief      hal timer driver component                                      *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_TIMER_H__
#define __HAL_TIMER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal_def.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        HAL TIMER PORT
 *******************************************************************************
 */
enum HAL_TIMER_PORT
{
    HAL_TIMER_0,  HAL_TIMER_1,  HAL_TIMER_2,  HAL_TIMER_3,  HAL_TIMER_4,
    HAL_TIMER_5,  HAL_TIMER_6,  HAL_TIMER_7,  HAL_TIMER_8,  HAL_TIMER_9,
    HAL_TIMER_10, HAL_TIMER_11, HAL_TIMER_12, HAL_TIMER_13, HAL_TIMER_14,
    HAL_TIMER_15, HAL_TIMER_16, HAL_TIMER_17, HAL_TIMER_18, HAL_TIMER_19,
    HAL_TIMER_20, HAL_TIMER_21, HAL_TIMER_22, HAL_TIMER_23, HAL_TIMER_24,
    HAL_TIMER_25, HAL_TIMER_26, HAL_TIMER_27, HAL_TIMER_28, HAL_TIMER_29,
    HAL_TIMER_30, HAL_TIMER_31, HAL_TIMER_32, HAL_TIMER_33, HAL_TIMER_34,
    HAL_TIMER_35, HAL_TIMER_36, HAL_TIMER_37, HAL_TIMER_38, HAL_TIMER_39,
    HAL_TIMER_40, HAL_TIMER_41, HAL_TIMER_42, HAL_TIMER_43, HAL_TIMER_44,
    HAL_TIMER_45, HAL_TIMER_46, HAL_TIMER_47, HAL_TIMER_48, HAL_TIMER_49,
    HAL_TIMER_MAX,
};

/**
 *******************************************************************************
 * @brief        HAL TIMER RUN MODE
 *******************************************************************************
 */
#define HAL_TIMER_ONE_SHOT_MODE                                                0
#define HAL_TIMER_PERIOD_MODE                                                  1

/**
 *******************************************************************************
 * @brief        HAL TIMER TICK MODE
 *******************************************************************************
 */
#define HAL_TIMER_CNT_UP                                                       0
#define HAL_TIMER_CNT_DOWN                                                     1

/**
 *******************************************************************************
 * @brief        HAL TIMER TICK UNIT
 *******************************************************************************
 */
#define HAL_TIMER_UNIT_US                                                      0
#define HAL_TIMER_UNIT_MS                                                      1
#define HAL_TIMER_UNIT_100MS                                                   2
#define HAL_TIMER_UNIT_SEC                                                     3
     
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      SERIAL ISR CALLBACK
 *******************************************************************************
 */
typedef void (*TimerIsrCallback)(void *param);
typedef struct
{
    TimerIsrCallback Callback;
    void *Param;
}Timer_Callback;

typedef void (*TimerSuper_t)(void *param);

/**
 *******************************************************************************
 * @brief      SERIAL HANDLE INIT TYPE
 *******************************************************************************
 */
typedef struct
{
    TimerIsrCallback Callback;
    void *Param;
    
    struct
    {
        uint32_t Tick;
        uint8_t  Port;
        uint8_t  Unit;
        uint8_t  Mode;
    }Attribute;
    
    struct
    {
        uint8_t  Inc    : 1;
        uint8_t  EnIrq  : 1;
        uint8_t  Reload : 1;
    }Flag;
}HAL_Timer_Config_t;

typedef struct
{
    HAL_Atrribute_t Attribute;

    //! 重加载Tick值
    uint32_t Tick;

    //! 底层操作句柄
    void *Param;
    //! 设备操作句柄
    HAL_Device_t *Dev;
}HAL_Timer_t;

typedef struct
{
    uint16_t (*Config)(HAL_Timer_t *timer, HAL_Timer_Config_t *config);

    void (*Start)(HAL_Timer_t *timer);
    void (*Stop)(HAL_Timer_t *timer);

    uint32_t (*GetCount)(HAL_Timer_t *timer);

    uint32_t (*Control)(HAL_Timer_t *timer, uint32_t cmd, void *arg);

}HAL_Timer_Interface_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern void HAL_Timer_Register(HAL_Timer_Interface_t *ops, void *userData);
extern void HAL_Timer_Init(HAL_Timer_t *timer, HAL_Timer_Config_t *config);
extern void HAL_Timer_Start(HAL_Timer_t *timer);
extern void HAL_Timer_Stop(HAL_Timer_t *timer);
extern uint32_t HAL_Timer_GetCount(HAL_Timer_t *timer);
extern void HAL_Timer_Isr_Handle(void *param);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
