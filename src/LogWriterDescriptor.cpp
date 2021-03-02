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
 *      implementation for an open, appendable System V Release 4
 *      (SVR4)-, 4.3BSD-, POSIX.1-2001-, or POSIX.1-2008-conformant
 *      file descriptor.
 */

#include <cassert>
#include <cstdio>

using namespace std;

#include <LogUtilities/LogWriterDescriptor.hpp>

namespace Nuovations
{

namespace Log
{

namespace Writer
{

static const Descriptor::Flags kFlagsDefault = Descriptor::Flags::kNone;

static inline Descriptor::Flags operator &(const Descriptor::Flags &inFirst, const Descriptor::Flags &inSecond)
{
    using underlying_type = typename std::underlying_type<Descriptor::Flags>::type;

    const Descriptor::Flags lFlags =
        static_cast<Descriptor::Flags>(static_cast<underlying_type>(inFirst) &
                                       static_cast<underlying_type>(inSecond));

    return (lFlags);
}

/**
 * Implementation of the @a Log::Writer::Descriptor object.
 *
 * @private
 */
struct Descriptor::Implementation
{
    Implementation(void);
    Implementation(int inDescriptor);
    Implementation(int inDescriptor, Flags inFlags);
    ~Implementation(void);

    Flags mFlags;   //!< Descriptor management flags which determine how
                    //!< the writer interacts with the descriptor.
    FILE * mStream; //!< The stream to which messages for the instantiated
                    //!< writer are written using the stdio(3) functions.
};

Descriptor::
Implementation::Implementation(void) :
    mFlags(kFlagsDefault),
    mStream(NULL)
{
    return;
}

Descriptor::
Implementation::Implementation(int inDescriptor) :
    mFlags(kFlagsDefault),
    mStream(fdopen(inDescriptor, "a"))
{
    assert(mStream != NULL);
}

Descriptor::
Implementation::Implementation(int inDescriptor, Flags inFlags) :
    mFlags(inFlags),
    mStream(fdopen(inDescriptor, "a"))
{
    assert(mStream != NULL);
}

Descriptor::
Implementation::~Implementation(void)
{
    int status;

    if ((mFlags & Flags::kNoFlush) != Flags::kNoFlush) {
        assert(mStream != NULL);

        status = fflush(mStream);
        assert(status == 0);
    }

    if ((mFlags & Flags::kNoClose) != Flags::kNoClose) {
        assert(mStream != NULL);

        status = fclose(mStream);
        assert(status == 0);
    }

    mFlags  = kFlagsDefault;
    mStream = NULL;
}

/**
 *  @brief
 *    This is the class default constructor.
 *
 *    This constructor instantiates the writer with an invalid initial
 *    state for which @a SetDescriptor must be called before use.
 *
 *  @sa SetDescriptor
 *
 */
Descriptor::Descriptor(void) :
    Stdio(),
    mImplementation(new Implementation)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates the writer associated with the
 *    specified descriptor and default descriptor management flags.
 *
 *  @param[in]  inDescriptor  An file descriptor suitable for
 *                            appending which the writer will write
 *                            to.
 *
 */
Descriptor::Descriptor(int inDescriptor) :
    Stdio(),
    mImplementation(new Implementation(inDescriptor))
{
    Stdio::SetStream(mImplementation->mStream);
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *    This constructor instantiates the writer associated with the
 *    specified descriptor and descriptor management flags.
 *
 *  @param[in]  inDescriptor  An file descriptor suitable for
 *                            appending which the writer will write
 *                            to.
 *  @param[in]  inFlags       The descriptor management flags to
 *                            instantiate the writer with.
 *
 */
Descriptor::Descriptor(int inDescriptor, Flags inFlags) :
    Stdio(),
    mImplementation(new Implementation(inDescriptor, inFlags))
{
    Stdio::SetStream(mImplementation->mStream);
}

/**
 *  @brief
 *    This is a class copy constructor.
 *
 *    This constructor instantiates the writer by copying
 *    the specified writer.
 *
 *  @param[in]  inWriter      An immutable reference to the writer
 *                            to copy.
 *
 */
Descriptor::Descriptor(const Descriptor & inWriter) :
    Stdio(inWriter),
    mImplementation(inWriter.mImplementation)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Descriptor::~Descriptor(void)
{
    return;
}

/**
 *  @brief
 *    This sets the descriptor for the writer with default descriptor
 *    management flags.
 *
 *  @param[in]  inDescriptor  An file descriptor suitable for
 *                            appending which the writer will write
 *                            to.
 *
 */
void
Descriptor::SetDescriptor(int inDescriptor)
{
    SetDescriptor(inDescriptor, kFlagsDefault);
}

/**
 *  @brief
 *    This sets the descriptor for the writer with provided descriptor
 *    management flags.
 *
 *  @param[in]  inDescriptor  An file descriptor suitable for
 *                            appending which the writer will write
 *                            to.
 *  @param[in]  inFlags       The descriptor management flags to
 *                            instantiate the writer with.
 *
 */
void
Descriptor::SetDescriptor(int inDescriptor, Flags inFlags)
{
    mImplementation->mFlags  = inFlags;
    mImplementation->mStream = fdopen(inDescriptor, "a");

    Stdio::SetStream(mImplementation->mStream);
}

}; // namespace Writer

}; // namespace Log

}; // namespace Nuovations
