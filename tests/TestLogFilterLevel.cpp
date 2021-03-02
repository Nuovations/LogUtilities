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
 *      This file implements a unit test for Log::Filter::Level.
 */

#include <LogUtilities/LogFilterLevel.hpp>

#include <limits.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogFilterLevel :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogFilterLevel);
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

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogFilterLevel);

void
TestLogFilterLevel :: TestDefaultConstruction(void)
{
    Log::Filter::Level lLevelDefaultFilter;
}

void
TestLogFilterLevel :: TestExplicitConstruction(void)
{
    const Log::Level   kLevelMin = 0;
    const Log::Level   kLevelMax = UINT_MAX;
    Log::Filter::Level lLevelMinFilter(kLevelMin);
    Log::Filter::Level lLevelMaxFilter(kLevelMax);
}

void
TestLogFilterLevel :: TestObservation(void)
{
    const Log::Level   kLevelMin = 0;
    const Log::Level   kLevelMax = UINT_MAX;
    Log::Filter::Level lLevelDefaultFilter;
    Log::Filter::Level lLevelMinFilter(kLevelMin);
    Log::Filter::Level lLevelMaxFilter(kLevelMax);
    Log::Level         lLevel;

    lLevel = lLevelDefaultFilter.GetLevel();
    CPPUNIT_ASSERT_EQUAL(kLevelMin, lLevel);

    lLevel = lLevelMinFilter.GetLevel();
    CPPUNIT_ASSERT_EQUAL(kLevelMin, lLevel);

    lLevel = lLevelMaxFilter.GetLevel();
    CPPUNIT_ASSERT_EQUAL(kLevelMax, lLevel);
}

void
TestLogFilterLevel :: TestMutation(void)
{
    const Log::Level   kLevelMin = 0;
    const Log::Level   kLevelMax = UINT_MAX;
    Log::Filter::Level lLevelDefaultFilter;
    Log::Filter::Level lLevelMinFilter(kLevelMin);
    Log::Filter::Level lLevelMaxFilter(kLevelMax);
    Log::Level         lLevel;

    lLevelDefaultFilter.SetLevel(kLevelMin + 1);
    lLevel = lLevelDefaultFilter.GetLevel();
    CPPUNIT_ASSERT_EQUAL(kLevelMin + 1, lLevel);

    lLevelMinFilter.SetLevel(kLevelMin + 2);
    lLevel = lLevelMinFilter.GetLevel();
    CPPUNIT_ASSERT_EQUAL(kLevelMin + 2, lLevel);

    lLevelMaxFilter.SetLevel(kLevelMax - 1);
    lLevel = lLevelMaxFilter.GetLevel();
    CPPUNIT_ASSERT_EQUAL(kLevelMax - 1, lLevel);
}

void
TestLogFilterLevel :: TestAllow(void)
{
    const Log::Level   kLevelMin    = 0;
    const Log::Level   kLevelMax    = UINT_MAX;
    const char *       kNullMessage = NULL;
    const char *       kTestMessage = "Test Message";
    bool               lAllow;
    Log::Filter::Level lLevelDefaultFilter;
    Log::Filter::Level lLevelMinFilter(kLevelMin);
    Log::Filter::Level lLevelMaxFilter(kLevelMax);

    // Default construction

    lAllow = lLevelDefaultFilter.Allow(kLevelMin);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lLevelDefaultFilter.Allow(kLevelMax);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    lAllow = lLevelDefaultFilter.Allow(kLevelMin, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lLevelDefaultFilter.Allow(kLevelMax, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    lAllow = lLevelDefaultFilter.Allow(kLevelMin, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lLevelDefaultFilter.Allow(kLevelMax, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    // Explicit construction with a minimum level

    lAllow = lLevelMinFilter.Allow(kLevelMin);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lLevelMinFilter.Allow(kLevelMax);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    lAllow = lLevelMinFilter.Allow(kLevelMin, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lLevelMinFilter.Allow(kLevelMax, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    lAllow = lLevelMinFilter.Allow(kLevelMin, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lLevelMinFilter.Allow(kLevelMax, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(false, lAllow);

    // Explicit construction with a maximum level

    lAllow = lLevelMaxFilter.Allow(kLevelMin);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lLevelMaxFilter.Allow(kLevelMax);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lLevelMaxFilter.Allow(kLevelMin, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lLevelMaxFilter.Allow(kLevelMax, kNullMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lLevelMaxFilter.Allow(kLevelMin, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);

    lAllow = lLevelMaxFilter.Allow(kLevelMax, kTestMessage);
    CPPUNIT_ASSERT_EQUAL(true, lAllow);
}
