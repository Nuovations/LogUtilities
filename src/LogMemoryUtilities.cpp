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
 *      This file implements Nuovations Log Utilities functions that may
 *      be used for logging the contents of arbitrary memory
 *      locations.
 */

#include <LogUtilities/LogMemoryUtilities.hpp>

#include <string>

using namespace std;

#include <ctype.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#include <LogUtilities/LogGlobals.hpp>

namespace Nuovations
{

namespace Log
{

namespace Utilities
{

namespace Memory
{

/**
 *  @brief
 *    Write a log message using the global Debug logger instance, with
 *    no indent and at the default level, containing the memory at the
 *    specified address formatted as 1 byte units with the specified
 *    number of memory units.
 *
 *  @param[in]  inAddress  The memory address to log.
 *  @param[in]  inUnits    The number of memory units to log.
 *
 *  @ingroup memory-utilities
 *
 */
void
Write(const void * inAddress, size_t inUnits)
{
    static const Log::Indent  kIndent = 0;
    static const Log::Level   kLevel  = 0;
    static const unsigned int kWidth  = sizeof(uint8_t);

    Write(Log::Debug(), kIndent, kLevel, inAddress, inUnits, kWidth);
}

/**
 *  @brief
 *    Write a log message using the global Debug logger instance, with
 *    no indent and at the provided level, containing the memory at
 *    the specified address formatted as 1 byte units with the
 *    specified number of memory units.
 *
 *  @param[in]  inLevel    The level the current message is to be logged
 *                         at.
 *  @param[in]  inAddress  The memory address to log.
 *  @param[in]  inUnits    The number of memory units to log.
 *
 *  @ingroup memory-utilities
 *
 */
void
Write(Log::Level inLevel, const void * inAddress, size_t inUnits)
{
    static const Log::Indent  kIndent = 0;
    static const unsigned int kWidth  = sizeof(uint8_t);

    Write(Log::Debug(), kIndent, inLevel, inAddress, inUnits, kWidth);
}

/**
 *  @brief
 *    Write a log message using the global Debug logger instance, with
 *    the provided indent and level, containing the memory at the
 *    specified address formatted as 1 byte units with the specified
 *    number of memory units.
 *
 *  @param[in]  inIndent   The level of indendation desired for the
 *                         provided log message.
 *  @param[in]  inLevel    The level the current message is to be logged
 *                         at.
 *  @param[in]  inAddress  The memory address to log.
 *  @param[in]  inUnits    The number of memory units to log.
 *
 *  @ingroup memory-utilities
 *
 */
void
Write(Log::Indent  inIndent,
      Log::Level   inLevel,
      const void * inAddress,
      size_t       inUnits)
{
    static const unsigned int kWidth = sizeof(uint8_t);

    Write(Log::Debug(), inIndent, inLevel, inAddress, inUnits, kWidth);
}

/**
 *  @brief
 *    Write a log message using the global Debug logger instance, with
 *    no indent and at the default level, containing the memory at the
 *    specified address formatted with the specified width and number
 *    of memory units of that width.
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
void
Write(const void * inAddress, size_t inUnits, unsigned int inWidth)
{
    static const Log::Indent kIndent = 0;
    static const Log::Level  kLevel  = 0;

    Write(Log::Debug(), kIndent, kLevel, inAddress, inUnits, inWidth);
}

/**
 *  @brief
 *    Write a log message using the global Debug logger instance, with
 *    no indent and at the provided level, containing the memory at the
 *    specified address formatted at the specified width and number of
 *    memory units of that width.
 *
 *  @param[in]  inLevel    The level the current message is to be logged
 *                         at.
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
void
Write(Log::Level   inLevel,
      const void * inAddress,
      size_t       inUnits,
      unsigned int inWidth)
{
    static const Log::Indent kIndent = 0;

    Write(Log::Debug(), kIndent, inLevel, inAddress, inUnits, inWidth);
}

/**
 *  @brief
 *    Write a log message using the global Debug logger instance, with
 *    no indent and at the default level, containing the memory at the
 *    specified address formatted at the specified width and number of
 *    memory units of that width.
 *
 *  @param[in]  inIndent   The level of indendation desired for the
 *                         provided log message.
 *  @param[in]  inLevel    The level the current message is to be logged
 *                         at.
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
void
Write(Log::Indent  inIndent,
      Log::Level   inLevel,
      const void * inAddress,
      size_t       inUnits,
      unsigned int inWidth)
{
    Write(Log::Debug(), inIndent, inLevel, inAddress, inUnits, inWidth);
}

/**
 *  @brief
 *    Write a log message using the indicated logger, with no indent
 *    and at the default level, containing the memory at the specified
 *    address formatted as 1 byte units with the specified number of
 *    memory units.
 *
 *  @param[in]  inLogger   A reference to the logger with which to write
 *                         the specified contents of memory.
 *  @param[in]  inAddress  The memory address to log.
 *  @param[in]  inUnits    The number of memory units to log.
 *
 *  @ingroup memory-utilities
 *
 */
void
Write(Logger & inLogger, const void * inAddress, size_t inUnits)
{
    static const Log::Indent  kIndent = 0;
    static const Log::Level   kLevel  = 0;
    static const unsigned int kWidth  = sizeof(uint8_t);

    Write(inLogger, kIndent, kLevel, inAddress, inUnits, kWidth);
}

/**
 *  @brief
 *    Write a log message using the indicated logger, with no indent
 *    and at the provided level, containing the memory at the
 *    specified address formatted as 1 byte units with the specified
 *    number of memory units.
 *
 *  @param[in]  inLogger   A reference to the logger with which to write
 *                         the specified contents of memory.
 *  @param[in]  inLevel    The level the current message is to be logged
 *                         at.
 *  @param[in]  inAddress  The memory address to log.
 *  @param[in]  inUnits    The number of memory units to log.
 *
 *  @ingroup memory-utilities
 *
 */
void
Write(Logger &     inLogger,
      Log::Level   inLevel,
      const void * inAddress,
      size_t       inUnits)
{
    static const Log::Indent  kIndent = 0;
    static const unsigned int kWidth  = sizeof(uint8_t);

    Write(inLogger, kIndent, inLevel, inAddress, inUnits, kWidth);
}

/**
 *  @brief
 *    Write a log message using the indicated logger, with the
 *    provided indent and level, containing the memory at the
 *    specified address formatted as 1 byte units with the specified
 *    number of memory units.
 *
 *  @param[in]  inLogger   A reference to the logger with which to write
 *                         the specified contents of memory.
 *  @param[in]  inIndent   The level of indendation desired for the
 *                         provided log message.
 *  @param[in]  inLevel    The level the current message is to be logged
 *                         at.
 *  @param[in]  inAddress  The memory address to log.
 *  @param[in]  inUnits    The number of memory units to log.
 *
 *  @ingroup memory-utilities
 *
 */
void
Write(Logger &     inLogger,
      Log::Indent  inIndent,
      Log::Level   inLevel,
      const void * inAddress,
      size_t       inUnits)
{
    static const unsigned int kWidth = sizeof(uint8_t);

    Write(inLogger, inIndent, inLevel, inAddress, inUnits, kWidth);
}

/**
 *  @brief
 *    Write a log message using the indicated logger, with no indent
 *    and at the default level, containing the memory at the specified
 *    address formatted with the specified width and number of memory
 *    units of that width.
 *
 *  @param[in]  inLogger   A reference to the logger with which to write
 *                         the specified contents of memory.
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
void
Write(Logger &     inLogger,
      const void * inAddress,
      size_t       inUnits,
      unsigned int inWidth)
{
    static const Log::Indent kIndent = 0;
    static const Log::Level  kLevel  = 0;

    Write(inLogger, kIndent, kLevel, inAddress, inUnits, inWidth);
}

/**
 *  @brief
 *    Write a log message using the indicated logger, with no indent
 *    and at the provided level, containing the memory at the
 *    specified address formatted at the specified width and number of
 *    memory units of that width.
 *
 *  @param[in]  inLogger   A reference to the logger with which to write
 *                         the specified contents of memory.
 *  @param[in]  inLevel    The level the current message is to be logged
 *                         at.
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
void
Write(Logger &     inLogger,
      Log::Level   inLevel,
      const void * inAddress,
      size_t       inUnits,
      unsigned int inWidth)
{
    static const Log::Indent kIndent = 0;

    Write(inLogger, kIndent, inLevel, inAddress, inUnits, inWidth);
}

static inline void
WriteAddress(Log::Logger &       inLogger,
             const Log::Indent & inIndent,
             const Log::Level &  inLevel,
             void const * const  inAddress)
{
    inLogger.Write(inIndent,
                   inLevel,
                   "%*p: ",
                   static_cast<int>(sizeof(inAddress)),
                   inAddress);
}

static inline void
WriteData(Log::Logger &        inLogger,
          const Log::Indent &  inIndent,
          const Log::Level &   inLevel,
          const uint64_t &     inData,
          const unsigned int & inWidth)
{
    /*
     * The more succinct approach to this would have been:
     *
     *     inLogger.Write(inIndent,
     *                    inLevel,
     *                    "%.*x ",
     *                    inWidth << 1,
     *                    data);
     *
     * however, this does not seem to work correctly and portably for
     * 64-bit types. Consequently, we need to use literal,
     * width-specific format specifiers from inttypes.h.
     *
     */

    switch (inWidth) {

    case 1:
        inLogger.Write(inIndent, inLevel, "%02"  PRIx8  " ", static_cast<uint8_t>(inData));
        break;

    case 2:
        inLogger.Write(inIndent, inLevel, "%04"  PRIx16 " ", static_cast<uint16_t>(inData));
        break;

    case 4:
        inLogger.Write(inIndent, inLevel, "%08"  PRIx32 " ", static_cast<uint32_t>(inData));
        break;

    case 8:
        inLogger.Write(inIndent, inLevel, "%016" PRIx64 " ", static_cast<uint64_t>(inData));
        break;

    default:
        break;

    }
}

static inline void
WriteFill(Log::Logger &        inLogger,
          const Log::Indent &  inIndent,
          const Log::Level &   inLevel,
          const unsigned int & inWidth)
{
    static const char * const kFill = "  ";

    inLogger.Write(inIndent, inLevel, "%*s ", inWidth << 1, kFill);
}

static inline void
WriteASCII(Log::Logger &       inLogger,
           const Log::Indent & inIndent,
           const Log::Level &  inLevel,
           const std::string & inAscii)
{
    inLogger.Write(inIndent, inLevel, "'%s'\n", inAscii.c_str());
}

/**
 *  @brief
 *    Write a log message using the indicated logger, with no indent
 *    and at the default level, containing the memory at the specified
 *    address formatted at the specified width and number of memory
 *    units of that width.
 *
 *  @param[in]  inLogger   A reference to the logger with which to write
 *                         the specified contents of memory.
 *  @param[in]  inIndent   The level of indendation desired for the
 *                         provided log message.
 *  @param[in]  inLevel    The level the current message is to be logged
 *                         at.
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
void
Write(Logger &     inLogger,
      Log::Indent  inIndent,
      Log::Level   inLevel,
      const void * inAddress,
      size_t       inUnits,
      unsigned int inWidth)
{
    const size_t    kDensity = 16;
    const size_t    lSize    = inUnits * inWidth;
    uint64_t        data     = 0;
    size_t          fill;
    string          ascii;
    uint8_t const * p;

    /* Determine the amount of fill to complete a line */

    if ((lSize % kDensity) != 0) {
        fill = kDensity - (lSize % kDensity);
    } else {
        fill = 0;
    }

    p = static_cast<uint8_t const *>(inAddress);

    for (unsigned int i = 0; i < (lSize + fill); i += inWidth) {

        /*
         * Grab the 1, 2, 4 or 8 byte quantity to display; otherwise,
         * there is nothing to do but return early.
         */

        switch (inWidth) {

        case 1:     data = *reinterpret_cast<const uint8_t *>(p);     break;
        case 2:     data = *reinterpret_cast<const uint16_t *>(p);    break;
        case 4:     data = *reinterpret_cast<const uint32_t *>(p);    break;
        case 8:     data = *reinterpret_cast<const uint64_t *>(p);    break;

        default:    return;

        }

        /* Decode the data into an ASCII represenation */

        for (unsigned int k = 0; k < inWidth; k++) {

            if (i < lSize) {
                const char c = static_cast<char>(*p++);

                ascii += ((isprint(c) || c == ' ') ? c : '.');

            } else {
                ascii += '.';

            }
        }

        /* Print the address/offset label */

        if (i % kDensity == 0) {
            WriteAddress(inLogger, inIndent, inLevel, p);
        }

        /* Print the data or fill byte(s) */

        if (i < lSize) {
            WriteData(inLogger, inIndent, inLevel, data, inWidth);

        } else {
            WriteFill(inLogger, inIndent, inLevel, inWidth);

        }

        /* Print the decoded ASCII representation */

        if (((i + inWidth) % kDensity) == 0) {
            WriteASCII(inLogger, inIndent, inLevel, ascii);

            ascii.clear();
        }
    }
}

}; // namespace Memory

}; // namespace Utilities

}; // namespace Log

}; // namespace Nuovations
