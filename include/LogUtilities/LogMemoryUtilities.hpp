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
 *      This file defines Nuovations Log Utilities functions that may
 *      be used for logging the contents of arbitrary memory
 *      locations.
 */

#ifndef LOGUTILITIES_LOGMEMORYUTILITIES_HPP
#define LOGUTILITIES_LOGMEMORYUTILITIES_HPP

#include <stddef.h>

#include "LogLogger.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Utilities
        {

            namespace Memory
            {

                extern void Write(const void * inAddress,
                                  size_t       inUnits);
                extern void Write(Log::Level   inLevel,
                                  const void * inAddress,
                                  size_t       inUnits);
                extern void Write(Log::Indent  inIndent,
                                  Log::Level   inLevel,
                                  const void * inAddress,
                                  size_t       inUnits);

                extern void Write(const void * inAddress,
                                  size_t       inUnits,
                                  unsigned int inWidth);
                extern void Write(Log::Level   inLevel,
                                  const void * inAddress,
                                  size_t       inUnits,
                                  unsigned int inWidth);
                extern void Write(Log::Indent  inIndent,
                                  Log::Level   inLevel,
                                  const void * inAddress,
                                  size_t       inUnits,
                                  unsigned int inWidth);

                extern void Write(Logger &     inLogger,
                                  const void * inAddress,
                                  size_t       inUnits);
                extern void Write(Logger &     inLogger,
                                  Log::Level   inLevel,
                                  const void * inAddress,
                                  size_t       inUnits);
                extern void Write(Logger &     inLogger,
                                  Log::Indent  inIndent,
                                  Log::Level   inLevel,
                                  const void * inAddress,
                                  size_t       inUnits);

                extern void Write(Logger &     inLogger,
                                  const void * inAddress,
                                  size_t       inUnits,
                                  unsigned int inWidth);
                extern void Write(Logger &     inLogger,
                                  Log::Level   inLevel,
                                  const void * inAddress,
                                  size_t       inUnits,
                                  unsigned int inWidth);
                extern void Write(Logger &     inLogger,
                                  Log::Indent  inIndent,
                                  Log::Level   inLevel,
                                  const void * inAddress,
                                  size_t       inUnits,
                                  unsigned int inWidth);

            }; // namespace Memory

        }; // namespace Utilities

    }; // namespace Log

}; // namespace Nuovations

/**
 *  @def LogMemoryDebug(inAddress, inUnits, inWidth)
 *
 *  @brief
 *    Conditionally, based on the preprocessor DEBUG and NDEBUG names,
 *    write a log message using the global Debug logger instance, with
 *    no indent and using the default level, containing the memory at
 *    the specified address formatted at the specified width and
 *    number of memory units of that width.
 *
 *  @param[in]  inAddress  The memory address to log.
 *  @param[in]  inUnits    The number of memory units to log.
 *  @param[in]  inWidth    The width, in bytes, to format the memory
 *                         units as: may be one of 1, 2, 4, or 8,
 *                         corresponding to sizeof (uint8_t), sizeof
 *                         (uint16_t), sizeof (uint32_t), or sizeof
 *                         (uint64_t), respectively.
 *
 *  @ingroup memory-utilities
 *
 */
#if (defined(DEBUG) && DEBUG) && !defined(NDEBUG)
#define LogMemoryDebug(inAddress, inUnits, inWidth)                            \
    Nuovations::Log::Utilities::Memory::Write(inAddress, inUnits, inWidth)
#else
#define LogMemoryDebug(inAddress, inUnits, inWidth)
#endif

#endif // LOGUTILITIES_LOGMEMORYUTILITIES_HPP
