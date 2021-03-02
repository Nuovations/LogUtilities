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
 *      This file defines a Nuovations Log Utilities abstract writer
 *      object.
 *
 */

#ifndef LOGUTILITIES_LOGWRITERBASE_HPP
#define LOGUTILITIES_LOGWRITERBASE_HPP

#include "LogTypes.hpp"

namespace Nuovations
{
    namespace Log
    {

        namespace Writer
        {

            /**
             *  @brief
             *    Abstract, base log writer object.
             *
             *  Writer objects are the finalizers in a logger instance
             *  that take a filtered, indented, and formatted message
             *  and write it to an output destination.
             *
             *  @ingroup writer
             *
             */
            class Base
            {
            public:
                virtual ~Base(void);

                /**
                 *  @brief
                 *    Write a log message at the specified level.
                 *
                 *  @param[in]  inLevel    The level the current message
                 *                         is to be logged at.
                 *  @param[in]  inMessage  The log message to write.
                 *
                 */
                virtual void Write(Level inLevel, const char * inMessage) = 0;

                /**
                 *  @brief
                 *    Write a log message at the default level.
                 *
                 *  @param[in]  inMessage  The log message to write.
                 *
                 */
                virtual void Write(const char * inMessage) = 0;

            protected:
                Base(void);
            };

        }; // namespace Writer

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGWRITERBASE_HPP */
