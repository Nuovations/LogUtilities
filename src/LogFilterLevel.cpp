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
 *      a dynamically-configurable level setting.
 */

#include <LogUtilities/LogFilterLevel.hpp>

namespace Nuovations
{

namespace Log
{

namespace Filter
{

static const Log::Level kLevelDefault = 0;

/**
 *  @brief
 *    This is the class default constructor.
 *
 *    The default constructor instantiates a level filter instance
 *    with the initial level at the default level.
 *
 */
Level::Level(void) :
    Base(),
    mLevel(kLevelDefault)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates a level filter instance with the
 *    specified initial level.
 *
 *  @param[in]  inLevel  The initial filter level at which or lower
 *                       the filter will pass logged messages.
 *
 */
Level::Level(Log::Level inLevel) :
    Base(),
    mLevel(inLevel)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Level::~Level(void)
{
    return;
}

/**
 *  @brief
 *    Return the current filter level.
 *
 *  @returns
 *     The current filter level.
 *
 */
Log::Level
Level::GetLevel(void) const
{
    return (mLevel);
}

/**
 *  @brief
 *    Set the current filter level.
 *
 *    The filter level is the level at which or lower, the filter will
 *    pass rather than reject messages.
 *
 *  @param[in]  inLevel  The new filter level to set. Logged messages at
 *                       this level or lower will be passed.
 *
 */
void
Level::SetLevel(Log::Level inLevel)
{
    mLevel = inLevel;
}

/**
 *  @brief
 *    Pass or reject a message based on the specified level and the
 *    current level of the filter.
 *
 *    Messages less than or equal to the current filter level are passed;
 *    those greater than are rejected.
 *
 *  @param[in]  inLevel  The level the current message is to be logged at.
 *
 *  @returns
 *    True if the log message should be passed; otherwise, false, if
 *    the message should be rejected based on the current level of the
 *    filter.
 */
bool
Level::Allow(Log::Level inLevel)
{
    return (inLevel <= mLevel);
}

/**
 *  @brief
 *    Pass or reject a message based on the specified level, the
 *    message to be logged, and the current level of the filter.
 *
 *    Messages less than or equal to the current filter level are passed;
 *    those greater than are rejected.
 *
 *  @param[in]  inLevel    The level the current message is to be logged at.
 *  @param[in]  inMessage  The log message to be filtered.
 *
 *  @returns
 *    True if the log message should be passed; otherwise, false, if
 *    the message should be rejected based on the current level of the
 *    filter.
 */
bool
Level::Allow(Log::Level inLevel, const char * inMessage)
{
    (void)inMessage;

    return (Allow(inLevel));
}

}; // namespace Filter

}; // namespace Log

}; // namespace Nuovations
