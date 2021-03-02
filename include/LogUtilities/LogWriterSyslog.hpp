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
 *      implementation for the Single UNIX Specification v2 (SUSv2)-,
 *      POSIX.1-2001-, and POSIX.1-2008-conformant syslog(3)
 *      interfaces.
 */

#ifndef LOGUTILITIES_LOGWRITERSYSLOG_HPP
#define LOGUTILITIES_LOGWRITERSYSLOG_HPP

#include <syslog.h>

#include "LogWriterBase.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Writer
        {

            /**
             *  @brief
             *    Log writer object for the Single UNIX Specification v2
             *    (SUSv2)-, POSIX.1-2001-, and POSIX.1-2008-conformant
             *    syslog(3) facility.
             *
             *  @ingroup writer
             *
             */
            class Syslog :
                public Base
            {
            public:
                Syslog(int inPriority);
                virtual ~Syslog(void);

                // Write at the specified level.

                virtual void Write(Level inLevel, const char * inMessage);

                // Write with no ident at level zero (0).

                virtual void Write(const char * inMessage);

                int  GetPriority(void);
                void SetPriority(int inPriority);

            private:
                int mPriority; //!< The priority at which messages for the
                               //!< instantiated writer are logged to the
                               //!< syslog(3) facility.
            };

        }; // namespace Writer

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGWRITERSYSLOG_HPP */
