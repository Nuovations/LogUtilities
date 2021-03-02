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
 *      This file implements a unit test for Log::Formatter::Stamped.
 */

#include <LogUtilities/LogFormatterStamped.hpp>

#include <limits.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogFormatterStamped :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogFormatterStamped);
    CPPUNIT_TEST(TestDefaultConstruction);
    CPPUNIT_TEST(TestFormatWithLevel);
    CPPUNIT_TEST(TestFormatWithDefaultLevel);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestDefaultConstruction(void);
    void TestFormatWithLevel(void);
    void TestFormatWithDefaultLevel(void);

private:
    void TestFormatWithLevel(const std::string &       inExpected,
                             Log::Formatter::Stamped & inFormatter,
                             const Log::Level &        inLevel,
                             const char *              inFormat,
                             ...);
    void TestFormatWithDefaultLevel(const std::string &       inExpected,
                                    Log::Formatter::Stamped & inFormatter,
                                    const char *              inFormat,
                                    ...);

    void CheckResults(const std::string & inExpected, const std::string & inActual);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogFormatterStamped);

void
TestLogFormatterStamped :: TestDefaultConstruction(void)
{
    Log::Formatter::Stamped lStampedFormatter;
}

void
TestLogFormatterStamped :: TestFormatWithLevel(void)
{
    Log::Formatter::Stamped lStampedFormatter;
    Log::Level              lLevel;
    std::string             lExpectedResult;
    std::string             lActualResult;

    // Try a NULL format/message string.

    lExpectedResult = "";

    lLevel = 0;

    lActualResult = lStampedFormatter.Format(lLevel, NULL);

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult, lStampedFormatter, lLevel, NULL);

    // Try an empty string.

    lExpectedResult = "";

    lLevel = 0;

    lActualResult = lStampedFormatter.Format(lLevel, "");

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult, lStampedFormatter, lLevel, "");

    // Try a non-NULL, non-empty string.

    lExpectedResult = "Test format message.\n";

    lLevel = 0;

    // Try the test message at level 0.

    lActualResult = lStampedFormatter.Format(lLevel,
                                             "%s",
                                             lExpectedResult.c_str());

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult,
                        lStampedFormatter,
                        lLevel,
                        "%s",
                        lExpectedResult.c_str());

    // Try the test message at level 1.

    lLevel = 1;

    lActualResult = lStampedFormatter.Format(lLevel,
                                             "%s",
                                             lExpectedResult.c_str());

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult,
                        lStampedFormatter,
                        lLevel,
                        "%s",
                        lExpectedResult.c_str());

    // Try the test message at level UINT_MAX.

    lLevel = UINT_MAX;

    lActualResult = lStampedFormatter.Format(lLevel,
                                             "%s",
                                             lExpectedResult.c_str());

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult,
                        lStampedFormatter,
                        lLevel,
                        "%s",
                        lExpectedResult.c_str());

    // Try a test message with variable arguments.

    lExpectedResult = "An important date is July 4, 1776.\n";

    lLevel = 0;

    lActualResult = lStampedFormatter.Format(lLevel,
                                             "%s %s %u, %u.\n",
                                             "An important date is",
                                             "July",
                                             4,
                                             1776);

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult,
                        lStampedFormatter,
                        lLevel,
                        "%s %s %u, %u.\n",
                        "An important date is",
                        "July",
                        4,
                        1776);
}

void
TestLogFormatterStamped :: TestFormatWithDefaultLevel(void)
{
    Log::Formatter::Stamped lStampedFormatter;
    std::string             lExpectedResult;
    std::string             lActualResult;

    // Try a NULL string.

    lExpectedResult = "";

    lActualResult = lStampedFormatter.Format(NULL);

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithDefaultLevel(lExpectedResult, lStampedFormatter, NULL);

    // Try an empty string.

    lExpectedResult = "";

    lActualResult = lStampedFormatter.Format("");

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithDefaultLevel(lExpectedResult, lStampedFormatter, "");

    // Try a non-NULL, non-empty string.

    lExpectedResult = "Test format message.\n";

    // Try the test message.

    lActualResult = lStampedFormatter.Format("%s", lExpectedResult.c_str());

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithDefaultLevel(lExpectedResult,
                               lStampedFormatter,
                               "%s",
                               lExpectedResult.c_str());

    // Try a test message with variable arguments.

    lExpectedResult = "An important date is July 4, 1776.\n";

    lActualResult = lStampedFormatter.Format("%s %s %u, %u.\n",
                                             "An important date is",
                                             "July",
                                             4,
                                             1776);

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithDefaultLevel(lExpectedResult,
                               lStampedFormatter,
                               "%s %s %u, %u.\n",
                               "An important date is",
                               "July",
                               4,
                               1776);
}

void
TestLogFormatterStamped :: TestFormatWithLevel(
    const std::string &       inExpected,
    Log::Formatter::Stamped & inFormatter,
    const Log::Level &        inLevel,
    const char *              inFormat,
    ...)
{
    va_list     lList;
    std::string lString;

    va_start(lList, inFormat);

    lString = inFormatter.Format(inLevel, inFormat, lList);

    va_end(lList);

    CheckResults(inExpected, lString);
}

void
TestLogFormatterStamped :: TestFormatWithDefaultLevel(
    const std::string &       inExpected,
    Log::Formatter::Stamped & inFormatter,
    const char *              inFormat,
    ...)
{
    va_list     lList;
    std::string lString;

    va_start(lList, inFormat);

    lString = inFormatter.Format(inFormat, lList);

    va_end(lList);

    CheckResults(inExpected, lString);
}

/**
 *  Check the expected versus actual formatting results
 *
 *  A stamped formatter output is of the form:
 *
 *    <year>-<month>-<day> <hour>:<minute>:<second> [<PID>:<thread>] (<level>) <message>
 *
 *  since everything up to <message> is variable, attempt to search
 *  for the ')' after <level>, skip the ') ' and then compare
 *  <message>.
 *
 */
void
TestLogFormatterStamped :: CheckResults(const std::string & inExpected,
                                        const std::string & inActual)
{
    const size_t      kSkip         = sizeof (')') + sizeof (' ');
    const size_t      lExpectedSize = inExpected.size();
    const size_t      lPos          = inActual.find(')');
    const std::string lActual       = ((lPos != std::string::npos)
                                           ? inActual.substr(lPos + kSkip)
                                           : inActual);
    const size_t      lActualSize   = lActual.size();

    CPPUNIT_ASSERT_EQUAL(lExpectedSize, lActualSize);

    CPPUNIT_ASSERT_EQUAL(inExpected, lActual);
}
