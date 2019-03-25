/**
 *******************************************************************************
 * @file       randrom.c                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-03-19                                                      *
 * @brief      randrom component source files                                  *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.部分内容参考自互联网                                                      *
 *******************************************************************************
 */

/**
 * @defgroup randrom library component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "randrom.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint16_t RandromSeed = 0xAA55;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void RandromSet(uint16_t seed)
{
    RandromSeed ^= seed;
}

void RandromReset( void )
{
    RandromSeed = 0xAA55;
}

uint16_t RandromGet(void)
{
   RandromSeed = 22695477UL * RandromSeed + 1;

   return RandromSeed;
}

/** @}*/     /** randrom library component */

/**********************************END OF FILE*********************************/
