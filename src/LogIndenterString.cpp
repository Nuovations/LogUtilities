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
 *      This file implements a Nuovations Log Utilities concrete indenter
 *      implementation that indents logged messages using an arbitrary
 *      string, character, or repeated characters.
 */

#include <string>
#include <vector>

using namespace std;

#include <LogUtilities/LogIndenterString.hpp>

namespace Nuovations
{

namespace Log
{

namespace Indenter
{

static const String::Flags kFlagsDefault = String::Flags::kFirst;

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the indenter with the specified
 *  NULL-terminated C string to use as the indent and only indents
 *  the first line of a log message.
 *
 *  @param[in]  inString  A pointer to the NULL-terminated C string
 *                        to use as the indent.
 *
 */
String::String(const char * inString) :
    mString(inString),
    mFlags(kFlagsDefault)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the indenter with the specified C++
 *  Standard Template Library (STL) string to use as the indent and
 *  only indents the first line of a log message.
 *
 *  @param[in]  inString  An immutable reference to the C++ STL string
 *                        to use as the indent.
 *
 */
String::String(const std::string & inString) :
    mString(inString),
    mFlags(kFlagsDefault)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the indenter with the single,
 *  specified character to use as the indent and only indents the
 *  first line of a log message.
 *
 *  @param[in]  inCharacter  The character to use as the indent.
 *
 */
String::String(char inCharacter) :
    mString(1, inCharacter),
    mFlags(kFlagsDefault)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the indenter with the specified
 *  number of characters to use as the indent and only indents the
 *  first line of a log message.
 *
 *  @param[in]  inCharacter  The character to use as the indent.
 *  @param[in]  inCount      The number of @a inCharacter to use
 *                           as the indent.
 *
 */
String::String(char inCharacter, size_t inCount) :
    mString(inCount, inCharacter),
    mFlags(kFlagsDefault)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the indenter with the specified
 *  NULL-terminated C string to use as the indent and indents with the
 *  specified behavior flags.
 *
 *  @param[in]  inString  A pointer to the NULL-terminated C string
 *                        to use as the indent.
 *  @param[in]  inFlags   The behavior flags indicating how a log
 *                        message should be indented.
 *
 */
String::String(const char * inString, Flags inFlags) :
    mString(inString),
    mFlags(inFlags)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the indenter with the specified C++
 *  Standard Template Library (STL) string to use as the indent and
 *  only indents with the specified behavior flags.
 *
 *  @param[in]  inString  An immutable reference to the C++ STL string
 *                        to use as the indent.
 *  @param[in]  inFlags   The behavior flags indicating how a log
 *                        message should be indented.
 *
 */
String::String(const std::string & inString, Flags inFlags) :
    mString(inString),
    mFlags(inFlags)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the indenter with the single,
 *  specified character to use as the indent and only indents with the
 *  specified behavior flags.
 *
 *  @param[in]  inCharacter  The character to use as the indent.
 *  @param[in]  inFlags      The behavior flags indicating how a log
 *                           message should be indented.
 *
 */
String::String(char inCharacter, Flags inFlags) :
    mString(1, inCharacter),
    mFlags(inFlags)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the indenter with the specified
 *  number of characters to use as the indent and only indents the
 *  first line of a log message.
 *
 *  @param[in]  inCharacter  The character to use as the indent.
 *  @param[in]  inCount      The number of @a inCharacter to use
 *                           as the indent.
 *  @param[in]  inFlags      The behavior flags indicating how a log
 *                           message should be indented.
 *
 */
String::String(char inCharacter, size_t inCount, Flags inFlags) :
    mString(inCount, inCharacter),
    mFlags(inFlags)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
String::~String(void)
{
    return;
}

/**
 *  @brief
 *    Inserts the specified indent into the provided log message at
 *    the indicated position.
 *
 *  @param[in]  inIndent    An immutable reference to the indent to
 *                          insert.
 *  @param[in]  inMessage   A reference to the log message to indent.
 *  @param[in]  inPosition  The position in @a inMessage to insert @a
 *                          inIndent at.
 *
 */
void
String::Indent(const string & inIndent,
               string &       inMessage,
               size_t         inPosition) const
{
    inMessage.insert(inPosition, inIndent);
}

/**
 *  @brief
 *    Inserts the specified indent into the provided log message at
 *    the indicated positions.
 *
 *  @param[in]  inIndent     An immutable reference to the indent to
 *                           insert.
 *  @param[in]  inMessage    A reference to the log message to indent.
 *  @param[in]  inPositions  A reference to the the positions in @a
 *                           inMessage to insert @a inIndent at.
 *
 *  @returns
 *    A reference to the indented log message.
 *
 */
string &
String::Indent(const string &   inIndent,
               string &         inMessage,
               vector<size_t> & inPositions) const
{
    vector<size_t>::const_iterator current = inPositions.begin();
    vector<size_t>::const_iterator end     = inPositions.end();

    // Iterate over each indent position, inserting the indent string
    // into the message string at that position.

    while (current != end) {
        Indent(inIndent, inMessage, *current);

        std::advance(current, 1);
    }

    return (inMessage);
}

/**
 *  @brief
 *    Indent the provided message to a caller-specified level.
 *
 *  @param[in]  inIndent   The level of indendation desired for the
 *                         provided log message.
 *  @param[in]  inMessage  A reference to the log message to
 *                         indent.
 *
 *  @returns
 *     A reference to the indented string.
 *
 */
string &
String::Indent(Log::Indent inIndent, string & inMessage)
{
    vector<size_t> thePositions;
    string         theIndent;
    const size_t   theSize = inMessage.size();

    // If we are at indent level zero (0) or if the message is empty,
    // then there's nothing to indent. Simply return the message as
    // is.

    if (inIndent == 0 || theSize == 0) {
        return (inMessage);
    }

    // Otherwise, we will be indenting something. Prebuild the indent
    // string since this needs to only be done once regardless of how
    // many lines we are indenting.

    while (inIndent--) {
        theIndent += mString;
    }

    // If we were asking to indent every line, work our way from the
    // end of the string to the beginning, finding new lines
    // characters that demarcate the start of a new line to indent.

    if (mFlags == Flags::kEvery) {
        size_t thePosition = string::npos;

        do {
            // Find, in reverse, the last new line in the message
            // starting at the specified position.

            thePosition = inMessage.find_last_of('\n', thePosition);

            // If we found one, push the position one character after
            // the position (the first character on the new line) onto
            // the insertion container if it wasn't a terminating new
            // line. Then, decrement the position so we don't refind
            // the new line we just found.

            if (thePosition != string::npos) {
                if (thePosition < (theSize - 1)) {
                    thePositions.push_back(thePosition + 1);
                }

                thePosition--;
            }

        } while (thePosition != string::npos);
    }

    // We always indent the first line, so push the start-of-
    // string position onto the insertion container.

    thePositions.push_back(0);

    // Return the string, indented at the found insertion locations.

    return (Indent(theIndent, inMessage, thePositions));
}

}; // namespace Indenter

}; // namespace Log

}; // namespace Nuovations
