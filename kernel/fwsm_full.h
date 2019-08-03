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
 * @file       fw_sm.h                                                         *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      framework state machine component head file                     *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20170110    创建文件fw_sm.h                                               *
 *******************************************************************************
 */

/**
 * @defgroup framework test component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_STATE_MACHINE_H__
#define __FRAMEWORK_STATE_MACHINE_H__

/* Add c++ compatibility -----------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      定义SM最大嵌套层级
 *******************************************************************************
 */
#define FW_SM_SUPER_LAYER_MAX                                                  5

/**
 *******************************************************************************
 * @brief      定义SM事件队列使能状态
 *******************************************************************************
 */
#define FW_SM_EVENT_QUEUE_ENABLE

/**
 *******************************************************************************
 * @brief      定义SM相关处理功能
 *******************************************************************************
 */
#define Fw_Sm_Tran(me, state)         (((FwSm_t *)me)->Temp = (SmStateHandle)(state), \
                                       FW_SM_RET_TRAN)
#define Fw_Sm_Handle()                (FW_SM_RET_HANDLED)
#define Fw_Sm_Super()                 (FW_SM_RET_SUPER)
#define Fw_Sm_Unhandle()              (FW_SM_RET_UNHANDLED)
#define Fw_Sm_Wait()                  (FW_SM_RET_WAIT)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      定义状态机数据类型
 *******************************************************************************
 */
enum FW_SM_RET
{
    FW_SM_RET_SUPER,
    FW_SM_RET_SUPER_SUB,
    FW_SM_RET_UNHANDLED,

    FW_SM_RET_WAIT,
    
    FW_SM_RET_CALL,
    FW_SM_RET_BACK,
    
    FW_SM_RET_HANDLED,
    FW_SM_RET_IGNORED,

    FW_SM_RET_ENTRY,
    FW_SM_RET_EXIT,

    FW_SM_RET_NULL,

    FW_SM_RET_TRAN,
    FW_SM_RET_TRAN_INIT,
    FW_SM_RET_TRAN_HIST,
};

//! 定义状态机状态
typedef uint8_t FwSmState_t;

struct FW_SM_ROOT;

//! 定义状态机事件
typedef struct FW_SM_EVT
{
    uint32_t Sig;
    
    union
    {
        size_t Expand;
        
        void *Ptr;

#ifdef USE_KEIL_C51_COMPILER
        uint8_t (__CODE *Last)(void *me, struct FW_SM_EVT *evt) reentrant;
#else
        uint8_t (*Last)(void *me, struct FW_SM_EVT *evt);
#endif
    };
}FwSmEvt_t;

//! 定义状态机处理函数
#ifdef USE_KEIL_C51_COMPILER
typedef uint8_t (__CODE *SmStateHandle)(void *me, FwSmEvt_t *evt) reentrant;
#else
typedef uint8_t (*SmStateHandle)(void *me, FwSmEvt_t *evt);
#endif

/**
 *******************************************************************************
 * @brief      HSM 数据结构
 *******************************************************************************
 */
typedef struct FW_SM_ROOT
{
    //! 根节点
    char              *Name;
    struct FW_SM_ROOT *Super;
    
    //! SM List
    FwList_t List;
    
    //! Sub SM List
    FwList_t SubList;
 
    SmStateHandle State;
    SmStateHandle Temp;
    
    FwTimer_t Timer;
}FwSmRoot_t, FwSm_t;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern int FwSm_Component_Init(void);

extern void FwSm_AddRoot(FwSmRoot_t *root, char *name, SmStateHandle init);
extern void FwSm_AddSub(FwSmRoot_t *root, FwSm_t *sm, char *name, SmStateHandle init);

extern uint8_t FwSm_Dispatch(FwSm_t *me, FwSmEvt_t *evt);

extern uint16_t FwSmPost(FwSm_t *me, uint32_t sig, uint32_t param);
extern uint16_t FwSmEmit(FwSm_t *me, uint32_t sig);
extern void *FwSm_State(FwSm_t *me);

extern void FwSm_Timer_Start(FwSm_t *me, uint32_t tick);
extern void FwSm_Timer_Stop(FwSm_t *me);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework state machine component */

/**********************************END OF FILE*********************************/
