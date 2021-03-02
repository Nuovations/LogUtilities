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
 *      This file implements a unit test for Log::Formatter::Plain.
 */

#include <LogUtilities/LogFormatterPlain.hpp>

#include <limits.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogFormatterPlain :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogFormatterPlain);
    CPPUNIT_TEST(TestDefaultConstruction);
    CPPUNIT_TEST(TestFormatWithLevel);
    CPPUNIT_TEST(TestFormatWithDefaultLevel);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestDefaultConstruction(void);
    void TestFormatWithLevel(void);
    void TestFormatWithDefaultLevel(void);

private:
    void TestFormatWithLevel(const std::string &     inExpected,
                             Log::Formatter::Plain & inFormatter,
                             const Log::Level &      inLevel,
                             const char *            inFormat,
                             ...);
    void TestFormatWithDefaultLevel(const std::string &     inExpected,
                                    Log::Formatter::Plain & inFormatter,
                                    const char *            inFormat,
                                    ...);

    void CheckResults(const std::string & inExpected, const std::string & inActual);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogFormatterPlain);

void
TestLogFormatterPlain :: TestDefaultConstruction(void)
{
    Log::Formatter::Plain lPlainFormatter;
}

void
TestLogFormatterPlain :: TestFormatWithLevel(void)
{
    Log::Formatter::Plain lPlainFormatter;
    Log::Level            lLevel;
    std::string           lExpectedResult;
    std::string           lActualResult;

    // Try a NULL format/message string.

    lExpectedResult = "";

    lLevel = 0;

    lActualResult = lPlainFormatter.Format(lLevel, NULL);

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult, lPlainFormatter, lLevel, NULL);

    // Try an empty string.

    lExpectedResult = "";

    lLevel = 0;

    lActualResult = lPlainFormatter.Format(lLevel, "");

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult, lPlainFormatter, lLevel, "");

    // Try a non-NULL, non-empty string.

    lExpectedResult = "Test format message.\n";

    lLevel = 0;

    // Try the test message at level 0.

    lActualResult = lPlainFormatter.Format(lLevel,
                                           "%s",
                                           lExpectedResult.c_str());

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult,
                        lPlainFormatter,
                        lLevel,
                        "%s",
                        lExpectedResult.c_str());

    // Try the test message at level 1.

    lLevel = 1;

    lActualResult = lPlainFormatter.Format(lLevel,
                                           "%s",
                                           lExpectedResult.c_str());

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult,
                        lPlainFormatter,
                        lLevel,
                        "%s",
                        lExpectedResult.c_str());

    // Try the test message at level UINT_MAX.

    lLevel = UINT_MAX;

    lActualResult = lPlainFormatter.Format(lLevel,
                                           "%s",
                                           lExpectedResult.c_str());

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult,
                        lPlainFormatter,
                        lLevel,
                        "%s",
                        lExpectedResult.c_str());

    // Try a test message with variable arguments.

    lExpectedResult = "An important date is July 4, 1776.\n";

    lLevel = 0;

    lActualResult = lPlainFormatter.Format(lLevel,
                                           "%s %s %u, %u.\n",
                                           "An important date is",
                                           "July",
                                           4,
                                           1776);

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithLevel(lExpectedResult,
                        lPlainFormatter,
                        lLevel,
                        "%s %s %u, %u.\n",
                        "An important date is",
                        "July",
                        4,
                        1776);
}

void
TestLogFormatterPlain :: TestFormatWithDefaultLevel(void)
{
    Log::Formatter::Plain lPlainFormatter;
    std::string           lExpectedResult;
    std::string           lActualResult;

    // Try a NULL string.

    lExpectedResult = "";

    lActualResult = lPlainFormatter.Format(NULL);

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithDefaultLevel(lExpectedResult, lPlainFormatter, NULL);

    // Try an empty string.

    lExpectedResult = "";

    lActualResult = lPlainFormatter.Format("");

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithDefaultLevel(lExpectedResult, lPlainFormatter, "");

    // Try a non-NULL, non-empty string.

    lExpectedResult = "Test format message.\n";

    // Try the test message.

    lActualResult = lPlainFormatter.Format("%s", lExpectedResult.c_str());

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithDefaultLevel(lExpectedResult,
                               lPlainFormatter,
                               "%s",
                               lExpectedResult.c_str());

    // Try a test message with variable arguments.

    lExpectedResult = "An important date is July 4, 1776.\n";

    lActualResult = lPlainFormatter.Format("%s %s %u, %u.\n",
                                           "An important date is",
                                           "July",
                                           4,
                                           1776);

    CheckResults(lExpectedResult, lActualResult);

    TestFormatWithDefaultLevel(lExpectedResult,
                               lPlainFormatter,
                               "%s %s %u, %u.\n",
                               "An important date is",
                               "July",
                               4,
                               1776);
}

void
TestLogFormatterPlain :: TestFormatWithLevel(const std::string &     inExpected,
                                             Log::Formatter::Plain & inFormatter,
                                             const Log::Level &      inLevel,
                                             const char *            inFormat,
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
TestLogFormatterPlain :: TestFormatWithDefaultLevel(
    const std::string &     inExpected,
    Log::Formatter::Plain & inFormatter,
    const char *            inFormat,
    ...)
{
    va_list     lList;
    std::string lString;

    va_start(lList, inFormat);

    lString = inFormatter.Format(inFormat, lList);

    va_end(lList);

    CheckResults(inExpected, lString);
}

void
TestLogFormatterPlain :: CheckResults(const std::string & inExpected,
                                     const std::string & inActual)
{
    const size_t lActualSize   = inActual.size();
    const size_t lExpectedSize = inExpected.size();

    CPPUNIT_ASSERT_EQUAL(lExpectedSize, lActualSize);

    CPPUNIT_ASSERT_EQUAL(inExpected, inActual);
}
