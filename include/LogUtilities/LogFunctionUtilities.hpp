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
 *      This file defines Nuovations Log Utilities objects that may be
 *      used for tracing the function or method execution of program
 *      flow.
 */

#ifndef LOGUTILITIES_LOGFUNCTIONUTILITIES_HPP
#define LOGUTILITIES_LOGFUNCTIONUTILITIES_HPP

#include "LogTypes.hpp"

namespace Nuovations
{

    namespace Log
    {

        namespace Utilities
        {

            namespace Function
            {

                /**
                 *  @brief
                 *    Abstract, base function or method tracer logging
                 *    object.
                 *
                 *  This object may be used to build concrete,
                 *  instantiable objects that trace the function or
                 *  method execution of program flow. Such objects
                 *  will, when logging is configured at or above the
                 *  specified level, log a preamble before the
                 *  function or method name or signature on entry and
                 *  then will log a preamble before the function or
                 *  method name or signature on exit.
                 *
                 *  @ingroup function-utilities utilities
                 *
                 */
                class TracerBase
                {
                public:
                    virtual ~TracerBase(void);

                protected:
                    TracerBase(const char * inName);
                    TracerBase(const char * inName, Log::Level inLevel);
                    TracerBase(const char * inName,
                               Log::Level   inLevel,
                               const char * inEnter,
                               const char * inExit);

                private:
                    virtual void Enter(void) const = 0;
                    virtual void Exit(void) const  = 0;

                protected:
                    void Enter(Log::Indent inIndent) const;
                    void Exit(Log::Indent inIndent) const;

                    void Log(Log::Indent inIndent, const char * inMarker) const;

                private:
                    const char * mName;  //!< Name of the function or function signature to be traced.
                    Log::Level   mLevel; //!< Level at which the tracer should be logged.
                    const char * mEnter; //!< Log message preamble written before @a mName when the function or method is entered.
                    const char * mExit;  //!< Log message preamble written before @a mName when the function or method is exited.
                };

                /**
                 *  @brief
                 *    Stateless, concrete function or method tracer
                 *    logging object.
                 *
                 *  This concrete object will trace the function or
                 *  method execution of program flow by, when logging
                 *  is configured at or above the specified level, log
                 *  a preamble before the function or method name or
                 *  signature on entry and then will log a preamble
                 *  before the function or method name or signature on
                 *  exit.
                 *
                 *  @ingroup function-utilities utilities
                 *
                 */
                class Tracer :
                    public TracerBase
                {
                public:
                    Tracer(const char * inName);
                    Tracer(const char * inName, Log::Level inLevel);
                    virtual ~Tracer(void);

                private:
                    virtual void Enter(void) const;
                    virtual void Exit(void) const;
                };

                /**
                 *  @brief
                 *    Stateful, concrete function or method tracer
                 *    logging object.
                 *
                 *  This concrete object will trace the function or
                 *  method execution of program flow by, when logging
                 *  is configured at or above the specified level, log
                 *  a preamble before the function or method name or
                 *  signature on entry and then will log a preamble
                 *  before the function or method name or signature on
                 *  exit.
                 *
                 *  This object differs from @a Tracer in that each
                 *  entry log message is indented by one level greater
                 *  than that before it as function or method
                 *  invocations deepen in the call stack. Similarly,
                 *  as the function or method invocations unwind and
                 *  become shallower, the log messages decrease.
                 *
                 *  @note This object is not thread-safe.
                 *
                 *  @ingroup function-utilities utilities
                 *
                 */
                class ScopedTracer :
                    public TracerBase
                {
                public:
                    ScopedTracer(const char * inName);
                    ScopedTracer(const char * inName, Log::Level inLevel);
                    virtual ~ScopedTracer(void);

                    static unsigned int GetDepth(void);

                private:
                    virtual void Enter(void) const;
                    virtual void Exit(void) const;

                private:
                    static unsigned int sDepth; //!< Stateful function or method call depth.
                };

            }; // namespace Function

        }; // namespace Utilities

    }; // namespace Log

}; // namespace Nuovations

/**
 *  @def DeclareTracerAtLevel(inType, inName, inLevel)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, an immutable (that is, const) function tracer
 *    object of the provided type at the specified log level.
 *
 *  @param[in]  inType   The tracer type to declare.
 *  @param[in]  inName   The name of the tracer to declare. This is
 *                       the name of the tracer stack or member
 *                       variable.
 *  @param[in]  inLevel  The log level at which the declared tracer
 *                       will log.
 *
 *  @sa Tracer
 *  @sa ScopedTracer
 *  @sa DeclareTracer
 *
 *  @ingroup function-utilities
 *
 */

/**
 *  @def DeclareTracer(inType, inName)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, an immutable (that is, const) function tracer
 *    object of the provided type at the default log level.
 *
 *  @param[in]  inType   The tracer type to declare.
 *  @param[in]  inName   The name of the tracer to declare. This is
 *                       the name of the tracer stack or member
 *                       variable.
 *
 *  @sa Tracer
 *  @sa ScopedTracer
 *  @sa DeclareTracerAtLevel
 *
 *  @ingroup function-utilities
 *
 */
#if defined(DEBUG) && !defined(NDEBUG)
# define DeclareTracerAtLevel(inType, inName, inLevel) \
    const inType inName(__PRETTY_FUNCTION__, inLevel)
# define DeclareTracer(inType, inName)                 \
    const inType inName(__PRETTY_FUNCTION__)
#else
# define DeclareTracerAtLevel(inType, inName, inLevel)
# define DeclareTracer(inType, inName)
#endif

/**
 *  @def DeclareFunctionTracerAtLevel(inName, inLevel)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, an immutable (that is, const), non-scoped function
 *    tracer object at the specified log level.
 *
 *  @param[in]  inName   The name of the tracer to declare. This is
 *                       the name of the tracer stack or member
 *                       variable.
 *  @param[in]  inLevel  The log level at which the declared tracer
 *                       will log.
 *
 *  @sa DeclareFunctionTracer
 *  @sa DeclareScopedFunctionTracerAtLevel
 *  @sa DeclareScopedFunctionTracer
 *  @sa Tracer
 *  @sa ScopedTracer
 *
 *  @ingroup function-utilities
 *
 */
#define DeclareFunctionTracerAtLevel(inName, inLevel)                          \
    DeclareTracerAtLevel(Nuovations::Log::Utilities::Function::Tracer,         \
                         inName,                                               \
                         inLevel)

/**
 *  @def DeclareFunctionTracer(inName)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, an immutable (that is, const), non-scoped function
 *    tracer object at the default log level.
 *
 *  @param[in]  inName   The name of the tracer to declare. This is
 *                       the name of the tracer stack or member
 *                       variable.
 *
 *  @sa DeclareFunctionTracerAtLevel
 *  @sa DeclareFunctionTracer
 *  @sa DeclareScopedFunctionTracerAtLevel
 *  @sa Tracer
 *  @sa ScopedTracer
 *
 *  @ingroup function-utilities
 *
 */
#define DeclareFunctionTracer(inName)                                          \
    DeclareTracer(Nuovations::Log::Utilities::Function::Tracer, inName)

/**
 *  @def DeclareScopedFunctionTracerAtLevel(inName, inLevel)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, an immutable (that is, const), scoped function
 *    tracer object at the specified log level.
 *
 *  @param[in]  inName   The name of the scoped tracer to declare. This
 *                       is the name of the tracer stack or member
 *                       variable.
 *  @param[in]  inLevel  The log level at which the declared tracer
 *                       will log.
 *
 *  @sa DeclareFunctionTracerAtLevel
 *  @sa DeclareFunctionTracer
 *  @sa DeclareScopedFunctionTracer
 *  @sa Tracer
 *  @sa ScopedTracer
 *
 *  @ingroup function-utilities
 *
 */
#define DeclareScopedFunctionTracerAtLevel(inName, inLevel)                    \
    DeclareTracerAtLevel(Nuovations::Log::Utilities::Function::ScopedTracer,   \
                         inName,                                               \
                         inLevel)

/**
 *  @def DeclareScopedFunctionTracer(inName)
 *
 *  @brief
 *    Conditionally declare, based on the preprocessor DEBUG and
 *    NDEBUG names, an immutable (that is, const), scoped function
 *    tracer object at the default log level.
 *
 *  @param[in]  inName   The name of the scoped tracer to declare. This
 *                       is the name of the tracer stack or member
 *                       variable.
 *
 *  @sa DeclareFunctionTracerAtLevel
 *  @sa DeclareFunctionTracer
 *  @sa DeclareScopedFunctionTracerAtLevel
 *  @sa Tracer
 *  @sa ScopedTracer
 *
 *  @ingroup function-utilities
 *
 */
#define DeclareScopedFunctionTracer(inName)                                    \
    DeclareTracer(Nuovations::Log::Utilities::Function::ScopedTracer, inName)

#endif // LOGUTILITIES_LOGFUNCTIONUTILITIES_HPP
