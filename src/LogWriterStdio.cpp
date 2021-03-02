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
 *      writer implementation for the C89-conformant C Standard
 *      Library input/output library functions (that is, stdio(3)).
 */

#include <cstdio>

using namespace std;

#include <LogUtilities/LogWriterStdio.hpp>

namespace Nuovations
{

namespace Log
{

namespace Writer
{

/**
 *  @brief
 *    This is the class default constructor.
 *
 *    This constructor instantiates the writer with an invalid initial
 *    state for which @a SetStream must be called before use.
 *
 *  @sa SetStream
 *
 */
Stdio::Stdio(void) :
    Base(),
    mStream(NULL)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates the writer associated with the
 *    specified stream.
 *
 *  @param[in]  inStream  An file stream suitable for appending
 *                        which the writer will write to.
 *
 */
Stdio::Stdio(std::FILE *inStream) :
    Base(),
    mStream(inStream)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Stdio::~Stdio(void)
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
Stdio::Write(Level inLevel, const char * inMessage)
{
    (void)inLevel;

    fputs(inMessage, mStream);
}

/**
 *  @brief
 *    Write a log message at the default level.
 *
 *  @param[in]  inMessage  The log message to write.
 *
 */
void
Stdio::Write(const char * inMessage)
{
    static const Log::Level kLevel = 0;

    Write(kLevel, inMessage);
}

/**
 *  @brief
 *    This sets the stream for the writer.
 *
 *  @note
 *    The specified stream instance must be in scope for the duration
 *    of the writer instance scope. Otherwise, undefined behavior will
 *    occur when the writer instance is used.
 *
 *  @note
 *    This interface is not thread-safe.
 *
 *  @param[in]  inStream  A reference to the stream to set.
 *
 */
void
Stdio::SetStream(FILE * inStream)
{
    mStream = inStream;
}

}; // namespace Writer

}; // namespace Log

}; // namespace Nuovations
