/*
 *    Copyright (c) 2021 Nuovation System Designs, LLC
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
 *      This file implements a unit test for Log::Utilities::Memory
 */

#include <LogUtilities/LogFilterAlways.hpp>
#include <LogUtilities/LogFormatterPlain.hpp>
#include <LogUtilities/LogGlobals.hpp>
#include <LogUtilities/LogIndenterNone.hpp>
#include <LogUtilities/LogLogger.hpp>
#include <LogUtilities/LogMemoryUtilities.hpp>
#include <LogUtilities/LogWriterDescriptor.hpp>

#include <ostream>
#include <regex>
#include <string>

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestLogUtilitiesBasis.hpp"

using namespace Nuovations;
using namespace std;

class TestMemoryLines
{
public:
    TestMemoryLines(const char * inMemoryLines);
    ~TestMemoryLines(void) = default;

    bool operator ==(const TestMemoryLines & inMemoryLines) const;

    size_t size(void) const;

    const std::string & operator ()(void) const;

    std::string & operator ()(void);

    std::ostream & operator <<(const TestMemoryLines & inMemoryLines) const;

private:
    class MemoryLine
    {
    public:
        MemoryLine(void);

        bool operator ==(const MemoryLine & inMemoryLine) const;
        bool operator !=(const MemoryLine & inMemoryLine) const;

        MemoryLine & operator =(const MemoryLine & inMemoryLine);
        MemoryLine   operator ++(int inDummy);

    public:
        size_t mAddressPosition;
        size_t mDataPosition;
        size_t mNewlinePosition;

    private:
        friend class TestMemoryLines;

        MemoryLine(const TestMemoryLines & inMemoryLines);
        MemoryLine(const TestMemoryLines & inMemoryLines,
                   const size_t &          inAddressPosition,
                   const size_t &          inDataPosition,
                   const size_t &          inNewlinePosition);

        const TestMemoryLines * mTestMemoryLines;
    };

    MemoryLine begin(void) const;
    MemoryLine end(void) const;

    bool CompareAddress(const MemoryLine &      inOurLine,
                        const TestMemoryLines & inTheirLines,
                        const MemoryLine &      inTheirLine) const;
    bool CompareData(const MemoryLine &      inOurLine,
                     const TestMemoryLines & inTheirLines,
                     const MemoryLine &      inTheirLine) const;

private:
    std::string mMemoryLines;
};

class TestLogMemoryUtilities :
    public TestLogUtilitiesBasis
{
    CPPUNIT_TEST_SUITE(TestLogMemoryUtilities);
    CPPUNIT_TEST(TestWithExplicitLoggerWithInvalidWidth);
    CPPUNIT_TEST(TestWithExplicitLoggerWithDefaultIndentAndLevel);
    CPPUNIT_TEST(TestWithExplicitLoggerWithDefaultIndentWithLevel);
    CPPUNIT_TEST(TestWithExplicitLoggerWithIndentAndLevel);
    CPPUNIT_TEST(TestWithImplicitLoggerWithInvalidWidth);
    CPPUNIT_TEST(TestWithImplicitLoggerWithDefaultIndentAndLevel);
    CPPUNIT_TEST(TestWithImplicitLoggerWithDefaultIndentWithLevel);
    CPPUNIT_TEST(TestWithImplicitLoggerWithIndentAndLevel);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestWithExplicitLoggerWithInvalidWidth(void);
    void TestWithExplicitLoggerWithDefaultIndentAndLevel(void);
    void TestWithExplicitLoggerWithDefaultIndentWithLevel(void);
    void TestWithExplicitLoggerWithIndentAndLevel(void);
    void TestWithImplicitLoggerWithInvalidWidth(void);
    void TestWithImplicitLoggerWithDefaultIndentAndLevel(void);
    void TestWithImplicitLoggerWithDefaultIndentWithLevel(void);
    void TestWithImplicitLoggerWithIndentAndLevel(void);

private:
    int CreateTemporaryFile(char * aPathBuffer);
    void CheckResults(const char * aPathBuffer, const TestMemoryLines & aExpected);

    static constexpr uint8_t     kUint8x8s[8]   =
        {
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
        };
    static constexpr uint8_t     kUint32x8s[32] =
        {
            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
            0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
            0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
            0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f
        };
    static constexpr uint16_t    kUint16s[16]   =
        {
            0x3000, 0x3001, 0x3002, 0x3003,
            0x3004, 0x3005, 0x3006, 0x3007,
            0x3008, 0x3009, 0x300a, 0x300b,
            0x300c, 0x300d, 0x300e, 0x300f
        };
    static constexpr uint32_t    kUint32s[8]    =
        {
            0x40000000, 0x40000001, 0x40000002, 0x40000003,
            0x40000004, 0x40000005, 0x40000006, 0x40000007,
        };
    static constexpr uint64_t    kUint64s[8]    =
        {
            0x5000000000000000, 0x5000000000000001,
            0x5000000000000002, 0x5000000000000003,
            0x5000000000000004, 0x5000000000000005,
            0x5000000000000006, 0x5000000000000007
        };
    static constexpr size_t      kOffsets[2] = { 0, 3 };
    static const TestMemoryLines kExpectedMemoryLines;
};

constexpr uint8_t     TestLogMemoryUtilities ::kUint8x8s[];
constexpr uint8_t     TestLogMemoryUtilities ::kUint32x8s[];
constexpr uint16_t    TestLogMemoryUtilities ::kUint16s[];
constexpr uint32_t    TestLogMemoryUtilities ::kUint32s[];
constexpr uint64_t    TestLogMemoryUtilities ::kUint64s[];
constexpr size_t      TestLogMemoryUtilities ::kOffsets[];
const TestMemoryLines TestLogMemoryUtilities ::kExpectedMemoryLines =
    "<address>: 00 01 02 03 04 05 06 07                         '................'\n"
    "<address>: 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f '................'\n"
    "<address>: 20 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f ' !\"#$%&'()*+,-./'\n"
    "<address>: 00 30 01 30 02 30 03 30 04 30 05 30 06 30 07 30 '.0.0.0.0.0.0.0.0'\n"
    "<address>: 00 00 00 40 01 00 00 40                         '...@...@........'\n"
    "<address>: 00 00 00 00 00 00 00 50                         '.......P........'\n"
    "<address>: 00 01 02 03 04 05 06 07                         '................'\n"
    "<address>: 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f '................'\n"
    "<address>: 20 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f ' !\"#$%&'()*+,-./'\n"
    "<address>: 3000 3001 3002 3003 3004 3005 3006 3007 '.0.0.0.0.0.0.0.0'\n"
    "<address>: 3008 3009 300a 300b 300c 300d 300e 300f '.0.0.0.0.0.0.0.0'\n"
    "<address>: 40000000 40000001 40000002 40000003 '...@...@...@...@'\n"
    "<address>: 40000004 40000005 40000006 40000007 '...@...@...@...@'\n"
    "<address>: 5000000000000000 5000000000000001 '.......P.......P'\n"
    "<address>: 5000000000000002 5000000000000003 '.......P.......P'\n"
    "<address>: 5000000000000004 5000000000000005 '.......P.......P'\n"
    "<address>: 5000000000000006 5000000000000007 '.......P.......P'\n"
    "<address>: 03 04 05 06 07                                  '................'\n"
    "<address>: 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 20 21 22 '............. !\"'\n"
    "<address>: 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f          '#$%&'()*+,-./...'\n"
    "<address>: 03 30 04 30 05 30 06 30 07 30 08 30 09          '.0.0.0.0.0.0....'\n"
    "<address>: 03 00 00 40 04                                  '...@............'\n"
    "<address>: 03 00 00 00 00                                  '................'\n"
    "<address>: 03 04 05 06 07                                  '................'\n"
    "<address>: 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 20 21 22 '............. !\"'\n"
    "<address>: 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f          '#$%&'()*+,-./...'\n"
    "<address>: 3003 3004 3005 3006 3007 3008 3009 300a '.0.0.0.0.0.0.0.0'\n"
    "<address>: 300b 300c 300d 300e 300f                '.0.0.0.0.0......'\n"
    "<address>: 40000003 40000004 40000005 40000006 '...@...@...@...@'\n"
    "<address>: 40000007                            '...@............'\n"
    "<address>: 5000000000000003 5000000000000004 '.......P.......P'\n"
    "<address>: 5000000000000005 5000000000000006 '.......P.......P'\n"
    "<address>: 5000000000000007                  '.......P........'\n";

TestMemoryLines :: TestMemoryLines(const char * inMemoryLines) :
    mMemoryLines(inMemoryLines)
{
    return;
}

TestMemoryLines :: MemoryLine :: MemoryLine(void) :
    mAddressPosition(0),
    mDataPosition(0),
    mNewlinePosition(0),
    mTestMemoryLines(nullptr)
{
    return;
}

TestMemoryLines :: MemoryLine :: MemoryLine(const TestMemoryLines & inTestMemoryLines) :
    mAddressPosition(0),
    mDataPosition(0),
    mNewlinePosition(0),
    mTestMemoryLines(&inTestMemoryLines)
{
    return;
}

TestMemoryLines :: MemoryLine :: MemoryLine(const TestMemoryLines & inTestMemoryLines,
                                            const size_t &          inAddressPosition,
                                            const size_t &          inDataPosition,
                                            const size_t &          inNewlinePosition) :
    mAddressPosition(inAddressPosition),
    mDataPosition(inDataPosition),
    mNewlinePosition(inNewlinePosition),
    mTestMemoryLines(&inTestMemoryLines)
{
    return;
}

bool
TestMemoryLines :: MemoryLine ::operator ==(const MemoryLine & inMemoryLine) const
{
    bool lRetval;

    lRetval = ((mAddressPosition == inMemoryLine.mAddressPosition) &&
               (mDataPosition    == inMemoryLine.mDataPosition   ) &&
               (mNewlinePosition == inMemoryLine.mNewlinePosition) &&
               (mTestMemoryLines == inMemoryLine.mTestMemoryLines));

    return (lRetval);
}

bool
TestMemoryLines :: MemoryLine :: operator !=(const MemoryLine & inMemoryLine) const
{
    return (!(*this == inMemoryLine));
}

TestMemoryLines::MemoryLine &
TestMemoryLines :: MemoryLine :: operator =(const MemoryLine & inMemoryLine)
{
    mAddressPosition = inMemoryLine.mAddressPosition;
    mDataPosition    = inMemoryLine.mDataPosition;
    mNewlinePosition = inMemoryLine.mNewlinePosition;
    mTestMemoryLines = inMemoryLine.mTestMemoryLines;

    return (*this);
}

TestMemoryLines::MemoryLine
TestMemoryLines :: MemoryLine :: operator ++(int inDummy)
{
    static const char kColon               = ':';
    static const char kNewline             = '\n';
    const MemoryLine  lCurrentLine         = *this;
    const size_t      lNextAddressPosition = mNewlinePosition + 1;

    (void)inDummy;

    // When this has incremented past the last line, ALL of the data
    // members should be set to string::npos. The find method covers
    // that for data and newline. We have to manually handle it for
    // the address.

    mAddressPosition = ((lNextAddressPosition >= mTestMemoryLines->size()) ? string::npos : lNextAddressPosition);
    mDataPosition    = mTestMemoryLines->mMemoryLines.find(kColon, mAddressPosition);
    mNewlinePosition = mTestMemoryLines->mMemoryLines.find(kNewline, mAddressPosition);

    return (lCurrentLine);
}

TestMemoryLines::MemoryLine
TestMemoryLines :: begin(void) const
{
    static const char kColon   = ':';
    static const char kNewline = '\n';
    MemoryLine        lMemoryLine(*this);

    lMemoryLine.mAddressPosition = 0;
    lMemoryLine.mDataPosition    = mMemoryLines.find(kColon, lMemoryLine.mAddressPosition);
    lMemoryLine.mNewlinePosition = mMemoryLines.find(kNewline, lMemoryLine.mAddressPosition);

    // If we found no data and no newline, then the lines are either
    // malformed or we are at the end. Regardless, return the end
    // iterator. Otherwise, return the start iterator.

    if ((lMemoryLine.mDataPosition    == string::npos) &&
        (lMemoryLine.mNewlinePosition == string::npos)) {
        return (end());
    } else {
        return (lMemoryLine);
    }
}

TestMemoryLines::MemoryLine
TestMemoryLines :: end(void) const
{
    const MemoryLine kLastMemoryLine(*this,
                                     string::npos,
                                     string::npos,
                                     string::npos);

    return (kLastMemoryLine);
}

bool
TestMemoryLines :: CompareAddress(const MemoryLine &      inOurLine,
                                  const TestMemoryLines & inTheirLines,
                                  const MemoryLine &      inTheirLine) const
{
    const auto  ourAddressIteratorBegin   = mMemoryLines.cbegin() + static_cast<string::difference_type>(inOurLine.mAddressPosition);
    const auto  ourAddressIteratorEnd     = mMemoryLines.cbegin() + static_cast<string::difference_type>(inOurLine.mDataPosition);
    const auto  theirAddressIteratorBegin = inTheirLines.mMemoryLines.cbegin() + static_cast<string::difference_type>(inTheirLine.mAddressPosition);
    const auto  theirAddressIteratorEnd   = inTheirLines.mMemoryLines.cbegin() + static_cast<string::difference_type>(inTheirLine.mDataPosition);
    const regex lRegex("(<address>|0x[[:xdigit:]]{4,16})");
    bool        lRetval = true;

    if (!regex_match(ourAddressIteratorBegin,   ourAddressIteratorEnd,   lRegex) ||
        !regex_match(theirAddressIteratorBegin, theirAddressIteratorEnd, lRegex)) {
        lRetval = false;
    }

    return (lRetval);
}

bool
TestMemoryLines :: CompareData(const MemoryLine &      inOurLine,
                               const TestMemoryLines & inTheirLines,
                               const MemoryLine &      inTheirLine) const
{
    const size_t ourDataLength   = inOurLine.mNewlinePosition   - inOurLine.mDataPosition;
    const size_t theirDataLength = inTheirLine.mNewlinePosition - inTheirLine.mDataPosition;
    int          lCompare;

    lCompare = mMemoryLines.compare(inOurLine.mDataPosition,
                                    ourDataLength,
                                    inTheirLines.mMemoryLines,
                                    inTheirLine.mDataPosition,
                                    theirDataLength);

    return (lCompare == 0);
}

bool
TestMemoryLines :: operator ==(const TestMemoryLines & inTheirLines) const
{
    MemoryLine lOurLine;
    MemoryLine lTheirLine;
    bool       lRetval = true;

    // Walk through each line, ours and theirs, comparing the address
    // portion for equivalence and comparing the data portion for
    // equality.

    lOurLine   = begin();
    lTheirLine = inTheirLines.begin();

    while (lRetval) {
        const bool lOurEnd   = (lOurLine == end());
        const bool lTheirEnd = (lTheirLine == inTheirLines.end());

        // If we are at our end but not theirs or vice versa, then we
        // have a line number mismatch and the lines, collectively are
        // not equivalent.

        if ((lOurEnd && !lTheirEnd) || (!lOurEnd && lTheirEnd)) {
            lRetval = false;
            break;
        }

        if (lOurEnd && lTheirEnd) {
            break;
        }

        // Check the address and the data portion

        lRetval = (CompareAddress(lOurLine, inTheirLines, lTheirLine) &&
                   CompareData(lOurLine, inTheirLines, lTheirLine));

        // Get our and their next line

        lOurLine++;
        lTheirLine++;
    }

    return (lRetval);
}

size_t
TestMemoryLines :: size(void) const
{
    return (mMemoryLines.size());
}

const std::string &
TestMemoryLines :: operator ()(void) const
{
    return (mMemoryLines);
}

std::string &
TestMemoryLines :: operator ()(void)
{
    return (mMemoryLines);
}

static std::ostream &
operator <<(std::ostream & inStream, const TestMemoryLines & inMemoryLines)
{
    const std::string & lString = (const std::string &)(inMemoryLines);

    inStream << lString;

    return (inStream);
}

namespace Detail
{

template <typename T, size_t N>
constexpr size_t
elementsof(const T (&)[N])
{
    return (N);
}

}; // namespace Detail

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogMemoryUtilities);

void
TestLogMemoryUtilities :: TestWithExplicitLoggerWithInvalidWidth(void)
{
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::None   lNoneIndenter;
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);
        Log::Logger             lLogger(lAlwaysFilter,
                                        lNoneIndenter,
                                        lPlainFormatter,
                                        lDescriptorWriter);

        for (auto lOffset : kOffsets) {
            static constexpr unsigned int kWidth = 3;

            // Default indent and level

            Log::Utilities::Memory::Write(lLogger, &kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset, kWidth);
            Log::Utilities::Memory::Write(lLogger, &kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset, kWidth);
            Log::Utilities::Memory::Write(lLogger, &kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset, kWidth);
            Log::Utilities::Memory::Write(lLogger, &kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset, kWidth);
            Log::Utilities::Memory::Write(lLogger, &kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset, kWidth);
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, "");
}

void
TestLogMemoryUtilities :: TestWithExplicitLoggerWithDefaultIndentAndLevel(void)
{
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::None   lNoneIndenter;
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);
        Log::Logger             lLogger(lAlwaysFilter,
                                        lNoneIndenter,
                                        lPlainFormatter,
                                        lDescriptorWriter);

        for (auto lOffset : kOffsets) {
            // Default indent, level, and width

            Log::Utilities::Memory::Write(lLogger, &kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset);
            Log::Utilities::Memory::Write(lLogger, &kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset);
            Log::Utilities::Memory::Write(lLogger, &kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset);
            Log::Utilities::Memory::Write(lLogger, &kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset);
            Log::Utilities::Memory::Write(lLogger, &kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset);

            // Default indent and level

            Log::Utilities::Memory::Write(lLogger, &kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset, sizeof (kUint8x8s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, &kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset, sizeof (kUint32x8s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, &kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset, sizeof (kUint16s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, &kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset, sizeof (kUint32s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, &kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset, sizeof (kUint64s[lOffset]));
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpectedMemoryLines);
}

void
TestLogMemoryUtilities :: TestWithExplicitLoggerWithDefaultIndentWithLevel(void)
{
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::None   lNoneIndenter;
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        const Log::Level        kLevel = 0;
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);
        Log::Logger             lLogger(lAlwaysFilter,
                                        lNoneIndenter,
                                        lPlainFormatter,
                                        lDescriptorWriter);

        for (auto lOffset : kOffsets) {
            // Default indent with level and default width

            Log::Utilities::Memory::Write(lLogger, kLevel, &kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset);
            Log::Utilities::Memory::Write(lLogger, kLevel, &kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset);
            Log::Utilities::Memory::Write(lLogger, kLevel, &kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset);
            Log::Utilities::Memory::Write(lLogger, kLevel, &kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset);
            Log::Utilities::Memory::Write(lLogger, kLevel, &kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset);

            // Default indent with level

            Log::Utilities::Memory::Write(lLogger, kLevel, &kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset, sizeof (kUint8x8s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, kLevel, &kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset, sizeof (kUint32x8s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, kLevel, &kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset, sizeof (kUint16s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, kLevel, &kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset, sizeof (kUint32s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, kLevel, &kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset, sizeof (kUint64s[lOffset]));
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpectedMemoryLines);
}

void
TestLogMemoryUtilities :: TestWithExplicitLoggerWithIndentAndLevel(void)
{
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::None   lNoneIndenter;
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        const Log::Indent       kIndent = 0;
        const Log::Level        kLevel  = 0;
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);
        Log::Logger             lLogger(lAlwaysFilter,
                                        lNoneIndenter,
                                        lPlainFormatter,
                                        lDescriptorWriter);

        for (auto lOffset : kOffsets) {
            // With indent and level and default width

            Log::Utilities::Memory::Write(lLogger, kIndent, kLevel, &kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset);
            Log::Utilities::Memory::Write(lLogger, kIndent, kLevel, &kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset);
            Log::Utilities::Memory::Write(lLogger, kIndent, kLevel, &kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset);
            Log::Utilities::Memory::Write(lLogger, kIndent, kLevel, &kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset);
            Log::Utilities::Memory::Write(lLogger, kIndent, kLevel, &kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset);

            // With indent and level

            Log::Utilities::Memory::Write(lLogger, kIndent, kLevel, &kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset, sizeof (kUint8x8s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, kIndent, kLevel, &kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset, sizeof (kUint32x8s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, kIndent, kLevel, &kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset, sizeof (kUint16s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, kIndent, kLevel, &kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset, sizeof (kUint32s[lOffset]));
            Log::Utilities::Memory::Write(lLogger, kIndent, kLevel, &kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset, sizeof (kUint64s[lOffset]));
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpectedMemoryLines);
}

void
TestLogMemoryUtilities :: TestWithImplicitLoggerWithInvalidWidth(void)
{
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::None   lNoneIndenter;
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);

        Log::Debug().SetFilter(lAlwaysFilter);
        Log::Debug().SetIndenter(lNoneIndenter);
        Log::Debug().SetFormatter(lPlainFormatter);
        Log::Debug().SetWriter(lDescriptorWriter);

        for (auto lOffset : kOffsets) {
            static constexpr unsigned int kWidth = 3;

            // Default indent and level

            Log::Utilities::Memory::Write(&kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset, kWidth);
            Log::Utilities::Memory::Write(&kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset, kWidth);
            Log::Utilities::Memory::Write(&kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset, kWidth);
            Log::Utilities::Memory::Write(&kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset, kWidth);
            Log::Utilities::Memory::Write(&kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset, kWidth);
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, "");
}

void
TestLogMemoryUtilities :: TestWithImplicitLoggerWithDefaultIndentAndLevel(void)
{
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::None   lNoneIndenter;
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);

        Log::Debug().SetFilter(lAlwaysFilter);
        Log::Debug().SetIndenter(lNoneIndenter);
        Log::Debug().SetFormatter(lPlainFormatter);
        Log::Debug().SetWriter(lDescriptorWriter);

        for (auto lOffset : kOffsets) {
            // Default indent, level, and width

            Log::Utilities::Memory::Write(&kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset);
            Log::Utilities::Memory::Write(&kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset);
            Log::Utilities::Memory::Write(&kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset);
            Log::Utilities::Memory::Write(&kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset);
            Log::Utilities::Memory::Write(&kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset);

            // Default indent and level

            Log::Utilities::Memory::Write(&kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset, sizeof (kUint8x8s[lOffset]));
            Log::Utilities::Memory::Write(&kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset, sizeof (kUint32x8s[lOffset]));
            Log::Utilities::Memory::Write(&kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset, sizeof (kUint16s[lOffset]));
            Log::Utilities::Memory::Write(&kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset, sizeof (kUint32s[lOffset]));
            Log::Utilities::Memory::Write(&kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset, sizeof (kUint64s[lOffset]));
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpectedMemoryLines);
}

void
TestLogMemoryUtilities :: TestWithImplicitLoggerWithDefaultIndentWithLevel(void)
{
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::None   lNoneIndenter;
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        const Log::Level        kLevel = 0;
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);

        Log::Debug().SetFilter(lAlwaysFilter);
        Log::Debug().SetIndenter(lNoneIndenter);
        Log::Debug().SetFormatter(lPlainFormatter);
        Log::Debug().SetWriter(lDescriptorWriter);

        for (auto lOffset : kOffsets) {
            // Default indent with level and default width

            Log::Utilities::Memory::Write(kLevel, &kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset);
            Log::Utilities::Memory::Write(kLevel, &kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset);
            Log::Utilities::Memory::Write(kLevel, &kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset);
            Log::Utilities::Memory::Write(kLevel, &kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset);
            Log::Utilities::Memory::Write(kLevel, &kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset);

            // Default indent with level

            Log::Utilities::Memory::Write(kLevel, &kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset, sizeof (kUint8x8s[lOffset]));
            Log::Utilities::Memory::Write(kLevel, &kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset, sizeof (kUint32x8s[lOffset]));
            Log::Utilities::Memory::Write(kLevel, &kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset, sizeof (kUint16s[lOffset]));
            Log::Utilities::Memory::Write(kLevel, &kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset, sizeof (kUint32s[lOffset]));
            Log::Utilities::Memory::Write(kLevel, &kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset, sizeof (kUint64s[lOffset]));
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpectedMemoryLines);
}

void
TestLogMemoryUtilities :: TestWithImplicitLoggerWithIndentAndLevel(void)
{
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::None   lNoneIndenter;
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        const Log::Indent       kIndent = 0;
        const Log::Level        kLevel  = 0;
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);

        Log::Debug().SetFilter(lAlwaysFilter);
        Log::Debug().SetIndenter(lNoneIndenter);
        Log::Debug().SetFormatter(lPlainFormatter);
        Log::Debug().SetWriter(lDescriptorWriter);

        for (auto lOffset : kOffsets) {
            // With indent and level and default width

            Log::Utilities::Memory::Write(kIndent, kLevel, &kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset);
            Log::Utilities::Memory::Write(kIndent, kLevel, &kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset);
            Log::Utilities::Memory::Write(kIndent, kLevel, &kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset);
            Log::Utilities::Memory::Write(kIndent, kLevel, &kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset);
            Log::Utilities::Memory::Write(kIndent, kLevel, &kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset);

            // With indent and level

            Log::Utilities::Memory::Write(kIndent, kLevel, &kUint8x8s[lOffset],  Detail::elementsof(kUint8x8s)  - lOffset, sizeof (kUint8x8s[lOffset]));
            Log::Utilities::Memory::Write(kIndent, kLevel, &kUint32x8s[lOffset], Detail::elementsof(kUint32x8s) - lOffset, sizeof (kUint32x8s[lOffset]));
            Log::Utilities::Memory::Write(kIndent, kLevel, &kUint16s[lOffset],   Detail::elementsof(kUint16s)   - lOffset, sizeof (kUint16s[lOffset]));
            Log::Utilities::Memory::Write(kIndent, kLevel, &kUint32s[lOffset],   Detail::elementsof(kUint32s)   - lOffset, sizeof (kUint32s[lOffset]));
            Log::Utilities::Memory::Write(kIndent, kLevel, &kUint64s[lOffset],   Detail::elementsof(kUint64s)   - lOffset, sizeof (kUint64s[lOffset]));
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpectedMemoryLines);
}

int
TestLogMemoryUtilities :: CreateTemporaryFile(char * aPathBuffer)
{
    static const char * const kTestName = "memory-utilities";
    int                       lStatus;

    lStatus = CreateTemporaryFileFromName(kTestName, aPathBuffer);

    return (lStatus);
}

void
TestLogMemoryUtilities :: CheckResults(const char *            aPathBuffer,
                                       const TestMemoryLines & aExpected)
{
    struct stat lStat;
    int         lStatus;
    int         lDescriptor;
    char *      lBuffer;
    ssize_t     lResidual;

    lStatus = stat(aPathBuffer, &lStat);
    CPPUNIT_ASSERT(lStatus == 0);

    lDescriptor = open(aPathBuffer, O_RDONLY);
    CPPUNIT_ASSERT(lDescriptor > 0);

    lBuffer = new char[static_cast<size_t>(lStat.st_size) + 1];
    CPPUNIT_ASSERT(lBuffer != NULL);

    lResidual = read(lDescriptor, &lBuffer[0], static_cast<size_t>(lStat.st_size));
    CPPUNIT_ASSERT_EQUAL(lStat.st_size, static_cast<off_t>(lResidual));

    close(lDescriptor);

    lBuffer[static_cast<size_t>(lStat.st_size)] = '\0';

    CPPUNIT_ASSERT_EQUAL(aExpected, TestMemoryLines(lBuffer));

    delete [] lBuffer;

    lStatus = unlink(aPathBuffer);
    CPPUNIT_ASSERT(lStatus == 0);
}
