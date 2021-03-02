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
 *      This file implements a test basis for Log Utilities tests needing
 *      file system input and output.
 */

#include "TestLogUtilitiesBasis.hpp"

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>


int
TestLogUtilitiesBasis :: CreateTemporaryFileFromName(const char * aTestName, char * aPathBuffer)
{
    static const char * const kPathStem     = "/tmp/logutilities-test-";
    static const char * const kPathWildcard = "XXXXXX";
    std::string               lPathPattern(kPathStem);
    int                       lStatus;

    lPathPattern += aTestName;
    lPathPattern += kPathWildcard;

    lStatus = CreateTemporaryFileFromPattern(lPathPattern.c_str(), aPathBuffer);

    return (lStatus);
}

int
TestLogUtilitiesBasis :: CreateTemporaryFileFromPattern(const char * aPathPattern, char * aPathBuffer)
{
    int lStatus;

    aPathBuffer[0] = '\0';
    strcat(aPathBuffer, aPathPattern);

    lStatus = mkstemp(aPathBuffer);
    CPPUNIT_ASSERT(lStatus > 0);

    return (lStatus);
}

void
TestLogUtilitiesBasis :: CheckResults(const char * aPathBuffer, const std::string & aExpected)
{
    struct stat lStat;
    int         lStatus;
    int         lDescriptor;
    char *      lBuffer;
    ssize_t     lResidual;

    lStatus = stat(aPathBuffer, &lStat);
    CPPUNIT_ASSERT(lStatus == 0);

    CPPUNIT_ASSERT_EQUAL(static_cast<off_t>(aExpected.size()), lStat.st_size);

    lDescriptor = open(aPathBuffer, O_RDONLY);
    CPPUNIT_ASSERT(lDescriptor > 0);

    lBuffer = new char[static_cast<size_t>(lStat.st_size) + 1];
    CPPUNIT_ASSERT(lBuffer != NULL);

    lResidual = read(lDescriptor, &lBuffer[0], static_cast<size_t>(lStat.st_size));
    CPPUNIT_ASSERT_EQUAL(lStat.st_size, static_cast<off_t>(lResidual));

    close(lDescriptor);

    lBuffer[static_cast<size_t>(lStat.st_size)] = '\0';

    CPPUNIT_ASSERT_EQUAL(aExpected, std::string(lBuffer));

    delete [] lBuffer;

    lStatus = unlink(aPathBuffer);
    CPPUNIT_ASSERT(lStatus == 0);
}
