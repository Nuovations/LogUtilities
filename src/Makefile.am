#
#    Copyright (c) 2021 Nuovation System Designs, LLC. All Rights Reserved.
#    Copyright 2016 Nest Labs Inc. All Rights Reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

#
#    Description:
#      This file is the GNU automake template for the Nuovations Logging Utilities.
#

include $(abs_top_nlbuild_autotools_dir)/automake/pre.am

EXTRA_DIST                          = \
    .clang-format                     \
    $(NULL)

lib_LTLIBRARIES                     = libLogUtilities.la

libLogUtilities_la_CPPFLAGS         = \
    -I$(top_builddir)/include         \
    -I$(top_srcdir)/include           \
    $(NULL)

libLogUtilities_la_SOURCES          = \
    LogFilterAlways.cpp               \
    LogFilterBase.cpp                 \
    LogFilterBoolean.cpp              \
    LogFilterChain.cpp                \
    LogFilterLevel.cpp                \
    LogFilterNever.cpp                \
    LogFilterQuiet.cpp                \
    LogFormatterBase.cpp              \
    LogFormatterPlain.cpp             \
    LogFormatterStamped.cpp           \
    LogFunctionUtilities.cpp          \
    LogGlobals.cpp                    \
    LogIndenterBase.cpp               \
    LogIndenterNone.cpp               \
    LogIndenterSpace.cpp              \
    LogIndenterString.cpp             \
    LogIndenterTab.cpp                \
    LogLogger.cpp                     \
    LogMemoryUtilities.cpp            \
    LogWriterASL.cpp                  \
    LogWriterBase.cpp                 \
    LogWriterChain.cpp                \
    LogWriterDescriptor.cpp           \
    LogWriterPath.cpp                 \
    LogWriterStderr.cpp               \
    LogWriterStdio.cpp                \
    LogWriterStdout.cpp               \
    LogWriterSyslog.cpp               \
    $(NULL)

if LOGUTILITIES_BUILD_COVERAGE
CLEANFILES                          = $(wildcard *.gcda *.gcno)
endif # LOGUTILITIES_BUILD_COVERAGE

include $(abs_top_nlbuild_autotools_dir)/automake/post.am
