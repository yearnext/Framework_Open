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
 * @file       hal_flash.h                                                     *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-10-27                                                      *
 * @brief      mcu flash driver component server head file                     *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 20171027    创建文件"veeprom.h"                                          *
 * 2. 20180829    简化veeprom组件，更名为"hal_flash.h"                         *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_FLASH_H__
#define __HAL_FLASH_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
//! define flash state
enum __HAL_FLASH_STATE
{
    HAL_FLASH_INIT = 0,
    
    HAL_FLASH_IDLE,
    HAL_FLASH_ERASE,
    HAL_FLASH_ERASE_WAIT,
    HAL_FLASH_WRITE,
    HAL_FLASH_WRITE_WAIT,
    
    HAL_FLASH_HW_ERROR,
};

//! flash driver event
#define HAL_FLASH_UPDATE_EVENT                                               (0)

//! flash driver 标识
#define HAL_FLASH_LOCK_FLAG                                             (0x0001)
#define HAL_FLASH_VERIFY_FLAG                                           (0x0002)
#define HAL_FLASH_ERASE_FLAG                                            (0x0004)
#define HAL_FLASH_WRITE_FLAG                                            (0x0008)

/* Exported types ------------------------------------------------------------*/
//! Veeprom 硬件操作接口
typedef struct 
{
    uint32_t (*ReadWord)(uint32_t addr);
    void     (*WriteWord)(uint32_t addr, uint32_t wdata);
    void     (*Erase)(uint32_t addr);
    void     (*Lock)(void);
    void     (*Unlock)(void);
    uint32_t (*GetFlag)(uint32_t flag, uint32_t addr, uint32_t vData);
}HAL_Flash_Interface_t;

typedef struct
{
    //! 页物理地址
    size_t PageBase;
    size_t PageEnd;
    //! 物理页大小
    size_t PageSize;
}HAL_FlashInfo_t;

typedef struct
{
    HAL_FlashInfo_t Atrribute;
    
    //! RAM缓冲区
    volatile uint8_t *Buffer;
    
    //! EEPROM空间
    uint16_t BufferLen;
}HAL_Flash_Config_t;

typedef struct
{
    HAL_Atrribute_t Atrribute;
    HAL_FlashInfo_t PhyInfo;
    
    //! 写入地址
    size_t   Addr;
    
    //! 设备句柄
    HAL_Device_t *Dev;
    
    //! RAM缓冲区
    volatile uint8_t *Buffer;
    
    //! Flash空间
    uint16_t BufferLen;
    
    //! 块数量
    uint16_t BlockNum;

    //! 页状态
    uint8_t PageState;
}HAL_Flash_t;

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern void     HAL_Flash_Register(HAL_Flash_Interface_t *ops, void *userData);
extern void     HAL_Flash_Init(HAL_Flash_t *eeprom, HAL_Flash_Config_t *config);

extern uint8_t  HAL_Flash_WriteByte(HAL_Flash_t *eeprom, uint16_t addr, uint8_t ch);
extern uint16_t HAL_Flash_Write(HAL_Flash_t *eeprom, uint8_t *buf, uint16_t addr, uint16_t len);
extern uint8_t  HAL_Flash_ReadByte(HAL_Flash_t *eeprom, uint32_t addr);
extern uint16_t HAL_Flash_Read(HAL_Flash_t *eeprom, uint8_t *buf, uint16_t addr, uint16_t len);

extern uint8_t  HAL_Flash_Update(void *param);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
