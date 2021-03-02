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
 *      This file defines a Nuovations Log Utilities concrete
 *      formatter object that prepends each logged message with a
 *      formatted information stamp.
 */

#ifndef LOGUTILITIES_LOGFORMATTERSTAMPED_HPP
#define LOGUTILITIES_LOGFORMATTERSTAMPED_HPP

#include "LogFormatterPlain.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Formatter
        {

            /**
             *  @brief
             *    Log formatter object that prepends each formatted
             *    log message with a formatted information stamp.
             *
             *  The formatted information stamp is of the form:
             *
             *      <year>-<month>-<day> <hour>:<minute>:<second> [\<PID\>:<thread>] (<level>) <message>
             *
             *  where @a PID is the process identification number,
             *  @a thread is the POSIX thread identifier/object pointer
             *  returned by pthread_self, and @a level is the level the
             *  logged message was specified at.
             *
             *  @ingroup formatter
             *
             */
            class Stamped :
                public Plain
            {
            public:
                Stamped(void);
                virtual ~Stamped(void);

                // Format with the specified level

                virtual std::string Format(Level inLevel,
                                           const char *inFormat,
                                           ...) _LOG_CHECK_FORMAT(3, 4);
                virtual std::string Format(Level inLevel,
                                           const char *inFormat,
                                           std::va_list inList) _LOG_CHECK_FORMAT(3, 0);

                // Format with level zero (0)

                virtual std::string Format(const char *inFormat,
                                           ...) _LOG_CHECK_FORMAT(2, 3);
                virtual std::string Format(const char *inFormat,
                                           std::va_list inList) _LOG_CHECK_FORMAT(2, 0);
            };

        }; // namespace Formatter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGFORMATTERSTAMPED_HPP */
