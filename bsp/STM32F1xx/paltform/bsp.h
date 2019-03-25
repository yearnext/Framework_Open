/**
 *******************************************************************************
 * @file       bsp.h                                                           *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-01-17                                                      *
 * @brief      bsp component                                                   *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_H__
#define __BSP_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"
#include "hal_msp.h"
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/
// <<< Use Configuration Wizard in Context Menu >>>
// <c1>Enable Led Super Component
//  <i>Enable Led Super Component
#define ENABLE_LED_SUPER_COMPONENT
// </c>

// <<< end of configuration section >>>

/**
 *******************************************************************************
 * @brief      定义LED引脚
 *******************************************************************************
 */
#define LED1_PORT HAL_PORT_B
#define LED1_PIN  HAL_PIN_13

#define LED2_PORT HAL_PORT_B
#define LED2_PIN  HAL_PIN_14

/**
 *******************************************************************************
 * @brief      定义按键引脚
 *******************************************************************************
 */
#define KEY_SET_PORT  HAL_PORT_E
#define KEY_SET_PIN   HAL_PIN_0

#define KEY_MODE_PORT HAL_PORT_C
#define KEY_MODE_PIN  HAL_PIN_13

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      BSP 外设ID
 *******************************************************************************
 */
enum
{
    BSP_LED_1 = 0,
    BSP_LED_2 = 1,
    
    BSP_KEY_1 = 0x01,
    BSP_KEY_2 = 0x02,
    BSP_KEY_3 = 0x03,
    
    BSP_DEVICE_MAX,
};

/**
 *******************************************************************************
 * @brief      BSP 专用消息类型
 *******************************************************************************
 */
typedef union
{
    //! 设备消息类型
    HAL_MSG_t DevMsg;
}BSP_MSG_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      BSP 基础组件 API
 *******************************************************************************
 */
extern int BSP_Init(void);
extern void BSP_Data_Recever(void);
extern void BSP_Data_Reset(void);
extern void BSP_Data_Init(void);

extern void BSP_MSG_Send(BSP_MSG_t *msg);
extern uint16_t BSP_MSG_Recv(BSP_MSG_t* msg);

/**
 *******************************************************************************
 * @brief      BSP LED组件 API
 *******************************************************************************
 */
extern int BSP_Led_Init(void);
extern void BSP_Led_On(uint8_t id);
extern void BSP_Led_Off(uint8_t id);
extern void BSP_Led_Control(uint8_t id, int16_t count, uint16_t tick);

/**
 *******************************************************************************
 * @brief      BSP 按键组件 API
 *******************************************************************************
 */
extern int BSP_Key_Init(void);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
