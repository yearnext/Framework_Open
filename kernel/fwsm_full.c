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
/* Private types -------------------------------------------------------------*/
//! SM 句柄
typedef struct
{
    //! 任务句柄
    FwTask_t Task;

    FwMQ_t Queue;
    
    //! SM Root List
    FwList_t List;
}FwSmHandle_t;

typedef struct
{
    FwSm_t *Object;
    FwSmEvt_t Event;
}FwSmMsg_t;

/* Private variables ---------------------------------------------------------*/
static FwSmHandle_t SmHandle;
static FwSmMsg_t SmQueue[FRAMEWORK_SM_COMPONENT_QUEUE_SIZE];

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void FwSm_Task_Handle(void *param)
{   
    FwSmMsg_t msg;

    while (1)
    {
        Fw_MQ_Read(&SmHandle.Queue, &msg, sizeof(msg));
        
        FwSm_Dispatch(msg.Object, &msg.Event);
    }
}

__STATIC_INLINE
uint8_t FwSmTran(FwSm_t *me)
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

void FwSm_Timer_Handle(void *param)
{
    FwSm_t *me = (FwSm_t *)param;
    FwSmEvt_t evt; 

    //! 启动SM调度器
    evt.Sig    = FRAMEWORK_TIMEOUT_EVENT;
    evt.Expand = 0;
    FwSm_Dispatch(me, &evt);
    
    //! 唤醒消息队列
    //Fw_Task_Wakeup(&me->Task);
}

void FwSmInit(FwSm_t *me, SmStateHandle init)
{
    FwSmEvt_t evt;

    Fw_Timer_Init(&me->Timer, "SM Timer", NULL, (void *)me, 0, 0);
    Fw_Timer_Stop(&me->Timer);
    
    me->Temp = init;

    evt.Sig    = FRAMEWORK_INIT_EVENT;
    evt.Expand = 0;
    me->Temp(me, &evt);
    
    me->State = me->Temp;
}

/* Exported functions --------------------------------------------------------*/
int FwSm_Component_Init(void)
{
    memset((void *)&SmHandle, 0, sizeof(SmHandle));

    Fw_Task_Init(&SmHandle.Task, "SM Task", FwSm_Task_Handle, NULL, FRAMEWORK_TASK_PRIORITY_MAX-1, 0);
    Fw_Task_Start(&SmHandle.Task);
    
    Fw_MQ_Init(&SmHandle.Queue, &SmQueue[0], sizeof(SmQueue));
    
    FwList_Init(&SmHandle.List);
    
    return 0;
}
INIT_COMPONENT_EXPORT(FwSm_Component_Init);

void FwSm_AddRoot(FwSm_t *me, char *name, SmStateHandle init)
{   
    me->Super = NULL;
    me->Name  = name;

    FwList_InsertAfter(&SmHandle.List, &me->List);
    
    FwSmInit(me, init);
}

void FwSm_AddSub(FwSm_t *root, FwSm_t *me, char *name, SmStateHandle init)
{
    me->Super = root;
    me->Name  = name;

    FwList_InsertAfter(&SmHandle.List, &me->List);
    
    FwSmInit(me, init);
}

uint8_t FwSm_Dispatch(FwSm_t *me, FwSmEvt_t *evt)
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
            ret = FwSmTran(me);
            
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

uint16_t FwSmPost(FwSm_t *me, uint32_t sig, uint32_t param)
{
    FwSmMsg_t msg;
    
    msg.Object       = me;
    msg.Event.Sig    = sig;
    msg.Event.Expand = param;
    
    return Fw_MQ_Send(&SmHandle.Queue, (void *)&msg, sizeof(msg));
}

uint16_t FwSmEmit(FwSm_t *me, uint32_t sig)
{
    FwSmMsg_t msg;
    
    msg.Object       = me;
    msg.Event.Sig    = sig;
    msg.Event.Expand = 0;

    return Fw_MQ_Send(&SmHandle.Queue, (void *)&msg, sizeof(msg));
}

void FwSm_Timer_Start(FwSm_t *me, uint32_t tick)
{
    Fw_Timer_Init(&me->Timer, "SM Timer", FwSm_Timer_Handle, (void *)me, tick, 0);
    Fw_Timer_Start(&me->Timer);
}

void FwSm_Timer_Stop(FwSm_t *me)
{
    Fw_Timer_Stop(&me->Timer);
}

__INLINE
void *FwSm_State(FwSm_t *me)
{
    return (void *)me->State;
}

/** @}*/     /** framework state machine component */

/**********************************END OF FILE*********************************/
