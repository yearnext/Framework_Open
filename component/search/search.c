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
 * @file       serach.c                                                        *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-10-24                                                      *
 * @brief      serach component source file                                    *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20181024    创建文件                                                      *
 *******************************************************************************
 */
 
/**
* @defgroup serach component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "search.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       常规查表算法
 *******************************************************************************
 */
__INLINE
uint16_t NormalSearchU8(uint8_t in, const uint8_t *tab, uint16_t len)
{
	uint16_t i;
	uint8_t now, next;

    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);
    
    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now = tab[i];
                next = tab[i + 1];

                if (in >= now && in < next)
                {
                    return i;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now  = tab[i];
                next = tab[i + 1];

                if (in <= now && in > next)
                {
                    return i;
                }
            }
        }
    }
    
    return len;
}

__INLINE
uint16_t NormalSearchS8(int8_t in, const int8_t *tab, uint16_t len)
{
	uint16_t i;
	int8_t now, next;

    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);
    
    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now = tab[i];
                next = tab[i + 1];

                if (in >= now && in < next)
                {
                    return i;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now  = tab[i];
                next = tab[i + 1];

                if (in <= now && in > next)
                {
                    return i;
                }
            }
        }
    }
    
    return len;
}

__INLINE
uint16_t NormalSearchU16(uint16_t in, const uint16_t *tab, uint16_t len)
{
	uint16_t i;
	uint16_t now, next;

    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);
    
    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now = tab[i];
                next = tab[i + 1];

                if (in >= now && in < next)
                {
                    return i;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now  = tab[i];
                next = tab[i + 1];

                if (in <= now && in > next)
                {
                    return i;
                }
            }
        }
    }
    
    return len;
}

__INLINE
uint16_t NormalSearchS16(int16_t in, const int16_t *tab, uint16_t len)
{
	uint16_t i;
	int16_t now, next;

    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);
    
    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now = tab[i];
                next = tab[i + 1];

                if (in >= now && in < next)
                {
                    return i;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now  = tab[i];
                next = tab[i + 1];

                if (in <= now && in > next)
                {
                    return i;
                }
            }
        }
    }

    return len;
}

__INLINE
uint16_t NormalSearchU32(uint32_t in, const uint32_t *tab, uint16_t len)
{
	uint16_t i;
	uint32_t now, next;

    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);
    
    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now = tab[i];
                next = tab[i + 1];

                if (in >= now && in < next)
                {
                    return i;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now  = tab[i];
                next = tab[i + 1];

                if (in <= now && in > next)
                {
                    return i;
                }
            }
        }
    }
    
    return len;
}

__INLINE
uint16_t NormalSearchS32(int32_t in, const int32_t *tab, uint16_t len)
{
	uint16_t i;
	int32_t now, next;
    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);
    
    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now = tab[i];
                next = tab[i + 1];

                if (in >= now && in < next)
                {
                    return i;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                now  = tab[i];
                next = tab[i + 1];

                if (in <= now && in > next)
                {
                    return i;
                }
            }
        }
    }
    
    return len;
}

/**
 *******************************************************************************
 * @brief       二分查表算法
 *******************************************************************************
 */
__INLINE
uint16_t BinarySearchU8(uint8_t in, const uint8_t *tab, uint16_t len)
{
	uint16_t out = len >> 1;
	uint16_t offset = out;
	uint8_t now, next;
    
    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);

    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in >= now && in < next)
                {
                    return out;
                }
                else if (in > now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in <= now && in > next)
                {
                    return out;
                }
                else if (in < now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
}

__INLINE
uint16_t BinarySearchS8(int8_t in, const int8_t *tab, uint16_t len)
{
	uint16_t out = len >> 1;
	uint16_t offset = out;
	int8_t now, next;

    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);

    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in >= now && in < next)
                {
                    return out;
                }
                else if (in > now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in <= now && in > next)
                {
                    return out;
                }
                else if (in < now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
}

__INLINE
uint16_t BinarySearchU16(uint16_t in, const uint16_t *tab, uint16_t len)
{
	uint16_t out = len >> 1;
	uint16_t offset = out;
	uint16_t now, next;

    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);

    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in >= now && in < next)
                {
                    return out;
                }
                else if (in > now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in <= now && in > next)
                {
                    return out;
                }
                else if (in < now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
}

__INLINE
uint16_t BinarySearchS16(int16_t in, const int16_t *tab, uint16_t len)
{
	uint16_t out = len >> 1;
	uint16_t offset = out;
	int16_t now, next;
    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);

    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in >= now && in < next)
                {
                    return out;
                }
                else if (in > now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in <= now && in > next)
                {
                    return out;
                }
                else if (in < now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
}

__INLINE
uint16_t BinarySearchU32(uint32_t in, const uint32_t *tab, uint16_t len)
{
	uint16_t out = len >> 1;
	uint16_t offset = out;
	uint32_t now, next;

    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);

    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in >= now && in < next)
                {
                    return out;
                }
                else if (in > now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in <= now && in > next)
                {
                    return out;
                }
                else if (in < now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
}

__INLINE
uint16_t BinarySearchS32(int32_t in, const int32_t *tab, uint16_t len)
{
	uint16_t out = len >> 1;
	uint16_t offset = out;
	int32_t now, next;

    uint8_t dir = (tab[0] > tab[1]) ? (1) : (0);

    //! 数据为从小到大
    if (dir == 0)
    {
        if (in <= tab[0])
        {
            return 0;
        }
        else if (in >= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in >= now && in < next)
                {
                    return out;
                }
                else if (in > now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
    //! 数据为从大到小
    else
    {
        if (in >= tab[0])
        {
            return 0;
        }
        else if (in <= tab[len-1])
        {
            return len-1;
        }
        else
        {
            while (1)
            {
                now  = tab[out];
                next = tab[out + 1];

                if (in <= now && in > next)
                {
                    return out;
                }
                else if (in < now)
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   += offset;
                }
                else
                {
                    offset = (offset <= 1) ? (1) : (offset >> 1);
                    out   -= offset;
                }
            }
        }
    }
}

/** @}*/     /** serach component */

/**********************************END OF FILE*********************************/
