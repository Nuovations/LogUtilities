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
 *      This file implements a unit test for Log::Filter::Never.
 */

#include <LogUtilities/LogFilterNever.hpp>

#include <limits.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogFilterNever :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogFilterNever);
    CPPUNIT_TEST(Test);
    CPPUNIT_TEST_SUITE_END();

public:
    void Test(void);

private:
    void Test(Log::Filter::Never & inFilter);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogFilterNever);

void
TestLogFilterNever :: Test(void)
{
    Log::Filter::Never lNeverFilter;

    Test(lNeverFilter);
}

void
TestLogFilterNever :: Test(Log::Filter::Never & inFilter)
{
    const bool       kAllow       = false;
    const Log::Level kLevelMin    = 0;
    const Log::Level kLevelMax    = UINT_MAX;
    const char *     kNullMessage = NULL;
    const char *     kTestMessage = "Test Message";
    bool             lAllow;

    lAllow = inFilter.Allow(kLevelMin);
    CPPUNIT_ASSERT_EQUAL(kAllow, lAllow);

    lAllow = inFilter.Allow(kLevelMax);
    CPPUNIT_ASSERT_EQUAL(kAllow, lAllow);

    lAllow = inFilter.Allow(kLevelMin, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(kAllow, lAllow);

    lAllow = inFilter.Allow(kLevelMax, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(kAllow, lAllow);

    lAllow = inFilter.Allow(kLevelMin, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(kAllow, lAllow);

    lAllow = inFilter.Allow(kLevelMax, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(kAllow, lAllow);
}
