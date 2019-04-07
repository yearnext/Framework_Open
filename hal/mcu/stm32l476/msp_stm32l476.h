/**
 *******************************************************************************
 * @file       msp_stm32l476.h                                                 *
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L476_SUPPOR_PACKET_H__
#define __STM32L476_SUPPOR_PACKET_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx.h"
#include "stm32l4xx_ll_crs.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_iwdg.h"
#include "stm32l4xx_ll_spi.h"
#include "stm32l4xx_ll_tim.h"
#include "stm32l4xx_ll_adc.h"
#include "stm32l4xx_ll_usart.h"

#include "compiler.h"
#include "msp_conf.h"
#include "hal_device.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        硬件中断操作
 *******************************************************************************
 */
#define MSP_Enable_Interrupt()                              _st(__enable_irq();)
#define MSP_Disable_Interrupt()                            _st(__disable_irq();)

/**
 *******************************************************************************
 * @brief        定义中断优先级组
 *******************************************************************************
 */
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET GPIO COMPONENT API
 *******************************************************************************
 */
extern void MSP_GPIO_Init(void);

extern void MSP_GPIO_Config(GPIO_TypeDef *port, uint32_t pin, uint32_t mode);
#define MSP_GPIO_Input(port, pin)       _st(MSP_GPIO_Config(port, pin, LL_GPIO_MODE_INPUT);)
#define MSP_GPIO_Output(port, pin)      _st(MSP_GPIO_Config(port, pin, LL_GPIO_MODE_OUTPUT);)

extern void MSP_Pin_Init(uint16_t port, uint32_t pin, uint16_t mode);
#define MSP_Pin_Input(port, pin)        _st(MSP_Pin_Init(port, pin, HAL_PIN_INPUT);)
#define MSP_Pin_Output(port, pin)       _st(MSP_Pin_Init(port, pin, HAL_PIN_OUTPUT);)
extern void MSP_Pin_Set(uint16_t port, uint32_t pin);
extern void MSP_Pin_Clr(uint16_t port, uint32_t pin);
extern void MSP_Pin_Toggle(uint16_t port, uint32_t pin);
extern uint16_t MSP_Pin_Read(uint16_t port, uint32_t pin);

extern void MSP_GPIO_Set(GPIO_TypeDef *port, uint32_t pin);
extern void MSP_GPIO_Clr(GPIO_TypeDef *port, uint32_t pin);
extern void MSP_GPIO_Toggle(GPIO_TypeDef *port, uint32_t pin);
extern uint32_t MSP_GPIO_Get(GPIO_TypeDef *port, uint32_t pin);

extern void MSP_GPIO_Write(GPIO_TypeDef *port, uint32_t wr);
extern uint32_t MSP_GPIO_Read(GPIO_TypeDef *port);

/**
 *******************************************************************************
 * @brief        WDG Component API
 *******************************************************************************
 */
extern void MSP_IWDG_Init(void);
extern void MSP_IWDG_Update(void);

/**
 *******************************************************************************
 * @brief        MSP API
 *******************************************************************************
 */
extern int MSP_Init(void);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
