/**
 *******************************************************************************
 * @file       msp_simulation.c                                                *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-11-12                                                      *
 * @brief      paltform support packet                                         *
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
 * @defgroup paltform support packet
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_msp.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static MMRESULT sysTimerId;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern void CALLBACK SystemTickHandle(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

int MSP_Init(void)
{
	MSP_GPIO_Init();

	MSP_ADC_Init();

	MSP_Timer_Init();

	sysTimerId = timeSetEvent(FRAMEWORK_TICK_TIME, 1, SystemTickHandle, 0, TIME_PERIODIC);

    return 0;
}

void MSP_Handle(void)
{
	MSP_Timer_Handle();
}

void MSP_Reboot(void)
{
	
}

void MSP_Delay_Us(uint16_t timeout)
{
	//uSleep(timeout);
}

void MSP_Delay_Ms(uint16_t timeout)
{
	Sleep(timeout);
}

void MSP_Enable_Irq(void)
{
	timeKillEvent(sysTimerId);
	sysTimerId = timeSetEvent(FRAMEWORK_TICK_TIME, 1, SystemTickHandle, 0, TIME_PERIODIC);
}

void MSP_Disable_Irq(void)
{
	timeKillEvent(sysTimerId);
}

/** @}*/     /** paltform support packet */

/**********************************END OF FILE*********************************/
