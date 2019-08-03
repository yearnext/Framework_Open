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
#include "hal_def.h"

/* Exported macro ------------------------------------------------------------*/
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
