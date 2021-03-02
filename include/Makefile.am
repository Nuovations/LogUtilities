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
#      This file is the GNU automake template for the Nuovations
#      Logging Utilities Library/Framework public headers.
#

include $(abs_top_nlbuild_autotools_dir)/automake/pre.am

EXTRA_DIST                              = \
    .clang-format                         \
    $(NULL)

LogUtilities_includedir                 = ${includedir}/LogUtilities

LogUtilities_include_HEADERS            = \
    LogUtilities/LogChain.hpp             \
    LogUtilities/LogFilter.hpp            \
    LogUtilities/LogFilterAlways.hpp      \
    LogUtilities/LogFilterBase.hpp        \
    LogUtilities/LogFilterBoolean.hpp     \
    LogUtilities/LogFilterChain.hpp       \
    LogUtilities/LogFilterLevel.hpp       \
    LogUtilities/LogFilterNever.hpp       \
    LogUtilities/LogFilterQuiet.hpp       \
    LogUtilities/LogFormatter.hpp         \
    LogUtilities/LogFormatterBase.hpp     \
    LogUtilities/LogFormatterPlain.hpp    \
    LogUtilities/LogFormatterStamped.hpp  \
    LogUtilities/LogFunctionUtilities.hpp \
    LogUtilities/LogGlobals.hpp           \
    LogUtilities/LogIndenter.hpp          \
    LogUtilities/LogIndenterBase.hpp      \
    LogUtilities/LogIndenterNone.hpp      \
    LogUtilities/LogIndenterSpace.hpp     \
    LogUtilities/LogIndenterString.hpp    \
    LogUtilities/LogIndenterTab.hpp       \
    LogUtilities/LogLogger.hpp            \
    LogUtilities/LogMacros.hpp            \
    LogUtilities/LogMemoryUtilities.hpp   \
    LogUtilities/LogTypes.hpp             \
    LogUtilities/LogUtilities.hpp         \
    LogUtilities/LogWriter.hpp            \
    LogUtilities/LogWriterASL.hpp         \
    LogUtilities/LogWriterBase.hpp        \
    LogUtilities/LogWriterChain.hpp       \
    LogUtilities/LogWriterDescriptor.hpp  \
    LogUtilities/LogWriterPath.hpp        \
    LogUtilities/LogWriterStderr.hpp      \
    LogUtilities/LogWriterStdio.hpp       \
    LogUtilities/LogWriterStdout.hpp      \
    LogUtilities/LogWriterSyslog.hpp      \
    $(NULL)

install-headers: install-includeHEADERS

include $(abs_top_nlbuild_autotools_dir)/automake/post.am
