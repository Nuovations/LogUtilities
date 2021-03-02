/*
 *    Copyright (c) 2008-2021 Nuovation System Designs, LLC
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
 *      This file implements a Nuovations Log Utilities concrete
 *      writer implementation for the C89-conformant C Standard
 *      Library input/output library functions (that is, stdio(3))
 *      standard output (also known as, stdout) stream.
 */

#include <cstdio>

#include <LogUtilities/LogWriterStdout.hpp>

namespace Nuovations
{

namespace Log
{

namespace Writer
{

/**
 *  @brief
 *    This is the class default constructor.
 *
 *  This constructor instantiates the writer with the C Standard
 *  Library input/output library functions (that is, stdio(3))
 *  standard output (also known as, stdout) stream.
 */
Stdout::Stdout(void) :
    Stdio(stdout)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Stdout::~Stdout(void)
{
    return;
}

}; // namespace Writer

}; // namespace Log

}; // namespace Nuovations
