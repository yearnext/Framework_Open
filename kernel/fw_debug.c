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
 * @file       fw_debug.c                                                      *
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
 * @defgroup framework debug component interface
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"
#include <string.h>
#include <stdio.h>

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef ENABLE_FRAMEWORK_DEBUG
static char *__version[] = { "Disable", "Nano", "Full" };
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       控制台初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        由Fw_Core_Start调用
 *******************************************************************************
 */
void Fw_Console_Init(void)
{
#ifdef __EVENT_RECORDER_H
    EventRecorderInitialize(EventRecordAll, 1);
    EventRecorderStart();
#endif

	//! 输出系统信息
	Fw_Put_Info();
}

#ifdef ENABLE_FRAMEWORK_DEBUG
/**
 *******************************************************************************
 * @brief       控制台输出函数
 * @param       [in/out]  str     字符串
 * @param       [in/out]  ...     拓展参数 
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Console_Put(char *str, ...)
{
    va_list ap;
    
    va_start(ap, str);
    vprintf(str, ap);
    va_end(ap);
}

/**
 *******************************************************************************
 * @brief       输出内核调试信息
 * @param       [in/out]  str     输入字符串
 * @param       [in/out]  ...     输入参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Core_Log(char *str, ...)
{
    char buf[128];
    
    va_list ap;
    
    va_start(ap, str);
    vsprintf(buf, str, ap);
    va_end(ap);
    
    Fw_Console_Put("[%d][CORE][LOG]%s\r\n", Fw_Tick_Get(), (char *)buf);
}

/**
 *******************************************************************************
 * @brief       输出内核调试信息
 * @param       [in/out]  str     输入字符串
 * @param       [in/out]  ...     输入参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Core_Error(char *str, ...)
{
    char buf[128];
    
    va_list ap;
    
    va_start(ap, str);
    vsprintf(buf, str, ap);
    va_end(ap);
    
    Fw_Console_Put("[%d][CORE][ERROR]%s\r\n", Fw_Tick_Get(), (char *)buf);
}

/**
 *******************************************************************************
 * @brief       输出内核调试信息
 * @param       [in/out]  str     输入字符串
 * @param       [in/out]  ...     输入参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Log(char *str, ...)
{
    char buf[128];
    
    va_list ap;
    
    va_start(ap, str);
    vsprintf(buf, str, ap);
    va_end(ap);
    
    Fw_Console_Put("[%d][LOG]%s\r\n", Fw_Tick_Get(), (char *)buf);
}

/**
 *******************************************************************************
 * @brief       输出内核调试信息
 * @param       [in/out]  str     输入字符串
 * @param       [in/out]  ...     输入参数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Error(char *str, ...)
{
    char buf[128];
    
    va_list ap;
    
    va_start(ap, str);
    vsprintf(buf, str, ap);
    va_end(ap);
    
    Fw_Console_Put("[%d][ERROR]%s\r\n", Fw_Tick_Get(), (char *)buf);
}
#endif

/**
 *******************************************************************************
 * @brief       获取MCU平台描述符
 * @param       [in/out]  void
 * @return      [in/out]  char*    描述字符串
 * @note        None
 *******************************************************************************
 */
char *Fw_Paltform_String(void)
{
    char *str;

    switch (BOARD_PALTFORM)
    {
        case USE_PALTFORM_SIMULATION:
            str = (char *)("Simulation");
            break;
        case USE_PALTFORM_N76E003:
            str = (char *)("N76E003");
            break;
        case USE_PALTFORM_NUC029LAN:
            str = (char *)("NUC029");
            break;
        case USE_PALTFORM_NANO103:
            str = (char *)("Nano103");
            break;
        case USE_PALTFORM_STM8L05x:
            str = (char *)("STM8L05x");
            break;
        case USE_PALTFORM_STM32L05x:
            str = (char *)("STM32L05x");
            break;
        case USE_PALTFORM_STM32F1xx:
            str = (char *)("STM32F1xx");
            break;
        case USE_PALTFORM_STM32L4xx:
            str = (char *)("STM32L4xx");
            break;
        case USE_PALTFORM_HC32L13x:
            str = (char *)("HC32L13x");
            break;
        case USE_PALTFORM_MIMXRT1052:
            str = (char *)("MIMXRT1052");
            break;        
        default:
            str = (char *)("Not Support Paltform");
            break;
    }
    
    return str;
}

#ifdef ENABLE_FRAMEWORK_DEBUG
/**
 *******************************************************************************
 * @brief       运行时间测试起始函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_TimeTest_Begin(void)
{
#ifdef __EVENT_RECORDER_H
    EventStartA(0);
#endif
}

/**
 *******************************************************************************
 * @brief       运行时间测试结束函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_TimeTest_End(void)
{
#ifdef __EVENT_RECORDER_H
    EventStopA(0);
#endif
}

/**
 *******************************************************************************
 * @brief       当前时间转字符串API
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
char *Fw_Time_To_Str(uint8_t level)
{
#ifdef SIMULATION_DEBUG
	SYSTEMTIME time;
	GetLocalTime(&time);

	static char localTime[64];
	int len;

	switch (level)
	{
		case 0x01:
			len = sprintf(&localTime[0], "%d-%d-%d", time.wYear, time.wMonth, time.wDay);
			break;
		case 0x10:
			len = sprintf(&localTime[0], "%d%d:%d%d:%d%d.%d", time.wHour/10, time.wHour%10, time.wMinute/10, time.wMinute%10, time.wSecond/10, time.wSecond%10, time.wMilliseconds);
			break;
		default:
			len = sprintf(&localTime[0], "%d-%d-%d %d%d:%d%d:%d%d.%d", time.wYear, time.wMonth, time.wDay, time.wHour/10, time.wHour%10, time.wMinute / 10, time.wMinute % 10, time.wSecond/10, time.wSecond%10, time.wMilliseconds);
			break;
	}

	localTime[len] = '\0';
	
	return &localTime[0];
#else
	return "0000-00-00 00:00:00.000";
#endif
}

/**
 *******************************************************************************
 * @brief       输出系统信息API
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Put_Info(void)
{
	Fw_Console_Put("\n* Framework(%s Version)\r\n", __version[USE_FRAMEWORK_VERSION]);
	Fw_Console_Put("* Author: Accumulate Team\r\n");
	Fw_Console_Put("* Version: %s\r\n", FRAMEWORK_SOFT_VERSION);
	Fw_Console_Put("* Build Time: %s\r\n", FRAMEWORK_BUILD_DATE);
	Fw_Console_Put("* Paltform: %s\r\n", Fw_Paltform_String());
	Fw_Console_Put("* Start Time: %s\r\n", Fw_Time_To_Str(FW_TIME_2_STR_ALL));
}

#ifdef FRAMEWORK_VERSION_FULL
/**
 *******************************************************************************
 * @brief       输出任务列表API
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Put_Task_List(void)
{
	int i;
	FwTask_t *task;
	FwList_t *p;
	
	for (i = 0; i < _dimof(FwCore.ActiveTable); i++)
	{
		p = FwCore.ActiveTable[i].Next;
		Fw_Console_Put("FwCore Task List(Priority %d): \r\n", i);	

		if (p == &FwCore.ActiveTable[i])
		{
			Fw_Console_Put("FwCore Task List(Priority %d) Is Empty \r\n\r\n", i);

			continue ;
		}

		Fw_Console_Put("[Head] -> ");

		for (; p != &FwCore.ActiveTable[i]; p = p->Next)
		{
			task = FwListEntry(p, FwTask_t, List);

			Fw_Console_Put("%s -> ", task->Name);
		}

		Fw_Console_Put("[End] \r\n\r\n");
	}
}

/**
 *******************************************************************************
 * @brief       输出定时器列表API
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Put_Timer_List(void)
{
	FwTimer_t *timer;
	FwList_t *p = FwTimer.List.Next;

	Fw_Console_Put("[%d]Framework Put Timer List: \r\n", Fw_Tick_Get());

	if (p == &FwTimer.List)
	{
		Fw_Console_Put("Framework Timer List Is Empty \r\n");

		return;
	}

	Fw_Console_Put("[Head] -> ");

	for (; p != &FwTimer.List; p = p->Next)
	{
		timer = FwListEntry(p, FwTimer_t, List);

		Fw_Console_Put("%s(%d Ticks) -> ", timer->Name, timer->Tick);
	}

	Fw_Console_Put("[End] \r\n\r\n");
}
#endif

/**
 *******************************************************************************
 * @brief       事件生成函数
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        测试用
 *******************************************************************************
 */
void Fw_Event_General(void)
{
#ifdef FRAMEWORK_VERSION_NANO
	uint8_t flag = 0;

	uint8_t id = rand() % Fw_Task_Num();
	uint8_t evt = rand() % FRAMEWORK_EVENT_MAX;

	evt = (evt) ? (evt) : (evt + 1);

	if (flag)
	{
#ifdef PUT_GENERAL_EVENT_INFO
		Fw_Core_Log("General Task：%d, General Event：%d \r\n", (uint8_t)id, (uint8_t)evt);
#endif
		Fw_Msg_Send(id, evt);
	}
#endif
}

/**
 *******************************************************************************
 * @brief       定时器测试函数——压力测试
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Timer_Test(void)
{
#ifdef ENABLE_FRAMEWORK_TIMER_DEBUG
    //! 定时器句柄
    //! 压力测试用
    static Fw_Timer_t DemoTimer[20];

    for (uint8_t i=0;  i<_dimof(DemoTimer); i++)
    {
        Fw_Timer_Init(&DemoTimer[i],  "Test", NULL, NULL);
        Fw_Timer_Startup(&DemoTimer[i], (i*10)+i, FW_TIM_EN_PERIOD);
    }
#endif
}
#endif

/** @}*/     /** framework debug component interface */

/**********************************END OF FILE*********************************/
