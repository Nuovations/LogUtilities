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
 *      formatter object that simply performs format output
 *      conversion on the specified message using the supplied
 *      arguments.
 */

#ifndef LOGUTILITIES_LOGFORMATTERPLAIN_HPP
#define LOGUTILITIES_LOGFORMATTERPLAIN_HPP

#include <cstdarg>
#include <string>

#include "LogFormatterBase.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Formatter
        {

            /**
             *  @brief
             *    Log formatter object that simply performs format
             *    output conversion on the specified message using the
             *    supplied arguments.
             *
             *  @ingroup formatter
             *
             */
            class Plain :
                public Base
            {
            public:
                Plain(void);
                virtual ~Plain(void);

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

#endif /* LOGUTILITIES_LOGFORMATTERPLAIN_HPP */
