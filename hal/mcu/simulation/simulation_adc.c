/**
 *******************************************************************************
 * @file       simulation_adc.c                                                *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-11-13                                                      *
 * @brief      simulation adc driver component                                 *
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
 * @defgroup simulation adc driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_msp.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
//! 定义ADC最大值
const uint16_t ADCValueMax = 4096;

/* Private variables ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void MSP_ADC_Init(void)
{
	time_t nowTime = time(NULL);

	srand((unsigned int)nowTime);
}

void MSP_ADC_Start(uint8_t channel)
{

}

uint16_t MSP_ADC_Read(uint8_t force)
{
    return rand() % ADCValueMax;
}

uint16_t MSP_ADC_Convert(uint8_t channel)
{
    return rand() % ADCValueMax;
}

/** @}*/     /** n76e003 adc driver component */

/**********************************END OF FILE*********************************/
