/**
 *******************************************************************************
 * @file       bsp_led.c                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-01-18                                                      *
 * @brief      led board support packet                                        *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 3. 2019-03-11  使用MSP LV1接口实现                                          *
 * 2. 2018-01-18  使用HAL LV1接口实现                                          *
 * 1. 2018-01-18  创建文件                                                     *
 *******************************************************************************
 */
 
/**
 * @defgroup led board support packet
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

/* Private define ------------------------------------------------------------*/
//! 定义LED数量
#define BSP_LED_MAX                                     _dimof(BOARD_LED_CONFIG)

//! 定义LED状态
#define LED_IDLE_STATE                                                      0x00
#define LED_OFF_STATE                                                       0x01
#define LED_ON_STATE                                                        0x02

//! 定义LED配置参数
//! 低电平点亮LED
#define LED_DRV_HIGH_FLAG                                                   0x01
//! 高电平点亮LED
#define LED_DRV_LOW_FLAG                                                    0x00

#define LED_IS_HIGH_DRV(x)         (Fw_Flag_Get(LED_FLAG(x), LED_DRV_HIGH_FLAG))

//! 定义LED端口
#define LED_PORT(x)                                   (BOARD_LED_CONFIG[x].Port)
#define LED_PIN(x)                                     (BOARD_LED_CONFIG[x].Pin)
#define LED_FLAG(x)                                                  ((x)->Flag)
#define LED_STATE(x)                                                ((x)->State)
#define LED_COUNT(x)                                                ((x)->Count)
#define LED_TIMEOUT(x)                                            ((x)->Timeout)
#define LED_TIMER(x)                                                ((x)->Timer)
#define LED_HANDLE(x)                                     (&BOARD_LED_CONFIG[x])

/* Private typedef -----------------------------------------------------------*/
//! 按键句柄定义
typedef struct 
{
    //! 硬件IO端口
    uint8_t  Port;
    uint8_t  Pin;
      
    //! 标志位设置
    uint8_t Flag;
    
    //! 当前状态
    uint8_t State;
    
    //! 闪烁次数
    uint16_t Count;
    
    //! 闪烁超时时间
    uint16_t Timeout;
    
    //! 定时器
    uint16_t Timer;
}Led_Handle_t;

#ifdef ENABLE_LED_SUPER_COMPONENT
FwTimer_t LedTimer;
#endif

/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Led_Handle_t BOARD_LED_CONFIG[] =
{
    {.Port = LED1_PORT, .Pin = LED1_PIN,  .Flag = LED_DRV_LOW_FLAG},
    {.Port = LED2_PORT, .Pin = LED2_PIN,  .Flag = LED_DRV_LOW_FLAG},
    {.Port = LED3_PORT, .Pin = LED3_PIN,  .Flag = LED_DRV_LOW_FLAG},
};

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
__STATIC_INLINE 
void Led_Pin_On(Led_Handle_t *led)
{
    if (LED_IS_HIGH_DRV(led))
    {
        MSP_Pin_Set(led->Port, led->Pin);
    }
    else
    {
        MSP_Pin_Clr(led->Port, led->Pin);
    }
}

__STATIC_INLINE
void Led_Pin_Off(Led_Handle_t *led)
{
    if (LED_IS_HIGH_DRV(led))
    {
        MSP_Pin_Clr(led->Port, led->Pin);
    }
    else
    {
        MSP_Pin_Set(led->Port, led->Pin);
    }
}

__STATIC_INLINE
void Led_Module_On(Led_Handle_t *led)
{
    Led_Pin_On(led);
    
    led->Timer   = 0;
    led->Timeout = 0;
    led->Count   = 0;
    led->State   = LED_ON_STATE;
}

__STATIC_INLINE
void Led_Module_Off(Led_Handle_t *led)
{
    Led_Pin_Off(led);
    
    led->Timer   = 0;
    led->Timeout = 0;
    led->Count   = 0;
    led->State   = LED_OFF_STATE;
}

void Led_Blink_Handle(void *param)
{
    uint8_t i;
    
    for (i=0; i<BSP_LED_MAX; i++)
    {
        Led_Handle_t *led = LED_HANDLE(i);
        
        switch (led->State)
        {
            case LED_ON_STATE:
                Led_Pin_Off(led);
                led->State = LED_OFF_STATE;
                break;
            case LED_OFF_STATE:
                if (led->Count <= 1)
                {
                    Led_Module_Off(led);
                }
                else
                {
                    led->Count --;

                    Led_Pin_On(led);
                    led->State = LED_ON_STATE;
                }
                break;
            case LED_IDLE_STATE:
                break;
            default:
                Led_Module_Off(led);
                break;
        }
    }
}

__STATIC_INLINE
void Board_Led_Init(void)
{
    uint16_t i;

    for (i=0; i<BSP_LED_MAX; i++)
    {
        MSP_Pin_Output(LED_PORT(i), LED_PIN(i));
        BSP_Led_Off(i);
    }
}

/* Exported functions --------------------------------------------------------*/
int BSP_Led_Init(void)
{
    Board_Led_Init();
    
#ifdef ENABLE_LED_SUPER_COMPONENT
    Fw_Timer_Init(&LedTimer, "[BSP]Led Timer", Led_Blink_Handle, NULL, 10, FW_TIM_EN_PERIOD);
    Fw_Timer_Start(&LedTimer);
#endif
    
    return 0;
}
INIT_BOARD_EXPORT(BSP_Led_Init);

void BSP_Led_On(uint8_t id)
{
    Led_Handle_t *led = LED_HANDLE(id);
    
    Led_Module_On(led);
    
    led->State = LED_IDLE_STATE;
}

void BSP_Led_Off(uint8_t id)
{
    Led_Handle_t *led = LED_HANDLE(id);
    
    Led_Module_Off(led);
    
    led->State = LED_IDLE_STATE;
}

void BSP_Led_Control(uint8_t id, int16_t count, uint16_t tick)
{
    Led_Handle_t *led = LED_HANDLE(id);
    
    Led_Pin_On(led);
    
    led->Timer   = 0;
    led->Timeout = tick;
    led->Count   = count;
    led->State   = LED_ON_STATE;
}

void BSP_Led_Handle(void)
{
    uint16_t i;
    
    for (i=0; i<BSP_LED_MAX; i++)
    {
        Led_Blink_Handle(LED_HANDLE(i));
    }
}

/** @}*/     /** led driver application component */

/**********************************END OF FILE*********************************/
