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
 * @file       fw_core.c                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework core interface source files                           *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
 *******************************************************************************
 */

/**
 * @defgroup framework core interface
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"
#include <string.h>

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       bit map
 *******************************************************************************
 */
static uint8_t __CONST FwBitMap[] =
{
	/* 00 */ 0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* 10 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* 20 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* 30 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* 40 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* 50 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* 60 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* 70 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* 80 */ 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* 90 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* A0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* B0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* C0 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* D0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* E0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	/* F0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
};

/* Exported variables --------------------------------------------------------*/
//! 框架事件句柄
FwCore_t FwCore;

/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       任务时间片轮询处理函数
 * @param       [in/out]  *param       任务回调参数
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
void FwTask_Timer_Handle(void *param)
{
    FwTask_t *task = (FwTask_t *)param;
    
    Fw_Task_Ready(task);
}

/**
 *******************************************************************************
 * @brief       任务延时处理函数
 * @param       [in/out]  *param       任务回调参数
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
static 
void FwTask_Delay_Handle(void *param)
{
    FwTask_t *task = (FwTask_t *)param;
    
    Fw_Task_Ready(task);
}

/**
 *******************************************************************************
 * @brief       空闲任务处理函数
 * @param       [in/out]  *param       任务回调参数
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
static 
void FwTask_Idle_Handle(void)
{
#ifdef FW_PUT_IDLE_INFO
	Fw_Core_Log("Framework Is Idle");
#endif

	if (!IS_PTR_NULL(FwIdleHook))
	{
		FwIdleHook();
	}
}

/**
 *******************************************************************************
 * @brief       消息邮箱定时器处理函数
 * @param       [in/out]  *param      参数
 * @return      [in/out]  void
 * @note        私有，用户不可直接访问
 *******************************************************************************
 */
static
void FwMQ_Timer_Callback(void *param)
{
    FwMQ_t *queue = (FwMQ_t *)param;
    
    if (queue->Task->State == FW_TASK_YEILD)
    {
        //! 消息已更新
        if (FwBuf_Used(&queue->Buffer) >= sizeof(FwMsg_t))
        {
            Fw_Task_Ready(queue->Task);
            
            queue->Task = NULL;
        }
        else
        {
            queue->Task->State = FW_TASK_SLEEP;
        }
    }
}

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       进入临界点函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_Enter_Critical(void)
{
    if (FwIsrLock == 0)
    {
        Fw_IRQ_Disable();

        FwIsrLock++;
    }
    else 
    {
        if (FwIsrLock < 0xFFFF)
        {
            FwIsrLock++;
        }
    }
}

/**
 *******************************************************************************
 * @brief       退出临界点函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_Exit_Critical(void)
{
    if (FwIsrLock)
    {
        FwIsrLock --;
        
        if (FwIsrLock == 0)
        {
            Fw_IRQ_Enable();
        }
    }
}

/**
 *******************************************************************************
 * @brief       任务初始化函数
 * @param       [in/out]  *task        任务句柄
 * @param       [in/out]  *name        任务名称
 * @param       [in/out]  handle       任务处理回调
 * @param       [in/out]  *param       任务回调参数
 * @param       [in/out]  priority     任务优先级
 * @param       [in/out]  priority     任务优先级
 * @param       [in/out]  flag         任务配置
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_Task_Init(FwTask_t *task, char *name, void *handle, void *param, uint8_t priority, uint8_t flag)
{
	memset(task, 0, sizeof(FwTask_t));
    
	if (priority >= FRAMEWORK_TASK_PRIORITY_MAX)
	{
#ifdef FW_PUT_INIT_INFO
		Fw_Core_Error("[FWERR-001]Task Name:%s, Set Priority:%d, New Priority:%d! \r\n", name, priority, (FRAMEWORK_TASK_PRIORITY_MAX - 1));
#endif

		priority = FRAMEWORK_TASK_PRIORITY_MAX - 1;
	}

    task->Handle   = handle;
    task->Param    = param;
    task->Priority = priority;
    task->Flag     = flag;
	task->Name     = name;

	//! 任务定时器初始化
	Fw_Timer_Init(&task->Timer, task->Name, FwTask_Delay_Handle, task, 0, 0);

    //! 设置任务运行状态模式
#ifdef ENABLE_FRAMEWORK_PROTOTHREAD
    if (Fw_Flag_Get(task->Flag, FW_TASK_EN_PROTOTHREAD))
    {
        Fw_PT_Init(task);
    }
#endif
    
    FwList_Init(&task->List);
}

/**
 *******************************************************************************
 * @brief       任务启动函数
 * @param       [in/out]  *task        任务句柄
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_Task_Start(FwTask_t *task)
{
    Fw_Task_Ready(task);
}

/**
 *******************************************************************************
 * @brief       任务延时函数
 * @param       [in/out]  tick    任务延时时间
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
void Fw_Task_Delay(uint32_t tick)
{
    //! 挂起任务
    FwCurTask->State = FW_TASK_DELAY;

    //! 设置超时定时器
    Fw_Timer_Set_Callback(&FwCurTask->Timer, FwTask_Delay_Handle, (void *)FwCurTask);
    Fw_Timer_Restart(&FwCurTask->Timer, tick, 0);
}

/**
 *******************************************************************************
 * @brief       任务阻塞函数
 * @param       [in/out]  tick       任务延时时间
 * @param       [in/out]  *handle    阻塞超时处理函数
 * @param       [in/out]  *param     阻塞超时处理参数
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_Task_Yeild(uint32_t timeout, void *handle, void *param)
{
    FwCurTask->State = FW_TASK_YEILD;
    
    Fw_Timer_Set_Callback(&FwCurTask->Timer, (FwTimerCallback)handle, param);
    Fw_Timer_Restart(&FwCurTask->Timer, timeout, 0);
}

/**
 *******************************************************************************
 * @brief       任务休眠函数
 * @param       [in/out]  *task        任务句柄
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_Task_Sleep(FwTask_t *task)
{
    task->State = FW_TASK_SLEEP;

    FwList_Remove(&task->List);
}

/**
 *******************************************************************************
 * @brief       将任务设置为就绪状态
 * @param       [in/out]  *task        任务句柄
 * @return      [in/out]  void
 * @note        私有，用户不可直接访问
 *******************************************************************************
 */
__INLINE
void Fw_Task_Ready(FwTask_t *task)
{
    FwList_t *p;
    FwList_t *head;
    
	Fw_Enter_Critical();

#ifdef FW_PUT_TASK_READY_INFO
	Fw_Log("[Begin Task Process]\r\n");
	Fw_Put_Task_List();
#endif

    //! 激活任务
    if (task->State == FW_TASK_INIT     \
		|| task->State == FW_TASK_DELAY \
        || task->State == FW_TASK_YEILD \
        || task->State == FW_TASK_SLEEP)
    {
        task->State = FW_TASK_READY;
    }

    //! 移除操作
    FwList_Remove(&task->List);
    
    //! 查找操作
    for (head = &FwActiveTaskTable[task->Priority], p = head->Next; p != head; p = p->Next);
    
    //! 在末尾插入
	FwList_InsertBefore(p, &task->List);
	
	//! 将任务加入任务就绪表中
    _mem_bit_set(FwTaskReadyTable, 8, task->Priority);

#ifdef FW_PUT_TASK_READY_INFO
	Fw_Log("[End Task Process]\r\n");
	Fw_Put_Task_List();
#endif

	Fw_Exit_Critical();
}

/**
 *******************************************************************************
 * @brief       任务唤醒函数
 * @param       [in/out]  *task        任务句柄
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_Task_Wakeup(FwTask_t *task)
{
    Fw_Task_Ready(task);
}

/**
 *******************************************************************************
 * @brief       任务注销函数
 * @param       [in/out]  *task        任务句柄
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
void Fw_Task_Fini(FwTask_t *task)
{
    //! todo: 待添加
}

/**
 *******************************************************************************
 * @brief       读取当前任务配置位
 * @param       [in/out]  flag      需要读取的配置位
 * @return      [in/out]  return    读取到的配置位
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
uint32_t Fw_Self_Flag_Get(uint32_t flag)
{
    return Fw_Flag_Get(FwCurTask->Flag, flag);
}

/**
 *******************************************************************************
 * @brief       消息初始化函数
 * @param       [in/out]  *queue      消息队列句柄
 * @param       [in/out]  *buf        缓存
 * @param       [in/out]  len         缓存区长度
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_MQ_Init(FwMQ_t *queue, void *buf, uint16_t len)
{
    FwBuf_Init(&queue->Buffer, (uint8_t *)buf, len);
    
    queue->Task = NULL;
}

/**
 *******************************************************************************
 * @brief       消息队列注销函数
 * @param       [in/out]  *queue      消息队列句柄
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_MQ_Fini(FwMQ_t *queue)
{
    FwBuf_Fini(&queue->Buffer);
}

/**
 *******************************************************************************
 * @brief       消息发送函数
 * @param       [in/out]  *queue      消息队列句柄
 * @param       [in/out]  *msg        发送消息
 * @param       [in/out]  size        发送消息长度
 * @return      [in/out]  size        发送消息长度
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
uint16_t Fw_MQ_Send(FwMQ_t *queue, void *msg, uint16_t size)
{
    uint16_t result = FwBuf_Write(&queue->Buffer, (uint8_t *)msg, size);
    
    if (!IS_PTR_NULL(queue->Task))
    {
        if (queue->Task->State != FW_TASK_DELAY)
        {
            Fw_Task_Ready(queue->Task);
            queue->Task = NULL;
        }
    }
    
    return result;
}

/**
 *******************************************************************************
 * @brief       消息接收函数
 * @param       [in/out]  *queue      消息队列句柄
 * @param       [in/out]  *msg        消息接收缓冲区
 * @param       [in/out]  size        消息大小
 * @param       [in/out]  tick        阻塞时间
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
FwErr_t Fw_MQ_Recv(FwMQ_t *queue, void *msg, uint16_t size, size_t tick)
{
    if (FwBuf_Read(&queue->Buffer, (uint8_t *)msg, size) != size)
    {
        //! 设置队列等待任务
        queue->Task = FwCurTask;

        if (tick > 0)
        {
            Fw_Task_Yeild(tick, (void *)FwMQ_Timer_Callback, (void *)queue);
        }
        else
        {
            Fw_Task_Sleep(FwCurTask);
        }
        
        return FW_ERR_EMPTY;
    }
    else
    {
        return FW_ERR_NONE;
    }
}

/**
 *******************************************************************************
 * @brief       消息接收函数
 * @param       [in/out]  *queue      消息队列句柄
 * @param       [in/out]  *msg        消息接收缓冲区
 * @param       [in/out]  size        消息大小
 * @param       [in/out]  tick        阻塞时间
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
FwErr_t Fw_MQ_Recv_Mirror(FwMQ_t *queue, void *msg, uint16_t size)
{
    if (FwBuf_ReadMirror(&queue->Buffer, (uint8_t *)msg, size) != size)
    {       
        //! 设置队列等待任务
        queue->Task = FwCurTask;
        
        Fw_Task_Sleep(FwCurTask);

        return FW_ERR_EMPTY;
    }
    else
    {
        return FW_ERR_NONE;
    }
}

/**
 *******************************************************************************
 * @brief       设置任务空闲钩子
 * @param       [in/out]  *hook       任务空闲钩子函数
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
void FwHook_Set_Idle(void *hook)
{
	FwIdleHook = (void(*)(void))hook;
}

/**
 *******************************************************************************
 * @brief       框架内核初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_Core_Init(void)
{
    uint16_t i;
    
    //! 初始化中断锁
    FwIsrLock = 0;

    Fw_Enter_Critical();
    
    //! 初始化系统事件
    FwCoreEvent = 0;
    
    //! 初始化任务就绪表
    for (i = 0; i<_dimof(FwActiveTaskTable); i++)
    {
        FwList_Init(&FwActiveTaskTable[i]);
    }

    for (i=0; i<_dimof(FwTaskReadyTable); i++)
    {
        FwTaskReadyTable[i] = 0;
    }

    //! 初始化当前任务指针
    FwCurTask = NULL;

	//! 输出系统信息
	Fw_Put_Info();

    //! 框架组件初始化
    Fw_Component_Init();

    //! HAL初始化
    Fw_HAL_Init();

	//! 硬件初始化
    Fw_Board_Init();

	//! 应用软件初始化
    Fw_App_Init();

    Fw_Exit_Critical();
}

/**
 *******************************************************************************
 * @brief       系统内核启动函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_Core_Startup(void)
{
    uint16_t prio;
    uint16_t i;
    FwList_t *list;
    
    while (1)
    {
#ifndef ENABLE_FRAMEWORK_TIMER_REAL
        //! 处理定时器任务
        if (Fw_Evt_Get(FwCoreEvent, FRAMEWORK_TICK_EVENT))
        {
            Fw_Enter_Critical();
        
            Fw_Evt_Clr(FwCoreEvent, FRAMEWORK_TICK_EVENT);
            
            Fw_Exit_Critical();
            
            FwTimer_Component_Handle();
        }
#endif

        //! 1. 获取就绪任务
        for (i=0; i<_dimof(FwTaskReadyTable); i++)
        {
            if (FwTaskReadyTable[i])
            {
                prio = FwBitMap[FwTaskReadyTable[i]] + (i * 8);
                
                if (prio >= FRAMEWORK_TASK_PRIORITY_MAX)
                {
                    goto __CLEAR_TASK_READY_FLAG;
                }
                
                //! 2. 获取就绪任务句柄
                list = FwList_DeleteAfter(&FwActiveTaskTable[prio]);
                
                if (IS_PTR_NULL(list))
                {
                    goto __CLEAR_TASK_READY_FLAG;
                }
                
                FwCurTask = (FwTask_t *)FwListEntry(list, FwTask_t, List);
                
                //! 3. 执行就绪任务
                if (!IS_PTR_NULL(FwCurTask))
                {
                    if (!IS_PTR_NULL(FwCurTask->Handle))
                    {
                        FwCurTask->TaskHandle(FwCurTask->Param);
                    }
                    
                    FwCurTask = NULL;
                }
                
                //! 4. 处理任务就绪标志
                if (FwList_IsEmpty(&FwActiveTaskTable[prio]))
                {
                    goto __CLEAR_TASK_READY_FLAG;
                }
                
                break;
                
                //! 5. 清除任务就绪标志
__CLEAR_TASK_READY_FLAG:
                _mem_bit_clr(FwTaskReadyTable, 8, prio);
                
                break;
            }
        }

		//! 空闲任务处理
		FwTask_Idle_Handle();
    }
}

/**
 *******************************************************************************
 * @brief       硬件组件初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由框架调用
 *******************************************************************************
 */
#ifdef ENABLE_FRAMEWORK_COMPONENT_INIT
/*
 * Components Initialization will initialize some driver and components as following
 * order:
 * rti_start                --> 0
 * FW_COMPONENT_EXPORT      --> 1
 * rti_fw_component_end     --> 1.end
 *
 * DEVICE_EXPORT            --> 2
 * COMPONENT_EXPORT         --> 3
 * FS_EXPORT                --> 4
 * ENV_EXPORT               --> 5
 * APP_EXPORT               --> 6
 *
 * rti_end                  --> 6.end
 *
 * These automatically initializaiton, the driver or component initial function must
 * be defined with:
 * INIT_BOARD_EXPORT(fn);
 * INIT_DEVICE_EXPORT(fn);
 * ...
 * INIT_APP_EXPORT(fn);
 * etc.
 */
static int fw_init_start(void)
{
    return 0;
}
INIT_EXPORT(fw_init_start, "0");

static int fw_component_init_start(void)
{
    return 0;
}
INIT_EXPORT(fw_component_init_start, "0.end");

static int fw_component_init_end(void)
{
    return 0;
}
INIT_EXPORT(fw_component_init_end, "1.end");

static int fw_hal_init_end(void)
{
    return 0;
}
INIT_EXPORT(fw_hal_init_end, "2.end");

static int fw_board_init_end(void)
{
    return 0;
}
INIT_EXPORT(fw_board_init_end, "3.end");

static int fw_app_init_end(void)
{
    return 0;
}
INIT_EXPORT(fw_app_init_end, "4.end");

static int fw_init_end(void)
{
    return 0;
}
INIT_EXPORT(fw_init_end, "6.end");

int Fw_Component_Init(void)
{
    const init_fn_t *fn;

    for (fn = &f_fw_component_init_start; fn<&f_fw_component_init_end; fn++)
    {
        (*fn)();
    }
    
    return 0;
}

int Fw_HAL_Init(void)
{
    const init_fn_t *fn;

    for (fn = &f_fw_component_init_end; fn<&f_fw_hal_init_end; fn++)
    {
        (*fn)();
    }
    
    return 0;
}

int Fw_Board_Init(void)
{
    const init_fn_t *fn;

    for (fn = &f_fw_hal_init_end; fn<&f_fw_board_init_end; fn++)
    {
        (*fn)();
    }
    
    return 0;
}

int Fw_App_Init(void)
{
    const init_fn_t *fn;

    for (fn = &f_fw_board_init_end; fn<&f_fw_app_init_end; fn++)
    {
        (*fn)();
    }
    
    return 0;
}
#else

__WEAK
int Fw_HAL_Init(void)
{
	return 0;
}

__WEAK
int Fw_Component_Init(void)
{
	FwTimer_Component_Init();

#ifdef ENABLE_FRAMEWORK_DEBUG
	Fwdbg_Component_Init();
#endif

	return 0;
}

#endif

/** @}*/     /** framework core interface */

/**********************************END OF FILE*********************************/
