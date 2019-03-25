/**
 *******************************************************************************
 * @file       simulation_timer.c                                              *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-11-13                                                      *
 * @brief      simulation timer driver component                               *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 MSVC                                                        *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
 
/**
 * @defgroup simulation timer driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_msp.h"

#pragma comment(lib,"Winmm.lib")

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void MSP_Timer_Init(void)
{

}

void MSP_Timer_Start(uint8_t timerID, uint16_t tick)
{

}

void MSP_Timer_Stop(uint8_t timerID)
{

}

void MSP_Timer_Handle(void)
{
/*	MSG msg;

	if (GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}
*/
}

/** @}*/     /** simulation timer driver component */

/**********************************END OF FILE*********************************/
