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
 *      This file implements Nuovations Log Utilities objects that may be
 *      used for tracing the function or method execution of program
 *      flow.
 */

#include <LogUtilities/LogFunctionUtilities.hpp>
#include <LogUtilities/LogGlobals.hpp>

namespace Nuovations
{

namespace Log
{

namespace Utilities
{

namespace Function
{

static const char * kEnter = "-->";
static const char * kExit  = "<--";

static const Log::Indent kIndentDefault = 0;
static const Log::Level  kLevelDefault  = 0;

unsigned int ScopedTracer::sDepth = 0;

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the tracer with the specified
 *  NULL-terminated C string to use as the name of the function or
 *  method to trace at the default log level and with the default
 *  entry and exit markers.
 *
 *  @param[in]  inName  A pointer to the NULL-terminated C string
 *                      to use as the function or method name to
 *                      trace.
 *
 */
TracerBase::TracerBase(const char * inName) :
    TracerBase(inName, kLevelDefault, kEnter, kExit)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the tracer with the specified
 *  NULL-terminated C string to use as the name of the function or
 *  method to trace at the specified log level and with the default
 *  entry and exit markers.
 *
 *  @param[in]  inName   A pointer to the NULL-terminated C string
 *                       to use as the function or method name to
 *                       trace.
 *  @param[in]  inLevel  The log level at which the declared tracer
 *                       will log.
 *
 */
TracerBase::TracerBase(const char * inName, Log::Level inLevel) :
    TracerBase(inName, inLevel, kEnter, kExit)
{
    return;
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the tracer with the specified
 *  NULL-terminated C string to use as the name of the function or
 *  method to trace at the specified log level with the provided entry
 *  and exit markers.
 *
 *  @param[in]  inName   A pointer to the NULL-terminated C string
 *                       to use as the function or method name to
 *                       trace.
 *  @param[in]  inLevel  The log level at which the declared tracer
 *                       will log.
 *  @param[in]  inEnter  A pointer to the NULL-terminated C string
 *                       to use as the tracer function or method entry
 *                       marker.
 *  @param[in]  inExit   A pointer to the NULL-terminated C string
 *                       to use as the tracer function or method exit
 *                       marker.
 *
 */
TracerBase::TracerBase(const char * inName,
                       Log::Level   inLevel,
                       const char * inEnter,
                       const char * inExit) :
    mName(inName),
    mLevel(inLevel),
    mEnter(inEnter),
    mExit(inExit)
{
    return;
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
TracerBase::~TracerBase(void)
{
    return;
}

/**
 *  @brief
 *    Trigger the tracer entry point.
 *
 *    This triggers the tracer entry point, logging a tracing entry
 *    message with the specified indent.
 *
 *  @param[in]  inIndent  The level of indendation desired for the
 *                        tracing entry log message.
 *
 */
void
TracerBase::Enter(Log::Indent inIndent) const
{
    Log(inIndent, mEnter);
}

/**
 *  @brief
 *    Trigger the tracer exit point.
 *
 *    This triggers the tracer exit point, logging a tracing exit
 *    message with the specified indent.
 *
 *  @param[in]  inIndent  The level of indendation desired for the
 *                        tracing exit log message.
 *
 */
void
TracerBase::Exit(Log::Indent inIndent) const
{
    Log(inIndent, mExit);
}

/**
 *  @brief
 *    Log a tracer entry or exit message.
 *
 *  This writes a log message for the function or method name the
 *  tracer was instantiated with at the requested indentation with the
 *  specified marker prior to the function or method name.
 *
 *  @param[in]  inIndent  The level of indendation desired for the
 *                        tracing exit log message.
 *  @param[in]  inMarker  A pointer to the NULL-terminated C string
 *                        to log as a marker preceding the function or
 *                        method name to trace.
 *
 */
void
TracerBase::Log(Log::Indent inIndent, const char * inMarker) const
{
    Log::Debug().Write(inIndent, mLevel, "%s %s\n", inMarker, mName);
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the non-scoped, stateless tracer
 *  with the specified NULL-terminated C string to use as the name of
 *  the function or method to trace at the default log level.
 *
 *  @note
 *    Instantiation also initiates function or method entry tracing,
 *    so placement of the tracer is tied directly to when and where in
 *    the function or method tracing begins.
 *
 *  @param[in]  inName  A pointer to the NULL-terminated C string
 *                      to use as the function or method name to
 *                      trace.
 *
 */
Tracer::Tracer(const char * inName) :
    TracerBase(inName)
{
    Enter();
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the non-scoped, stateless tracer
 *  with the specified NULL-terminated C string to use as the name of
 *  the function or method to trace at the specified log level.
 *
 *  @note
 *    Instantiation also initiates function or method entry tracing,
 *    so placement of the tracer is tied directly to when and where in
 *    the function or method tracing begins.
 *
 *  @param[in]  inName   A pointer to the NULL-terminated C string
 *                       to use as the function or method name to
 *                       trace.
 *  @param[in]  inLevel  The log level at which the declared tracer
 *                       will log.
 *
 */
Tracer::Tracer(const char * inName, Log::Level inLevel) :
    TracerBase(inName, inLevel)
{
    Enter();
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
Tracer::~Tracer(void)
{
    Exit();
}

/**
 *  @brief
 *    Trigger the non-scoped tracer entry point.
 *
 *    This triggers the non-scoped tracer entry point, logging a
 *    tracing entry message with a default indent.
 *
 */
void
Tracer::Enter(void) const
{
    TracerBase::Enter(kIndentDefault);
}

/**
 *  @brief
 *    Trigger the non-scoped tracer exit point.
 *
 *    This triggers the non-scoped tracer exit point, logging a
 *    tracing exit message with a default indent.
 *
 */
void
Tracer::Exit(void) const
{
    TracerBase::Exit(kIndentDefault);
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the scoped, stateful tracer with the
 *  specified NULL-terminated C string to use as the name of the
 *  function or method to trace at the default log level.
 *
 *  @note
 *    Instantiation also initiates function or method entry tracing,
 *    so placement of the tracer is tied directly to when and where in
 *    the function or method tracing begins.
 *
 *  @param[in]  inName  A pointer to the NULL-terminated C string
 *                      to use as the function or method name to
 *                      trace.
 *
 */
ScopedTracer::ScopedTracer(const char * inName) :
    TracerBase(inName)
{
    Enter();
}

/**
 *  @brief
 *    This is a class constructor.
 *
 *  This constructor instantiates the scoped, stateful tracer with the
 *  specified NULL-terminated C string to use as the name of the
 *  function or method to trace at the specified log level.
 *
 *  @note
 *    Instantiation also initiates function or method entry tracing,
 *    so placement of the tracer is tied directly to when and where in
 *    the function or method tracing begins.
 *
 *  @param[in]  inName   A pointer to the NULL-terminated C string
 *                       to use as the function or method name to
 *                       trace.
 *  @param[in]  inLevel  The log level at which the declared tracer
 *                       will log.
 *
 */
ScopedTracer::ScopedTracer(const char * inName, Log::Level inLevel) :
    TracerBase(inName, inLevel)
{
    Enter();
}

/**
 *  @brief
 *    This is the class destructor.
 *
 */
ScopedTracer::~ScopedTracer(void)
{
    Exit();
}

/**
 *  @brief
 *    Trigger the scoped tracer entry point.
 *
 *    This triggers the scoped tracer entry point, logging a tracing
 *    entry message with a default indent while also increasing the
 *    call depth state by one (1) such that subsequent triggers log
 *    one indent level deeper.
 *
 *  @note This method is not thread-safe.
 *
 */
void
ScopedTracer::Enter(void) const
{
    TracerBase::Enter(sDepth++);
}

/**
 *  @brief
 *    Trigger the scoped tracer exit point.
 *
 *    This triggers the scoped tracer exit point, logging a tracing
 *    exit message with a default indent while also decreasing the
 *    call depth state by one (1) such that subsequent triggers log
 *    one indent level shallower.
 *
 *  @note This method is not thread-safe.
 *
 */
void
ScopedTracer::Exit(void) const
{
    TracerBase::Exit(--sDepth);
}

/**
 *  @brief
 *    Return the current call tracing depth.
 *
 *  @returns
 *    The current call tracing depth.
 *
 *  @note This method is not thread-safe.
 *
 */
unsigned int
ScopedTracer::GetDepth(void)
{
    return (sDepth);
}

}; // namespace Function

}; // namespace Utilities

}; // namespace Log

}; // namespace Nuovations
