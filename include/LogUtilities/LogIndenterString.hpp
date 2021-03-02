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
 *      implementation that indents logged messages using an arbitrary
 *      string, character, or repeated characters.
 */

#ifndef LOGUTILITIES_LOGINDENTERSTRING_HPP
#define LOGUTILITIES_LOGINDENTERSTRING_HPP

#include <string>
#include <vector>

#include <stddef.h>
#include <stdint.h>

#include "LogIndenterBase.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Indenter
        {

            /**
             *  @brief
             *    Log indenter object that indents logged messages
             *    using an arbitrary string, character, or repeated
             *    characters.
             *
             *  @ingroup indenter
             *
             */
            class String :
                public Base
            {
            public:
                /**
                 *  @brief
                 *    String indentation behavior flags.
                 *
                 *    String indentation behavior flags which determine
                 *    how the indenter interacts with a message.
                 */
#if __cplusplus >= 201103L
                enum class Flags : uint8_t {
#else
                enum Flags {
#endif // __cplusplus >= 201103L
                    kFirst, //!< Only indent the first line of a message.
                    kEvery  //!< Indent every line of a message.
                };

            public:
                String(const char * inString);
                String(const std::string & inString);
                String(char inCharacter);
                String(char inCharacter, size_t inCount);
                String(const char * inString, Flags inFlags);
                String(const std::string & inString, Flags inFlags);
                String(char inCharacter, Flags inFlags);
                String(char inCharacter, size_t inCount, Flags inFlags);
                virtual ~String(void);

                virtual std::string & Indent(Log::Indent inIndent,
                                             std::string &inMessage);

            private:
                std::string & Indent(const std::string &   inIndent,
                                     std::string &         inMessage,
                                     std::vector<size_t> & inPositions) const;
                void          Indent(const std::string & inIndent,
                                     std::string &       inMessage,
                                     size_t              inPosition) const;

            private:
                const std::string mString; //!< The string to use for indentation.
                const Flags       mFlags;  //!< String indentation behavior flags.
            };

        }; // namespace Indenter

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGINDENTERSTRING_HPP */
