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
 *      This file defines a Nuovations Log Utilities concrete indenter
 *      implementation that indents logged messages using a tab (0x09)
 *      character.
 */

#ifndef LOGUTILITIES_LOGINDENTERTAB_HPP
#define LOGUTILITIES_LOGINDENTERTAB_HPP

#include "LogIndenterString.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Indenter
        {

            /**
             *  @brief
             *    Log indenter object that indents logged messages
             *    using a tab (0x09) character.
             *
             *  @ingroup indenter
             *
             */
            class Tab :
                public String
            {
            public:
                Tab(void);
                Tab(Flags inFlags);
                virtual ~Tab(void);
            };

        }; // namespace Indenter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGINDENTERTAB_HPP */
