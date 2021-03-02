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
 *      This file implements a unit test for Log::Utilities::Memory
 */

#include <LogUtilities/LogFilterAlways.hpp>
#include <LogUtilities/LogFormatterPlain.hpp>
#include <LogUtilities/LogFunctionUtilities.hpp>
#include <LogUtilities/LogGlobals.hpp>
#include <LogUtilities/LogIndenterTab.hpp>
#include <LogUtilities/LogLogger.hpp>
#include <LogUtilities/LogWriterDescriptor.hpp>

#include <ostream>
#include <regex>
#include <string>

#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestLogUtilitiesBasis.hpp"


using namespace Nuovations;
using namespace std;


class TestLogFunctionUtilities :
    public TestLogUtilitiesBasis
{
    CPPUNIT_TEST_SUITE(TestLogFunctionUtilities);
    CPPUNIT_TEST(TestFunctionTracer);
    CPPUNIT_TEST(TestFunctionTracerWithLevel);
    CPPUNIT_TEST(TestScopedFunctionTracer);
    CPPUNIT_TEST(TestScopedFunctionTracerWithLevel);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestFunctionTracer(void);
    void TestFunctionTracerWithLevel(void);
    void TestScopedFunctionTracer(void);
    void TestScopedFunctionTracerWithLevel(void);

private:
    int  CreateTemporaryFile(char * aPathBuffer);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogFunctionUtilities);

static void
c(void)
{
    const Log::Utilities::Function::ScopedTracer lScopedTracer(__PRETTY_FUNCTION__);
}

static void
b(void)
{
    const Log::Utilities::Function::ScopedTracer lScopedTracer(__PRETTY_FUNCTION__);

    c();
}

static void
a(void)
{
    const Log::Utilities::Function::Tracer lTracer(__PRETTY_FUNCTION__);

    b();
}

static void
c(const Log::Level & inLevel)
{
    const Log::Utilities::Function::ScopedTracer lScopedTracer(__FUNCTION__, inLevel);
}

static void
b(const Log::Level & inLevel)
{
    const Log::Utilities::Function::ScopedTracer lScopedTracer(__FUNCTION__, inLevel);

    c(inLevel);
}

static void
a(const Log::Level & inLevel)
{
    const Log::Utilities::Function::Tracer lTracer(__FUNCTION__, inLevel);

    b(inLevel);
}

void
TestLogFunctionUtilities :: TestFunctionTracer(void)
{
    const string kExpected =
        "--> void TestLogFunctionUtilities::TestFunctionTracer()\n"
        "--> void a()\n"
        "--> void b()\n"
        "	--> void c()\n"
        "	<-- void c()\n"
        "<-- void b()\n"
        "<-- void a()\n"
        "<-- void TestLogFunctionUtilities::TestFunctionTracer()\n";
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::Tab    lTabIndenter(Log::Indenter::String::Flags::kEvery);
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);

        Log::Debug().SetFilter(lAlwaysFilter);
        Log::Debug().SetIndenter(lTabIndenter);
        Log::Debug().SetFormatter(lPlainFormatter);
        Log::Debug().SetWriter(lDescriptorWriter);

        {
            const Log::Utilities::Function::Tracer lTracer(__PRETTY_FUNCTION__);

            a();
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpected);
}

void
TestLogFunctionUtilities :: TestFunctionTracerWithLevel(void)
{
    const string kExpected =
        "--> TestFunctionTracerWithLevel\n"
        "--> a\n"
        "--> b\n"
        "	--> c\n"
        "	<-- c\n"
        "<-- b\n"
        "<-- a\n"
        "<-- TestFunctionTracerWithLevel\n";
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::Tab    lTabIndenter(Log::Indenter::String::Flags::kEvery);
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);

        Log::Debug().SetFilter(lAlwaysFilter);
        Log::Debug().SetIndenter(lTabIndenter);
        Log::Debug().SetFormatter(lPlainFormatter);
        Log::Debug().SetWriter(lDescriptorWriter);

        {
            const Log::Level                       kLevel = 0;
            const Log::Utilities::Function::Tracer lTracer(__FUNCTION__, kLevel);

            a(kLevel);
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpected);
}


void
TestLogFunctionUtilities :: TestScopedFunctionTracer(void)
{
    const string kExpected =
        "--> void TestLogFunctionUtilities::TestScopedFunctionTracer()\n"
        "--> void a()\n"
        "	--> void b()\n"
        "		--> void c()\n"
        "		<-- void c()\n"
        "	<-- void b()\n"
        "<-- void a()\n"
        "<-- void TestLogFunctionUtilities::TestScopedFunctionTracer()\n";
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::Tab    lTabIndenter(Log::Indenter::String::Flags::kEvery);
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);

        Log::Debug().SetFilter(lAlwaysFilter);
        Log::Debug().SetIndenter(lTabIndenter);
        Log::Debug().SetFormatter(lPlainFormatter);
        Log::Debug().SetWriter(lDescriptorWriter);

        {
            const Log::Utilities::Function::ScopedTracer lScopedTracer(__PRETTY_FUNCTION__);
            const unsigned int                           kExpectedDepth = 1;
            const unsigned int                           kActualDepth   = lScopedTracer.GetDepth();

            CPPUNIT_ASSERT_EQUAL(kExpectedDepth, kActualDepth);

            a();
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpected);
}

void
TestLogFunctionUtilities :: TestScopedFunctionTracerWithLevel(void)
{
    const string kExpected =
        "--> TestScopedFunctionTracerWithLevel\n"
        "--> a\n"
        "	--> b\n"
        "		--> c\n"
        "		<-- c\n"
        "	<-- b\n"
        "<-- a\n"
        "<-- TestScopedFunctionTracerWithLevel\n";
    Log::Filter::Always   lAlwaysFilter;
    Log::Indenter::Tab    lTabIndenter(Log::Indenter::String::Flags::kEvery);
    Log::Formatter::Plain lPlainFormatter;
    char                  lPathBuffer[PATH_MAX];
    int                   lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    {
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);

        Log::Debug().SetFilter(lAlwaysFilter);
        Log::Debug().SetIndenter(lTabIndenter);
        Log::Debug().SetFormatter(lPlainFormatter);
        Log::Debug().SetWriter(lDescriptorWriter);

        {
            const Log::Level                             kLevel = 0;
            const Log::Utilities::Function::ScopedTracer lScopedTracer(__FUNCTION__, kLevel);
            const unsigned int                           kExpectedDepth = 1;
            const unsigned int                           kActualDepth   = lScopedTracer.GetDepth();

            CPPUNIT_ASSERT_EQUAL(kExpectedDepth, kActualDepth);

            a(kLevel);
        }
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpected);
}

int
TestLogFunctionUtilities :: CreateTemporaryFile(char * aPathBuffer)
{
    static const char * const kTestName = "function-utilities";
    int                       lStatus;

    lStatus = CreateTemporaryFileFromName(kTestName, aPathBuffer);

    return (lStatus);
}
