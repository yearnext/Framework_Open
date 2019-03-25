/**
 *******************************************************************************
 *                 Copyright (C) 2017 - 2018  Accumulate Team                  *
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
 * @file       crc.c                                                           *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-09-17                                                      *
 * @brief      crc component source files                                      *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
 *******************************************************************************
 */

/**
 * @defgroup crc component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "crc.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      CRC7计算
 *******************************************************************************
 */
uint8_t Crc7_Cal(uint8_t *in, uint16_t len)
{
    uint16_t i,j;
    uint8_t chCRC = 0;
    uint8_t value = CRC7_INIT;
    
    if (IS_PTR_NULL(in))
    {
        return 0;
    }

    for (i=0; i<len; i++) 
    {
        chCRC = (*in++) ^ (value << 1);
        
        for (j=0; j<7; j++) 
        {
            if (chCRC & 0x80) 
            {
                chCRC ^= CRC7_POLY;
            } 
            
            chCRC <<= 1;
        }
        
        if (chCRC & 0x80) 
        {
            chCRC ^= CRC7_POLY;
        } 
        
        value = chCRC;
    }

    return value;
}

/**
 *******************************************************************************
 * @brief      CRC8计算
 *******************************************************************************
 */
static uint32_t crc8_data_reversal(uint32_t wValue, uint8_t chLength)
{
    uint8_t i;
    uint32_t wTempValue = 0;

    for (i = 1; i < (chLength + 1); i++)
    {
        if (wValue & 0x01)
        {
            wTempValue |= ((uint32_t)1 << (chLength - i));
        }
        
        wValue >>= 1;
    }

    return wTempValue;
}

uint8_t Crc8_Cal(uint8_t *in, uint16_t len)
{
    uint16_t i,j;
    uint8_t chCRC = 0;
    uint8_t value = CRC8_INIT;
    
    if (IS_PTR_NULL(in))
    {
        return 0;
    }

    for (i=0; i<len; i++)
    {
        chCRC = (*in++) ^ (value);
        
        for (j = 0; j < 8; j++) 
        {
            if (chCRC & 0x80) 
            {
                chCRC <<= 1;
                chCRC ^= CRC8_POLY;
            }
            else
            {
                chCRC <<= 1;
            }
        }
        
        value = chCRC;
    }

    return value;
}

uint8_t Crc8_Rohc_Cal(uint8_t *in, uint16_t len)
{
    uint16_t i,j;
    uint8_t chCRC = 0;
    uint8_t value = CRC8_ROHC_INIT;
    
    if (IS_PTR_NULL(in))
    {
        return 0;
    }

    for (i = 0; i < len; i++)
    {
        chCRC = (value) ^ (*in++);
        chCRC = (uint8_t)crc8_data_reversal(chCRC, 8);

        for (j = 0; j < 8; j++) 
        {
            if (chCRC & 0x80) 
            {
                chCRC <<= 1;
                chCRC ^= CRC8_ROHC_POLY;
            }
            else
            {
                chCRC <<= 1;
            }
        }

        chCRC = (uint8_t)crc8_data_reversal(chCRC, 8);        
        value = chCRC;
    }

    return value;
}

/**
 *******************************************************************************
 * @brief      CRC16计算
 *******************************************************************************
 */
static uint32_t crc16_data_reversal(uint32_t wValue, uint8_t chLength)
{
    uint8_t i;
    uint32_t wTempValue = 0;

    for (i = 1; i < (chLength + 1); i++) 
    {
        if (wValue & 0x01) 
        {
            wTempValue |= ((uint32_t)1 << (chLength - i));
        }
        wValue >>= 1;
    }

    return wTempValue;
}

uint16_t Crc16_Usb_Cal(uint16_t *in, uint16_t len)
{
    uint16_t i,j;
    uint16_t chCRC = 0;
    uint16_t value = CRC16_USB_INIT;
    
    if (IS_PTR_NULL(in))
    {
        return 0;
    }

    for (i=0; i<len; i++)
    {
        chCRC = ((value) ^ (*in++)) & 0x00FF;        
        chCRC = (uint16_t)crc16_data_reversal(chCRC, 16);
        
        for (j = 0; j < 8; j++) 
        {
            if (chCRC & 0x8000) 
            {
                chCRC <<= 1;
                chCRC ^= CRC16_POLY;
            } 
            else
            {
                chCRC <<= 1;
            }
        }
        
         chCRC = (uint16_t)crc16_data_reversal(chCRC, 16);
        value = (value >> 8) ^ chCRC;
    }

    return (value = ~(value));
}

__STATIC_INLINE
uint16_t Crc16SingleCal(uint8_t crcbuf, uint16_t crc)
{
	uint8_t i; 
	uint8_t chk;
    
	crc = crc ^ crcbuf;
    
	for(i=0; i<8; i++)
	{
        chk = crc & 1;
        crc = crc >> 1;
        crc = crc & 0x7FFF;
        if (chk)
        {
            crc = crc ^ 0xA001;
        }

        crc = crc & 0xFFFF;
	}
	return crc; 
}

uint16_t Crc16_Cal(uint8_t *ptr, uint16_t Length)
{
	uint8_t hi,lo;
	uint8_t i;
    uint16_t crc = 0xFFFF;
    
	for (i=0; i<Length; i++)
	{
	   crc = Crc16SingleCal(ptr[i], crc);
	}
    
	hi = crc % 256;
	lo = crc / 256;
	crc = (hi<<8) | lo;
    
	return crc;
}

uint16_t Crc16_Modbus_Cal(uint16_t *in, uint16_t len)
{
    uint16_t i,j;
    uint16_t chCRC = 0;
    uint16_t value = CRC16_MODBUS_INIT;
    
    if (IS_PTR_NULL(in))
    {
        return 0;
    }

    for (i=0; i<len; i++) 
    {
        chCRC = ((value) ^ (*in++)) & 0x00FF;        
        chCRC = (uint16_t)crc16_data_reversal(chCRC, 16);
        
        for (j = 0; j < 8; j++) 
        {
            if (chCRC & 0x8000) 
            {
                chCRC <<= 1;
                chCRC ^= CRC16_POLY;
            } 
            else 
            {
                chCRC <<= 1;
            }
        }
        
        chCRC = (uint16_t)crc16_data_reversal(chCRC, 16);
        value = (value >> 8) ^ chCRC;
    }

    return value;
}

uint16_t Crc16_CCITT_Cal(uint16_t *in, uint16_t len)
{
    uint16_t i,j;
    uint16_t chCRC = 0;
    uint16_t value = CRC16_INIT;

    if (IS_PTR_NULL(in))
    {
        return 0;
    }

    for (i=0; i<len; i++) 
    {
        chCRC = ((uint16_t)(*in++) << 8) ^ (value & 0xFF00);
        for (j = 0; j < 8; j++)
        {
            if (chCRC & 0x8000)
            {
                chCRC <<= 1;
                chCRC ^= CRC16_CCITT_FALSE_POLY;
            }
            else
            {
                chCRC <<= 1;
            }
        }
        value = (value << 8) ^ chCRC;
    }

    return value;
}

uint16_t Crc16_Modem_Cal(uint16_t *in, uint16_t len)
{
    uint16_t i,j;
    uint16_t chCRC = 0;
    uint16_t value = CRC16_MODEM_INIT;

    if (IS_PTR_NULL(in))
    {
        return 0;
    }
    
    for (i=0; i<len; i++) 
    {
        chCRC = ((uint16_t)(*in++) << 8) ^ (value & 0xFF00);
        
        for (j = 0; j < 8; j++) 
        {
            if (chCRC & 0x8000) 
            {
                chCRC <<= 1;
                chCRC ^= CRC16_CCITT_FALSE_POLY;
            } 
            else 
            {
                chCRC <<= 1;
            }
        }
        
        value = (value << 8) ^ chCRC;
    }

    return value;
}

/**
 *******************************************************************************
 * @brief      CRC32计算
 *******************************************************************************
 */
static uint32_t crc32_data_reversal(uint32_t wValue, uint8_t chLength)
{
    uint8_t i;
    uint32_t wTempValue = 0;

    for (i = 1; i < (chLength + 1); i++)
    {
        if (wValue & 0x01)
        {
            wTempValue |= ((uint32_t)1 << (chLength - i));
        }
        
        wValue >>= 1;
    }

    return wTempValue;
}

uint32_t Crc32_Cal(uint32_t *in, uint16_t len)
{
    uint16_t i,j;
    uint32_t chCRC = 0;
    uint32_t value = CRC32_INIT;

    if (IS_PTR_NULL(in))
    {
        return 0;
    }

    for (i=0; i<len; i++)
    {
        chCRC = ((value) ^ (*in++)) & 0x000000FF;        
        chCRC = crc32_data_reversal(chCRC, 32);
        for (j = 0; j < 8; j++)
        {
            if (chCRC & 0x80000000)
            {
                chCRC <<= 1;
                chCRC ^= CRC32_POLY;
            } 
            else
            {
                chCRC <<= 1;
            }
        }
        
        chCRC = crc32_data_reversal(chCRC, 32);
        value = (value >> 8) ^ chCRC;
    }

    return (value = ~value);
}

uint32_t Crc32_IEEE802_3_Cal(uint32_t *in, uint16_t len)
{
    uint16_t i,j;
    uint32_t chCRC = 0;
    uint32_t value = CRC32_INIT;
    
    if (IS_PTR_NULL(in))
    {
        return 0;
    }
    
    for (i=0; i<len; i++)
    {
        chCRC = ((uint32_t)(*in++) << 24) ^ (value & 0xFF000000);
        for (j = 0; j < 8; j++)
        {
            if (chCRC & 0x80000000) 
            {
                chCRC <<= 1;
                chCRC ^= CRC32_IEEE802_3_POLY;
            } 
            else
            {
                chCRC <<= 1;
            }
        }
        value = (value << 8) ^ chCRC;
    }

    return value;
}

/** @}*/     /** crc component */

/**********************************END OF FILE*********************************/
