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
 * @file       MCU_def.h                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2019-04-17                                                      *
 * @brief      MCU device define head file                                     *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 20190417    创建文件"MCU_def.h"                                          *
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MCU_DEVICE_DEFINE_H__
#define __MCU_DEVICE_DEFINE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        MCU Pin Port
 *******************************************************************************
 */
//! 定义MCU端口号
enum MCU_GPIO_PORT
{
    MCU_PORT_A = 0,
    MCU_PORT_B,
    MCU_PORT_C,
    MCU_PORT_D,
    MCU_PORT_E,
    MCU_PORT_F,
    MCU_PORT_G,
    MCU_PORT_H,
    MCU_PORT_I,
    MCU_PORT_J,
    MCU_PORT_K,
    MCU_PORT_L,
    MCU_PORT_M,
    MCU_PORT_N,

    MCU_PORT_MAX,
};

//! 定义MCU引脚号
enum MCU_GPIO_PIN
{
    MCU_PIN_0 = 0,
    MCU_PIN_1,
    MCU_PIN_2,
    MCU_PIN_3,
    MCU_PIN_4,
    MCU_PIN_5,
    MCU_PIN_6,
    MCU_PIN_7,
    MCU_PIN_8,
    MCU_PIN_9,
    MCU_PIN_10,
    MCU_PIN_11,
    MCU_PIN_12,
    MCU_PIN_13,
    MCU_PIN_14,
    MCU_PIN_15,
    MCU_PIN_16,
    MCU_PIN_17,
    MCU_PIN_18,
    MCU_PIN_19,
    MCU_PIN_20,
    MCU_PIN_21,
    MCU_PIN_22,
    MCU_PIN_23,
    MCU_PIN_24,
    MCU_PIN_25,
    MCU_PIN_26,
    MCU_PIN_27,
    MCU_PIN_28,
    MCU_PIN_29,
    MCU_PIN_30,
    MCU_PIN_31,

    MCU_PIN_MAX,
};

//! 定义MCU模式
enum MCU_PIN_MODE
{
    MCU_PIN_INPUT = 0,
    MCU_PIN_OUTPUT,
    MCU_PIN_FLOAT,
    MCU_PIN_QUASI,
    MCU_PIN_ANALOG,

    MCU_PIN_MODE_MAX,
};

//! 定义引脚状态
#define MCU_PIN_INIT                                                        0x00
#define MCU_PIN_ACTIVE                                                      0x01
#define MCU_PIN_INACTIVE                                                    0x02

//! 定义引脚配置参数
#define MCU_PIN_ACTIVE_HIGH                                                 0x01
#define MCU_PIN_ACTIVE_LOW                                                  0x00
#define MCU_PIN_IS_HIGH_ACTIVE(x)        (Fw_Flag_Get((x), MCU_PIN_ACTIVE_HIGH))

/**
 *******************************************************************************
 * @brief        MCU ADC PORT
 *******************************************************************************
 */
enum MCU_ADC_PORT
{
    MCU_ADC_CH0,  MCU_ADC_CH1,  MCU_ADC_CH2,  MCU_ADC_CH3,
    MCU_ADC_CH4,  MCU_ADC_CH5,  MCU_ADC_CH6,  MCU_ADC_CH7,
    MCU_ADC_CH8,  MCU_ADC_CH9,  MCU_ADC_CH10, MCU_ADC_CH11,
    MCU_ADC_CH12, MCU_ADC_CH13, MCU_ADC_CH14, MCU_ADC_CH15,
    MCU_ADC_CH16, MCU_ADC_CH17, MCU_ADC_CH18, MCU_ADC_CH19,
    MCU_ADC_CH20, MCU_ADC_CH21, MCU_ADC_CH22, MCU_ADC_CH23,
    MCU_ADC_CH24, MCU_ADC_CH25, MCU_ADC_CH26, MCU_ADC_CH27,
    MCU_ADC_CH28, MCU_ADC_CH29, MCU_ADC_CH30, MCU_ADC_CH31,

    MCU_ADC_CH_MAX,
};

//! MCU ADC CONVERT MODE
//! ADC转换失能
#define MCU_ADC_DISABLE_CONVERT                                             0x00
//! ADC单次转换模式                                                            
#define MCU_ADC_SINGLE_CONVERT                                              0x01
//! ADC单次周期转换模式                                                        
#define MCU_ADC_SINGLE_PERIOD_CONVERT                                       0x02
//! ADC循环转换模式                                                            
#define MCU_ADC_CONTINUE_CONVERT                                            0x03
//! MCU ADC CONVERT STATE                                                      
#define MCU_ADC_SCAN_INIT                                                      0
#define MCU_ADC_SCAN_DOING                                                     1
#define MCU_ADC_SCAN_WAIT                                                      2
#define MCU_ADC_SCAN_HANDLE                                                    3
#define MCU_ADC_SCAN_END                                                       4

/**
 *******************************************************************************
 * @brief        MCU TIMER PORT
 *******************************************************************************
 */
enum MCU_TIMER_PORT
{
    MCU_TIMER_0,  MCU_TIMER_1,  MCU_TIMER_2,  MCU_TIMER_3,  MCU_TIMER_4,
    MCU_TIMER_5,  MCU_TIMER_6,  MCU_TIMER_7,  MCU_TIMER_8,  MCU_TIMER_9,
    MCU_TIMER_10, MCU_TIMER_11, MCU_TIMER_12, MCU_TIMER_13, MCU_TIMER_14,
    MCU_TIMER_15, MCU_TIMER_16, MCU_TIMER_17, MCU_TIMER_18, MCU_TIMER_19,
    MCU_TIMER_20, MCU_TIMER_21, MCU_TIMER_22, MCU_TIMER_23, MCU_TIMER_24,
    MCU_TIMER_25, MCU_TIMER_26, MCU_TIMER_27, MCU_TIMER_28, MCU_TIMER_29,
    MCU_TIMER_30, MCU_TIMER_31, MCU_TIMER_32, MCU_TIMER_33, MCU_TIMER_34,
    MCU_TIMER_35, MCU_TIMER_36, MCU_TIMER_37, MCU_TIMER_38, MCU_TIMER_39,
    MCU_TIMER_40, MCU_TIMER_41, MCU_TIMER_42, MCU_TIMER_43, MCU_TIMER_44,
    MCU_TIMER_45, MCU_TIMER_46, MCU_TIMER_47, MCU_TIMER_48, MCU_TIMER_49,
    MCU_TIMER_MAX,
};

//! MCU TIMER RUN MODE
#define MCU_TIMER_ONE_SHOT_MODE                                                0
#define MCU_TIMER_PERIOD_MODE                                                  1
//! MCU TIMER TICK MODE
#define MCU_TIMER_CNT_UP                                                       0
#define MCU_TIMER_CNT_DOWN                                                     1
//! MCU TIMER TICK UNIT
#define MCU_TIMER_UNIT_US                                                      0
#define MCU_TIMER_UNIT_MS                                                      1
#define MCU_TIMER_UNIT_100MS                                                   2
#define MCU_TIMER_UNIT_SEC                                                     3
//! MCU TIMER CALLBACK
typedef void (*MCU_TIM_Callback)(void *param);
typedef struct
{
    MCU_TIM_Callback Callback;
    void *Param;
}MCU_TIM_Callback_t;

/**
 *******************************************************************************
 * @brief        MCU PWM PORT
 *******************************************************************************
 */
enum MCU_PWM_PORT
{
    MCU_PWM_CH0,  MCU_PWM_CH1,  MCU_PWM_CH2,  MCU_PWM_CH3,
    MCU_PWM_CH4,  MCU_PWM_CH5,  MCU_PWM_CH6,  MCU_PWM_CH7,
    MCU_PWM_CH8,  MCU_PWM_CH9,  MCU_PWM_CH10, MCU_PWM_CH11,
    MCU_PWM_CH12, MCU_PWM_CH13, MCU_PWM_CH14, MCU_PWM_CH15,
    MCU_PWM_CH16, MCU_PWM_CH17, MCU_PWM_CH18, MCU_PWM_CH19,
    MCU_PWM_CH20, MCU_PWM_CH21, MCU_PWM_CH22, MCU_PWM_CH23,
    MCU_PWM_CH24, MCU_PWM_CH25, MCU_PWM_CH26, MCU_PWM_CH27,
    MCU_PWM_CH28, MCU_PWM_CH29, MCU_PWM_CH30, MCU_PWM_CH31,
    
    MCU_PWM_CH_MAX,
};

enum MCU_PWM_CHANNEL
{
    MCU_PWM_CHANNEL_NORMAL,
    MCU_PWM_CHANNEL_NEGATION,
};

#define MCU_PWM_READ                                                           0
#define MCU_PWM_WRITE                                                          1

/**
 *******************************************************************************
 * @brief        MCU SERIAL PORT
 *******************************************************************************
 */
enum MCU_SERIAL_PORT
{
    MCU_SERIAL_0,
    MCU_SERIAL_1,
    MCU_SERIAL_2,
    MCU_SERIAL_3,
    MCU_SERIAL_4,
    MCU_SERIAL_5,
    MCU_SERIAL_6,
    MCU_SERIAL_7,
    MCU_SERIAL_8,
    
    MCU_SERIAL_MAX,
};
//! SERIAL 波特率
#define MCU_SERIAL_BAUD_2400                                                2400
#define MCU_SERIAL_BAUD_4800                                                4800
#define MCU_SERIAL_BAUD_9600                                                9600
#define MCU_SERIAL_BAUD_19200                                              19200
#define MCU_SERIAL_BAUD_38400                                              38400
#define MCU_SERIAL_BAUD_57600                                              57600
#define MCU_SERIAL_BAUD_115200                                            115200
#define MCU_SERIAL_BAUD_230400                                            230400
#define MCU_SERIAL_BAUD_460800                                            460800
#define MCU_SERIAL_BAUD_921600                                            921600
#define MCU_SERIAL_BAUD_2000000                                          2000000
#define MCU_SERIAL_BAUD_3000000                                          3000000
//! SERIAL 数据位
#define MCU_SERIAL_DATA_BITS_5                                                 5
#define MCU_SERIAL_DATA_BITS_6                                                 6
#define MCU_SERIAL_DATA_BITS_7                                                 7
#define MCU_SERIAL_DATA_BITS_8                                                 8
#define MCU_SERIAL_DATA_BITS_9                                                 9
//! SERIAL 停止位                                                              
#define MCU_SERIAL_STOP_BITS_1                                                 1
#define MCU_SERIAL_STOP_BITS_1_5                                               2
#define MCU_SERIAL_STOP_BITS_2                                                 3
//! SERIAL 校验位                                                              
#define MCU_SERIAL_PARITY_NONE                                                 0
#define MCU_SERIAL_PARITY_ODD                                                  1                           //! 奇校验
#define MCU_SERIAL_PARITY_EVEN                                                 2                           //! 偶校验
//! SERIAL 编码方式配置参数                                                    
#define MCU_SERIAL_NRZ_NORMAL                                                  0       /* Non Return to Zero : normal mode */
#define MCU_SERIAL_NRZ_INVERTED                                                1       /* Non Return to Zero : inverted mode */
//! SERIAL 发送缓存区长度                                                     
#define MCU_SERIAL_CACHE_SIZE                                                 64
//! SERIAL 硬件事件
#define MCU_SERIAL_EVENT_RX_IND                                             0x01       /* Rx indication */
#define MCU_SERIAL_EVENT_TX_DONE                                            0x02       /* Tx complete   */
#define MCU_SERIAL_EVENT_RX_FIFO_DONE                                       0x03       /* Rx fifo transfer done */
#define MCU_SERIAL_EVENT_TX_FIFO_DONE                                       0x04       /* Tx fifo transfer complete */
#define MCU_SERIAL_EVENT_RX_DMADONE                                         0x05       /* Rx DMA transfer done */
#define MCU_SERIAL_EVENT_TX_DMADONE                                         0x06       /* Tx DMA transfer done */
#define MCU_SERIAL_EVENT_RX_TIMEOUT                                         0x07       /* Rx timeout    */
//! SERIAL 组件事件                                                         
#define MCU_SERIAL_TX_DONE                                                  0x08
#define MCU_SERIAL_TX_START                                                 0x09
#define MCU_SERIAL_TX_TIMEOUT                                               0x0A
#define MCU_SERIAL_RX_ONCE                                                  0x0B
#define MCU_SERIAL_RX_DONE                                                  0x0C
#define MCU_SERIAL_RX_TIMEOUT                                               0x0D
#define MCU_SERIAL_RX_OVERFLOW                                              0x0E
//! SERIAL 传输方向定义                                                   
#define MCU_SERIAL_DIR_TX                                                   0x00
#define MCU_SERIAL_DIR_RX                                                   0x01
//! SERIAL 时间参数                                                       
#define MCU_SERIAL_RX_TICK                                                    10
//! SERIAL 工作标志位                                                     
#define MCU_SERIAL_TRANSFER_ISR                                           0x0001
#define MCU_SERIAL_TRANSFER_FIFO                                          0x0002
#define MCU_SERIAL_TRANSFER_DMA                                           0x0004

/**
 *******************************************************************************
 * @brief        MCU SPI PORT
 *******************************************************************************
 */
enum MCU_SPI_PORT
{
    MCU_SPI_0 = 0,
    MCU_SPI_1,
    MCU_SPI_2,
    MCU_SPI_3,
    MCU_SPI_4,
    MCU_SPI_5,
    
    MCU_SPI_END,
};

//! SPI 模式
//! CPOL = 0, CPHA = 0
#define MCU_SPI_MODE_0                                                         0
//! CPOL = 0, CPHA = 1                                                        
#define MCU_SPI_MODE_1                                                         1
//! CPOL = 1, CPHA = 0                                                        
#define MCU_SPI_MODE_2                                                         2
//! CPOL = 1, CPHA = 1                                                        
#define MCU_SPI_MODE_3                                                         3
//! SPI 数据长度                                                              
#define MCU_SPI_DATA_LEN_8                                                     8
#define MCU_SPI_DATA_LEN_16                                                   16
#define MCU_SPI_DATA_LEN_32                                                   32
//! SPI 传输速度
#define MCU_SPI_SPEED_10K                                                10000UL
#define MCU_SPI_SPEED_20K                                                20000UL
#define MCU_SPI_SPEED_50K                                                50000UL
#define MCU_SPI_SPEED_100K                                              100000UL
#define MCU_SPI_SPEED_200K                                              200000UL
#define MCU_SPI_SPEED_500K                                              500000UL
#define MCU_SPI_SPEED_1M                                               1000000UL
#define MCU_SPI_SPEED_2M                                               2000000UL
#define MCU_SPI_SPEED_5M                                               5000000UL
#define MCU_SPI_SPEED_10M                                             10000000UL
#define MCU_SPI_SPEED_20M                                             20000000UL
//! SPI 配置选项                                                      
#define MCU_SPI_EN_TX                                                     0x0001
#define MCU_SPI_EN_TX_ISR                                                 0x0002
#define MCU_SPI_EN_TX_DMA                                                 0x0004
#define MCU_SPI_EN_TX_FIFO                                                0x0008
#define MCU_SPI_EN_TX_MSG                                                 0x0010
#define MCU_SPI_EN_TX_CALLBACK                                            0x0020
#define MCU_SPI_EN_RX                                                     0x0100
#define MCU_SPI_EN_RX_ISR                                                 0x0200
#define MCU_SPI_EN_RX_DMA                                                 0x0400
#define MCU_SPI_EN_RX_FIFO                                                0x0800
#define MCU_SPI_EN_RX_MSG                                                 0x1000
#define MCU_SPI_EN_RX_CALLBACK                                            0x2000
//! SPI 配置选项                                                      
#define MCU_SPI_TAKE_FLAG                                                 0x0001

/**
 *******************************************************************************
 * @brief        MCU IIC PORT
 *******************************************************************************
 */
enum MCU_IIC_PORT
{
    MCU_IIC_0,
    MCU_IIC_1,
    MCU_IIC_2,
    
    MCU_IIC_MAX,
};

/**
 *******************************************************************************
 * @brief        MCU DMA PORT
 *******************************************************************************
 */
enum MCU_DMA_PORT
{
    MCU_DMA_CH0,  MCU_DMA_CH1,  MCU_DMA_CH2,  MCU_DMA_CH3,
    MCU_DMA_CH4,  MCU_DMA_CH5,  MCU_DMA_CH6,  MCU_DMA_CH7,
    MCU_DMA_CH8,  MCU_DMA_CH9,  MCU_DMA_CH10, MCU_DMA_CH11,
    MCU_DMA_CH12, MCU_DMA_CH13, MCU_DMA_CH14, MCU_DMA_CH15,
    MCU_DMA_CH16, MCU_DMA_CH17, MCU_DMA_CH18, MCU_DMA_CH19,
    MCU_DMA_CH20, MCU_DMA_CH21, MCU_DMA_CH22, MCU_DMA_CH23,
    MCU_DMA_CH24, MCU_DMA_CH25, MCU_DMA_CH26, MCU_DMA_CH27,
    MCU_DMA_CH28, MCU_DMA_CH29, MCU_DMA_CH30, MCU_DMA_CH31,
    
    MCU_DMA_CH_MAX,
};

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
