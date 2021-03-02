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
 *      This file implements a Nuovations Log Utilities base, derivable
 *      filter implementation that passes logged messages based on the
 *      instantiated Boolean value.
 */

#include <LogUtilities/LogFilterBoolean.hpp>

namespace Nuovations
{

namespace Log
{

namespace Filter
{

/**
 *  @brief
 *    This is the class constructor, building an invariant Boolean
 *    filter instance.
 *
 *  This filter instance can be constructed that either invariantly
 *  passes (constructed with @a inAllow as true) or rejects
 *  (constructed with @a inAllow as false) logged messages.
 *
 *  @param[in]  inAllow  A Boolean indicating whether the filter, once
 *                       constructed, invariantly passes (true) or
 *                       rejects (false) logged messages.
 *
 */
Boolean::Boolean(bool inAllow) :
    Base(),
    mAllow(inAllow)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Boolean::~Boolean(void)
{
    return;
}

/**
 *  @brief
 *    Pass or reject a message based on the specified level (unused)
 *    and the instantiated Boolean state of the filter.
 *
 *  @param[in]  inLevel  The level the current message is to be logged at.
 *
 *  @returns
 *    True if the log message should be passed; otherwise, false, if
 *    the message should be rejected based on the instantiated Boolean
 *    state of the filter.
 */
bool
Boolean::Allow(Level inLevel)
{
    (void)inLevel;

    return (mAllow);
}

/**
 *  @brief
 *    Pass or reject a message based on the specified level (unused),
 *    the message to be logged, and the instantiated Boolean state of
 *    the filter.
 *
 *  @param[in]  inLevel    The level the current message is to be logged at.
 *  @param[in]  inMessage  The log message to be filtered.
 *
 *  @returns
 *    True if the log message should be passed; otherwise, false, if
 *    the message should be rejected based on the instantiated Boolean
 *    state of the filter.
 */
bool
Boolean::Allow(Level inLevel, const char * inMessage)
{
    (void)inMessage;

    return (Allow(inLevel));
}

}; // namespace Filter

}; // namespace Log

}; // namespace Nuovations
