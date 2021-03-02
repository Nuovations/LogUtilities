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
 *      This file implements a unit test for Log::Indenter::None.
 */

#include <LogUtilities/LogIndenterNone.hpp>

#include <limits.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogIndenterNone :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogIndenterNone);
    CPPUNIT_TEST(TestDefaultConstruction);
    CPPUNIT_TEST(TestIndent);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestDefaultConstruction(void);
    void TestIndent(void);

private:
    void CheckResults(const std::string & inExpected, const std::string & inActual);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogIndenterNone);

void
TestLogIndenterNone :: TestDefaultConstruction(void)
{
    Log::Indenter::None lNoIndenter;
}

void
TestLogIndenterNone :: TestIndent(void)
{
    Log::Indenter::None lNoIndenter;
    Log::Indent         lIndent;
    std::string         lExpectedResult;
    std::string         lActualResult;

    // Try an empty message with no indent.

    lExpectedResult = "";

    lIndent = 0;

    lActualResult = lNoIndenter.Indent(lIndent, lExpectedResult);

    CheckResults(lExpectedResult, lActualResult);

    // Try an empty string with a single indent.

    lIndent = 1;

    lActualResult = lNoIndenter.Indent(lIndent, lExpectedResult);

    CheckResults(lExpectedResult, lActualResult);

    // Try an empty string with a maximum indent.

    lIndent = UINT_MAX;

    lActualResult = lNoIndenter.Indent(lIndent, lExpectedResult);

    CheckResults(lExpectedResult, lActualResult);

    // Try a non-NULL, non-empty string with no indent.

    lExpectedResult = "Test indent message.\n";

    lIndent = 0;

    lActualResult = lNoIndenter.Indent(lIndent, lExpectedResult);

    CheckResults(lExpectedResult, lActualResult);

    // Try a non-NULL, non-empty string with a single indent.

    lIndent = 1;

    lActualResult = lNoIndenter.Indent(lIndent, lExpectedResult);

    CheckResults(lExpectedResult, lActualResult);

    // Try a non-NULL, non-empty string with a maximum indent.

    lIndent = UINT_MAX;

    lActualResult = lNoIndenter.Indent(lIndent, lExpectedResult);

    CheckResults(lExpectedResult, lActualResult);
}

void
TestLogIndenterNone :: CheckResults(const std::string & inExpected,
                                    const std::string & inActual)
{
    const size_t lActualSize   = inActual.size();
    const size_t lExpectedSize = inExpected.size();

    CPPUNIT_ASSERT_EQUAL(lExpectedSize, lActualSize);

    CPPUNIT_ASSERT_EQUAL(inExpected, inActual);
}
