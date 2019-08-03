/**
 *******************************************************************************
 *                 Copyright (C) 2017 - 2019  Accumulate Team                  *
 *                                                                             *
 *      Licensed under the Apache License, Version 2.0 (the "License");        *
 *      you may not use this file except in compliance with the License.       *
 *      You may obtain a copy of the License at                                *
 *                 http://www.apache.org/licenses/LICENSE-2.0                  *
 *                                                                             *
 *   Unless required by applicable law or agreed to in writing, software       *
 *   distributed under the License is distributed on an "AS IS" BASIS,         *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *   See the License for the specific language governing permissions and       *
 *   limitations under the License.                                            *
 *******************************************************************************
 * @file       hal_def.h                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2019-03-09                                                      *
 * @brief      hal device define head file                                     *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 20190309    创建文件"hal_def.h"                                          *
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DEVICE_DEFINE_H__
#define __HAL_DEVICE_DEFINE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"
#include "fw_server.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        HAL 设备类型
 *******************************************************************************
 */
//! 定义设备类型
enum HAL_DEVICE_TYPE
{
    HAL_DEVICE_MCU = 0,
    HAL_DEVICE_PIN,
    HAL_DEVICE_ADC,
    HAL_DEVICE_TIMER,
    HAL_DEVICE_PWM,
    HAL_DEVICE_SERIAL,
    HAL_DEVICE_IIC,
    HAL_DEVICE_SPI,
    HAL_DEVICE_HALL,
    HAL_DEVICE_FLASH,
    HAL_DEVICE_VEEPROM,
    HAL_DEVICE_MAX,
};

/**
 *******************************************************************************
 * @brief        HAL 设备描述符
 *******************************************************************************
 */
//! 定义设备描述字符串
#define HAL_PIN_STR                                                       "GPIO"
#define HAL_ADC_STR                                                        "ADC"
#define HAL_TIMER_STR                                                    "TIMER"
#define HAL_PWM_STR                                                        "PWM"
#define HAL_SERIAL_STR                                                  "SERIAL"
#define HAL_IIC_STR                                                        "IIC"
#define HAL_SPI_STR                                                        "SPI"
#define HAL_HALL_STR                                                      "HALL"
#define HAL_FLASH_STR                                                    "FLASH"
#define HAL_VEEPROM_STR                                                "VEEPROM"

/**
 *******************************************************************************
 * @brief        HAL 设备状态
 *******************************************************************************
 */
enum __HAL_DEVICE_STATE
{
    HAL_DEVICE_INIT = 0,
    HAL_DEVICE_IDLE,
    HAL_DEVICE_READY,
    HAL_DEVICE_BUSY,
    HAL_DEVICE_SLEEP,
};

/**
 *******************************************************************************
 * @brief        HAL IRQ处理相关数据
 *******************************************************************************
 */
typedef void (*HAL_IrqHandle)(void *param);
typedef struct
{
    HAL_IrqHandle Handle;
    void          *Param;
}HAL_IRQ_t;

/**
 *******************************************************************************
 * @brief        HAL 通用设备操作接口
 *******************************************************************************
 */
struct HAL_DEVICE;
typedef struct
{
    uint16_t (*Init)(struct HAL_DEVICE *dev, size_t param);
    uint16_t (*Fini)(struct HAL_DEVICE *dev);

    uint16_t (*Open)(struct HAL_DEVICE *dev, uint16_t flag);
    uint16_t (*Close)(struct HAL_DEVICE *dev);
    
    uint16_t (*Write)(struct HAL_DEVICE *dev, uint16_t pos, uint8_t *buf, uint16_t len);
    uint16_t (*Read)(struct HAL_DEVICE *dev, uint16_t pos, uint8_t *buf, uint16_t len);
    
    uint16_t (*Control)(struct HAL_DEVICE *dev, uint8_t cmd, void *args);
}HAL_Interface_t;

/**
 *******************************************************************************
 * @brief        HAL 设备句柄
 *******************************************************************************
 */
typedef struct HAL_DEVICE
{
    //! 设备类型
    uint8_t Type;
    //! 设备状态
    uint8_t State;
    //! 设备标识
    uint16_t Flag;
    //! 设备链表
    FwList_t List;
    //! 设备操作接口
    HAL_Interface_t Ops;
    //! 设备名称
    char *Name;
    //! 用户数据
    void *UserData;
}HAL_Device_t;

/**
 *******************************************************************************
 * @brief        HAL Flag Encode
 *******************************************************************************
 */
#define HAL_Flag_Encode(type, flag)                          (type << 16 | flag)

/**
 *******************************************************************************
 * @brief        HAL 设备属性
 *******************************************************************************
 */
typedef struct
{
    //! 设备端口
    uint16_t Port;
    //! 设备状态
    uint16_t State;
    //! 设备标志
    uint16_t Flag;
    //! 设备事件
    uint16_t Event;
}HAL_Atrribute_t;

/**
 *******************************************************************************
 * @brief      HAL 有效位设置
 *******************************************************************************
 */
#define HAL_DEVICE_MSB                                                       (0)
#define HAL_DEVICE_LSB                                                       (1)

/**
 *******************************************************************************
 * @brief      HAL 设备操作标识
 *******************************************************************************
 */
#define HAL_READ_FLAG                                                     _bv(0)
#define HAL_WRITE_FLAG                                                    _bv(1)

/**
 *******************************************************************************
 * @brief      HAL 设备操作命令
 *******************************************************************************
 */
enum HAL_DEVICE_CMDS
{
    HAL_INIT_CMD = 0,
    HAL_FINI_CMD,
    HAL_REQUEST_CMD,
    HAL_SET_CALLBACK_CMD,
    
    HAL_SPECIAL_CMD,
};

/**
 *******************************************************************************
 * @brief      HAL 设备中断事件
 *******************************************************************************
 */
enum HAL_DEVICE_EVENT
{
    HAL_EVENT_NONE = 0,
    //! Rx indication
    HAL_EVENT_RX_IND,
    //! Rx fifo transfer done
    HAL_EVENT_RX_FIFO_DONE,
    //! Rx DMA transfer done
    HAL_EVENT_RX_DMADONE,
    //! Rx timeout
    HAL_EVENT_RX_TIMEOUT,
    //! Tx complete
    HAL_EVENT_TX_DONE,
    //! Tx fifo transfer complete
    HAL_EVENT_TX_FIFO_DONE,
    //! Tx DMA transfer done
    HAL_EVENT_TX_DMADONE,
};

/**
 *******************************************************************************
 * @brief        HAL PORT DEFINE
 *******************************************************************************
 */
enum HAL_GPIO_PORT
{
    HAL_PORT_A = 0,
    HAL_PORT_B,
    HAL_PORT_C,
    HAL_PORT_D,
    HAL_PORT_E,
    HAL_PORT_F,
    HAL_PORT_G,
    HAL_PORT_H,
    HAL_PORT_I,
    HAL_PORT_J,
    HAL_PORT_K,
    HAL_PORT_L,
    HAL_PORT_M,
    HAL_PORT_N,
                            
    HAL_PORT_MAX,
};

enum HAL_GPIO_PIN
{
    HAL_PIN_0 = 0,
    HAL_PIN_1,
    HAL_PIN_2,
    HAL_PIN_3,
    HAL_PIN_4,
    HAL_PIN_5,
    HAL_PIN_6,
    HAL_PIN_7,
    HAL_PIN_8,
    HAL_PIN_9,
    HAL_PIN_10,
    HAL_PIN_11,
    HAL_PIN_12,
    HAL_PIN_13,
    HAL_PIN_14,
    HAL_PIN_15,
    HAL_PIN_16,
    HAL_PIN_17,
    HAL_PIN_18,
    HAL_PIN_19,
    HAL_PIN_20,
    HAL_PIN_21,    
    HAL_PIN_22,
    HAL_PIN_23,
    HAL_PIN_24,
    HAL_PIN_25,
    HAL_PIN_26,
    HAL_PIN_27,   
    HAL_PIN_28,
    HAL_PIN_29,
    HAL_PIN_30,
    HAL_PIN_31,

    HAL_PIN_MAX,
};

enum HAL_PIN_MODE
{
    HAL_PIN_INPUT = 0,
    HAL_PIN_OUTPUT,
    HAL_PIN_FLOAT,
    HAL_PIN_QUASI,
    HAL_PIN_ANALOG,

    HAL_PIN_MODE_MAX,
};

enum HAL_PORT_CMD
{
    GPIO_SET_CMD = HAL_SPECIAL_CMD,
    GPIO_CLR_CMD,
    GPIO_TOGGLE_CMD,
    GPIO_INPUT_MODE_CMD,
    GPIO_OUTPUT_MODE_CMD,
    GPIO_GET_OUTPUT_CMD,
    GPIO_GET_INPUT_CMD,
};

/**
 *******************************************************************************
 * @brief        HAL GPIO PORT ID Conversion
 *******************************************************************************
 */
#define HAL_PIN_ID(port, pin)                             ((port) << 16 | (pin))
#define HAL_PORT(id)                                                ((id) >> 16)
#define HAL_PIN(id)                                        ((id) & 0x0000FFFFUL)

//! 定义引脚状态
#define HAL_PIN_INIT                                                        0x00
#define HAL_PIN_ACTIVE                                                      0x01
#define HAL_PIN_INACTIVE                                                    0x02

//! 定义引脚配置参数
#define HAL_PIN_ACTIVE_HIGH                                                 0x01
#define HAL_PIN_ACTIVE_LOW                                                  0x00
#define HAL_PIN_IS_HIGH_ACTIVE(x)        (Fw_Flag_Get((x), HAL_PIN_ACTIVE_HIGH))

/**
 *******************************************************************************
 * @brief        HAL BLINK DEFINE
 *******************************************************************************
 */
//! BLINK 状态定义
#define HAL_BLINK_INIT_STATE  0
#define HAL_BLINK_ON_STATE    1
#define HAL_BLINK_OFF_STATE   2
#define HAL_BLINK_DOING_STATE 3

//! BLINK 命令定义
#define HAL_BLINK_INIT_CMD    0
#define HAL_BLINK_ON_CMD      1
#define HAL_BLINK_OFF_CMD     2

/**
 *******************************************************************************
 * @brief        HAL ADC PORT
 *******************************************************************************
 */
enum HAL_ADC_PORT
{
    HAL_ADC_CH0,  HAL_ADC_CH1,  HAL_ADC_CH2,  HAL_ADC_CH3,
    HAL_ADC_CH4,  HAL_ADC_CH5,  HAL_ADC_CH6,  HAL_ADC_CH7,
    HAL_ADC_CH8,  HAL_ADC_CH9,  HAL_ADC_CH10, HAL_ADC_CH11,
    HAL_ADC_CH12, HAL_ADC_CH13, HAL_ADC_CH14, HAL_ADC_CH15,
    HAL_ADC_CH16, HAL_ADC_CH17, HAL_ADC_CH18, HAL_ADC_CH19,
    HAL_ADC_CH20, HAL_ADC_CH21, HAL_ADC_CH22, HAL_ADC_CH23,
    HAL_ADC_CH24, HAL_ADC_CH25, HAL_ADC_CH26, HAL_ADC_CH27,
    HAL_ADC_CH28, HAL_ADC_CH29, HAL_ADC_CH30, HAL_ADC_CH31,
    HAL_ADC_CH_MAX,
};

/**
 *******************************************************************************
 * @brief        HAL ADC CONVERT MODE
 *******************************************************************************
 */
//! ADC转换失能
#define HAL_ADC_DISABLE_CONVERT           0x00
//! ADC单次转换模式
#define HAL_ADC_SINGLE_CONVERT            0x01
//! ADC单次周期转换模式
#define HAL_ADC_SINGLE_PERIOD_CONVERT     0x02
//! ADC循环转换模式
#define HAL_ADC_CONTINUE_CONVERT          0x03

/**
 *******************************************************************************
 * @brief        HAL ADC CONVERT STATE
 *******************************************************************************
 */
#define HAL_ADC_SCAN_INIT                 0
#define HAL_ADC_SCAN_DOING                1
#define HAL_ADC_SCAN_WAIT                 2
#define HAL_ADC_SCAN_HANDLE               3
#define HAL_ADC_SCAN_END                  4

/**
 *******************************************************************************
 * @brief        HAL TIMER PORT
 *******************************************************************************
 */
enum HAL_TIMER_PORT
{
    HAL_TIMER_0,  HAL_TIMER_1,  HAL_TIMER_2,  HAL_TIMER_3,  HAL_TIMER_4,
    HAL_TIMER_5,  HAL_TIMER_6,  HAL_TIMER_7,  HAL_TIMER_8,  HAL_TIMER_9,
    HAL_TIMER_10, HAL_TIMER_11, HAL_TIMER_12, HAL_TIMER_13, HAL_TIMER_14,
    HAL_TIMER_15, HAL_TIMER_16, HAL_TIMER_17, HAL_TIMER_18, HAL_TIMER_19,
    HAL_TIMER_20, HAL_TIMER_21, HAL_TIMER_22, HAL_TIMER_23, HAL_TIMER_24,
    HAL_TIMER_25, HAL_TIMER_26, HAL_TIMER_27, HAL_TIMER_28, HAL_TIMER_29,
    HAL_TIMER_30, HAL_TIMER_31, HAL_TIMER_32, HAL_TIMER_33, HAL_TIMER_34,
    HAL_TIMER_35, HAL_TIMER_36, HAL_TIMER_37, HAL_TIMER_38, HAL_TIMER_39,
    HAL_TIMER_40, HAL_TIMER_41, HAL_TIMER_42, HAL_TIMER_43, HAL_TIMER_44,
    HAL_TIMER_45, HAL_TIMER_46, HAL_TIMER_47, HAL_TIMER_48, HAL_TIMER_49,
    HAL_TIMER_MAX,
};

/**
 *******************************************************************************
 * @brief        HAL TIMER RUN MODE
 *******************************************************************************
 */
#define HAL_TIMER_ONE_SHOT_MODE                                                0
#define HAL_TIMER_PERIOD_MODE                                                  1

/**
 *******************************************************************************
 * @brief        HAL TIMER TICK MODE
 *******************************************************************************
 */
#define HAL_TIMER_CNT_UP                                                       0
#define HAL_TIMER_CNT_DOWN                                                     1

/**
 *******************************************************************************
 * @brief        HAL TIMER TICK UNIT
 *******************************************************************************
 */
#define HAL_TIMER_UNIT_US                                                      0
#define HAL_TIMER_UNIT_MS                                                      1
#define HAL_TIMER_UNIT_100MS                                                   2
#define HAL_TIMER_UNIT_SEC                                                     3

/**
 *******************************************************************************
 * @brief        HAL PWM PORT
 *******************************************************************************
 */
enum HAL_PWM_PORT
{
    HAL_PWM_CH0,  HAL_PWM_CH1,  HAL_PWM_CH2,  HAL_PWM_CH3,
    HAL_PWM_CH4,  HAL_PWM_CH5,  HAL_PWM_CH6,  HAL_PWM_CH7,
    HAL_PWM_CH8,  HAL_PWM_CH9,  HAL_PWM_CH10, HAL_PWM_CH11,
    HAL_PWM_CH12, HAL_PWM_CH13, HAL_PWM_CH14, HAL_PWM_CH15,
    HAL_PWM_CH16, HAL_PWM_CH17, HAL_PWM_CH18, HAL_PWM_CH19,
    HAL_PWM_CH20, HAL_PWM_CH21, HAL_PWM_CH22, HAL_PWM_CH23,
    HAL_PWM_CH24, HAL_PWM_CH25, HAL_PWM_CH26, HAL_PWM_CH27,
    HAL_PWM_CH28, HAL_PWM_CH29, HAL_PWM_CH30, HAL_PWM_CH31,
    
    HAL_PWM_CH_MAX,
};

enum HAL_PWM_CMD
{
    HAL_PWM_CHANNEL_NORMAL = HAL_SPECIAL_CMD,
    HAL_PWM_CHANNEL_NEGATION,
};

/**
 *******************************************************************************
 * @brief        HAL PWM OPTION
 *******************************************************************************
 */
#define HAL_PWM_READ                                                           0
#define HAL_PWM_WRITE                                                          1

/**
 *******************************************************************************
 * @brief        HAL SPI PORT
 *******************************************************************************
 */
enum HAL_SPI_PORT
{
    HAL_SPI_0 = 0,
    HAL_SPI_1,
    HAL_SPI_2,
    HAL_SPI_3,
    HAL_SPI_4,
    HAL_SPI_5,
    
    HAL_SPI_END,
};

/**
 *******************************************************************************
 * @brief      定义 SPI 模式
 *******************************************************************************
 */
//! CPOL = 0, CPHA = 0
#define HAL_SPI_MODE_0        0
//! CPOL = 0, CPHA = 1
#define HAL_SPI_MODE_1        1
//! CPOL = 1, CPHA = 0
#define HAL_SPI_MODE_2        2
//! CPOL = 1, CPHA = 1
#define HAL_SPI_MODE_3        3

/**
 *******************************************************************************
 * @brief      定义 SPI 数据长度
 *******************************************************************************
 */
#define HAL_SPI_DATA_LEN_8    8
#define HAL_SPI_DATA_LEN_16  16
#define HAL_SPI_DATA_LEN_32  32

/**
 *******************************************************************************
 * @brief      定义 SPI 传输速度
 *******************************************************************************
 */
#define HAL_SPI_SPEED_10K     10000UL
#define HAL_SPI_SPEED_20K     20000UL
#define HAL_SPI_SPEED_50K     50000UL
#define HAL_SPI_SPEED_100K    100000UL
#define HAL_SPI_SPEED_200K    200000UL
#define HAL_SPI_SPEED_500K    500000UL
#define HAL_SPI_SPEED_1M      1000000UL
#define HAL_SPI_SPEED_2M      2000000UL
#define HAL_SPI_SPEED_5M      5000000UL
#define HAL_SPI_SPEED_10M     10000000UL
#define HAL_SPI_SPEED_20M     20000000UL

/**
 *******************************************************************************
 * @brief      SPI 配置选项
 *******************************************************************************
 */
#define HAL_SPI_EN_TX                 0x0001
#define HAL_SPI_EN_TX_ISR             0x0002
#define HAL_SPI_EN_TX_DMA             0x0004
#define HAL_SPI_EN_TX_FIFO            0x0008
#define HAL_SPI_EN_TX_MSG             0x0010
#define HAL_SPI_EN_TX_CALLBACK        0x0020

#define HAL_SPI_EN_RX                 0x0100
#define HAL_SPI_EN_RX_ISR             0x0200
#define HAL_SPI_EN_RX_DMA             0x0400
#define HAL_SPI_EN_RX_FIFO            0x0800
#define HAL_SPI_EN_RX_MSG             0x1000
#define HAL_SPI_EN_RX_CALLBACK        0x2000

/**
 *******************************************************************************
 * @brief      SPI 标识定义
 *******************************************************************************
 */
#define HAL_SPI_TAKE_FLAG             0x0001


/**
 *******************************************************************************
 * @brief        HAL SERIAL PORT
 *******************************************************************************
 */
enum HAL_SERIAL_PORT
{
    HAL_SERIAL_0,
    HAL_SERIAL_1,
    HAL_SERIAL_2,
    HAL_SERIAL_3,
    HAL_SERIAL_4,
    HAL_SERIAL_5,
    HAL_SERIAL_6,
    HAL_SERIAL_7,
    HAL_SERIAL_8,
    
    HAL_SERIAL_MAX,
};

/**
 *******************************************************************************
 * @brief      定义 SERIAL 波特率配置参数
 *******************************************************************************
 */
#define HAL_SERIAL_BAUD_2400              2400
#define HAL_SERIAL_BAUD_4800              4800
#define HAL_SERIAL_BAUD_9600              9600
#define HAL_SERIAL_BAUD_19200             19200
#define HAL_SERIAL_BAUD_38400             38400
#define HAL_SERIAL_BAUD_57600             57600
#define HAL_SERIAL_BAUD_115200            115200
#define HAL_SERIAL_BAUD_230400            230400
#define HAL_SERIAL_BAUD_460800            460800
#define HAL_SERIAL_BAUD_921600            921600
#define HAL_SERIAL_BAUD_2000000           2000000
#define HAL_SERIAL_BAUD_3000000           3000000

/**
 *******************************************************************************
 * @brief      定义 SERIAL 数据位配置参数
 *******************************************************************************
 */
#define HAL_SERIAL_DATA_BITS_5            5
#define HAL_SERIAL_DATA_BITS_6            6
#define HAL_SERIAL_DATA_BITS_7            7
#define HAL_SERIAL_DATA_BITS_8            8
#define HAL_SERIAL_DATA_BITS_9            9

/**
 *******************************************************************************
 * @brief      定义 SERIAL 停止位配置参数
 *******************************************************************************
 */
#define HAL_SERIAL_STOP_BITS_1            1
#define HAL_SERIAL_STOP_BITS_2            2
#define HAL_SERIAL_STOP_BITS_3            3
#define HAL_SERIAL_STOP_BITS_4            4

/**
 *******************************************************************************
 * @brief      定义 SERIAL 校验位配置参数
 *******************************************************************************
 */
#define HAL_SERIAL_PARITY_NONE            0
#define HAL_SERIAL_PARITY_ODD             1                           //! 奇校验
#define HAL_SERIAL_PARITY_EVEN            2                           //! 偶校验

/**
 *******************************************************************************
 * @brief      定义 SERIAL 编码方式配置参数
 *******************************************************************************
 */
#define HAL_SERIAL_NRZ_NORMAL             0       /* Non Return to Zero : normal mode */
#define HAL_SERIAL_NRZ_INVERTED           1       /* Non Return to Zero : inverted mode */

/**
 *******************************************************************************
 * @brief      SERIAL 发送缓存区长度
 *******************************************************************************
 */
#define HAL_SERIAL_CACHE_SIZE            64

/**
 *******************************************************************************
 * @brief      SERIAL 事件定义
 *******************************************************************************
 */
//! 硬件事件
#define HAL_SERIAL_EVENT_RX_IND          0x01       /* Rx indication */
#define HAL_SERIAL_EVENT_TX_DONE         0x02       /* Tx complete   */
#define HAL_SERIAL_EVENT_RX_FIFO_DONE    0x03       /* Rx fifo transfer done */
#define HAL_SERIAL_EVENT_TX_FIFO_DONE    0x04       /* Tx fifo transfer complete */
#define HAL_SERIAL_EVENT_RX_DMADONE      0x05       /* Rx DMA transfer done */
#define HAL_SERIAL_EVENT_TX_DMADONE      0x06       /* Tx DMA transfer done */
#define HAL_SERIAL_EVENT_RX_TIMEOUT      0x07       /* Rx timeout    */

//! 组件事件
#define HAL_SERIAL_TX_DONE               0x08
#define HAL_SERIAL_TX_START              0x09
#define HAL_SERIAL_TX_TIMEOUT            0x0A
#define HAL_SERIAL_RX_ONCE               0x0B
#define HAL_SERIAL_RX_DONE               0x0C
#define HAL_SERIAL_RX_TIMEOUT            0x0D
#define HAL_SERIAL_RX_OVERFLOW           0x0E

/**
 *******************************************************************************
 * @brief      SERIAL 传输方向定义
 *******************************************************************************
 */
#define HAL_SERIAL_DIR_TX                0x00
#define HAL_SERIAL_DIR_RX                0x01
    
/**
 *******************************************************************************
 * @brief      SERIAL 时间参数
 *******************************************************************************
 */
#define HAL_SERIAL_RX_TICK              10

/**
 *******************************************************************************
 * @brief      SERIAL 工作标志位
 *******************************************************************************
 */
#define HAL_SERIAL_TRANSFER_ISR                                           0x0001
#define HAL_SERIAL_TRANSFER_FIFO                                          0x0002
#define HAL_SERIAL_TRANSFER_DMA                                           0x0004

/**
 *******************************************************************************
 * @brief        HAL DMA PORT
 *******************************************************************************
 */
enum HAL_DMA_PORT
{
    HAL_DMA_CH0,  HAL_DMA_CH1,  HAL_DMA_CH2,  HAL_DMA_CH3,
    HAL_DMA_CH4,  HAL_DMA_CH5,  HAL_DMA_CH6,  HAL_DMA_CH7,
    HAL_DMA_CH8,  HAL_DMA_CH9,  HAL_DMA_CH10, HAL_DMA_CH11,
    HAL_DMA_CH12, HAL_DMA_CH13, HAL_DMA_CH14, HAL_DMA_CH15,
    HAL_DMA_CH16, HAL_DMA_CH17, HAL_DMA_CH18, HAL_DMA_CH19,
    HAL_DMA_CH20, HAL_DMA_CH21, HAL_DMA_CH22, HAL_DMA_CH23,
    HAL_DMA_CH24, HAL_DMA_CH25, HAL_DMA_CH26, HAL_DMA_CH27,
    HAL_DMA_CH28, HAL_DMA_CH29, HAL_DMA_CH30, HAL_DMA_CH31,
    
    HAL_DMA_CH_MAX,
};

enum HAL_DMA_CMD
{
    HAL_DMA_CHANNEL_NORMAL = HAL_SPECIAL_CMD,
    HAL_DMA_CHANNEL_NEGATION,
};

/**
 *******************************************************************************
 * @brief        HAL IIC PORT
 *******************************************************************************
 */
enum HAL_IIC_PORT
{
    HAL_IIC_0,
    HAL_IIC_1,
    HAL_IIC_2,
    
    HAL_IIC_MAX,
};

/**
 *******************************************************************************
 * @brief        HAL DMA OPTION
 *******************************************************************************
 */
#define HAL_DMA_READ                                                           0
#define HAL_DMA_WRITE                                                          1

/**
 *******************************************************************************
 * @brief        HAL DMA EVENT
 *******************************************************************************
 */
#define HAL_DMA_EVENT_TX_DONE                                                  2
#define HAL_DMA_EVENT_RX_DONE                                                  3

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      HAL 设备消息
 *******************************************************************************
 */
#define HAL_DEVICE_NORMAL_MSG 0
#define HAL_DEVICE_KEY_MSG    1
#define HAL_DEVICE_BLINK_MSG  2
#define HAL_DEVICE_UART_MSG   3

typedef union
{
    //! 基本消息
    struct
    {
        uint16_t MsgType;
        uint16_t Event;
        
        union
        {
            void     *Param;
            uint32_t Extend;
        };
    };
    
    //! 按键消息
    struct
    {
        uint16_t : 16;
        uint16_t KeyState;
        uint16_t KeyValue;
        uint16_t KeyTick;
    };
}HAL_MSG_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        HAL定时器操作API
 *******************************************************************************
 */
#define HAL_CMD_Nop(t)
#define HAL_Delay_Us(t)
#define HAL_Delay_Ms(t)

//! HAL 定时器操作接口
//! 驱动底层使用此接口
#define HAL_GenTimer_Start(tim, tick) _st((tim) = (tick);)
#define HAL_GenTimer_Stop(tim)        _st((tim) = 0;)
#define HAL_GenTimer_Handle(tim)      _st(if(tim > 0)        \
                                         {                  \
                                             if(!--tim)     \
                                             {              \
                                                 tim = -1;  \
                                             }              \
                                         })
#define HAL_GenTimer_Done(tim)       (((tim) == -1) ? ((tim) = 0, 1) : (0))

/**
 *******************************************************************************
 * @brief        HAL事件操作API
 *******************************************************************************
 */
#define HAL_Evt_Set(p, e)                         _set_bit((p), (e))
#define HAL_Evt_Clr(p, e)                         _clr_bit((p), (e))
#define HAL_Evt_Get(p, e)                         _read_bit((p), (e))
 
/**
 *******************************************************************************
 * @brief        HAL Flag操作API
 *******************************************************************************
 */
#define HAL_Flag_Set(p, e)                        _set_reg((p), (e))
#define HAL_Flag_Clr(p, e)                        _clr_reg((p), (e))
#define HAL_Flag_Get(p, e)                        _get_reg((p), (e))

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
