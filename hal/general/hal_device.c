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
 * @file       hal_device.c                                                    *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-08-28                                                      *
 * @brief      hal device component                                            *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 20170828    创建文件"hal_device.c"                                       *
 * 2. 20180127    修改HAL层架构                                                *
 *******************************************************************************
 */
 
/**
 * @defgroup hal device component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"
#include <string.h>

/* Private define ------------------------------------------------------------*/
//! HAL Flag decode
#define HAL_Flag_Decode_Type(flag)                                  (flag >> 16)
#define HAL_Flag_Decode_Flag(flag)                         (flag & 0x0000FFFFUL)

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      HAL DEVICE 专用变量
 *******************************************************************************
 */
#ifdef ENABLE_HAL_DRIVER_COMPONENT
struct 
{
    FwList_t List;

    uint16_t   Num;
}DeviceList;
#endif

/* Private functions ---------------------------------------------------------*/
#ifdef ENABLE_HAL_DRIVER_COMPONENT
/**
 *******************************************************************************
 * @brief       设备组件初始化函数
 * @param       [in/out]  void
 * @return      [in/out]  0
 * @note        由内核调用
 *******************************************************************************
 */
//! 初始化HAL层驱动
int HAL_Component_Init(void)
{
    //! 初始化设备列表
    FwListInit(&DeviceList.List);
    DeviceList.Num = 0;

    return 0;
}
INIT_COMPONENT_EXPORT(HAL_Component_Init);

/**
 *******************************************************************************
 * @brief       设备注册函数
 * @param       [in/out]  *dev     设备句柄
 * @param       [in/out]  *name    设备描述符
 * @param       [in/out]  *ops     设备操作接口
 * @param       [in/out]  flag     驱动配置
 * @return      [in/out]  0        注册成功
 * @return      [in/out]  1        注册失败
 * @note        由内核调用
 *******************************************************************************
 */
uint16_t HAL_Device_Register(HAL_Device_t *dev, char *name, HAL_Interface_t *ops, uint32_t flag)
{
    dev->Name = name;

    dev->Flag = HAL_Flag_Decode_Flag(flag);
    dev->Type = HAL_Flag_Decode_Type(flag);

    dev->Ops.Init    = ops->Init;
    dev->Ops.Fini    = ops->Fini;
    dev->Ops.Open    = ops->Open;
    dev->Ops.Close   = ops->Close;
    dev->Ops.Read    = ops->Read;
    dev->Ops.Write   = ops->Write;
    dev->Ops.Control = ops->Control;
    
    dev->State = 1;
    DeviceList.Num ++;
    
    FwListInit(&dev->List);
    FwListInsertAfter(&DeviceList.List, &dev->List);

    return 0;
}

/**
 *******************************************************************************
 * @brief       设备注销函数
 * @param       [in/out]  *dev     设备句柄
 * @return      [in/out]  0        注册成功
 * @return      [in/out]  1        注册失败
 * @note        由内核调用
 *******************************************************************************
 */
uint16_t HAL_Device_Unregister(HAL_Device_t *dev)
{
    if (dev->State)
    {
        FwListRemove(&dev->List);
        
        dev->State = 0;
        
        DeviceList.Num --;
    }
    
    return 0;
}

/**
 *******************************************************************************
 * @brief       设备查找函数
 * @param       [in/out]  type             设备类型
 * @return      [in/out]  HAL_Device_t *   设备句柄
 * @note        由内核调用
 *******************************************************************************
 */
HAL_Device_t *HAL_Device_Find(uint16_t type)
{
    HAL_Device_t *dev = NULL;
    FwList_t *list = &DeviceList.List;
    uint16_t i;
    
    for (i=0; i<DeviceList.Num; i++)
    {
        list = list->Next;
        
        dev = FwListEntry(list, HAL_Device_t, List);
        
        if (dev->Type == type)
        {
            return dev;
        }
    }

    return NULL;
}

/**
 *******************************************************************************
 * @brief       设备初始化函数
 * @param       [in/out]  *dev             设备类型
 * @param       [in/out]  param            设备参数
 * @return      [in/out]  state            状态
 * @note        由内核调用
 *******************************************************************************
 */
__INLINE
uint16_t HAL_Device_Init(struct HAL_DEVICE *dev, size_t param)
{
    if (!IS_PTR_NULL(dev->Ops.Init))
    {
        return dev->Ops.Init(dev, param);
    }
    
    return 1;
}

/**
 *******************************************************************************
 * @brief       设备反初始化函数
 * @param       [in/out]  *dev             设备类型
 * @return      [in/out]  state            状态
 * @note        由内核调用
 *******************************************************************************
 */
__INLINE
uint16_t HAL_Device_Fini(struct HAL_DEVICE *dev)
{
    if (!IS_PTR_NULL(dev->Ops.Fini))
    {
        return dev->Ops.Fini(dev);
    }
    
    return 1;
}

/**
 *******************************************************************************
 * @brief       设备打开函数
 * @param       [in/out]  *dev             设备句柄
 * @return      [in/out]  state            设备状态
 * @note        由内核调用
 *******************************************************************************
 */
__INLINE
uint16_t HAL_Device_Open(struct HAL_DEVICE *dev, uint16_t flag)
{
    if (!IS_PTR_NULL(dev->Ops.Open))
    {
        return dev->Ops.Open(dev, flag);
    }
    
    return 1;
}

/**
 *******************************************************************************
 * @brief       设备关闭函数
 * @param       [in/out]  *dev             设备句柄
 * @return      [in/out]  state            设备状态
 * @note        由内核调用
 *******************************************************************************
 */
__INLINE
uint16_t HAL_Device_Close(struct HAL_DEVICE *dev)
{
    if (!IS_PTR_NULL(dev->Ops.Close))
    {
        return dev->Ops.Close(dev);
    }
    
    return 1;
}

/**
 *******************************************************************************
 * @brief       设备数据写入函数
 * @param       [in/out]  *dev             设备句柄
 * @param       [in/out]  pos              缓冲区偏移量
 * @param       [in/out]  *buf             缓冲区
 * @param       [in/out]  len              写入长度
 * @return      [in/out]  num              实际写入数量
 * @note        由内核调用
 *******************************************************************************
 */
__INLINE
uint16_t HAL_Device_Write(struct HAL_DEVICE *dev, uint16_t pos, uint8_t *buf, uint16_t len)
{
    if (!IS_PTR_NULL(dev->Ops.Write))
    {
        return dev->Ops.Write(dev, pos, buf, len);
    }
    
    return 0; 
}

/**
 *******************************************************************************
 * @brief       设备数据读取函数
 * @param       [in/out]  *dev             设备句柄
 * @param       [in/out]  pos              缓冲区偏移量
 * @param       [in/out]  *buf             缓冲区
 * @param       [in/out]  len              读取长度
 * @return      [in/out]  num              实际读取数量
 * @note        由内核调用
 *******************************************************************************
 */
__INLINE
uint16_t HAL_Device_Read(struct HAL_DEVICE *dev, uint16_t pos, uint8_t *buf, uint16_t len)
{
    if (!IS_PTR_NULL(dev->Ops.Read))
    {
        return dev->Ops.Read(dev, pos, buf, len);
    }
    
    return 0;
}

/**
 *******************************************************************************
 * @brief       设备控制函数
 * @param       [in/out]  *dev             设备句柄
 * @param       [in/out]  cmd              控制命令
 * @param       [in/out]  *args            控制参数
 * @return      [in/out]  state            状态
 * @note        由内核调用
 *******************************************************************************
 */
__INLINE
uint16_t HAL_Device_Control(struct HAL_DEVICE *dev, uint8_t cmd, void *args)
{
    if (!IS_PTR_NULL(dev->Ops.Control))
    {
        return dev->Ops.Control(dev, cmd, args);
    }
    
    return 0xFFFF;
}
#endif

/** @}*/     /** hal device component */

/**********************************END OF FILE*********************************/
