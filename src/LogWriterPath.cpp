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
 *      This file implements a Nuovations Log Utilities concrete writer
 *      implementation for an arbitrary, appendable file system regular
 *      file specified by a path name.
 */

#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

#include <LogUtilities/LogWriterPath.hpp>

namespace Nuovations
{

namespace Log
{

namespace Writer
{

static const int    kDescriptorInvalid = -1;

static const int    kFlags = (O_WRONLY | O_APPEND | O_CREAT);
static const mode_t kMode  = ((S_IRUSR | S_IWUSR) |
                              (S_IRGRP | S_IWGRP) |
                              (S_IROTH | S_IWOTH));

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates the writer associated with the
 *    specified path using the default file mode.
 *
 *  @param[in]  inPath  A file path suitable for appending
 *                      which the writer will open and write to.
 *
 */
Path::Path(const char * inPath) :
    Descriptor(),
    mDescriptor(open(inPath, kFlags, kMode))
{
    assert(mDescriptor > 0);

    Descriptor::SetDescriptor(mDescriptor);
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates the writer associated with the
 *    specified path using the specified file mode.
 *
 *  @param[in]  inPath  A file path suitable for appending
 *                      which the writer will open and write to.
 *  @param[in]  inMode  The file mode the path will be created with
 *                      if it does not already exist.
 *
 */
Path::Path(const char * inPath, mode_t inMode) :
    Descriptor(),
    mDescriptor(open(inPath, kFlags, inMode))
{
    assert(mDescriptor > 0);

    Descriptor::SetDescriptor(mDescriptor);
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Path::~Path(void)
{
    // Do not sync or close the descriptor here. We let the descriptor
    // object handle that on our behalf.

    mDescriptor = kDescriptorInvalid;
}

}; // namespace Writer

}; // namespace Log

}; // namespace Nuovations
