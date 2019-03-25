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
 * @file       hal_spi.c                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-06-28                                                      *
 * @brief      hal spi driver component source file                            *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 2018-06-28 从“hal_device.h”分离出SPI驱动                                 *
 *******************************************************************************
 */
 
/**
* @defgroup hal spi driver component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef ENABLE_HAL_SPI_DRIVER
struct
{
    HAL_Device_t    Parent;
    HAL_SPI_Interface_t Ops;

    LinkList_t List;
}DeviceSPIBus;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#ifdef ENABLE_HAL_SPI_DRIVER
void HAL_SPI_Register(HAL_SPI_Interface_t *ops, void *userData)
{
    memset(&DeviceSPIBus, 0, sizeof(DeviceSPIBus));

    DeviceSPIBus.Ops.Config      = ops->Config;
    DeviceSPIBus.Ops.Transfer    = ops->Transfer;
    
    LinkListInit(&DeviceSPIBus.List);
#ifdef ENABLE_HAL_DRIVER_COMPONENT
    HAL_Interface_t halDevOps;
    
    DeviceSPIBus.Parent.UserData = userData;
    
    halDevOps.Init    = NULL;
    halDevOps.Fini    = NULL;
    halDevOps.Open    = NULL;
    halDevOps.Close   = NULL;
    halDevOps.Write   = NULL;
    halDevOps.Read    = NULL;
    halDevOps.Control = NULL;
    
    HAL_Device_Register(&DeviceSPIBus.Parent, HAL_SPI_STR, &halDevOps, HAL_Flag_Encode(HAL_DEVICE_SERIAL, HAL_READ_FLAG | HAL_WRITE_FLAG));
#endif
}

void HAL_SPI_Bus_Init(HAL_SPI_Bus_t *spi, HAL_SPI_Config_t *config)
{
    memset(&DeviceSPIBus, 0, sizeof(DeviceSPIBus));
    
    spi->Atrribute.Port  = config->Atrribute.Port;
    spi->Dev             = &DeviceSPIBus.Parent;
    spi->Owner           = NULL;
    spi->Atrribute.State = HAL_DEVICE_IDLE;
    
    LinkListInit(&spi->List);
    LinkListInsertAfter(&DeviceSPIBus.List, &spi->List);
    
    if (!IS_PTR_NULL(DeviceSPIBus.Ops.Config))
    {
        DeviceSPIBus.Ops.Config(spi, config);
    }
}

void HAL_SPI_Device_Init(HAL_SPI_Device_t *spiDev, uint8_t busPort, uint32_t css)
{
    LinkList_t *list = DeviceSPIBus.List.Next;
    HAL_SPI_Bus_t *spiBus;
    
    //! 初始化spi设备 css 引脚
    spiDev->Css.Port = HAL_PORT(css);
    spiDev->Css.Pin  = HAL_PIN(css);
    spiDev->Css.Mode = HAL_PIN_OUTPUT;
    HAL_Pin_Init(css, HAL_PIN_OUTPUT);
    //! 释放spi总线
    HAL_Pin_Set(css);
    
    //! 载入总线句柄
    while(!IS_PTR_NULL(list))
    {
        spiBus = LinkListEntry(list, HAL_SPI_Bus_t, List);
        
        if (spiBus->Atrribute.Port == busPort)
        {
            spiDev->Bus = spiBus;
            spiDev->Atrribute.State = HAL_DEVICE_IDLE;
            break;
        }
    }
}
    
uint8_t HAL_SPI_Bus_Take(HAL_SPI_Device_t *spi)
{
    //! 总线空闲则占用总线
    if (HAL_Flag_Get(spi->Bus->Atrribute.Flag, HAL_SPI_TAKE_FLAG) == 0)
    {
        HAL_Flag_Set(spi->Bus->Atrribute.Flag, HAL_SPI_TAKE_FLAG);
        spi->Bus->Owner = spi;
        
        return 0;
    }

    return 1;
}

uint8_t HAL_SPI_Bus_Release(HAL_SPI_Device_t *spi)
{
    //! 总线被占用则释放总线
    if (spi->Bus->Owner == spi)
    {
        if (HAL_Flag_Get(spi->Bus->Atrribute.Flag, HAL_SPI_TAKE_FLAG))
        {
            HAL_Flag_Clr(spi->Bus->Atrribute.Flag, HAL_SPI_TAKE_FLAG);
            spi->Bus->Owner = NULL;
            
            return 0;
        }
    }
    
    return 1;
}

uint8_t HAL_SPI_Take(HAL_SPI_Device_t *spi)
{
    if (HAL_SPI_Bus_Take(spi))
    {
        return 1;
    }
    
    if (HAL_Flag_Get(spi->Atrribute.Flag, HAL_SPI_TAKE_FLAG) == 0)
    {
        HAL_Flag_Set(spi->Atrribute.Flag, HAL_SPI_TAKE_FLAG);

        //! 占用SPI总线
        HAL_Pin_Clr(HAL_PIN_ID(spi->Css.Port, spi->Css.Pin));
        
        return 0;
    }

    return 1;
}

uint8_t HAL_SPI_Release(HAL_SPI_Device_t *spi)
{
    if (HAL_SPI_Bus_Release(spi))
    {
        return 1;
    }
    
    if (HAL_Flag_Get(spi->Atrribute.Flag, HAL_SPI_TAKE_FLAG))
    {
        HAL_Flag_Clr(spi->Atrribute.Flag, HAL_SPI_TAKE_FLAG);

        //! 释放SPI总线
        HAL_Pin_Set(HAL_PIN_ID(spi->Css.Port, spi->Css.Pin));
        return 0;
    }
    
    return 0;
}

uint16_t HAL_SPI_Send(HAL_SPI_Device_t *spiDev, uint8_t *buf, uint16_t len)
{
    SPI_Message_t msg;
    
    //! 获取SPI总线
    if (HAL_SPI_Take(spiDev))
    {
        return 0;
    }
    
    if (!IS_PTR_NULL(DeviceSPIBus.Ops.Transfer))
    {
        memset(&msg, 0, sizeof(msg));
        
        msg.EnBusRecv = 0;
        msg.EnBusSend = 1;
        msg.SendBuf   = buf;
        msg.RwLen     = len;
        
        len = DeviceSPIBus.Ops.Transfer(spiDev->Bus, &msg);
    }
    
    //! 释放SPI总线
    if (HAL_SPI_Release(spiDev))
    {
        return 0;
    }
    
    return len;
}

uint16_t HAL_SPI_Recv(HAL_SPI_Device_t *spiDev, uint8_t *buf, uint16_t len)
{
    SPI_Message_t msg;
    
    //! 获取SPI总线
    if (HAL_SPI_Take(spiDev))
    {
        return 0;
    }
    
    if (!IS_PTR_NULL(DeviceSPIBus.Ops.Transfer))
    {
        memset(&msg, 0, sizeof(msg));
        
        msg.EnBusRecv = 1;
        msg.EnBusSend = 0;
        msg.SendBuf   = buf;
        msg.RwLen     = len;
        
        len = DeviceSPIBus.Ops.Transfer(spiDev->Bus, &msg);
    }
    
    //! 释放SPI总线
    if (HAL_SPI_Release(spiDev))
    {
        return 0;
    }
    
    return len;
}

uint16_t HAL_SPI_Transfer(HAL_SPI_Device_t *spiDev, uint8_t *sendBuf, uint8_t *recvBuf, uint16_t len)
{
    SPI_Message_t msg;
    
    //! 获取SPI总线
    if (HAL_SPI_Take(spiDev))
    {
        return 0;
    }
    
    if (!IS_PTR_NULL(DeviceSPIBus.Ops.Transfer))
    {
        memset(&msg, 0, sizeof(msg));
        
        msg.EnBusRecv = 1;
        msg.EnBusSend = 1;
        msg.SendBuf   = sendBuf;
        msg.RecvBuf   = recvBuf;
        msg.RwLen     = len;
        
        len = DeviceSPIBus.Ops.Transfer(spiDev->Bus, &msg);
    }
    
    //! 释放SPI总线
    if (HAL_SPI_Release(spiDev))
    {
        return 0;
    }
    
    return len;
}

uint16_t HAL_SPI_Transfer_Message(HAL_SPI_Device_t *spiDev, SPI_Message_t *msg)
{
    if (!IS_PTR_NULL(DeviceSPIBus.Ops.Transfer))
    {
        return DeviceSPIBus.Ops.Transfer(spiDev->Bus, msg);
    }
    
    return 0;
}

uint16_t HAL_SPI_Send_Then_Send(HAL_SPI_Device_t *spiDev, uint8_t *sendBuf1, uint16_t sendLen1, uint8_t *sendBuf2, uint16_t sendLen2)
{
    SPI_Message_t msg;
    uint16_t len;
    
    //! 获取SPI总线
    if (HAL_SPI_Take(spiDev))
    {
        return 0;
    }
    
    if (!IS_PTR_NULL(DeviceSPIBus.Ops.Transfer))
    {
        memset(&msg, 0, sizeof(msg));
        
        msg.EnBusRecv = 0;
        msg.EnBusSend = 1;
        msg.SendBuf   = sendBuf1;
        msg.RwLen     = sendLen1;
        
        len = DeviceSPIBus.Ops.Transfer(spiDev->Bus, &msg);
        
        msg.EnBusRecv = 0;
        msg.EnBusSend = 1;
        msg.SendBuf   = sendBuf2;
        msg.RwLen     = sendLen2;
        
        len += DeviceSPIBus.Ops.Transfer(spiDev->Bus, &msg);
    }
    
    //! 释放SPI总线
    if (HAL_SPI_Release(spiDev))
    {
        return 0;
    }
    
    return len;
}

uint16_t HAL_SPI_Send_Then_Recv(HAL_SPI_Device_t *spiDev, uint8_t *sendBuf, uint16_t sendLen, uint8_t *recvBuf, uint16_t recvLen)
{
    SPI_Message_t msg;
    uint16_t len;
    
    //! 获取SPI总线
    if (HAL_SPI_Take(spiDev))
    {
        return 0;
    }
    
    if (!IS_PTR_NULL(DeviceSPIBus.Ops.Transfer))
    {
        memset(&msg, 0, sizeof(msg));
        
        msg.EnBusRecv = 0;
        msg.EnBusSend = 1;
        msg.SendBuf   = sendBuf;
        msg.RwLen     = sendLen;
        
        len = DeviceSPIBus.Ops.Transfer(spiDev->Bus, &msg);
        
        msg.EnBusRecv = 1;
        msg.EnBusSend = 0;
        msg.SendBuf   = recvBuf;
        msg.RwLen     = recvLen;
        
        len += DeviceSPIBus.Ops.Transfer(spiDev->Bus, &msg);
    }
    
    //! 释放SPI总线
    if (HAL_SPI_Release(spiDev))
    {
        return 0;
    }
    
    return len;
}
#endif

/** @}*/     /** hal spi driver component */

/**********************************END OF FILE*********************************/
