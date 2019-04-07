/**
 *******************************************************************************
 * @file       msp_mimxrt1052.h                                                *
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
#ifndef __MIMXRT1052_SUPPOR_PACKET_H__
#define __MIMXRT1052_SUPPOR_PACKET_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"
#include "msp_conf.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "hal_device.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        硬件信息定义
 *******************************************************************************
 */
/*! @brief The board name */
#define BOARD_NAME                    "YH i.MX RT1052 Board"

/* 调试串口定义的信息 */
#define BOARD_DEBUG_UART_TYPE         DEBUG_CONSOLE_DEVICE_TYPE_LPUART
#define BOARD_DEBUG_UART_BASEADDR     (uint32_t) LPUART1
#define BOARD_DEBUG_UART_INSTANCE     1U

#define BOARD_DEBUG_UART_CLK_FREQ     BOARD_DebugConsoleSrcFreq()

#define BOARD_UART_IRQ                LPUART1_IRQn
#define BOARD_UART_IRQ_HANDLER        LPUART1_IRQHandler

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE     (115200U)
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/*! @brief FLASH空间大小 */
#define BOARD_FLASH_SIZE    (0x2000000U)

/**
 *******************************************************************************
 * @brief        时钟频率定义
 *******************************************************************************
 */
#define BOARD_XTAL0_CLK_HZ                         24000000U  /*!< Board xtal0 frequency in Hz */
#define BOARD_XTAL32K_CLK_HZ                          32768U  /*!< Board xtal32k frequency in Hz */
#define BOARD_BOOTCLOCKRUN_CORE_CLOCK             600000000U  /*!< Core clock frequency: 600000000Hz */

/**
 *******************************************************************************
 * @brief        硬件中断操作
 *******************************************************************************
 */
#define MSP_Enable_Interrupt()  _st(__enable_irq();)
#define MSP_Disable_Interrupt() _st(__disable_irq();)

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
//! Arm PLL set for BOARD_BootClockRUN configuration.
extern const clock_arm_pll_config_t g_armPllConfig_BOARD_BootClockRUN;
//!Usb1 PLL set for BOARD_BootClockRUN configuration.
extern const clock_usb_pll_config_t g_usb1PllConfig_BOARD_BootClockRUN;
//!Sys PLL for BOARD_BootClockRUN configuration.
extern const clock_sys_pll_config_t g_sysPllConfig_BOARD_BootClockRUN;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET GPIO COMPONENT API
 *******************************************************************************
 */
extern void MSP_GPIO_Init(void);

/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET CORE COMPONENT API
 *******************************************************************************
 */
extern int  MSP_Init(void);
extern void MSP_Reboot(void);
extern void MSP_Delay_Us(uint16_t timeout);
extern void MSP_Delay_Ms(uint16_t timeout);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
