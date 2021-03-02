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
 *      This file implements a unit test for Log::Writer::Syslog
 */

#include <LogUtilities/LogWriterSyslog.hpp>

#include <string>

#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;


class TestLogWriterSyslog :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogWriterSyslog);
    CPPUNIT_TEST(TestConstruction);
    CPPUNIT_TEST(TestObservation);
    CPPUNIT_TEST(TestMutation);
    CPPUNIT_TEST(TestSyslogWriter);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestConstruction(void);
    void TestObservation(void);
    void TestMutation(void);
    void TestSyslogWriter(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogWriterSyslog);

void
TestLogWriterSyslog :: TestConstruction(void)
{
    Log::Writer::Syslog lSyslogWriter(LOG_DEBUG);
}

void
TestLogWriterSyslog :: TestObservation(void)
{
    const int           kExpectedPriority = LOG_DEBUG;
    Log::Writer::Syslog lSyslogWriter(kExpectedPriority);
    int                 lActualPriority;

    lActualPriority = lSyslogWriter.GetPriority();
    CPPUNIT_ASSERT_EQUAL(kExpectedPriority, lActualPriority);
}

void
TestLogWriterSyslog :: TestMutation(void)
{
    int                 lSetPriority = LOG_DEBUG;
    Log::Writer::Syslog lSyslogWriter(lSetPriority);
    int                 lActualPriority;

    lActualPriority = lSyslogWriter.GetPriority();
    CPPUNIT_ASSERT_EQUAL(lSetPriority, lActualPriority);

    lSetPriority = LOG_INFO;
    lSyslogWriter.SetPriority(lSetPriority);

    lActualPriority = lSyslogWriter.GetPriority();
    CPPUNIT_ASSERT_EQUAL(lSetPriority, lActualPriority);
}

void
TestLogWriterSyslog :: TestSyslogWriter(void)
{
    const int           kExpectedPriority = LOG_DEBUG;
    Log::Writer::Syslog lSyslogWriter(kExpectedPriority);

    lSyslogWriter.Write(NULL);
    lSyslogWriter.Write(0, NULL);
    lSyslogWriter.Write(UINT_MAX, NULL);

    lSyslogWriter.Write("");
    lSyslogWriter.Write(0, "");
    lSyslogWriter.Write(UINT_MAX, "");

    lSyslogWriter.Write("Syslog writer w/o level.\n");
    lSyslogWriter.Write(0, "Syslog writer w/ level 0.\n");
    lSyslogWriter.Write(UINT_MAX, "Syslog writer w/ level UINT_MAX.\n");
}
