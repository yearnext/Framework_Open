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
 * @file       fw_nano.c                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      framework core nano version interface source files              *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20170110    创建文件fw_event.c         		                           *
 * 2.20180918    修改文件架构，更名为fw_nano.c                                 *
 * 2.20180920    修改任务调度方式，将纯事件驱动调度修改为基于任务优先级的      *
 *               事件驱动调度方式                                              *
 *******************************************************************************
 */

/**
 * @defgroup framework nano version interface
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"
#include "fw_sm.h"
#include <string.h>

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        任务数量定义
 *******************************************************************************
 */
#define FRAMEWORK_TASK_MAX                                  (_dimof(FwTaskList))
#define FRAMEWORK_TASK_INIT_MAX                         (_dimof(FwTaskInitList))

/**
 *******************************************************************************
 * @brief        定时器数量定义
 *******************************************************************************
 */
#define FRAMEWORK_TIMER_MAX                                    (_dimof(FwTimer))

/**
 *******************************************************************************
 * @brief        消息队列数量定义
 *******************************************************************************
 */
#define FRAMEWORK_MSG_QUEUE_MAX     (FRAMEWORK_TASK_MAX*FRAMEWORK_MQ_SIZE_PARAM)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        消息队列内存定义
 *******************************************************************************
 */
typedef struct
{
    uint8_t Msg;
    uint8_t Next;
}FwQueue_Mem_t;

/**
 *******************************************************************************
 * @brief        消息队列内存管理组件定义
 *******************************************************************************
 */
typedef struct
{
    uint8_t Head;
    uint8_t Tail;
}FwQueue_Mgr_t;

/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        定义位图 16Bit
 *******************************************************************************
 */
__CONST uint8_t FwNanoMap[] = {255, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0};

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        内核句柄
 *******************************************************************************
 */
#ifdef USE_KEIL_C51_COMPILER
__DATA FwCore_t FwCore;
#else
FwCore_t FwCore;
#endif

/**
 *******************************************************************************
 * @brief        定时器句柄
 *******************************************************************************
 */
#ifdef USE_KEIL_C51_COMPILER
__DATA FwTimer_t FwTimer[FW_TIMER_MAX];
#else
FwTimer_t FwTimer[FW_TIMER_MAX];
#endif

/**
 *******************************************************************************
 * @brief        任务处理函数
 *******************************************************************************
 */
//! 任务列表
__CODE FwTaskInit FwTaskInitList[] = {Fw_Task_Init_Array};
__CODE FwTaskHandle FwTaskList[]   = {Fw_Task_Handle_Array};

//! 任务句柄
#ifdef USE_KEIL_C51_COMPILER
FwTask_t __DATA FwTask[FRAMEWORK_TASK_MAX];
#else
FwTask_t FwTask[FRAMEWORK_TASK_MAX];
#endif

/**
 *******************************************************************************
 * @brief        任务事件队列
 *******************************************************************************
 */
//! 队列缓冲区
FwQueue_Mem_t __DATA FwMsgMemory[FRAMEWORK_MSG_QUEUE_MAX];
//! 队列缓冲区管理
FwQueue_Mgr_t __DATA FwMsgMgr[FRAMEWORK_TASK_MAX];
//! 状态
uint8_t __DATA FwMsgMemFlag[(FRAMEWORK_MSG_QUEUE_MAX % 8) ? (FRAMEWORK_MSG_QUEUE_MAX/8 + 1) : (FRAMEWORK_MSG_QUEUE_MAX/8)];

/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       消息队列初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
void Fw_Msg_Init(void)
{
    uint8_t i = 0;
    
    //! 初始化消息缓存
    for (i=0; i<FRAMEWORK_MSG_QUEUE_MAX; i++)
    {
        FwMsgMemory[i].Next = FW_MSG_ADDR_NULL;
        FwMsgMemory[i].Msg  = 0;
    }
    
    //! 初始化任务消息队列
    for (i=0; i<FRAMEWORK_TASK_MAX; i++)
    {
        FwMsgMgr[i].Head = FW_MSG_ADDR_NULL;
        FwMsgMgr[i].Tail = FW_MSG_ADDR_NULL;
    }
    
    //! 初始化消息内存状态
    for (i=0; i<_dimof(FwMsgMemFlag); i++)
    {
        FwMsgMemFlag[i] = 0xFF;
    }
}

/**
 *******************************************************************************
 * @brief       消息队列内存分配函数
 * @param       [in/out]  void
 * @return      [in/out]  FW_MSG_ADDR_NULL    分配失败
 * @return      [in/out]  addr                分配地址
 * @note        由用户调用
 *******************************************************************************
 */
uint8_t Fw_Msg_Alloc(void)
{
    uint8_t isr  = 0;

    uint8_t addr = FW_MSG_ADDR_NULL;
    uint8_t i = 0;
    uint8_t low, high;
    
    Fw_Atom_Begin(isr);
    
    //! 计算内存表空闲内存地址
    do
    {
        if (FwMsgMemFlag[i])
        {
            low  = FwMsgMemFlag[i] & 0x0F;
            high = FwMsgMemFlag[i] >> 4;
            
            if ((addr = FwNanoMap[low]) <= 3)
            {
                //! do nothing!
            }
            else if ((addr = FwNanoMap[high]) <= 3)
            {
                addr += 4;
            }
            else
            {
                continue;
            }

            _clr_bit(FwMsgMemFlag[i], addr);
            
            addr += i * 8;
            
            if (addr < FRAMEWORK_MSG_QUEUE_MAX)
            {
                break;
            }
			else
			{
				addr = FW_MSG_ADDR_NULL;
			}
        }
    }while(++i < _dimof(FwMsgMemFlag));

#ifdef FW_PUT_MSG_ALLOC_INFO
	if (addr >= FRAMEWORK_MSG_QUEUE_MAX)
	{
		Fw_Core_Log("Msg Memory Alloc Addr Is Overflow");
	}
	else
	{
		Fw_Core_Log("Msg Memory Alloc Addr Is %d", (uint8_t)addr);
	}
#endif

    Fw_Atom_End(isr);
    
    return addr;
}

/**
 *******************************************************************************
 * @brief       消息队列内存释放函数
 * @param       [in/out]  id     内存地址
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
#define Fw_Msg_Free(addr)         _set_bit(FwMsgMemFlag[(addr) / 8], (addr) % 8)

/**
  *******************************************************************************
  * @brief       输出消息列表信息
  * @param       [in/out]  void
  * @return      [in/out]  void
  * @note        由用户调用
  *******************************************************************************
  */
#ifdef FW_PUT_MSG_CMPT_INFO
void Fw_Put_Msg_List(void)
{
	for (int i = 0; i < _dimof(FwMsgMgr); i++)
	{
		int head = FwMsgMgr[i].Head;
		int tail = FwMsgMgr[i].Tail;
		int now  = head;
		int len;

		if (head == 0xFF)
		{
			printf("Task %d Msg Head: Empty\r\n", (uint8_t)i);
		}
		else
		{
			printf("Task %d Msg Head: %d\r\n", (uint8_t)i, (uint8_t)head);
		}
		
		if (tail == 0xFF)
		{
			printf("Task %d Msg Tail: Empty\r\n", (uint8_t)i);
		}
		else
		{
			printf("Task %d Msg Tail: %d\r\n", (uint8_t)i, (uint8_t)tail);
		}

		printf("Put Message List:");

		len = 0;

		while (1)
		{
			if (now == 0xFF)
			{
				printf("\r\nEND, Msg List Len：%d\r\n\r\n", (uint8_t)len);

				break;
			}
			else
			{
				printf("Mem[%d]", (uint8_t)now);

				len++;
			}

			now = FwMsgMemory[now].Next;

			if (now != 0xFF)
			{
				printf(" -> ");
			}
		}
	}
}
#endif

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       消息发送函数
 * @param       [in/out]  id        任务ID
 * @param       [in/out]  msg       消息
 * @return      [in/out]  0         发送成功
 * @return      [in/out]  1         发送失败
 * @note        由用户调用
 *******************************************************************************
 */
uint8_t Fw_Msg_Send(uint8_t id, uint8_t msg)
{
    uint8_t isr  = 0;
    uint8_t mem  = Fw_Msg_Alloc();
    uint8_t head = FwMsgMgr[id].Head;
    uint8_t tail = FwMsgMgr[id].Tail;
    
    if (mem >= FRAMEWORK_MSG_QUEUE_MAX || id >= FRAMEWORK_TASK_MAX)
    {
		return 1;
    }

#ifdef FW_PUT_MSG_CMPT_INFO
	Fw_Core_Log("\r\n********************Alloc Message Memory Begin, Dst Task Id:%d, Message:%d********************", (uint8_t)id, (uint8_t)msg);
	Fw_Put_Msg_List();
#endif

    Fw_Atom_Begin(isr);
    
    //! 加入消息队列
    if(head == FW_MSG_ADDR_NULL && tail == FW_MSG_ADDR_NULL)
    {
        FwMsgMgr[id].Head = mem;
        FwMsgMgr[id].Tail = mem;
    }
    else
    {
        FwMsgMemory[tail].Next = mem;
        FwMsgMgr[id].Tail      = mem;
    }
    
    //! 写入消息
    FwMsgMemory[mem].Msg  = msg;
    FwMsgMemory[mem].Next = FW_MSG_ADDR_NULL;
    
#ifdef FW_PUT_MESSAGE_CHECK_INFO
	if (msg == 0)
	{
		Fw_Core_Error("Task %d Send Message Error", (uint8_t)id);
	}
#endif

    Fw_Evt_Set(FwTask[id].Event, FRAMEWORK_MSG_EVENT);
    
#ifdef FW_PUT_MSG_CMPT_INFO
	Fw_Core_Log("\r\nAlloc Message Memory End");
	Fw_Put_Msg_List();
	printf("********************************************************************************\r\n\r\n\r\n");
#endif

    Fw_Atom_End(isr);
    
    return 0;
}

/**
 *******************************************************************************
 * @brief       消息接收函数
 * @param       [in/out]  id         任务ID
 * @return      [in/out]  0          消息队列中无消息
 * @return      [in/out]  else       消息队列中有消息
 * @note        由用户调用
 *******************************************************************************
 */
uint8_t Fw_Msg_Recv(uint8_t id)
{
    uint8_t isr  = 0;
    uint8_t mem  = FwMsgMgr[id].Head;
    uint8_t head = FwMsgMgr[id].Head;
    uint8_t msg;

    if(id >= FRAMEWORK_TASK_MAX || head == FW_MSG_ADDR_NULL || mem >= FRAMEWORK_MSG_QUEUE_MAX)
    {
#ifdef FW_PUT_MSG_FREE_INFO
		Fw_Core_Error("Read Task：%d Message Error", (uint8_t)id);
#endif
        return 0;
    }

    Fw_Atom_Begin(isr);

#ifdef FW_PUT_MSG_CMPT_INFO
	Fw_Core_Log("\r\n********************Free Message Memory Begin********************");
	Fw_Put_Msg_List();
#endif

	//! 读取消息
	msg = FwMsgMemory[mem].Msg;

#ifdef FW_PUT_MESSAGE_CHECK_INFO
	if (msg == 0)
	{
		Fw_Core_Error("Task %d Recv Message Error", (uint8_t)id);
	}
#endif

    //! 设置句柄状态
    FwMsgMgr[id].Head = FwMsgMemory[head].Next;

    if (FwMsgMgr[id].Head == FW_MSG_ADDR_NULL)
    {
        FwMsgMgr[id].Tail = FW_MSG_ADDR_NULL;
        
        Fw_Evt_Clr(FwTask[id].Event, FRAMEWORK_MSG_EVENT);
    }

    FwMsgMemory[mem].Next = FW_MSG_ADDR_NULL;

    Fw_Msg_Free(mem);

#ifdef FW_PUT_MSG_CMPT_INFO
	Fw_Core_Log("\r\nFree Message Memory End, Src Task Id:%d, Message:%d", (uint8_t)id, (uint8_t)msg);
	Fw_Put_Msg_List();
	printf("********************************************************************************\r\n\r\n\r\n");
#endif

    Fw_Atom_End(isr);
    
    return msg;
}

/**
 *******************************************************************************
 * @brief       任务初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由内核调用
 *******************************************************************************
 */
void Fw_Task_Init(void)
{
    for (FwCore.CurTask=0; FwCore.CurTask<FRAMEWORK_TASK_MAX; FwCore.CurTask++)
    {
        FwTaskInitList[FwCore.CurTask](FwCore.CurTask);

#ifdef ENABLE_FRAMEWORK_NANO_EXPAND
        FwTask[FwCore.CurTask].State = FW_TASK_READY;
#endif
    }
    
    FwCore.CurTask = 0;
}

#ifdef ENABLE_FRAMEWORK_NANO_EXPAND
/**
 *******************************************************************************
 * @brief       任务就绪
 * @param       [in/out]  id     任务ID
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_Task_Ready(uint8_t id)
{
    FwTask[id].State = FW_TASK_READY;
}

/**
 *******************************************************************************
 * @brief       任务休眠
 * @param       [in/out]  id     任务ID
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_Task_Sleep(uint8_t id)
{
    FwTask[id].State = FW_TASK_SLEEP;
}

/**
 *******************************************************************************
 * @brief       任务休眠
 * @param       [in/out]  id     任务ID
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_Task_Yeild(uint8_t id)
{
    FwTask[id].State = FW_TASK_YEILD;
}

/**
 *******************************************************************************
 * @brief       任务状态
 * @param       [in/out]  id       任务ID
 * @return      [in/out]  state    任务状态
 * @note        None
 *******************************************************************************
 */
__INLINE
uint8_t Fw_Task_State(uint8_t id)
{
    return FwTask[id].State;
}
#endif

/**
 *******************************************************************************
 * @brief       计算Task数量
 * @param       [in/out]  void
 * @return      [in/out]  num    Task数量
 * @note        None
 *******************************************************************************
 */
uint16_t Fw_Task_Num(void)
{
	return FRAMEWORK_TASK_MAX;
}

/**
 *******************************************************************************
 * @brief       初始化定时器
 * @param       [in/out]  id       定时器ID
 * @param       [in/out]  callback 定时器回调
 * @param       [in/out]  param    回调参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_TaskTimer_Init(uint8_t id, void *callback, void *param)
{
    FwTimer_t *timer = &FwTask[id].Timer;
    
    timer->Tick = 0;

#ifdef ENABLE_FRAMEWORK_NANO_EXPAND
    timer->Reload = 0;

    timer->Func  = callback;
    timer->Param = param;
#else
    _unused(callback);
    _unused(param);
#endif
}

/**
 *******************************************************************************
 * @brief       启动定时器
 * @param       [in/out]  id       定时器ID
 * @param       [in/out]  tick     定时器时间
 * @param       [in/out]  flag     定时器参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_TaskTimer_Start(uint8_t id, FwTick_t tick, uint16_t flag)
{
    FwTask[id].Timer.Tick = tick;

#ifdef ENABLE_FRAMEWORK_NANO_EXPAND
    if (flag)
    {
        FwTask[id].Timer.Reload = tick;
    }
    else
    {
        FwTask[id].Timer.Reload = 0;
    }
#else
    _unused(flag);
#endif
}

/**
 *******************************************************************************
 * @brief       计算Timer数量
 * @param       [in/out]  void
 * @return      [in/out]  num    Timer数量
 * @note        None
 *******************************************************************************
 */
uint16_t Fw_TaskTimer_Num(void)
{
	return FRAMEWORK_TASK_MAX;
}

/**
 *******************************************************************************
 * @brief       计算Tick时间
 * @param       [in/out]  uint16_t    上一次TICK
 * @return      [in/out]  uint16_t    PAST TICK
 * @note        None
 *******************************************************************************
 */
FwTick_t Fw_Tick_PastWithUpdate(FwTick_t *last)
{
    uint8_t isr = 0;
    FwTick_t past;
    
    Fw_Atom_Begin(isr);
    
    past = Fw_Tick_Past(*last);

    *last = FwCore.Tick;
    
    Fw_Atom_End(isr);
    
    return past;
}

/**
 *******************************************************************************
 * @brief       内核心跳处理函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
void Fw_Tick_Handle(void)
{
	static FwTick_t tick = 0;
	FwTick_t past = Fw_Tick_Past(tick);
    uint8_t i;
    FwTimer_t *timer;
    
    for (i=0; i<FRAMEWORK_TASK_MAX; i++)
    {
        timer = &FwTask[i].Timer;
        
        if (timer->Tick)
        {
            if (past >= timer->Tick)
            {
#ifdef ENABLE_FRAMEWORK_NANO_EXPAND
                if (!IS_PTR_NULL(timer->Callback))
                {
                    timer->Callback(timer->Param);
                }
                else
                {
                    FwTask_Set_Evt(i, FRAMEWORK_TICK_EVENT);
                }

                timer->Tick = timer->Reload;
#else
                FwTask_Set_Evt(i, FRAMEWORK_TICK_EVENT);
                timer->Tick = 0;
#endif

#ifdef FW_PUT_TICK_HANDLE_INFO
				Fw_Core_Log("Task：%d Timer Timeout \r\n", i);
#endif
            }
            else
            {
                timer->Tick -= past;
            }
        }
    }

#ifdef ENABLE_FRAMEWORK_TIMER_COMPONENT
    //! 刷新定时时钟
    past = Fw_Tick_Past(tick);
    
    for (i=0; i<FRAMEWORK_TIMER_MAX; i++)
    {
        timer = &FwTimer[i];
        
        if (timer->Tick)
        {
            if (past >= timer->Tick)
            {
                timer->Tick = timer->Reload;
                
                if (!IS_PTR_NULL(timer->Callback))
                {
                    timer->Callback(timer->Param);
                }

#ifdef ENABLE_FRAMEWORK_SM_COMPONENT 
                else if (timer->SmId)
                {
                    FwSm_Post_Msg(timer->SmId, timer->Sig);
                }
#endif

#ifdef FW_PUT_TICK_HANDLE_INFO
                Fw_Core_Log("Timer:%d Timer Timeout \r\n", i);
#endif
            }
            else
            {
                timer->Tick -= past;
            }
        }
    }
#endif

    tick = Fw_Tick_Get();
}

#ifdef ENABLE_FRAMEWORK_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       初始化定时器
 * @param       [in/out]  id       定时器ID
 * @param       [in/out]  callback 定时器回调
 * @param       [in/out]  param    回调参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Timer_Init(uint8_t id, void *callback, void *param)
{
    FwTimer_t *timer = &FwTimer[id];
    
    timer->Tick = 0;
    timer->Reload = 0;

    timer->Func  = callback;
    timer->Param = param;
}

/**
 *******************************************************************************
 * @brief       设置定时器回调函数
 * @param       [in/out]  id           定时器ID
 * @param       [in/out]  callback     回调函数
 * @param       [in/out]  param        回调参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Timer_SetCallback(uint8_t id, void *callback, void *param)
{
    FwTimer_t *timer = &FwTimer[id];
    
    timer->Tick = 0;
    timer->Reload = 0;

    timer->Func  = callback;
    timer->Param = param;
}

/**
 *******************************************************************************
 * @brief       设置定时器信号发射器
 * @param       [in/out]  id       定时器ID
 * @param       [in/out]  smId     状态机ID
 * @param       [in/out]  sig      触发信号
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Timer_SetSmSig(uint8_t id, uint16_t smId, uint16_t sig)
{
    FwTimer_t *timer = &FwTimer[id];
    
    timer->Func = NULL;
    timer->Param = 0;

    timer->SmId = smId;
    timer->Sig  = sig;
}

/**
 *******************************************************************************
 * @brief       启动定时器
 * @param       [in/out]  id       定时器ID
 * @param       [in/out]  tick     定时器时间
 * @param       [in/out]  flag     定时器参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Timer_Start(uint8_t id, FwTick_t tick, uint16_t flag)
{
    FwTimer_t *timer = &FwTimer[id];

    timer->Tick = tick;

    if (flag)
    {
        timer->Reload = tick;
    }
    else
    {
        timer->Reload = 0;
    }
}

/**
 *******************************************************************************
 * @brief       获取定时器当前时间
 * @param       [in/out]  id       定时器ID
 * @return      [in/out]  tick     定时器当前Tick
 * @note        None
 *******************************************************************************
 */
FwTick_t Fw_Timer_Tick(uint8_t id)
{
    FwTimer_t *timer = &FwTimer[id];

    return timer->Tick;
}

/**
 *******************************************************************************
 * @brief       停止定时器
 * @param       [in/out]  id       定时器ID
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Timer_Stop(uint8_t id)
{
    FwTimer_t *timer = &FwTimer[id];

    timer->Tick = 0;
    timer->Reload = 0;
}

#endif

/**
 *******************************************************************************
 * @brief       框架内核初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
void Fw_Core_Init(void)
{
    //! 初始化系统唤醒变量
    memset((void *)&FwCore,    0, sizeof(FwCore));
    memset((void *)&FwTask[0], 0, sizeof(FwTask));

#ifdef ENABLE_FRAMEWORK_TIMER_COMPONENT
    memset((void *)&FwTimer[0], 0, sizeof(FwTimer));
#endif
    
    //! 系统服务初始化
#ifdef ENABLE_FRAMEWORK_SERVER
    Fw_Server_Init();
#endif

#ifdef ENABLE_FRAMEWORK_CONSOLE
    Fw_Console_Init();
#endif
    
    //! 关闭全局中断
    Fw_IRQ_Disable();

    //! 消息队列初始化
    Fw_Msg_Init();

    //! 硬件组件初始化
    //! 由用户实现
    Fw_Hardware_Init();
    
    //! 任务组件初始化
    Fw_Task_Init();

    //! 开启全局中断
    Fw_IRQ_Enable();
}

/**
 *******************************************************************************
 * @brief       系统内核调度函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
void Fw_Core_Dispatch(void)
{
#ifdef ENABLE_FRAMEWORK_EXPORT
	uint8_t isr = 0;
	uint16_t task = 0;

	Fw_Atom_Begin(isr);

	//! 时钟任务处理
#ifndef ENABLE_FRAMEWORK_TIMER_REAL
	if (Fw_Evt_Get(FwCore.Event, FRAMEWORK_TICK_EVENT))
	{
		Fw_Tick_Handle();
		Fw_Evt_Clr(FwCore.Event, FRAMEWORK_TICK_EVENT);
	}
#endif

	//! 任务调度
	FwCore.CurTask = 0;

	do
	{
#ifdef ENABLE_FRAMEWORK_NANO_EXPAND
		if (FwTask[FwCore.CurTask].Event && FwTask[FwCore.CurTask].State == FW_TASK_READY)
#else
		if (FwTask[FwCore.CurTask].Event)
#endif
		{
			break;
		}
	} while (++FwCore.CurTask < FRAMEWORK_TASK_MAX);

	task = FwCore.CurTask;

	Fw_Atom_End(isr);

	if (task < FRAMEWORK_TASK_MAX)
	{
		//            Fw_Atom_Begin(isr);
		FwTaskList[task](task, FwTask[task].Event);
		//            Fw_Atom_End(isr);
	}
	else
	{
		Fw_Sleep_Handle();
	}

	Fw_Hardware_Poll();
#endif
}

/**
 *******************************************************************************
 * @brief       系统内核启动函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
void Fw_Core_Startup(void)
{
    uint8_t isr   = 0;
    uint16_t task = 0;
    
    while (1)
    {
        Fw_Atom_Begin(isr);
        
        //! 时钟任务处理
#ifndef ENABLE_FRAMEWORK_TIMER_REAL
        if (Fw_Evt_Get(FwCore.Event, FRAMEWORK_TICK_EVENT))
        {
            Fw_Tick_Handle();
            Fw_Evt_Clr(FwCore.Event, FRAMEWORK_TICK_EVENT);
        }
#endif

        //! 任务调度
        FwCore.CurTask = 0;
        
        do
        {
#ifdef ENABLE_FRAMEWORK_NANO_EXPAND
            if (FwTask[FwCore.CurTask].Event && FwTask[FwCore.CurTask].State == FW_TASK_READY)
#else
            if (FwTask[FwCore.CurTask].Event)
#endif
            {
                break;
            }
        }while(++FwCore.CurTask < FRAMEWORK_TASK_MAX);
        
        task = FwCore.CurTask;
        
        Fw_Atom_End(isr);
        
        if (task < FRAMEWORK_TASK_MAX)
        {
//            Fw_Atom_Begin(isr);
            FwTaskList[task](task, FwTask[task].Event);
//            Fw_Atom_End(isr);
        }
        else
        {
            Fw_Sleep_Handle();
        }
        
        Fw_Hardware_Poll();
    }
}

/** @}*/     /** framework core interface */

/**********************************END OF FILE*********************************/
