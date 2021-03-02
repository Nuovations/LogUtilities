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
 *      This file defines a Nuovations Log Utilities base, derivable
 *      filter implementation that passes logged messages based on the
 *      instantiated Boolean value.
 */

#ifndef LOGUTILITIES_LOGFILTERBOOLEAN_HPP
#define LOGUTILITIES_LOGFILTERBOOLEAN_HPP

#include "LogFilterBase.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Filter
        {

            /**
             *  @brief
             *    Base, derivable log filter object that passes logged
             *    messages based on the instantiated Boolean value.
             *
             *  @ingroup filter
             *
             */
            class Boolean :
                public Base
            {
            public:
                virtual ~Boolean(void);

                virtual bool Allow(Level inLevel);
                virtual bool Allow(Level inLevel, const char * inMessage);

            protected:
                Boolean(bool inAllow);

            private:
                bool mAllow;
            };

        }; // namespace Filter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGFILTERBOOLEAN_HPP */
