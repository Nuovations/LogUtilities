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
 *      This file implements a unit tests for the LogDebug(),
 *      LogInfo(), and LogError() preprocessor wrapper macros.
 */

#include <LogUtilities/LogMacros.hpp>

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogMacros :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogMacros);
    CPPUNIT_TEST(Test);
    CPPUNIT_TEST_SUITE_END();

public:
    void Test(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogMacros);

void
TestLogMacros :: Test(void)
{
    const Log::Indent lIndent = 0;
    const Log::Level  lLevel  = 0;

    LogDebug(lIndent, lLevel, "Test debug macro %d\n", 1);
    LogInfo(lIndent, lLevel, "Test info macro %d\n", 2);
    LogError(lIndent, lLevel, "Test error macro %d\n", 3);
}
