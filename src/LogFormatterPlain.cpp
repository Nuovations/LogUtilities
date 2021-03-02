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
 *      formatter object that simply performs format output
 *      conversion on the specified message using the supplied
 *      arguments.
 */

#include <LogUtilities/LogFormatterPlain.hpp>

#include <cstdio>
#include <string>


using namespace std;


namespace Nuovations
{

namespace Log
{

namespace Formatter
{

Plain::Plain(void)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Plain::~Plain(void)
{
    return;
}

/**
 *  @brief
 *    Performs output format conversion on a log message at the
 *    indicated level based on the specified printf-style format
 *    string and the variadic argument list.
 *
 *  @param[in]  inLevel   The level the current message is to be logged at.
 *  @param[in]  inFormat  The log message, consisting of a printf-style
 *                        format string composed of zero or more
 *                        output conversion directives.
 *  @param[in]  ...       A variadic argument list, where each argument
 *                        corresponds with its peer output conversion
 *                        directive in @a inFormat.
 *
 *  @returns
 *     A string object containing the formatted output message.
 */
string
Plain::Format(Level inLevel, const char * inFormat, ...)
{
    va_list theList;
    string  theString;

    va_start(theList, inFormat);

    theString = Format(inLevel, inFormat, theList);

    va_end(theList);

    return (theString);
}

/**
 *  @brief
 *    Performs output format conversion on a log message at the
 *    indicated level based on the specified printf-style format
 *    string and the variable argument list.
 *
 *  @param[in]  inLevel   The level the current message is to be logged at.
 *  @param[in]  inFormat  The log message, consisting of a printf-style
 *                        format string composed of zero or more
 *                        output conversion directives.
 *  @param[in]  inList    A variable argument list, where each argument
 *                        corresponds with its peer output conversion
 *                        directive in @a inFormat.
 *
 *  @returns
 *     A string object containing the formatted output message.
 */
string
Plain::Format(Level inLevel, const char * inFormat, std::va_list inList)
{
    string theString;
    int    status;
    char * p = NULL;

    (void)inLevel;

    if (inFormat != NULL) {
        status = vasprintf(&p, inFormat, inList);

        if ((status != -1) && (p != NULL)) {
            theString = p;
            free(p);
        }
    }

    return (theString);
}

/**
 *  @brief
 *    Performs output format conversion on a log message at the
 *    default level based on the specified printf-style format
 *    string and the variadic argument list.
 *
 *  @param[in]  inFormat  The log message, consisting of a printf-style
 *                        format string composed of zero or more
 *                        output conversion directives.
 *  @param[in]  ...       A variadic argument list, where each argument
 *                        corresponds with its peer output conversion
 *                        directive in @a inFormat.
 *
 *  @returns
 *     A string object containing the formatted output message.
 */
string
Plain::Format(const char * inFormat, ...)
{
    va_list theList;
    string  theString;

    va_start(theList, inFormat);

    theString = Format(inFormat, theList);

    va_end(theList);

    return (theString);
}

/**
 *  @brief
 *    Performs output format conversion on a log message at the
 *    default level based on the specified printf-style format
 *    string and the variable argument list.
 *
 *  @param[in]  inFormat  The log message, consisting of a printf-style
 *                        format string composed of zero or more
 *                        output conversion directives.
 *  @param[in]  inList    A variable argument list, where each argument
 *                        corresponds with its peer output conversion
 *                        directive in @a inFormat.
 *
 *  @returns
 *     A string object containing the formatted output message.
 */
string
Plain::Format(const char * inFormat, std::va_list inList)
{
    const Log::Level kLevel = 0;

    return (Format(kLevel, inFormat, inList));
}

}; // namespace Formatter

}; // namespace Log

}; // namespace Nuovations
