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
 *      This file implements a unit test for Log::Indenter::String.
 */

#include <LogUtilities/LogIndenterString.hpp>

#include <string>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogIndenterString :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogIndenterString);
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

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogIndenterString);

void
TestLogIndenterString :: TestConstruction(void)
{
    const char *          kSpaceCString = " ";
    const char            kSpaceChar    = ' ';
    const size_t          kCount        = 1;
    const std::string     kSpaceCxxString(kSpaceCString);
    Log::Indenter::String lCString(kSpaceCString);
    Log::Indenter::String lCxxString(kSpaceCxxString);
    Log::Indenter::String lChar(kSpaceChar);
    Log::Indenter::String lCharWithCOunt(kSpaceChar, kCount);
    Log::Indenter::String lCStringWithFirstFlag(kSpaceCString, Log::Indenter::String::Flags::kFirst);
    Log::Indenter::String lCStringWithEveryFlag(kSpaceCString, Log::Indenter::String::Flags::kEvery);
    Log::Indenter::String lCxxStringWithFirstFlag(kSpaceCxxString, Log::Indenter::String::Flags::kFirst);
    Log::Indenter::String lCxxStringWithEveryFlag(kSpaceCxxString, Log::Indenter::String::Flags::kEvery);
    Log::Indenter::String lCharWithFirstFlag(kSpaceChar, Log::Indenter::String::Flags::kFirst);
    Log::Indenter::String lCharWithEveryFlag(kSpaceChar, Log::Indenter::String::Flags::kEvery);
    Log::Indenter::String lCharWithCountWithFirstFlag(kSpaceChar, kCount, Log::Indenter::String::Flags::kFirst);
    Log::Indenter::String lCharWithCountWithEveryFlag(kSpaceChar, kCount, Log::Indenter::String::Flags::kEvery);
}

void
TestLogIndenterString :: TestFirstIndent(void)
{
    const size_t          lCount      = 1;
    const char            lCharacter  = '.';
    const std::string     lTestString =
        "First line.\n"
        "Second line.\n"
        "Third line.\n";
    Log::Indenter::String lStringIndenter(lCharacter,
                                          lCount,
                                          Log::Indenter::String::Flags::kFirst);
    Log::Level            lLevel;
    std::string           lInputString;
    std::string           lExpectedResult;
    std::string           lActualResult;

    // Try the indenter at level 0

    lLevel = 0;

    lInputString    = lTestString;
    lExpectedResult = std::string(lLevel, lCharacter) + lTestString;

    lActualResult = lStringIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 1

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel, lCharacter) + lTestString;

    lActualResult = lStringIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 2

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel, lCharacter) + lTestString;

    lActualResult = lStringIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 3

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel, lCharacter) + lTestString;

    lActualResult = lStringIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 4

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel, lCharacter) + lTestString;

    lActualResult = lStringIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);
}

void
TestLogIndenterString ::TestEveryIndent(void)
{
    const size_t          lCount      = 1;
    const char            lCharacter  = '.';
    const std::string     lTestString =
        "First line.\n"
        "Second line.\n"
        "Third line.\n";
    Log::Indenter::String lStringIndenter(lCharacter,
                                          lCount,
                                          Log::Indenter::String::Flags::kEvery);
    Log::Level            lLevel;
    std::string           lInputString;
    std::string           lExpectedResult;
    std::string           lActualResult;

    // Try the indenter at level 0

    lLevel = 0;

    lInputString    = lTestString;
    lExpectedResult = lTestString;

    lActualResult = lStringIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 1

    lInputString    = lTestString;
    lExpectedResult = ".First line.\n"
                      ".Second line.\n"
                      ".Third line.\n";

    lActualResult = lStringIndenter.Indent(++lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 2

    lInputString    = lTestString;
    lExpectedResult = "..First line.\n"
                      "..Second line.\n"
                      "..Third line.\n";

    lActualResult = lStringIndenter.Indent(++lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 3

    lInputString    = lTestString;
    lExpectedResult = "...First line.\n"
                      "...Second line.\n"
                      "...Third line.\n";

    lActualResult = lStringIndenter.Indent(++lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 4

    lInputString    = lTestString;
    lExpectedResult = "....First line.\n"
                      "....Second line.\n"
                      "....Third line.\n";

    lActualResult = lStringIndenter.Indent(++lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 4, with a string containing some
    // existing '.' and blank lines.

    lInputString    = ".First line.\n"
                      "\n"
                      "..Second line.\n"
                      "\n"
                      "\n"
                      "...Third line.\n"
                      "\n";
    lExpectedResult = ".....First line.\n"
                      "....\n"
                      "......Second line.\n"
                      "....\n"
                      "....\n"
                      ".......Third line.\n"
                      "....\n";

    lActualResult = lStringIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);
}

void
TestLogIndenterString :: CheckResults(const std::string & inExpected,
                                      const std::string & inActual)
{
    const size_t lActualSize   = inActual.size();
    const size_t lExpectedSize = inExpected.size();

    CPPUNIT_ASSERT_EQUAL(lExpectedSize, lActualSize);

    CPPUNIT_ASSERT_EQUAL(inExpected, inActual);
}
