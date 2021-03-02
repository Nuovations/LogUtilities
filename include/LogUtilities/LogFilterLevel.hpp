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
 *      a dynamically-configurable level setting.
 */

#ifndef LOGUTILITIES_LOGFILTERLEVEL_HPP
#define LOGUTILITIES_LOGFILTERLEVEL_HPP

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
             *    level setting.
             *
             *    The level setting is compared against the level of
             *    the message to be logged. Those messages at that
             *    level or or lower are passed. Those messages higher
             *    than that level are rejected.
             *
             *  @ingroup filter
             *
             */
            class Level :
                public Base
            {
            public:
                Level(void);
                Level(Log::Level inLevel);
                virtual ~Level(void);

                Log::Level GetLevel(void) const;
                void       SetLevel(Log::Level inLevel);

                virtual bool Allow(Log::Level inLevel);
                virtual bool Allow(Log::Level inLevel, const char * inMessage);

            private:
                Log::Level mLevel; //!< Level setting that is compared against the logged message level to determine whether messages are passed (less than or equal to @ mLevel) or rejected (greater than @a mLevel).
            };

        }; // namespace Filter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGFILTERLEVEL_HPP */
