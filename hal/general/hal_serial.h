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
 * @file       hal_serial.h                                                    *
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DRIVER_SERIAL_H__
#define __HAL_DRIVER_SERIAL_H__

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
 * @brief      SERIAL DRIVER STATUS
 *******************************************************************************
 */
typedef enum
{
    HAL_SERIAL_INIT,
    HAL_SERIAL_IDLE,
    HAL_SERIAL_BUSY,
    HAL_SERIAL_DONE,
    HAL_SERIAL_SLEEP,
}Serial_Status;

/**
 *******************************************************************************
 * @brief      SERIAL SUPER CALLBACK TYPE
 *******************************************************************************
 */
typedef uint32_t (*SerialSuper_t)(void *super, uint32_t evt, uint16_t len);

/**
 *******************************************************************************
 * @brief      SERIAL HANDLE INIT TYPE
 *******************************************************************************
 */
typedef struct
{
    struct
    {
        uint8_t *Tx;
        uint8_t *Rx;
        
        uint16_t TxLen;
        uint16_t RxLen;
    }Buffer;
    
    struct
    {
        uint32_t Baud;

        uint32_t DataBits :4;
        uint32_t StopBits :2;
        uint32_t Parity   :2;
        uint32_t BitOrder :1;
        uint32_t Invert   :1;
        uint32_t BufSize  :16;
        uint32_t Port     :6;
    }Attribute;
    
    SerialSuper_t Super;
    void          *SuperParam;
}HAL_Serial_Config_t;

/**
 *******************************************************************************
 * @brief      SERIAL PIPELINE COMPONENT
 *******************************************************************************
 */
typedef struct
{
    FwBuf_t Fifo;

    Serial_Status State;
}Serial_Pipe_t;

/**
 *******************************************************************************
 * @brief      SERIAL COMPONENT HANDLE
 * @note       todo 添加对动态内存的支持，需要开启LIBC组件
 *******************************************************************************
 */
typedef struct
{
    HAL_Atrribute_t Attribute;
    
    //! 上层回调
    SerialSuper_t Super;
    void          *SuperParam;

    //! 底层操作句柄
    void *Param;

    //! 设备操作句柄
    HAL_Device_t *Dev;

    //! 通讯管道
    Serial_Pipe_t Tx;
    Serial_Pipe_t Rx;
}HAL_Serial_t;

/**
 *******************************************************************************
 * @brief      SERIAL INTERFACE
 *******************************************************************************
 */
typedef struct
{
    uint16_t (*Config)(HAL_Serial_t *serial, HAL_Serial_Config_t *config);
    uint32_t (*Control)(HAL_Serial_t *serial, uint32_t cmd, void *arg);

    uint16_t (*PutChar)(HAL_Serial_t *serial, char c);
    uint16_t (*GetChar)(HAL_Serial_t *serial, char *c);

    uint16_t (*DmaTransmit)(HAL_Serial_t *serial, uint8_t *buf, uint16_t size, uint8_t dir);
}HAL_Serial_Interface_t;

/**
 *******************************************************************************
 * @brief      SERIAL ISR CALLBACK
 *******************************************************************************
 */
typedef void (*SerialIsrCallback)(void *port, uint16_t evt);
typedef struct
{
    SerialIsrCallback Callback;
    void *Param;
}Serial_Callback;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
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
extern void HAL_Serial_Register(HAL_Serial_Interface_t *ops, void *userData);

/**
 *******************************************************************************
 * @brief       SERIAL 驱动初始化
 * @param       [in/out]  serial    设备句柄
 * @param       [in/out]  config    配置参数
 * @return      [in/out]  配置结果
 * @note        None
 *******************************************************************************
 */
extern void HAL_Serial_Init(HAL_Serial_t *serial, HAL_Serial_Config_t *config);

/**
 *******************************************************************************
 * @brief       SERIAL 使能发送组件
 * @param       [in/out]  serial    设备句柄
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void HAL_Serial_EnableTx(HAL_Serial_t *serial);

/**
 *******************************************************************************
 * @brief       SERIAL 禁用发送组件
 * @param       [in/out]  serial    设备句柄
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void HAL_Serial_DisableTx(HAL_Serial_t *serial);

/**
 *******************************************************************************
 * @brief       SERIAL 使能接收组件
 * @param       [in/out]  serial    设备句柄
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void HAL_Serial_EnableRx(HAL_Serial_t *serial);

/**
 *******************************************************************************
 * @brief       SERIAL 禁用接收组件
 * @param       [in/out]  serial    设备句柄
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void HAL_Serial_DisableRx(HAL_Serial_t *serial);

/**
 *******************************************************************************
 * @brief       SERIAL 输出字符
 * @param       [in/out]  serial    设备句柄
 * @param       [in/out]  c         发送的字符
 * @return      [in/out]  0         输出失败
 * @return      [in/out]  1         输出成功
 * @note        None
 *******************************************************************************
 */
extern uint16_t HAL_Serial_PutChar(HAL_Serial_t *serial, uint8_t c);

/**
 *******************************************************************************
 * @brief       SERIAL 输入字符
 * @param       [in/out]  serial    设备句柄
 * @return      [in/out]  *c        接收的字符
 * @return      [in/out]  0         输入失败
 * @return      [in/out]  1         输入成功
 * @note        None
 *******************************************************************************
 */
extern uint16_t HAL_Serial_GetChar(HAL_Serial_t *serial, uint8_t *c);

/**
 *******************************************************************************
 * @brief       SERIAL 输出字符串
 * @param       [in/out]  serial    设备句柄
 * @param       [in/out]  buf       发送缓存
 * @param       [in/out]  pos       发送地址偏移量
 * @param       [in/out]  len       发送数据长度
 * @return      [in/out]  实际写入数据的数据长度
 * @note        None
 *******************************************************************************
 */
extern uint16_t HAL_Serial_Put(HAL_Serial_t *serial, uint8_t *buf, uint16_t pos, uint16_t len);

/**
 *******************************************************************************
 * @brief       SERIAL 写入
 * @param       [in/out]  serial    设备句柄
 * @param       [in/out]  buf       发送缓存
 * @param       [in/out]  len       发送数据长度
 * @return      [in/out]  实际写入数据的数据长度
 * @note        None
 *******************************************************************************
 */
extern uint16_t HAL_Serial_Write(HAL_Serial_t *serial, uint8_t *buf, uint16_t len);

/**
 *******************************************************************************
 * @brief       SERIAL 读取
 * @param       [in/out]  serial    设备句柄
 * @param       [in/out]  buf       接收缓存
 * @param       [in/out]  len       接收数据长度
 * @return      [in/out]  实际读取到的数据长度
 * @note        None
 *******************************************************************************
 */
extern uint16_t HAL_Serial_Read(HAL_Serial_t *serial, uint8_t *buf, uint16_t len);

/**
 *******************************************************************************
 * @brief       SERIAL 硬件事件处理
 * @param       [in/out]  *port     设备句柄
 * @param       [in/out]  event     触发事件
 * @return      [in/out]  void
 * @note        支持DMA发送、DMA接收、UART发送、UART接收
 *******************************************************************************
 */
extern void HAL_Serial_Isr_Handle(void *port, uint16_t event);

/**
 *******************************************************************************
 * @brief       SERIAL 时钟事件处理
 * @param       [in/out]  drv       设备句柄
 * @return      [in/out]  void
 * @note        void
 *******************************************************************************
 */
extern void HAL_Serial_Tick(void *param);

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
