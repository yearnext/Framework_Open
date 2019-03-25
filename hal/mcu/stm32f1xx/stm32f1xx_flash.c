/**
 *******************************************************************************
 * @file       stm32f1xx_flash.c                                               *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-01-16                                                      *
 * @brief      stm32f1xx flash driver component                                *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
 
/**
 * @defgroup stm32f1xx flash driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_msp.h"

/* Private define ------------------------------------------------------------*/
#define MCU_EEPROM_BASE_ADDR 0x08080000UL
#define MCU_EEPROM_END_ADDR  0x0808FFFFUL

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
//! ªÒ»°Flashµÿ÷∑ª∫¥Ê
void MCU_EEPROM_Init(void)
{
}

void MCU_EEPROM_WriteByte(uint8_t addr, uint8_t wByte)
{
    HAL_FLASHEx_DATAEEPROM_Unlock();
    HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, MCU_EEPROM_BASE_ADDR+addr, wByte);
    HAL_FLASHEx_DATAEEPROM_Lock();
}

uint8_t MCU_EEPROM_ReadByte(uint8_t addr)
{
    uint8_t *rdBuf = (uint8_t *)(MCU_EEPROM_BASE_ADDR + addr);  
    return *rdBuf;
}

void MCU_EEPROM_WriteHalfWord(uint8_t addr, uint16_t wHalfword)
{
    HAL_FLASHEx_DATAEEPROM_Unlock();
    HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_HALFWORD, MCU_EEPROM_BASE_ADDR+addr, wHalfword);
    HAL_FLASHEx_DATAEEPROM_Lock();
}

uint16_t MCU_EEPROM_ReadHalfWord(uint8_t addr)
{
    uint16_t *rdBuf = (uint16_t *)(MCU_EEPROM_BASE_ADDR + addr);  
    return *rdBuf;
}

void MCU_EEPROM_WriteWord(uint8_t addr, uint32_t wWord)
{
    HAL_FLASHEx_DATAEEPROM_Unlock();
    HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, MCU_EEPROM_BASE_ADDR+addr, wWord);
    HAL_FLASHEx_DATAEEPROM_Lock();
}

uint32_t MCU_EEPROM_ReadWord(uint8_t addr)
{
    uint32_t *rdBuf = (uint32_t *)(MCU_EEPROM_BASE_ADDR + addr);  
    return *rdBuf;
}

uint16_t MCU_EEPROM_Write(uint8_t addr, uint8_t *wBuf, uint8_t len)
{
    uint8_t i;
    
    HAL_FLASHEx_DATAEEPROM_Unlock();
    
    for (i=0; i<len; i++)
    {
        HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, MCU_EEPROM_BASE_ADDR+addr+i, wBuf[i]);
    }
    
    HAL_FLASHEx_DATAEEPROM_Lock();
    
    return len;
}

uint16_t MCU_EEPROM_Read(uint8_t addr, uint8_t *rBuf, uint8_t len)
{
    uint8_t *rdBuf = (uint8_t *)(MCU_EEPROM_BASE_ADDR + addr);
    uint8_t i;
    
    for (i=0; i<len; i++)
    {
        rBuf[i] = rdBuf[i];
    }
    
    return len;
}

uint16_t hal_eeprom_write(uint16_t dev, uint16_t pos, uint8_t *buf, uint16_t len)
{
    uint8_t i;
    
    HAL_FLASHEx_DATAEEPROM_Unlock();
    
    for (i=0; i<len; i++)
    {
        HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, MCU_EEPROM_BASE_ADDR+pos+i, buf[i]);
    }
    
    HAL_FLASHEx_DATAEEPROM_Lock();
    
    return len;
}

uint16_t hal_eeprom_read(uint16_t dev, uint16_t pos, uint8_t *buf, uint16_t len)
{
    uint8_t *rdBuf = (uint8_t *)(MCU_EEPROM_BASE_ADDR + pos);
    uint8_t i;
    
    for (i=0; i<len; i++)
    {
        buf[i] = rdBuf[i];
    }
    
    return len;
}

/** @}*/     /** stm32f1xxstm32f1xx flash driver component */

/**********************************END OF FILE*********************************/
