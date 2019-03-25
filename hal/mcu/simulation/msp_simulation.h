/**
 *******************************************************************************
 * @file       msp_simulation.h                                                *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-11-12                                                      *
 * @brief      mcu config component                                            *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 MSVC                                                        *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MSVC_SIMULATION_SUPPOR_PACKET_H__
#define __MSVC_SIMULATION_SUPPOR_PACKET_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"
#include "msp_conf.h"
#include "hal_device.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET GPIO COMPONENT API
 *******************************************************************************
 */
extern void MSP_GPIO_Init(void);

//! MSP LV0 API
extern void MSP_GPIO_Set(uint32_t port, uint32_t pin);
extern void MSP_GPIO_Clr(uint32_t port, uint32_t pin);
extern uint32_t MSP_GPIO_Get(uint32_t port, uint32_t pin);
extern void MSP_GPIO_Write(uint32_t port, uint32_t wr);
extern uint32_t MSP_GPIO_Read(uint32_t port);
extern void MSP_GPIO_Config(uint32_t port, uint32_t pin, uint32_t mode);

#define MSP_GPIO_Output(port, pin) _st(MSP_GPIO_Config(port, pin, LL_GPIO_MODE_OUTPUT);)
#define MSP_GPIO_Input(port, pin)  _st(MSP_GPIO_Config(port, pin, LL_GPIO_MODE_INPUT);)

//! MSP LV1 API
extern void MSP_Pin_Init(uint16_t port, uint32_t pin, uint16_t mode);
extern void MSP_Pin_Set(uint16_t port, uint32_t pin);
extern void MSP_Pin_Clr(uint16_t port, uint32_t pin);
extern void MSP_Pin_Toggle(uint16_t port, uint32_t pin);
extern uint16_t MSP_Pin_Read(uint16_t port, uint32_t pin);

#define MSP_Pin_Output(port, pin) _st(MSP_Pin_Init(port, pin, HAL_PIN_OUTPUT);)
#define MSP_Pin_Input(port, pin)  _st(MSP_Pin_Init(port, pin, HAL_PIN_INPUT);)

/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET TIMER COMPONENT API
 *******************************************************************************
 */
#define MCU_TIMER0_ID (0)
#define MCU_TIMER1_ID (1)
#define MCU_TIMER2_ID (2)

extern void MSP_Timer_Init(void);
extern void MSP_Timer_Start(uint8_t timerID, uint16_t tick);
extern void MSP_Timer_Stop(uint8_t timerID);
extern void MSP_Timer_Handle(void);

#define MSP_Timer0_Reload()
#define MSP_Timer0_Tick(t) 
#define MSP_Timer0_Get()   
#define MSP_Timer0_Clr()   
#define MSP_Timer0_IRQ(x)  
#define MSP_Timer0_Start() 
#define MSP_Timer0_Stop()  

#define MSP_Timer1_Reload()
#define MSP_Timer1_Tick(t) 
#define MSP_Timer1_Get()   
#define MSP_Timer1_Clr()   
#define MSP_Timer1_IRQ(x)  
#define MSP_Timer1_Start() 
#define MSP_Timer1_Stop()  

#define MSP_Timer2_Reload()
#define MSP_Timer2_Tick(t) 
#define MSP_Timer2_Get()   
#define MSP_Timer2_Clr()   
#define MSP_Timer2_IRQ(x)  
#define MSP_Timer2_Start() 
#define MSP_Timer2_Stop()  

/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET PWM COMPONENT API
 *******************************************************************************
 */
#define MSP_PWM_Init()
#define MSP_PWM_Start(channel)
#define MSP_PWM_Stop(channel)
#define MSP_PWM_Set(channel, duty)
#define MSP_PWM_Output(channel, state)
#define MSP_PWM_Get(channel)                                                 (0)

/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET ADC COMPONENT API
 *******************************************************************************
 */
extern void MSP_ADC_Init(void);
extern void MSP_ADC_Start(uint8_t channel);
extern uint16_t MSP_ADC_Read(uint8_t force);
extern uint16_t MSP_ADC_Convert(uint8_t channel);

#if 0
/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET UART COMPONENT API
 *******************************************************************************
 */
extern void MSP_UART_Init(void);

#define MSP_UART0_Recv()  (SBUF)
#define MSP_UART0_Send(c) _st(SBUF = (c);)

#define MSP_UART1_Recv()  (SBUF_1)
#define MSP_UART1_Send(c) _st(SBUF_1 = (c);)

/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET SPI COMPONENT API
 *******************************************************************************
 */
extern void MSP_SPI_Init(void);
extern uint8_t MSP_SPI_RW_Byte(uint8_t txData);
extern void MSP_SPI_Write(uint8_t *tx, uint8_t txLen);
extern void MSP_SPI_Read(uint8_t *rx, uint8_t rxLen);

/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET IIC COMPONENT API
 *******************************************************************************
 */
extern void MSP_IIC_Init(void);
extern void MSP_IIC_Start(void);
extern void MSP_IIC_Stop(void);
extern void MSP_IIC_Timeout_Start(void);
extern void MSP_IIC_Timeout_Stop(void);
#endif

/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET WDG COMPONENT API
 *******************************************************************************
 */
#define MSP_WDG_Init()
#define MSP_WDG_Feed()

/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET FLASH COMPONENT API
 *******************************************************************************
 */
#define MSP_EEPROM_Init()
#define MSP_EEPROM_Write_Byte(addr,  wByte)
#define MSP_EEPROM_Read_Byte(addr)                 (0xFF)
#define MSP_EEPROM_Write_HalfWord(addr, wByte)
#define MSP_EEPROM_Read_HalfWord(addr)             (0xFFFF)
#define MSP_EEPROM_Write_Word(addr, wByte)
#define MSP_EEPROM_Read_Word(addr)                 (0xFFFFFFFF)
#define MSP_EEPROM_Write(addr, wBuf, len)          (0)
#define MSP_EEPROM_Read(addr, rBuf, len)           (0)
#define MSP_Flash_Read_Byte(u16_addr)
#define MSP_EEPROM_Update()

/**
 *******************************************************************************
 * @brief      MCU SUPPORT PACKET CORE COMPONENT API
 *******************************************************************************
 */
extern int  MSP_Init(void);
extern void MSP_Handle(void);
extern void MSP_Reboot(void);
extern void MSP_Delay_Us(uint16_t timeout);
extern void MSP_Delay_Ms(uint16_t timeout);
extern void MSP_Enable_Irq(void);
extern void MSP_Disable_Irq(void);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
