/**
 *******************************************************************************
 * @file       msp_conf.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-01-13                                                      *
 * @brief      msp config head files                                           *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. STM32L50x Series MCU Support Packet Config File                          *
 *******************************************************************************
 */
 
/**
 * @defgroup msp config file
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L4xx_MSP_CONF_H__
#define __STM32L4xx_MSP_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Define and config ---------------------------------------------------------*/
// <<< Use Configuration Wizard in Context Menu >>>
// <c1>Enable HAL Driver Component
//  <i>Enable HAL Driver Component
#define ENABLE_HAL_DRIVER_SUPPORT
// </c>

// <o>Set Internal high speed RC clock frequency(unit: hz)
//  <i>Default: 80000000UL  (80MHz)
#define MCU_CLK_FREQUENCE 80000000UL

// <o>Set SysTick Period
//  <i>Default: 1000 (Unit:us)
#define MCU_SYSTICK_FREQUENCE 1000

// <c1>Enable MCU Clock Test
//  <i>Enable MCU Clock Test
#define ENABLE_MSP_CLK_OUT_DRIVER
// </c>

// <c1>Enable MCU Extern High Clock
//  <i>Enable MCU Extern High Clock
//#define ENABLE_EXT_HIGH_CLOCK
// </c>

// <c1>Enable MCU Extern Low Clock
//  <i>Enable MCU Extern Low Clock
//#define ENABLE_EXT_LOW_CLOCK
// </c>

// <c1>Enable MCU Low Power Management
//  <i>Enable MCU Low Power Management
//#define ENABLE_LOW_POWER_MANAGEMENT
// </c>

// <c1>Enable MSP Test Component
//  <i>Enable MSP Test Component
//#define ENABLE_MSP_TEST
// </c>


// <h>MCU Timer Param Config
//  <i>MCU Timer Param Config

// <c1>Enable MSP TIMER ISR CALLBACK
//  <i>Enable MSP TIMER ISR CALLBACK
#define ENABLE_MCU_TIM_CALLBACK
// </c>

// <h>MCU TIM0 Param Config
//  <i>MCU TIM0 Param Config

// <o>Set TIM0 Tick Value
//  <i>default: 1000 (1KHz)
#define MCU_TIM0_TICK 1000UL

// <o>Set TIM0 Tick Unit
//  <0=> us
//  <1=> ms
//  <2=> 100ms
//  <3=> sec
#define MCU_TIM0_TICK_UNIT 1

// <c1>Enable MSP TIM0 Driver
//  <i>Enable MSP TIM0 Driver
//#define ENABLE_MSP_TIMER0_DRIVER
// </c>

//! end of the MCU TIM0 Param Config
// </h>

// <h>MCU TIM1 Param Config
//  <i>MCU TIM1 Param Config

// <o>Set TIM1 Tick Value
//  <i>default: 1000 (1KHz)
#define MCU_TIM1_TICK 1000UL

// <o>Set TIM1 Tick Unit
//  <0=> us
//  <1=> ms
//  <2=> 100ms
//  <3=> sec
#define MCU_TIM1_TICK_UNIT 1

// <c1>Enable MSP TIM1 Driver
//  <i>Enable MSP TIM1 Driver
//#define ENABLE_MSP_TIMER1_DRIVER
// </c>

//! end of the MCU TIM1 Param Config
// </h>

// <h>MCU TIM2 Param Config
//  <i>MCU TIM2 Param Config

// <o>Set TIM2 Tick Value
//  <i>default: 1000 (1KHz)
#define MCU_TIM2_TICK 1000UL

// <o>Set TIM2 Tick Unit
//  <0=> us
//  <1=> ms
//  <2=> 100ms
//  <3=> sec
#define MCU_TIM2_TICK_UNIT 1

// <c1>Enable MSP TIM2 Driver
//  <i>Enable MSP TIM2 Driver
//#define ENABLE_MSP_TIMER2_DRIVER
// </c>

//! end of the MCU TIM2 Param Config
// </h>

// <h>MCU TIM3 Param Config
//  <i>MCU TIM3 Param Config

// <o>Set TIM3 Tick Value
//  <i>default: 1000 (1KHz)
#define MCU_TIM3_TICK 1000UL

// <o>Set TIM3 Tick Unit
//  <0=> us
//  <1=> ms
//  <2=> 100ms
//  <3=> sec
#define MCU_TIM3_TICK_UNIT 1

// <c1>Enable MSP TIM3 Driver
//  <i>Enable MSP TIM3 Driver
//#define ENABLE_MSP_TIMER3_DRIVER
// </c>

//! end of the MCU TIM3 Param Config
// </h>

// <h>MCU TIM4 Param Config
//  <i>MCU TIM4 Param Config

// <o>Set TIM4 Tick Value
//  <i>default: 1000 (1KHz)
#define MCU_TIM4_TICK 1000UL

// <o>Set TIM4 Tick Unit
//  <0=> us
//  <1=> ms
//  <2=> 100ms
//  <3=> sec
#define MCU_TIM4_TICK_UNIT 1

// <c1>Enable MSP TIM4 Driver
//  <i>Enable MSP TIM4 Driver
//#define ENABLE_MSP_TIMER4_DRIVER
// </c>

//! end of the MCU TIM4 Param Config
// </h>

// <h>MCU TIM5 Param Config
//  <i>MCU TIM5 Param Config

// <o>Set TIM5 Tick Value
//  <i>default: 1000 (1KHz)
#define MCU_TIM5_TICK 1000UL

// <o>Set TIM5 Tick Unit
//  <0=> us
//  <1=> ms
//  <2=> 100ms
//  <3=> sec
#define MCU_TIM5_TICK_UNIT 1

// <c1>Enable MSP TIM5 Driver
//  <i>Enable MSP TIM5 Driver
//#define ENABLE_MSP_TIMER5_DRIVER
// </c>

//! end of the MCU TIM5 Param Config
// </h>

// <h>MCU TIM6 Param Config
//  <i>MCU TIM6 Param Config

// <o>Set TIM6 Tick Value
//  <i>default: 1000 (1KHz)
#define MCU_TIM6_TICK 1000UL

// <o>Set TIM6 Tick Unit
//  <0=> us
//  <1=> ms
//  <2=> 100ms
//  <3=> sec
#define MCU_TIM6_TICK_UNIT 1

// <c1>Enable MSP TIM6 Driver
//  <i>Enable MSP TIM6 Driver
//#define ENABLE_MSP_TIMER6_DRIVER
// </c>

//! end of the MCU TIM6 Param Config
// </h>

// <h>MCU TIM7 Param Config
//  <i>MCU TIM7 Param Config

// <o>Set TIM7 Tick Value
//  <i>default: 1000 (1KHz)
#define MCU_TIM7_TICK 1000UL

// <o>Set TIM7 Tick Unit
//  <0=> us
//  <1=> ms
//  <2=> 100ms
//  <3=> sec
#define MCU_TIM7_TICK_UNIT 1

// <c1>Enable MSP TIM7 Driver
//  <i>Enable MSP TIM7 Driver
//#define ENABLE_MSP_TIMER7_DRIVER
// </c>

//! end of the MCU TIM7 Param Config
// </h>

// <h>MCU TIM8 Param Config
//  <i>MCU TIM8 Param Config

// <o>Set TIM8 Tick Value
//  <i>default: 1000 (1KHz)
#define MCU_TIM8_TICK 1000UL

// <o>Set TIM8 Tick Unit
//  <0=> us
//  <1=> ms
//  <2=> 100ms
//  <3=> sec
#define MCU_TIM8_TICK_UNIT 1

// <c1>Enable MSP TIM8 Driver
//  <i>Enable MSP TIM8 Driver
//#define ENABLE_MSP_TIMER8_DRIVER
// </c>

//! end of the MCU TIM8 Param Config
// </h>

#if defined(ENABLE_MSP_TIMER1_DRIVER) || defined(ENABLE_MSP_TIMER2_DRIVER)
    || defined(ENABLE_MSP_TIMER3_DRIVER) || defined(ENABLE_MSP_TIMER4_DRIVER)
    || defined(ENABLE_MSP_TIMER5_DRIVER) || defined(ENABLE_MSP_TIMER6_DRIVER)
    || defined(ENABLE_MSP_TIMER7_DRIVER) || defined(ENABLE_MSP_TIMER8_DRIVER)
#define ENABLE_MSP_TIMER_DRIVER
#endif

//! end of the MCU Timer Param Config
// </h>

// <h>MCU PWM Param Config
//  <i>MCU PWM Param Config

// <c1>Enable MCU PWM Test Component
//  <i>Enable MCU PWM Test Component
//#define ENABLE_MSP_PWM_TEST
// </c>

// <h>MCU PWM CH0 Param Config
//  <i>MCU PWM CH0 Param Config

// <o>Set MCU PWM CH0 Port
//  <0=> PE9(default)
//  <i> (default)TIM1 CH1 ---> PE9
#define MCU_PWM_CH0_AF_PORT 0

// <o>Set MCU PWM CH0 Default Period
//  <i>default: 100K (Normal)
#define MCU_PWM_CH0_DEFAULT_PERIOD 100000

// <o>Set MCU PWM CH0 Default Duty
//  <i>default: 0 (Normal)
#define MCU_PWM_CH0_DEFAULT_DUTY   0

// <c1>Enable MSP PWM CH0 Driver
//  <i>Enable MSP PWM CH0 Driver
//#define ENABLE_MSP_PWM_CH0_DRIVER
// </c>

//! end of the MCU PWM CH0 Param Config
// </h>

// <h>MCU PWM CH1 Param Config
//  <i>MCU PWM CH1 Param Config

// <o>Set MCU PWM CH1 Port
//  <0=> PE11(default)
//  <i> (default)TIM1 CH2 ---> PE11
#define MCU_PWM_CH1_AF_PORT 0

// <o>Set MCU PWM CH1 Default Period
//  <i>default: 100K (Normal)
#define MCU_PWM_CH1_DEFAULT_PERIOD 100000

// <o>Set MCU PWM CH1 Default Duty
//  <i>default: 0 (Normal)
#define MCU_PWM_CH1_DEFAULT_DUTY   0

// <c1>Enable MSP PWM CH1 Driver
//  <i>Enable MSP PWM CH1 Driver
//#define ENABLE_MSP_PWM_CH1_DRIVER
// </c>

//! end of the MCU PWM CH1 Param Config
// </h>

// <h>MCU PWM CH2 Param Config
//  <i>MCU PWM CH2 Param Config

// <o>Set MCU PWM CH2 Port
//  <0=> PE13(default)
//  <i> (default)TIM1 CH3 ---> PE13
#define MCU_PWM_CH2_AF_PORT 0

// <o>Set MCU PWM CH2 Default Period
//  <i>default: 100K (Normal)
#define MCU_PWM_CH2_DEFAULT_PERIOD 100000

// <o>Set MCU PWM CH2 Default Duty
//  <i>default: 0 (Normal)
#define MCU_PWM_CH2_DEFAULT_DUTY   0

// <c1>Enable MSP PWM CH2 Driver
//  <i>Enable MSP PWM CH2 Driver
//#define ENABLE_MSP_PWM_CH2_DRIVER
// </c>

//! end of the MCU PWM CH2 Param Config
// </h>

// <h>MCU PWM CH3 Param Config
//  <i>MCU PWM CH3 Param Config

// <o>Set MCU PWM CH3 Port
//  <0=> PE14(default)
//  <i> (default)TIM1 CH4 ---> PE14
#define MCU_PWM_CH3_AF_PORT 0

// <o>Set MCU PWM CH3 Default Period
//  <i>default: 100K (Normal)
#define MCU_PWM_CH3_DEFAULT_PERIOD 100000

// <o>Set MCU PWM CH3 Default Duty
//  <i>default: 0 (Normal)
#define MCU_PWM_CH3_DEFAULT_DUTY   0

// <c1>Enable MSP PWM CH3 Driver
//  <i>Enable MSP PWM CH3 Driver
//#define ENABLE_MSP_PWM_CH3_DRIVER
// </c>

//! end of the MCU PWM CH3 Param Config
// </h>

// <h>MCU PWM CH4 Param Config
//  <i>MCU PWM CH4 Param Config

// <o>Set MCU PWM CH4 Port
//  <0=> PB10(default)
//  <i> (default)TIM2 CH3 ---> PB10
#define MCU_PWM_CH4_AF_PORT 0

// <o>Set MCU PWM CH4 Default Period
//  <i>default: 100K (Normal)
#define MCU_PWM_CH4_DEFAULT_PERIOD 100000

// <o>Set MCU PWM CH4 Default Duty
//  <i>default: 0 (Normal)
#define MCU_PWM_CH4_DEFAULT_DUTY   0

// <c1>Enable MSP PWM CH4 Driver
//  <i>Enable MSP PWM CH4 Driver
//#define ENABLE_MSP_PWM_CH4_DRIVER
// </c>

//! end of the MCU PWM CH4 Param Config
// </h>

// <h>MCU PWM CH5 Param Config
//  <i>MCU PWM CH5 Param Config

// <o>Set MCU PWM CH5 Port
//  <0=> PB11(default)
//  <i> (default)TIM2 CH4 ---> PB11
#define MCU_PWM_CH5_AF_PORT 0

// <o>Set MCU PWM CH5 Default Period
//  <i>default: 100K (Normal)
#define MCU_PWM_CH5_DEFAULT_PERIOD 100000

// <o>Set MCU PWM CH5 Default Duty
//  <i>default: 0 (Normal)
#define MCU_PWM_CH5_DEFAULT_DUTY   0

// <c1>Enable MSP PWM CH5 Driver
//  <i>Enable MSP PWM CH5 Driver
//#define ENABLE_MSP_PWM_CH5_DRIVER
// </c>

//! end of the MCU PWM CH5 Param Config
// </h>

// <h>MCU PWM CH6 Param Config
//  <i>MCU PWM CH6 Param Config

// <o>Set MCU PWM CH6 Port
//  <0=> PA15(default)
//  <i> (default)TIM2 CH1 ---> PA15
#define MCU_PWM_CH6_AF_PORT 0

// <o>Set MCU PWM CH6 Default Period
//  <i>default: 100K (Normal)
#define MCU_PWM_CH6_DEFAULT_PERIOD 100000

// <o>Set MCU PWM CH6 Default Duty
//  <i>default: 0 (Normal)
#define MCU_PWM_CH6_DEFAULT_DUTY   0

// <c1>Enable MSP PWM CH6 Driver
//  <i>Enable MSP PWM CH6 Driver
//#define ENABLE_MSP_PWM_CH6_DRIVER
// </c>

//! end of the MCU PWM CH6 Param Config
// </h>

// <h>MCU PWM CH7 Param Config
//  <i>MCU PWM CH7 Param Config

// <o>Set MCU PWM CH7 Port
//  <0=> PB3(default)
//  <i> (default)TIM2 CH2 ---> PB3
#define MCU_PWM_CH7_AF_PORT 0

// <o>Set MCU PWM CH7 Default Period
//  <i>default: 100K (Normal)
#define MCU_PWM_CH7_DEFAULT_PERIOD 100000

// <o>Set MCU PWM CH7 Default Duty
//  <i>default: 0 (Normal)
#define MCU_PWM_CH7_DEFAULT_DUTY   0

// <c1>Enable MSP PWM CH7 Driver
//  <i>Enable MSP PWM CH7 Driver
//#define ENABLE_MSP_PWM_CH7_DRIVER
// </c>

//! end of the MCU PWM CH7 Param Config
// </h>

#if defined(ENABLE_MSP_PWM_CH1_DRIVER) || defined(ENABLE_MSP_PWM_CH2_DRIVER)
    || defined(ENABLE_MSP_PWM_CH3_DRIVER) || defined(ENABLE_MSP_PWM_CH4_DRIVER)
    || defined(ENABLE_MSP_PWM_CH5_DRIVER) || defined(ENABLE_MSP_PWM_CH6_DRIVER)
    || defined(ENABLE_MSP_PWM_CH7_DRIVER) || defined(ENABLE_MSP_PWM_CH6_DRIVER)
#define ENABLE_MSP_PWM_DRIVER
#endif

//! end of the MCU PWM Param Config
// </h>

// <h>MCU ADC Param Config
//  <i>MCU ADC Param Config

// <h>MCU ADC CH0 Param Config
//  <i>MCU ADC CH0 Param Config

// <o>Set MCU ADC CH0 Port
//  <0=>PC0
#define MCU_ADC_CH0_AF_PORT 0

// <c1>Enable MSP ADC CH0 Driver
//  <i>Enable MSP ADC CH0 Driver
//#define ENABLE_MSP_ADC_CH0_DRIVER
// </c>

//! end of the MCU ADC CH0 Param Config
// </h>

// <h>MCU ADC CH1 Param Config
//  <i>MCU ADC CH1 Param Config

// <o>Set MCU ADC CH1 Port
//  <0=>PC1
#define MCU_ADC_CH1_AF_PORT 0

// <c1>Enable MSP ADC CH1 Driver
//  <i>Enable MSP ADC CH1 Driver
//#define ENABLE_MSP_ADC_CH1_DRIVER
// </c>

//! end of the MCU ADC CH1 Param Config
// </h>

// <h>MCU ADC CH2 Param Config
//  <i>MCU ADC CH2 Param Config

// <o>Set MCU ADC CH2 Port
//  <0=>PC2
#define MCU_ADC_CH2_AF_PORT 0

// <c1>Enable MSP ADC CH2 Driver
//  <i>Enable MSP ADC CH2 Driver
//#define ENABLE_MSP_ADC_CH2_DRIVER
// </c>

//! end of the MCU ADC CH2 Param Config
// </h>

// <h>MCU ADC CH3 Param Config
//  <i>MCU ADC CH3 Param Config

// <o>Set MCU ADC CH3 Port
//  <0=>PC3
#define MCU_ADC_CH3_AF_PORT 0

// <c1>Enable MSP ADC CH3 Driver
//  <i>Enable MSP ADC CH3 Driver
//#define ENABLE_MSP_ADC_CH3_DRIVER
// </c>

//! end of the MCU ADC CH3 Param Config
// </h>

// <h>MCU ADC CH4 Param Config
//  <i>MCU ADC CH4 Param Config

// <o>Set MCU ADC CH4 Port
//  <0=>PA0
#define MCU_ADC_CH4_AF_PORT 0

// <c1>Enable MSP ADC CH4 Driver
//  <i>Enable MSP ADC CH4 Driver
//#define ENABLE_MSP_ADC_CH4_DRIVER
// </c>

//! end of the MCU ADC CH4 Param Config
// </h>

// <h>MCU ADC CH5 Param Config
//  <i>MCU ADC CH5 Param Config

// <o>Set MCU ADC CH5 Port
//  <0=>PA1
#define MCU_ADC_CH5_AF_PORT 0

// <c1>Enable MSP ADC CH5 Driver
//  <i>Enable MSP ADC CH5 Driver
//#define ENABLE_MSP_ADC_CH5_DRIVER
// </c>

//! end of the MCU ADC CH5 Param Config
// </h>

// <h>MCU ADC CH6 Param Config
//  <i>MCU ADC CH6 Param Config

// <o>Set MCU ADC CH6 Port
//  <0=>PA2
#define MCU_ADC_CH6_AF_PORT 0

// <c1>Enable MSP ADC CH6 Driver
//  <i>Enable MSP ADC CH6 Driver
//#define ENABLE_MSP_ADC_CH6_DRIVER
// </c>

//! end of the MCU ADC CH6 Param Config
// </h>

// <h>MCU ADC CH7 Param Config
//  <i>MCU ADC CH7 Param Config

// <o>Set MCU ADC CH7 Port
//  <0=>PA3
#define MCU_ADC_CH7_AF_PORT 0

// <c1>Enable MSP ADC CH7 Driver
//  <i>Enable MSP ADC CH7 Driver
//#define ENABLE_MSP_ADC_CH7_DRIVER
// </c>

//! end of the MCU ADC CH7 Param Config
// </h>

// <h>MCU ADC CH8 Param Config
//  <i>MCU ADC CH8 Param Config

// <o>Set MCU ADC CH8 Port
//  <0=>PA4
#define MCU_ADC_CH8_AF_PORT 0

// <c1>Enable MSP ADC CH8 Driver
//  <i>Enable MSP ADC CH8 Driver
//#define ENABLE_MSP_ADC_CH8_DRIVER
// </c>

//! end of the MCU ADC CH8 Param Config
// </h>

// <h>MCU ADC CH9 Param Config
//  <i>MCU ADC CH9 Param Config

// <o>Set MCU ADC CH9 Port
//  <0=>PA5
#define MCU_ADC_CH9_AF_PORT 0

// <c1>Enable MSP ADC CH9 Driver
//  <i>Enable MSP ADC CH9 Driver
//#define ENABLE_MSP_ADC_CH9_DRIVER
// </c>

//! end of the MCU ADC CH9 Param Config
// </h>

// <h>MCU ADC CH10 Param Config
//  <i>MCU ADC CH10 Param Config

// <o>Set MCU ADC CH10 Port
//  <0=>PA6
#define MCU_ADC_CH10_AF_PORT 0

// <c1>Enable MSP ADC CH10 Driver
//  <i>Enable MSP ADC CH10 Driver
//#define ENABLE_MSP_ADC_CH10_DRIVER
// </c>

//! end of the MCU ADC CH10 Param Config
// </h>

// <h>MCU ADC CH11 Param Config
//  <i>MCU ADC CH11 Param Config

// <o>Set MCU ADC CH11 Port
//  <0=>PA7
#define MCU_ADC_CH11_AF_PORT 0

// <c1>Enable MSP ADC CH11 Driver
//  <i>Enable MSP ADC CH11 Driver
//#define ENABLE_MSP_ADC_CH11_DRIVER
// </c>

//! end of the MCU ADC CH11 Param Config
// </h>

// <h>MCU ADC CH12 Param Config
//  <i>MCU ADC CH12 Param Config

// <o>Set MCU ADC CH12 Port
//  <0=>PC4
#define MCU_ADC_CH12_AF_PORT 0

// <c1>Enable MSP ADC CH12 Driver
//  <i>Enable MSP ADC CH12 Driver
//#define ENABLE_MSP_ADC_CH12_DRIVER
// </c>

//! end of the MCU ADC CH12 Param Config
// </h>

// <h>MCU ADC CH13 Param Config
//  <i>MCU ADC CH13 Param Config

// <o>Set MCU ADC CH13 Port
//  <0=>PC5
#define MCU_ADC_CH13_AF_PORT 0

// <c1>Enable MSP ADC CH13 Driver
//  <i>Enable MSP ADC CH13 Driver
//#define ENABLE_MSP_ADC_CH13_DRIVER
// </c>

//! end of the MCU ADC CH13 Param Config
// </h>

// <h>MCU ADC CH13 Param Config
//  <i>MCU ADC CH13 Param Config

// <o>Set MCU ADC CH14 Port
//  <0=>PB0
#define MCU_ADC_CH14_AF_PORT 0

// <c1>Enable MSP ADC CH14 Driver
//  <i>Enable MSP ADC CH14 Driver
//#define ENABLE_MSP_ADC_CH14_DRIVER
// </c>

//! end of the MCU ADC CH14 Param Config
// </h>

// <h>MCU ADC CH15 Param Config
//  <i>MCU ADC CH15 Param Config

// <o>Set MCU ADC CH15 Port
//  <0=>PB1
#define MCU_ADC_CH15_AF_PORT 0

// <c1>Enable MSP ADC CH15 Driver
//  <i>Enable MSP ADC CH15 Driver
//#define ENABLE_MSP_ADC_CH15_DRIVER
// </c>

//! end of the MCU ADC CH15 Param Config
// </h>

#if defined(ENABLE_MSP_ADC_CH1_DRIVER)     || defined(ENABLE_MSP_ADC_CH2_DRIVER)
    || defined(ENABLE_MSP_ADC_CH3_DRIVER)  || defined(ENABLE_MSP_ADC_CH4_DRIVER)
    || defined(ENABLE_MSP_ADC_CH5_DRIVER)  || defined(ENABLE_MSP_ADC_CH6_DRIVER)
    || defined(ENABLE_MSP_ADC_CH7_DRIVER)  || defined(ENABLE_MSP_ADC_CH8_DRIVER)
    || defined(ENABLE_MSP_ADC_CH9_DRIVER)  || defined(ENABLE_MSP_ADC_CH10_DRIVER)
    || defined(ENABLE_MSP_ADC_CH11_DRIVER) || defined(ENABLE_MSP_ADC_CH12_DRIVER)
    || defined(ENABLE_MSP_ADC_CH13_DRIVER) || defined(ENABLE_MSP_ADC_CH14_DRIVER)
    || defined(ENABLE_MSP_ADC_CH15_DRIVER)
#define ENABLE_MSP_ADC_DRIVER
#endif

//! end of the MCU ADC Param Config
// </h>

// <h>MCU UART Param Config
//  <i>MCU UART Param Config

// <c1>Enable MCU UART Test Component
//  <i>Enable MCU UART Test Component
#define ENABLE_MSP_UART_TEST
// </c>

// <h>MCU UART1 Param Config
//  <i>MCU UART1 Param Config

// <o>Set UART1 AF Port
//  <0=> PA9,PA10(default)
//  <i> (default)Tx ---> PA9    Rx ---> PA10
#define MCU_UART1_AF_PORT 0

// <o>Set UART1 baud (uint: bps)
//  <i>default: 115200 (bps)
#define MCU_UART1_BAUD 9600UL

// <o>Set UART1 data bits
//  <i>default: 8
#define MCU_UART1_DATA_BITS 8

// <o>Set UART1 stop bits
//  <i>default: 1
#define MCU_UART1_STOP_BITS 1

// <o>Set UART1 parity mode
//  <i>default: 0
#define MCU_UART1_PARITY    0

// <c1>Enable MCU UART1 Tx ISR
//  <i>Enable MCU UART1 Tx ISR
#define ENABLE_UART1_TX_ISR
// </c>

// <c1>Enable MCU UART1 Tx DMA
//  <i>Enable MCU UART1 Tx DMA
#define ENABLE_UART1_TX_DMA
// </c>

// <c1>Enable MCU UART1 Rx ISR
//  <i>Enable MCU UART1 Rx ISR
#define ENABLE_UART1_RX_ISR
// </c>

// <c1>Enable MSP UART1 Driver
//  <i>Enable MSP UART1 Driver
//#define ENABLE_MSP_UART1_DRIVER
// </c>

//! end of the MCU UART1 Param Config
// </h>

// <h>MCU UART2 Param Config
//  <i>MCU UART2 Param Config

// <o>Set UART2 AF Port
//  <0=> PA2,PA3(default)
//  <i> (default)Tx ---> PA2    Rx ---> PA3
#define MCU_UART2_AF_PORT 0

// <o>Set UART2 baud (uint: bps)
//  <i>default: 115200 (bps)
#define MCU_UART2_BAUD 9600UL

// <o>Set UART2 data bits
//  <i>default: 8
#define MCU_UART2_DATA_BITS 8

// <o>Set UART2 stop bits
//  <i>default: 1
#define MCU_UART2_STOP_BITS 1

// <o>Set UART2 parity mode
//  <i>default: 0
#define MCU_UART2_PARITY    0

// <c1>Enable MCU UART2 Tx ISR
//  <i>Enable MCU UART2 Tx ISR
#define ENABLE_UART2_TX_ISR
// </c>

// <c1>Enable MCU UART2 Tx DMA
//  <i>Enable MCU UART2 Tx DMA
#define ENABLE_UART2_TX_DMA
// </c>

// <c1>Enable MCU UART2 Rx ISR
//  <i>Enable MCU UART2 Rx ISR
#define ENABLE_UART2_RX_ISR
// </c>

// <c1>Enable MSP UART2 Driver
//  <i>Enable MSP UART2 Driver
//#define ENABLE_MSP_UART2_DRIVER
// </c>

//! end of the MCU UART2 Param Config
// </h>

#if defined(ENABLE_MSP_UART1_DRIVER) || defined(ENABLE_MSP_UART2_DRIVER)
#define ENABLE_MSP_UART_DRIVER
#endif

//! end of the MCU UART Param Config
// </h>

// <h>MCU SPI Param Config
//  <i>MCU SPI Param Config

// <h>MCU SPI1 Param Config
//  <i>MCU SPI1 Param Config

// <o>Set SPI1 AF Port
//  <0=> PA5,PA6,PA7(default)
//  <i> (default)SCK ---> PA5    MISO ---> PA6    MOSI ---> PA7
#define MCU_SPI1_AF_PORT 0

// <o>Set SPI1 Mode (uint: bps)
//  <i>default: 0 (0: Master Mode 1:Slave Mode)
#define MCU_SPI1_MODE 0

// <o>Set SPI1 Clock (uint: bps)
//  <i>default: 3 (0: 8MHz 1:4MHz 2:2MHz 3:1MHz)
#define MCU_SPI1_CLOCK 3

// <o>Set SPI1 Clock Frame (uint: bps)
//  <i>default: 0
//!           |    CPHA = 0   |   CPHA = 1   |
//!           |               |              |
//!           |     |___      |     ___|     |
//! CPOL = 0  |     |   |     |    |   |     |
//!           |   __|   |__   |  __|   |__   |
//!           |     |         |        |     |
//!           |               |              |
//!           |---------------|--------------|
//!           |               |              |
//!           |   __|    __   |  __    |__   |
//! CPOL = 1  |     |   |     |    |   |     |
//!           |     |___|     |    |___|     |
//!           |     |         |        |     |
//!           |               |              |
#define MCU_SPI1_CLK_FRAME 0

// <o>Set SPI1 First Bit (uint: bps)
//  <i>default: 1 (0: LSB 1: MSB)
#define MCU_SPI1_FIRST_BIT 1

// <c1>Enable MCU SPI1 Rx ISR
//  <i>Enable MCU SPI1 Rx ISR
//#define ENABLE_SPI1_RX_ISR
// </c>

// <c1>Enable MCU SPI1 Tx ISR
//  <i>Enable MCU SPI1 Tx ISR
//#define ENABLE_SPI1_TX_ISR
// </c>

// <c1>Enable MSP SPI1 Driver
//  <i>Enable MSP SPI1 Driver
//#define ENABLE_MSP_SPI1_DRIVER
// </c>

//! end of the MCU SPI1 Param Config
// </h>

// <h>MCU SPI2 Param Config
//  <i>MCU SPI2 Param Config

// <o>Set SPI2 AF Port
//  <0=> PB13,PB14,PB15(default)
//  <i> (default)SCK ---> PB13    MISO ---> PB14    MOSI ---> PB15
#define MCU_SPI2_AF_PORT 0

// <o>Set SPI2 Mode (uint: bps)
//  <i>default: 0 (0: Master Mode 1:Slave Mode)
#define MCU_SPI2_MODE 0

// <o>Set SPI2 Clock (uint: bps)
//  <i>default: 3 (0: 8MHz 1:4MHz 2:2MHz 3:1MHz)
#define MCU_SPI2_CLOCK 3

// <o>Set SPI2 Clock Frame (uint: bps)
//  <i>default: 0
//!           |    CPHA = 0   |   CPHA = 1   |
//!           |               |              |
//!           |     |___      |     ___|     |
//! CPOL = 0  |     |   |     |    |   |     |
//!           |   __|   |__   |  __|   |__   |
//!           |     |         |        |     |
//!           |               |              |
//!           |---------------|--------------|
//!           |               |              |
//!           |   __|    __   |  __    |__   |
//! CPOL = 1  |     |   |     |    |   |     |
//!           |     |___|     |    |___|     |
//!           |     |         |        |     |
//!           |               |              |
#define MCU_SPI2_CLK_FRAME 0

// <o>Set SPI2 First Bit (uint: bps)
//  <i>default: 1 (0: LSB 1: MSB)
#define MCU_SPI2_FIRST_BIT 1

// <c1>Enable MCU SPI2 Rx ISR
//  <i>Enable MCU SPI2 Rx ISR
//#define ENABLE_SPI2_RX_ISR
// </c>

// <c1>Enable MCU SPI2 Tx ISR
//  <i>Enable MCU SPI2 Tx ISR
//#define ENABLE_SPI2_TX_ISR
// </c>

// <c1>Enable MSP SPI2 Driver
//  <i>Enable MSP SPI2 Driver
//#define ENABLE_MSP_SPI2_DRIVER
// </c>

//! end of the MCU SPI2 Param Config
// </h>

// <h>MCU SPI3 Param Config
//  <i>MCU SPI3 Param Config

// <o>Set SPI3 AF Port
//  <0=> PB3,PB4,PB5(default)
//  <i> (default)SCK ---> PB3    MISO ---> PB4    MOSI ---> PB5
#define MCU_SPI3_AF_PORT 0

// <o>Set SPI3 Mode (uint: bps)
//  <i>default: 0 (0: Master Mode 1:Slave Mode)
#define MCU_SPI3_MODE 0

// <o>Set SPI3 Clock (uint: bps)
//  <i>default: 3 (0: 8MHz 1:4MHz 2:2MHz 3:1MHz)
#define MCU_SPI3_CLOCK 3

// <o>Set SPI3 Clock Frame (uint: bps)
//  <i>default: 0
//!           |    CPHA = 0   |   CPHA = 1   |
//!           |               |              |
//!           |     |___      |     ___|     |
//! CPOL = 0  |     |   |     |    |   |     |
//!           |   __|   |__   |  __|   |__   |
//!           |     |         |        |     |
//!           |               |              |
//!           |---------------|--------------|
//!           |               |              |
//!           |   __|    __   |  __    |__   |
//! CPOL = 1  |     |   |     |    |   |     |
//!           |     |___|     |    |___|     |
//!           |     |         |        |     |
//!           |               |              |
#define MCU_SPI3_CLK_FRAME 0

// <o>Set SPI3 First Bit (uint: bps)
//  <i>default: 1 (0: LSB 1: MSB)
#define MCU_SPI3_FIRST_BIT 1

// <c1>Enable MCU SPI3 Rx ISR
//  <i>Enable MCU SPI3 Rx ISR
//#define ENABLE_SPI3_RX_ISR
// </c>

// <c1>Enable MCU SPI3 Tx ISR
//  <i>Enable MCU SPI3 Tx ISR
//#define ENABLE_SPI3_TX_ISR
// </c>

// <c1>Enable MSP SPI3 Driver
//  <i>Enable MSP SPI3 Driver
//#define ENABLE_MSP_SPI3_DRIVER
// </c>

//! end of the MCU SPI3 Param Config
// </h>

#if defined(ENABLE_MSP_SPI1_DRIVER) || defined(ENABLE_MSP_SPI2_DRIVER)
    || defined(ENABLE_MSP_SPI3_DRIVER)
#define ENABLE_MSP_SPI_DRIVER
#endif

//! end of the MCU SPI Param Config
// </h>

// <h>MCU WDG Param Config
//  <i>MCU WDG Param Config

// <o>Set WDG Timeout Tick
//  <i>default: 1000(unit:s)
#define MCU_WDG_TIMEOUT 1000

// <c1>Enable MSP WDG Driver
//  <i>Enable MSP WDG Driver
//#define ENABLE_MSP_WDG_DRIVER
// </c>

//! end of the MCU WDG Param Config
// </h>

// <<< end of configuration section >>>

/* Exported types ------------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** msp config file */

/**********************************END OF FILE*********************************/
