/**
 *******************************************************************************
 * @file       stm32f1xx_pwm.c                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-01-16                                                      *
 * @brief      stm32f1xx pwm driver component                                  *
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
 * @defgroup stm32f1xx pwm driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_msp.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void MX_TIM1_Init(void)
{
    LL_TIM_InitTypeDef TIM_InitStruct;
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;
    LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct;

    LL_GPIO_InitTypeDef GPIO_InitStruct;
    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);

    TIM_InitStruct.Prescaler = 0;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 0;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter = 0;
    LL_TIM_Init(TIM1, &TIM_InitStruct);

    LL_TIM_DisableARRPreload(TIM1);

    LL_TIM_SetClockSource(TIM1, LL_TIM_CLOCKSOURCE_INTERNAL);

    LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH1);

    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = 0;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCNPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
    TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;
    LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

    LL_TIM_OC_DisableFast(TIM1, LL_TIM_CHANNEL_CH1);

    LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH2);

    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
    LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);

    LL_TIM_OC_DisableFast(TIM1, LL_TIM_CHANNEL_CH2);

    LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH3);

    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
    LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH3, &TIM_OC_InitStruct);

    LL_TIM_OC_DisableFast(TIM1, LL_TIM_CHANNEL_CH3);

    LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH4);

    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
    LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH4, &TIM_OC_InitStruct);

    LL_TIM_OC_DisableFast(TIM1, LL_TIM_CHANNEL_CH4);

    LL_TIM_SetTriggerOutput(TIM1, LL_TIM_TRGO_RESET);

    LL_TIM_DisableMasterSlaveMode(TIM1);

    TIM_BDTRInitStruct.OSSRState = LL_TIM_OSSR_DISABLE;
    TIM_BDTRInitStruct.OSSIState = LL_TIM_OSSI_DISABLE;
    TIM_BDTRInitStruct.LockLevel = LL_TIM_LOCKLEVEL_OFF;
    TIM_BDTRInitStruct.DeadTime = 0;
    TIM_BDTRInitStruct.BreakState = LL_TIM_BREAK_DISABLE;
    TIM_BDTRInitStruct.BreakPolarity = LL_TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStruct.AutomaticOutput = LL_TIM_AUTOMATICOUTPUT_DISABLE;
    LL_TIM_BDTR_Init(TIM1, &TIM_BDTRInitStruct);

    /**TIM1 GPIO Configuration    
    PE9     ------> TIM1_CH1
    PE11     ------> TIM1_CH2
    PE13     ------> TIM1_CH3
    PE14     ------> TIM1_CH4 
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_9|LL_GPIO_PIN_11|LL_GPIO_PIN_13|LL_GPIO_PIN_14;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    LL_GPIO_AF_EnableRemap_TIM1();

}
/* TIM2 init function */
void MX_TIM2_Init(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct;
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;

  LL_GPIO_InitTypeDef GPIO_InitStruct;
  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 0;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM2, &TIM_InitStruct);

  LL_TIM_DisableARRPreload(TIM2);

  LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);

  LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH1);

  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 0;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  LL_TIM_OC_Init(TIM2, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM2, LL_TIM_CHANNEL_CH1);

  LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH2);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM2, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM2, LL_TIM_CHANNEL_CH2);

  LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH3);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM2, LL_TIM_CHANNEL_CH3, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM2, LL_TIM_CHANNEL_CH3);

  LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH4);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM2, LL_TIM_CHANNEL_CH4, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM2, LL_TIM_CHANNEL_CH4);

  LL_TIM_SetTriggerOutput(TIM2, LL_TIM_TRGO_RESET);

  LL_TIM_DisableMasterSlaveMode(TIM2);

    /**TIM2 GPIO Configuration    
    PB10     ------> TIM2_CH3
    PB11     ------> TIM2_CH4
    PA15     ------> TIM2_CH1
    PB3     ------> TIM2_CH2 
    */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_10|LL_GPIO_PIN_11|LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_15;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  LL_GPIO_AF_EnableRemap_TIM2();

}
/* TIM3 init function */
void MX_TIM3_Init(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct;
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;

  LL_GPIO_InitTypeDef GPIO_InitStruct;
  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 0;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM3, &TIM_InitStruct);

  LL_TIM_DisableARRPreload(TIM3);

  LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_INTERNAL);

  LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH1);

  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 0;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  LL_TIM_OC_Init(TIM3, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM3, LL_TIM_CHANNEL_CH1);

  LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH2);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM3, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM3, LL_TIM_CHANNEL_CH2);

  LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH3);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM3, LL_TIM_CHANNEL_CH3, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM3, LL_TIM_CHANNEL_CH3);

  LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH4);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM3, LL_TIM_CHANNEL_CH4, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM3, LL_TIM_CHANNEL_CH4);

  LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_RESET);

  LL_TIM_DisableMasterSlaveMode(TIM3);

    /**TIM3 GPIO Configuration    
    PA6     ------> TIM3_CH1
    PA7     ------> TIM3_CH2
    PB0     ------> TIM3_CH3
    PB1     ------> TIM3_CH4 
    */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_6|LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}
/* TIM4 init function */
void MX_TIM4_Init(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct;
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;

  LL_GPIO_InitTypeDef GPIO_InitStruct;
  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);

  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 0;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM4, &TIM_InitStruct);

  LL_TIM_DisableARRPreload(TIM4);

  LL_TIM_SetClockSource(TIM4, LL_TIM_CLOCKSOURCE_INTERNAL);

  LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH1);

  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 0;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM4, LL_TIM_CHANNEL_CH1);

  LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH2);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM4, LL_TIM_CHANNEL_CH2);

  LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH3);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH3, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM4, LL_TIM_CHANNEL_CH3);

  LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH4);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH4, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM4, LL_TIM_CHANNEL_CH4);

  LL_TIM_SetTriggerOutput(TIM4, LL_TIM_TRGO_RESET);

  LL_TIM_DisableMasterSlaveMode(TIM4);

    /**TIM4 GPIO Configuration    
    PD12     ------> TIM4_CH1
    PD13     ------> TIM4_CH2
    PD14     ------> TIM4_CH3
    PD15     ------> TIM4_CH4 
    */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_12|LL_GPIO_PIN_13|LL_GPIO_PIN_14|LL_GPIO_PIN_15;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  LL_GPIO_AF_EnableRemap_TIM4();

}
/* TIM5 init function */
void MX_TIM5_Init(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct;
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;

  LL_GPIO_InitTypeDef GPIO_InitStruct;
  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);

  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 0;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM5, &TIM_InitStruct);

  LL_TIM_DisableARRPreload(TIM5);

  LL_TIM_SetClockSource(TIM5, LL_TIM_CLOCKSOURCE_INTERNAL);

  LL_TIM_OC_EnablePreload(TIM5, LL_TIM_CHANNEL_CH1);

  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 0;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  LL_TIM_OC_Init(TIM5, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM5, LL_TIM_CHANNEL_CH1);

  LL_TIM_OC_EnablePreload(TIM5, LL_TIM_CHANNEL_CH2);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM5, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM5, LL_TIM_CHANNEL_CH2);

  LL_TIM_OC_EnablePreload(TIM5, LL_TIM_CHANNEL_CH3);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM5, LL_TIM_CHANNEL_CH3, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM5, LL_TIM_CHANNEL_CH3);

  LL_TIM_OC_EnablePreload(TIM5, LL_TIM_CHANNEL_CH4);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM5, LL_TIM_CHANNEL_CH4, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM5, LL_TIM_CHANNEL_CH4);

  LL_TIM_SetTriggerOutput(TIM5, LL_TIM_TRGO_RESET);

  LL_TIM_DisableMasterSlaveMode(TIM5);

    /**TIM5 GPIO Configuration    
    PA0-WKUP     ------> TIM5_CH1
    PA1     ------> TIM5_CH2
    PA2     ------> TIM5_CH3
    PA3     ------> TIM5_CH4 
    */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2|LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}
/* TIM8 init function */
void MX_TIM8_Init(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct;
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;
  LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct;

  LL_GPIO_InitTypeDef GPIO_InitStruct;
  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);

  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 0;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(TIM8, &TIM_InitStruct);

  LL_TIM_DisableARRPreload(TIM8);

  LL_TIM_SetClockSource(TIM8, LL_TIM_CLOCKSOURCE_INTERNAL);

  LL_TIM_OC_EnablePreload(TIM8, LL_TIM_CHANNEL_CH1);

  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 0;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCNPolarity = LL_TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
  TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;
  LL_TIM_OC_Init(TIM8, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM8, LL_TIM_CHANNEL_CH1);

  LL_TIM_OC_EnablePreload(TIM8, LL_TIM_CHANNEL_CH2);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM8, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM8, LL_TIM_CHANNEL_CH2);

  LL_TIM_OC_EnablePreload(TIM8, LL_TIM_CHANNEL_CH3);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM8, LL_TIM_CHANNEL_CH3, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM8, LL_TIM_CHANNEL_CH3);

  LL_TIM_OC_EnablePreload(TIM8, LL_TIM_CHANNEL_CH4);

  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  LL_TIM_OC_Init(TIM8, LL_TIM_CHANNEL_CH4, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM8, LL_TIM_CHANNEL_CH4);

  LL_TIM_SetTriggerOutput(TIM8, LL_TIM_TRGO_RESET);

  LL_TIM_DisableMasterSlaveMode(TIM8);

  TIM_BDTRInitStruct.OSSRState = LL_TIM_OSSR_DISABLE;
  TIM_BDTRInitStruct.OSSIState = LL_TIM_OSSI_DISABLE;
  TIM_BDTRInitStruct.LockLevel = LL_TIM_LOCKLEVEL_OFF;
  TIM_BDTRInitStruct.DeadTime = 0;
  TIM_BDTRInitStruct.BreakState = LL_TIM_BREAK_DISABLE;
  TIM_BDTRInitStruct.BreakPolarity = LL_TIM_BREAK_POLARITY_HIGH;
  TIM_BDTRInitStruct.AutomaticOutput = LL_TIM_AUTOMATICOUTPUT_DISABLE;
  LL_TIM_BDTR_Init(TIM8, &TIM_BDTRInitStruct);

    /**TIM8 GPIO Configuration    
    PC6     ------> TIM8_CH1
    PC7     ------> TIM8_CH2
    PC8     ------> TIM8_CH3
    PC9     ------> TIM8_CH4 
    */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_6|LL_GPIO_PIN_7|LL_GPIO_PIN_8|LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/* Exported functions --------------------------------------------------------*/

/** @}*/     /** stm32f1xx pwm driver component */

/**********************************END OF FILE*********************************/
