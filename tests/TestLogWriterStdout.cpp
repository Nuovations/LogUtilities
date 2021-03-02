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
 *      This file implements a unit test for Log::Writer::Stdout
 */

#include <LogUtilities/LogWriterStdout.hpp>

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


class TestLogWriterStdout :
    public TestLogUtilitiesBasis
{
    CPPUNIT_TEST_SUITE(TestLogWriterStdout);
    CPPUNIT_TEST(TestConstruction);
    CPPUNIT_TEST(TestStdoutWriter);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestConstruction(void);
    void TestStdoutWriter(void);

private:
    int  CreateTemporaryFile(char * aPathBuffer);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogWriterStdout);

void
TestLogWriterStdout :: TestConstruction(void)
{
    Log::Writer::Stdout lWriterStdout;
}

void
TestLogWriterStdout :: TestStdoutWriter(void)
{
    const std::string kExpected =
        "(null)(null)(null)Standard Output Stream w/o level.\n"
        "Standard Output Stream w/ level 0.\n"
        "Standard Output Stream w/ level UINT_MAX.\n";
    char              lPathBuffer[PATH_MAX];
    int               lStatus;
    int               lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);

    lStatus = dup2(lDescriptor, STDOUT_FILENO);
    CPPUNIT_ASSERT(lStatus > 0);

    close(lDescriptor);

    {
        Log::Writer::Stdout lStdoutWriter;

        lStdoutWriter.Write(NULL);
        lStdoutWriter.Write(0, NULL);
        lStdoutWriter.Write(UINT_MAX, NULL);

        lStdoutWriter.Write("");
        lStdoutWriter.Write(0, "");
        lStdoutWriter.Write(UINT_MAX, "");

        lStdoutWriter.Write("Standard Output Stream w/o level.\n");
        lStdoutWriter.Write(0, "Standard Output Stream w/ level 0.\n");
        lStdoutWriter.Write(UINT_MAX, "Standard Output Stream w/ level UINT_MAX.\n");

        fflush(stdout);
    }

    CheckResults(lPathBuffer, kExpected);
}

int
TestLogWriterStdout :: CreateTemporaryFile(char * aPathBuffer)
{
    static const char * const kTestName = "writer-stdout";
    int                       lStatus;

    lStatus = CreateTemporaryFileFromName(kTestName, aPathBuffer);

    return (lStatus);
}
