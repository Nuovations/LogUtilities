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
 *      This file implements a unit test for Log::Indenter::Tab.
 */

#include <LogUtilities/LogIndenterTab.hpp>

#include <string>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogIndenterTab :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogIndenterTab);
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

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogIndenterTab);

void
TestLogIndenterTab :: TestConstruction(void)
{
    Log::Indenter::Tab lTab;
    Log::Indenter::Tab lTabWithFirstFlag(Log::Indenter::Tab::Flags::kFirst);
    Log::Indenter::Tab lTabWithEveryFlag(Log::Indenter::Tab::Flags::kEvery);
}

void
TestLogIndenterTab :: TestFirstIndent(void)
{
    const size_t          lCount      = 1;
    const char            lCharacter  = '\t';
    const std::string     lTestString =
        "First line.\n"
        "Second line.\n"
        "Third line.\n";
    Log::Indenter::Tab    lTabIndenter(Log::Indenter::Tab::Flags::kFirst);
    Log::Level            lLevel;
    std::string           lInputString;
    std::string           lExpectedResult;
    std::string           lActualResult;

    // Try the indenter at level 0

    lLevel = 0;

    lInputString    = lTestString;
    lExpectedResult = std::string(lLevel * lCount, lCharacter) + lTestString;

    lActualResult = lTabIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 1

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel * lCount, lCharacter) + lTestString;

    lActualResult = lTabIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 2

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel * lCount, lCharacter) + lTestString;

    lActualResult = lTabIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 3

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel * lCount, lCharacter) + lTestString;

    lActualResult = lTabIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 4

    lInputString    = lTestString;
    lExpectedResult = std::string(++lLevel * lCount, lCharacter) + lTestString;

    lActualResult = lTabIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);
}

void
TestLogIndenterTab :: TestEveryIndent(void)
{
    const std::string     lTestString =
        "First line.\n"
        "Second line.\n"
        "Third line.\n";
    Log::Indenter::Tab    lTabIndenter(Log::Indenter::Tab::Flags::kEvery);
    Log::Level            lLevel;
    std::string           lInputString;
    std::string           lExpectedResult;
    std::string           lActualResult;

    // Try the indenter at level 0

    lLevel = 0;

    lInputString    = lTestString;
    lExpectedResult = lTestString;

    lActualResult = lTabIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 1

    lInputString    = lTestString;
    lExpectedResult = "\tFirst line.\n"
                      "\tSecond line.\n"
                      "\tThird line.\n";

    lActualResult = lTabIndenter.Indent(++lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 2

    lInputString    = lTestString;
    lExpectedResult = "\t\tFirst line.\n"
                      "\t\tSecond line.\n"
                      "\t\tThird line.\n";

    lActualResult = lTabIndenter.Indent(++lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 3

    lInputString    = lTestString;
    lExpectedResult = "\t\t\tFirst line.\n"
                      "\t\t\tSecond line.\n"
                      "\t\t\tThird line.\n";

    lActualResult = lTabIndenter.Indent(++lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);

    // Try the indenter at level 4

    lInputString    = lTestString;
    lExpectedResult = "\t\t\t\tFirst line.\n"
                      "\t\t\t\tSecond line.\n"
                      "\t\t\t\tThird line.\n";

    lActualResult = lTabIndenter.Indent(++lLevel, lInputString);

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
    lExpectedResult = "\t\t\t\t First line.\n"
                      "\t\t\t\t\n"
                      "\t\t\t\t  Second line.\n"
                      "\t\t\t\t\n"
                      "\t\t\t\t\n"
                      "\t\t\t\t   Third line.\n"
                      "\t\t\t\t\n";

    lActualResult = lTabIndenter.Indent(lLevel, lInputString);

    CheckResults(lExpectedResult, lActualResult);
}

void
TestLogIndenterTab :: CheckResults(const std::string & inExpected,
                                   const std::string & inActual)
{
    const size_t lActualSize   = inActual.size();
    const size_t lExpectedSize = inExpected.size();

    CPPUNIT_ASSERT_EQUAL(lExpectedSize, lActualSize);

    CPPUNIT_ASSERT_EQUAL(inExpected, inActual);
}
