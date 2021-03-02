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
 *      This file implements a Nuovations Log Utilities logger object.
 */

#include <cstdarg>
#include <string>

using namespace std;

#include <LogUtilities/LogLogger.hpp>

namespace Nuovations
{

namespace Log
{

/**
 *  @brief
 *    This is the class constructor, building a logger instance from
 *    the specified filter, indenter, formatter, and writer.
 *
 *  @note
 *    All specified filter, indenter, formatter, and writer instances
 *    must be in scope for the duration of the logger instance
 *    scope. Otherwise, undefined behavior will occur when the logger
 *    instance is used.
 *
 *  @param[in]  inFilter     A reference to the filter to the instantiate
 *                           the logger with.
 *  @param[in]  inIndenter   A reference to the indenter to the instantiate
 *                           the logger with.
 *  @param[in]  inFormatter  TBD
 *  @param[in]  inWriter     TBD
 *
 */
Logger::Logger(Filter::Base &    inFilter,
               Indenter::Base &  inIndenter,
               Formatter::Base & inFormatter,
               Writer::Base &    inWriter) :
    mFilter(&inFilter),
    mIndenter(&inIndenter),
    mFormatter(&inFormatter),
    mWriter(&inWriter)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Logger::~Logger(void)
{
    return;
}

/**
 *  @brief
 *    Return a reference to the indenter associated with the logger.
 *
 *  @returns
 *    A reference to the indenter associated with the logger.
 *
 */
Indenter::Base &
Logger::GetIndenter(void)
{
    return (*mIndenter);
}

/**
 *  @brief
 *    Return an immutable reference to the indenter associated with the
 *    logger.
 *
 *  @returns
 *    An immutable reference to the indenter associated with the logger.
 *
 */
const Indenter::Base &
Logger::GetIndenter(void) const
{
    return (*mIndenter);
}

/**
 *  @brief
 *    This sets the indenter for the logger.
 *
 *  @note
 *    The specified indenter instance must be in scope for the
 *    duration of the logger instance scope. Otherwise, undefined
 *    behavior will occur when the logger instance is used.
 *
 *  @note
 *    This interface is not thread-safe.
 *
 *  @param[in]  inIndenter   A reference to the indenter to set.
 *
 */
void
Logger::SetIndenter(Indenter::Base & inIndenter)
{
    mIndenter = &inIndenter;
}

/**
 *  @brief
 *    Return an immutable reference to the formatter associated with the
 *    logger.
 *
 *  @returns
 *    An immutable reference to the formatter associated with the logger.
 *
 */
Formatter::Base &
Logger::GetFormatter(void)
{
    return (*mFormatter);
}

/**
 *  @brief
 *    Return an immutable reference to the formatter associated with the
 *    logger.
 *
 *  @returns
 *    An immutable reference to the formatter associated with the logger.
 *
 */
const Formatter::Base &
Logger::GetFormatter(void) const
{
    return (*mFormatter);
}

/**
 *  @brief
 *    This sets the formatter for the logger.
 *
 *  @note
 *    The specified formatter instance must be in scope for the
 *    duration of the logger instance scope. Otherwise, undefined
 *    behavior will occur when the logger instance is used.
 *
 *  @note
 *    This interface is not thread-safe.
 *
 *  @param[in]  inFormatter   A reference to the formatter to set.
 *
 */
void
Logger::SetFormatter(Formatter::Base & inFormatter)
{
    mFormatter = &inFormatter;
}

/**
 *  @brief
 *    Return a reference to the filter associated with the logger.
 *
 *  @returns
 *    A reference to the filter associated with the logger.
 *
 */
Filter::Base &
Logger::GetFilter(void)
{
    return (*mFilter);
}

/**
 *  @brief
 *    Return an immutable reference to the filter associated with the
 *    logger.
 *
 *  @returns
 *    An immutable reference to the filter associated with the logger.
 *
 */
const Filter::Base &
Logger::GetFilter(void) const
{
    return (*mFilter);
}

/**
 *  @brief
 *    This sets the filter for the logger.
 *
 *  @note
 *    The specified filter instance must be in scope for the
 *    duration of the logger instance scope. Otherwise, undefined
 *    behavior will occur when the logger instance is used.
 *
 *  @note
 *    This interface is not thread-safe.
 *
 *  @param[in]  inFilter   A reference to the filter to set.
 *
 */
void
Logger::SetFilter(Filter::Base & inFilter)
{
    mFilter = &inFilter;
}


/**
 *  @brief
 *    Return a reference to the writer associated with the logger.
 *
 *  @returns
 *    A reference to the writer associated with the logger.
 *
 */
Writer::Base &
Logger::GetWriter(void)
{
    return (*mWriter);
}

/**
 *  @brief
 *    Return an immutable reference to the writer associated with the
 *    logger.
 *
 *  @returns
 *    An immutable reference to the writer associated with the logger.
 *
 */
const Writer::Base &
Logger::GetWriter(void) const
{
    return (*mWriter);
}

/**
 *  @brief
 *    This sets the writer for the logger.
 *
 *  @note
 *    The specified writer instance must be in scope for the
 *    duration of the logger instance scope. Otherwise, undefined
 *    behavior will occur when the logger instance is used.
 *
 *  @note
 *    This interface is not thread-safe.
 *
 *  @param[in]  inWriter   A reference to the writer to set.
 *
 */
void
Logger::SetWriter(Writer::Base & inWriter)
{
    mWriter = &inWriter;
}

/**
 *  @brief
 *    Write a log message at the specified indent and level.
 *
 *  @param[in]  inIndent  The level of indendation desired for the
 *                        provided log message.
 *  @param[in]  inLevel   The level the current message is to be logged
 *                        at.
 *  @param[in]  inFormat  The log message, consisting of a printf-style
 *                        format string composed of zero or more
 *                        output conversion directives.
 *  @param[in]  ...       A variadic argument list, where each argument
 *                        corresponds with its peer output conversion
 *                        directive in @a inFormat.
 *
 */
void
Logger::Write(Log::Indent  inIndent,
              Log::Level   inLevel,
              const char * inFormat,
              ...)
{
    va_list theArguments;

    va_start(theArguments, inFormat);

    Write(inIndent, inLevel, inFormat, theArguments);

    va_end(theArguments);
}

/**
 *  @brief
 *    Write a log message at the specified indent and level.
 *
 *  @param[in]  inIndent     The level of indendation desired for
 *                           the provided log message.
 *  @param[in]  inLevel      The level the current message is to be
 *                           logged at.
 *  @param[in]  inFormat     The log message, consisting of a printf-
 *                           style format string composed of zero or
 *                           more output conversion directives.
 *  @param[in]  inArguments  A variable argument list, where each
 *                           argument corresponds with its peer output
 *                           conversion directive in @a inFormat.
 *
 */
void
Logger::Write(Log::Indent  inIndent,
              Log::Level   inLevel,
              const char * inFormat,
              std::va_list inArguments)
{
    string theMessage;

    // Perform any up front, level-only filtering to avoid spending
    // any cycles formatting messages that are going to be tossed
    // anyway.

    if (!mFilter->Allow(inLevel)) {
        return;
    }

    // Format the message.

    theMessage = mFormatter->Format(inLevel, inFormat, inArguments);

    // Indent the message.

    theMessage = mIndenter->Indent(inIndent, theMessage);

    // Finally, write the message, if allowed based on the level and
    // message contents.

    if (mFilter->Allow(inLevel, theMessage.c_str())) {
        mWriter->Write(inLevel, theMessage.c_str());
    }
}

/**
 *  @brief
 *    Write a log message with no indent and at the provided level.
 *
 *  @param[in]  inLevel   The level the current message is to be
 *                        logged at.
 *  @param[in]  inFormat  The log message, consisting of a printf-
 *                        style format string composed of zero or
 *                        more output conversion directives.
 *  @param[in]  ...       A variadic argument list, where each
 *                        argument corresponds with its peer output
 *                        conversion directive in @a inFormat.
 *
 */
void
Logger::Write(Log::Level inLevel, const char * inFormat, ...)
{
    va_list theArguments;

    va_start(theArguments, inFormat);

    Write(inLevel, inFormat, theArguments);

    va_end(theArguments);
}

/**
 *  @brief
 *    Write a log message with no indent and at the provided level.
 *
 *  @param[in]  inLevel      The level the current message is to be
 *                           logged at.
 *  @param[in]  inFormat     The log message, consisting of a printf-
 *                           style format string composed of zero or
 *                           more output conversion directives.
 *  @param[in]  inArguments  A variable argument list, where each
 *                           argument corresponds with its peer output
 *                           conversion directive in @a inFormat.
 *
 */
void
Logger::Write(Log::Level   inLevel,
              const char * inFormat,
              std::va_list inArguments)
{
    static const Log::Indent kIndent = 0;

    Write(kIndent, inLevel, inFormat, inArguments);
}

/**
 *  @brief
 *    Write a log message with no indent and at the default level.
 *
 *  @param[in]  inFormat  The log message, consisting of a printf-
 *                        style format string composed of zero or
 *                        more output conversion directives.
 *  @param[in]  ...       A variadic argument list, where each
 *                        argument corresponds with its peer output
 *                        conversion directive in @a inFormat.
 *
 */
void
Logger::Write(const char * inFormat, ...)
{
    va_list theArguments;

    va_start(theArguments, inFormat);

    Write(inFormat, theArguments);

    va_end(theArguments);
}

/**
 *  @brief
 *    Write a log message with no indent and at the default level.
 *
 *  @param[in]  inFormat     The log message, consisting of a printf-
 *                           style format string composed of zero or
 *                           more output conversion directives.
 *  @param[in]  inArguments  A variable argument list, where each
 *                           argument corresponds with its peer output
 *                           conversion directive in @a inFormat.
 *
 */
void
Logger::Write(const char * inFormat, std::va_list inArguments)
{
    static const Log::Indent kIndent = 0;
    static const Log::Level  kLevel  = 0;

    Write(kIndent, kLevel, inFormat, inArguments);
}

}; // namespace Log

}; // namespace Nuovations
