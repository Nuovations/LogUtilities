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
 *      indenter implementation that indents logged messages using a
 *      tab (0x09) character.
 */

#include <LogUtilities/LogIndenterTab.hpp>

namespace Nuovations
{

namespace Log
{

namespace Indenter
{

static const char kTab = '\t';

/**
 *  @brief
 *    This is the class default constructor.
 *
 *    This constructor instantiates the backing String indenter with
 *    default indentation and behavior: one (1) tab (0x09) indentation
 *    character with the default behavior flags.
 *
 */
Tab::Tab(void) :
    String(kTab)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates the backing String indenter with
 *    default indentation (one (1) tab (0x09) character) and the
 *    specified behavior flags.
 *
 *  @param[in]  inFlags  The behavior flags indicating how a log
 *                       message should be indented.
 *
 */
Tab::Tab(Flags inFlags) :
    String(kTab, inFlags)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Tab::~Tab(void)
{
    return;
}

}; // namespace Indenter

}; // namespace Log

}; // namespace Nuovations
