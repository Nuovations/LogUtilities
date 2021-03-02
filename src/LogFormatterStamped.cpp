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
 *      formatter object that prepends each logged message with a
 *      formatted information stamp.
 */

#include <LogUtilities/LogFormatterStamped.hpp>

#include <cstdio>
#include <ctime>
#include <string>

using namespace std;

#include <pthread.h>
#include <unistd.h>

// Preprocessor Definitions

#if __linux__
#define kPThreadSelfFormat "%lu"
#elif __APPLE__
#define kPThreadSelfFormat "%p"
#else
#error "Unknown pthread_self format specifier for this platform."
#endif // __linux__


namespace Nuovations
{

namespace Log
{

namespace Formatter
{

Stamped::Stamped(void)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Stamped::~Stamped(void)
{
    return;
}

/**
 *  @brief
 *    Prepends a unique information stamp to the log message and
 *    performs output format conversion on a log message at the
 *    indicated level based on the specified printf-style format
 *    string and the variadic argument list.
 *
 *  The formatted information stamp is of the form:
 *
 *      <year>-<month>-<day> <hour>:<minute>:<second> [\<PID\>:<thread>] (<level>) <message>
 *
 *  where @a PID is the process identification number, @a thread is the
 *  POSIX thread identifier/object pointer returned by pthread_self,
 *  and @a level is the level the logged message was specified at.
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
Stamped::Format(Level inLevel, const char * inFormat, ...)
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
 *    Prepends a unique information stamp to the log message and
 *    performs output format conversion on a log message at the
 *    indicated level based on the specified printf-style format
 *    string and the variable argument list.
 *
 *  The formatted information stamp is of the form:
 *
 *      <year>-<month>-<day> <hour>:<minute>:<second> [\<PID\>:<thread>] (<level>) <message>
 *
 *  where @a PID is the process identification number, @a thread is the
 *  POSIX thread identifier/object pointer returned by pthread_self,
 *  and @a level is the level the logged message was specified at.
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
Stamped::Format(Level inLevel, const char * inFormat, std::va_list inList)
{
    string theString;
    int    status;
    char * p = NULL;

    if (inFormat != NULL) {
        time_t    theTime;
        struct tm theDate;

        theTime = time(NULL);
        localtime_r(&theTime, &theDate);

        status = asprintf(&p,
                          "%04d-%02d-%02d %02d:%02d:%02d [%d:" kPThreadSelfFormat "] (%u) ",
                          theDate.tm_year + 1900,
                          theDate.tm_mon,
                          theDate.tm_mday,
                          theDate.tm_hour,
                          theDate.tm_min,
                          theDate.tm_sec,
                          getpid(),
                          pthread_self(),
                          inLevel);

        if ((status != -1) && (p != NULL)) {
            theString = p;
            free(p);

            theString += Plain::Format(inLevel, inFormat, inList);
        }
    }

    return (theString);
}

/**
 *  @brief
 *    Prepends a unique information stamp to the log message and
 *    performs output format conversion on a log message at the
 *    indicated level based on the specified printf-style format
 *    string and the variadic argument list.
 *
 *  The formatted information stamp is of the form:
 *
 *      <year>-<month>-<day> <hour>:<minute>:<second> [\<PID\>:<thread>] (<level>) <message>
 *
 *  where @a PID is the process identification number, @a thread is the
 *  POSIX thread identifier/object pointer returned by pthread_self,
 *  and @a level is the level the logged message was specified at.
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
Stamped::Format(const char * inFormat, ...)
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
 *    Prepends a unique information stamp to the log message and
 *    performs output format conversion on a log message at the
 *    indicated level based on the specified printf-style format
 *    string and the variable argument list.
 *
 *  The formatted information stamp is of the form:
 *
 *      <year>-<month>-<day> <hour>:<minute>:<second> [\<PID\>:<thread>] (<level>) <message>
 *
 *  where @a PID is the process identification number, @a thread is the
 *  POSIX thread identifier/object pointer returned by pthread_self,
 *  and @a level is the level the logged message was specified at.
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
Stamped::Format(const char * inFormat, std::va_list inList)
{
    const Log::Level kLevel = 0;

    return (Format(kLevel, inFormat, inList));
}

}; // namespace Formatter

}; // namespace Log

}; // namespace Nuovations
