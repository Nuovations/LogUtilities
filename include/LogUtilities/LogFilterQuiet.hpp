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
 *      This file defines a Nuovations Log Utilities concrete filter
 *      implementation that passes or rejects logged messages based on
 *      a dynamically-configurable runtime quiet/verbose setting.
 */

#ifndef LOGUTILITIES_LOGFILTERQUIET_HPP
#define LOGUTILITIES_LOGFILTERQUIET_HPP

#include "LogFilterBase.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Filter
        {

            /**
             *  @brief
             *    Log filter object that passes or rejects logged
             *    messages based on a dynamically-configurable runtime
             *    quiet/verbose setting.
             *
             *  @ingroup filter
             *
             */
            class Quiet :
                public Base
            {
            public:
                Quiet(void);
                Quiet(bool inQuiet);
                virtual ~Quiet(void);

                bool GetQuiet(void) const;
                void SetQuiet(bool inQuiet);

                virtual bool Allow(Log::Level inLevel);
                virtual bool Allow(Log::Level inLevel, const char * inMessage);

            private:
                bool mQuiet; //!< Quiet setting that determines whether messages are passed (false) or rejected (true).
            };

        }; // namespace Filter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGFILTERQUIET_HPP */
