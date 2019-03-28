/**
 *******************************************************************************
 * @file       stm32l4xx_wdg.c                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2019-03-28                                                      *
 * @brief      stm32l4xx wdg driver component                                  *
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
 * @defgroup stm32l4xx wdg driver component
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
/* Exported functions --------------------------------------------------------*/
__INLINE
void MSP_WDG_Init(void)
{
#ifdef ENABLE_MSP_WDG_DRIVER
    LL_IWDG_Enable(IWDG);
    LL_IWDG_EnableWriteAccess(IWDG);
    LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_4);
    LL_IWDG_SetReloadCounter(IWDG, 4095);
    while (LL_IWDG_IsReady(IWDG) != 1);
    LL_IWDG_SetWindow(IWDG, 4095);
    LL_IWDG_ReloadCounter(IWDG);
#endif
}

__INLINE
void MSP_WDG_Feed(void)
{
#ifdef ENABLE_MSP_WDG_DRIVER
    LL_IWDG_ReloadCounter(IWDG);
#endif
}

/** @}*/     /** stm32l4xx wdg driver component */

/**********************************END OF FILE*********************************/
