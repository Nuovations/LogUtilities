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
 *      implementation that passes or rejects logged messages based on
 *      a dynamically-configurable runtime quiet/verbose setting.
 */

#include <LogUtilities/LogFilterQuiet.hpp>

namespace Nuovations
{

namespace Log
{

namespace Filter
{

static const bool kQuietDefault = false;

/**
 *  @brief
 *    This is the class default constructor.
 *
 *    The default constructor instantiates a quiet filter instance
 *    with the initial state at the default.
 *
 */
Quiet::Quiet(void) :
    Base(),
    mQuiet(kQuietDefault)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates a quiet filter instance with the
 *    specified initial quiet state.
 *
 *  @param[in]  inQuiet  The initial quiet state. When asserted (true),
 *                       the filter will reject messages; when
 *                       the filter will pass logged messages.
 *
 */
Quiet::Quiet(bool inQuiet) :
    Base(),
    mQuiet(inQuiet)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Quiet::~Quiet(void)
{
    return;
}

/**
 *  @brief
 *    Return the current quiet state.
 *
 *  @returns
 *     The current quiet state.
 *
 */
bool
Quiet::GetQuiet(void) const
{
    return (mQuiet);
}

/**
 *  @brief
 *    Set the current quiet state.
 *
 *    The filter quiet state is that which, when true, messages will
 *    be rejected by the filter and, when false, messages will be
 *    passed by it.
 *
 *  @param[in]  inQuiet  The new quiet state to set. Logged messages
 *                       will be passed when true and rejected when
 *                       false.
 *
 */
void
Quiet::SetQuiet(bool inQuiet)
{
    mQuiet = inQuiet;
}

/**
 *  @brief
 *    Pass or reject a message based on the specified level (unused)
 *    and the current quiet state of the filter.
 *
 *    When the quiet state is asserted, messages are rejected; otherwise,
 *    they are passed.
 *
 *  @param[in]  inLevel  The level the current message is to be logged at.
 *
 *  @returns
 *    True if the log message should be passed; otherwise, false, if
 *    the message should be rejected based on the current quiet state of
 *    the filter.
 */
bool
Quiet::Allow(Log::Level inLevel)
{
    (void)inLevel;

    return (!mQuiet);
}

/**
 *  @brief
 *    Pass or reject a message based on the specified level, the
 *    message to be logged, and the current quiet state of the filter.
 *
 *    When the quiet state is asserted, messages are rejected; otherwise,
 *    they are passed.
 *
 *  @param[in]  inLevel    The level the current message is to be logged at.
 *  @param[in]  inMessage  The log message to be filtered.
 *
 *  @returns
 *    True if the log message should be passed; otherwise, false, if
 *    the message should be rejected based on the current quiet state of
 *    the filter.
 */
bool
Quiet::Allow(Log::Level inLevel, const char * inMessage)
{
    (void)inMessage;

    return (Allow(inLevel));
}

}; // namespace Filter

}; // namespace Log

}; // namespace Nuovations
