/**
 *******************************************************************************
 * @file       drv_uart.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-01-18                                                      *
 * @brief      uart driver application component                               *
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
#ifndef __BSP_Uart_H__
#define __BSP_Uart_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"

/* Exported macro ------------------------------------------------------------*/
#define UART_RX_FIFO_SIZE      32
    
#define UART_TX_START_EVENT    0
#define UART_TX_TIMEOUT_EVENT  1
#define UART_TX_ISR_EVENT      2
#define UART_RX_TIMEOUT_EVENT  3
#define UART_RX_TIMER_EVENT    4
#define UART_RX_FULL_EVENT     5

/* Exported types ------------------------------------------------------------*/
//typedef uint8_t (*DrvUartCallback)(uint8_t cmd);
    
enum BSP_UART_STATE
{
    UART_IDLE_STATE,
    UART_BUSY_STATE,
    UART_TX_IDLE_STATE = UART_IDLE_STATE,
    UART_TX_BUSY_STATE = UART_BUSY_STATE,
    UART_RX_IDLE_STATE = UART_IDLE_STATE,
    UART_RX_BUSY_STATE = UART_BUSY_STATE,
};

typedef struct
{
    uint8_t *TxBuf;
    uint8_t TxNum;
    uint8_t TxLen;
    uint8_t TxState;

    uint8_t RxBuf[UART_RX_FIFO_SIZE];
    uint8_t RxNum;
    uint8_t RxState;
    
    uint8_t ID;
    uint8_t Evt;
    uint8_t TxTimer;
    uint8_t RxTimer;
//    __CONST DrvUartCallback Callback;
}BSP_Uart_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern BSP_Uart_t Uart0;
extern BSP_Uart_t Uart1;

/* Exported functions --------------------------------------------------------*/
extern void BSP_Uart_Init(BSP_Uart_t *uart, uint8_t id, uint8_t txtimer, uint8_t rxtimer);
extern uint8_t BSP_Uart_Write(BSP_Uart_t *uart, uint8_t *txBuf, uint8_t len, uint8_t force);
extern uint8_t BSP_Uart_Read(BSP_Uart_t *uart, uint8_t *rxBuf, int16_t len);
extern void BSP_Uart_Transfer(BSP_Uart_t *uart);
extern void BSP_Uart_Handle(void);
extern uint8_t BSP_Uart_IsTxComplete(BSP_Uart_t *uart);
extern uint8_t BSP_Uart_IsRxComplete(BSP_Uart_t *uart);
extern void BSP_Uart_StartTx(BSP_Uart_t *uart);
extern void BSP_Uart_StartRx(BSP_Uart_t *uart);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
