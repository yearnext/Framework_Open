/**
 *******************************************************************************
 * @file       msp_stm32f1xx.h                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-01-16                                                      *
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
#ifndef __STM32F1xx_SUPPOR_PACKET_H__
#define __STM32F1xx_SUPPOR_PACKET_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"
#include "stm32f1xx_ll_iwdg.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_spi.h"

#include "compiler.h"
#include "msp_conf.h"
#include "hal_device.h"


/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        硬件中断操作
 *******************************************************************************
 */
#define MSP_Enable_Irq()                                    _st(__enable_irq();)
#define MSP_Disable_Irq()                                  _st(__disable_irq();)

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        GPIO Component API
 *******************************************************************************
 */
extern void MSP_GPIO_Init(void);
 
//! MSP LV0 API
extern void MSP_GPIO_Set(GPIO_TypeDef *port, uint32_t pin);
extern void MSP_GPIO_Clr(GPIO_TypeDef *port, uint32_t pin);
extern uint32_t MSP_GPIO_Get(GPIO_TypeDef *port, uint32_t pin);
extern void MSP_GPIO_Write(GPIO_TypeDef *port, uint32_t wr);
extern uint32_t MSP_GPIO_Read(GPIO_TypeDef *port);
extern void MSP_GPIO_Config(GPIO_TypeDef *port, uint32_t pin, uint32_t mode);

#define MSP_GPIO_Output(port, pin) _st(MSP_GPIO_Config(port, pin, LL_GPIO_MODE_OUTPUT);)
#define MSP_GPIO_Input(port, pin)  _st(MSP_GPIO_Config(port, pin, LL_GPIO_MODE_INPUT);)

//! MSP LV1 API
extern void MSP_Pin_Init(uint16_t port, uint32_t pin, uint16_t mode);
extern void MSP_Pin_Set(uint16_t port, uint32_t pin);
extern void MSP_Pin_Clr(uint16_t port, uint32_t pin);
extern void MSP_Pin_Toggle(uint16_t port, uint32_t pin);
extern uint16_t MSP_Pin_Read(uint16_t port, uint32_t pin);

#define MSP_Pin_Output(port, pin) _st(MSP_Pin_Init(port, pin, HAL_PIN_OUTPUT);)
#define MSP_Pin_Input(port, pin)  _st(MSP_Pin_Init(port, pin, HAL_PIN_INPUT);)

/**
 *******************************************************************************
 * @brief        UART Component API
 *******************************************************************************
 */
extern void MSP_UART_Init(void);

extern uint16_t MSP_UART_Write(USART_TypeDef *uart, uint8_t *buf, uint16_t pos, uint16_t len);
extern uint16_t MSP_UART_Send(USART_TypeDef *uart, uint8_t c);
extern uint16_t MSP_UART_Recv(USART_TypeDef *uart, uint8_t *c);
extern void MSP_UART_SetCallback(USART_TypeDef *uart, void *callback, void *param);

/**
 *******************************************************************************
 * @brief        SPI Component API
 *******************************************************************************
 */
extern void MSP_SPI_Init(void);

/**
 *******************************************************************************
 * @brief        TIMER Component API
 *******************************************************************************
 */
extern void MSP_Timer_Init(void);

extern void *MSP_SYSTICK_Init(void);
extern void MSP_Timer_Start(TIM_TypeDef *timer);
extern void MSP_Timer_Stop(TIM_TypeDef *timer);
extern void MSP_Timer_SetCallback(TIM_TypeDef *timer, void *callback, void *param);

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
