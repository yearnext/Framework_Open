/**
 *******************************************************************************
 * @file       msp_stm32l476.c                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-12-17                                                      *
 * @brief      mcu config component                                            *
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
 * @defgroup mcu config component
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
__STATIC_INLINE
void LL_Init(void)
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
}

__STATIC_INLINE
void SystemClock_Config(void)
{
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);

    if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_4)
    {
        //! Error Do Something!
    }
    
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
    LL_RCC_HSE_Enable();

    /* Wait till HSE is ready */
    while(LL_RCC_HSE_IsReady() != 1);
    LL_RCC_LSI_Enable();

    /* Wait till LSI is ready */
    while(LL_RCC_LSI_IsReady() != 1);
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_1, 20, LL_RCC_PLLR_DIV_2);
    LL_RCC_PLL_EnableDomain_SYS();
    LL_RCC_PLL_Enable();

    /* Wait till PLL is ready */
    while(LL_RCC_PLL_IsReady() != 1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

    /* Wait till System clock is ready */
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);
    
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
    
    LL_Init1msTick(MCU_CLK_FREQUENCE);
    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
    LL_SetSystemCoreClock(MCU_CLK_FREQUENCE);
}

/* Exported functions --------------------------------------------------------*/
int MSP_Init(void)
{
#if defined(ENABLE_HAL_COMPONENT)
    HAL_Component_Init();
#endif
    
	LL_Init();
	
	SystemClock_Config();

#if defined(ENABLE_HAL_GPIO_DRIVER)
    MSP_GPIO_Init();
#endif
    
    return 0;
}
INIT_HAL_EXPORT(MSP_Init);


/** @}*/     /** mcu config component */

/**********************************END OF FILE*********************************/
