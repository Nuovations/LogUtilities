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
 *      This file defines preprocessor macros for more succinctly
 *      working with Nuovations Log Utilities global logger instances.
 */

#ifndef LOGUTILITIES_LOGMACROS_HPP
#define LOGUTILITIES_LOGMACROS_HPP

#include "LogGlobals.hpp"

/**
 *  @def LogDebug(inIndent, inLevel, inFormat, ...)
 *
 *  @brief
 *    Conditionally write, based on the preprocessor DEBUG and NDEBUG
 *    names, a log message at the specified indent and level using the
 *    global Debug logger instance.
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
 *  @sa Debug
 *
 */
#if (defined(DEBUG) && DEBUG) && !defined(NDEBUG)
# define LogDebug(inIndent, inLevel, inFormat, ...)                            \
    Nuovations::Log::Debug().Write(inIndent, inLevel, inFormat, ##__VA_ARGS__)
#else
# define LogDebug(inIndent, inLevel, inFormat, ...)
#endif

/**
 *  @def LogInfo(inIndent, inLevel, inFormat, ...)
 *
 *  @brief
 *    Write a log message at the specified indent and level using the
 *    global Info logger instance.
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
 *  @sa Info
 *
 */
#define LogInfo(inIndent, inLevel, inFormat, ...)                              \
    Nuovations::Log::Info().Write(inIndent, inLevel, inFormat, ##__VA_ARGS__)

/**
 *  @def LogError(inIndent, inLevel, inFormat, ...)
 *
 *  @brief
 *    Write a log message at the specified indent and level using the
 *    global Error logger instance.
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
 *  @sa Error
 *
 */
#define LogError(inIndent, inLevel, inFormat, ...)                             \
    Nuovations::Log::Error().Write(inIndent, inLevel, inFormat, ##__VA_ARGS__)

#endif /* LOGUTILITIES_LOGMACROS_HPP */
