/**
 *******************************************************************************
 * @file       simulation_gpio.c                                               *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-11-12                                                      *
 * @brief      simulation gpio driver component                                *
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
 * @defgroup simulation gpio driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_msp.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void MSP_GPIO_Init(void)
{

}

//! MSP LV0 API
void MSP_GPIO_Set(uint32_t port, uint32_t pin)
{

}

void MSP_GPIO_Clr(uint32_t port, uint32_t pin)
{

}

uint32_t MSP_GPIO_Get(uint32_t port, uint32_t pin)
{
	return 0;
}

void MSP_GPIO_Write(uint32_t port, uint32_t wr)
{

}

uint32_t MSP_GPIO_Read(uint32_t port)
{
	return 0;
}

void MSP_GPIO_Config(uint32_t port, uint32_t pin, uint32_t mode)
{

}

void MSP_Pin_Init(uint16_t port, uint32_t pin, uint16_t mode)
{

}

void MSP_Pin_Set(uint16_t port, uint32_t pin)
{

}

void MSP_Pin_Clr(uint16_t port, uint32_t pin)
{

}

void MSP_Pin_Toggle(uint16_t port, uint32_t pin)
{

}

uint16_t MSP_Pin_Read(uint16_t port, uint32_t pin)
{
	return 0;
}

/** @}*/     /** simulation gpio driver component */

/**********************************END OF FILE*********************************/
