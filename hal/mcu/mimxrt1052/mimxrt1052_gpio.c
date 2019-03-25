/**
 *******************************************************************************
 * @file       mimxrt1052_gpio.c                                               *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-09-09                                                      *
 * @brief      mimxrt1052 gpio driver component                                *
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
 * @defgroup mimxrt1052 gpio driver component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_msp.h"

/* Private define ------------------------------------------------------------*/
#define GPIO_BASE_POS (GPIOB_BASE - GPIOA_BASE)

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
//__STATIC_INLINE
//GPIO_T *MSP_GPIO_Base_Get(uint16_t port)
//{
//    return (GPIO_T *)(GPIOA_BASE + port * GPIO_BASE_POS);
//}

//__STATIC_INLINE
//uint32_t MSP_GPIO_PinMask_Get(uint16_t pin)
//{
//    return (uint32_t)(1 << pin);
//}

//__STATIC_INLINE
//uint32_t MSP_GPIO_ModeMask_Get(uint16_t mode)
//{
//    const uint32_t modeParam[] = {GPIO_PMD_INPUT, GPIO_PMD_OUTPUT, GPIO_PMD_INPUT, GPIO_PMD_OUTPUT, GPIO_PMD_INPUT};
//    
//    return modeParam[mode];
//}

#ifdef ENABLE_HAL_GPIO_DRIVER
static void pin_init(HAL_Device_t *dev, uint32_t pin, uint16_t mode)
{
//    GPIO_T *port = MSP_GPIO_Base_Get(HAL_PORT(pin));
//    uint32_t modeParam = MSP_GPIO_ModeMask_Get(mode);
//    
//    MSP_GPIO_Config(port, HAL_PIN(pin), modeParam);
}

static void pin_write(HAL_Device_t *dev, uint32_t pin, uint32_t value)
{
//    GPIO_T *port = MSP_GPIO_Base_Get(HAL_PORT(pin));
//    uint32_t pinMask = MSP_GPIO_PinMask_Get(HAL_PIN(pin));

//    if (value)
//    {
//        _set_reg(port->DOUT, pinMask);
//    }
//    else
//    {
//        _clr_reg(port->DOUT, pinMask);
//    }
}

static void pin_toggle(HAL_Device_t *dev, uint32_t pin)
{
//    GPIO_T *port = MSP_GPIO_Base_Get(HAL_PORT(pin));
//    uint32_t pinMask = MSP_GPIO_PinMask_Get(HAL_PIN(pin));

//    if (_get_reg(port->PIN, pinMask))
//    {
//        _clr_reg(port->DOUT, pinMask);
//    }
//    else
//    {
//        _set_reg(port->DOUT, pinMask);
//    }
}

static uint32_t pin_read(HAL_Device_t *dev, uint32_t pin)
{
//    GPIO_T *port = MSP_GPIO_Base_Get(HAL_PORT(pin));
//    uint32_t pinMask = MSP_GPIO_PinMask_Get(HAL_PIN(pin));

//    return _read_reg(port->PIN & pinMask);
    
    return 0;
}
#endif

///* Exported functions --------------------------------------------------------*/
__INLINE
void MSP_GPIO_Config(GPIO_Type *port, uint32_t pin, uint32_t mode)
{
//    uint32_t clr = ~(0x03 << (pin << 1));
//    uint32_t set = (mode << (pin << 1));
//    
//    port->MODE &= clr;
//    port->MODE |= set;
}

__INLINE
void MSP_GPIO_Set(GPIO_Type *port, uint32_t pin)
{
    _set_bit(port->DR, pin);
}

__INLINE
void MSP_GPIO_Clr(GPIO_Type *port, uint32_t pin)
{
    _clr_bit(port->DR, pin);
}

__INLINE
void MSP_GPIO_Toggle(GPIO_Type *port, uint32_t pin)
{
    _xor_bit(port->DR, pin);
}

__INLINE
uint32_t MSP_GPIO_Get(GPIO_Type *port, uint32_t pin)
{
    return _read_bit(port->PSR, pin);
}

__INLINE 
void MSP_GPIO_Write(GPIO_Type *port, uint32_t wr)
{
    _write_reg(port->DR, wr);
}

__INLINE uint32_t MSP_GPIO_Read(GPIO_Type *port)
{
    return _read_reg(port->PSR);
}

void MSP_GPIO_Init(void)
{
    //! 使能IO复用时钟
    CLOCK_EnableClock(kCLOCK_Iomuxc);
    
#ifdef ENABLE_HAL_GPIO_DRIVER
    HAL_Port_Interface_t PinOps;

    PinOps.Init   = pin_init;
    PinOps.Read   = pin_read;
    PinOps.Write  = pin_write;
    PinOps.Toggle = pin_toggle;
    
    HAL_Pin_Register(&PinOps, NULL);
#endif
}

/** @}*/     /** mimxrt1052 gpio driver component */

/**********************************END OF FILE*********************************/
