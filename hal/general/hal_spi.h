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
 * @file       hal_spi.h                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-06-28                                                      *
 * @brief      hal spi driver component head file                              *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 2018-06-28 从“hal_device.h”分离出SPI驱动                                 *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DRIVER_SPI_H__
#define __HAL_DRIVER_SPI_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"

/* Exported macro ------------------------------------------------------------*/
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

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        HAL SPI Config
 *******************************************************************************
 */
typedef struct
{
    struct
    {
        uint32_t Port         : 8;
        uint32_t DataWidth    : 8;
        uint32_t Mode         : 3;
        uint32_t FirstBit     : 1;
        uint32_t Master       : 1;
        uint32_t TransferMode : 1;

        uint32_t Speed;
    }Atrribute;
    
    struct
    {
        uint16_t EnTx         : 1;
        uint16_t EnTxIsr      : 1;
        uint16_t EnTxDma      : 1;
        uint16_t EnTxFifo     : 1;
        uint16_t EnTxMsg      : 1;
        uint16_t EnTxCallback : 1;
        uint16_t : 2;
        uint16_t EnRx         : 1;
        uint16_t EnRxIsr      : 1;
        uint16_t EnRxDma      : 1;
        uint16_t EnRxFifo     : 1;
        uint16_t EnRxMsg      : 1;
        uint16_t EnRxCallback : 1;
        uint16_t : 2;
    }Flag;
}HAL_SPI_Config_t;

/**
 *******************************************************************************
 * @brief        HAL SPI Message
 *******************************************************************************
 */
typedef struct __SPI_MESSAGE
{
    struct __SPI_MESSAGE *Next;
    
    uint8_t       *SendBuf;
    uint8_t       *RecvBuf;
    uint16_t       RwLen;
    
//    uint16_t EnBusTake    : 1;
//    uint16_t EnBusRelease : 1;
    uint16_t EnBusSend    : 1;
    uint16_t EnBusRecv    : 1;
}SPI_Message_t;

/**
 *******************************************************************************
 * @brief        HAL SPI Interface
 *******************************************************************************
 */
struct __HAL_SPI_BUS;
typedef struct
{
    uint16_t (*Config)(struct __HAL_SPI_BUS *spi, HAL_SPI_Config_t *config);
    uint32_t (*Transfer)(struct __HAL_SPI_BUS *spi, SPI_Message_t *msg);
}HAL_SPI_Interface_t;

/**
 *******************************************************************************
 * @brief        HAL SPI Handle
 *******************************************************************************
 */
struct __HAL_SPI_DEVICE;
typedef struct __HAL_SPI_BUS
{
    //! 总线属性
    HAL_Atrribute_t Atrribute;
    //! 总线队列
    FwList_t List;
    //! 底层操作句柄
    void *Param;
    //! 设备句柄
    HAL_Device_t *Dev;
    //! 当前占用总线的设备
    struct __HAL_SPI_DEVICE *Owner;
}HAL_SPI_Bus_t;

typedef struct __HAL_SPI_DEVICE
{
    HAL_Atrribute_t Atrribute;
    HAL_SPI_Bus_t *Bus;
    
    //! SPI CSS 引脚
    HAL_Port_t Css;
}HAL_SPI_Device_t;

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern void HAL_SPI_Register(HAL_SPI_Interface_t *ops, void *userData);
extern void HAL_SPI_Bus_Init(HAL_SPI_Bus_t *spi, HAL_SPI_Config_t *config);
extern void HAL_SPI_Device_Init(HAL_SPI_Device_t *spiDev, uint8_t busPort, uint32_t css);
 
extern uint8_t HAL_SPI_Bus_Take(HAL_SPI_Device_t *spi);
extern uint8_t HAL_SPI_Bus_Release(HAL_SPI_Device_t *spi);

extern uint8_t HAL_SPI_Take(HAL_SPI_Device_t *spiDev);
extern uint8_t HAL_SPI_Release(HAL_SPI_Device_t *spiDev);

extern uint16_t HAL_SPI_Send(HAL_SPI_Device_t *spiDev, uint8_t *buf, uint16_t len);
extern uint16_t HAL_SPI_Recv(HAL_SPI_Device_t *spiDev, uint8_t *buf, uint16_t len);
extern uint16_t HAL_SPI_Transfer(HAL_SPI_Device_t *spiDev, uint8_t *sendBuf, uint8_t *recvBuf, uint16_t len);
extern uint16_t HAL_SPI_Transfer_Message(HAL_SPI_Device_t *spiDev, SPI_Message_t *msg);
extern uint16_t HAL_SPI_Send_Then_Send(HAL_SPI_Device_t *spiDev, uint8_t *sendBuf1, uint16_t sendLen1, uint8_t *sendBuf2, uint16_t sendLen2);
extern uint16_t HAL_SPI_Send_Then_Recv(HAL_SPI_Device_t *spiDev, uint8_t *sendBuf, uint16_t sendLen, uint8_t *recvBuf, uint16_t recvLen);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
