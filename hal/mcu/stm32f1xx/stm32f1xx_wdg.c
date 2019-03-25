/**
 *******************************************************************************
 * @file       stm32f1xx_wdg.c                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-01-16                                                      *
 * @brief      stm32f1xx wdg driver component                                  *
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
 * @defgroup stm32f1xx wdg driver component
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
/**
 *******************************************************************************
 * @brief       IWDG 初始化函数
 * @param       void
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
void MSP_IWDG_Init(void)
{
#ifdef ENABLE_MSP_WDG_DRIVER
    LL_IWDG_Enable(IWDG);

    LL_IWDG_EnableWriteAccess(IWDG);

    LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_4);

    LL_IWDG_SetReloadCounter(IWDG, 4095);

    while (LL_IWDG_IsReady(IWDG) != 1)
    {
    }

    LL_IWDG_ReloadCounter(IWDG);
#endif  
}

/**
 *******************************************************************************
 * @brief       IWDG 喂狗函数
 * @param       void
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
void MSP_IWDG_Update(void)
{
#ifdef ENABLE_MSP_WDG_DRIVER
    LL_IWDG_ReloadCounter(IWDG);
#endif
}

/** @}*/     /** stm32f1xx wdg driver component */

/**********************************END OF FILE*********************************/
