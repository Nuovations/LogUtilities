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
 *      This file implements a unit test for Log::Logger.
 */

#include <LogUtilities/LogFilterChain.hpp>
#include <LogUtilities/LogFilterLevel.hpp>
#include <LogUtilities/LogFilterQuiet.hpp>
#include <LogUtilities/LogFormatterPlain.hpp>
#include <LogUtilities/LogFormatterStamped.hpp>
#include <LogUtilities/LogIndenterSpace.hpp>
#include <LogUtilities/LogIndenterTab.hpp>
#include <LogUtilities/LogLogger.hpp>
#include <LogUtilities/LogWriterDescriptor.hpp>
#include <LogUtilities/LogWriterStderr.hpp>
#include <LogUtilities/LogWriterStdout.hpp>

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestLogUtilitiesBasis.hpp"


using namespace Nuovations;


class TestLogLogger :
    public TestLogUtilitiesBasis
{
    CPPUNIT_TEST_SUITE(TestLogLogger);
    CPPUNIT_TEST(TestConstruction);
    CPPUNIT_TEST(TestMutableObservation);
    CPPUNIT_TEST(TestImmutableObservation);
    CPPUNIT_TEST(TestMutation);
    CPPUNIT_TEST(TestLogger);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestConstruction(void);
    void TestMutableObservation(void);
    void TestImmutableObservation(void);
    void TestMutation(void);
    void TestLogger(void);

private:
    void TestLoggerWrite(const char * inTag, Log::Logger & inLogger);

    int  CreateTemporaryFile(char * aPathBuffer);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogLogger);

void
TestLogLogger :: TestConstruction(void)
{
    Log::Writer::Stderr   lStderrWriter;
    Log::Filter::Quiet    lQuietFilter;
    Log::Filter::Level    lLevelFilter;
    Log::Indenter::Tab    lTabIndenter(Log::Indenter::String::Flags::kEvery);
    Log::Formatter::Plain lPlainFormatter;
    Log::Filter::Chain    lChainFilter;

    lChainFilter.Push(lQuietFilter);
    lChainFilter.Push(lLevelFilter);

    Log::Logger lLogger(lChainFilter,
                        lTabIndenter,
                        lPlainFormatter,
                        lStderrWriter);
}

void
TestLogLogger :: TestMutableObservation(void)
{
    Log::Writer::Stderr   lStderrWriter;
    Log::Filter::Quiet    lQuietFilter;
    Log::Filter::Level    lLevelFilter;
    Log::Indenter::Tab    lTabIndenter(Log::Indenter::String::Flags::kEvery);
    Log::Formatter::Plain lPlainFormatter;
    Log::Filter::Chain    lChainFilter;

    lChainFilter.Push(lQuietFilter);
    lChainFilter.Push(lLevelFilter);

    Log::Logger lLogger(lChainFilter,
                        lTabIndenter,
                        lPlainFormatter,
                        lStderrWriter);

    CPPUNIT_ASSERT(&lStderrWriter   == &lLogger.GetWriter());
    CPPUNIT_ASSERT(&lChainFilter    == &lLogger.GetFilter());
    CPPUNIT_ASSERT(&lTabIndenter    == &lLogger.GetIndenter());
    CPPUNIT_ASSERT(&lPlainFormatter == &lLogger.GetFormatter());
}

void
TestLogLogger :: TestImmutableObservation(void)
{
    Log::Writer::Stderr   lStderrWriter;
    Log::Filter::Quiet    lQuietFilter;
    Log::Filter::Level    lLevelFilter;
    Log::Indenter::Tab    lTabIndenter(Log::Indenter::String::Flags::kEvery);
    Log::Formatter::Plain lPlainFormatter;
    Log::Filter::Chain    lChainFilter;

    lChainFilter.Push(lQuietFilter);
    lChainFilter.Push(lLevelFilter);

    const Log::Logger lLogger(lChainFilter,
                              lTabIndenter,
                              lPlainFormatter,
                              lStderrWriter);

    CPPUNIT_ASSERT(&lStderrWriter   == &lLogger.GetWriter());
    CPPUNIT_ASSERT(&lChainFilter    == &lLogger.GetFilter());
    CPPUNIT_ASSERT(&lTabIndenter    == &lLogger.GetIndenter());
    CPPUNIT_ASSERT(&lPlainFormatter == &lLogger.GetFormatter());
}

void
TestLogLogger :: TestMutation(void)
{
    Log::Writer::Stderr     lStderrWriter;
    Log::Writer::Stdout     lStdoutWriter;
    Log::Filter::Quiet      lQuietFilter;
    Log::Filter::Level      lLevelFilter;
    Log::Indenter::Space    lSpaceIndenter(Log::Indenter::String::Flags::kEvery);
    Log::Indenter::Tab      lTabIndenter(Log::Indenter::String::Flags::kEvery);
    Log::Formatter::Plain   lPlainFormatter;
    Log::Formatter::Stamped lStampedFormatter;
    Log::Filter::Chain      lChainFilter;

    lChainFilter.Push(lQuietFilter);
    lChainFilter.Push(lLevelFilter);

    Log::Logger lLogger(lChainFilter,
                        lTabIndenter,
                        lPlainFormatter,
                        lStderrWriter);

    CPPUNIT_ASSERT(&lStderrWriter   == &lLogger.GetWriter());
    CPPUNIT_ASSERT(&lChainFilter    == &lLogger.GetFilter());
    CPPUNIT_ASSERT(&lTabIndenter    == &lLogger.GetIndenter());
    CPPUNIT_ASSERT(&lPlainFormatter == &lLogger.GetFormatter());

    lLogger.SetFilter(lLevelFilter);
    lLogger.SetIndenter(lSpaceIndenter);
    lLogger.SetFormatter(lStampedFormatter);
    lLogger.SetWriter(lStdoutWriter);

    CPPUNIT_ASSERT(&lStdoutWriter     == &lLogger.GetWriter());
    CPPUNIT_ASSERT(&lLevelFilter      == &lLogger.GetFilter());
    CPPUNIT_ASSERT(&lSpaceIndenter    == &lLogger.GetIndenter());
    CPPUNIT_ASSERT(&lStampedFormatter == &lLogger.GetFormatter());
}

void
TestLogLogger :: TestLogger(void)
{
    const std::string       kExpected =
        "TEST (Default): This is a single line message at level/indent default/default.\n"
        "TEST (Default): This is a single line message at level/indent 0/default.\n"
        "TEST (Default): This is a single line message at level/indent 0/0.\n"
        "TEST (Default): This is a multi-line message at level/indent default/default.\n"
        "TEST (Default): This is a multi-line\n"
        "message at level/indent 0/default.\n"
        "TEST (Default): This is a multi-line\n"
        "message at level/indent 0/0.\n"
        "TEST (1): This is a single line message at level/indent default/default.\n"
        "TEST (1): This is a single line message at level/indent 0/default.\n"
        "TEST (1): This is a single line message at level/indent 0/0.\n"
        "TEST (1): This is a single line message at level/indent 1/0.\n"
        "	TEST (1): This is a single line message at level/indent 1/1.\n"
        "TEST (1): This is a multi-line message at level/indent default/default.\n"
        "TEST (1): This is a multi-line\n"
        "message at level/indent 0/default.\n"
        "TEST (1): This is a multi-line\n"
        "message at level/indent 0/0.\n"
        "TEST (1): This is a multi-line\n"
        "message at level/indent 1/0.\n"
        "\tTEST (1): This is a multi-line\n"
        "\tmessage at level/indent 1/1.\n"
        "TEST (UINT_MAX): This is a single line message at level/indent default/default.\n"
        "TEST (UINT_MAX): This is a single line message at level/indent 0/default.\n"
        "TEST (UINT_MAX): This is a single line message at level/indent 0/0.\n"
        "TEST (UINT_MAX): This is a single line message at level/indent 1/0.\n"
        "\tTEST (UINT_MAX): This is a single line message at level/indent 1/1.\n"
        "\t\tTEST (UINT_MAX): This is a single line message at level/indent 2/2.\n"
        "\t\tTEST (UINT_MAX): This is a single line message at level/indent 4294967295/2.\n"
        "TEST (UINT_MAX): This is a multi-line message at level/indent default/default.\n"
        "TEST (UINT_MAX): This is a multi-line\n"
        "message at level/indent 0/default.\n"
        "TEST (UINT_MAX): This is a multi-line\n"
        "message at level/indent 0/0.\n"
        "TEST (UINT_MAX): This is a multi-line\n"
        "message at level/indent 1/0.\n"
        "\tTEST (UINT_MAX): This is a multi-line\n"
        "\tmessage at level/indent 1/1.\n"
        "\t\tTEST (UINT_MAX): This is a multi-line\n"
        "\t\tmessage at level/indent 2/2.\n"
        "\t\tTEST (UINT_MAX): This is a multi-line\n"
        "\t\tmessage at level/indent 4294967295/2.\n";
    Log::Filter::Quiet      lQuietFilter;
    Log::Filter::Level      lLevelFilter;
    Log::Indenter::Tab      lTabIndenter(Log::Indenter::String::Flags::kEvery);
    Log::Formatter::Plain   lPlainFormatter;
    Log::Filter::Chain      lChainFilter;
    Log::Filter::Base *     lFilter;
    char                    lPathBuffer[PATH_MAX];
    int                     lDescriptor;

    lDescriptor = CreateTemporaryFile(lPathBuffer);
    CPPUNIT_ASSERT(lDescriptor > 0);

    lChainFilter.Push(lQuietFilter);
    lChainFilter.Push(lLevelFilter);

    {
        Log::Writer::Descriptor lDescriptorWriter(lDescriptor);
        Log::Logger             lLogger(lChainFilter,
                                        lTabIndenter,
                                        lPlainFormatter,
                                        lDescriptorWriter);

        // Test the logger with its default settings

        TestLoggerWrite("TEST (Default)", lLogger);

        // Test the logger with the level increased to 1.

        lFilter = static_cast<Log::Filter::Chain &>
            (lLogger.GetFilter()).Link<Log::Filter::Level>(1);
        CPPUNIT_ASSERT(lFilter != NULL);

        static_cast<Log::Filter::Level *>(lFilter)->SetLevel(1);
        CPPUNIT_ASSERT(static_cast<Log::Filter::Level *>(lFilter)->GetLevel() == 1);

        TestLoggerWrite("TEST (1)", lLogger);

        // Test the logger with the level increased to UINT_MAX.

        static_cast<Log::Filter::Level *>(lFilter)->SetLevel(UINT_MAX);
        CPPUNIT_ASSERT(static_cast<Log::Filter::Level *>(lFilter)->GetLevel() == UINT_MAX);

        TestLoggerWrite("TEST (UINT_MAX)", lLogger);

        // Test the logger with quiet set.

        lFilter = static_cast<Log::Filter::Chain &>
            (lLogger.GetFilter()).Link<Log::Filter::Quiet>(0);
        CPPUNIT_ASSERT(lFilter != NULL);

        static_cast<Log::Filter::Quiet *>(lFilter)->SetQuiet(true);
        CPPUNIT_ASSERT(static_cast<Log::Filter::Quiet *>(lFilter)->GetQuiet() == true);

        TestLoggerWrite("TEST (Quiet)", lLogger);
    }

    close(lDescriptor);

    CheckResults(lPathBuffer, kExpected);
}

void
TestLogLogger :: TestLoggerWrite(const char * inTag, Log::Logger & inLogger)
{
    Log::Level  theLevel;
    Log::Indent theIndent;

    // Test several single-line messages with various levels and indents.

    inLogger.Write("%s: This is a single line message at "
                   "level/indent default/default.\n", inTag);

    theLevel = 0;

    inLogger.Write(theLevel, "%s: This is a single line message at "
                   "level/indent %u/default.\n",
                   inTag, theLevel);

    theIndent = 0;

    inLogger.Write(theIndent, theLevel, "%s: This is a single line "
                   "message at level/indent %u/%u.\n",
                   inTag, theLevel, theIndent);

    theLevel++;

    inLogger.Write(theIndent, theLevel, "%s: This is a single line "
                   "message at level/indent %u/%u.\n",
                   inTag, theLevel, theIndent);

    theIndent++;

    inLogger.Write(theIndent, theLevel, "%s: This is a single line "
                   "message at level/indent %u/%u.\n",
                   inTag, theLevel, theIndent);

    theLevel++;
    theIndent++;

    inLogger.Write(theIndent, theLevel, "%s: This is a single line "
                   "message at level/indent %u/%u.\n",
                   inTag, theLevel, theIndent);

    theLevel = UINT_MAX;

    inLogger.Write(theIndent, theLevel, "%s: This is a single line "
                   "message at level/indent %u/%u.\n",
                   inTag, theLevel, theIndent);

    // Test several multi-line messages with various levels and indents.

    inLogger.Write("%s: This is a multi-line message at "
                   "level/indent default/default.\n", inTag);

    theLevel = 0;

    inLogger.Write(theLevel, "%s: This is a multi-line\nmessage at "
                   "level/indent %u/default.\n",
                   inTag, theLevel);

    theIndent = 0;

    inLogger.Write(theIndent, theLevel, "%s: This is a multi-line\n"
                   "message at level/indent %u/%u.\n",
                   inTag, theLevel, theIndent);

    theLevel++;

    inLogger.Write(theIndent, theLevel, "%s: This is a multi-line\n"
                   "message at level/indent %u/%u.\n",
                   inTag, theLevel, theIndent);

    theIndent++;

    inLogger.Write(theIndent, theLevel, "%s: This is a multi-line\n"
                   "message at level/indent %u/%u.\n",
                   inTag, theLevel, theIndent);

    theLevel++;
    theIndent++;

    inLogger.Write(theIndent, theLevel, "%s: This is a multi-line\n"
                   "message at level/indent %u/%u.\n",
                   inTag, theLevel, theIndent);

    theLevel = UINT_MAX;

    inLogger.Write(theIndent, theLevel, "%s: This is a multi-line\n"
                   "message at level/indent %u/%u.\n",
                   inTag, theLevel, theIndent);
}

int
TestLogLogger :: CreateTemporaryFile(char * aPathBuffer)
{
    static const char * const kTestName = "logger";
    int                       lStatus;

    lStatus = CreateTemporaryFileFromName(kTestName, aPathBuffer);

    return (lStatus);
}
