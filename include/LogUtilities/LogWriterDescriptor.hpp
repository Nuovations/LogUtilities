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
 *      This file defines a Nuovations Log Utilities concrete writer
 *      implementation for an open, appendable System V Release 4
 *      (SVR4)-, 4.3BSD-, POSIX.1-2001-, or POSIX.1-2008-conformant
 *      file descriptor.
 */

#ifndef LOGUTILITIES_LOGWRITERDESCRIPTOR_HPP
#define LOGUTILITIES_LOGWRITERDESCRIPTOR_HPP

#include <stdint.h>

#include <boost/shared_ptr.hpp>

#include "LogWriterStdio.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Writer
        {

            /**
             *  @brief
             *    Log writer object for an open, appendable System V
             *    Release 4 (SVR4)-, 4.3BSD-, POSIX.1-2001-, or
             *    POSIX.1-2008-conformant file descriptor.
             *
             *  @ingroup writer
             *
             */
            class Descriptor :
                public Stdio
            {
            public:
                /**
                 *  @brief
                 *    Descriptor management flags.
                 *
                 *    Descriptor management flags which determine how
                 *    the writer interacts with the descriptor. These
                 *    flags may be bitwise-or'd with one another to
                 *    create compound management behaviors.
                 */
#if __cplusplus >= 201103L
                enum class Flags : uint8_t {
#else
                enum Flags {
#endif // __cplusplus >= 201103L
                    kNone    = 0,      //!< Specify no special descriptor management behavior.
                    kNoClose = 1 << 0, //!< Do not attempt to close the descriptor associated with the writer when the writer is destroyed.
                    kNoFlush = 1 << 1  //!< Do not attempt to flush the buffers associated with the writer when the writer is destroyed.
                };

            public:
                Descriptor(int inDescriptor);
                Descriptor(int inDescriptor, Flags inFlags);
                Descriptor(const Descriptor & inWriter);
                virtual ~Descriptor(void);

            protected:
                Descriptor(void);

                void SetDescriptor(int inDescriptor);
                void SetDescriptor(int inDescriptor, Flags inFlags);

            private:
                struct Implementation;

                /**
                 *  A shared, reference-counted pointer to the writer
                 *  implementation.
                 */
                boost::shared_ptr<Implementation> mImplementation;
            };

            /**
             *  @brief
             *    Bitwise or operator overload to support combining
             *    descriptor management flags.
             *
             *  @param[in]  inFirst   The operator left hand descriptor
             *                        management flags to combine.
             *  @param[in]  inSecond  The operator right hand descriptor
             *                        management flags to combine.
             *
             *  @returns
             *    The combined descriptor management flags.
             *
             */
            inline Descriptor::Flags operator |(const Descriptor::Flags &inFirst, const Descriptor::Flags &inSecond)
            {
                using underlying_type = typename std::underlying_type<Descriptor::Flags>::type;

                const Descriptor::Flags lFlags =
                    static_cast<Descriptor::Flags>(static_cast<underlying_type>(inFirst) |
                                                   static_cast<underlying_type>(inSecond));

                return (lFlags);
            }

        }; // namespace Writer

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGWRITERDESCRIPTOR_HPP */
