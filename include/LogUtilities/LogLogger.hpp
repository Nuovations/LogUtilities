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
 *      This file defines a Nuovations Log Utilities logger object.
 */

#ifndef LOGUTILITIES_LOGLOGGER_HPP
#define LOGUTILITIES_LOGLOGGER_HPP

#include <cstdarg>
#include <string>

#include "LogFilterBase.hpp"
#include "LogFormatterBase.hpp"
#include "LogIndenterBase.hpp"
#include "LogTypes.hpp"
#include "LogWriterBase.hpp"

namespace Nuovations
{
    namespace Log
    {

        /**
         *  @brief
         *    Generic, instantiable logger object for logging
         *    (including filtering, formatting, and writing) formatted
         *    messages.
         *
         *    A logger consists of a filter, indenter, formatter, and
         *    writer. The filter is used to pass or reject messages
         *    either before indenting and formatting or after those
         *    but before writing based on the logged level and message
         *    content. The indenter is used to potentially indent
         *    messages based on the logged level. The formatter is
         *    used for output conversion of specified arguments to a
         *    printf-style format message string. The writer is used
         *    to output the indented and formatted message to an
         *    output destination.
         */
        class Logger
        {
        public:
            Logger(Filter::Base &    inFilter,
                   Indenter::Base &  inIndenter,
                   Formatter::Base & inFormatter,
                   Writer::Base &    inWriter);
            virtual ~Logger(void);

            Filter::Base &       GetFilter(void);
            const Filter::Base & GetFilter(void) const;
            void                 SetFilter(Filter::Base & inFilter);

            Indenter::Base &       GetIndenter(void);
            const Indenter::Base & GetIndenter(void) const;
            void                   SetIndenter(Indenter::Base & inIndenter);

            Formatter::Base &       GetFormatter(void);
            const Formatter::Base & GetFormatter(void) const;
            void                    SetFormatter(Formatter::Base & inFormatter);

            Writer::Base &       GetWriter(void);
            const Writer::Base & GetWriter(void) const;
            void                 SetWriter(Writer::Base & inWriter);

            // Write with indent and level specified.

            void Write(Log::Indent  inIndent,
                       Log::Level   inLevel,
                       const char * inFormat,
                       ...) _LOG_CHECK_FORMAT(4, 5);
            void Write(Log::Indent  inIndent,
                       Log::Level   inLevel,
                       const char * inFormat,
                       std::va_list inArguments) _LOG_CHECK_FORMAT(4, 0);

            // Write with no indent and level specified.

            void Write(Log::Level   inLevel,
                       const char * inFormat,
                       ...) _LOG_CHECK_FORMAT(3, 4);
            void Write(Log::Level   inLevel,
                       const char * inFormat,
                       std::va_list inArguments) _LOG_CHECK_FORMAT(3, 0);

            // Write with no ident at level zero (0).

            void Write(const char * inFormat,
                       ...) _LOG_CHECK_FORMAT(2, 3);
            void Write(const char * inFormat,
                       std::va_list inArguments) _LOG_CHECK_FORMAT(2, 0);

        private:
            Filter::Base *    mFilter;
            Indenter::Base *  mIndenter;
            Formatter::Base * mFormatter;
            Writer::Base *    mWriter;
        };

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGLOGGER_HPP */
