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
 *      implementation for an arbitrary, appendable file system regular
 *      file specified by a path name.
 */

#ifndef LOGUTILITIES_LOGWRITERPATH_HPP
#define LOGUTILITIES_LOGWRITERPATH_HPP

#include <fcntl.h>

#include "LogWriterDescriptor.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Writer
        {

            /**
             *  @brief
             *    Log writer object for an arbitrary, appendable file
             *    system regular file specified by a path name.
             *
             *  @ingroup writer
             *
             */
            class Path :
                public Descriptor
            {
            public:
                Path(const char * inPath);
                Path(const char * inPath, mode_t inMode);
                virtual ~Path(void);

            private:
                int mDescriptor; //!< The open, appendable file descriptor
                                 //!< associated with the instantiated path
                                 //!< to which messages for the instantiated
                                 //!< writer are written.
            };

        }; // namespace Writer

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGWRITERPATH_HPP */
