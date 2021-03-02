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
 *      This file implements a unit test for Log::Chain.
 */

#include <LogUtilities/LogChain.hpp>

#include <vector>

#include <stdint.h>

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Nuovations;

static std::vector<int> sValues;

class LogChainTestBaseLink
{
public:
    virtual ~LogChainTestBaseLink(void) = default;

    enum class Kind : std::uint8_t
    {
        kDerivedA,
        kDerivedB,
        kDerivedC
    };

    virtual void Action(const int & inValue) = 0;

protected:
    LogChainTestBaseLink(void) = default;
};

class LogChainTestALink :
    public LogChainTestBaseLink
{
public:
    LogChainTestALink(void)          = default;
    virtual ~LogChainTestALink(void) = default;

    void Action(const int &inValue) final
    {
        sValues.push_back(inValue);
    }
};

class LogChainTestBLink :
    public LogChainTestBaseLink
{
public:
    LogChainTestBLink(void)          = default;
    virtual ~LogChainTestBLink(void) = default;

    void Action(const int &inValue) final
    {
        sValues.push_back(inValue * 2);
    }
};

class LogChainTestCLink :
    public LogChainTestBaseLink
{
public:
    LogChainTestCLink(void)          = default;
    virtual ~LogChainTestCLink(void) = default;

    void Action(const int &inValue) final
    {
        sValues.push_back(inValue + 7);
    }
};

class LogChainTestChain :
    public Log::Chain<LogChainTestBaseLink>,
    public LogChainTestBaseLink
{
public:
    LogChainTestChain(void)          = default;
    virtual ~LogChainTestChain(void) = default;

    void Action(const int &inValue) final
    {
        container_type::iterator lCurrentLink = Container().begin();
        container_type::iterator lLastLink    = Container().end();

        while (lCurrentLink != lLastLink) {
            (*lCurrentLink)->Action(inValue);

            std::advance(lCurrentLink, 1);
        }
    }
};

class TestLogChain :
    public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogChain);
    CPPUNIT_TEST(TestImplicitDefaultConstruction);
    CPPUNIT_TEST(TestImplicitCopyConstruction);
    CPPUNIT_TEST(TestObservation);
    CPPUNIT_TEST(TestMutation);
    CPPUNIT_TEST(TestChainedAction);
    CPPUNIT_TEST_SUITE_END();

public:
    void TestImplicitDefaultConstruction(void);
    void TestImplicitCopyConstruction(void);
    void TestObservation(void);
    void TestMutation(void);
    void TestChainedAction(void);

private:
    void TestObservation(const LogChainTestChain & inChain);
    void TestReset(LogChainTestChain & inChain);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogChain);

void
TestLogChain :: TestImplicitDefaultConstruction(void)
{
    LogChainTestChain lLogChainTestChain;
}

void
TestLogChain :: TestImplicitCopyConstruction(void)
{
    LogChainTestChain lLogChainTestChainA;
    LogChainTestChain lLogChainTestChainB(lLogChainTestChainA);
}

void
TestLogChain :: TestObservation(void)
{
    LogChainTestChain lLogChainTestChainA;
    LogChainTestChain lLogChainTestChainB(lLogChainTestChainA);

    TestObservation(lLogChainTestChainA);
    TestObservation(lLogChainTestChainB);
}

void
TestLogChain :: TestObservation(const LogChainTestChain &inChain)
{
    size_t                 lSize;
    bool                   lEmpty;
    LogChainTestBaseLink * lLink;

    lSize = inChain.Size();
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), lSize);

    lEmpty = inChain.Empty();
    CPPUNIT_ASSERT_EQUAL(true, lEmpty);

    lLink = inChain.Link<LogChainTestBaseLink>(0);
    CPPUNIT_ASSERT_EQUAL(static_cast<LogChainTestBaseLink *>(NULL), lLink);
}

void
TestLogChain :: TestMutation(void)
{
    LogChainTestChain      lLogChainTestChain;
    LogChainTestALink      lLogChainTestLinkA;
    LogChainTestBLink      lLogChainTestLinkB;
    LogChainTestCLink      lLogChainTestLinkC;
    size_t                 lSize;
    bool                   lEmpty;
    LogChainTestBaseLink * lLink;

    // Test the base, empty chain

    TestObservation(lLogChainTestChain);

    // Push an "A" link and then test observation.

    lLogChainTestChain.Push(lLogChainTestLinkA);

    lSize = lLogChainTestChain.Size();
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), lSize);

    lEmpty = lLogChainTestChain.Empty();
    CPPUNIT_ASSERT_EQUAL(false, lEmpty);

    lLink = lLogChainTestChain.Link<LogChainTestBaseLink>(0);
    CPPUNIT_ASSERT(lLink != NULL);
    CPPUNIT_ASSERT(typeid(*lLink) == typeid(LogChainTestALink));
    {
        LogChainTestBaseLink &lFrontLink = lLogChainTestChain.Front<LogChainTestBaseLink>();
        CPPUNIT_ASSERT(typeid(lFrontLink) == typeid(LogChainTestALink));
    }

    // Push a "B" link and then test observation.

    lLogChainTestChain.Push(lLogChainTestLinkB);

    lSize = lLogChainTestChain.Size();
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), lSize);

    lEmpty = lLogChainTestChain.Empty();
    CPPUNIT_ASSERT_EQUAL(false, lEmpty);

    lLink = lLogChainTestChain.Link<LogChainTestBaseLink>(0);
    CPPUNIT_ASSERT(lLink != NULL);
    CPPUNIT_ASSERT(typeid(*lLink) == typeid(LogChainTestALink));
    {
        LogChainTestBaseLink &lFrontLink = lLogChainTestChain.Front<LogChainTestBaseLink>();
        CPPUNIT_ASSERT(typeid(lFrontLink) == typeid(LogChainTestALink));
    }

    lLink = lLogChainTestChain.Link<LogChainTestBaseLink>(1);
    CPPUNIT_ASSERT(lLink != NULL);
    CPPUNIT_ASSERT(typeid(*lLink) == typeid(LogChainTestBLink));

    // Push a "C" link and then test observation.

    lLogChainTestChain.Push(lLogChainTestLinkC);

    lSize = lLogChainTestChain.Size();
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), lSize);

    lEmpty = lLogChainTestChain.Empty();
    CPPUNIT_ASSERT_EQUAL(false, lEmpty);

    lLink = lLogChainTestChain.Link<LogChainTestBaseLink>(0);
    CPPUNIT_ASSERT(lLink != NULL);
    CPPUNIT_ASSERT(typeid(*lLink) == typeid(LogChainTestALink));
    {
        LogChainTestBaseLink &lFrontLink = lLogChainTestChain.Front<LogChainTestBaseLink>();
        CPPUNIT_ASSERT(typeid(lFrontLink) == typeid(LogChainTestALink));
    }

    lLink = lLogChainTestChain.Link<LogChainTestBaseLink>(1);
    CPPUNIT_ASSERT(lLink != NULL);
    CPPUNIT_ASSERT(typeid(*lLink) == typeid(LogChainTestBLink));

    lLink = lLogChainTestChain.Link<LogChainTestBaseLink>(2);
    CPPUNIT_ASSERT(lLink != NULL);
    CPPUNIT_ASSERT(typeid(*lLink) == typeid(LogChainTestCLink));

    // Test popping links off the chain

    // Pop the "C" link off

    lLogChainTestChain.Pop();

    lSize = lLogChainTestChain.Size();
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), lSize);

    lEmpty = lLogChainTestChain.Empty();
    CPPUNIT_ASSERT_EQUAL(false, lEmpty);

    lLink = lLogChainTestChain.Link<LogChainTestBaseLink>(0);
    CPPUNIT_ASSERT(lLink != NULL);
    CPPUNIT_ASSERT(typeid(*lLink) == typeid(LogChainTestALink));
    {
        LogChainTestBaseLink &lFrontLink = lLogChainTestChain.Front<LogChainTestBaseLink>();
        CPPUNIT_ASSERT(typeid(lFrontLink) == typeid(LogChainTestALink));
    }

    lLink = lLogChainTestChain.Link<LogChainTestBaseLink>(1);
    CPPUNIT_ASSERT(lLink != NULL);
    CPPUNIT_ASSERT(typeid(*lLink) == typeid(LogChainTestBLink));

    // Pop the "B" link off

    lLogChainTestChain.Pop();

    lSize = lLogChainTestChain.Size();
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), lSize);

    lEmpty = lLogChainTestChain.Empty();
    CPPUNIT_ASSERT_EQUAL(false, lEmpty);

    lLink = lLogChainTestChain.Link<LogChainTestBaseLink>(0);
    CPPUNIT_ASSERT(lLink != NULL);
    CPPUNIT_ASSERT(typeid(*lLink) == typeid(LogChainTestALink));
    {
        LogChainTestBaseLink &lFrontLink = lLogChainTestChain.Front<LogChainTestBaseLink>();
        CPPUNIT_ASSERT(typeid(lFrontLink) == typeid(LogChainTestALink));
    }

    // Pop the "A" link off

    lLogChainTestChain.Pop();

    lSize = lLogChainTestChain.Size();
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), lSize);

    lEmpty = lLogChainTestChain.Empty();
    CPPUNIT_ASSERT_EQUAL(true, lEmpty);

    lLink = lLogChainTestChain.Link<LogChainTestBaseLink>(0);
    CPPUNIT_ASSERT_EQUAL(static_cast<LogChainTestBaseLink *>(NULL), lLink);

    // Re-establish the chain links and then test reset.

    lLogChainTestChain.Push(lLogChainTestLinkA);
    lLogChainTestChain.Push(lLogChainTestLinkB);
    lLogChainTestChain.Push(lLogChainTestLinkC);
}

void
TestLogChain :: TestReset(LogChainTestChain &inChain)
{
    inChain.Reset();

    TestObservation(inChain);
}

void
TestLogChain :: TestChainedAction(void)
{
    LogChainTestChain lLogChainTestChain;
    LogChainTestALink lLogChainTestLinkA;
    LogChainTestBLink lLogChainTestLinkB;
    LogChainTestCLink lLogChainTestLinkC;

    lLogChainTestChain.Push(lLogChainTestLinkA);
    lLogChainTestChain.Push(lLogChainTestLinkB);
    lLogChainTestChain.Push(lLogChainTestLinkC);

    lLogChainTestChain.Action(13);

    CPPUNIT_ASSERT_EQUAL(13, sValues.at(0));
    CPPUNIT_ASSERT_EQUAL(26, sValues.at(1));
    CPPUNIT_ASSERT_EQUAL(20, sValues.at(2));
}
