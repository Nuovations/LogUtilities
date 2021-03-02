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
 *      This file implements a Nuovations Log Utilities concrete writer
 *      implementation that performs sequential writes to each link in
 *      a chain of writers on a single write to the chain.
 */

#include <LogUtilities/LogWriterChain.hpp>

namespace Nuovations
{

namespace Log
{

namespace Writer
{

Chain::Chain(void)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Chain::~Chain(void)
{
    return;
}

void
Chain::Write(Level inLevel, const char * inMessage)
{
    container_type::iterator current = Container().begin();
    container_type::iterator end     = Container().end();

    while (current != end) {
        (*current)->Write(inLevel, inMessage);

        advance(current, 1);
    }
}

void
Chain::Write(const char * inMessage)
{
    Write(0, inMessage);
}

}; // namespace Writer

}; // namespace Log

}; // namespace Nuovations
