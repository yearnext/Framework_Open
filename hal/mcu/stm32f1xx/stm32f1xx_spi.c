/**
 *******************************************************************************
 * @file       stm32f1xx_spi.c                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-02-03                                                      *
 * @brief      stm32f1xx spi driver component                                  *
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
 * @defgroup stm32f1xx spi drvier component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "msp_stm32f1xx.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
__STATIC_INLINE
uint32_t SPI_Baud_Get(SPI_TypeDef *port, uint32_t speed)
{
    uint32_t baud = 0;
    
    if (port == SPI1)
    {
        switch(speed)
        {
            case HAL_SPI_SPEED_20M:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV4;
                break;
            case HAL_SPI_SPEED_10M:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV8;
                break;
            case HAL_SPI_SPEED_5M:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV16;
                break;
            case HAL_SPI_SPEED_2M:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV32;
                break;       
            case HAL_SPI_SPEED_1M:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV64;
                break;
            case HAL_SPI_SPEED_500K:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV128;
                break;
            default:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV256;
                break;
        }
    }
    else
    {
        switch(speed)
        {
            case HAL_SPI_SPEED_20M:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV2;
                break;
            case HAL_SPI_SPEED_10M:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV4;
                break;
            case HAL_SPI_SPEED_5M:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV8;
                break;
            case HAL_SPI_SPEED_2M:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV16;
                break;       
            case HAL_SPI_SPEED_1M:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV32;
                break;
            case HAL_SPI_SPEED_500K:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV64;
                break;     
            case HAL_SPI_SPEED_200K:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV128;
                break;
            default:
                baud = LL_SPI_BAUDRATEPRESCALER_DIV256;
                break;
        }
    }
    
    return baud;
}

void SPI_Config(SPI_TypeDef *port, uint8_t master, uint8_t spiMode, uint32_t spd, uint8_t bitOrder)
{
    LL_SPI_InitTypeDef SPI_InitStruct;
    
    SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
    
    if (master)
    {
        SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
    }
    else
    {
        SPI_InitStruct.Mode = LL_SPI_MODE_SLAVE;
    }
    
    SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
    
    if (spiMode == HAL_SPI_MODE_0)
    {
        SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
        SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
    }
    else if (spiMode == HAL_SPI_MODE_1)
    {
        SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
        SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
    }
    else if (spiMode == HAL_SPI_MODE_2)
    {
        SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
        SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
    }
    else
    {
        SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
        SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
    }
    
    if (bitOrder == HAL_DEVICE_MSB)
    {
        SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
    }
    else
    {
        SPI_InitStruct.BitOrder = LL_SPI_LSB_FIRST;
    }    
    
    SPI_InitStruct.BaudRate = SPI_Baud_Get(port, spd);
  
    SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
    SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
    SPI_InitStruct.CRCPoly = 10;
    
    LL_SPI_Init(port, &SPI_InitStruct);
}

/* SPI1 init function */
void *MSP_SPI1_Config(uint8_t master, uint8_t spiMode, uint32_t spd, uint8_t bitOrder)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

#if MCU_SPI1_AF_PORT == 0
    /**SPI1 GPIO Configuration  
    PA5   ------> SPI1_SCK
    PA6   ------> SPI1_MISO
    PA7   ------> SPI1_MOSI 
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_5|LL_GPIO_PIN_7;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#else
    #error SPI0 AF Port Config Not Support!
#endif

    SPI_Config(SPI1, master, spiMode, spd, bitOrder);

    //! SPI NVIC Config
    /* SPI1 interrupt Init */
//    NVIC_SetPriority(SPI1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
//    NVIC_EnableIRQ(SPI1_IRQn);
    
    return SPI1;
}

/* SPI2 init function */
void *MSP_SPI2_Config(uint8_t master, uint8_t spiMode, uint32_t spd, uint8_t bitOrder)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
    
#if MCU_SPI2_AF_PORT == 0
    /**SPI2 GPIO Configuration  
    PB13   ------> SPI2_SCK
    PB14   ------> SPI2_MISO
    PB15   ------> SPI2_MOSI 
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_13|LL_GPIO_PIN_15;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#else
    #error SPI1 AF Port Config Not Support!
#endif

    SPI_Config(SPI2, master, spiMode, spd, bitOrder);
    
    //! SPI NVIC Config
    /* SPI1 interrupt Init */
//    NVIC_SetPriority(SPI2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
//    NVIC_EnableIRQ(SPI2_IRQn);
    
    return SPI2;
}

/* SPI3 init function */
void *MSP_SPI3_Config(uint8_t master, uint8_t spiMode, uint32_t spd, uint8_t bitOrder)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
    
#if MCU_SPI3_AF_PORT == 0
    /**SPI3 GPIO Configuration  
    PB3   ------> SPI3_SCK
    PB4   ------> SPI3_MISO
    PB5   ------> SPI3_MOSI 
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_3|LL_GPIO_PIN_5;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#else
    #error SPI3 AF Port Config Not Support!
#endif

    SPI_Config(SPI3, master, spiMode, spd, bitOrder);
    
    /* SPI1 interrupt Init */
//    NVIC_SetPriority(SPI3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
//    NVIC_EnableIRQ(SPI3_IRQn);
    
    return SPI3;
}

#ifdef ENABLE_HAL_SPI_DRIVER
uint16_t msp_spi_config(struct __HAL_SPI_BUS *spi, HAL_SPI_Config_t *config)
{
    switch (spi->Atrribute.Port)
    {
        case HAL_SPI_0:
            spi->Param = MSP_SPI1_Config(config->Atrribute.Master, config->Atrribute.Mode, config->Atrribute.Speed, config->Atrribute.FirstBit);
            break;
        case HAL_SPI_1:
            spi->Param = MSP_SPI2_Config(config->Atrribute.Master, config->Atrribute.Mode, config->Atrribute.Speed, config->Atrribute.FirstBit);
            break;
        case HAL_SPI_2:
            spi->Param = MSP_SPI3_Config(config->Atrribute.Master, config->Atrribute.Mode, config->Atrribute.Speed, config->Atrribute.FirstBit);
            break;
        default:
            break;
    }
    
    return 0;
}

__STATIC_INLINE
uint8_t spi_rw_byte(SPI_TypeDef *spi, uint8_t wr, uint8_t *rd)
{
    LL_SPI_TransmitData8(spi, wr);
    
    while(LL_SPI_IsActiveFlag_TXE(spi) == 0);
    
    *rd = LL_SPI_ReceiveData8(spi);

    return 0;
}

uint8_t spi_write(SPI_TypeDef *spi, uint8_t *buf, uint16_t len)
{
    uint16_t i;
    uint8_t recv;
    uint16_t result;
    
    for (i=0; i<len; i++)
    {
        result = spi_rw_byte(spi, buf[i], &recv);
        
        if (result)
        {
            break;
        }
    }

    return i;
}

uint8_t spi_read(SPI_TypeDef *spi, uint8_t *buf, uint16_t len)
{
    uint16_t i;
    uint16_t result;
    
    for (i=0; i<len; i++)
    {
        result = spi_rw_byte(spi, 0xFF, &buf[i]);
        
        if (result)
        {
            break;
        }
    }

    return i;
}

uint8_t spi_write_and_read(SPI_TypeDef *spi, uint8_t *wr, uint8_t *rd, uint16_t len)
{
    uint16_t i;
    uint16_t result;
    
    for (i=0; i<len; i++)
    {
        result = spi_rw_byte(spi, wr[i], &rd[i]);
        
        if (result)
        {
            break;
        }
    }
    
    return i;
}

uint32_t msp_spi_transfer(struct __HAL_SPI_BUS *spi, SPI_Message_t *msg)
{
    uint8_t result;

    if (msg->EnBusSend && msg->EnBusRecv)
    {
        result = spi_write_and_read((SPI_TypeDef *)spi->Param, msg->SendBuf, msg->RecvBuf, msg->RwLen);
    }
    else if (msg->EnBusSend)
    {
        result = spi_write((SPI_TypeDef *)spi->Param, msg->SendBuf, msg->RwLen);
    }
    else
    {
        result = spi_read((SPI_TypeDef *)spi->Param, msg->RecvBuf, msg->RwLen);
    }
    
    return result;
}
#endif

/* Exported functions --------------------------------------------------------*/
void MSP_SPI_Init(void)
{
#ifdef ENABLE_MSP_SPI1_DRIVER
//    MX_SPI1_Init(&config);
#endif
   
#ifdef ENABLE_MSP_SPI2_DRIVER    
//    MX_SPI2_Init(&config);
#endif

#ifdef ENABLE_MSP_SPI3_DRIVER
//    MX_SPI3_Init(&config);
#endif
    
#ifdef ENABLE_HAL_SPI_DRIVER
    HAL_SPI_Interface_t Ops;
    
    Ops.Config   = msp_spi_config;
    Ops.Transfer = msp_spi_transfer;
    
    HAL_SPI_Register(&Ops, NULL);
#endif
}

/** @}*/     /** stm32f1xx spi drvier component */

/**********************************END OF FILE*********************************/
