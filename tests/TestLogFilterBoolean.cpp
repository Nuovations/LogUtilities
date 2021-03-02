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
 *      This file implements a unit test for Log::Filter::Boolean.
 */

#include <LogUtilities/LogFilterBoolean.hpp>

#include <limits.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class BooleanFilterWrapper :
    public Log::Filter::Boolean
{
public:
    BooleanFilterWrapper(bool inAllow);
};

class TestLogFilterBoolean :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogFilterBoolean);
    CPPUNIT_TEST(Test);
    CPPUNIT_TEST_SUITE_END();

public:
    void Test(void);

private:
    void Test(BooleanFilterWrapper & inFilter, bool inExpected);
};

BooleanFilterWrapper :: BooleanFilterWrapper(bool inAllow) :
    Boolean(inAllow)
{
    return;
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogFilterBoolean);

void
TestLogFilterBoolean :: Test(void)
{
    const bool           kAllow = true;
    BooleanFilterWrapper lTrueFilter(kAllow);
    BooleanFilterWrapper lFalseFilter(!kAllow);

    Test(lTrueFilter,   kAllow);
    Test(lFalseFilter, !kAllow);
}

void
TestLogFilterBoolean :: Test(BooleanFilterWrapper & inFilter, bool inExpected)
{
    const Log::Level kLevelMin    = 0;
    const Log::Level kLevelMax    = UINT_MAX;
    const char *     kNullMessage = NULL;
    const char *     kTestMessage = "Test Message";
    bool             lAllow;

    lAllow = inFilter.Allow(kLevelMin);
    CPPUNIT_ASSERT_EQUAL(inExpected, lAllow);

    lAllow = inFilter.Allow(kLevelMax);
    CPPUNIT_ASSERT_EQUAL(inExpected, lAllow);

    lAllow = inFilter.Allow(kLevelMin, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(inExpected, lAllow);

    lAllow = inFilter.Allow(kLevelMax, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(inExpected, lAllow);

    lAllow = inFilter.Allow(kLevelMin, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(inExpected, lAllow);

    lAllow = inFilter.Allow(kLevelMax, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(inExpected, lAllow);
}
