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
 *      This file implements a Nuovations Log Utilities concrete
 *      indenter implementation that indents logged messages using one
 *      or more space (' ') characters.
 */

#include <LogUtilities/LogIndenterSpace.hpp>

namespace Nuovations
{

namespace Log
{

namespace Indenter
{

static const char   kSpace = ' ';
static const size_t kCount = 4;

/**
 *  @brief
 *    This is the class default constructor.
 *
 *    This constructor instantiates the backing String indenter with
 *    default indentation and behavior: four (4) space (' ')
 *    indentation characters with the default behavior flags.
 *
 */
Space::Space(void) :
    String(kSpace, kCount)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates the backing String indenter with
 *    default indentation (four (4) space (' ') characters) and the
 *    specified behavior flags.
 *
 *  @param[in]  inFlags  The behavior flags indicating how a log
 *                       message should be indented.
 *
 */
Space::Space(Flags inFlags) :
    String(kSpace, kCount, inFlags)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates the backing String indenter with
 *    the specified number of space (' ') indentation characters and
 *    the default behavior flags.
 *
 *  @param[in]  inCount  The number of space (' ') characters to use
 *                       as the indent.
 *
 */
Space::Space(size_t inCount) :
    String(kSpace, inCount)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates the backing String indenter with
 *    the specified number of space (' ') indentation characters and
 *    behavior flags.
 *
 *  @param[in]  inCount  The number of space (' ') characters to use
 *                       as the indent.
 *  @param[in]  inFlags  The behavior flags indicating how a log
 *                       message should be indented.
 *
 */
Space::Space(size_t inCount, Flags inFlags) :
    String(kSpace, inCount, inFlags)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Space::~Space(void)
{
    return;
}

}; // namespace Indenter

}; // namespace Log

}; // namespace Nuovations
