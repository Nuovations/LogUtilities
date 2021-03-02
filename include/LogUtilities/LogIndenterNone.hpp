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
 *      implementation that never indents logged messages.
 */

#ifndef LOGUTILITIES_LOGINDENTERNONE_HPP
#define LOGUTILITIES_LOGINDENTERNONE_HPP

#include "LogIndenterBase.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Indenter
        {

            /**
             *  @brief
             *    Log indenter object that never indents logged messages.
             *
             *  @ingroup indenter
             *
             */
            class None :
                public Base
            {
            public:
                None(void);
                virtual ~None(void);

                virtual std::string & Indent(Log::Indent inIndent,
                                             std::string &inMessage);
            };

        }; // namespace Indenter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGINDENTERNONE_HPP */
