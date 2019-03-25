/**
 *******************************************************************************
 * @file       application.c                                                   *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2016-01-26                                                      *
 * @brief      application component source files                              *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.消息邮箱、事件机制测试程序                                                *
 *******************************************************************************
 */

/**
* @defgroup application component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"
#include "bsp.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FwTask_t Task;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
//! 主函数
int main(void)
{
    Fw_Core_Init();

    Fw_Core_Startup();
    
    return 0;
}

void Task1_Handle(void *param)
{
    Fw_PT_Begin();
    
    while (1)
    {
        BSP_Led_On(0);
        Fw_PT_Delay(500);
        
        BSP_Led_Off(0);
        Fw_PT_Delay(500);
    }
    
    Fw_PT_End();
}

int App_Task_Init(void)
{
    Fw_Task_Init(&Task, "Test1 Task", (void *)Task1_Handle, &Task, 1, FW_TASK_EN_PROTOTHREAD|FW_TASK_EN_TIM);
    Fw_Task_Start(&Task);

    return 0;
}INIT_APP_EXPORT(App_Task_Init);
