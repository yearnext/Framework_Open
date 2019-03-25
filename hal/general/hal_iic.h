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
 * @file       hal_iic.h                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-06-28                                                      *
 * @brief      hal iic driver component head file                              *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 2018-06-28 从“hal_device.h”分离出IIC驱动                                 *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DRIVER_IIC_H__
#define __HAL_DRIVER_IIC_H__

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
 * @brief        HAL IIC FLAG DEFINE
 *******************************************************************************
 */
#define HAL_IIC_WRITE_FLAG                                                     0
#define HAL_IIC_READ_FLAG                                                      1

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        HAL IIC PORT
 *******************************************************************************
 */
enum HAL_IIC_PORT
{
#ifndef HAL_IIC_0
    HAL_IIC_0,
#endif
    
#ifndef HAL_IIC_1   
    HAL_IIC_1,
#endif
    
#ifndef HAL_IIC_2
    HAL_IIC_2,
#endif
    
    HAL_IIC_MAX,
};

/**
 *******************************************************************************
 * @brief        HAL IIC EVENT
 *******************************************************************************
 */
enum HAL_IIC_EVENT
{
    HAL_IIC_NONE = 0,
    
    HAL_IIC_RELEASE_EVENT,
    
    HAL_IIC_START_EVENT,
    HAL_IIC_STOP_EVENT,
    HAL_IIC_SEND_ADDR_ACK_EVENT,
    HAL_IIC_SEND_ADDR_NOACK_EVENT,
    HAL_IIC_SEND_DATA_ACK_EVENT,
    HAL_IIC_SEND_DATA_NOACK_EVENT,
    HAL_IIC_RECV_ADDR_ACK_EVENT,
    HAL_IIC_RECV_ADDR_NOACK_EVENT,
    HAL_IIC_RECV_DATA_ACK_EVENT,
    HAL_IIC_RECV_DATA_NOACK_EVENT,
    
    HAL_IIC_TIMEOUT_EVENT,
    HAL_IIC_ARBITRATION_LOSS_EVENT,
    HAL_IIC_BUS_ERROR_EVENT,
};

/**
 *******************************************************************************
 * @brief        HAL IIC Config
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
}HAL_IIC_Config_t;

/**
 *******************************************************************************
 * @brief        HAL IIC EVENT
 *******************************************************************************
 */
typedef struct
{
    uint8_t  Addr;
    uint8_t  Flag;
    uint16_t Len;
    uint8_t  *Buf;
}IIC_Msg_t;

/**
 *******************************************************************************
 * @brief        HAL IIC Interface
 *******************************************************************************
 */
struct __HAL_IIC_BUS;
typedef struct
{
    uint32_t (*Slave)(struct __HAL_IIC_BUS *iic, IIC_Msg_t *msg);
    uint32_t (*Master)(struct __HAL_IIC_BUS *iic, IIC_Msg_t *msg);
    
    uint16_t (*Control)(struct __HAL_IIC_BUS *iic, uint32_t cmd, uint32_t param);
}HAL_IIC_Interface_t;

/**
 *******************************************************************************
 * @brief        HAL IIC Handle
 *******************************************************************************
 */
struct __HAL_IIC_DEVICE;
typedef struct __HAL_IIC_BUS
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
    struct __HAL_IIC_DEVICE *Owner;
}HAL_IIC_Bus_t;

typedef struct __HAL_IIC_DEVICE
{
    HAL_Atrribute_t Atrribute;
    HAL_IIC_Bus_t   *Bus;
}HAL_IIC_Device_t;

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if 0
extern void HAL_IIC_Bus_Register(HAL_IIC_Interface_t *ops, void *data);

extern void HAL_IIC_Bus_Init(HAL_IIC_Bus_t *bus, HAL_IIC_Config_t *config);

extern void HAL_IIC_Device_Init(HAL_IIC_Device_t *dev, uint16_t port);

extern uint16_t HAL_IIC_Master_Send(HAL_IIC_Bus_t *bus, IIC_Msg_t *msg);
extern uint16_t HAL_IIC_Master_Recv(HAL_IIC_Bus_t *bus, IIC_Msg_t *msg);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
