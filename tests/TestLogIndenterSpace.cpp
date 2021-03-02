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
 *      This file implements a unit test for Log::Indenter::Space.
 */

#include <LogUtilities/LogIndenterSpace.hpp>

#include <string>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogIndenterSpace :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogIndenterSpace);
    CPPUNIT_TEST(TestConstruction);
    CPPUNIT_TEST(TestFirstIndent);
    CPPUNIT_TEST(TestEveryIndent);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestConstruction(void);
    void TestFirstIndent(void);
    void TestEveryIndent(void);

private:
    void CheckResults(const std::string & inExpected, const std::string & inActual);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogIndenterSpace);

void
TestLogIndenterSpace :: TestConstruction(void)
{
    Log::Indenter::Space lSpace;
    Log::Indenter::Space lSpaceWithCount(3);
    Log::Indenter::Space lSpaceWithFirstFlag(Log::Indenter::Space::Flags::kFirst);
    Log::Indenter::Space lSpaceWithEveryFlag(Log::Indenter::Space::Flags::kEvery);
    Log::Indenter::Space lSpaceWithCountAndFirstFlag(3, Log::Indenter::Space::Flags::kFirst);
    Log::Indenter::Space lSpaceWithCountAndEveryFlag(3, Log::Indenter::Space::Flags::kEvery);
}

void
TestLogIndenterSpace :: TestFirstIndent(void)
{
    const size_t         lCount       = 4;
    const char           lCharacter = ' ';
    const std::string    lTestString  =
        "First line.\n"
        "Second line.\n"
        "Third line.\n";
    Log::Indenter::Space lSpaceIndenter(lCount,
                                        Log::Indenter::String::Flags::kFirst);
    Log::Level           lLevel;
    std::string          lInputString;
    std::string          lExpectedResult;
    std::string          lActualResult;

    // Try the indenter at level 0

    lLevel = 0;

    lInputString    = lTestString;
    lExpectedResult = std::string(lLevel * lCount, lCharacter) + lTestString;

    lActualResult = lSpaceIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 1

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel * lCount, lCharacter) + lTestString;

    lActualResult = lSpaceIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 2

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel * lCount, lCharacter) + lTestString;

    lActualResult = lSpaceIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 3

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel * lCount, lCharacter) + lTestString;

    lActualResult = lSpaceIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 4

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel * lCount, lCharacter) + lTestString;

    lActualResult = lSpaceIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);
}

void
TestLogIndenterSpace :: TestEveryIndent(void)
{
    const size_t         lCount      = 4;
    const std::string    lTestString =
        "First line.\n"
        "Second line.\n"
        "Third line.\n";
    Log::Indenter::Space lSpaceIndenter(lCount,
                                        Log::Indenter::String::Flags::kEvery);
    Log::Level           lLevel;
    std::string          lInputString;
    std::string          lExpectedResult;
    std::string          lActualResult;

    // Try the indenter at level 0

    lLevel = 0;

    lInputString    = lTestString;
    lExpectedResult = lTestString;

    lActualResult = lSpaceIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 1

    lInputString    = lTestString;
    lExpectedResult = "    First line.\n"
                      "    Second line.\n"
                      "    Third line.\n";

    lActualResult = lSpaceIndenter.Indent(++lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 2

    lInputString    = lTestString;
    lExpectedResult = "        First line.\n"
                      "        Second line.\n"
                      "        Third line.\n";

    lActualResult = lSpaceIndenter.Indent(++lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 3

    lInputString    = lTestString;
    lExpectedResult = "            First line.\n"
                      "            Second line.\n"
                      "            Third line.\n";

    lActualResult = lSpaceIndenter.Indent(++lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 4

    lInputString    = lTestString;
    lExpectedResult = "                First line.\n"
                      "                Second line.\n"
                      "                Third line.\n";

    lActualResult = lSpaceIndenter.Indent(++lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 4, with a string containing some
    // existing ' ' and blank lines.

    lInputString    = " First line.\n"
                      "\n"
                      "  Second line.\n"
                      "\n"
                      "\n"
                      "   Third line.\n"
                      "\n";
    lExpectedResult = "                 First line.\n"
                      "                \n"
                      "                  Second line.\n"
                      "                \n"
                      "                \n"
                      "                   Third line.\n"
                      "                \n";

    lActualResult = lSpaceIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);
}

void
TestLogIndenterSpace :: CheckResults(const std::string & inExpected,
                                     const std::string & inActual)
{
    const size_t lActualSize   = inActual.size();
    const size_t lExpectedSize = inExpected.size();

    CPPUNIT_ASSERT_EQUAL(lExpectedSize, lActualSize);

    CPPUNIT_ASSERT_EQUAL(inExpected, inActual);
}
