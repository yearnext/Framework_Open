/**
 *******************************************************************************
 * @file       stm32f1xx_timer.c                                               *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-01-16                                                      *
 * @brief      stm32f1xx timer driver component                                *
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
 * @defgroup stm32f1xx timer driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_msp.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef ENABLE_MCU_TIM_CALLBACK
Timer_Callback Timer_ISR[8];
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
__STATIC_INLINE
void *Timer_Cmpt_Config(TIM_TypeDef *TIMx, uint32_t irqID, uint32_t unit, uint32_t tick)
{
    LL_TIM_InitTypeDef TIM_InitStruct;
    LL_RCC_ClocksTypeDef clk;
    
    LL_RCC_GetSystemClocksFreq(&clk);

    if (unit == HAL_TIMER_UNIT_US)
    {
        TIM_InitStruct.Prescaler     = clk.SYSCLK_Frequency / 1000000UL - 1;
        TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    }
    else
    {
        TIM_InitStruct.Prescaler     = clk.SYSCLK_Frequency / 4000UL - 1;
        TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV4;
    }

    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload  = tick;
    
    TIM_InitStruct.RepetitionCounter = 0;
    
    LL_TIM_Init(TIMx, &TIM_InitStruct);

    LL_TIM_EnableARRPreload(TIMx);
    
    LL_TIM_SetTriggerOutput(TIMx, LL_TIM_TRGO_RESET);
    
    if (TIMx != TIM6 && TIMx != TIM7)
    {
        LL_TIM_SetClockSource(TIMx, LL_TIM_CLOCKSOURCE_INTERNAL);

        LL_TIM_DisableMasterSlaveMode(TIMx);
    }
    
    LL_TIM_EnableIT_UPDATE(TIMx);
    
    NVIC_SetPriority((IRQn_Type)irqID, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ((IRQn_Type)irqID);
    
    return TIMx;
}

void *MSP_TIM1_Config(uint32_t mode, uint32_t unit, uint32_t tick)
{
    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);

    return Timer_Cmpt_Config(TIM1, TIM1_UP_IRQn, unit, tick);
}

void *MSP_TIM2_Config(uint32_t mode, uint32_t unit, uint32_t tick)
{
    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

    return Timer_Cmpt_Config(TIM2, TIM2_IRQn, unit, tick);
}

void *MSP_TIM3_Config(uint32_t mode, uint32_t unit, uint32_t tick)
{
    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

    return Timer_Cmpt_Config(TIM3, TIM3_IRQn, unit, tick);
}

void *MSP_TIM4_Config(uint32_t mode, uint32_t unit, uint32_t tick)
{
    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);

    return Timer_Cmpt_Config(TIM4, TIM4_IRQn, unit, tick);
}

void *MSP_TIM5_Config(uint32_t mode, uint32_t unit, uint32_t tick)
{
    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);

    return Timer_Cmpt_Config(TIM5, TIM5_IRQn, unit, tick);
}

void *MSP_TIM6_Config(uint32_t mode, uint32_t unit, uint32_t tick)
{
    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);

    return Timer_Cmpt_Config(TIM6, TIM6_IRQn, unit, tick);
}

void *MSP_TIM7_Config(uint32_t mode, uint32_t unit, uint32_t tick)
{
    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);

    return Timer_Cmpt_Config(TIM7, TIM7_IRQn, unit, tick);
}

void *MSP_TIM8_Config(uint32_t mode, uint32_t unit, uint32_t tick)
{
    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);

    return Timer_Cmpt_Config(TIM8, TIM8_UP_IRQn, unit, tick);
}

#ifdef ENABLE_HAL_TIMER_DRIVER
__STATIC_INLINE
uint16_t Timer_Config(HAL_Timer_t *timer, HAL_Timer_Config_t *config)
{
    switch (config->Attribute.Port)
    {
        case 0:
//            MSP_SYSTICK_Init();
            timer->Param = NULL;
            break;
        case 1:
            timer->Param = MSP_TIM1_Config(config->Attribute.Mode, config->Attribute.Unit, config->Attribute.Tick);
            break;
        case 2:
            timer->Param = MSP_TIM2_Config(config->Attribute.Mode, config->Attribute.Unit, config->Attribute.Tick);
            break;
        case 3:
            timer->Param = MSP_TIM3_Config(config->Attribute.Mode, config->Attribute.Unit, config->Attribute.Tick);
            break;
        case 4:
            timer->Param = MSP_TIM4_Config(config->Attribute.Mode, config->Attribute.Unit, config->Attribute.Tick);
            break;
        case 5:
            timer->Param = MSP_TIM5_Config(config->Attribute.Mode, config->Attribute.Unit, config->Attribute.Tick);
            break;
        case 6:
            timer->Param = MSP_TIM6_Config(config->Attribute.Mode, config->Attribute.Unit, config->Attribute.Tick);
            break;
        case 7:
            timer->Param = MSP_TIM7_Config(config->Attribute.Mode, config->Attribute.Unit, config->Attribute.Tick);
            break;
        case 8:
            timer->Param = MSP_TIM8_Config(config->Attribute.Mode, config->Attribute.Unit, config->Attribute.Tick);
            break;
        default:
            return 1;
    }

    return 0;
}

__STATIC_INLINE
void Timer_Start(HAL_Timer_t *timer)
{
    if (IS_PTR_NULL(timer->Param))
    {
        return;
    }
    
    LL_TIM_EnableCounter((TIM_TypeDef *)timer->Param);
}

__STATIC_INLINE
void Timer_Stop(HAL_Timer_t *timer)
{
    if (IS_PTR_NULL(timer->Param))
    {
        return;
    }
    
    LL_TIM_DisableCounter((TIM_TypeDef *)timer->Param);
}

__STATIC_INLINE
uint32_t Timer_Get_Count(HAL_Timer_t *timer)
{
    if (IS_PTR_NULL(timer->Param))
    {
        return 0;
    }
    
    return LL_TIM_GetCounter((TIM_TypeDef *)timer->Param);
}

__STATIC_INLINE
uint32_t Timer_Control(HAL_Timer_t *timer, uint32_t cmd, void *arg)
{
    uint32_t result = 0;
    
    switch (cmd)
    {
        case HAL_SET_CALLBACK_CMD:
        {
#ifdef ENABLE_MCU_TIM_CALLBACK
            Timer_Callback *callback = (Timer_Callback *)arg;
            
            Timer_ISR[timer->Attribute.Port].Callback = callback->Callback;
            Timer_ISR[timer->Attribute.Port].Param    = callback->Param;
#endif
            break;
        }
        default:
            break;
    }
    
    return result;
}
#endif

/* Exported functions --------------------------------------------------------*/
void MSP_Timer_Init(void)
{
#ifdef ENABLE_MSP_TIMER1_DRIVER
    MSP_TIM1_Config(0, MCU_TIM1_TICK_UNIT, MCU_TIM1_TICK);
#endif
    
#ifdef ENABLE_MSP_TIMER2_DRIVER
    MSP_TIM2_Config(0, MCU_TIM2_TICK_UNIT, MCU_TIM2_TICK);
#endif

#ifdef ENABLE_MSP_TIMER3_DRIVER
    MSP_TIM3_Config(0, MCU_TIM3_TICK_UNIT, MCU_TIM3_TICK);
#endif

#ifdef ENABLE_MSP_TIMER4_DRIVER
    MSP_TIM4_Config(0, MCU_TIM4_TICK_UNIT, MCU_TIM4_TICK);
#endif

#ifdef ENABLE_MSP_TIMER5_DRIVER
    MSP_TIM5_Config(0, MCU_TIM5_TICK_UNIT, MCU_TIM5_TICK);
#endif

#ifdef ENABLE_MSP_TIMER6_DRIVER
    MSP_TIM6_Config(0, MCU_TIM6_TICK_UNIT, MCU_TIM6_TICK);
#endif

#ifdef ENABLE_MSP_TIMER7_DRIVER
    MSP_TIM7_Config(0, MCU_TIM7_TICK_UNIT, MCU_TIM7_TICK);
#endif

#ifdef ENABLE_MSP_TIMER8_DRIVER
    MSP_TIM8_Config(0, MCU_TIM8_TICK_UNIT, MCU_TIM8_TICK);
#endif

#ifdef ENABLE_HAL_TIMER_DRIVER
    HAL_Timer_Interface_t ops;

    ops.Config   = Timer_Config;
    ops.Control  = Timer_Control;
    ops.GetCount = Timer_Get_Count;
    ops.Start    = Timer_Start;
    ops.Stop     = Timer_Stop;
    
    HAL_Timer_Register(&ops, NULL);
#endif
}

__INLINE
void MSP_Timer_Start(TIM_TypeDef *timer)
{
    LL_TIM_EnableCounter(timer);
}

__INLINE
void MSP_Timer_Stop(TIM_TypeDef *timer)
{
    LL_TIM_DisableCounter(timer);
}

void MSP_Timer_SetCallback(TIM_TypeDef *timer, void *callback, void *param)
{
#ifdef ENABLE_MCU_TIM_CALLBACK
    uint8_t port;
    
    if (timer == TIM1)
    {
        port = 0;
    }
    else if (timer == TIM2)
    {
        port = 0;
    }
    else if (timer == TIM3)
    {
        port = 2;
    }
    else if (timer == TIM4)
    {
        port = 3;
    }
    else if (timer == TIM5)
    {
        port = 4;
    }
    else if (timer == TIM6)
    {
        port = 5;
    }
    else if (timer == TIM7)
    {
        port = 6;
    }
    else if (timer == TIM8)
    {
        port = 7;
    }
    else
    {
        return ;
    }
    
    Timer_ISR[port].Callback = (TimerIsrCallback)callback;
    Timer_ISR[port].Param    = param;
#endif
}

__WEAK
void MCU_TIM1_IRQ_Handle(void)
{

}

void TIM1_UP_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM1))
    {
#ifdef ENABLE_MCU_TIM_CALLBACK
        if (!IS_PTR_NULL(Timer_ISR[0].Callback))
        {
            Timer_ISR[0].Callback(Timer_ISR[0].Param);
        } 
#else
         MCU_TIM1_IRQ_Handle();   
#endif
        LL_TIM_ClearFlag_UPDATE(TIM1);
    }
}

__WEAK
void MCU_TIM2_IRQ_Handle(void)
{

}

void TIM2_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM2))
    {
#ifdef ENABLE_MCU_TIM_CALLBACK
        if (!IS_PTR_NULL(Timer_ISR[1].Callback))
        {
            Timer_ISR[1].Callback(Timer_ISR[1].Param);
        }
#else
        MCU_TIM2_IRQ_Handle();
#endif
        LL_TIM_ClearFlag_UPDATE(TIM2);
    }
}

__WEAK
void MCU_TIM3_IRQ_Handle(void)
{

}

void TIM3_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM3))
    {
#ifdef ENABLE_MCU_TIM_CALLBACK
        if (!IS_PTR_NULL(Timer_ISR[2].Callback))
        {
            Timer_ISR[2].Callback(Timer_ISR[2].Param);
        }
#else
        MCU_TIM3_IRQ_Handle();
#endif

        LL_TIM_ClearFlag_UPDATE(TIM3);
    }
}

__WEAK
void MCU_TIM4_IRQ_Handle(void)
{

}

void TIM4_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM4))
    {
#ifdef ENABLE_MCU_TIM_CALLBACK
        if (!IS_PTR_NULL(Timer_ISR[3].Callback))
        {
            Timer_ISR[3].Callback(Timer_ISR[3].Param);
        }
#else
        MCU_TIM4_IRQ_Handle();
#endif
        
        LL_TIM_ClearFlag_UPDATE(TIM4);
    }
}

__WEAK
void MCU_TIM5_IRQ_Handle(void)
{

}

void TIM5_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM5))
    {
#ifdef ENABLE_MCU_TIM_CALLBACK
        if (!IS_PTR_NULL(Timer_ISR[4].Callback))
        {
            Timer_ISR[4].Callback(Timer_ISR[4].Param);
        }
#else
        MCU_TIM5_IRQ_Handle();
#endif
        LL_TIM_ClearFlag_UPDATE(TIM5);
    }
}

__WEAK
void MCU_TIM6_IRQ_Handle(void)
{

}

void TIM6_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM6))
    {
#ifdef ENABLE_MCU_TIM_CALLBACK
        if (!IS_PTR_NULL(Timer_ISR[5].Callback))
        {
            Timer_ISR[5].Callback(Timer_ISR[5].Param);
        }
#else
        MCU_TIM6_IRQ_Handle();
#endif
        
        LL_TIM_ClearFlag_UPDATE(TIM6);
    }
}

__WEAK
void MCU_TIM7_IRQ_Handle(void)
{

}

void TIM7_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM7))
    {
#ifdef ENABLE_MCU_TIM_CALLBACK  
        if (!IS_PTR_NULL(Timer_ISR[6].Callback))
        {
            Timer_ISR[6].Callback(Timer_ISR[6].Param);
        }
#else
        MCU_TIM7_IRQ_Handle();
#endif
        
        LL_TIM_ClearFlag_UPDATE(TIM7);
    }
}

__WEAK
void MCU_TIM8_IRQ_Handle(void)
{

}

void TIM8_UP_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM8))
    {
#ifdef ENABLE_MCU_TIM_CALLBACK
        if (!IS_PTR_NULL(Timer_ISR[7].Callback))
        {
            Timer_ISR[7].Callback(Timer_ISR[7].Param);
        }
#else
        MCU_TIM8_IRQ_Handle();
#endif 

        LL_TIM_ClearFlag_UPDATE(TIM8);
    }
}


/** @}*/     /** stm32f1xx timer driver component */

/**********************************END OF FILE*********************************/
