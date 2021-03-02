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
 *      This file defines a Nuovations Log Utilities abstract formatter
 *      object.
 */

#ifndef LOGUTILITIES_LOGFORMATTERBASE_HPP
#define LOGUTILITIES_LOGFORMATTERBASE_HPP

#include <cstdarg>
#include <string>

#include "LogTypes.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Formatter
        {

            /**
             *  @brief
             *    Abstract, base log formatter object.
             *
             *  Formatters objects provide formatted output
             *  conversation of a series of binary data into a
             *  printf-style formatted message string, after that
             *  message has been filtered but before it has been
             *  written.
             *
             *  @ingroup formatter
             *
             */
            class Base
            {
            public:
                virtual ~Base(void);

                /**
                 *  @brief
                 *    Performs output format conversion on a log
                 *    message at the indicated level based on the
                 *    specified printf-style format string and the
                 *    variadic argument list.
                 *
                 *  @param[in]  inLevel   The level the current message
                 *                        is to be logged at.
                 *  @param[in]  inFormat  The log message, consisting
                 *                        of a printf-style format
                 *                        string composed of zero or
                 *                        more output conversion
                 *                        directives.
                 *  @param[in]  ...       A variadic argument list, where
                 *                        each argument corresponds
                 *                        with its peer output
                 *                        conversion directive in @a
                 *                        inFormat.
                 *
                 *  @returns
                 *     A string object containing the formatted output
                 *     message.
                 */
                virtual std::string Format(Level inLevel,
                                           const char *inFormat,
                                           ...) = 0;

                /**
                 *  @brief
                 *    Performs output format conversion on a log
                 *    message at the indicated level based on the
                 *    specified printf-style format string and the
                 *    variable argument list.
                 *
                 *  @param[in]  inLevel   The level the current message
                 *                        is to be logged at.
                 *  @param[in]  inFormat  The log message, consisting
                 *                        of a printf-style format
                 *                        string composed of zero or
                 *                        more output conversion
                 *                        directives.
                 *  @param[in]  inList    A variable argument list, where
                 *                        each argument corresponds
                 *                        with its peer output
                 *                        conversion directive in @a
                 *                        inFormat.
                 *
                 *  @returns
                 *     A string object containing the formatted output
                 *     message.
                 */
                virtual std::string Format(Level        inLevel,
                                           const char * inFormat,
                                           std::va_list inList) = 0;

                /**
                 *  @brief
                 *    Performs output format conversion on a log
                 *    message at the default level based on the
                 *    specified printf-style format string and the
                 *    variadic argument list.
                 *
                 *  @param[in]  inFormat  The log message, consisting
                 *                        of a printf-style format
                 *                        string composed of zero or
                 *                        more output conversion
                 *                        directives.
                 *  @param[in]  ...       A variadic argument list, where
                 *                        each argument corresponds
                 *                        with its peer output
                 *                        conversion directive in @a
                 *                        inFormat.
                 *
                 *  @returns
                 *     A string object containing the formatted output
                 *     message.
                 */
                virtual std::string Format(const char * inFormat, ...) = 0;

                /**
                 *  @brief
                 *    Performs output format conversion on a log
                 *    message at the default level based on the
                 *    specified printf-style format string and the
                 *    variable argument list.
                 *
                 *  @param[in]  inFormat  The log message, consisting
                 *                        of a printf-style format
                 *                        string composed of zero or
                 *                        more output conversion
                 *                        directives.
                 *  @param[in]  inList    A variable argument list, where
                 *                        each argument corresponds
                 *                        with its peer output
                 *                        conversion directive in @a
                 *                        inFormat.
                 *
                 *  @returns
                 *     A string object containing the formatted output
                 *     message.
                 */
                virtual std::string Format(const char *inFormat,
                                           std::va_list inList) = 0;

            protected:
                Base(void);
            };

        }; // namespace Formatter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGFORMATTERBASE_HPP */
