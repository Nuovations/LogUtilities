/*
 *    Copyright (c) 2008-2021 Nuovation System Designs, LLC
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      This file defines Nuovations Log Utilities global logger
 *      instances and utility interfaces for working with those (or
 *      other) instances.
 */

#ifndef LOGUTILITIES_LOGGLOBALS_HPP
#define LOGUTILITIES_LOGGLOBALS_HPP

#include "LogLogger.hpp"

namespace Nuovations
{

    namespace Log
    {

        extern Logger & Debug(void);
        extern Logger & Info(void);
        extern Logger & Error(void);

        extern bool GetFilter(const Logger & inLogger,
                              Log::Level &   outLevel,
                              bool &         outQuiet);
        extern bool SetFilter(Logger &   inLogger,
                              Log::Level inLevel,
                              bool       inQuiet);

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGGLOBALS_HPP */
