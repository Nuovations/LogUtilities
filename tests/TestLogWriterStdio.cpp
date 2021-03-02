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
 *      This file implements a unit test for Log::Writer::Stdio
 */

#include <LogUtilities/LogWriterStdio.hpp>

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


class TestLogWriterStdio :
    public TestLogUtilitiesBasis
{
    CPPUNIT_TEST_SUITE(TestLogWriterStdio);
    CPPUNIT_TEST(TestConstruction);
    CPPUNIT_TEST(TestStderrWriter);
    CPPUNIT_TEST(TestStdoutWriter);
    CPPUNIT_TEST(TestPathWriter);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestConstruction(void);
    void TestStderrWriter(void);
    void TestStdoutWriter(void);
    void TestPathWriter(void);

private:
    int  CreateTemporaryFile(char * aPathBuffer);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogWriterStdio);

void
TestLogWriterStdio :: TestConstruction(void)
{
    Log::Writer::Stdio lWriterStdio(stdout);
}

void
TestLogWriterStdio :: TestStderrWriter(void)
{
    const std::string kExpected =
        "(null)(null)(null)Standard I/O Stream (Error) w/o level.\n"
        "Standard I/O Stream (Error) w/ level 0.\n"
        "Standard I/O Stream (Error) w/ level UINT_MAX.\n";
    char              lPathBuffer[PATH_MAX];
    int               lStatus;
    int               lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);

    lStatus = dup2(lDescriptor, STDERR_FILENO);
    CPPUNIT_ASSERT(lStatus > 0);

    close(lDescriptor);

    {
        Log::Writer::Stdio lStderrWriter(stderr);

        lStderrWriter.Write(NULL);
        lStderrWriter.Write(0, NULL);
        lStderrWriter.Write(UINT_MAX, NULL);

        lStderrWriter.Write("");
        lStderrWriter.Write(0, "");
        lStderrWriter.Write(UINT_MAX, "");

        lStderrWriter.Write("Standard I/O Stream (Error) w/o level.\n");
        lStderrWriter.Write(0, "Standard I/O Stream (Error) w/ level 0.\n");
        lStderrWriter.Write(UINT_MAX, "Standard I/O Stream (Error) w/ level UINT_MAX.\n");

        fflush(stderr);
    }

    CheckResults(lPathBuffer, kExpected);
}

void
TestLogWriterStdio :: TestStdoutWriter(void)
{
    const std::string kExpected =
        "(null)(null)(null)Standard I/O Stream (Out) w/o level.\n"
        "Standard I/O Stream (Out) w/ level 0.\n"
        "Standard I/O Stream (Out) w/ level UINT_MAX.\n";
    char              lPathBuffer[PATH_MAX];
    int               lStatus;
    int               lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);

    lStatus = dup2(lDescriptor, STDOUT_FILENO);
    CPPUNIT_ASSERT(lStatus > 0);

    close(lDescriptor);

    {
        Log::Writer::Stdio lStdoutWriter(stdout);

        lStdoutWriter.Write(NULL);
        lStdoutWriter.Write(0, NULL);
        lStdoutWriter.Write(UINT_MAX, NULL);

        lStdoutWriter.Write("");
        lStdoutWriter.Write(0, "");
        lStdoutWriter.Write(UINT_MAX, "");

        lStdoutWriter.Write("Standard I/O Stream (Out) w/o level.\n");
        lStdoutWriter.Write(0, "Standard I/O Stream (Out) w/ level 0.\n");
        lStdoutWriter.Write(UINT_MAX, "Standard I/O Stream (Out) w/ level UINT_MAX.\n");

        fflush(stdout);
    }

    CheckResults(lPathBuffer, kExpected);
}

void
TestLogWriterStdio :: TestPathWriter(void)
{
    const std::string kExpected =
        "(null)(null)(null)Standard I/O Stream (Arbitrary) w/o level.\n"
        "Standard I/O Stream (Arbitrary) w/ level 0.\n"
        "Standard I/O Stream (Arbitrary) w/ level UINT_MAX.\n";
    char              lPathBuffer[PATH_MAX];
    int               lDescriptor;
    FILE *            lStream;

    lDescriptor = CreateTemporaryFile(lPathBuffer);

    lStream = fdopen(lDescriptor, "w");
    CPPUNIT_ASSERT(lStream != NULL);

    {
        Log::Writer::Stdio lStreamWriter(lStream);

        lStreamWriter.Write(NULL);
        lStreamWriter.Write(0, NULL);
        lStreamWriter.Write(UINT_MAX, NULL);

        lStreamWriter.Write("");
        lStreamWriter.Write(0, "");
        lStreamWriter.Write(UINT_MAX, "");

        lStreamWriter.Write("Standard I/O Stream (Arbitrary) w/o level.\n");
        lStreamWriter.Write(0, "Standard I/O Stream (Arbitrary) w/ level 0.\n");
        lStreamWriter.Write(UINT_MAX, "Standard I/O Stream (Arbitrary) w/ level UINT_MAX.\n");
    }

    fclose(lStream);
    close(lDescriptor);

    CheckResults(lPathBuffer, kExpected);
}

int
TestLogWriterStdio :: CreateTemporaryFile(char * aPathBuffer)
{
    static const char * const kTestName = "writer-stdio";
    int                       lStatus;

    lStatus = CreateTemporaryFileFromName(kTestName, aPathBuffer);

    return (lStatus);
}
