/**
 *******************************************************************************
 * @file       stm32f1xx_uart.c                                                *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-01-16                                                      *
 * @brief      stm32f1xx uart driver component                                   *
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
 * @defgroup stm32f1xx uart driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_msp.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Serial_Callback UART_ISR[5];

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
__STATIC_INLINE
void MSP_UART_Config(USART_TypeDef *port, uint32_t irqId, uint32_t baud, uint8_t dataBits, uint8_t stopBits, uint8_t parity)
{
    LL_USART_InitTypeDef USART_InitStruct;
    
    //! 配置UART参数
    USART_InitStruct.BaudRate = baud;
    
    if (dataBits == HAL_SERIAL_DATA_BITS_8)
    {
        USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    }
    else
    {
        USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_9B;
    }
    
    if (stopBits == HAL_SERIAL_STOP_BITS_1)
    {
        USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    }
    else
    {
        USART_InitStruct.StopBits = LL_USART_STOPBITS_2;
    }
    
    if (parity == HAL_SERIAL_PARITY_ODD)
    {
        USART_InitStruct.Parity = LL_USART_PARITY_ODD;
    }
    else if (parity == HAL_SERIAL_PARITY_EVEN)
    {
        USART_InitStruct.Parity = LL_USART_PARITY_EVEN;
    }
    else
    {
        USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    }

    USART_InitStruct.TransferDirection |= LL_USART_DIRECTION_RX | LL_USART_DIRECTION_TX;

    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    
    LL_USART_Init(port, &USART_InitStruct);

    //! 配置为异步模式
    LL_USART_ConfigAsyncMode(port);
    
    //! 配置uart中断
    LL_USART_EnableIT_RXNE(port);
    LL_USART_EnableIT_TC(port);
    LL_USART_EnableDMAReq_TX(port);

    NVIC_SetPriority((IRQn_Type)irqId, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ((IRQn_Type)irqId);
    
    //! 启动UART
    LL_USART_Enable(port);
    
    //! 清除终端标志位
    LL_USART_ClearFlag_RXNE(port);
    LL_USART_ClearFlag_TC(port);
}

void *MSP_UART1_Config(uint32_t baud, uint8_t dataBits, uint8_t stopBits, uint8_t parity)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

    //! todo 待添加其他复用端口
#if MCU_UART1_AF_PORT == 0
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    
    /**USART1 GPIO Configuration  
    PA9   ------> USART1_TX
    PA10   ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif

    //! TX DMA 配置
#ifdef ENABLE_UART1_TX_DMA
    /* USART1 DMA Init */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
    
    /* USART1_TX Init */
    LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

    LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PRIORITY_LOW);

    LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MODE_NORMAL);

    LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PERIPH_NOINCREMENT);

    LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MEMORY_INCREMENT);

    LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PDATAALIGN_BYTE);

    LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MDATAALIGN_BYTE);

    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_4); 

    /* USART1 interrupt Init */
    NVIC_SetPriority(DMA1_Channel4_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
#endif

    MSP_UART_Config(USART1, USART1_IRQn, baud, dataBits, stopBits, parity);
    
    return USART1;
}

void *MSP_UART2_Config(uint32_t baud, uint8_t dataBits, uint8_t stopBits, uint8_t parity)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

#if MCU_UART2_AF_PORT == 0
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    
    /**USART2 GPIO Configuration  
    PA2   ------> USART2_TX
    PA3   ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif

    //! TX DMA 配置
#ifdef ENABLE_UART2_TX_DMA
    /* USART2 DMA Init */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

    /* USART2_TX Init */
    LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_7, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

    LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_7, LL_DMA_PRIORITY_LOW);

    LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_7, LL_DMA_MODE_NORMAL);

    LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_7, LL_DMA_PERIPH_NOINCREMENT);

    LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_7, LL_DMA_MEMORY_INCREMENT);

    LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_7, LL_DMA_PDATAALIGN_BYTE);

    LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_7, LL_DMA_MDATAALIGN_BYTE);

    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_7); 

    NVIC_SetPriority(DMA1_Channel7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ(DMA1_Channel7_IRQn);
#endif

    MSP_UART_Config(USART2, USART2_IRQn, baud, dataBits, stopBits, parity);
    
    return USART2;
}

void *MSP_UART3_Config(uint32_t baud, uint8_t dataBits, uint8_t stopBits, uint8_t parity)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);

#if MCU_UART3_AF_PORT == 0
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
    
    /**USART3 GPIO Configuration  
    PB10   ------> USART3_TX
    PB11   ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif

    //! TX DMA 配置
#ifdef ENABLE_UART3_TX_DMA
    /* USART3 DMA Init */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

    /* USART3_TX Init */
    LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

    LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PRIORITY_LOW);

    LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_NORMAL);

    LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PERIPH_NOINCREMENT);

    LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_INCREMENT);

    LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PDATAALIGN_BYTE);

    LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_BYTE);
    
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2); 

    NVIC_SetPriority(DMA1_Channel2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
#endif

    MSP_UART_Config(USART3, USART3_IRQn, baud, dataBits, stopBits, parity);

    return USART3;
}

void *MSP_UART4_Config(uint32_t baud, uint8_t dataBits, uint8_t stopBits, uint8_t parity)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
    
#if MCU_UART4_AF_PORT == 0
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
    
    /**UART4 GPIO Configuration  
    PC10   ------> UART4_TX
    PC11   ------> UART4_RX 
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
#endif

    //! TX DMA 配置
#ifdef ENABLE_UART4_TX_DMA
    /* UART4 DMA Init */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
    
    /* UART4_TX Init */
    LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_CHANNEL_5, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

    LL_DMA_SetChannelPriorityLevel(DMA2, LL_DMA_CHANNEL_5, LL_DMA_PRIORITY_LOW);

    LL_DMA_SetMode(DMA2, LL_DMA_CHANNEL_5, LL_DMA_MODE_NORMAL);

    LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_CHANNEL_5, LL_DMA_PERIPH_NOINCREMENT);

    LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_CHANNEL_5, LL_DMA_MEMORY_INCREMENT);

    LL_DMA_SetPeriphSize(DMA2, LL_DMA_CHANNEL_5, LL_DMA_PDATAALIGN_BYTE);

    LL_DMA_SetMemorySize(DMA2, LL_DMA_CHANNEL_5, LL_DMA_MDATAALIGN_BYTE);
    
    LL_DMA_EnableIT_TC(DMA2, LL_DMA_CHANNEL_5); 

    NVIC_SetPriority(DMA2_Channel4_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ(DMA2_Channel4_5_IRQn);
#endif

    MSP_UART_Config(UART4, UART4_IRQn, baud, dataBits, stopBits, parity);
    
    return UART4;
}

void *MSP_UART5_Config(uint32_t baud, uint8_t dataBits, uint8_t stopBits, uint8_t parity)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);

#if MCU_UART5_AF_PORT == 0
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
    
    /**UART5 GPIO Configuration  
    PC12   ------> UART5_TX
    PD2   ------> UART5_RX 
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_12;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
    LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
#endif

    MSP_UART_Config(UART5, UART5_IRQn, baud, dataBits, stopBits, parity);
    
    return UART5;
}

void MSP_UART1_Write(uint8_t *tx, uint16_t len)
{
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, len);
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_4, (uint32_t)tx, (uint32_t)&USART1->DR, LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4));

    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);
}

void MSP_UART2_Write(uint8_t *tx, uint16_t len)
{
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_7, len);
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_7, (uint32_t)tx, (uint32_t)&USART1->DR, LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_7));

    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_7);
}

void MSP_UART3_Write(uint8_t *tx, uint16_t len)
{
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, len);
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2, (uint32_t)tx, (uint32_t)&USART1->DR, LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2));

    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
}

void MSP_UART4_Write(uint8_t *tx, uint16_t len)
{
    LL_DMA_SetDataLength(DMA2, LL_DMA_CHANNEL_5, len);
    LL_DMA_ConfigAddresses(DMA2, LL_DMA_CHANNEL_5, (uint32_t)tx, (uint32_t)&USART1->DR, LL_DMA_GetDataTransferDirection(DMA2, LL_DMA_CHANNEL_5));

    LL_DMA_EnableChannel(DMA2, LL_DMA_CHANNEL_5);
}

#ifdef ENABLE_HAL_SERIAL_DRIVER
__STATIC_INLINE
USART_TypeDef *MSP_UART_Base_Get(uint8_t id)
{
    const uint32_t port[] = {USART1_BASE, USART2_BASE, USART3_BASE, UART4_BASE, UART5_BASE};
    
    return (USART_TypeDef *)(port[id]);
}

uint16_t uart_config(HAL_Serial_t *serial, HAL_Serial_Config_t *config)
{
    switch (serial->Attribute.Port)
    {
        case HAL_SERIAL_0:
            serial->Param = MSP_UART1_Config(config->Attribute.Baud, config->Attribute.DataBits, config->Attribute.StopBits, config->Attribute.Parity);
            break;
        case HAL_SERIAL_1:
            serial->Param = MSP_UART2_Config(config->Attribute.Baud, config->Attribute.DataBits, config->Attribute.StopBits, config->Attribute.Parity);
            break;
        case HAL_SERIAL_2:
            serial->Param = MSP_UART3_Config(config->Attribute.Baud, config->Attribute.DataBits, config->Attribute.StopBits, config->Attribute.Parity);
            break;
        case HAL_SERIAL_3:
            serial->Param = MSP_UART4_Config(config->Attribute.Baud, config->Attribute.DataBits, config->Attribute.StopBits, config->Attribute.Parity);
            break;
        case HAL_SERIAL_4:
            serial->Param = MSP_UART5_Config(config->Attribute.Baud, config->Attribute.DataBits, config->Attribute.StopBits, config->Attribute.Parity);
            break;
        default:
            break;
    }

    return 0;
}

uint32_t uart_control(HAL_Serial_t *serial, uint32_t cmd, void *arg)
{
    uint32_t result = 0;
    
    switch (cmd)
    {
        case HAL_REQUEST_CMD:
            result = (uint32_t)MSP_UART_Base_Get(serial->Attribute.Port);
            break;
        case HAL_SET_CALLBACK_CMD:
        {
            Serial_Callback *callback = (Serial_Callback *)arg;
            
            UART_ISR[serial->Attribute.Port].Callback = callback->Callback;
            UART_ISR[serial->Attribute.Port].Param    = callback->Param;
            break;
        }
        default:
            break;
    }
    
    return result;
}

uint16_t uart_putchar(HAL_Serial_t *serial, char c)
{
    USART_TypeDef *uart = (USART_TypeDef *)serial->Param;
    
    uart->DR = c;
    
    return 0;
}

uint16_t uart_getchar(HAL_Serial_t *serial, char *c)
{
    USART_TypeDef *uart = (USART_TypeDef *)serial->Param;
    
    *c = uart->DR;
    
    return 0;
}

uint16_t uart_dma_transmit(HAL_Serial_t *serial, uint8_t *buf, uint16_t size, uint8_t dir)
{
    if (dir == 0)
    {
        switch (serial->Attribute.Port)
        {
            case HAL_SERIAL_0:
                MSP_UART1_Write(buf, size);
                break;
            case HAL_SERIAL_1:
                MSP_UART2_Write(buf, size);
                break;
            case HAL_SERIAL_2:
                MSP_UART3_Write(buf, size);
                break;
            case HAL_SERIAL_3:
                MSP_UART4_Write(buf, size);
                break;
            default:
                return 0;
    //            break;
        }
        
        return size;
    }
    
    return 0;
}
#endif

/* Exported functions --------------------------------------------------------*/
void MSP_UART_Init(void)
{
    //! MSP UART1 组件 初始化
#ifdef ENABLE_MSP_UART1_DRIVER
    MSP_UART1_Config(MCU_UART1_BAUD, MCU_UART1_DATA_BITS, MCU_UART1_STOP_BITS, MCU_UART1_PARITY);
#endif

    //! MSP UART2 组件 初始化
#ifdef ENABLE_MSP_UART2_DRIVER
    MSP_UART2_Config(MCU_UART2_BAUD, MCU_UART2_DATA_BITS, MCU_UART2_STOP_BITS, MCU_UART2_PARITY);
#endif

    //! MSP UART3 组件 初始化
#ifdef ENABLE_MSP_UART3_DRIVER
    MSP_UART3_Config(MCU_UART3_BAUD, MCU_UART3_DATA_BITS, MCU_UART3_STOP_BITS, MCU_UART3_PARITY);
#endif

    //! MSP UART4 组件 初始化
#ifdef ENABLE_MSP_UART4_DRIVER
    MSP_UART4_Config(MCU_UART4_BAUD, MCU_UART4_DATA_BITS, MCU_UART4_STOP_BITS, MCU_UART4_PARITY);
#endif

    //! MSP UART5 组件 初始化
#ifdef ENABLE_MSP_UART5_DRIVER
    MSP_UART5_Config(MCU_UART5_BAUD, MCU_UART5_DATA_BITS, MCU_UART5_STOP_BITS, MCU_UART5_PARITY);
#endif

#ifdef ENABLE_HAL_SERIAL_DRIVER
    HAL_Serial_Interface_t UartOps;
    
    //! HAL 组件初始化
    UartOps.Config      = uart_config;
    UartOps.Control     = uart_control;
    UartOps.DmaTransmit = uart_dma_transmit;
    UartOps.GetChar     = uart_getchar;
    UartOps.PutChar     = uart_putchar;
    
    HAL_Serial_Register(&UartOps, NULL);
#endif  
}

uint16_t MSP_UART_Write(USART_TypeDef *uart, uint8_t *buf, uint16_t pos, uint16_t len)
{
    if (uart == USART1)
    {
        MSP_UART1_Write((uint8_t *)&buf[pos], len);
        
        return len;
    }
    else if (uart == USART2)
    {
        MSP_UART2_Write((uint8_t *)&buf[pos], len);
        
        return len; 
    }
    else if (uart == USART3)
    {
        MSP_UART3_Write((uint8_t *)&buf[pos], len);
        
        return len; 
    }
    else if (uart == UART4)
    {
        MSP_UART4_Write((uint8_t *)&buf[pos], len);
                
        return len;
    }
    else
    {
        //! do nothing!
    }
    
    return 0;
}

uint16_t MSP_UART_Send(USART_TypeDef *uart, uint8_t c)
{
    uart->DR = c;
    
    return 1;
}

uint16_t MSP_UART_Recv(USART_TypeDef *uart, uint8_t *c)
{
    *c = uart->DR;
    
    return 1;
}

void MSP_UART_SetCallback(USART_TypeDef *uart, void *callback, void *param)
{
    uint8_t port;
    
    if (uart == USART1)
    {
        port = 0;
    }
    else if (uart == USART2)
    {
        port = 1;
    }
    else if (uart == USART3)
    {
        port = 2;
    }
    else if (uart == UART4)
    {
        port = 3;
    }
    else if (uart == UART5)
    {
        port = 4;
    }
    else
    {
        return ;
    }
    
    UART_ISR[port].Callback = (SerialIsrCallback)callback;
    UART_ISR[port].Param    = param;
}

void USART1_IRQHandler(void)
{
    uint16_t evt = 0;
    
    if (LL_USART_IsActiveFlag_TC(USART1))
    {
        evt = HAL_SERIAL_EVENT_TX_DONE;
        
        LL_USART_ClearFlag_TC(USART1);
    }
    else if (LL_USART_IsActiveFlag_RXNE(USART1))
    {
        evt = HAL_SERIAL_EVENT_RX_IND;
        
        LL_USART_ClearFlag_RXNE(USART1);
    }
    else
    {
        return ;
    }
    
    if (!IS_PTR_NULL(UART_ISR[0].Callback))
    {
        UART_ISR[0].Callback(UART_ISR[0].Param, evt);
    }
}

void USART2_IRQHandler(void)
{
    uint16_t evt = 0;
    
    if (LL_USART_IsActiveFlag_TC(USART2))
    {
        evt = HAL_SERIAL_EVENT_TX_DONE;
        
        LL_USART_ClearFlag_TC(USART2);
    }
    else if (LL_USART_IsActiveFlag_RXNE(USART2))
    {
        evt = HAL_SERIAL_EVENT_RX_IND;
        
        LL_USART_ClearFlag_RXNE(USART2);
    }
    else
    {
        return ;
    }
    
    if (!IS_PTR_NULL(UART_ISR[1].Callback))
    {
        UART_ISR[1].Callback(UART_ISR[1].Param, evt);
    }
}

void USART3_IRQHandler(void)
{
    uint16_t evt = 0;
    
    if (LL_USART_IsActiveFlag_TC(USART3))
    {
        evt = HAL_SERIAL_EVENT_TX_DONE;
        
        LL_USART_ClearFlag_TC(USART3);
    }
    else if (LL_USART_IsActiveFlag_RXNE(USART3))
    {
        evt = HAL_SERIAL_EVENT_RX_IND;
        
        LL_USART_ClearFlag_RXNE(USART3);
    }
    else
    {
        return ;
    }
    
    if (!IS_PTR_NULL(UART_ISR[2].Callback))
    {
        UART_ISR[2].Callback(UART_ISR[2].Param, evt);
    }
}
void UART4_IRQHandler(void)
{
    uint16_t evt = 0;
    
    if (LL_USART_IsActiveFlag_TC(UART4))
    {
        evt = HAL_SERIAL_EVENT_TX_DONE;
        
        LL_USART_ClearFlag_TC(UART4);
    }
    else if (LL_USART_IsActiveFlag_RXNE(UART4))
    {
        evt = HAL_SERIAL_EVENT_RX_IND;
        
        LL_USART_ClearFlag_RXNE(UART4);
    }
    else
    {
        return ;
    }
    
    if (!IS_PTR_NULL(UART_ISR[3].Callback))
    {
        UART_ISR[3].Callback(UART_ISR[3].Param, evt);
    }
}

void UART5_IRQHandler(void)
{
    uint16_t evt = 0;
    
    if (LL_USART_IsActiveFlag_TC(UART5))
    {
        evt = HAL_SERIAL_EVENT_TX_DONE;
        
        LL_USART_ClearFlag_TC(UART5);
    }
    else if (LL_USART_IsActiveFlag_RXNE(UART5))
    {
        evt = HAL_SERIAL_EVENT_RX_IND;
        
        LL_USART_ClearFlag_RXNE(UART5);
    }
    else
    {
        return ;
    }
    
    if (!IS_PTR_NULL(UART_ISR[4].Callback))
    {
        UART_ISR[4].Callback(UART_ISR[4].Param, evt);
    }
}

/** @}*/     /** stm32f1xx uart driver component */

/**********************************END OF FILE*********************************/
