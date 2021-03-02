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
 *      This file defines a Nuovations Log Utilities abstract filter
 *      object.
 */

#ifndef LOGUTILITIES_LOGFILTERBASE_HPP
#define LOGUTILITIES_LOGFILTERBASE_HPP

#include "LogTypes.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Filter
        {

            /**
             *  @brief
             *    Abstract, base log filter object.
             *
             *  Filter objects allow rejection or passing of logged
             *  messaged based on the specified level or message
             *  content, either before they are indented and formatted
             *  or before they are written.
             *
             *  @ingroup filter
             *
             */
            class Base
            {
            public:
                virtual ~Base(void);

                /**
                 *  @brief
                 *    Pass or reject a message based on the specified
                 *    level (unused) and the instantiated Boolean
                 *    state of the filter.
                 *
                 *  @param[in]  inLevel  The level the current message
                 *                       is to be logged at.
                 *
                 *  @returns
                 *    True if the log message should be passed;
                 *    otherwise, false, if the message should be
                 *    rejected based on the instantiated Boolean state
                 *    of the filter.
                 */
                virtual bool Allow(Level inLevel) = 0;

                /**
                 *  @brief
                 *    Pass or reject a message based on the specified
                 *    level (unused), the message to be logged, and
                 *    the instantiated Boolean state of the filter.
                 *
                 *  @param[in]  inLevel    The level the current message
                 *                         is to be logged at.
                 *  @param[in]  inMessage  The log message to be filtered.
                 *
                 *  @returns
                 *    True if the log message should be passed;
                 *    otherwise, false, if the message should be
                 *    rejected based on the instantiated Boolean state
                 *    of the filter.
                 */
                virtual bool Allow(Level inLevel, const char * inMessage) = 0;

            protected:
                Base(void);
            };

        }; // namespace Filter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGFILTERBASE_HPP */
