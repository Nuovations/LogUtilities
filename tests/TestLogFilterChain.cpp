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
 *      This file implements a unit test for Log::Filter::Chain.
 */

#include <LogUtilities/LogFilterAlways.hpp>
#include <LogUtilities/LogFilterChain.hpp>
#include <LogUtilities/LogFilterLevel.hpp>
#include <LogUtilities/LogFilterNever.hpp>
#include <LogUtilities/LogFilterQuiet.hpp>

#include <stdint.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogFilterChain :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogFilterChain);
    CPPUNIT_TEST(TestDefaultConstruction);
    CPPUNIT_TEST(TestCopyConstruction);
    CPPUNIT_TEST(TestObservation);
    CPPUNIT_TEST(TestAlwaysChain);
    CPPUNIT_TEST(TestNeverChain);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestDefaultConstruction(void);
    void TestCopyConstruction(void);
    void TestObservation(void);
    void TestAlwaysChain(void);
    void TestNeverChain(void);

private:
    void TestObservation(const Log::Filter::Chain & inChain);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogFilterChain);

void
TestLogFilterChain :: TestDefaultConstruction(void)
{
    Log::Filter::Chain lFilterChain;
}

void
TestLogFilterChain :: TestCopyConstruction(void)
{
    Log::Filter::Chain lFilterChainA;
    Log::Filter::Chain lFilterChainB(lFilterChainA);
}

void
TestLogFilterChain :: TestObservation(void)
{
    Log::Filter::Chain lFilterChainA;
    Log::Filter::Chain lFilterChainB(lFilterChainA);

    TestObservation(lFilterChainA);
    TestObservation(lFilterChainB);
}

void
TestLogFilterChain :: TestObservation(const Log::Filter::Chain & inChain)
{
    size_t              lSize;
    bool                lEmpty;
    Log::Filter::Base * lLink;

    lSize = inChain.Size();
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), lSize);

    lEmpty = inChain.Empty();
    CPPUNIT_ASSERT_EQUAL(true, lEmpty);

    lLink = inChain.Link<Log::Filter::Base>(0);
    CPPUNIT_ASSERT_EQUAL(static_cast<Log::Filter::Base *>(NULL), lLink);
}

void
TestLogFilterChain :: TestAlwaysChain(void)
{
    Log::Filter::Always lAlwaysFilter;
    Log::Filter::Quiet  lQuietFilter;
    Log::Filter::Level  lLevelFilter;
    Log::Filter::Chain  lChainFilter;
    bool                lAllow;
    size_t              lSize;
    bool                lEmpty;
    Log::Filter::Base * lFilter;

    // Test pushing links onto the chain

    lChainFilter.Push(lAlwaysFilter);
    lChainFilter.Push(lQuietFilter);
    lChainFilter.Push(lLevelFilter);

    // Test size observers

    lEmpty = lChainFilter.Empty();
    CPPUNIT_ASSERT(!lEmpty);

    lSize = lChainFilter.Size();
    CPPUNIT_ASSERT(lSize == 3);

    // Test link observers

    lFilter = lChainFilter.Link<Log::Filter::Always>(0);
    CPPUNIT_ASSERT(lFilter != NULL);

    lFilter = lChainFilter.Link<Log::Filter::Quiet>(1);
    CPPUNIT_ASSERT(lFilter != NULL);

    lFilter = lChainFilter.Link<Log::Filter::Level>(2);
    CPPUNIT_ASSERT(lFilter != NULL);

    lFilter = lChainFilter.Link<Log::Filter::Base>(3);
    CPPUNIT_ASSERT(lFilter == NULL);

    // Test filter with links at their default settings

    lAllow = lChainFilter.Allow(0);
    CPPUNIT_ASSERT(lAllow == true);

    lAllow = lChainFilter.Allow(0, "At level 0, with quiet true and level 0, having an always filter in the chain will allow.\n");
    CPPUNIT_ASSERT(lAllow == true);

    lAllow = lChainFilter.Allow(1);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(1, "At level 1, with quiet true and level 0, having an always filter in the chain will not allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX, "At level UINT_MAX, with quiet true and level 0 having an always filter in the chain will not allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    // Increase the level to 1 and retest.

    lFilter = lChainFilter.Link<Log::Filter::Level>(2);
    CPPUNIT_ASSERT(lFilter != NULL);

    static_cast<Log::Filter::Level *>(lFilter)->SetLevel(1);
    CPPUNIT_ASSERT(static_cast<Log::Filter::Level *>(lFilter)->GetLevel() == 1);

    lAllow = lChainFilter.Allow(0);
    CPPUNIT_ASSERT(lAllow == true);

    lAllow = lChainFilter.Allow(0, "At level 0, with quiet true and level 1, having an always filter in the chain will allow.\n");
    CPPUNIT_ASSERT(lAllow == true);

    lAllow = lChainFilter.Allow(1);
    CPPUNIT_ASSERT(lAllow == true);

    lAllow = lChainFilter.Allow(1, "At level 1, with quiet true and level 1, having an always filter in the chain will allow.\n");
    CPPUNIT_ASSERT(lAllow == true);

    lAllow = lChainFilter.Allow(UINT_MAX);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX, "At level UINT_MAX, with quiet true and level 1, having an always filter in the chain will not allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    // Increase the level to UINT_MAX and retest.

    lFilter = lChainFilter.Link<Log::Filter::Level>(2);
    CPPUNIT_ASSERT(lFilter != NULL);

    static_cast<Log::Filter::Level *>(lFilter)->SetLevel(UINT_MAX);
    CPPUNIT_ASSERT(static_cast<Log::Filter::Level *>(lFilter)->GetLevel() == UINT_MAX);

    lAllow = lChainFilter.Allow(0);
    CPPUNIT_ASSERT(lAllow == true);

    lAllow = lChainFilter.Allow(0, "At level 0, with quiet true and level UINT_MAX, having an always filter in the chain will allow.\n");
    CPPUNIT_ASSERT(lAllow == true);

    lAllow = lChainFilter.Allow(1);
    CPPUNIT_ASSERT(lAllow == true);

    lAllow = lChainFilter.Allow(1, "At level 1, with quiet true and level UINT_MAX, having an always filter in the chain will allow.\n");
    CPPUNIT_ASSERT(lAllow == true);

    lAllow = lChainFilter.Allow(UINT_MAX);
    CPPUNIT_ASSERT(lAllow == true);

    lAllow = lChainFilter.Allow(UINT_MAX, "At level UINT_MAX, with quiet true and level UINT_MAX, having an always filter in the chain will allow.\n");
    CPPUNIT_ASSERT(lAllow == true);

    // Set quiet to true and retest

    lFilter = lChainFilter.Link<Log::Filter::Quiet>(1);
    CPPUNIT_ASSERT(lFilter != NULL);

    static_cast<Log::Filter::Quiet *>(lFilter)->SetQuiet(true);
    CPPUNIT_ASSERT(static_cast<Log::Filter::Quiet *>(lFilter)->GetQuiet() == true);

    lAllow = lChainFilter.Allow(0);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(0, "At level 0, with quiet false and level UINT_MAX, having an always filter in the chain will not allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(1);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(1, "At level 1, with quiet false and level UINT_MAX, having an always filter in the chain will not allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX, "At level UINT_MAX, with quiet false and level UINT_MAX, having an always filter in the chain will not allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    // Test popping links off the chain

    lChainFilter.Pop();

    lEmpty = lChainFilter.Empty();
    CPPUNIT_ASSERT(!lEmpty);

    lSize = lChainFilter.Size();
    CPPUNIT_ASSERT(lSize == 2);

    lChainFilter.Pop();

    lEmpty = lChainFilter.Empty();
    CPPUNIT_ASSERT(!lEmpty);

    lSize = lChainFilter.Size();
    CPPUNIT_ASSERT(lSize == 1);

    lChainFilter.Pop();

    TestObservation(lChainFilter);

    // Retest with an empty chain.

    lAllow = lChainFilter.Allow(0);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(0, "At level 0, when empty, the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(1);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(1, "At level 1, when empty, the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX, "At level UINT_MAX, when empty, the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);
}

void
TestLogFilterChain :: TestNeverChain(void)
{
    Log::Filter::Never  lNeverFilter;
    Log::Filter::Quiet  lQuietFilter;
    Log::Filter::Level  lLevelFilter;
    Log::Filter::Chain  lChainFilter;
    bool                lAllow;
    size_t              lSize;
    bool                lEmpty;
    Log::Filter::Base * lFilter;

    // Test pushing links onto the chain

    lChainFilter.Push(lNeverFilter);
    lChainFilter.Push(lQuietFilter);
    lChainFilter.Push(lLevelFilter);

    // Test size observers

    lEmpty = lChainFilter.Empty();
    CPPUNIT_ASSERT(!lEmpty);

    lSize = lChainFilter.Size();
    CPPUNIT_ASSERT(lSize == 3);

    // Test link observers

    lFilter = lChainFilter.Link<Log::Filter::Never>(0);
    CPPUNIT_ASSERT(lFilter != NULL);

    lFilter = lChainFilter.Link<Log::Filter::Quiet>(1);
    CPPUNIT_ASSERT(lFilter != NULL);

    lFilter = lChainFilter.Link<Log::Filter::Level>(2);
    CPPUNIT_ASSERT(lFilter != NULL);

    lFilter = lChainFilter.Link<Log::Filter::Base>(3);
    CPPUNIT_ASSERT(lFilter == NULL);

    lAllow = lChainFilter.Allow(0);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(0, "At level 0, having a never filter in the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(1);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(1, "At level 1, having a never filter in the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX, "At level UINT_MAX, having a never filter in the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lFilter = lChainFilter.Link<Log::Filter::Quiet>(1);
    CPPUNIT_ASSERT(lFilter != NULL);

    static_cast<Log::Filter::Quiet *>(lFilter)->SetQuiet(true);
    CPPUNIT_ASSERT(static_cast<Log::Filter::Quiet *>(lFilter)->GetQuiet() == true);

    lAllow = lChainFilter.Allow(0);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(0, "At level 0 with quiet enabled, having a never filter in the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(1);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(1, "At level 1 with quiet enabled, having a never filter in the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX, "At level UINT_MAX with quiet enabled, having a never filter in the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    // Test popping links off the chain

    lChainFilter.Pop();

    lEmpty = lChainFilter.Empty();
    CPPUNIT_ASSERT(!lEmpty);

    lSize = lChainFilter.Size();
    CPPUNIT_ASSERT(lSize == 2);

    lChainFilter.Pop();

    lEmpty = lChainFilter.Empty();
    CPPUNIT_ASSERT(!lEmpty);

    lSize = lChainFilter.Size();
    CPPUNIT_ASSERT(lSize == 1);

    lChainFilter.Pop();

    TestObservation(lChainFilter);

    // Retest with an empty chain.

    lAllow = lChainFilter.Allow(0);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(0, "At level 0, when empty the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(1);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(1, "At level 1, when empty the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX);
    CPPUNIT_ASSERT(lAllow == false);

    lAllow = lChainFilter.Allow(UINT_MAX, "At level UINT_MAX, when empty the chain will never allow.\n");
    CPPUNIT_ASSERT(lAllow == false);
}
