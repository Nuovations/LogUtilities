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
 *      implementation that performs sequential message filter
 *      operations on each link in a chain of filters on a single
 *      message filter operation to the chain.
 */

#ifndef LOGUTILITIES_LOGFILTERCHAIN_HPP
#define LOGUTILITIES_LOGFILTERCHAIN_HPP

#include "LogChain.hpp"
#include "LogFilterBase.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Filter
        {

            /**
             *  @brief
             *    Log writer object that performs sequential message
             *    filter operations to each link in a chain of filters
             *    on a single message filter operation to the chain.
             *
             *  @ingroup filter
             *
             */
            class Chain :
                public Log::Chain<Base>,
                public Base
            {
            public:
                Chain(void);
                virtual ~Chain(void);

                virtual bool Allow(Level inLevel);
                virtual bool Allow(Level inLevel, const char * inMessage);
            };

        }; // namespace Filter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGFILTERCHAIN_HPP */
