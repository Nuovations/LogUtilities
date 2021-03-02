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
 *      implementation that performs sequential writes to each link in
 *      a chain of writers on a single write to the chain.
 */

#ifndef LOGUTILITIES_LOGWRITERCHAIN_HPP
#define LOGUTILITIES_LOGWRITERCHAIN_HPP

#include "LogChain.hpp"
#include "LogWriterBase.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Writer
        {

            /**
             *  @brief
             *    Log writer object that performs sequential writes to each
             *    link in a chain of writers on a single write to the chain.
             *
             *  @ingroup writer
             *
             */
            class Chain :
                public Log::Chain<Base>,
                public Base
            {
            public:
                Chain(void);
                virtual ~Chain(void);

                // Write at the specified level.

                virtual void Write(Level inLevel, const char * inMessage);

                // Write with no ident at level zero (0).

                virtual void Write(const char * inMessage);
            };

        }; // namespace Writer

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGWRITERCHAIN_HPP */
