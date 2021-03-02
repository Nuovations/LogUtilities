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
 *      This file defines intrinsic types used by nearly all
 *      Nuovations Logging Utilities objects and interfaces.
 */

#ifndef LOGUTILITIES_LOGTYPES_HPP
#define LOGUTILITIES_LOGTYPES_HPP

/**
 *  @def _LOG_CHECK_FORMAT(inFormatPosition, inVarargPosition)
 *
 *  @brief
 *    Type check the printf-style format specifier against the
 *    variable argument list.
 *
 *  @param[in]  inFormatPosition  The position in the argument list
 *                                corresponding to the printf-style format
 *                                specifier argument.
 *  @param[in]  inVarargPosition  The position in the argument list
 *                                corresponding to the first variable argument
 *                                for the printf-style format argument.
 *
 */
#if defined(__GNUC__) && ((__GNUC__ > 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 7)))
#define _LOG_CHECK_FORMAT(inFormatPosition, inVarargPosition)  __attribute__((__format__(__printf__, inFormatPosition, inVarargPosition)))
#else
#define _LOG_CHECK_FORMAT(inFormatPosition, inVarargPosition)
#endif // defined(__GNUC__) && ((__GNUC__ > 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 7)))

namespace Nuovations
{
    namespace Log
    {
        /**
         *  The type used for specifying the increments of indentation
         *  applied to a logged message.
         */
        typedef unsigned int Indent;

        /**
         *  The type used for specifying the level at which a logged
         *  message will be written.
         */
        typedef unsigned int Level;

    }; // namespace Log

}; // namespace Nuovations

/**
 *  @def DeclareLogType(inType, inName)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, a named log utilities stack or member variable of
 *    the provided type.
 *
 *  @param[in]  inType   The type to declare.
 *  @param[in]  inName   The name of the type to declare. This is
 *                       the name of the type stack or member
 *                       variable.
 *
 *  @sa DeclareLogTypeWithValue
 *
 */

/**
 *  @def DeclareLogTypeWithValue(inType, inName, inValue)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, a named log utilities stack or member variable of
 *    the provided type with the specified initially-assigned value.
 *
 *  @param[in]  inType   The type to declare.
 *  @param[in]  inName   The name of the type to declare. This is
 *                       the name of the type stack or member
 *                       variable.
 *  @param[in]  inValue  The initially-assigned value for the named
 *                       type.

 *
 *  @sa DeclareLogType
 *
 */
#if defined(DEBUG) && !defined(NDEBUG)
# define DeclareLogType(inType, inName)                     \
    inType inName
# define DeclareLogTypeWithValue(inType, inName, inValue)   \
    inType inName = inValue;
#else
# define DeclareLogType(inType, inName)
# define DeclareLogTypeWithValue(inType, inName, inValue)
#endif

/**
 *  @def DeclareLogIndent(inName)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, a named log indent stack or member variable.
 *
 *  @param[in]  inName   The name of the indent to declare. This is
 *                       the name of the indent stack or member
 *                       variable.
 *
 *  @sa DeclareLogIndentWithValue
 *
 */
#define DeclareLogIndent(inName)                         \
    DeclareLogType(Nuovations::Log::Indent, inName)

/**
 *  @def DeclareLogIndentWithValue(inName, inValue)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, a named log indent stack or member variable with
 *    the specified initially-assigned value.
 *
 *  @param[in]  inName   The name of the indent to declare. This is
 *                       the name of the indent stack or member
 *                       variable.
 *  @param[in]  inValue  The initially-assigned value for the named
 *                       indent.
 *
 *
 *  @sa DeclareLogIndent
 *
 */
#define DeclareLogIndentWithValue(inName, inValue)       \
    DeclareLogTypeWithValue(Nuovations::Log::Indent, inName, inValue)

/**
 *  @def DeclareLogLevel(inName)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, a named log level stack or member variable.
 *
 *  @param[in]  inName   The name of the level to declare. This is
 *                       the name of the level stack or member
 *                       variable.
 *
 *  @sa DeclareLogLevelWithValue
 *
 */
#define DeclareLogLevel(inName)                          \
    DeclareLogType(Nuovations::Log::Level, inName)

/**
 *  @def DeclareLogLevelWithValue(inName, inValue)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, a named log level stack or member variable with
 *    the specified initially-assigned value.
 *
 *  @param[in]  inName   The name of the level to declare. This is
 *                       the name of the level stack or member
 *                       variable.
 *  @param[in]  inValue  The initially-assigned value for the named
 *                       level.

 *
 *  @sa DeclareLogLevel
 *
 */
#define DeclareLogLevelWithValue(inName, inValue)        \
    DeclareLogTypeWithValue(Nuovations::Log::Level, inName, inValue)

#endif /* LOGUTILITIES_LOGTYPES_HPP */
