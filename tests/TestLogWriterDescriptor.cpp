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
 *      This file implements a unit test for Log::Writer::Descriptor
 */

#include <LogUtilities/LogWriterDescriptor.hpp>

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


class TestLogWriterDescriptor :
    public TestLogUtilitiesBasis
{
    CPPUNIT_TEST_SUITE(TestLogWriterDescriptor);
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

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogWriterDescriptor);

void
TestLogWriterDescriptor :: TestConstruction(void)
{
    using Flags = Log::Writer::Descriptor::Flags;

    char lPathBuffer[PATH_MAX];
    int  lStatus;
    int  lDescriptor;

    {
        lDescriptor = CreateTemporaryFile(lPathBuffer);

        Log::Writer::Descriptor lWriterDescriptorOnly(lDescriptor);

        lStatus = unlink(lPathBuffer);
        CPPUNIT_ASSERT(lStatus == 0);
    }

    {
        lDescriptor = CreateTemporaryFile(lPathBuffer);

        Log::Writer::Descriptor lWriterDescriptorNoClose(lDescriptor, Flags::kNoClose);
        Log::Writer::Descriptor lWriterDescriptorNoCloseAndNoFlush(lDescriptor, Flags::kNoClose | Flags::kNoFlush);

        close(lDescriptor);

        lStatus = unlink(lPathBuffer);
        CPPUNIT_ASSERT(lStatus == 0);
    }

    {
        lDescriptor = CreateTemporaryFile(lPathBuffer);

        Log::Writer::Descriptor lWriterDescriptorNoFlush(lDescriptor, Flags::kNoFlush);

        lStatus = unlink(lPathBuffer);
        CPPUNIT_ASSERT(lStatus == 0);
    }
}

void
TestLogWriterDescriptor :: TestStderrWriter(void)
{
    const std::string kExpected =
        "Standard Error w/o level.\n"
        "Standard Error w/ level 0.\n"
        "Standard Error w/ level UINT_MAX.\n";
    char              lPathBuffer[PATH_MAX];
    int               lStatus;
    int               lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);

    lStatus = dup2(lDescriptor, STDERR_FILENO);
    CPPUNIT_ASSERT(lStatus > 0);

    close(lDescriptor);

    {
        using Flags = Log::Writer::Descriptor::Flags;

        Log::Writer::Descriptor lStderrWriter(STDERR_FILENO, Flags::kNoClose);

        lStderrWriter.Write(NULL);
        lStderrWriter.Write(0, NULL);
        lStderrWriter.Write(UINT_MAX, NULL);

        lStderrWriter.Write("");
        lStderrWriter.Write(0, "");
        lStderrWriter.Write(UINT_MAX, "");

        lStderrWriter.Write("Standard Error w/o level.\n");
        lStderrWriter.Write(0, "Standard Error w/ level 0.\n");
        lStderrWriter.Write(UINT_MAX, "Standard Error w/ level UINT_MAX.\n");
    }

    CheckResults(lPathBuffer, kExpected);
}

void
TestLogWriterDescriptor :: TestStdoutWriter(void)
{
    const std::string kExpected =
        "Standard Output w/o level.\n"
        "Standard Output w/ level 0.\n"
        "Standard Output w/ level UINT_MAX.\n";
    char              lPathBuffer[PATH_MAX];
    int               lStatus;
    int               lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);

    lStatus = dup2(lDescriptor, STDOUT_FILENO);
    CPPUNIT_ASSERT(lStatus > 0);

    close(lDescriptor);

    {
        using Flags = Log::Writer::Descriptor::Flags;

        Log::Writer::Descriptor lStdoutWriter(STDOUT_FILENO, Flags::kNoClose);

        lStdoutWriter.Write(NULL);
        lStdoutWriter.Write(0, NULL);
        lStdoutWriter.Write(UINT_MAX, NULL);

        lStdoutWriter.Write("");
        lStdoutWriter.Write(0, "");
        lStdoutWriter.Write(UINT_MAX, "");

        lStdoutWriter.Write("Standard Output w/o level.\n");
        lStdoutWriter.Write(0, "Standard Output w/ level 0.\n");
        lStdoutWriter.Write(UINT_MAX, "Standard Output w/ level UINT_MAX.\n");
    }

    CheckResults(lPathBuffer, kExpected);
}

void
TestLogWriterDescriptor :: TestPathWriter(void)
{
    const std::string kExpected =
        "Path Descriptor w/o level.\n"
        "Path Descriptor w/ level 0.\n"
        "Path Descriptor w/ level UINT_MAX.\n";
    char              lPathBuffer[PATH_MAX];
    int               lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);

    {
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);

        lDescriptorWriter.Write(NULL);
        lDescriptorWriter.Write(0, NULL);
        lDescriptorWriter.Write(UINT_MAX, NULL);

        lDescriptorWriter.Write("");
        lDescriptorWriter.Write(0, "");
        lDescriptorWriter.Write(UINT_MAX, "");

        lDescriptorWriter.Write("Path Descriptor w/o level.\n");
        lDescriptorWriter.Write(0, "Path Descriptor w/ level 0.\n");
        lDescriptorWriter.Write(UINT_MAX, "Path Descriptor w/ level UINT_MAX.\n");
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpected);
}

int
TestLogWriterDescriptor :: CreateTemporaryFile(char * aPathBuffer)
{
    static const char * const kTestName = "writer-descriptor";
    int                       lStatus;

    lStatus = CreateTemporaryFileFromName(kTestName, aPathBuffer);

    return (lStatus);
}
