/**
 *******************************************************************************
 * @file       fw_conf.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework global config head files                              *
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
 * @defgroup framework global config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_GLOBAL_CONF_H__
#define __FRAMEWORK_GLOBAL_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Define and config ---------------------------------------------------------*/
// <<< Use Configuration Wizard in Context Menu >>>
#define USE_PALTFORM_SIMULATION     0x0000
#define USE_PALTFORM_QT             0x0001
#define USE_PALTFORM_N76E003        0x0010
#define USE_PALTFORM_NUC029LAN      0x0020
#define USE_PALTFORM_NANO103        0x0030
#define USE_PALTFORM_STM8L05x       0x0040
#define USE_PALTFORM_STM32L05x      0x0050
#define USE_PALTFORM_STM32F1xx      0x0060
#define USE_PALTFORM_STM32L4xx      0x0070
#define USE_PALTFORM_HC32L13x       0x0080
#define USE_PALTFORM_MIMXRT1052     0x0090

// <o>Select Board Support Packet
//  <0x0000=> Simulation <0x0001=> QT
//  <0x0010=> N76E003    <0x0020=> NUC029    <0x0030=> NANO103
//  <0x0040=> STM8L05x
//  <0x0050=> STM32L05x  <0x0060=> STM32F1xx <0x0070=> STM32L4xx
//  <0x0080=> HC32L13x
//  <0x0090=> MIMXRT1052
//  <i> 0x0000:Simulation 0x0001:QT
//  <i> 0x0010:N76E003    0x0020: NUC029    0x0030: NANO103
//  <i> 0x0040:STM8L05x
//  <i> 0x0050:STM32L05x  0x0060: STM32F1xx 0x0070: STM32L4xx
//  <i> 0x0080:HC32L13x
//  <i> 0x0090:MIMXRT1052
#define BOARD_PALTFORM              0x70

#ifdef SIMULATION_DEBUG
#undef  BOARD_PALTFORM
#define BOARD_PALTFORM              0
#endif

#define FRAMEWORK_USED_DISABLE      0
#define FRAMEWORK_NANO_VERSION      1
#define FRAMEWORK_FULL_VERSION      2
// <o>Select Framework Version
//  <0=> Disable
//  <1=> Nano
//  <2=> Full
//  <i>0: 禁用框架
//  <i>1: 精简版本
//  <i>2: 完整版本
#define USE_FRAMEWORK_VERSION       2

#if USE_FRAMEWORK_VERSION == 1
#define FRAMEWORK_VERSION_NANO
#elif USE_FRAMEWORK_VERSION == 2
#define FRAMEWORK_VERSION_FULL
#endif

// <o>Set Framework Event Queue Max
//  <i>Default: 16
#define FRAMEWORK_EVENT_QUEUE_MAX   32

// <o>Set Framework Message Queue Param
//  <i>Default: 8
#define FRAMEWORK_MQ_SIZE_PARAM 16

// <o>Set Framework Task Priority Max
//  <i>Default: 8
#define FRAMEWORK_TASK_PRIORITY_MAX 3

// <o>Set Framework Tick Time
//  <i>Default: 1  (unit:ms)
#define FRAMEWORK_TICK_TIME 1

// <c1>Enable Framework ProtoThread Component
//  <i>Enable Framework ProtoThread Component
#define ENABLE_FRAMEWORK_PROTOTHREAD
// </c>

// <c1>Enable Framework Real Handle
//  <i>Enable Framework Real Handle
//#define ENABLE_FRAMEWORK_TIMER_REAL
// </c>

// <h>Framework Component Configuration
// <c1>Enable Framework Component Init
//  <i>Enable Framework Component Init
#define ENABLE_FRAMEWORK_COMPONENT_INIT
// </c>

// <c1>Enable Framework Debug Component
//  <i>Enable Framework Debug Component
//#define ENABLE_FRAMEWORK_DEBUG
// </c>

// <h>Framework Console Component Config

// <c1>Enable Framework Console Component
//  <i>Enable Framework Console Component
//#define ENABLE_FRAMEWORK_CONSOLE
// </c>

// <c1>Enable Framework Console Debug
//  <i>Enable Framework Console Debug
//#define ENABLE_FRAMEWORK_CONSOLE_DEBUG
// </c>

// <o>Select Framework Console Hardware Class
//  <0=> SERIAL
//  <1=> USB
#define FW_CONSOLE_DEVICE_CLASS 0

// <o>Select Framework Console Port
//  <i> 0 (Port ID)
#define FW_CONSOLE_PORT 0

// <o>Select Framework Console Rate
//  <i> 9600
#define FW_CONSOLE_RATE 115200

// <o>Set Console Cache Size
//  <i> 128 (unit: byte)
#define FW_CONSOLE_BUFFER_MAX 128

// </h>

// <h>Framework HAL Driver Component Configuration
// <c1>Enable HAL Driver Component
//  <i>Enable HAL Driver Component
//#define ENABLE_HAL_DRIVER_COMPONENT
// </c>

// <c1>Enable HAL GPIO Driver
//  <i>Enable HAL GPIO Driver
//#define ENABLE_HAL_GPIO_DRIVER
// </c>

// <c1>Enable HAL Timer Driver
//  <i>Enable HAL Timer Driver
//#define ENABLE_HAL_TIMER_DRIVER
// </c>

// <c1>Enable HAL PWM Driver
//  <i>Enable HAL PWM Driver
//#define ENABLE_HAL_PWM_DRIVER
// </c>

// <c1>Enable HAL ADC Driver
//  <i>Enable HAL ADC Driver
//#define ENABLE_HAL_ADC_DRIVER 
// </c>

// <c1>Enable HAL SERIAL Driver
//  <i>Enable HAL SERIAL Driver
//#define ENABLE_HAL_SERIAL_DRIVER
// </c>

// <c1>Enable HAL SPI Driver
//  <i>Enable HAL SPI Driver
//#define ENABLE_HAL_SPI_DRIVER
// </c>

// <c1>Enable HAL IIC Driver
//  <i>Enable HAL IIC Driver
//#define ENABLE_HAL_IIC_DRIVER
// </c>

// <c1>Enable HAL Key Driver
//  <i>Enable HAL Key Driver
//#define ENABLE_HAL_KEY_DRIVER
// </c>

// <c1>Enable HAL Blink Driver
//  <i>Enable HAL Blink Driver
//#define ENABLE_HAL_BLINK_DRIVE
// </c>

// <c1>Enable HAL Hall Driver
//  <i>Enable HAL Hall Driver
//#define ENABLE_HAL_HALL_DRIVER
// </c>

// <c1>Enable HAL Flash Driver
//  <i>Enable HAL Flash Driver
//#define ENABLE_HAL_FLASH_DRIVER
// </c>

// <c1>Enable HAL Virtual EEPROM Driver
//  <i>Enable HAL Virtual EEPROM Driver
//#define ENABLE_HAL_VIRTUAL_EEPROM_DRIVER
// </c>

//! end of Framework HAL Driver Component Configuration
// </h>

// <c1>Enable Debug Component
//  <i>Enable Debug Component
//#define ENABLE_FRAMEWORK_DEBUG_COMPONENT
// </c>

#ifdef ENABLE_FRAMEWORK_DEBUG_COMPONENT
#include "EventRecorder.h"
#endif

//! 调试组件API
#ifdef ENABLE_FRAMEWORK_DEBUG_COMPONENT
#define DEBUG_CMPT_INIT()              {EventRecorderInitialize(EventRecordAll, 1); \
                                        EventRecorderStart();}

#define DEBUG_PUT(id, a, b)            EventRecordData(id, a, b)

#define DEBUG_PUT_DATA(id, a, b, c, d) EventRecord4(id, a, b, c, d)

#else
#define DEBUG_CMPT_INIT()
#define DEBUG_PUT(id, a, b)
#define DEBUG_PUT_DATA(id, a, b, c, d)
#endif
                                        
//! end of Framework Component Configuration
// </h>

// <<< end of configuration section >>>

/**
 *******************************************************************************
 * @brief        定义系统事件
 *******************************************************************************
 */
enum FRAMEWORK_GLOBAL_EVENT
{
    FRAMEWORK_EMPTY_EVENT = 0,
    FRAMEWORK_INIT_EVENT,
    FRAMEWORK_ENTRY_EVENT,
    FRAMEWORK_EXIT_EVENT,
    FRAMEWORK_TICK_EVENT,
    FRAMEWORK_TIMEOUT_EVENT,
    FRAMEWORK_MSG_EVENT,
    FRAMEWORK_USER_EVENT,

	FRAMEWORK_EVENT_MAX,
};

/**
*******************************************************************************
* @brief        定义调试相关宏
*******************************************************************************
*/
#ifdef SIMULATION_DEBUG
#endif

/* Exported functions --------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework global config files */

/**********************************END OF FILE*********************************/
