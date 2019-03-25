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
 * @file       fwsm_nano.c                                                     *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-12-13                                                      *
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
#include "fwsm_nano.h"

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
    
    //! 退出当前状态
    evt.Sig = FRAMEWORK_EXIT_EVENT;
    evt.Ptr = NULL;

    me->State(me, &evt);

    //! 进入新状态
    evt.Sig = FRAMEWORK_ENTRY_EVENT;
    ret = me->Temp(me, &evt);

    me->State = me->Temp;
    
    return ret;
}

__STATIC_INLINE
uint8_t Fw_Sm_Back_Handle(FwSm_t *me)
{
    uint8_t ret;
    FwSmEvt_t evt;
    
    //! 退出当前状态
    evt.Sig = FRAMEWORK_EXIT_EVENT;
    evt.Ptr = NULL;

    me->State(me, &evt);
    me->State = me->Temp;
    
    return ret;
}

__STATIC_INLINE
uint8_t Fw_Sm_ExitSub_Handle(FwSm_t *me, SmStateHandle now, SmStateHandle page)
{
    uint8_t ret;
    FwSmEvt_t evt;
    
    SmStateHandle temp = page;
    
    while(1)
    {
        //! 退出当前状态
        evt.Sig = FRAMEWORK_EXIT_EVENT;
        evt.Ptr = NULL;
        
        ret = temp(me, &evt);
        
        if (me->Temp == now)
        {
            break;
        }
        
        temp = me->Temp;
    }
    
    return ret;
}

uint8_t Fw_Sm_Evt_Handle(FwSm_t *me, FwSmEvt_t *evt)
{
    uint8_t status;
    
    FwSmState_t ret;
    
    void *ptr = (void *)me->State;
    
#ifdef FW_SM_EVENT_TABLE_ENABLE
	evt->Sig = Fm_SmTable_Filter(me, evt->Sig);
#endif

    while (1)
    {
        ret = me->State(me, evt);

__SM_RET_HANDLE:
        //! 状态转移处理
        if (ret == FW_SM_RET_TRAN)
        {
            ret = Fw_Sm_Tran_Handle(me);
            
            ptr = (void *)me->State;
            
            goto __SM_RET_HANDLE;
        }
        //! 等待处理
        else if (ret == FW_SM_RET_WAIT)
        {
            status = 0;
            break;
        }
        //! 父状态处理
        else if (ret == FW_SM_RET_SUPER)
        {
            me->State = me->Temp;
        }
        //! 子状态返回处理
        else if (ret == FW_SM_RET_BACK)
        {
            ret = Fw_Sm_Back_Handle(me);
            
            ptr = (void *)me->State;
            
            goto __SM_RET_HANDLE;
        }
        //! 子状态退出
        else if (ret == FW_SM_RET_EXIT_SUB)
        {
            Fw_Sm_ExitSub_Handle(me, me->State, (SmStateHandle)ptr);
            ptr = (void *)me->State;
            
            break;
        }
        //! 其他状态处理
        else
        {
            status = 1;
            break;
        }
    }
    
    me->State = (SmStateHandle)ptr;
    
    return status;
}

void Fw_Sm_Timer_Handle(void *param)
{
    FwSm_t *me = (FwSm_t *)param;
    FwSmEvt_t evt; 

    //! 启动SM调度器
    evt.Sig = FRAMEWORK_TIMEOUT_EVENT;
    evt.Ptr = NULL;
    Fw_Sm_Evt_Handle(me, &evt);
    
    Fw_Task_Evt_Set(me->Task, FRAMEWORK_MSG_EVENT);
    Fw_Task_Ready(me->Task);
}

/* Exported functions --------------------------------------------------------*/
void Fw_Sm_Init(FwSm_t *me, void *buf, uint16_t size)
{
    //! 初始化消息队列
    RingBufferInit(&me->Queue, buf, size);
}

uint16_t Fw_Sm_Dispatch(void *param)
{
	FwSm_t *me = (FwSm_t *)param;
	FwSmEvt_t evt;

	while (1)
	{
		//! 消息预处理
		if (RingBufferReadMirror(&me->Queue, (uint8_t *)&evt, sizeof(evt)) != sizeof(evt))
		{
			Fw_Task_Evt_Rst(me->Task);
			break;
		}

		if (Fw_Sm_Evt_Handle(me, &evt) == 0)
		{
			Fw_Task_Yeild(me->Task);
			break;
		}

		//! 移除消息
		RingBufferRead(&me->Queue, (uint8_t *)&evt, sizeof(evt));
	}

	return 0;
}

void Fw_SmTable_Init(FwSm_t *me, const FwSmTab_t *tab, uint16_t len, uint16_t init)
{
#ifdef FW_SM_EVENT_TABLE_ENABLE
	me->Table      = tab;
	me->TableLen   = len;
	me->TableState = init;
#endif
}

uint16_t Fm_SmTable_Filter(FwSm_t *sm, uint16_t event)
{
#ifdef FW_SM_EVENT_TABLE_ENABLE
	uint16_t i;
    uint16_t outState;

	const FwSmTab_t *table;

	if (!IS_PTR_NULL(sm->Table))
	{
		for (i = 0, table = &sm->Table[0]; i < sm->TableLen; i++)
		{
			if (((sm->TableState & table->NowLevel) == table->NowState) && (event == table->InputEvent || table->InputEvent == 0))
			{
				outState = (sm->TableState & ~table->NextLevel) | table->NextState;

#ifdef PUT_SM_TABLE_INFO
                printf("[SM]NowState:%p, TrigEvent:%d, SwitchState:%p, OutEvent:%d \r\n", (void *)sm->TableState, event, (void *)outState, table->OutEvent);
#endif

                sm->TableState = outState;
                event = table->OutEvent;
				break;
			}
            
            table ++;
		}
	}
#endif

	return event;
}

void Fw_Sm_Start(FwSm_t *me, uint8_t id, SmStateHandle init)
{
    FwSmEvt_t evt;

    //! 更新任务ID
    me->Task = id;
    
    //! 初始化定时器
    Fw_Timer_Init(me->Task, Fw_Sm_Timer_Handle, (void *)me);
    
    //! 初始化状态机
    me->Temp  = init;

    evt.Sig = FRAMEWORK_ENTRY_EVENT;    
    me->Temp(me, &evt);
    
    me->State = me->Temp;
}

__INLINE
uint16_t Fw_SmEvt_Post(FwSm_t *me, FwSmEvt_t *evt)
{
    uint16_t len = RingBufferWrite(&me->Queue, (void *)evt, sizeof(FwSmEvt_t));
    
    Fw_Task_Evt_Set(me->Task, FRAMEWORK_MSG_EVENT);

    return len;
}

void Fw_SmTimer_Start(FwSm_t *me, uint32_t tick)
{
    Fw_Timer_Init(me->Task, Fw_Sm_Timer_Handle, (void *)me);
    Fw_Timer_Start(me->Task, tick, 0);
}

void Fw_SmTimer_Stop(FwSm_t *me)
{
    Fw_Timer_Stop(me->Task);
}

__INLINE
void *Fw_Sm_State(FwSm_t *me)
{
    return (void *)me->State;
}

/** @}*/     /** framework state machine component */

/**********************************END OF FILE*********************************/
