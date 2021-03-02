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
 *      This file implements a unit test for Log::Writer::Chain.
 */

#include <LogUtilities/LogWriterChain.hpp>
#include <LogUtilities/LogWriterDescriptor.hpp>

#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/stat.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestLogUtilitiesBasis.hpp"


using namespace Nuovations;


class TestLogWriterChain :
    public TestLogUtilitiesBasis
{
    CPPUNIT_TEST_SUITE(TestLogWriterChain);
    CPPUNIT_TEST(TestDefaultConstruction);
    CPPUNIT_TEST(TestCopyConstruction);
    CPPUNIT_TEST(TestObservation);
    CPPUNIT_TEST(TestWriterChain);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestDefaultConstruction(void);
    void TestCopyConstruction(void);
    void TestObservation(void);
    void TestWriterChain(void);

private:
    void TestObservation(const Log::Writer::Chain & inChain);

    int  CreateTemporaryFile(char * aPathBuffer);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogWriterChain);

void
TestLogWriterChain :: TestDefaultConstruction(void)
{
    Log::Writer::Chain lWriterChain;
}

void
TestLogWriterChain :: TestCopyConstruction(void)
{
    Log::Writer::Chain lWriterChainA;
    Log::Writer::Chain lWriterChainB(lWriterChainA);
}

void
TestLogWriterChain :: TestObservation(void)
{
    Log::Writer::Chain lWriterChainA;
    Log::Writer::Chain lWriterChainB(lWriterChainA);

    TestObservation(lWriterChainA);
    TestObservation(lWriterChainB);
}

void
TestLogWriterChain :: TestObservation(const Log::Writer::Chain & inChain)
{
    size_t              lSize;
    bool                lEmpty;
    Log::Writer::Base * lLink;

    lSize = inChain.Size();
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), lSize);

    lEmpty = inChain.Empty();
    CPPUNIT_ASSERT_EQUAL(true, lEmpty);

    lLink = inChain.Link<Log::Writer::Base>(0);
    CPPUNIT_ASSERT_EQUAL(static_cast<Log::Writer::Base *>(NULL), lLink);
}

void
TestLogWriterChain :: TestWriterChain(void)
{
    const std::string kExpected =
        "(null)(null)(null)Chained writer w/o level.\n"
        "Chained writer w/ level 0.\n"
        "Chained writer w/ level UINT_MAX.\n";
    char                    lPathBufferA[PATH_MAX];
    char                    lPathBufferB[PATH_MAX];
    int                     lDescriptorA;
    int                     lDescriptorB;

    lDescriptorA = CreateTemporaryFile(lPathBufferA);
    CPPUNIT_ASSERT(lDescriptorA > 0);

    lDescriptorB = CreateTemporaryFile(lPathBufferB);
    CPPUNIT_ASSERT(lDescriptorA > 0);

    {
        Log::Writer::Descriptor lDescriptorWriterA(lDescriptorA);
        Log::Writer::Descriptor lDescriptorWriterB(lDescriptorB);
        Log::Writer::Chain      lChainWriter;
        size_t                  lSize;
        bool                    lEmpty;
        Log::Writer::Base *     lWriter;

        // Test pushing links onto the chain

        lChainWriter.Push(lDescriptorWriterA);
        lChainWriter.Push(lDescriptorWriterB);

        // Test size observers

        lEmpty = lChainWriter.Empty();
        CPPUNIT_ASSERT(!lEmpty);

        lSize = lChainWriter.Size();
        CPPUNIT_ASSERT(lSize == 2);

        // Test link observers

        lWriter = lChainWriter.Link<Log::Writer::Descriptor>(0);
        CPPUNIT_ASSERT(lWriter != NULL);

        lWriter = lChainWriter.Link<Log::Writer::Descriptor>(1);
        CPPUNIT_ASSERT(lWriter != NULL);

        lWriter = lChainWriter.Link<Log::Writer::Base>(3);
        CPPUNIT_ASSERT(lWriter == NULL);

        // Test writer with links

        lChainWriter.Write(NULL);
        lChainWriter.Write(0, NULL);
        lChainWriter.Write(UINT_MAX, NULL);

        lChainWriter.Write("");
        lChainWriter.Write(0, "");
        lChainWriter.Write(UINT_MAX, "");

        lChainWriter.Write("Chained writer w/o level.\n");
        lChainWriter.Write(0, "Chained writer w/ level 0.\n");
        lChainWriter.Write(UINT_MAX, "Chained writer w/ level UINT_MAX.\n");

        // Test popping links off the chain

        lChainWriter.Pop();

        lEmpty = lChainWriter.Empty();
        CPPUNIT_ASSERT(!lEmpty);

        lSize = lChainWriter.Size();
        CPPUNIT_ASSERT(lSize == 1);

        lChainWriter.Pop();

        TestObservation(lChainWriter);

        // Retest with an empty chain.

        lChainWriter.Write(NULL);
        lChainWriter.Write(0, NULL);
        lChainWriter.Write(UINT_MAX, NULL);

        lChainWriter.Write("");
        lChainWriter.Write(0, "");
        lChainWriter.Write(UINT_MAX, "");

        lChainWriter.Write("Chained writer w/o level.\n");
        lChainWriter.Write(0, "Chained writer w/ level 0.\n");
        lChainWriter.Write(UINT_MAX, "Chained writer w/ level UINT_MAX.\n");
    }

    close(lDescriptorA);
    close(lDescriptorB);

    CheckResults(lPathBufferA, kExpected);
    CheckResults(lPathBufferB, kExpected);
}

int
TestLogWriterChain :: CreateTemporaryFile(char * aPathBuffer)
{
    static const char * const kTestName = "writer-chain";
    int                       lStatus;

    lStatus = CreateTemporaryFileFromName(kTestName, aPathBuffer);

    return (lStatus);
}
