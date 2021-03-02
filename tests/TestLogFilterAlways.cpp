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
 *      This file implements a unit test for Log::Filter::Always.
 */

#include <LogUtilities/LogFilterAlways.hpp>

#include <limits.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogFilterAlways :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogFilterAlways);
    CPPUNIT_TEST(Test);
    CPPUNIT_TEST_SUITE_END();

public:
    void Test(void);

private:
    void Test(Log::Filter::Always & inFilter);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogFilterAlways);

void
TestLogFilterAlways :: Test(void)
{
    Log::Filter::Always lAlwaysFilter;

    Test(lAlwaysFilter);
}

void
TestLogFilterAlways :: Test(Log::Filter::Always & inFilter)
{
    const bool       kAllow       = true;
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
