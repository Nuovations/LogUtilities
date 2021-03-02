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
 *      This file implements a Nuovations Log Utilities concrete filter
 *      implementation that performs sequential message filter
 *      operations on each link in a chain of filters on a single
 *      message filter operation to the chain.
 */

#include <LogUtilities/LogFilterChain.hpp>

namespace Nuovations
{

namespace Log
{

namespace Filter
{

Chain::Chain(void)
{
    return;
}

Chain::~Chain(void)
{
    return;
}

bool
Chain::Allow(Level inLevel)
{
    container_type::iterator current   = Container().begin();
    container_type::iterator end       = Container().end();
    bool                     willAllow = false;

    while (current != end) {
        willAllow = (*current)->Allow(inLevel);

        if (!willAllow) {
            break;
        }

        std::advance(current, 1);
    }

    return (willAllow);
}

bool
Chain::Allow(Level inLevel, const char * inMessage)
{
    container_type::iterator current   = Container().begin();
    container_type::iterator end       = Container().end();
    bool                     willAllow = false;

    while (current != end) {
        willAllow = (*current)->Allow(inLevel, inMessage);

        if (!willAllow) {
            break;
        }

        std::advance(current, 1);
    }

    return (willAllow);
}

}; // namespace Filter

}; // namespace Log

}; // namespace Nuovations
