/******************************************************************************
 *
 * This file is part of Log4Qt library.
 *
 * Copyright (C) 2007 - 2020 Log4Qt contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#include "loggerstatic.h"

#include "log4qt/logger.h"
#include "log4qt/logmanager.h"

LOG4QT_DECLARE_STATIC_LOGGER(logger, LoggerStatic)

LoggerStatic::LoggerStatic()
{
    logger()->trace() << "ctor Debug output";
    logger()->info() << "Log4Qt Version String: " << Log4Qt::LogManager::version();
    logger()->info() << "Log4Qt Version Number: " << Log4Qt::LogManager::versionNumber().toString();
}

LoggerStatic::~LoggerStatic()
{
    logger()->trace() << "dtor Debug output";
}
