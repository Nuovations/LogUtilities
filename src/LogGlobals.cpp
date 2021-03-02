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
 *      This file implements Nuovations Log Utilities global logger
 *      instances and utility interfaces for working with those (or
 *      other) instances.
 */

#include <typeinfo>

using namespace std;

#include <LogUtilities/LogFilterAlways.hpp>
#include <LogUtilities/LogFilterChain.hpp>
#include <LogUtilities/LogFilterLevel.hpp>
#include <LogUtilities/LogFilterQuiet.hpp>
#include <LogUtilities/LogFormatterPlain.hpp>
#include <LogUtilities/LogIndenterTab.hpp>
#include <LogUtilities/LogWriterChain.hpp>
#include <LogUtilities/LogWriterStderr.hpp>
#include <LogUtilities/LogWriterStdout.hpp>
#include <LogUtilities/LogWriterSyslog.hpp>

#include <LogUtilities/LogGlobals.hpp>

namespace Nuovations
{

namespace Log
{

/**
 *  @brief
 *    This routine returns the global shared logger instance for debug
 *    messages.
 *
 *    @note Because most systems filter anything below LOG_NOTICE for
 *    syslog, this instance uses LOG_NOTICE rather than LOG_DEBUG for
 *    the syslog writer.
 *
 *  @returns
 *    A reference to the global shared debug logger instance.
 *
 */
Logger &
Debug(void)
{
    static Writer::Stdout   stdoutWriter;
    static Writer::Syslog   syslogWriter(LOG_NOTICE);
    static Filter::Quiet    quietFilter;
    static Filter::Level    levelFilter;
    static Indenter::Tab    tabIndenter(Indenter::String::Flags::kEvery);
    static Formatter::Plain plainFormatter;
    static Writer::Chain    chainWriter;
    static Filter::Chain    chainFilter;
    static bool             isInitialized = false;

    if (!isInitialized) {
        chainFilter.Push(quietFilter);
        chainFilter.Push(levelFilter);
        chainWriter.Push(stdoutWriter);
        chainWriter.Push(syslogWriter);
        isInitialized = true;
    }

    static Logger debugLogger(chainFilter,
                              tabIndenter,
                              plainFormatter,
                              chainWriter);

    return (debugLogger);
}

/**
 *  @brief
 *    This routine returns the global shared logger instance for
 *    informational messages.
 *
 *    @note Because most systems filter anything below LOG_NOTICE for
 *    syslog, this instance uses LOG_NOTICE rather than LOG_INFO for
 *    the syslog writer.
 *
 *    @note While the initialization of this object is not
 *    thread-safe; the post-initialization use of the object is
 *    thread-safe.
 *
 *  @returns
 *    A reference to the global shared informational logger instance.
 *
 */
Logger &
Info(void)
{
    static Writer::Stdout   stdoutWriter;
    static Writer::Syslog   syslogWriter(LOG_NOTICE);
    static Filter::Quiet    quietFilter;
    static Filter::Level    levelFilter;
    static Indenter::Tab    tabIndenter(Indenter::String::Flags::kEvery);
    static Formatter::Plain plainFormatter;
    static Writer::Chain    chainWriter;
    static Filter::Chain    chainFilter;
    static bool             isInitialized = false;

    if (!isInitialized) {
        chainFilter.Push(quietFilter);
        chainFilter.Push(levelFilter);
        chainWriter.Push(stdoutWriter);
        chainWriter.Push(syslogWriter);
        isInitialized = true;
    }

    static Logger infoLogger(chainFilter,
                             tabIndenter,
                             plainFormatter,
                             chainWriter);

    return (infoLogger);
}

/**
 *  @brief
 *    This routine returns the global shared logger instance for error
 *    messages.
 *
 *    @note While the initialization of this object is not
 *    thread-safe; the post-initialization use of the object is
 *    thread-safe.
 *
 *  @returns
 *    A reference to the global shared error logger instance.
 *
 */
Logger &
Error(void)
{
    static Writer::Stderr   stderrWriter;
    static Writer::Syslog   syslogWriter(LOG_ERR);
    static Filter::Always   noFilter;
    static Indenter::Tab    tabIndenter(Indenter::String::Flags::kEvery);
    static Formatter::Plain plainFormatter;
    static Writer::Chain    chainWriter;
    static bool             isInitialized = false;

    if (!isInitialized) {
        chainWriter.Push(stderrWriter);
        chainWriter.Push(syslogWriter);
        isInitialized = true;
    }

    static Logger errorLogger(noFilter,
                              tabIndenter,
                              plainFormatter,
                              chainWriter);

    return (errorLogger);
}

/**
 *  @brief
 *    This routine atttempts to set the provided filter chain to the
 *    specified level and quiet settings.
 *
 *  @param[in,out]  inChain  A reference to the filter chain for which
 *                           the level and quiet filter parameters are
 *                           to be set. On success, the chain is
 *                           modified with the values from @a inLevel
 *                           and @a inQuiet.
 *  @param[in]      inLevel  The level to set the level filter in the
 *                           chain to.
 *  @param[in]      inQuiet  The quiet status to set the quiet filter
 *                           in the chain to.
 *
 *  @returns
 *    True if the filter parameters were successfully set; otherwise,
 *    false.
 *
 */
static bool
SetFilter(Filter::Chain & inChain, Log::Level inLevel, bool inQuiet)
{
    bool         setQuiet = false;
    bool         setLevel = false;
    const size_t theLinks = inChain.Size();

    for (size_t theLink = 0; theLink < theLinks; theLink++) {
        Filter::Base * theFilter = inChain.Link<Filter::Base>(theLink);

        if (theFilter != NULL) {
            if (typeid(*theFilter) == typeid(Filter::Quiet)) {
                static_cast<Filter::Quiet *>(theFilter)->SetQuiet(inQuiet);
                setQuiet = true;
            }

            if (typeid(*theFilter) == typeid(Filter::Level)) {
                static_cast<Filter::Level *>(theFilter)->SetLevel(inLevel);
                setLevel = true;
            }
        }
    }

    return (setQuiet && setLevel);
}

/**
 *  @brief
 *    This routine atttempts to get the level and quiet settings for
 *    the provided filter chain.
 *
 *  @param[in]  inChain   An immutable reference to the filter chain to
 *                        get the level and quiet filter parameters for.
 *  @param[out] outLevel  The level the level filter is currently set to.
 *  @param[out] outQuiet  The quiet status the quiet filter is currently
 *                        set to.
 *
 *  @returns
 *    True if the filter parameters were successfully gotten;
 *    otherwise, false.
 *
 */
static bool
GetFilter(const Filter::Chain & inChain, Log::Level & outLevel, bool & outQuiet)
{
    bool         gotQuiet = false;
    bool         gotLevel = false;
    const size_t theLinks = inChain.Size();

    for (size_t theLink = 0; theLink < theLinks; theLink++) {
        const Filter::Base * theFilter = inChain.Link<const Filter::Base>(theLink);

        if (theFilter != NULL) {
            if (typeid(*theFilter) == typeid(Filter::Quiet)) {
                outQuiet = static_cast<const Filter::Quiet *>(theFilter)->GetQuiet();
                gotQuiet = true;
            }

            if (typeid(*theFilter) == typeid(Filter::Level)) {
                outLevel = static_cast<const Filter::Level *>(theFilter)->GetLevel();
                gotLevel = true;
            }
        }
    }

    return (gotQuiet && gotLevel);
}

/**
 *  @brief
 *    This routine atttempts to get the level and quiet settings for
 *    the filter chain associated with the specified logger.
 *
 *  @param[in]   inLogger  A reference to the logger from which to get
 *                         the filter chain level and quiet filter
 *                         parameters.
 *  @param[out]  outLevel  The level the level filter in the chain
 *                         is currently set to.
 *  @param[out]  outQuiet  The quiet state the quiet filter in the
 *                         chain is currently set to.
 *
 *  @returns
 *    True if the filter parameters were successfully obtained;
 *    otherwise, false.
 *
 */
bool
GetFilter(const Logger & inLogger, Log::Level & outLevel, bool & outQuiet)
{
    const Log::Filter::Base & theFilter = inLogger.GetFilter();

    if (typeid(theFilter) != typeid(Filter::Chain)) {
        return (false);
    }

    return (GetFilter(static_cast<const Filter::Chain &>(theFilter),
                      outLevel,
                      outQuiet));
}

/**
 *  @brief
 *    This routine atttempts to set the filter chain associated with
 *    the specified logger to the specified level and quiet settings.
 *
 *  @param[in,out]  inLogger  A reference to the logger for which the
 *                            filter chain level and quiet filter
 *                            parameters are to be set. On success,
 *                            the logger filter chain is modified with
 *                            the values from @a inLevel and @a
 *                            inQuiet.
 *  @param[in]      inLevel   The level to set the level filter in the
 *                            chain to.
 *  @param[in]      inQuiet   The quiet status to set the quiet filter
 *                            in the chain to.
 *
 *  @returns
 *    True if the filter parameters were successfully set; otherwise,
 *    false.
 *
 */
bool
SetFilter(Logger & inLogger, Log::Level inLevel, bool inQuiet)
{
    Log::Filter::Base & theFilter = inLogger.GetFilter();

    if (typeid(theFilter) != typeid(Filter::Chain)) {
        return (false);
    }

    return (SetFilter(static_cast<Filter::Chain &>(theFilter),
                      inLevel,
                      inQuiet));
}

}; // namespace Log

}; // namespace Nuovations
