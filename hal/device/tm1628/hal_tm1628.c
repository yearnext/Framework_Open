/**
 *******************************************************************************
 * @file       hal_tm1628.c                                                    *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-09-25                                                      *
 * @brief      tm1628 driver component source file                             *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 20180925 创建文件                                                        *
 *******************************************************************************
 */
 
/**
* @defgroup tm1628 driver component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       TM1628 IO功能定义
 *******************************************************************************
 */
//! IO功能定义
#define DEV_TM1628_ENABLE()      dev->Ops.STB_Port(0)
#define DEV_TM1628_DISABLE()     dev->Ops.STB_Port(1)

#define DEV_TM1628_OUT_HIGH()    dev->Ops.DIO_Port(1)
#define DEV_TM1628_OUT_LOW()     dev->Ops.DIO_Port(0)
#define DEV_TM1628_INPUT_PIN()   dev->Ops.DIO_Port(2)

#define DEV_TM1628_CLK_HIGH()    dev->Ops.CLK_Port(1)
#define DEV_TM1628_CLK_LOW()     dev->Ops.CLK_Port(0)

/* Private constants ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void DEV_TM1628_Delay(void)
{
    uint8_t i = 200;
    
    do
    {
        __NOP();
    }while(--i);
}

uint8_t NumToNixieTubeCode(uint8_t num)
{
    uint8_t code[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    
    if (num > 15)
    {
        return 0;
    }
    
    return code[num];
}

uint8_t LevelToNixieTubeCode(uint8_t level)
{
    if (level > 8 || level == 0)
    {
        return 0;
    }
    
    level --;
    
    return (1 << level);
}

void TM1628_Write_Byte(HAL_TM1628_t *dev, uint8_t wr)
{
    uint8_t i;
    
    for (i=0; i<8; i++)
    {
        DEV_TM1628_CLK_LOW();
        
        if (_read_bit(wr, i))
        {
            DEV_TM1628_OUT_HIGH();
        }
        else
        {
            DEV_TM1628_OUT_LOW();
        }
        
        DEV_TM1628_Delay();
        
        DEV_TM1628_CLK_HIGH();
    }
}

uint8_t TM1628_Read_Byte(HAL_TM1628_t *dev)
{
    uint8_t i;
    uint8_t temp = 0;
    
    for (i=0; i<8; i++)
    {
        DEV_TM1628_CLK_HIGH();
        
        if (DEV_TM1628_INPUT_PIN())
        {
            _set_bit(temp, i);
        }
        
        DEV_TM1628_Delay();
        
        DEV_TM1628_CLK_LOW();
    }
    
    return temp;
}

void TM1628_Write_Cmd(HAL_TM1628_t *dev, uint8_t cmd)
{
    DEV_TM1628_ENABLE();
    
    DEV_TM1628_Delay();
    
    TM1628_Write_Byte(dev, cmd);
    
    DEV_TM1628_Delay();
    
    DEV_TM1628_DISABLE();
}

void TM1628_Write_Data(HAL_TM1628_t *dev, uint8_t addr, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    
    DEV_TM1628_ENABLE();
    
    DEV_TM1628_Delay();
    
    TM1628_Write_Byte(dev, addr);
    
    for (i=0; i<len; i++)
    {
        TM1628_Write_Byte(dev, buf[i]);
        DEV_TM1628_Delay();
    }
    
    DEV_TM1628_Delay();
    
    DEV_TM1628_DISABLE();
}

/* Exported functions --------------------------------------------------------*/
void HAL_TM1628_Init(HAL_TM1628_t *dev, TM1628_Interface_t *ops)
{
    memset(dev, 0, sizeof(HAL_TM1628_t));

    if (IS_PTR_NULL(ops) || IS_PTR_NULL(ops->CLK_Port) || IS_PTR_NULL(ops->DIO_Port) || IS_PTR_NULL(ops->STB_Port))
    {
        return ;
    }

    dev->Ops.CLK_Port = ops->CLK_Port;
    dev->Ops.DIO_Port = ops->DIO_Port;
    dev->Ops.STB_Port = ops->STB_Port;
    
    dev->Attribute.State = 1;
}

void HAL_TM1628_WriteBit(HAL_TM1628_t *dev, uint8_t bitPos, uint8_t segPos, uint8_t flag)
{
    bitPos --;
    segPos --;
    
    if (flag)
    {
        _set_bit(dev->Cache[bitPos], segPos);
    }
    else
    {
        _clr_bit(dev->Cache[bitPos], segPos);
    }
}

uint8_t HAL_TM1628_ReadBit(HAL_TM1628_t *dev, uint8_t bitPos, uint8_t segPos)
{
    return 0;
}

void HAL_TM1628_Update(void *param)
{
    HAL_TM1628_t *dev = (HAL_TM1628_t *)param; 
    
    TM1628_Write_Cmd(dev, TM1628_CMD_DRV_6BIT13SEG);
    TM1628_Write_Cmd(dev, TM1628_CMD_ADDR_INC | TM1628_CMD_WRITE);
    TM1628_Write_Data(dev, 0xC0, (uint8_t *)&dev->Cache[0], _dimof(dev->Cache));
    TM1628_Write_Cmd(dev, TM1628_CMD_LUMIN_LV8);
}

/** @}*/     /** tm1628 driver component */

/**********************************END OF FILE*********************************/
