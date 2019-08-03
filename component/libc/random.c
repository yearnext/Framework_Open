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
static int next = 1;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void RandromSet(int seed)
{
    next ^= seed;
}

void RandromReset(void)
{
    next = 1;
}

int RandromGet(void)
{
   return ( ( next = next * 1103515245L + 12345L ) % RAND_LOCAL_MAX );
}

/** @}*/     /** randrom library component */

/**********************************END OF FILE*********************************/
