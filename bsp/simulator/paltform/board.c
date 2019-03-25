/**
 *******************************************************************************
 * @file       bsp.c                                                           *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-01-17                                                      *
 * @brief      bsp component                                                   *
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
 * @defgroup bsp component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int BSP_Init(void)
{
	Fw_Enter_Critical();

	BSP_Data_Init();

	Fw_Exit_Critical();

	return 0;
}
INIT_BOARD_EXPORT(BSP_Init);

/* Exported functions --------------------------------------------------------*/
int Fw_MSP_Init(void)
{
	MSP_Init();

	return 0;
}

int Fw_Board_Init(void)
{
	BSP_Init();
	
	BSP_Led_Init();

	return 0;
}

void BSP_Data_Recever(void)
{

}

void BSP_Data_Reset(void)
{

}

void BSP_Data_Init(void)
{
//    uint16_t firstKey = BSP_EEPROM_Read_HalfWord(BSP_FIRST_ADDR);
//    
//    if (firstKey == BSP_FIRST_KEY)
//    {
//        BSP_Data_Recever();
//    }
//    else
//    {
//        BSP_EEPROM_Write_HalfWord(BSP_FIRST_ADDR, BSP_FIRST_KEY);
//        BSP_Data_Reset();
//    }
}

void BSP_MSG_Send(BSP_MSG_t *msg)
{
//    Fw_MQ_Send(&DeviceMQ, (Fw_Msg_t *)msg);
}

uint16_t BSP_MSG_Recv(BSP_MSG_t* msg)
{
    //! 接收到来自设备驱动的消息
//    if (HAL_Msg_Recv((HAL_MSG_t *)msg))
//    {
//        return 1;
//    }

    return 0;
}

//! 中断处理函数
void FwTick_Irq_Handler(void)
{
	Fw_Tick_Inc();
}

/** @}*/     /** bsp component */

/**********************************END OF FILE*********************************/
