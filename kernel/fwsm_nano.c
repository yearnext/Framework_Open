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
#include "fw_sm.h"
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/
#define FwSm_Get_Obj(id) (&FwSm[id])
#define FwSm_Read_Msg(evt) if (FwBufRead(&FwSmMgr.Queue, ((uint8_t *)evt), sizeof(FwSmMsg_t)) != sizeof(FwSmMsg_t)) \
                               {FwTask_Clr_Evt(FRAMEWORK_MSG_EVENT); return 0;}                                     \
                           else{if (FwBufUsed(&FwSmMgr.Queue) == 0){FwTask_Clr_Evt(FRAMEWORK_MSG_EVENT);}}

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	uint8_t Id;
	
	FwBuf_t Queue;
	FwSmMsg_t Buf[FRAMEWORK_SM_QUEUE_SIZE];
}FwSmMgr_t;

/* Private variables ---------------------------------------------------------*/
FwSmMgr_t FwSmMgr;

/* Exported variables --------------------------------------------------------*/
FwSm_t FwSm[FW_SM_MAX];

/* Private functions ---------------------------------------------------------*/
__STATIC_INLINE
uint8_t FwSm_Tran_Handle(FwSm_t *me)
{
    uint8_t ret;
    FwSmMsg_t msg;
    
    //! 退出当前状态
    msg.Sig = FRAMEWORK_EXIT_EVENT;

    me->State(me, &msg);

    //! 进入新状态
    msg.Sig = FRAMEWORK_ENTRY_EVENT;
    ret = me->Temp(me, &msg);

    me->State = me->Temp;
    
    return ret;
}

__STATIC_INLINE
uint8_t FwSm_Back_Handle(FwSm_t *me)
{
    uint8_t ret;
    FwSmMsg_t msg;
    
    //! 退出当前状态
    msg.Sig = FRAMEWORK_EXIT_EVENT;

    ret = me->State(me, &msg);
    me->State = me->Temp;
    
    return ret;
}

__STATIC_INLINE
uint8_t FwSm_ExitSub_Handle(FwSm_t *me, SmStateHandle now, SmStateHandle page)
{
    uint8_t ret;
    FwSmMsg_t msg;
    
    SmStateHandle temp = page;
    
    while(1)
    {
        //! 退出当前状态
        msg.Sig = FRAMEWORK_EXIT_EVENT;

        ret = temp(me, &msg);
        
        if (me->Temp == now)
        {
            break;
        }
        
        temp = me->Temp;
    }
    
    return ret;
}

__STATIC_INLINE
uint8_t FwSm_Evt_Handle(FwSm_t *me, FwSmMsg_t *evt)
{
    uint8_t status = 0;
    
    if (IS_PTR_NULL(me))
    {
        me = FwSm_Get_Obj(evt->Id);
        
        if (IS_PTR_NULL(me))
        {
#ifdef PUT_FW_SM_INFO
            Fw_Console_Put("[%d][Fw SM][Error]Get Sm Handle Failed\r\n", Fw_Tick_Get());
#endif
            return 1;
        }
	}

    FwSmState_t ret;
    
    void *ptr = (void *)me->State;

    while (1)
    {
        ret = me->State(me, evt);

__SM_RET_HANDLE:
        //! 状态转移处理
        if (ret == FW_SM_RET_TRAN)
        {
            ret = FwSm_Tran_Handle(me);
            
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
            me = FwSm_Get_Obj(me->SuperId);
        }
        //! 子状态返回处理
        else if (ret == FW_SM_RET_BACK)
        {
            ret = FwSm_Back_Handle(me);
            
            ptr = (void *)me->State;
            
            goto __SM_RET_HANDLE;
        }
        //! 子状态退出
        else if (ret == FW_SM_RET_EXIT_SUB)
        {
            FwSm_ExitSub_Handle(me, me->State, (SmStateHandle)ptr);
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

void FwSm_Timer_Handle(void *param)
{
    FwSm_t *me = (FwSm_t *)param;
//    FwSmMsg_t msg; 

//    //! 启动SM调度器
//    msg.Sig = FRAMEWORK_TIMEOUT_EVENT;
//    msg.Id = me->SmId;
//    FwSm_Evt_Handle(me, &msg);
    
    FwSm_Post_Msg(me->SmId, FRAMEWORK_TIMEOUT_EVENT);
}

/* Exported functions --------------------------------------------------------*/
void FwSm_Task_Init(uint8_t taskId)
{
	memset(&FwSmMgr, 0, sizeof(FwSmMgr));
	
	FwBufInit(&FwSmMgr.Queue, &FwSmMgr.Buf[0], sizeof(FwSmMgr.Buf));
	
	FwSmMgr.Id = taskId;
}

uint16_t FwSm_Task_Handle(uint8_t taskid, uint16_t evt)
{
	FwSmMsg_t msg;

	_unused(taskid);
	if (Fw_Evt_Get(evt, FRAMEWORK_MSG_EVENT))
	{
		FwSm_Read_Msg(&msg);
		
		FwSm_Evt_Handle(NULL, &msg);
	}
	
	return 0;
}

void Fw_Sm_Init(uint8_t smId, uint8_t timerId, SmStateHandle init)
{
    FwSmMsg_t msg;

	FwSm_t *me = &FwSm[smId];

	me->StateCode = 0;
	me->SuperId = FW_SM_NULL;
	me->SmId    = smId;
	me->TimerId = timerId;

    //! 初始化定时器
    Fw_Timer_Init(me->TimerId, FwSm_Timer_Handle, (void *)me);
    
    //! 初始化状态机
    me->Temp  = init;

    msg.Sig = FRAMEWORK_INIT_EVENT;    
    me->Temp(me, &msg);
    
    me->State = me->Temp;
}

__INLINE
uint16_t FwSm_Release_Wait(FwSm_t *me)  
{
    uint16_t sig = me->Wait;
    
    if (me->Wait)
    {
        me->Wait = 0;
    }
    
    return sig;
}

__INLINE
void FwSm_Clear_Wait(FwSm_t *me)  
{
    me->Wait = 0;
}

void FwSm_Post_Msg(uint16_t sm, uint16_t sig)
{
	FwSmMsg_t msg;
	
	msg.Id = (uint8_t)sm;
	msg.Sig = sig;

	if (FwBufWrite(&FwSmMgr.Queue, (uint8_t *)&msg, sizeof(msg)) != sizeof(msg))
    {
#ifdef PUT_FW_SM_INFO
        Fw_Console_Put("[%d][Fw SM][Error]Write SM Queue Failed, Because Queue Is Full\r\n", Fw_Tick_Get());
#endif
    }
	
	FwTask_Set_Evt(FwSmMgr.Id, FRAMEWORK_MSG_EVENT);
}

void FwSm_Timer_Start(FwSm_t *me, FwTick_t tick)
{
    if (tick == 0)
    {
        FwSm_Post_Msg(me->SmId, FRAMEWORK_TIMEOUT_EVENT);
    }
    else
    {
        Fw_Timer_Init(me->TimerId, FwSm_Timer_Handle, (void *)me);
        Fw_Timer_Start(me->TimerId, tick, 0);
    }
}

void FwSm_Timer_Stop(FwSm_t *me)
{
    Fw_Timer_Stop(me->TimerId);
}

uint32_t FwSm_Timer_Tick(FwSm_t *me)
{
    return Fw_Timer_Tick(me->TimerId);
}

uint16_t Fw_Sm_Code(FwSm_t *me)
{
    return me->StateCode;
}

void Fw_Sm_SetCode(FwSm_t *me, uint16_t sCode)
{
    me->StateCode = sCode;
}

__INLINE
void *Fw_Sm_State(uint16_t smId)
{
    FwSm_t *me = &FwSm[smId];

    return (void *)me->State;
}

/** @}*/     /** framework state machine component */

/**********************************END OF FILE*********************************/
