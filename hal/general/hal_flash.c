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
 * @file       hal_flash.c                                                     *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-10-27                                                      *
 * @brief      mcu flash driver component server source file                   *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 20171027    创建文件"veeprom.c"                                          *
 * 2. 20180829    精简veeprom组件，更名为"hal_flash.c"                         *
 *******************************************************************************
 */
 
/**
* @defgroup hal flash driver component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"

/* Private define ------------------------------------------------------------*/
#define HAL_FLASH_ALIGNMENT                        (sizeof(size_t)/sizeof(char))

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef ENABLE_HAL_FLASH_DRIVER
struct
{
    HAL_Device_t          Parent;
    
    HAL_Flash_Interface_t Ops;
}DeviceFlash;
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#ifdef ENABLE_HAL_FLASH_DRIVER
__STATIC_INLINE
void flash_lock(void)
{
    if (!IS_PTR_NULL(DeviceFlash.Ops.Lock))
    {
        DeviceFlash.Ops.Lock();
    }
}

__STATIC_INLINE
void flash_unlock(void)
{
    if (!IS_PTR_NULL(DeviceFlash.Ops.Unlock))
    {
        DeviceFlash.Ops.Unlock();
    }
}

//__STATIC_INLINE
//void flash_rw_unlock(HAL_Flash_t *flash)
//{
//    Fw_Flag_Clr(flash->Atrribute.Flag, HAL_FLASH_LOCK_FLAG);
//}

//__STATIC_INLINE
//void flash_rw_lock(HAL_Flash_t *flash)
//{
//    Fw_Flag_Set(flash->Atrribute.Flag, HAL_FLASH_LOCK_FLAG);
//}

//__STATIC_INLINE
//uint8_t flash_is_rw_lock(HAL_Flash_t *flash)
//{
//    return (Fw_Flag_Get(flash->Atrribute.Flag, HAL_FLASH_LOCK_FLAG) || (flash->Atrribute.State == HAL_FLASH_HW_ERROR));
//}

__STATIC_INLINE
void flash_erase(uint32_t addr)
{
    if (!IS_PTR_NULL(DeviceFlash.Ops.Erase))
    {
        DeviceFlash.Ops.Erase(addr);
    }
}

__STATIC_INLINE
uint32_t flash_read_word(uint32_t addr)
{
    if (!IS_PTR_NULL(DeviceFlash.Ops.ReadWord))
    {
        return DeviceFlash.Ops.ReadWord(addr);
    }
    
    return 0xFFFFFFFF;
}

__STATIC_INLINE
void flash_write_word(uint32_t addr, uint32_t wr)
{
    if (!IS_PTR_NULL(DeviceFlash.Ops.WriteWord))
    {
        DeviceFlash.Ops.WriteWord(addr, wr);
    }
}

__STATIC_INLINE
uint32_t flash_get_flag(uint32_t flag, uint32_t addr, uint32_t vData)
{
    if (!IS_PTR_NULL(DeviceFlash.Ops.GetFlag))
    {
        return DeviceFlash.Ops.GetFlag(flag, addr, vData);
    }
    
    return 0;
}

__STATIC_INLINE
void flash_load_data(HAL_Flash_t *flash)
{
    uint16_t i;
    uint32_t *p = (uint32_t *)&flash->Buffer[0];
    
    for (i=0; i<=flash->BufferLen; i+=4)
    {
        *p++ = flash_read_word(flash->PhyInfo.PageBase + i);
    }
}

/* Exported functions --------------------------------------------------------*/
void HAL_Flash_Register(HAL_Flash_Interface_t *ops, void *userData)
{    
    memset(&DeviceFlash, 0, sizeof(DeviceFlash));

    DeviceFlash.Ops.Erase          = ops->Erase;
    DeviceFlash.Ops.Lock           = ops->Lock;
    DeviceFlash.Ops.Unlock         = ops->Unlock;
    DeviceFlash.Ops.ReadWord       = ops->ReadWord;
    DeviceFlash.Ops.WriteWord      = ops->WriteWord;
    DeviceFlash.Ops.GetFlag        = ops->GetFlag;
    
    DeviceFlash.Parent.UserData    = userData;

#ifdef ENABLE_HAL_DRIVER_COMPONENT
    HAL_Interface_t halDevOps;
    
    halDevOps.Init    = NULL;
    halDevOps.Fini    = NULL;
    halDevOps.Open    = NULL;
    halDevOps.Close   = NULL;
    halDevOps.Write   = NULL;
    halDevOps.Read    = NULL;
    halDevOps.Control = NULL;
    
    HAL_Device_Register(&DeviceFlash.Parent, HAL_VEEPROM_STR, &halDevOps, HAL_Flag_Encode(HAL_DEVICE_FLASH, HAL_READ_FLAG | HAL_WRITE_FLAG));
#endif
}

void HAL_Flash_Init(HAL_Flash_t *flash, HAL_Flash_Config_t *config)
{
    size_t space = config->Atrribute.PageEnd - config->Atrribute.PageBase;

    memset(flash, 0, sizeof(HAL_Flash_t));

    flash->PhyInfo.PageBase = config->Atrribute.PageBase;
    flash->PhyInfo.PageEnd  = config->Atrribute.PageEnd;
    flash->PhyInfo.PageSize = config->Atrribute.PageSize;
    
    flash->BlockNum         = space / config->Atrribute.PageSize;
    
    flash->Buffer           = config->Buffer;
    flash->BufferLen        = config->BufferLen;
    
    flash->Dev              = &DeviceFlash.Parent;
    
    if (IS_PTR_NULL(flash->Buffer))
    {
        return;
    }
    else if (flash->BufferLen % 4 || flash->BufferLen == 0)
    {
        return;
    }
    else if (flash->PhyInfo.PageSize < flash->BufferLen)
    {
        return;
    }
    
    flash_unlock();
    
    flash_load_data(flash);
    
    flash_lock();
    
    flash->Atrribute.State = HAL_FLASH_IDLE;
}

uint8_t HAL_Flash_WriteByte(HAL_Flash_t *flash, uint16_t addr, uint8_t ch)
{
    HAL_Atom_Begin();
    
    if (flash->Buffer[addr] != ch)
    {
        flash->Buffer[addr] = ch;
        HAL_Evt_Set(flash->Atrribute.Event, HAL_FLASH_UPDATE_EVENT);
    }

    HAL_Atom_End();
    
    return 1;
}

uint16_t HAL_Flash_Write(HAL_Flash_t *flash, uint8_t *buf, uint16_t addr, uint16_t len)
{
    HAL_Atom_Begin();
    
    uint16_t i;
    uint8_t *p = (uint8_t *)&flash->Buffer[addr];
    
    for (i=0; i<len; i++)
    {
        if (p[i] != buf[i])
        {
            p[i] = buf[i];
            HAL_Evt_Set(flash->Atrribute.Event, HAL_FLASH_UPDATE_EVENT);
        }
    }

    HAL_Atom_End();
    
    return len;
}

uint8_t HAL_Flash_ReadByte(HAL_Flash_t *flash, uint32_t addr)
{
    uint8_t read;

    read = flash->Buffer[addr];

    return read;
}

uint16_t HAL_Flash_Read(HAL_Flash_t *flash, uint8_t *buf, uint16_t addr, uint16_t len)
{
    uint16_t i;
    uint8_t *p = (uint8_t *)&flash->Buffer[addr];
    
    for (i=0; i<len; i++)
    {
        buf[i] = p[i];
    }

    return len;
}

uint8_t HAL_Flash_Update(void *param)
{
    HAL_Flash_t *flash = (HAL_Flash_t *)param;
    uint8_t ret = 1;
    
    HAL_Atom_Begin();
    
    switch (flash->Atrribute.State)
    {
        case HAL_FLASH_IDLE:
        {
            if (HAL_Evt_Get(flash->Atrribute.Event, HAL_FLASH_UPDATE_EVENT))
            {
                HAL_Evt_Clr(flash->Atrribute.Event, HAL_FLASH_UPDATE_EVENT);
                
                flash_unlock();
                flash->Addr = flash->PhyInfo.PageBase;
                
                flash->Atrribute.State = HAL_FLASH_ERASE;
            }
            else
            {
                ret = 0;
            }
            break;
        }
        case HAL_FLASH_ERASE:
        {
            flash_erase(flash->Addr);
            flash->Atrribute.State = HAL_FLASH_ERASE_WAIT;
            break;
        }
        case HAL_FLASH_ERASE_WAIT:
        {
            uint8_t state = flash_get_flag(HAL_FLASH_ERASE_FLAG, 0, 0);
            
            //! 写入成功
            if (state == 0)
            {
                flash->Addr += flash->PhyInfo.PageSize;
                
                if (flash->Addr >= flash->PhyInfo.PageEnd)
                {
                    flash->Addr = flash->PhyInfo.PageBase;
                    flash->Atrribute.State = HAL_FLASH_WRITE;
                }
                else
                {
                    flash->Atrribute.State = HAL_FLASH_ERASE;
                }
            }
            //! 写入失败
            else if (state == 2)
            {
                flash->Atrribute.State = HAL_FLASH_HW_ERROR;
            }
            break;
        }
        case HAL_FLASH_WRITE:
        {
            uint32_t pos = flash->Addr - flash->PhyInfo.PageBase;
            uint32_t wrData = *((uint32_t *)&flash->Buffer[pos]);
            flash_write_word(flash->Addr, wrData);
            
            flash->Atrribute.State = HAL_FLASH_WRITE_WAIT;
            break;
        }
        case HAL_FLASH_WRITE_WAIT:
        {
            uint8_t state = flash_get_flag(HAL_FLASH_WRITE_FLAG, 0, 0);
            uint32_t pos = flash->Addr - flash->PhyInfo.PageBase;
            uint32_t wrData = *((uint32_t *)&flash->Buffer[pos]);
            
            if (state == 0)
            {
                //! 校验成功
                if (flash_get_flag(HAL_FLASH_VERIFY_FLAG, flash->Addr, wrData) == 0)
                {
                    flash->Addr += HAL_FLASH_ALIGNMENT;
                    
                    if (flash->Addr > flash->PhyInfo.PageEnd - 4)
                    {
                        flash->Addr = 0;
                        
                        flash_lock();
                        flash->Atrribute.State = HAL_FLASH_IDLE;
                    }
                    else
                    {
                        flash->Atrribute.State = HAL_FLASH_WRITE;
                    }
                }
                //! 校验失败
                else
                {
                    flash->Atrribute.State = HAL_FLASH_WRITE;
                }
            }
            //! 写入失败
            else if (state == 2)
            {
                flash->Atrribute.State = HAL_FLASH_HW_ERROR;
            }
            break;
        }
        default:
            break;
    }
    
    HAL_Atom_End();
    
    return ret;
}
#endif

/** @}*/     /** hal flash driver component */

/**********************************END OF FILE*********************************/
