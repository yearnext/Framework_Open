/**
 *******************************************************************************
 * @file       randrom.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-03-19                                                      *
 * @brief      randrom component head files                                    *
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
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RANDROM_LIBRARY_H__
#define __RANDROM_LIBRARY_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/ 
/* Exported functions --------------------------------------------------------*/
extern void RandromSet(uint16_t seed);
extern void RandromReset( void );
extern uint16_t RandromGet(void);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** randrom library component */

/**********************************END OF FILE*********************************/

