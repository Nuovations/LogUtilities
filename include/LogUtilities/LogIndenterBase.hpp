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
 *      This file defines a Nuovations Log Utilities abstract indenter
 *      object.
 */

#ifndef LOGUTILITIES_LOGINDENTERBASE_HPP
#define LOGUTILITIES_LOGINDENTERBASE_HPP

#include <string>

#include "LogTypes.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Indenter
        {

            /**
             *  @brief
             *    Abstract, base log indenter object.
             *
             *  Indenter objects provide indendentation, to a
             *  caller-specified level, of a logged message after the
             *  message has been filtered but before it is written.
             *
             *  @ingroup indenter
             *
             */
            class Base
            {
            public:
                virtual ~Base(void);

                /**
                 *  @brief
                 *    Indent the provided message to a
                 *    caller-specified level.
                 *
                 *  @param[in]  inIndent   The level of indendation
                 *                         desired for the provided
                 *                         log message.
                 *  @param[in]  inMessage  A reference to the log
                 *                         message to indent.
                 *
                 *  @returns
                 *     A reference to the indented string.
                 *
                 */
                virtual std::string & Indent(Log::Indent inIndent,
                                             std::string &inMessage) = 0;

            protected:
                Base(void);
            };

        }; // namespace Indenter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGINDENTERBASE_HPP */
