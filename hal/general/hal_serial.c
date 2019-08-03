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
 * @file       hal_serial.c                                                    *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      hal serial driver component                                     *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20170110 创建文件 文件名:fw_debug.c                                       *
 * 2.20171106 合并fw_stream.c组件内容，实现串口流控，跨平台控制                *
 *            更名为HAL_SERIAL.c                                               *
 * 3.20180423 统一硬件抽象层，修改硬件底层驱动(参考RT-THREAD)                  *
 *            支持多种UART模式                                                 *
 * 4.20180804 修改文件名，将HAL_SERIAL.c修改为HAL_SERIAL.c                     *
 * 5.20180815 波特率115200下通过压力测试(每隔10MS发送"Hello World!")           *
 *******************************************************************************
 */
 
/**
 * @defgroup hal serial driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"
#include <string.h>

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       serial组件相关操作宏
 *******************************************************************************
 */
#if 0
#define Serial_PutChar(a, c) ((!IS_PTR_NULL(DeviceSerial.Ops.PutChar)) ? (DeviceSerial.Ops.PutChar((serial), (c))) : (0))
#define Serial_GetChar(a, c) ((!IS_PTR_NULL(DeviceSerial.Ops.GetChar)) ? (DeviceSerial.Ops.GetChar((serial), (char *)(c))) : (0))
#define Serial_Put(a, b, c)  ((!IS_PTR_NULL(DeviceSerial.Ops.DmaTransmit)) ? (DeviceSerial.Ops.DmaTransmit(serial, (b), (c), HAL_SERIAL_DIR_TX)) : (0))
#else
#define Serial_PutChar(a, c) (DeviceSerial.Ops.PutChar((serial), (c)))
#define Serial_GetChar(a, c) (DeviceSerial.Ops.GetChar((serial), (char *)(c)))
#define Serial_Put(a, b, c)  (DeviceSerial.Ops.DmaTransmit(serial, (b), (c), HAL_SERIAL_DIR_TX))
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef ENABLE_HAL_SERIAL_DRIVER
struct HAL_DRIVER_SERIAL
{
    HAL_Device_t           Parent;
    HAL_Serial_Interface_t Ops;
}DeviceSerial;
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#ifdef ENABLE_HAL_SERIAL_DRIVER
/**
 *******************************************************************************
 * @brief       SERIAL 发送处理函数
 * @param       [in/out]  serial    设备句柄
 * @param       [in/out]  void
 * @return      [in/out]  计算结果
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
uint8_t Serial_Send_Handle(HAL_Serial_t *serial)
{
    if (serial->Tx.State != HAL_SERIAL_IDLE)
    {
        return 0;
    }
    
    HAL_Atom_Begin();

    FwBuf_t *fifo = &serial->Tx.Fifo;

    if (fifo->Head != fifo->Tail)
    {
        char ch = fifo->Buffer[fifo->Head++];

        fifo->Size --;

        if (fifo->Head >= fifo->Len)
        {
            fifo->Head = 0;
        }

        Serial_PutChar(serial, ch);
    }

    HAL_Atom_End();
    
    return 1;
}

/**
 *******************************************************************************
 * @brief       SERIAL 设备注册函数
 * @param       [in/out]  name       设备名称
 * @param       [in/out]  ops        设备底层操作接口
 * @param       [in/out]  flag       设备配置参数
 * @param       [in/out]  userData   用户数据
 * @return      [in/out]  配置结果
 * @note        None
 *******************************************************************************
 */
void HAL_Serial_Register(HAL_Serial_Interface_t *ops, void *userData)
{
    memset(&DeviceSerial, 0, sizeof(DeviceSerial));

    DeviceSerial.Ops.Config      = ops->Config;
    DeviceSerial.Ops.Control     = ops->Control;
    DeviceSerial.Ops.DmaTransmit = ops->DmaTransmit;
    DeviceSerial.Ops.GetChar     = ops->GetChar;
    DeviceSerial.Ops.PutChar     = ops->PutChar;

#if defined(ENABLE_HAL_DRIVER_COMPONENT)
    HAL_Interface_t halDevOps;

    halDevOps.Close   = NULL;
    halDevOps.Control = NULL;
    halDevOps.Fini    = NULL;
    halDevOps.Init    = NULL;
    halDevOps.Open    = NULL;
    halDevOps.Read    = NULL;
    halDevOps.Write   = NULL;

    DeviceSerial.Parent.UserData = userData;

    HAL_Device_Register(&DeviceSerial.Parent, HAL_SERIAL_STR, &halDevOps, HAL_Flag_Encode(HAL_DEVICE_SERIAL, HAL_READ_FLAG | HAL_WRITE_FLAG));
#endif
}

/**
 *******************************************************************************
 * @brief       UART 驱动初始化
 * @param       [in/out]  serial    设备句柄
 * @param       [in/out]  config    配置参数
 * @return      [in/out]  配置结果
 * @note        None
 *******************************************************************************
 */
void HAL_Serial_Init(HAL_Serial_t *serial, HAL_Serial_Config_t *config)
{
    memset(serial, 0, sizeof(HAL_Serial_t));

    FwBufInit(&serial->Tx.Fifo, config->Buffer.Tx, config->Buffer.TxLen);
    FwBufInit(&serial->Rx.Fifo, config->Buffer.Rx, config->Buffer.RxLen);

    serial->Attribute.Port = config->Attribute.Port;

    serial->Tx.State   = HAL_SERIAL_INIT;
    serial->Rx.State   = HAL_SERIAL_INIT;

    serial->Super      = config->Super;
    serial->SuperParam = config->SuperParam;
    
    serial->Dev        = &DeviceSerial.Parent;
    
    //! 初始化硬件
    if (!IS_PTR_NULL(DeviceSerial.Ops.Config))
    {
        DeviceSerial.Ops.Config(serial, config);
    }
    
    //! 注册设备驱动回调    
    Serial_Callback callback = {.Callback = HAL_Serial_Isr_Handle, .Param = (void *)serial};
    
    if (!IS_PTR_NULL(DeviceSerial.Ops.Control))
    {
        DeviceSerial.Ops.Control(serial, HAL_SET_CALLBACK_CMD, (void *)&callback);
    }

    //! 配置位检测
    HAL_Serial_EnableTx(serial);
    HAL_Serial_EnableRx(serial);
}

/**
 *******************************************************************************
 * @brief       UART 使能发送组件
 * @param       [in/out]  serial     设备句柄
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void HAL_Serial_EnableTx(HAL_Serial_t *serial)
{
    if (serial->Tx.State == HAL_SERIAL_INIT || serial->Tx.State == HAL_SERIAL_SLEEP)
    {
		serial->Tx.State = HAL_SERIAL_IDLE;

        FwBufSetEmpty(&serial->Tx.Fifo);
    }
}

/**
 *******************************************************************************
 * @brief       UART 禁用发送组件
 * @param       [in/out]  serial    设备句柄
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void HAL_Serial_DisableTx(HAL_Serial_t *serial)
{
    serial->Tx.State = HAL_SERIAL_SLEEP;
    
    FwBufSetEmpty(&serial->Tx.Fifo);
}

/**
 *******************************************************************************
 * @brief       UART 使能接收组件
 * @param       [in/out]  serial    设备句柄
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void HAL_Serial_EnableRx(HAL_Serial_t *serial)
{
    if (serial->Rx.State == HAL_SERIAL_INIT || serial->Rx.State == HAL_SERIAL_SLEEP)
    {
        serial->Rx.State = HAL_SERIAL_IDLE;
    
        FwBufSetEmpty(&serial->Rx.Fifo);
    }
}

/**
 *******************************************************************************
 * @brief       UART 禁用接收组件
 * @param       [in/out]  serial    设备句柄
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void HAL_Serial_DisableRx(HAL_Serial_t *serial)
{
    serial->Rx.State = HAL_SERIAL_SLEEP;
    
    FwBufSetEmpty(&serial->Rx.Fifo);
}

/**
 *******************************************************************************
 * @brief       检测 UART 发送是否完成
 * @param       [in/out]  serial    设备句柄
 * @return      [in/out]  0         发送中
 * @return      [in/out]  1         发送完成
 * @note        None
 *******************************************************************************
 */
uint16_t HAL_Serial_IsTxDone(HAL_Serial_t *serial)
{
    if (serial->Tx.State == HAL_SERIAL_DONE)
    {
        serial->Tx.State = HAL_SERIAL_IDLE;
        
        return 1;
    }
    
    return 0;
}

/**
 *******************************************************************************
 * @brief       检测 UART 接收是否完成
 * @param       [in/out]  serial    设备句柄
 * @return      [in/out]  0         接收中
 * @return      [in/out]  1         接收完成
 * @note        None
 *******************************************************************************
 */
uint16_t HAL_Serial_IsRxDone(HAL_Serial_t *serial)
{
    if (serial->Rx.State == HAL_SERIAL_DONE)
    {
        serial->Rx.State = HAL_SERIAL_IDLE;
        
        return 1;
    }
    
    return 0;
}

/**
 *******************************************************************************
 * @brief       UART 输出字符
 * @param       [in/out]  serial    设备句柄
 * @param       [in/out]  c         发送的字符
 * @return      [in/out]  0         输出失败
 * @return      [in/out]  1         输出成功
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t HAL_Serial_PutChar(HAL_Serial_t *serial, uint8_t c)
{
    return Serial_PutChar(serial, c);
}

/**
 *******************************************************************************
 * @brief       UART 输入字符
 * @param       [in/out]  serial    设备句柄
 * @return      [in/out]  *c        接收的字符
 * @return      [in/out]  0         输入失败
 * @return      [in/out]  1         输入成功
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t HAL_Serial_GetChar(HAL_Serial_t *serial, uint8_t *c)
{
    return Serial_GetChar(serial, c);
}

/**
 *******************************************************************************
 * @brief       UART 输出字符串
 * @param       [in/out]  serial    设备句柄
 * @param       [in/out]  buf       发送缓存
 * @param       [in/out]  pos       发送地址偏移量
 * @param       [in/out]  len       发送数据长度
 * @return      [in/out]  实际写入数据的数据长度
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t HAL_Serial_Put(HAL_Serial_t *serial, uint8_t *buf, uint16_t pos, uint16_t len)
{
    return Serial_Put(serial, &buf[pos], len);
}

/**
 *******************************************************************************
 * @brief       UART 写入
 * @param       [in/out]  drv       设备句柄
 * @param       [in/out]  buf       发送缓存
 * @param       [in/out]  len       发送数据长度
 * @return      [in/out]  实际写入数据的数据长度
 * @note        None
 *******************************************************************************
 */
uint16_t HAL_Serial_Write(HAL_Serial_t *serial, uint8_t *buf, uint16_t len)
{
    HAL_Atom_Begin();
    
    switch (serial->Tx.State)
    {
        case HAL_SERIAL_IDLE:
            FwBufWrite(&serial->Tx.Fifo, &buf[0], len);
            Serial_Send_Handle(serial);
            serial->Tx.State = HAL_SERIAL_BUSY;
            break;
        case HAL_SERIAL_SLEEP:
        case HAL_SERIAL_BUSY:
            len = FwBufWrite(&serial->Tx.Fifo, &buf[0], len);
            break;
        default:
            len = 0;
            break;
    }

    HAL_Atom_End();
    
    return len;
}

/**
 *******************************************************************************
 * @brief       UART 读取
 * @param       [in/out]  serial    设备句柄
 * @param       [in/out]  buf       接收缓存
 * @param       [in/out]  len       接收数据长度
 * @return      [in/out]  实际读取到的数据长度
 * @note        None
 *******************************************************************************
 */
uint16_t HAL_Serial_Read(HAL_Serial_t *serial, uint8_t *buf, uint16_t len)
{
    uint16_t i;
    
    FwBuf_t *fifo = &serial->Rx.Fifo;
    
    HAL_Atom_Begin();

    for (i=0; i<len && fifo->Head != fifo->Tail; i++)
    {
        buf[i] = fifo->Buffer[fifo->Head++];
    
        if (fifo->Head >= fifo->Len)
        {
            fifo->Head = 0;
        }
    }

    HAL_Atom_End();
    
    return i;
}

/**
 *******************************************************************************
 * @brief       UART 事件处理
 * @param       [in/out]  *port     设备句柄
 * @param       [in/out]  event     触发事件
 * @return      [in/out]  void
 * @note        支持DMA发送、DMA接收、UART发送、UART接收 建议放在中断函数中处理
 *******************************************************************************
 */
void HAL_Serial_Isr_Handle(void *port, uint16_t event)
{
    HAL_Serial_t *serial = (HAL_Serial_t *)port;

    switch (event)
    {
        /* Rx indication */
        case HAL_SERIAL_EVENT_RX_IND:
        {
            uint8_t ch;
            int16_t state;
            uint16_t size;
            FwBuf_t *fifo = &serial->Rx.Fifo;
            
            while (1)
            {
                state = Serial_GetChar(serial, &ch);
                
                if (state == 0)
                {
                    break;
                }
                
                //! 仅保留最新接收的数据
                fifo->Buffer[fifo->Tail++] = ch;
                
                if(fifo->Tail >= fifo->Len)
                {
                    fifo->Tail = 0;
                }

                if(fifo->Tail == fifo->Head)
                {
                    if (++fifo->Head >= fifo->Len)
                    {
                        fifo->Head = 0;
                    }
                }
            }
            
            if (!IS_PTR_NULL(serial->Super))
            {
                if (fifo->Tail >= fifo->Head)
                {
                    size = fifo->Tail - fifo->Head;
                }
                else
                {
                    size = fifo->Len - (fifo->Head - fifo->Tail);
                }
                
                serial->Super(serial->SuperParam, (uint32_t)HAL_SERIAL_EVENT_RX_IND, size);
            }
            break;
        }
        case HAL_SERIAL_EVENT_RX_TIMEOUT:
            HAL_Evt_Set(serial->Attribute.Event, HAL_SERIAL_RX_TIMEOUT);
            break;
        /* Tx complete   */
        case HAL_SERIAL_EVENT_TX_DONE:
        {
            FwBuf_t *fifo = &serial->Tx.Fifo;
            
            if (fifo->Tail == fifo->Head)
            {
                serial->Tx.State = HAL_SERIAL_IDLE;

                if (!IS_PTR_NULL(serial->Super))
                {
                    serial->Super(serial->SuperParam, (uint32_t)HAL_SERIAL_EVENT_TX_DONE, 0);
                }
                
                break;
            }

            char ch = fifo->Buffer[fifo->Head++];

            fifo->Size --;

            if (fifo->Head >= fifo->Len)
            {
                fifo->Head = 0;
            }
            
            Serial_PutChar(serial, ch);
            break;
        }
        /* Rx DMA transfer done */
        case HAL_SERIAL_EVENT_RX_DMADONE:
            //! 触发接收完成事件
            HAL_Evt_Set(serial->Attribute.Event, HAL_SERIAL_RX_DONE);
            break;
        /* Tx DMA transfer done */
        case HAL_SERIAL_EVENT_TX_DMADONE:
            //! 发送完成处理
            HAL_Evt_Set(serial->Attribute.Event, HAL_SERIAL_TX_DONE);
            break;
        default:
            break;
    }
}

#endif

/** @}*/     /** hal serial driver component */

/**********************************END OF FILE*********************************/
