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
 *      This file implements a unit tests for Log::Debug(),
 *      Log::Info(), and Log::Error() global singleton instances.
 */

#include <LogUtilities/LogGlobals.hpp>

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogGlobals :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogGlobals);
    CPPUNIT_TEST(Test);
    CPPUNIT_TEST_SUITE_END();

public:
    void Test(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogGlobals);

void
TestLogGlobals :: Test(void)
{
    Log::Indent lIndent = 0;
    Log::Level  lActualLevel;
    Log::Level  lLevel  = 0;
    bool        lActualQuiet;
    bool        lStatus;

    // Log some messages at the default settings.

    Log::Debug().Write(lIndent, lLevel, "Test debug global %d\n", 1);
    Log::Info().Write(lIndent, lLevel, "Test info global %d\n", 2);
    Log::Error().Write(lIndent, lLevel, "Test error global %d\n", 3);

    // Increase the filter level through the convenience interface

    lStatus = SetFilter(Log::Debug(), lLevel + 1, false);
    CPPUNIT_ASSERT(lStatus == true);

    lStatus = GetFilter(Log::Debug(), lActualLevel, lActualQuiet);
    CPPUNIT_ASSERT(lStatus == true);
    CPPUNIT_ASSERT(lLevel + 1 == lActualLevel);
    CPPUNIT_ASSERT(false == lActualQuiet);

    lStatus = SetFilter(Log::Info(), lLevel + 1, false);
    CPPUNIT_ASSERT(lStatus == true);

    lStatus = GetFilter(Log::Info(), lActualLevel, lActualQuiet);
    CPPUNIT_ASSERT(lStatus == true);
    CPPUNIT_ASSERT(lLevel + 1 == lActualLevel);
    CPPUNIT_ASSERT(false == lActualQuiet);

    lStatus = SetFilter(Log::Error(), lLevel + 1, false);
    CPPUNIT_ASSERT(lStatus == false);

    lStatus = GetFilter(Log::Error(), lActualLevel, lActualQuiet);
    CPPUNIT_ASSERT(lStatus == false);

    // Log some more messages at the new level.

    Log::Debug().Write(lIndent, lLevel + 1, "Test debug global %d\n", 4);
    Log::Info().Write(lIndent, lLevel + 1, "Test info global %d\n", 5);
    Log::Error().Write(lIndent, lLevel + 1, "Test error global %d\n", 6);

    // Set the filter as quiet

    lStatus = SetFilter(Log::Debug(), lLevel, true);
    CPPUNIT_ASSERT(lStatus == true);

    lStatus = GetFilter(Log::Debug(), lActualLevel, lActualQuiet);
    CPPUNIT_ASSERT(lStatus == true);
    CPPUNIT_ASSERT(lLevel == lActualLevel);
    CPPUNIT_ASSERT(true == lActualQuiet);

    lStatus = SetFilter(Log::Info(), lLevel, true);
    CPPUNIT_ASSERT(lStatus == true);

    lStatus = GetFilter(Log::Info(), lActualLevel, lActualQuiet);
    CPPUNIT_ASSERT(lStatus == true);
    CPPUNIT_ASSERT(lLevel == lActualLevel);
    CPPUNIT_ASSERT(true == lActualQuiet);

    lStatus = SetFilter(Log::Error(), lLevel, true);
    CPPUNIT_ASSERT(lStatus == false);

    lStatus = GetFilter(Log::Error(), lActualLevel, lActualQuiet);
    CPPUNIT_ASSERT(lStatus == false);

    // Log some more messages, all but the error log should be suppressed.

    Log::Debug().Write(lIndent, lLevel, "Test debug global %d\n", 7);
    Log::Info().Write(lIndent, lLevel, "Test info global %d\n", 8);
    Log::Error().Write(lIndent, lLevel, "Test error global %d\n", 9);

    // Set the filter as verbose

    lStatus = SetFilter(Log::Debug(), lLevel, false);
    CPPUNIT_ASSERT(lStatus == true);

    lStatus = SetFilter(Log::Info(), lLevel, false);
    CPPUNIT_ASSERT(lStatus == true);

    lStatus = SetFilter(Log::Error(), lLevel, false);
    CPPUNIT_ASSERT(lStatus == false);

    Log::Debug().Write(lIndent, lLevel, "Test debug global %d\n", 10);
    Log::Info().Write(lIndent, lLevel, "Test info global %d\n", 11);
    Log::Error().Write(lIndent, lLevel, "Test error global %d\n", 12);
}
