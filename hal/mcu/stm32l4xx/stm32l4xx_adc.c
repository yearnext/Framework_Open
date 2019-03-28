/**
 *******************************************************************************
 * @file       stm32l4xx_adc.c                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2019-03-29                                                      *
 * @brief      stm32l4xx adc driver component                                  *
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
 * @defgroup stm32l4xx adc driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_msp.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
const uint32_t ADC_CH_Mask[] = 
{
    LL_ADC_CHANNEL_0,  LL_ADC_CHANNEL_1,  LL_ADC_CHANNEL_2,  LL_ADC_CHANNEL_3,
    LL_ADC_CHANNEL_4,  LL_ADC_CHANNEL_5,  LL_ADC_CHANNEL_6,  LL_ADC_CHANNEL_7,
    LL_ADC_CHANNEL_8,  LL_ADC_CHANNEL_9,  LL_ADC_CHANNEL_10, LL_ADC_CHANNEL_11,
    LL_ADC_CHANNEL_12, LL_ADC_CHANNEL_13, LL_ADC_CHANNEL_14, LL_ADC_CHANNEL_15,
    LL_ADC_CHANNEL_16, LL_ADC_CHANNEL_17, LL_ADC_CHANNEL_18,
};

/* Private variables ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#ifdef ENABLE_HAL_ADC_DRIVER
static uint32_t adc_config(HAL_ADC_t *adc, HAL_ADC_Config_t *config)
{
    MSP_ADC_Channel_Init(config->Atrribute.Channel);
    
    if (!IS_PTR_NULL(adc))
    {
        adc->Param = (void *)ADC;
    }
    
    return 0;
}

//static uint32_t adc_convert(HAL_ADC_t *adc, uint16_t channel, uint8_t mode)
//{
//    return MSP_ADC_Convert(_bv(channel));
//}

//static void adc_start(HAL_ADC_t *adc, uint16_t channel)
//{
//    MSP_ADC_Start(channel);
//}

static uint32_t adc_get_value(HAL_ADC_t *adc, uint16_t channel)
{
    return (uint32_t)MSP_ADC_GetValue(channel);
}
#endif

void MSP_ADC_Init(void)
{
#ifdef ENABLE_MSP_ADC_CH0_DRIVER
    MSP_ADC_Channel_Init(0);
#endif
    
#ifdef ENABLE_MSP_ADC_CH1_DRIVER
    MSP_ADC_Channel_Init(1);
#endif
    
#ifdef ENABLE_MSP_ADC_CH2_DRIVER
    MSP_ADC_Channel_Init(2);
#endif
    
#ifdef ENABLE_MSP_ADC_CH3_DRIVER
    MSP_ADC_Channel_Init(3);
#endif

#ifdef ENABLE_MSP_ADC_CH4_DRIVER
    MSP_ADC_Channel_Init(4);
#endif

#ifdef ENABLE_MSP_ADC_CH5_DRIVER
    MSP_ADC_Channel_Init(5);
#endif

#ifdef ENABLE_MSP_ADC_CH6_DRIVER
    MSP_ADC_Channel_Init(6);
#endif

#ifdef ENABLE_MSP_ADC_CH7_DRIVER
    MSP_ADC_Channel_Init(7);
#endif

#ifdef ENABLE_HAL_ADC_DRIVER
    HAL_ADC_Interface_t ops;

    ops.Config   = adc_config;
    ops.GetValue = adc_get_value;
    
    HAL_ADC_Register(&ops, NULL);
#endif
}

//    ADC1 GPIO Configuration  
//    PC0   ------> ADC1_IN1
//    PC1   ------> ADC1_IN2
//    PC2   ------> ADC1_IN3
//    PC3   ------> ADC1_IN4
//    PA0   ------> ADC1_IN5
//    PA1   ------> ADC1_IN6
//    PA2   ------> ADC1_IN7
//    PA3   ------> ADC1_IN8
//    PA4   ------> ADC1_IN9
//    PA5   ------> ADC1_IN10
//    PA6   ------> ADC1_IN11
//    PA7   ------> ADC1_IN12
//    PC4   ------> ADC1_IN13
//    PC5   ------> ADC1_IN14
//    PB0   ------> ADC1_IN15
//    PB1   ------> ADC1_IN16
void MSP_ADC_Channel_Init(uint16_t ch)
{
    LL_ADC_InitTypeDef ADC_InitStruct;
    LL_ADC_REG_InitTypeDef ADC_REG_InitStruct;
    LL_ADC_CommonInitTypeDef ADC_CommonInitStruct;

    LL_GPIO_InitTypeDef GPIO_InitStruct;
  
    /* Peripheral clock enable */
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC);

    switch (ch)
    {
        case HAL_ADC_CH0:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOC, LL_GPIO_PIN_0);
            break;
        case HAL_ADC_CH1:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOC, LL_GPIO_PIN_1);
            break;
        case HAL_ADC_CH2:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOC, LL_GPIO_PIN_2);
            break;
        case HAL_ADC_CH3:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOC, LL_GPIO_PIN_3);
            break;
        case HAL_ADC_CH4:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOA, LL_GPIO_PIN_0);
            break;
        case HAL_ADC_CH5:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOA, LL_GPIO_PIN_1);
            break;
        case HAL_ADC_CH6:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOA, LL_GPIO_PIN_2);
            break;
        case HAL_ADC_CH7:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOA, LL_GPIO_PIN_3);
            break;
        case HAL_ADC_CH8:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOA, LL_GPIO_PIN_4);
            break;
        case HAL_ADC_CH9:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOA, LL_GPIO_PIN_5);
            break;
        case HAL_ADC_CH10:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOA, LL_GPIO_PIN_6);
            break;
        case HAL_ADC_CH11:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOA, LL_GPIO_PIN_7);
            break;
        case HAL_ADC_CH12:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOC, LL_GPIO_PIN_4);
            break;
        case HAL_ADC_CH13:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOC, LL_GPIO_PIN_5);
            break;
        case HAL_ADC_CH14:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOB, LL_GPIO_PIN_0);
            break;
        case HAL_ADC_CH15:
            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

            GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
            GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
            LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        
            LL_GPIO_EnablePinAnalogControl(GPIOB, LL_GPIO_PIN_1);
            break;    
        default:
            break;
    }
    
    //! ADC时钟初始化
    ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_ASYNC_DIV1;
    ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
    LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);
    
    //! ADC初始化
    ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
    ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
    ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
    LL_ADC_Init(ADC1, &ADC_InitStruct);
    //! ADC工作模式初始化
    ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
    ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
    ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
    ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
    ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
    ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
    LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
    
    LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE);
    LL_ADC_DisableIT_EOC(ADC1);
    LL_ADC_DisableIT_EOS(ADC1);
    /* Disable ADC deep power down (enabled by default after reset state) */
    LL_ADC_DisableDeepPowerDown(ADC1);
    /* Enable ADC internal voltage regulator */
    LL_ADC_EnableInternalRegulator(ADC1);
    /* Run ADC self calibration */
    LL_ADC_StartCalibration(ADC1, LL_ADC_SINGLE_ENDED);
    while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0);

    /* Enable ADC */
    LL_ADC_Enable(ADC1);
    while (LL_ADC_IsActiveFlag_ADRDY(ADC1) == 0);
}

void MSP_ADC_Start(uint16_t ch)
{
    //! 设置转化通道
    LL_ADC_SetChannelSamplingTime(ADC1, ADC_CH_Mask[ch], LL_ADC_SAMPLINGTIME_47CYCLES_5);
    LL_ADC_SetChannelSingleDiff(ADC1, ADC_CH_Mask[ch], LL_ADC_SINGLE_ENDED);
    //! 启动转换
    LL_ADC_REG_StartConversion(ADC1);
}

uint16_t MSP_ADC_GetValue(uint16_t ch)
{
    if (LL_ADC_IsActiveFlag_EOC(ADC1))
    {
        LL_ADC_ClearFlag_EOC(ADC1);
        
        return LL_ADC_REG_ReadConversionData12(ADC1);
    }
    
    return 0xFFFF;
}

uint16_t MSP_ADC_Convert(uint16_t ch)
{
    uint16_t value;
    
    //! 设置转化通道
    LL_ADC_SetChannelSamplingTime(ADC1, ADC_CH_Mask[ch], LL_ADC_SAMPLINGTIME_47CYCLES_5);
    LL_ADC_SetChannelSingleDiff(ADC1, ADC_CH_Mask[ch], LL_ADC_SINGLE_ENDED);
    //! 启动转换
    LL_ADC_REG_StartConversion(ADC1);
    
    do
    {
        value = MSP_ADC_GetValue(ch);
    }
    while(value == 0xFFFF);

    return value;
}

/** @}*/     /** stm32l4xx adc driver component */

/**********************************END OF FILE*********************************/
