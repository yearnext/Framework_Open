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
 * @file       fw_qt.h                                                         *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2019-05-26                                                      *
 * @brief      framework qt support component head file                        *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20190526    Create File                                                   *
 *******************************************************************************
 */

/**
 * @defgroup framework qt support component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FRAMEWORK_QT_SUPPORT_H__
#define FRAMEWORK_QT_SUPPORT_H__

/* Includes ------------------------------------------------------------------*/
#include <QObject>
#include <QThread>
#include <QDebug>
#include "compiler.h"
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class FwServer : public QThread
{
public:
	FwServer(QObject *parent = nullptr);
	~FwServer();

protected:
	virtual void run();

private:
	bool enableCore;

	void coreInit();
	void coreRun();
	void coreExit();
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#endif       /** end include define */

/** @}*/     /** framework qt support component */

/**********************************END OF FILE*********************************/
