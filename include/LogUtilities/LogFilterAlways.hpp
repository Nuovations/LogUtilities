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
 *      implementation that always passes logged messages.
 */

#ifndef LOGUTILITIES_LOGFILTERALWAYS_HPP
#define LOGUTILITIES_LOGFILTERALWAYS_HPP

#include "LogFilterBoolean.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Filter
        {

            /**
             *  @brief
             *    Log filter object that always passes logged messages.
             *
             *  @ingroup filter
             *
             */
            class Always :
                public Boolean
            {
            public:
                Always(void);
                virtual ~Always(void);
            };

        }; // namespace Filter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGFILTERALWAYS_HPP */
