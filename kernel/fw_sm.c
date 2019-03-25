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
 * @file       fw_sm.c                                                         *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      framework state machine component source files                  *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20170110    创建文件fw_sm.c         		                               *
 *******************************************************************************
 */

/**
 * @defgroup framework state machine component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_sm.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
__STATIC_INLINE
uint8_t Fw_Sm_Tran_Handle(FwSm_t *me)
{
    uint8_t ret;
    
    FwSmEvt_t evt;
    
    evt.Sig = FRAMEWORK_EXIT_EVENT;
    me->State(me, &evt);

    evt.Sig = FRAMEWORK_ENTRY_EVENT;
    ret = me->Temp(me, &evt);

    me->State = me->Temp;
    
    return ret;
}

void Fw_Sm_Timer_Handle(void *param)
{
    FwSm_t *me = (FwSm_t *)param;
    FwSmEvt_t evt; 

    //! 启动SM调度器
    evt.Sig = FRAMEWORK_TIMEOUT_EVENT;
    evt.Ptr = NULL;
    Fw_Sm_Dispatch(me, &evt);
    
    //! 唤醒消息队列
    Fw_Task_Wakeup(&me->Task);
}

uint16_t Fw_Sm_Task_Handle(void *param)
{
    FwSm_t *me = (FwSm_t *)param;
    FwSmEvt_t evt;
    
    while (1)
    {
        //! 消息预处理
        Fw_MQ_Read_Mirror(&me->Queue, &evt, sizeof(evt));
        
        if (Fw_Sm_Dispatch(me, &evt) == 0)
        {
            Fw_Task_Sleep(&me->Task);
            break;
        }

        //! 移除消息
        Fw_MQ_Read(&me->Queue, &evt, sizeof(evt));
    }
    
    return 0;
}

/* Exported functions --------------------------------------------------------*/
void Fw_Sm_Init(FwSm_t *me, void *buf, uint16_t size, SmStateHandle init)
{
    FwSmEvt_t evt;

    Fw_Task_Init(&me->Task, "SM Task", Fw_Sm_Task_Handle, (void *)me);
    Fw_Task_Startup(&me->Task, FRAMEWORK_TASK_PRIORITY_MAX-2, 0);
    
    Fw_Timer_Init(&me->Task.Timer, "SM Timer", NULL, (void *)me);
    Fw_Timer_Stop(&me->Task.Timer);
    
    Fw_MQ_Init(&me->Queue, (uint8_t *)buf, size);

    me->Temp  = init;

    evt.Sig = FRAMEWORK_ENTRY_EVENT;    
    me->Temp(me, &evt);
    
    me->State = me->Temp;
}

uint8_t Fw_Sm_Dispatch(FwSm_t *me, FwSmEvt_t *evt)
{
    uint8_t status;
    
    FwSmState_t ret;
    
    while (1)
    {
        ret = me->State(me, evt);

__SM_RET_HANDLE:
        //! 状态转移处理
        if (ret == FW_SM_RET_TRAN)
        {
            ret = Fw_Sm_Tran_Handle(me);
            
            goto __SM_RET_HANDLE;
        }
        //! 等待处理
        else if (ret == FW_SM_RET_WAIT)
        {
            status = 0;
            break;
        }
        //! 其他状态处理
        else
        {
            status = 1;
            break;
        }
    }
    
    return status;
}

__INLINE
uint16_t Fw_SmEvt_Post(FwSm_t *me, FwSmEvt_t *evt)
{
    return Fw_MQ_Send(&me->Queue, (void *)evt, sizeof(FwSmEvt_t));
}

void Fw_SmTimer_Start(FwSm_t *me, uint32_t tick)
{
    Fw_Timer_Init(&me->Task.Timer, "SM Timer", Fw_Sm_Timer_Handle, (void *)me);
    Fw_Timer_Startup(&me->Task.Timer, tick, 0);
}

void Fw_SmTimer_Stop(FwSm_t *me)
{
    Fw_Timer_Stop(&me->Task.Timer);
}

__INLINE
void *Fw_Sm_State(FwSm_t *me)
{
    return (void *)me->State;
}

/** @}*/     /** framework state machine component */

/**********************************END OF FILE*********************************/
