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
 * @file       fw_core.h                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework core head files                                       *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/**
 * @defgroup framework core interface
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_CORE_H__
#define __FRAMEWORK_CORE_H__

/* Add c++ compatibility -----------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"
#include "fw_server.h"

#if defined(FRAMEWORK_VERSION_NANO)
#include "fw_nano.h"
#elif defined(FRAMEWORK_VERSION_FULL)
/**
 *******************************************************************************
 * @brief        定义协程相关接口
 *******************************************************************************
 */
#ifdef ENABLE_FRAMEWORK_PROTOTHREAD
//! ProtoThread API
#define Fw_PT_Init(task)                           _st((task)->ThreadState = 0;)
//! ProtoThread API
#define Fw_PT_Begin()                  switch (FwCurTask->ThreadState) {case 0:
//! ProtoThread API
#define Fw_PT_End()                                             default: break;}
//! ProtoThread API
#define Fw_PT_Enter()              FwCurTask->ThreadState = (uint16_t)__LINE__;\
                                                                  case __LINE__:
//! ProtoThread API
#define Fw_PT_Wait(state)                                        Fw_PT_Enter();\
                                                            if(state) {return ;}
//! ProtoThread API
#define Fw_PT_Delay(tick)                                  Fw_Task_Delay(tick);\
                                   FwCurTask->ThreadState = (uint16_t)__LINE__;\
                                                                         break;\
                                                                  case __LINE__:
//! ProtoThread API
#define Fw_PT_Exit()                                             Fw_PT_Enter();\
                                                                       return ;
#else
#define Fw_PT_Init(task)
#define Fw_PT_Begin()
#define Fw_PT_End()
#define Fw_PT_Enter()
#define Fw_PT_Wait(state)
#define Fw_PT_Exit()                                  
#define Fw_PT_Delay(tick)
#endif

//! 任务等待函数
#define Fw_Task_Wait(s)                            _st(if ((s) == 0){return 0;})

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      定义错误消息
 *******************************************************************************
 */
typedef enum
{
    FW_ERR_NONE = 0,
    FW_ERR_FAIL,
    FW_ERR_NOT_READY,
    FW_ERR_WAIT,
    FW_ERR_NOT_SUPPORT,
    FW_ERR_UNINIT,
    FW_ERR_LOCKED,
    FW_ERR_INVAILD_PTR,
    FW_ERR_INVAILD_PARAM,
    FW_ERR_IO,
    FW_ERR_BUG,
    FW_ERR_UNKNOW,
    FW_ERR_OVERFLOW,
    FW_ERR_TIMEOUT,
    FW_ERR_EMPTY,
}FwErr_t;

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

//! 用户任务配置选项
#define FW_TASK_EN_PROTOTHREAD                                              0x01
#define FW_TASK_EN_TIM                                                      0x02

//! 任务创建功能
#if USE_FRAMEWORK_VERSION == FRAMEWORK_NANO_VERSION
#define FW_TASK_CREATE(name) 
#elif USE_FRAMEWORK_VERSION == FRAMEWORK_GENERAL_VERSION
#define FW_TASK_CREATE(name) FwTask_t name;
#endif

//! 定义任务最低优先级
#define FRAMEWORK_MINIMUM_PRIORITY               (FRAMEWORK_TASK_PRIORITY_MAX-1)

//! 定义任务最高优先级
#define FRAMEWORK_HIGHEST_PRIORITY                                           (0)

/**
 *******************************************************************************
 * @brief        定时器组件
 *******************************************************************************
 */
//! 定时器运行参数       位偏移地址
//! = 1: 周期运行
//! = 0: 单次运行
#define FW_TIM_EN_PERIOD                                                  _bv(0)

//! 定时器工作状态
#define FW_TIM_SLEEP                                                         (0)
#define FW_TIM_DOING                                                         (1)
#define FW_TIM_COMPLETE                                                      (2)

#define FW_TICK_MAX                                                 (0xFFFFFFFF)

//! 定时器创建功能
#define FW_TIM_CREATE(name) FwTimer_t name;

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        timer block
 *******************************************************************************
 */
typedef void (*FwTimerCallback)(void *param);

typedef struct
{
    //! 回调函数
    FwTimerCallback Callback;
    void            *Param;
    
    //! 定时器计数值
    uint32_t    Timeout;
    uint32_t    Tick;
    
    FwList_t  List;
    
    char        *Name;
    
    //! 定时器状态属性
    uint16_t     Flag;
    uint16_t     State;
}FwTimer_t;

/**
 *******************************************************************************
 * @brief        Framework Core Data Structure
 *******************************************************************************
 */
//! 框架任务组件
typedef void (*FwTaskCallback)(void *Param);
typedef struct __FW_TASK
{
    //! 任务回调
    union
    {
        FwTaskCallback  TaskHandle;
        void            *Handle;
    };

    void *Param;

    //! 任务列表
    FwList_t List;

	//! 轮询定时器
	FwTimer_t Timer;
    
	//! 任务名称
    char *Name;
    
    //! 轮询时基
    uint32_t Tick;
    
    //! 任务属性
    uint16_t Flag;

    //! 协程状态
#ifdef ENABLE_FRAMEWORK_PROTOTHREAD
    uint16_t ThreadState;
#endif

    //! 任务状态
    uint8_t State;
    
    //! 任务优先级
    uint8_t Priority;
}FwTask_t;

//! 框架消息队列组件
//! 消息类型
typedef struct
{
    uint32_t Event;
    
    union
    {
        void     *Param;
        size_t   Expand;
    };
}FwMsg_t;

//! 消息队列
//! 消息队列只能由单个任务做出响应
typedef struct
{
    FwBuf_t Buffer;
    
    FwTask_t *Task;
}FwMQ_t;

//! 框架事件组件
//! 事件类型
//! 事件可以由多个任务做出响应
typedef struct
{ 
    uint32_t   Event;
    
    FwList_t List;
}FwEvt_t;

//! 定义定时器句柄
typedef struct
{
	//! 定时器队列
	FwList_t List;

	//! 定义系统心跳
	volatile uint32_t Tick;
}FwTimerHandle_t;

//! 内核句柄
typedef struct
{
	//! 当前活动任务
	FwTask_t *CurTask;

	//! 空闲任务钩子
	void(*IdleHook)(void);

	//! 任务活动列表
	FwList_t ActiveTable[FRAMEWORK_TASK_PRIORITY_MAX];

	//! 任务就绪表
	uint8_t ReadyTable[(FRAMEWORK_TASK_PRIORITY_MAX % 8) ? (FRAMEWORK_TASK_PRIORITY_MAX / 8 + 1) : (FRAMEWORK_TASK_PRIORITY_MAX / 8)];

	//! 框架事件
	volatile uint16_t Event;

	//! 中断锁
	volatile uint16_t IsrLock;
}FwCore_t;

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        定义内核组件句柄
 *******************************************************************************
 */
extern FwCore_t FwCore;

//! 用于兼容老代码
#define FwCurTask                                               (FwCore.CurTask)
#define FwIdleHook                                             (FwCore.IdleHook)
#define FwIsrLock                                               (FwCore.IsrLock)
#define FwCoreEvent                                               (FwCore.Event)
#define FwTaskReadyTable                                     (FwCore.ReadyTable)
#define FwActiveTaskTable                                   (FwCore.ActiveTable)
#define FwCurTaskHandle(evt)             FwCurTask->TaskHandle(FwCurTask->Param)

/**
 *******************************************************************************
 * @brief        定义定时器组件句柄
 *******************************************************************************
 */
extern FwTimerHandle_t FwTimer;

/* Exported functions --------------------------------------------------------*/
/**
 * @defgroup framework core interface
 * @{
 */
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
 * @brief       框架HAL初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern int Fw_HAL_Init(void);

/**
 *******************************************************************************
 * @brief       框架MCU支持包初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern int Fw_MSP_Init(void);

/**
 *******************************************************************************
 * @brief       框架BSP初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern int Fw_Board_Init(void);

/**
 *******************************************************************************
 * @brief       框架组件初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern int Fw_Component_Init(void);

/**
 *******************************************************************************
 * @brief       框架应用组件初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern int Fw_App_Init(void);

/**
 *******************************************************************************
 * @brief       设置任务空闲钩子
 * @param       [in/out]  *hook       任务空闲钩子函数
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
extern void FwHook_Set_Idle(void *hook);

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

/**
 *******************************************************************************
 * @brief       任务初始化函数
 * @param       [in/out]  *task        任务句柄
 * @param       [in/out]  *name        任务名称
 * @param       [in/out]  handle       任务处理回调
 * @param       [in/out]  *param       任务回调参数
 * @param       [in/out]  priority     任务优先级
 * @param       [in/out]  flag         任务配置
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Task_Init(FwTask_t *task, char *name, void *handle, void *param, uint8_t priority, uint8_t flag);

/**
 *******************************************************************************
 * @brief       任务启动函数
 * @param       [in/out]  *task                     任务句柄
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Task_Start(FwTask_t *task);

/**
 *******************************************************************************
 * @brief       任务延时函数
 * @param       [in/out]  tick    任务延时时间
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Task_Delay(uint32_t tick);

/**
 *******************************************************************************
 * @brief       任务阻塞函数
 * @param       [in/out]  tick       任务延时时间
 * @param       [in/out]  *handle    阻塞超时处理函数
 * @param       [in/out]  *param     阻塞超时处理参数
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Task_Yeild(uint32_t timeout, void *handle, void *param);

/**
 *******************************************************************************
 * @brief       任务休眠函数
 * @param       [in/out]  *task        任务句柄
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Task_Sleep(FwTask_t *task);

/**
 *******************************************************************************
 * @brief       将任务设置为就绪状态
 * @param       [in/out]  *task        任务句柄
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Task_Ready(FwTask_t *task);

/**
 *******************************************************************************
 * @brief       任务唤醒函数
 * @param       [in/out]  *task        任务句柄
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Task_Wakeup(FwTask_t *task);

/**
 *******************************************************************************
 * @brief       任务注销函数
 * @param       [in/out]  *task        任务句柄
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Task_Fini(FwTask_t *task);

/**
 *******************************************************************************
 * @brief       消息初始化函数
 * @param       [in/out]  *queue      消息队列句柄
 * @param       [in/out]  *buf        缓存
 * @param       [in/out]  len         缓存区长度
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_MQ_Init(FwMQ_t *queue, void *buf, uint16_t len);

/**
 *******************************************************************************
 * @brief       消息队列注销函数
 * @param       [in/out]  *queue      消息队列句柄
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_MQ_Fini(FwMQ_t *queue);

/**
 *******************************************************************************
 * @brief       消息发送函数
 * @param       [in/out]  *queue      消息队列句柄
 * @param       [in/out]  *msg        发送消息
 * @param       [in/out]  size        发送消息长度
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern uint16_t Fw_MQ_Send(FwMQ_t *queue, void *msg, uint16_t size);

/**
 *******************************************************************************
 * @brief       消息接收函数
 * @param       [in/out]  *queue      消息队列句柄
 * @param       [in/out]  *msg        消息接收缓冲区
 * @param       [in/out]  size        消息大小
 * @param       [in/out]  tick        阻塞时间
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
//! 由框架API调用
extern FwErr_t Fw_MQ_Recv(FwMQ_t *queue, void *msg, uint16_t size, size_t tick);
extern FwErr_t Fw_MQ_Recv_Mirror(FwMQ_t *queue, void *msg, uint16_t size);

//! 由用户程序调用
#define Fw_MQ_Read(queue, msg, size) _st(if(Fw_MQ_Recv((queue), (void *)(msg), (size), 0) == FW_ERR_EMPTY) {break;})
#define Fw_MQ_Read_Mirror(queue, msg, size) _st(if(Fw_MQ_Recv_Mirror((queue), (void *)(msg), (size)) == FW_ERR_EMPTY) {break;})

/** @}*/     /** framework core interface */

/**
 * @defgroup framework timer interface
 * @{
 */

/**
 *******************************************************************************
 * @brief       定时器组件初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由Fw_Core_Init函数调用，无需用户调用
 *******************************************************************************
 */
extern int FwTimer_Component_Init(void);

/**
 *******************************************************************************
 * @brief       获取定时器列表头
 * @param       [in/out]  void
 * @return      [in/out]  FwList_t*    定时器列表头
 * @note        None
 *******************************************************************************
 */
extern FwList_t *FwTimer_List_Root(void);

/**
 *******************************************************************************
 * @brief       定时器句柄初始化函数
 * @param       [in/out]  timer        定时器句柄
 * @param       [in/out]  name         定时器名称
 * @param       [in/out]  callback     定时器回调
 * @param       [in/out]  param        回调参数
 * @param       [in/out]  tick         定时器定时时间
 * @param       [in/out]  flag         定时器工作标志
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Timer_Init(FwTimer_t *timer, char *name, FwTimerCallback callback, void *param, uint32_t tick, uint8_t flag);

/**
 *******************************************************************************
 * @brief       设置定时器回调函数
 * @param       [in/out]  *timer       定时器句柄
 * @param       [in/out]  callback     定时器回调
 * @param       [in/out]  *param       回调参数
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Timer_Set_Callback(FwTimer_t *timer, FwTimerCallback callback, void *param);

/**
 *******************************************************************************
* @brief        定时器注销函数
 * @param       [in/out]  *timer      定时器句柄
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Timer_Fini(FwTimer_t *timer);

/**
 *******************************************************************************
 * @brief       定时器启动函数
 * @param       [in/out]  timer        定时器句柄
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Timer_Start(FwTimer_t *timer);

/**
 *******************************************************************************
 * @brief       定时器重启函数
 * @param       [in/out]  timer        定时器句柄
 * @param       [in/out]  tick         定时器定时时间
 * @param       [in/out]  flag         定时器工作模式
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
extern void Fw_Timer_Restart(FwTimer_t *timer, uint32_t tick, uint8_t flag);
    
/**
 *******************************************************************************
 * @brief       获取定时器状态
 * @param       [in/out]  timer        定时器句柄
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern uint16_t Fw_Timer_State(FwTimer_t *timer);

/**
 *******************************************************************************
 * @brief       获取定时器完成状态
 * @param       [in/out]  timer        定时器句柄
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern uint8_t Fw_Timer_Done(FwTimer_t *timer);

/**
 *******************************************************************************
 * @brief       定时器停止函数
 * @param       [in/out]  timer        定时器句柄
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Timer_Stop(FwTimer_t *timer);

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
												
/**
 *******************************************************************************
 * @brief       定时器心跳计数函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        用户可调用
 *******************************************************************************
 */
extern void Fw_Tick_Inc(void);

/**
 *******************************************************************************
 * @brief       获取当前心跳值
 * @param       [in/out]  void
 * @return      [in/out]  uint32_t    当前心跳值
 * @note        用户可调用
 *******************************************************************************
 */
extern uint32_t Fw_Tick_Get(void);

/**
 *******************************************************************************
 * @brief       计算距离上个时间点的心跳值
 * @param       [in/out]  lastTick    上个时间点
 * @return      [in/out]  uint32_t    消逝的时间
 * @note        None
 *******************************************************************************
 */
extern uint32_t Fw_Tick_Past(uint32_t lastTick);

/**
 *******************************************************************************
 * @brief       定时器处理函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由Fw_Core_Start调用
 *******************************************************************************
 */
extern void FwTimer_Component_Handle(void);
/** @}*/     /** framework timer interface */

/**
 * @defgroup framework debug interface
 * @{
 */

/**
 *******************************************************************************
 * @brief       调试组件初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由Fw_Core_Start调用
 *******************************************************************************
 */
extern int Fwdbg_Component_Init(void);

#ifdef ENABLE_FRAMEWORK_DEBUG
/**
 *******************************************************************************
 * @brief       运行时间测试起始函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_TimeTest_Begin(void);

/**
 *******************************************************************************
 * @brief       运行时间测试结束函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_TimeTest_End(void);

/**
 *******************************************************************************
 * @brief       定时器测试函数——压力测试
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Timer_Test(void);

/**
 *******************************************************************************
 * @brief       内核输出日志API
 * @param       [in/out]  str     日志信息
 * @param       [in/out]  ...     日志参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Core_Log(char *str, ...);

/**
 *******************************************************************************
 * @brief       内核输出错误API
 * @param       [in/out]  str     日志信息
 * @param       [in/out]  ...     日志参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Core_Error(char *str, ...);

/**
 *******************************************************************************
 * @brief       日志输出API
 * @param       [in/out]  str     日志信息
 * @param       [in/out]  ...     日志参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Log(char *str, ...);

/**
 *******************************************************************************
 * @brief       错误输出API
 * @param       [in/out]  str     日志信息
 * @param       [in/out]  ...     日志参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Error(char *str, ...);

/**
 *******************************************************************************
 * @brief       当前时间转字符串API
 * @param       [in/out]  level    转换等级
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
#define FW_TIME_2_STR_ALL  0
#define FW_TIME_2_STR_DATE 1
#define FW_TIME_2_STR_TIME 0x10

extern char *Fw_Time_To_Str(uint8_t level);

/**
 *******************************************************************************
 * @brief       输出内核信息API
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Put_Info(void);

/**
 *******************************************************************************
 * @brief       输出任务列表API
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Put_Task_List(void);

/**
 *******************************************************************************
 * @brief       输出定时器列表API
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Put_Timer_List(void);

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
 * @brief       定时器测试函数——压力测试
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void Fw_Timer_Test(void);
#else
#define Fw_TimeTest_Begin()
#define Fw_TimeTest_End()
#define Fw_Timer_Test()
#define Fw_Core_Log(s, ...)
#define Fw_Core_Error(s, ...)
#define Fw_Log(s, ...)
#define Fw_Error(s, ...)
#define Fw_Put_Info()
#define Fw_Event_General()
#define Fw_Timer_Test()
#endif

/** @}*/     /** framework debug interface */

#endif

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       定义框架软件版本
 *******************************************************************************
 */
#define FRAMEWORK_SOFT_VERSION                                           "1.3.3"

/**
 *******************************************************************************
 * @brief       定义框架编译日期
 *******************************************************************************
 */
#define FRAMEWORK_BUILD_DATE                                        "2019-03-22"

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
 * @brief      MACRO
 *******************************************************************************
 */
#define Fw_Evt_Set(b, pos)                                      _set_bit(b, pos)
#define Fw_Evt_Clr(b, pos)                                      _clr_bit(b, pos)
#define Fw_Evt_Get(b, pos)                                     _read_bit(b, pos)

#define Fw_Flag_Set(b, flag)                                   _set_reg(b, flag)
#define Fw_Flag_Clr(b, flag)                                   _clr_reg(b, flag)
#define Fw_Flag_Get(b, flag)                                   _get_reg(b, flag)

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework core interface  */

/**********************************END OF FILE*********************************/
