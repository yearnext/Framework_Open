/**
 *******************************************************************************
 * @file       bsp_key.c                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-02-05                                                      *
 * @brief      bsp key component                                               *
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
 * @defgroup bsp key component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

/* Private define ------------------------------------------------------------*/
//! 按键数量
#define BSP_KEY_MAX                                              _dimof(BSP_KEY)

/* Private typedef -----------------------------------------------------------*/
//! 按键句柄定义
typedef struct 
{
    uint32_t Pin;

    //! |7     |6     |5     |4     |3                 |2                 |1                 |       0      |
    //! |未使用|未使用|未使用|未使用|事件机制使能标志位|消息机制使能标志位|长按检测使能标志位|按键有效电平位|
    uint16_t Flag;
}BSP_KEY_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
//! 定义按键端口
__CONST BSP_KEY_t BSP_KEY[] = 
{
    {.Pin = HAL_PIN_ID(KEY_SET_PORT, KEY_SET_PIN),  .Flag = HAL_KEY_LOW_TRIG},
    {.Pin = HAL_PIN_ID(KEY_MODE_PORT, KEY_MODE_PIN), .Flag = HAL_KEY_LOW_TRIG},
};

HAL_Key_t KeyGroup1;

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
int BSP_KEY_Init(void)
{
    uint16_t i;
    
    for (i=0; i<BSP_KEY_MAX; i++)
    {
        HAL_Pin_Input(BSP_KEY[i].Pin);
    }
    
    uint16_t BSP_KEY_Group1_Scan(void);
    HAL_Key_Init(&KeyGroup1, BSP_KEY_Group1_Scan, 10, HAL_KEY_LONG_SCAN);

    return 0;
}
INIT_BOARD_EXPORT(BSP_KEY_Init);

uint16_t BSP_KEY_Group1_Scan(void)
{
    uint16_t value = 0;
    uint8_t i;
    
    for (i=0; i<BSP_KEY_MAX; i++)
    {
        if (HAL_Pin_Get(BSP_KEY[i].Pin))
        {
            if (HAL_Flag_Get(BSP_KEY[i].Flag, HAL_KEY_HIGH_TRIG))
            {
                _set_bit(value, i);
            }
        }
        else
        {
            if (!HAL_Flag_Get(BSP_KEY[i].Flag, HAL_KEY_HIGH_TRIG))
            {
                _set_bit(value, i);
            }
        }
    }
    
    return value;
}

/** @}*/     /** bsp key component */

/**********************************END OF FILE*********************************/
