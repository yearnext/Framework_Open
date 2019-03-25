/**
 *******************************************************************************
 *                 Copyright (C) 2017 - 2018  Accumulate Team                  *
 *                                                                             *
 *      Licensed under the Apache License, Version 2.0 (the "License");        *
 *      you may not use this file except in compliance with the License.       *
 *      You may obtain a copy of the License at                                *
 *                 http://www.apache.org/licenses/LICENSE-2.0                  *
 *                                                                             *
 *   Unless required by applicable law or agreed to in writing, software       *
 *   distributed under the License is distributed on an "AS IS" BASIS,         *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *   See the License for the specific language governing permissions and       *
 *   limitations under the License.                                            *
 *******************************************************************************
 * @file       crc.h                                                           *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-09-17                                                      *
 * @brief      crc component head files                                        *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
 *******************************************************************************
 */
 
/**
 * @defgroup crc tools component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRC_COMPONENT_H__
#define __CRC_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"
    
/* Exported macro ------------------------------------------------------------*/
#define CRC_INIT                    (0xFFFF)

#define CRC7_INIT                   (0x00)
#define CRC7_POLY                   (0x89)

#define CRC8_INIT                   (0x00)
#define CRC8_POLY                   (0x07)
#define CRC8_ROHC_INIT              (0xFF)
#define CRC8_ROHC_POLY              (0x07)

#define CRC16_INIT                  (0xFFFF)
#define CRC16_MODBUS_INIT           (0xFFFF)
#define CRC16_USB_INIT              (0xFFFF)
#define CRC16_MODEM_INIT            (0x0000)
#define CRC16_POLY                  (0x8005)

#define CRC16_CCITT_FALSE_INIT      (0xFFFF)
#define CRC16_CCITT_FALSE_POLY      (0x1021)

#define CRC32_INIT                  (0xFFFFFFFF)
#define CRC32_POLY                  (0x04C11DB7)
#define CRC32_IEEE802_3_INIT        (0xFFFFFFFF)
#define CRC32_IEEE802_3_POLY        (0x04C11DB7)

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern uint8_t Crc7_Cal(uint8_t *in, uint16_t len);
extern uint8_t Crc8_Cal(uint8_t *in, uint16_t len);

extern uint8_t Crc8_Cal(uint8_t *in, uint16_t len);
extern uint8_t Crc8_Rohc_Cal(uint8_t *in, uint16_t len);

extern uint16_t Crc16_Cal(uint8_t *ptr, uint16_t Length);
extern uint16_t Crc16_Usb_Cal(uint16_t *in, uint16_t len);
extern uint16_t Crc16_Modbus_Cal(uint16_t *in, uint16_t len);
extern uint16_t Crc16_CCITT_Cal(uint16_t *in, uint16_t len);
extern uint16_t Crc16_Modem_Cal(uint16_t *in, uint16_t len);

extern uint32_t Crc32_Cal(uint32_t *in, uint16_t len);
extern uint32_t Crc32_IEEE802_3_Cal(uint32_t *in, uint16_t len);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** crc component */

/**********************************END OF FILE*********************************/
