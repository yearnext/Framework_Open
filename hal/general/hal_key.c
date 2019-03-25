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
 * @file       hal_key.c                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2015-06-15                                                      *
 * @brief      key driver component                                            *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 2015-06-15 创建文件 原名“bsp_key.c” 实现按键的检测处理，通过FSM实现      *
 * 2. 2015-08-25 通过函数数组实现底层的状态迁移，加快执行速度                  *
 * 3. 2016-03-02 增加面向对象特性                                              *
 * 4. 2017-02-23 修改文件名为“fw_signal.c”,重构组件，使用框架API实现           *
 * 5. 2018-05-16 修改文件名为“HAL_key.c”,重构组件，使用HAL层API实现            *
 * 6. 2018-06-28 修改文件名为“hal_key.c”,统一HAL层架构                         *
 *******************************************************************************
 */

/**
 * @defgroup key driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"

/* Private define ------------------------------------------------------------*/
//! 按键状态迁移
#define KEY_STATE_TRNASFER(now_key, new_state) _st((now_key)->State = (new_state);)

//! 按键消息发送函数
#define KEY_MSG_Send(msg, dev) _st((msg).MsgType  = HAL_DEVICE_KEY_MSG; \
                                   (msg).KeyState = (dev)->State; \
                                   (msg).KeyTick  = (dev)->Tick; \
                                   (msg).KeyValue = (dev)->Value; \
                                   HAL_Msg_Send(&(msg));)
  
/* Private typedef -----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void HAL_Key_Init(HAL_Key_t *key, HALKeyScan scan, uint16_t tick, uint16_t flag)
{
    key->Scan = scan;
    key->Flag = flag;

    key->FilterTick = 0;
    key->FilterValue = 0;
    key->State = KEY_RELEASE_STATE;
    key->Tick  = 0;
    key->Value = 0;
    
    HAL_SuperTimer_Init(key->Timer, "Key Driver", HAL_Key_Scan, key);
    HAL_SuperTimer_Start(key->Timer, tick/FRAMEWORK_TICK_TIME, FW_TIM_EN_PERIOD);
}

void HAL_Key_Fini(HAL_Key_t *key)
{
    HAL_SuperTimer_Stop(key->Timer);
}

void HAL_Key_Scan(void *param)
{
    HAL_Key_t *key = (HAL_Key_t *)param;
    
    HAL_MSG_t msg;
    
    uint16_t nowValue = key->Scan();
    
    uint8_t change = 0;

    //! 1. 按键电平检测
    if (nowValue != key->FilterValue)
    {
        key->FilterValue = nowValue;
        key->FilterTick = 0;
        
        change = 1;
    }

    //! 2. 更新按键时钟
    if (key->FilterTick < 0xFFFF)
    {
        key->FilterTick ++;
    }
    
    //! 3. 按键状态机处理
    switch (key->State)
    {
        case KEY_RELEASE_STATE:
            if (change)
            {
                //! 按键状态迁移
                //! 迁移至按下操作滤波状态
                KEY_STATE_TRNASFER(key, KEY_RELEASE_FILTER_STATE);
            }
            break;
        case KEY_RELEASE_FILTER_STATE:
            if (change)
            {
                //! 按键状态迁移
                //! 迁移至按键松开状态
                KEY_STATE_TRNASFER(key, KEY_RELEASE_STATE);
                
                //! 确认为按键抖动
                if (key->Value == key->FilterValue)
                {
                    KEY_STATE_TRNASFER(key, KEY_RELEASE_STATE);
                }
            }
            else
            {   
                //! 滤波超时
                if (key->FilterTick >= HAL_KEY_FILTER_TICK)
                {
                    //! 更新tick
                    key->Tick = key->FilterTick;
                    
                    //! 更新键值
                    key->Value = key->FilterValue;
                    
                    //! 按键状态迁移
                    //! 迁移至按键按下边沿状态
                    KEY_STATE_TRNASFER(key, KEY_PRESS_EDGE_STATE);
                    
                    //! 按键状态迁移
                    //! 迁移至按键按住状态
                    //! 发送相关消息或事件
                    KEY_MSG_Send(msg, key);
                    
                    //! 按键状态迁移
                    //! 迁移至按键按住状态
                    KEY_STATE_TRNASFER(key, KEY_PRESS_STATE);
                }
            }
            break;
        case KEY_PRESS_STATE:
            if (change)
            {
                //! 按键状态迁移
                //! 迁移至按键松开滤波状态
                KEY_STATE_TRNASFER(key, KEY_PRESS_FILTER_STATE);
            }
            else
            {   
                key->Tick = key->FilterTick;
                
                //! 使能了长按检测
                if (HAL_Flag_Get(key->Flag, HAL_KEY_LONG_SCAN))
                {
                    //! 每秒发送一个消息
                    if ((key->Tick % HAL_KEY_SECOND_TICK) == 0)
                    {
                        //! 按键状态迁移
                        //! 发送相关消息或事件
                        KEY_MSG_Send(msg, key);
                    }
                }
            }
            break;
        case KEY_PRESS_FILTER_STATE:
            if (change)
            {
                //! 按键状态迁移
                //! 迁移至按键按下边沿响应状态
                key->FilterTick = key->Tick;
                
                //! 确认为按键抖动
                if (key->Value == key->FilterValue)
                {
                    KEY_STATE_TRNASFER(key, KEY_PRESS_STATE);
                }
            }
            else
            {   
                //! 滤波超时
                if (key->FilterTick >= HAL_KEY_FILTER_TICK)
                {
                    //! 按键状态迁移
                    //! 迁移至按键松开边沿状态
                    KEY_STATE_TRNASFER(key, KEY_RELEASE_EDGE_STATE);
                
                    //! 发送相关消息或事件
                    KEY_MSG_Send(msg, key);
                    
                    //! 清空计数值
                    key->Tick = 0;

                    //! 更新键值
                    key->Value = key->FilterValue;
                    
                    //! 迁移至按键按下边沿状态
                    if (key->Value == HAL_KEY_VALUE_NOP)
                    {
                        //! 按键状态迁移
                        //! 迁移至按键松开状态
                        KEY_STATE_TRNASFER(key, KEY_RELEASE_STATE);
                    }
                    else
                    {
                        //! 按键状态迁移
                        //! 迁移至按键松开状态
                        KEY_STATE_TRNASFER(key, KEY_RELEASE_FILTER_STATE);
                    }
                }
            }
            break;
//            case KEY_RELEASE_EDGE_STATE:
//                break;
        default:
            break;
    }
}

/** @}*/     /** key driver component */

/**********************************END OF FILE*********************************/
