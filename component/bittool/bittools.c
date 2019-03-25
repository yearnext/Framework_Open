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
 * @file       bittools.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-09-17                                                      *
 * @brief      bit tool component source files                                 *
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
 * @defgroup bit tool component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "bittools.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       bit map
 *******************************************************************************
 */
uint8_t __CONST _BitMap[] =
{
    /* 00 */ 0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 10 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 20 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 30 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 40 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 50 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 60 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 70 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 80 */ 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 90 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* A0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* B0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* C0 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* D0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* E0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* F0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
};

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       set memory is used
 * @param       [in/out]  offset      memory id
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void BitMapClr(uint8_t offset, uint8_t *tab, uint32_t *group)
{
    uint8_t l = offset / 8;
    uint8_t r = offset % 8;

    tab[l] &= ~(1 << r);
    
    if(tab[l] == 0x00)
    {
        *group &= ~(1 << l);
    }
}

/**
 *******************************************************************************
 * @brief       set memory is unused
 * @param       [in/out]  offset      memory id
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void BitMapSet(uint8_t offset, uint8_t *tab, uint32_t *group)
{
    uint8_t l = offset / 8;
    uint8_t r = offset % 8;
    
    tab[l] |= 1 << r;
    *group |= 1 << l;
}

/**
 *******************************************************************************
 * @brief       get free memory address
 * @param       [in/out]  void
 * @return      [in/out]  address    event space address
 * @note        None
 *******************************************************************************
 */
__INLINE
uint8_t BitMapGet(uint8_t *tab, uint32_t group)
{
    uint32_t temp;
    uint8_t x;
    uint8_t y;
    uint8_t prio;
    
    if ((temp = group & 0xFFUL) != 0UL)
    {
        x = _BitMap[temp];
    }
    else if ((temp = (group & 0xFF00UL) >> 8) != 0UL)
    {
        x = _BitMap[temp] + 8;
    }
    else if ((temp = (group & 0xFF0000UL) >> 16) != 0UL)
    {
        x = _BitMap[temp] + 16;
    }
    else if ((temp = (group & 0xFF00000UL) >> 24) != 0UL)
    {
        x = _BitMap[temp] + 24;
    }
    else
    {
        return 0xFF;
    }
    
    y = _BitMap[tab[x]];
    prio = (x << 3) | y;

    return prio;
}

/**
 *******************************************************************************
 * @brief       get free memory address
 * @param       [in/out]  void
 * @return      [in/out]  address    event space address
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t ByteExchange(uint16_t halfWord)
{
    uint16_t ret = halfWord << 8;
    
    ret |= halfWord >> 8;
    
    return ret;
}

/**
 *******************************************************************************
 * @brief       get free memory address
 * @param       [in/out]  void
 * @return      [in/out]  address    event space address
 * @note        None
 *******************************************************************************
 */
__INLINE
void ByteOrderExchange(uint16_t *buf,uint16_t dataLen)
{
    uint16_t i = 0;

    for(i=0; i<dataLen; i++)
    {
        buf[i] = ByteExchange(buf[i]);
    }
}

/** @}*/     /** bit tool component */

/**********************************END OF FILE*********************************/
