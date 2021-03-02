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
 *      This file implements a unit test for Log::Writer::Stderr
 */

#include <LogUtilities/LogWriterStderr.hpp>

#include <string>

#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestLogUtilitiesBasis.hpp"


using namespace Nuovations;


class TestLogWriterStderr :
    public TestLogUtilitiesBasis
{
    CPPUNIT_TEST_SUITE(TestLogWriterStderr);
    CPPUNIT_TEST(TestConstruction);
    CPPUNIT_TEST(TestStderrWriter);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestConstruction(void);
    void TestStderrWriter(void);

private:
    int  CreateTemporaryFile(char * aPathBuffer);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogWriterStderr);

void
TestLogWriterStderr :: TestConstruction(void)
{
    Log::Writer::Stderr lWriterStderr;
}

void
TestLogWriterStderr :: TestStderrWriter(void)
{
    const std::string kExpected =
        "(null)(null)(null)Standard Error Stream w/o level.\n"
        "Standard Error Stream w/ level 0.\n"
        "Standard Error Stream w/ level UINT_MAX.\n";
    char              lPathBuffer[PATH_MAX];
    int               lStatus;
    int               lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);

    lStatus = dup2(lDescriptor, STDERR_FILENO);
    CPPUNIT_ASSERT(lStatus > 0);

    close(lDescriptor);

    {
        Log::Writer::Stderr lStderrWriter;

        lStderrWriter.Write(NULL);
        lStderrWriter.Write(0, NULL);
        lStderrWriter.Write(UINT_MAX, NULL);

        lStderrWriter.Write("");
        lStderrWriter.Write(0, "");
        lStderrWriter.Write(UINT_MAX, "");

        lStderrWriter.Write("Standard Error Stream w/o level.\n");
        lStderrWriter.Write(0, "Standard Error Stream w/ level 0.\n");
        lStderrWriter.Write(UINT_MAX, "Standard Error Stream w/ level UINT_MAX.\n");

        fflush(stderr);
    }

    CheckResults(lPathBuffer, kExpected);
}

int
TestLogWriterStderr :: CreateTemporaryFile(char * aPathBuffer)
{
    static const char * const kTestName = "writer-stderr";
    int                       lStatus;

    lStatus = CreateTemporaryFileFromName(kTestName, aPathBuffer);

    return (lStatus);
}
