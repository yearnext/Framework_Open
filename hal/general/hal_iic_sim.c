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
 * @file       hal_iic_sim.c                                                   *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-10-31                                                      *
 * @brief      hal iic simulation component source file                        *
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
* @defgroup hal iic simulation component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "hal_iic_sim.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define IIC_SDA_HIGH(ops) _st(ops->SDA(ops->Handle, 1);)
#define IIC_SDA_LOW(ops)  _st(ops->SDA(ops->Handle, 0);)
#define IIC_SDA(ops, b)   _st(ops->SDA(ops->Handle, b);)
#define IIC_SDA_GET(ops)  ops->GetSDA(ops->Handle)

#define IIC_SCL_LOW(ops)  _st(ops->SCL(ops->Handle, 0);)
#define IIC_SCL(ops, b)   _st(ops->SCL(ops->Handle, b);)
#define IIC_SCL_GET(ops)  ops->GetSCL(ops->Handle)

#define IIC_DELAY1(ops)   _st(ops->Delay((ops->DelayTick + 1) >> 1);)
#define IIC_DELAY2(ops)   _st(ops->Delay(ops->DelayTick);)

#define IIC_WAIT(ops)     (ops->Wait(ops->Timeout))

/* Private constants ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
__STATIC_INLINE
uint8_t IIC_SCL_HIGH(HAL_IIC_SimDevice_t *ops)
{
    IIC_SCL_HIGH(ops);

	if (IS_PTR_NULL(ops->GetSCL))
	{
		IIC_DELAY1(ops);
		
		return 0;
	}

    while (IIC_SCL_GET(ops) == 0)
    {
		if (IIC_WAIT(ops) == 0)
		{
			return 2;
		}
    }
	
	return 0;
}

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      IIC START SIGNAL
 * @note       时序图
 * SDA:
 *             -----
 *                 |
 *                 |
 *                 -----
 * SCL:
 *             -----
 *                 |
 *                 |
 *                 -----
 *******************************************************************************
 */
void iic_start(HAL_IIC_SimDevice_t *ops)
{
    IIC_SDA_LOW(ops);
    IIC_DELAY1(ops);
    IIC_SCL_LOW(ops);
}

void iic_restart(HAL_IIC_SimDevice_t *ops)
{
    IIC_SDA_HIGH(ops);
    IIC_SCL_HIGH(ops);
    IIC_DELAY1(ops);
	
    IIC_SDA_LOW(ops);
    IIC_DELAY1(ops);
    IIC_SCL_LOW(ops);
}

/**
 *******************************************************************************
 * @brief      IIC STOP SIGNAL
 * @note       时序图
 * SDA:
 *                  -----
 *                  |
 *                  |
 *              -----
 * SCL:
 *                -----
 *                |
 *                |
 *             ----
 *******************************************************************************
 */
void iic_stop(HAL_IIC_SimDevice_t *ops)
{
    IIC_SDA_LOW(ops);
    IIC_DELAY1(ops);
	
    IIC_SCL_HIGH(ops);
    IIC_DELAY1(ops);
	
    IIC_SDA_HIGH(ops);
    IIC_DELAY2(ops);
}

uint8_t iic_wait_ack(HAL_IIC_SimDevice_t *ops)
{
    uint8_t ack;

    IIC_SDA_HIGH(ops);
    IIC_DELAY1(ops);

    if (IIC_SCL_HIGH(ops))
    {
        return 2;
    }

    ack = IIC_SDA_GET(ops) ? (0) : (1);    /* ACK : SDA pin is pulled low */

    IIC_SCL_LOW(ops);

    return ack;
}

uint8_t iic_send_ack_or_nack(HAL_IIC_SimDevice_t *ops, uint8_t ack)
{
    if (ack)
	{
        IIC_SDA_LOW(ops);
	}
	
    IIC_DELAY1(ops);
    
	if (IIC_SCL_HIGH(ops))
    {
        return 2;
    }
	
    IIC_SCL_LOW(ops);

    return 0;
}

uint8_t iic_tr_write_byte(HAL_IIC_SimDevice_t *ops, uint8_t wr)
{
	int8_t i;
	
    for (i=7; i>0; i--)
    {
        IIC_SCL_LOW(ops);		
		IIC_SDA(ops, _read_bit(wr, i));
		IIC_DELAY1(ops);

        if (IIC_SCL_HIGH(ops))
        {
            return 2;
        }
    }
    IIC_SCL_LOW(ops);
    IIC_DELAY1(ops);

    return iic_wait_ack(ops);
}

uint8_t iic_tr_read_byte(HAL_IIC_SimDevice_t *ops)
{
	int8_t i;
	uint8_t rd = 0;
	
    IIC_SDA_HIGH(ops);
    IIC_DELAY1(ops);
	
    for (i=7; i>=0; i--)
    {
        if (IIC_SCL_HIGH(ops))
        {
            return 2;
        }

        if (IIC_SDA_GET(ops))
		{
			_set_bit(rd, i);
		}

        IIC_SCL_LOW(ops);
        IIC_DELAY2(ops);
    }

    return rd;
}

#undef IIC_SDA_HIGH
#undef IIC_SDA_LOW
#undef IIC_SDC_GET
#undef IIC_SCL_LOW
#undef IIC_SCL_GET
#undef IIC_DELAY1
#undef IIC_DELAY2

/** @}*/     /** hal iic simulation component */

/**********************************END OF FILE*********************************/
