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
 *      This file implements a unit test for Log::Writer::Path
 */

#include <LogUtilities/LogWriterPath.hpp>

#include <string>

#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestLogUtilitiesBasis.hpp"


using namespace Nuovations;


class TestLogWriterPath :
    public TestLogUtilitiesBasis
{
    CPPUNIT_TEST_SUITE(TestLogWriterPath);
    CPPUNIT_TEST(TestConstruction);
    CPPUNIT_TEST(TestPathWriter);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestConstruction(void);
    void TestPathWriter(void);

    void setUp(void);

private:
    int  CreateTemporaryFile(char * aPathBuffer);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogWriterPath);

void
TestLogWriterPath :: setUp(void)
{
    const mode_t kModeMask = 0;

    // Ensure that there is no user-imposed umask that prevents the
    // mode check from working as expected.

    umask(kModeMask);
}

void
TestLogWriterPath :: TestConstruction(void)
{
    char        lPathBuffer[PATH_MAX];
    int         lStatus;
    int         lDescriptor;
    struct stat lStats;

    // Test default construction

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    close(lDescriptor);

    lStatus = unlink(lPathBuffer);
    CPPUNIT_ASSERT(lStatus == 0);

    {
        Log::Writer::Path lPathWriter(lPathBuffer);

        lStatus = stat(lPathBuffer, &lStats);
        CPPUNIT_ASSERT(lStatus == 0);

        lStatus = unlink(lPathBuffer);
        CPPUNIT_ASSERT(lStatus == 0);
    }

    // Test construction with RW by user mode.

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    close(lDescriptor);

    lStatus = unlink(lPathBuffer);
    CPPUNIT_ASSERT(lStatus == 0);

    {
        const mode_t      kExpectedMode = ((S_IRUSR | S_IWUSR));
        Log::Writer::Path lPathWriter(lPathBuffer, kExpectedMode);
        mode_t            lActualMode;

        lStatus = stat(lPathBuffer, &lStats);
        CPPUNIT_ASSERT(lStatus == 0);

        lActualMode = static_cast<mode_t>(lStats.st_mode & ACCESSPERMS);

        CPPUNIT_ASSERT_EQUAL(kExpectedMode, lActualMode);

        lStatus = unlink(lPathBuffer);
        CPPUNIT_ASSERT(lStatus == 0);
    }

    // Test construction with RW by user and group mode.

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    close(lDescriptor);

    lStatus = unlink(lPathBuffer);
    CPPUNIT_ASSERT(lStatus == 0);

    {
        const mode_t      kExpectedMode = ((S_IRUSR | S_IWUSR) |
                                           (S_IRGRP | S_IWGRP));
        Log::Writer::Path lPathWriter(lPathBuffer, kExpectedMode);
        mode_t            lActualMode;

        lStatus = stat(lPathBuffer, &lStats);
        CPPUNIT_ASSERT(lStatus == 0);

        lActualMode = static_cast<mode_t>(lStats.st_mode & ACCESSPERMS);

        CPPUNIT_ASSERT_EQUAL(kExpectedMode, lActualMode);

        lStatus = unlink(lPathBuffer);
        CPPUNIT_ASSERT(lStatus == 0);
    }

    // Test construction with RW by user, group, and others mode.

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    close(lDescriptor);

    lStatus = unlink(lPathBuffer);
    CPPUNIT_ASSERT(lStatus == 0);

    {
        const mode_t      kExpectedMode = ((S_IRUSR | S_IWUSR) |
                                           (S_IRGRP | S_IWGRP) |
                                           (S_IROTH | S_IWOTH));
        Log::Writer::Path lPathWriter(lPathBuffer, kExpectedMode);
        mode_t            lActualMode;

        lStatus = stat(lPathBuffer, &lStats);
        CPPUNIT_ASSERT(lStatus == 0);

        lActualMode = static_cast<mode_t>(lStats.st_mode & ACCESSPERMS);

        CPPUNIT_ASSERT_EQUAL(kExpectedMode, lActualMode);

        lStatus = unlink(lPathBuffer);
        CPPUNIT_ASSERT(lStatus == 0);
    }
}

void
TestLogWriterPath :: TestPathWriter(void)
{
    const std::string kExpected =
        "(null)(null)(null)Path w/o level.\n"
        "Path w/ level 0.\n"
        "Path w/ level UINT_MAX.\n";
    char              lPathBuffer[PATH_MAX];
    int               lDescriptor;
    int               lStatus;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    close(lDescriptor);

    lStatus = unlink(lPathBuffer);
    CPPUNIT_ASSERT(lStatus == 0);

    {
        Log::Writer::Path lPathWriter(lPathBuffer);

        lPathWriter.Write(NULL);
        lPathWriter.Write(0, NULL);
        lPathWriter.Write(UINT_MAX, NULL);

        lPathWriter.Write("");
        lPathWriter.Write(0, "");
        lPathWriter.Write(UINT_MAX, "");

        lPathWriter.Write("Path w/o level.\n");
        lPathWriter.Write(0, "Path w/ level 0.\n");
        lPathWriter.Write(UINT_MAX, "Path w/ level UINT_MAX.\n");
    }

    CheckResults(lPathBuffer, kExpected);
}

int
TestLogWriterPath :: CreateTemporaryFile(char * aPathBuffer)
{
    static const char * const kTestName = "writer-path";
    int                       lStatus;

    lStatus = CreateTemporaryFileFromName(kTestName, aPathBuffer);

    return (lStatus);
}
