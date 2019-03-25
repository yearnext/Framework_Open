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
 * @file       fw_nano.h                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      framework core nano version interface head files                *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20170110    创建文件fw_event.h         		                           *
 * 2.20180918    修改文件架构，更名为fw_nano.h                                 *
 *******************************************************************************
 */

/**
 * @defgroup framework core interface
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_NANO_H__
#define __FRAMEWORK_NANO_H__

/* Add c++ compatibility -----------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"
#include "hal_msp.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        任务组件
 *******************************************************************************
 */
//! 定义任务组件状态
#define FW_TASK_INIT                                                         (0)
#define FW_TASK_READY                                                        (1)
#define FW_TASK_YEILD                                                        (2)
#define FW_TASK_DELAY                                                        (3)
#define FW_TASK_SLEEP                                                        (4)

/**
 *******************************************************************************
 * @brief        任务组件
 *******************************************************************************
 */
//! 定义任务最低优先级
#define FRAMEWORK_MINIMUM_PRIORITY               (FRAMEWORK_TASK_PRIORITY_MAX-1)

//! 定义任务最高优先级
#define FRAMEWORK_HIGHEST_PRIORITY                                           (0)

//! framework array link list null
#define FW_MSG_ADDR_NULL                                                  (0xFF)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        tick block
 *******************************************************************************
 */
#ifdef FRAMEWORK_NANO_EXPAND
typedef uint32_t FwTick_t;
#define FRAMEWORK_TICK_MAX UINT32_MAX
#else
typedef uint16_t FwTick_t;
#define FRAMEWORK_TICK_MAX UINT16_MAX
#endif

/**
 *******************************************************************************
 * @brief        timer block
 *******************************************************************************
 */
typedef struct
{
#ifdef FRAMEWORK_NANO_EXPAND
    union
    {
        void (*Callback)(void *param);
        void *Ptr;
    }Handle;
    
    void *param;
    
    FwTick_t Reload;
#endif
    
    FwTick_t Tick;
}FwTimer_t;

/**
 *******************************************************************************
 * @brief        Framework Core Data Structure
 *******************************************************************************
 */
//! 任务处理
#if defined(USE_KEIL_C51_COMPILER)
typedef uint16_t (__CODE *FwTaskHandle)(uint8_t taskid, uint16_t evt);
typedef FwTaskHandle Fw_Task_t;

typedef void (__CODE *FwTaskInit)(uint8_t taskid);
typedef FwTaskInit Fw_Task_Init_t;
#else
typedef uint16_t(*FwTaskHandle)(uint8_t taskid, uint16_t evt);
typedef FwTaskHandle Fw_Task_t;

typedef void(*FwTaskInit)(uint8_t taskid);
typedef FwTaskInit Fw_Task_Init_t;
#endif

//! 任务句柄
typedef struct
{
    FwTimer_t Timer;
    
#ifdef FRAMEWORK_NANO_EXPAND
    uint16_t State;
#endif
    
    uint16_t Event;
}FwTask_t;

//! 内核句柄
typedef struct
{
    volatile FwTick_t Tick;
    
#ifdef FRAMEWORK_NANO_EXPAND
    volatile uint32_t IsrLock;
#endif
    
    volatile uint16_t Event;
    
    uint16_t CurTask;
}FwHandle_t;

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        任务处理函数
 *******************************************************************************
 */
//! 任务列表
extern __CODE Fw_Task_t      FwTaskList[];
extern __CODE Fw_Task_Init_t FwTaskInitList[];

#ifdef USE_KEIL_C51_COMPILER
extern __DATA FwTask_t FwTask[];
extern __DATA FwHandle_t FwCore;
#else
extern FwTask_t FwTask[];
extern FwHandle_t FwCore;
#endif

/* Exported functions --------------------------------------------------------*/
/**
 * @defgroup framework core interface
 * @{
 */
/**
 *******************************************************************************
 * @brief       禁用全局中断
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
#define Fw_IRQ_Disable()                                     __DISABLE_ALL_ISR()

/**
 *******************************************************************************
 * @brief       开启全局中断函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
#define Fw_IRQ_Enable()                                       __ENABLE_ALL_ISR()

/**
 *******************************************************************************
 * @brief       临界点操作函数
 * @note        用户可调用
 *******************************************************************************
 */
#ifdef FRAMEWORK_NANO_EXPAND
#define Fw_Atom_Begin(x)                    _st((x) = (x); Fw_Enter_Critical();)
#define Fw_Atom_End(x)                       _st((x) = (x); Fw_Exit_Critical();)
#else
#define Fw_Atom_Begin(x)       _st((x) = __GET_ISR_FLAG(); __DISABLE_ALL_ISR();)
#define Fw_Atom_End(x)                                   _st(__SET_ISR_FLAG(x);)
#endif

/**
 *******************************************************************************
 * @brief       进入临界点函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Enter_Critical(void);

/**
 *******************************************************************************
 * @brief       退出临界点函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Exit_Critical(void);

/**
 *******************************************************************************
 * @brief       硬件组件初始化
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户实现
 *******************************************************************************
 */
extern void Fw_Hardware_Init(void);

/**
 *******************************************************************************
 * @brief       硬件轮询函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户实现
 *******************************************************************************
 */
extern void Fw_Hardware_Poll(void);

/**
 *******************************************************************************
 * @brief       睡眠处理函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户实现
 *******************************************************************************
 */
extern void Fw_Sleep_Handle(void);

/**
 *******************************************************************************
 * @brief       设置任务事件
 * @param       [in/out]  id      任务ID
 * @param       [in/out]  evt     任务事件
 * @return      [in/out]  void
 * @note        用户实现
 *******************************************************************************
 */
#define Fw_Task_Evt_Set(id, evt)             Fw_Evt_Set(FwTask[(id)].Event, evt)

/**
 *******************************************************************************
 * @brief       清除任务事件
 * @param       [in/out]  evt     任务事件
 * @note        用户实现
 *******************************************************************************
 */
#define Fw_Task_Evt_Clr(evt)       Fw_Evt_Clr(FwTask[FwCore.CurTask].Event, evt)

/**
 *******************************************************************************
 * @brief       复位任务事件
 * @param       [in/out]  id       任务ID
 * @note        用户实现
 *******************************************************************************
 */
#define Fw_Task_Evt_Rst(id)               _st(FwTask[FwCore.CurTask].Event = 0;)

/**
 *******************************************************************************
 * @brief       获取任务事件
 * @param       [in/out]  evt     任务事件
 * @note        用户实现
 *******************************************************************************
 */
#define Fw_Task_Evt_Get(evt)       Fw_Evt_Get(FwTask[FwCore.CurTask].Event, evt)

/**
 *******************************************************************************
 * @brief       消息发送函数
 * @param       [in/out]  id        任务ID
 * @param       [in/out]  evt       发送事件
 * @return      [in/out]  0         发送成功
 * @return      [in/out]  1         发送失败
 * @note        由用户调用
 *******************************************************************************
 */
extern uint8_t Fw_Msg_Send(uint8_t id, uint8_t evt);

/**
 *******************************************************************************
 * @brief       消息接收函数
 * @param       [in/out]  id         任务ID
 * @return      [in/out]  0          消息队列中无消息
 * @return      [in/out]  else       消息队列中有消息
 * @note        由用户调用
 *******************************************************************************
 */
extern uint8_t Fw_Msg_Recv(uint8_t id);

/**
 *******************************************************************************
 * @brief       事件生成函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        测试用
 *******************************************************************************
 */
extern void Fw_Event_General(void);

/**
 *******************************************************************************
 * @brief       任务消息接收函数
 * @param       [in/out]  id         任务ID
 * @return      [in/out]  0          消息队列中无消息
 * @return      [in/out]  else       消息队列中有消息
 * @note        由用户调用
 *******************************************************************************
 */
#define Fw_Task_Msg_Recv()                           Fw_Msg_Recv(FwCore.CurTask)

/**
 *******************************************************************************
 * @brief       任务延时函数
 * @param       [in/out]  tick    延时时间
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
#ifdef FRAMEWORK_NANO_EXPAND
#define Fw_Task_Delay(tick)     _st(FwTask[FwCore.CurTask].Timer.Reload = 0;   \
                                    FwTask[FwCore.CurTask].Timer.Tick = (tick);)
#else
#define Fw_Task_Delay(tick)     _st(FwTask[FwCore.CurTask].Timer.Tick = (tick);)
#endif

/**
 *******************************************************************************
 * @brief       启动任务定时器
 * @param       [in/out]  tick    定时时间
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
#ifdef FRAMEWORK_NANO_EXPAND
#define Fw_TaskTimer_Start(id, tick)        _st(FwTask[id].Timer.Reload = 0;   \
                                                FwTask[id].Timer.Tick = (tick);)
#else
#define Fw_TaskTimer_Start(id, tick)        _st(FwTask[id].Timer.Tick = (tick);)
#endif

#define Fw_TaskTimer_Stop(id)                  _st(FwTask[id].Timer.Tick = (0);)

 /**
  *******************************************************************************
  * @brief       计算Task数量
  * @param       [in/out]  void
  * @return      [in/out]  num    Task数量
  * @note        None
  *******************************************************************************
  */
extern uint16_t Fw_Task_Num(void);

/**
 *******************************************************************************
 * @brief       计算Timer数量
 * @param       [in/out]  void
 * @return      [in/out]  num    Timer数量
 * @note        None
 *******************************************************************************
 */
extern uint16_t Fw_Timer_Num(void);

#ifdef FRAMEWORK_NANO_EXPAND
/**
 *******************************************************************************
 * @brief       任务就绪
 * @param       [in/out]  id     任务ID
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Task_Ready(uint8_t id);

/**
 *******************************************************************************
 * @brief       任务休眠
 * @param       [in/out]  id     任务ID
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Task_Sleep(uint8_t id);

/**
 *******************************************************************************
 * @brief       任务休眠
 * @param       [in/out]  id     任务ID
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Task_Yeild(uint8_t id);

/**
 *******************************************************************************
 * @brief       任务状态
 * @param       [in/out]  id       任务ID
 * @return      [in/out]  state    任务状态
 * @note        None
 *******************************************************************************
 */
extern uint8_t Fw_Task_State(uint8_t id);
#endif

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
extern void Fw_Timer_Init(uint8_t id, void *callback, void *param);

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
extern void Fw_Timer_Start(uint8_t id, FwTick_t tick, uint16_t flag);

/**
 *******************************************************************************
 * @brief       停止定时器
 * @param       [in/out]  id       定时器ID
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Timer_Stop(uint8_t id);

/**
 *******************************************************************************
 * @brief       获取任务延时状态
 * @param       [in/out]  evt     当前任务事件
 * @return      [in/out]  1       延时结束
 * @return      [in/out]  0       延时中
 * @note        由用户调用
 *******************************************************************************
 */
#define Fw_Delay_Done(evt)                Fw_Evt_Get(evt, FRAMEWORK_DELAY_EVENT)
     
 /**
 *******************************************************************************
 * @brief       清除任务延时状态
 * @param       [in/out]  evt     当前任务事件
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
#define Fw_Delay_Clr(evt)                 Fw_Task_Evt_Clr(FRAMEWORK_DELAY_EVENT)

/**
 *******************************************************************************
 * @brief       获取当前心跳值
 * @note        由用户调用
 *******************************************************************************
 */ 
#define Fw_Tick_Get()                                              (FwCore.Tick)
  
/**
 *******************************************************************************
 * @brief       计算Tick时间
 * @note        None
 *******************************************************************************
 */
#define Fw_Tick_Past(in) (((in) > (FwCore.Tick)) ?                             \
                                  ((FRAMEWORK_TICK_MAX - (in) + FwCore.Tick))  \
                                  : (FwCore.Tick - (in)))
//! 带保存功能
extern FwTick_t Fw_Tick_PastWithUpdate(FwTick_t *last);

/**
 *******************************************************************************
 * @brief       内核心跳处理函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
extern void Fw_Tick_Handle(void);

/**
 *******************************************************************************
 * @brief       内核心跳自增函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
#ifdef ENABLE_FRAMEWORK_TIMER_REAL
#define Fw_Tick_Inc()                                                          \
                                           _st(FwCore.Tick++; Fw_Tick_Handle();)
#else
#define Fw_Tick_Inc()                                                          \
             _st(FwCore.Tick++; Fw_Evt_Set(FwCore.Event, FRAMEWORK_TICK_EVENT);)
#endif

/**
 *******************************************************************************
 * @brief       基础定时器函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
#define Fw_GenTimer_Start(tim, tick)            _st((tim) = (tick);)
#define Fw_GenTimer_Stop(tim)                   _st((tim) = 0;)
#define Fw_GenTimer_Done(tim)                   ((tim) == 0)
#define Fw_GenTimer_Handle(tim)                 _st(if((tim) > 0)             \
                                                {                             \
                                                    --(tim);                  \
                                                })
#define Fw_GenTimer_HandleWithMsg(tim, id, evt) _st(if((tim) > 0)             \
                                                {                             \
                                                    if(!--(tim))              \
                                                    {                         \
                                                        Fw_Msg_Send(id, evt); \
                                                    }                         \
                                                })
                                                
#define Fw_GenTimer_HandleWithBSPMsg(tim, evt) _st(if((tim) > 0)             \
                                               {                             \
                                                   if(!--(tim))              \
                                                   {                         \
                                                       BSP_Msg_Send(evt);    \
                                                   }                         \
                                               })
/**
 *******************************************************************************
 * @brief       框架内核初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Core_Init(void);

/**
 *******************************************************************************
 * @brief       框架运行函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Core_Startup(void);

#ifdef ENABLE_FRAMEWORK_DEBUG
extern void Fw_Log(char *str, ...);
#endif

/**
 *******************************************************************************
 * @brief        定义协程相关接口
 *******************************************************************************
 */
#ifdef ENABLE_FRAMEWORK_PROTOTHREAD
//! ProtoThread API
#define Fw_PT_Init(task)                            static uint16_t ptState = 0;
//! ProtoThread API
#define Fw_PT_Begin()                                 switch (ptState) { case 0:
//! ProtoThread API
#define Fw_PT_End()                                             default: break;}
//! ProtoThread API
#define Fw_PT_Enter()                             ptState = (uint16_t)__LINE__;\
                                                                  case __LINE__:
//! ProtoThread API
#define Fw_PT_Wait(state)                                        Fw_PT_Enter();\
                                                 if(state) {return FW_ERR_WAIT;}
//! ProtoThread API
#define Fw_PT_Delay(tick)                                  Fw_Task_Delay(tick);\
                                                   evt = FRAMEWORK_EMPTY_EVENT;\
                                       Fw_PT_Wait(evt != FRAMEWORK_DELAY_EVENT);
//! ProtoThread API
#define Fw_PT_Exit()                                             Fw_PT_Enter();\
                                                             return FW_ERR_NONE;
#else
#define Fw_PT_Init(task)
#define Fw_PT_Begin()
#define Fw_PT_End()
#define Fw_PT_Enter()
#define Fw_PT_Wait(state)
#define Fw_PT_Exit()                                  
#define Fw_PT_Delay(tick)
#endif

/**
 *******************************************************************************
 * @brief        定义日志相关接口
 *******************************************************************************
 */
extern void Fw_Core_Log(char *str, ...);
extern void Fw_Core_Error(char *str, ...);
extern void Fw_Log(char *str, ...);
extern void Fw_Error(char *str, ...);

/**
 *******************************************************************************
 * @brief        定义状态机相关接口
 *******************************************************************************
 */
enum FSM_RET_STATE
{
	SM_RET_HANDLE = 0,
	SM_RET_SUPER,
	SM_RET_IGNORED,

	SM_RET_DOING,
	SM_RET_TRAN,
	SM_RET_COMPLETE,
	SM_RET_SLEEP,
};

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework core interface  */

/**********************************END OF FILE*********************************/
