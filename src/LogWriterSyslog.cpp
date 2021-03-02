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
 *      implementation for the Single UNIX Specification v2 (SUSv2)-,
 *      POSIX.1-2001-, and POSIX.1-2008-conformant syslog(3)
 *      interfaces.
 */

#include <syslog.h>

#include <LogUtilities/LogWriterSyslog.hpp>

namespace Nuovations
{

namespace Log
{

namespace Writer
{

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates the writer associated with the
 *    syslog using the specified priority for all written messages.
 *
 *  @param[in]  inPriority  The syslog priority at which the writer
 *                          will write messages.
 *
 */
Syslog::Syslog(int inPriority) :
    Base(),
    mPriority(inPriority)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Syslog::~Syslog(void)
{
    return;
}

/**
 *  @brief
 *    Write a log message at the specified level.
 *
 *  @param[in]  inLevel    The level the current message is to be logged
 *                         at.
 *  @param[in]  inMessage  The log message to write.
 *
 */
void
Syslog::Write(Level inLevel, const char * inMessage)
{
    (void)inLevel;

    syslog(mPriority, "%s", inMessage);
}

/**
 *  @brief
 *    Write a log message at the default level.
 *
 *  @param[in]  inMessage  The log message to write.
 *
 */
void
Syslog::Write(const char * inMessage)
{
    static const Log::Level kLevel = 0;

    Write(kLevel, inMessage);
}

/**
 *  @brief
 *    Return the current writer syslog priority.
 *
 *  @returns
 *     The current writer syslog priority.
 *
 */
int
Syslog::GetPriority(void)
{
    return (mPriority);
}

/**
 *  @brief
 *    Set the current writer syslog priority.
 *
 *  @param[in]  inPriority  The syslog priority at which the writer
 *                          will write messages.
 *
 */
void
Syslog::SetPriority(int inPriority)
{
    mPriority = inPriority;
}

}; // namespace Writer

}; // namespace Log

}; // namespace Nuovations
