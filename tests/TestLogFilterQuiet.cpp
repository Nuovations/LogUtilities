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
 *      This file implements a unit test for Log::Filter::Quiet.
 */

#include <LogUtilities/LogFilterQuiet.hpp>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogFilterQuiet :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogFilterQuiet);
    CPPUNIT_TEST(TestDefaultConstruction);
    CPPUNIT_TEST(TestExplicitConstruction);
    CPPUNIT_TEST(TestObservation);
    CPPUNIT_TEST(TestMutation);
    CPPUNIT_TEST(TestAllow);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestDefaultConstruction(void);
    void TestExplicitConstruction(void);
    void TestObservation(void);
    void TestMutation(void);
    void TestAllow(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogFilterQuiet);

void
TestLogFilterQuiet :: TestDefaultConstruction(void)
{
    Log::Filter::Quiet lQuietDefaultFilter;
}

void
TestLogFilterQuiet :: TestExplicitConstruction(void)
{
    const bool         kQuiet = true;
    Log::Filter::Quiet lQuietTrueFilter(kQuiet);
    Log::Filter::Quiet lQuietFalseFilter(!kQuiet);
}

void
TestLogFilterQuiet :: TestObservation(void)
{
    const bool         kQuiet = true;
    Log::Filter::Quiet lQuietDefaultFilter;
    Log::Filter::Quiet lQuietTrueFilter(kQuiet);
    Log::Filter::Quiet lQuietFalseFilter(!kQuiet);
    bool               lQuiet;

    lQuiet = lQuietDefaultFilter.GetQuiet();
    CPPUNIT_ASSERT_EQUAL(!kQuiet, lQuiet);

    lQuiet = lQuietTrueFilter.GetQuiet();
    CPPUNIT_ASSERT_EQUAL(kQuiet, lQuiet);

    lQuiet = lQuietFalseFilter.GetQuiet();
    CPPUNIT_ASSERT_EQUAL(!kQuiet, lQuiet);
}

void
TestLogFilterQuiet :: TestMutation(void)
{
    const bool         kQuiet = true;
    Log::Filter::Quiet lQuietDefaultFilter;
    Log::Filter::Quiet lQuietTrueFilter(kQuiet);
    Log::Filter::Quiet lQuietFalseFilter(!kQuiet);
    bool               lQuiet;

    lQuietDefaultFilter.SetQuiet(!kQuiet);
    lQuiet = lQuietDefaultFilter.GetQuiet();
    CPPUNIT_ASSERT_EQUAL(!kQuiet, lQuiet);

    lQuietTrueFilter.SetQuiet(!kQuiet);
    lQuiet = lQuietTrueFilter.GetQuiet();
    CPPUNIT_ASSERT_EQUAL(!kQuiet, lQuiet);

    lQuietFalseFilter.SetQuiet(kQuiet);
    lQuiet = lQuietFalseFilter.GetQuiet();
    CPPUNIT_ASSERT_EQUAL(kQuiet, lQuiet);
}

void
TestLogFilterQuiet :: TestAllow(void)
{
    const bool         kQuiet       = true;
    const Log::Level   kLevelMin    = 0;
    const Log::Level   kLevelMax    = UINT_MAX;
    const char *       kNullMessage = NULL;
    const char *       kTestMessage = "Test Message";
    bool               lAllow;
    Log::Filter::Quiet lQuietDefaultFilter;
    Log::Filter::Quiet lQuietTrueFilter(kQuiet);
    Log::Filter::Quiet lQuietFalseFilter(!kQuiet);

    // Default construction (quiet deasserted)

    lAllow = lQuietDefaultFilter.Allow(kLevelMin);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lQuietDefaultFilter.Allow(kLevelMax);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lQuietDefaultFilter.Allow(kLevelMin, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lQuietDefaultFilter.Allow(kLevelMax, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lQuietDefaultFilter.Allow(kLevelMin, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lQuietDefaultFilter.Allow(kLevelMax, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    // Explicit construction with quiet asserted

    lAllow = lQuietTrueFilter.Allow(kLevelMin);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    lAllow = lQuietTrueFilter.Allow(kLevelMax);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    lAllow = lQuietTrueFilter.Allow(kLevelMin, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    lAllow = lQuietTrueFilter.Allow(kLevelMax, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    lAllow = lQuietTrueFilter.Allow(kLevelMin, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    lAllow = lQuietTrueFilter.Allow(kLevelMax, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    // Explicit construction with quiet deasserted

    lAllow = lQuietFalseFilter.Allow(kLevelMin);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lQuietFalseFilter.Allow(kLevelMax);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lQuietFalseFilter.Allow(kLevelMin, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lQuietFalseFilter.Allow(kLevelMax, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lQuietFalseFilter.Allow(kLevelMin, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lQuietFalseFilter.Allow(kLevelMax, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);
}
