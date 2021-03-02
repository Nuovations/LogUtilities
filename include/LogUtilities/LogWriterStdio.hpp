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
 *      implementation for the C89-conformant C Standard Library
 *      input/output library functions (that is, stdio(3)).
 */

#ifndef LOGUTILITIES_LOGWRITERSTDIO_HPP
#define LOGUTILITIES_LOGWRITERSTDIO_HPP

#include <cstdio>

#include "LogWriterBase.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Writer
        {

            /**
             *  @brief
             *    Log writer object for the C89-conformant C Standard
             *    Library input/output library functions (that is,
             *    stdio(3)).
             *
             *  @ingroup writer
             *
             */
            class Stdio :
                public Base
            {
            public:
                Stdio(std::FILE * inStream);
                virtual ~Stdio(void);

                // Write at the specified level.

                virtual void Write(Level inLevel, const char * inMessage);

                // Write with no ident at level zero (0).

                virtual void Write(const char * inMessage);

            protected:
                Stdio(void);

                void SetStream(std::FILE * inStream);

            private:
                FILE * mStream; //!< The stream to which messages for the
                                //!< instantiated writer are written using
                                //!< the stdio(3) functions.
            };

        }; // namespace Writer

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGWRITERSTDIO_HPP */
