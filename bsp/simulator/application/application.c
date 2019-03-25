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
#include "bsp.h"
#include "fw_core.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FwTask_t Task1;
FwTask_t Task2;
FwTask_t Task3;
FwTask_t Task4;
FwTask_t Task5;

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

void Task_Handle(void *param)
{
	int time = rand() % 1000;
	FwTask_t *task = (FwTask_t *)param;

	Fw_Log("%s Delay %d Ticks! \r\n", task->Name, time);
	
	Fw_Task_Delay(rand() % 1000);
}

int App_Task_Init(void)
{
    Fw_Task_Init(&Task1, "Test1 Task", Task_Handle, &Task1, 0, FW_TASK_EN_TIM);
    Fw_Task_Start(&Task1);

	Fw_Task_Init(&Task2, "Test2 Task", Task_Handle, &Task2, 1, FW_TASK_EN_TIM);
	Fw_Task_Start(&Task2);

	Fw_Task_Init(&Task3, "Test3 Task", Task_Handle, &Task3, 2, FW_TASK_EN_TIM);
	Fw_Task_Start(&Task3);

	Fw_Task_Init(&Task4, "Test4 Task", Task_Handle, &Task4, 3, FW_TASK_EN_TIM);
	Fw_Task_Start(&Task4);

	Fw_Task_Init(&Task5, "Test5 Task", Task_Handle, &Task5, 4, FW_TASK_EN_TIM);
	Fw_Task_Start(&Task5);

	return 0;
}INIT_APP_EXPORT(App_Task_Init);

int Fw_App_Init(void)
{
	App_Task_Init();

	return 0;
}
