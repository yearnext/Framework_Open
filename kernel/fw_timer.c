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
 * @file       fw_timer.c                                                      *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2016-07-09                                                      *
 * @brief      timer component source files                                    *
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
* @defgroup framework timer component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"
#include <string.h>

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        定义定时器句柄
 *******************************************************************************
 */
FwTimerHandle_t FwTimer;

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       定时器组件初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由Fw_Core_Init函数调用，无需用户调用
 *******************************************************************************
 */
int FwTimer_Component_Init(void)
{ 
    memset((void *)&FwTimer, 0, sizeof(FwTimer));
    
    FwListInit((FwList_t *)&FwTimer.List);

    return 0;
}
INIT_COMPONENT_EXPORT(FwTimer_Component_Init);

/**
 *******************************************************************************
 * @brief       获取定时器列表头
 * @param       [in/out]  void
 * @return      [in/out]  FwList_t*    定时器列表头
 * @note        None
 *******************************************************************************
 */
FwList_t *FwTimer_List_Root(void)
{
	return FwTimer.List.Next;
}

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
__INLINE
void Fw_Timer_Init(FwTimer_t *timer, char *name, FwTimerCallback callback, void *param, uint32_t tick, uint8_t flag)
{
    FwListInit(&timer->List);

    timer->Callback = callback;
    timer->Param    = param;
	timer->Name     = name;

    if (Fw_Flag_Get(flag, FW_TIM_EN_PERIOD))
    {
        Fw_Flag_Set(timer->Flag, FW_TIM_EN_PERIOD);
    }
    else
    {
        Fw_Flag_Clr(timer->Flag, FW_TIM_EN_PERIOD);
    }

    timer->Timeout = tick;
    timer->State   = FW_TIM_SLEEP;
}

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
__INLINE
void Fw_Timer_Set_Callback(FwTimer_t *timer, FwTimerCallback callback, void *param)
{
    timer->Callback = callback;
    timer->Param    = param;
}

/**
 *******************************************************************************
 * @brief       定时器注销函数
 * @param       [in/out]  *timer      定时器句柄
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_Timer_Fini(FwTimer_t *timer)
{
    memset(timer, 0, sizeof(FwTimer_t));
}

/**
 *******************************************************************************
 * @brief       定时器启动函数
 * @param       [in/out]  timer        定时器句柄
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
void Fw_Timer_Start(FwTimer_t *timer)
{
    FwList_t *p;
    FwTimer_t *t;
    
    Fw_Enter_Critical();

#ifdef FW_PUT_TIMER_START_INFO
	Fw_Log("[Begin Process]\r\n");
	Fw_Put_Timer_List();
#endif

    //! 删除列表
    FwListRemove(&timer->List);

    //! 更新时钟
    timer->Tick = Fw_Tick_Get() + timer->Timeout;

    //! 插入操作
    for (p = FwTimer.List.Next; p != &FwTimer.List; p = p->Next)
    {
        t = FwListEntry(p, FwTimer_t, List);
        
        if (t->Tick >= timer->Tick)
        {
            break;
        }
    }

    FwListInsertBefore(p, &timer->List);

    timer->State  = FW_TIM_DOING;

#ifdef FW_PUT_TIMER_START_INFO
	Fw_Log("[End Process]\r\n");
	Fw_Put_Timer_List();
#endif

    Fw_Exit_Critical();
}

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
void Fw_Timer_Restart(FwTimer_t *timer, uint32_t tick, uint8_t flag)
{
    Fw_Enter_Critical();
    
    if (Fw_Flag_Get(flag, FW_TIM_EN_PERIOD))
    {
        Fw_Flag_Set(timer->Flag, FW_TIM_EN_PERIOD);
    }
    else
    {
        Fw_Flag_Clr(timer->Flag, FW_TIM_EN_PERIOD);
    }

    timer->Timeout = tick;
    
    Fw_Timer_Start(timer);
    
    Fw_Exit_Critical();
}

/**
 *******************************************************************************
 * @brief       获取定时器状态
 * @param       [in/out]  timer        定时器句柄
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
uint16_t Fw_Timer_State(FwTimer_t *timer)
{
    if (timer->State == FW_TIM_COMPLETE)
    {
        timer->State = FW_TIM_SLEEP;
        
        return FW_TIM_COMPLETE;
    }
    
    return timer->State;
}

/**
 *******************************************************************************
 * @brief       获取定时器完成状态
 * @param       [in/out]  timer        定时器句柄
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
uint8_t Fw_Timer_Done(FwTimer_t *timer)
{
    if (timer->State == FW_TIM_COMPLETE)
    {
        timer->State = FW_TIM_SLEEP;
        
        return 1;
    }
    
    return 0;
}

/**
 *******************************************************************************
 * @brief       定时器停止函数
 * @param       [in/out]  timer        定时器句柄
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
__INLINE
void Fw_Timer_Stop(FwTimer_t *timer)
{
    Fw_Enter_Critical();
    
    timer->Tick    = 0;
    timer->Timeout = 0;
    timer->State = FW_TIM_SLEEP;

    FwListRemove(&timer->List);
    
    Fw_Exit_Critical();
}

/**
 *******************************************************************************
 * @brief       定时器心跳计数函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由用户调用
 *******************************************************************************
 */
void Fw_Tick_Inc(void)
{
    Fw_Enter_Critical();

    FwTimer.Tick ++;
    
#ifdef FW_PUT_TICK_INFO
	Fw_Core_Log("%s", Fw_Time_To_Str(FW_TIME_2_STR_TIME));
#endif

#ifdef ENABLE_FRAMEWORK_TIMER_REAL
    FwTimer_Component_Handle();
#else
    Fw_Evt_Set(FwCoreEvent, FRAMEWORK_TICK_EVENT);
#endif
    
    Fw_Exit_Critical();
}

/**
 *******************************************************************************
 * @brief       获取当前心跳值
 * @param       [in/out]  void
 * @return      [in/out]  uint32_t    当前心跳值
 * @note        由用户调用
 *******************************************************************************
 */
uint32_t Fw_Tick_Get(void)
{
    return FwTimer.Tick;
}

/**
 *******************************************************************************
 * @brief       计算距离上个时间点的心跳值
 * @param       [in/out]  lastTick    上个时间点
 * @return      [in/out]  uint32_t    消逝的时间
 * @note        None
 *******************************************************************************
 */
__INLINE
uint32_t Fw_Tick_Past(uint32_t lastTick)
{
    return (FwTimer.Tick < lastTick) ? (UINT32_MAX - lastTick + FwTimer.Tick) : (FwTimer.Tick - lastTick);
}

/**
 *******************************************************************************
 * @brief       定时器处理函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由Fw_Core_Start调用
 *******************************************************************************
 */
void FwTimer_Component_Handle(void)
{
    uint32_t tick;
    
    FwList_t *p;
    
    FwTimer_t *t;
    
    Fw_Enter_Critical();
    
#ifdef FW_PUT_TIMER_PROCESS_INFO
	Fw_Log("[Begin Timer Process]\r\n");
	Fw_Put_Timer_List();
#endif

    for (p = FwTimer.List.Next; p != &FwTimer.List;)
    {
        t = FwListEntry(p, FwTimer_t, List);
        
        //! 更新当前时钟
        tick = Fw_Tick_Get();
        
        if ((tick - t->Tick) < FW_TICK_MAX / 2)
        {
            //! 切换到下一个节点
            p = p->Next;
            
            //! 移除当前节点
            FwListRemove(&t->List);

            Fw_Exit_Critical();
            
            //! 超时处理
            if (!IS_PTR_NULL(t->Callback))
            {
                t->Callback(t->Param);
            }
            
            Fw_Enter_Critical();
            
            //! 更新标志位
            if (Fw_Flag_Get(t->Flag, FW_TIM_EN_PERIOD))
            {
                t->Tick = Fw_Tick_Get() + t->Timeout;
                
                Fw_Timer_Start(t);
            }
            else
            {
                t->State = FW_TIM_SLEEP;
            }
        }
        else
        {
            break;
        }
    }
    
#ifdef FW_PUT_TIMER_PROCESS_INFO
	Fw_Log("[End Timer Process]\r\n");
	Fw_Put_Timer_List();
#endif

    Fw_Exit_Critical();
}

/** @}*/     /** framework timer component */

/**********************************END OF FILE*********************************/
