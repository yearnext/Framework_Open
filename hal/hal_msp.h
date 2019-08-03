/**
 *******************************************************************************
 *                 Copyright (C) 2017 - 2019  Accumulate Team                  *
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
 * @file       hal_msp.h                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-09-08                                                      *
 * @brief      hal msp layer file                                              *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 20180908 Create File                                                     *
 * 2. 20181217 新增STM32L476 MSP包                                             *
 *******************************************************************************
 */
#include "compiler.h"

#if BOARD_PALTFORM == USE_PALTFORM_SIMULATION
#include "mcu/simulation/msp_simulation.h"
#elif BOARD_PALTFORM == USE_PALTFORM_QT
#include "mcu/qt/msp_qt.h"
#elif BOARD_PALTFORM == USE_PALTFORM_N76E003
#include "mcu/n76e003/msp_n76e003.h"
#elif BOARD_PALTFORM == USE_PALTFORM_NUC029LAN
#include "mcu/nuc029lan/msp_nuc029lan.h"
#elif BOARD_PALTFORM == USE_PALTFORM_NANO103
#include "mcu/nano103/msp_nano103.h"
#elif BOARD_PALTFORM == USE_PALTFORM_STM8L05x
#include "mcu/stm8l05x/msp_stm8l05x.h"
#elif BOARD_PALTFORM == USE_PALTFORM_STM32L05x
#include "mcu/stm32l05x/msp_stm32l05x.h"
#elif BOARD_PALTFORM == USE_PALTFORM_STM32L4xx
#include "mcu/stm32l476/msp_stm32l476.h"
#elif BOARD_PALTFORM == USE_PALTFORM_STM32F1xx
#include "mcu/stm32f1xx/msp_stm32f1xx.h"
#elif BOARD_PALTFORM == USE_PALTFORM_HC32L13x
#include "mcu/hc32l13x/msp_hc32l13x.h"
#elif BOARD_PALTFORM == USE_PALTFORM_MIMXRT1052
#include "mcu/mimxrt1052/msp_mimxrt1052.h"
#else
#error Not Support Device!
#endif

/**********************************END OF FILE*********************************/
