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
#      This file is the GNU automake template for the Nuovations Logging
#      Utilities Library/Framework unit tests.
#

include $(abs_top_nlbuild_autotools_dir)/automake/pre.am

#
# Local headers to build against and distribute but not to install
# since they are not part of the package.
#
noinst_HEADERS                                 = \
    TestLogUtilitiesBasis.hpp                    \
    $(NULL)

#
# Other files we do want to distribute with the package.
#
EXTRA_DIST                                     = \
    $(NULL)

if LOGUTILITIES_BUILD_TESTS
# C preprocessor option flags that will apply to all compiled objects in this
# makefile.

AM_CPPFLAGS                                    = \
    -I$(top_srcdir)/include                      \
    $(CPPUNIT_CPPFLAGS)                          \
    $(NULL)

DEBUG_CPPFLAGS                                 = \
    $(AM_CPPFLAGS)                               \
    -DDEBUG=1                                    \
    $(NULL)

NONDEBUG_CPPFLAGS                              = \
    $(AM_CPPFLAGS)                               \
    -DNDEBUG=1                                   \
    $(NULL)

COMMON_LDADD                                   = \
    $(top_builddir)/src/libLogUtilities.la       \
    $(CPPUNIT_LDFLAGS) $(CPPUNIT_LIBS)           \
    $(NULL)

# Test applications that should be run when the 'check' target is run.

check_PROGRAMS                                 = \
    TestLogChain                                 \
    TestLogFilterBoolean                         \
    TestLogFilterAlways                          \
    TestLogFilterLevel                           \
    TestLogFilterNever                           \
    TestLogFilterQuiet                           \
    TestLogFilterChain                           \
    TestLogFormatterPlain                        \
    TestLogFormatterStamped                      \
    TestLogFunctionUtilities                     \
    TestLogGlobals                               \
    TestLogIndenterNone                          \
    TestLogIndenterSpace                         \
    TestLogIndenterString                        \
    TestLogIndenterTab                           \
    TestLogLogger                                \
    TestLogMacrosDebug                           \
    TestLogMacrosNonDebug                        \
    TestLogMemoryUtilities                       \
    TestLogWriterChain                           \
    TestLogWriterDescriptor                      \
    TestLogWriterPath                            \
    TestLogWriterStderr                          \
    TestLogWriterStdio                           \
    TestLogWriterStdout                          \
    TestLogWriterSyslog                          \
    $(NULL)

# Test applications and scripts that should be built and run when the
# 'check' target is run.

TESTS                                          = \
    $(check_PROGRAMS)                            \
    $(NULL)

# The additional environment variables and their values that will be
# made available to all programs and scripts in TESTS.

TESTS_ENVIRONMENT                              = \
    $(NULL)

# Source, compiler, and linker options for test programs.

TestLogChain_LDADD                             = $(COMMON_LDADD)
TestLogChain_SOURCES                           = TestDriver.cpp               \
                                                 TestLogChain.cpp

TestLogFilterAlways_LDADD                      = $(COMMON_LDADD)
TestLogFilterAlways_SOURCES                    = TestDriver.cpp               \
                                                 TestLogFilterAlways.cpp

TestLogFilterBoolean_LDADD                     = $(COMMON_LDADD)
TestLogFilterBoolean_SOURCES                   = TestDriver.cpp               \
                                                 TestLogFilterBoolean.cpp

TestLogFilterChain_LDADD                       = $(COMMON_LDADD)
TestLogFilterChain_SOURCES                     = TestDriver.cpp               \
                                                 TestLogFilterChain.cpp

TestLogFilterLevel_LDADD                       = $(COMMON_LDADD)
TestLogFilterLevel_SOURCES                     = TestDriver.cpp               \
                                                 TestLogFilterLevel.cpp

TestLogFilterNever_LDADD                       = $(COMMON_LDADD)
TestLogFilterNever_SOURCES                     = TestDriver.cpp               \
                                                 TestLogFilterNever.cpp

TestLogFilterQuiet_LDADD                       = $(COMMON_LDADD)
TestLogFilterQuiet_SOURCES                     = TestDriver.cpp               \
                                                 TestLogFilterQuiet.cpp

TestLogFormatterPlain_LDADD                    = $(COMMON_LDADD)
TestLogFormatterPlain_SOURCES                  = TestDriver.cpp               \
                                                 TestLogFormatterPlain.cpp

TestLogFormatterStamped_LDADD                  = $(COMMON_LDADD)
TestLogFormatterStamped_SOURCES                = TestDriver.cpp               \
                                                 TestLogFormatterStamped.cpp

TestLogFunctionUtilities_LDADD                 = $(COMMON_LDADD)
TestLogFunctionUtilities_SOURCES               = TestDriver.cpp               \
                                                 TestLogUtilitiesBasis.cpp    \
                                                 TestLogFunctionUtilities.cpp

TestLogGlobals_LDADD                           = $(COMMON_LDADD)
TestLogGlobals_SOURCES                         = TestDriver.cpp               \
                                                 TestLogGlobals.cpp

TestLogIndenterNone_LDADD                      = $(COMMON_LDADD)
TestLogIndenterNone_SOURCES                    = TestDriver.cpp               \
                                                 TestLogIndenterNone.cpp

TestLogIndenterSpace_LDADD                     = $(COMMON_LDADD)
TestLogIndenterSpace_SOURCES                   = TestDriver.cpp               \
                                                 TestLogIndenterSpace.cpp

TestLogIndenterString_LDADD                    = $(COMMON_LDADD)
TestLogIndenterString_SOURCES                  = TestDriver.cpp               \
                                                 TestLogIndenterString.cpp

TestLogIndenterTab_LDADD                       = $(COMMON_LDADD)
TestLogIndenterTab_SOURCES                     = TestDriver.cpp               \
                                                 TestLogIndenterTab.cpp

TestLogLogger_LDADD                            = $(COMMON_LDADD)
TestLogLogger_SOURCES                          = TestDriver.cpp               \
                                                 TestLogUtilitiesBasis.cpp    \
                                                 TestLogLogger.cpp

TestLogMacrosDebug_CPPFLAGS                    = $(DEBUG_CPPFLAGS)
TestLogMacrosDebug_LDADD                       = $(COMMON_LDADD)
TestLogMacrosDebug_SOURCES                     = TestDriver.cpp               \
                                                 TestLogMacros.cpp

TestLogMacrosNonDebug_CPPFLAGS                 = $(NONDEBUG_CPPFLAGS)
TestLogMacrosNonDebug_LDADD                    = $(COMMON_LDADD)
TestLogMacrosNonDebug_SOURCES                  = TestDriver.cpp               \
                                                 TestLogMacros.cpp

TestLogMemoryUtilities_LDADD                   = $(COMMON_LDADD)
TestLogMemoryUtilities_SOURCES                 = TestDriver.cpp               \
                                                 TestLogUtilitiesBasis.cpp    \
                                                 TestLogMemoryUtilities.cpp

TestLogWriterChain_LDADD                       = $(COMMON_LDADD)
TestLogWriterChain_SOURCES                     = TestDriver.cpp               \
                                                 TestLogUtilitiesBasis.cpp    \
                                                 TestLogWriterChain.cpp

TestLogWriterDescriptor_LDADD                  = $(COMMON_LDADD)
TestLogWriterDescriptor_SOURCES                = TestDriver.cpp               \
                                                 TestLogUtilitiesBasis.cpp    \
                                                 TestLogWriterDescriptor.cpp

TestLogWriterPath_LDADD                        = $(COMMON_LDADD)
TestLogWriterPath_SOURCES                      = TestDriver.cpp               \
                                                 TestLogUtilitiesBasis.cpp    \
                                                 TestLogWriterPath.cpp

TestLogWriterStderr_LDADD                      = $(COMMON_LDADD)
TestLogWriterStderr_SOURCES                    = TestDriver.cpp               \
                                                 TestLogUtilitiesBasis.cpp    \
                                                 TestLogWriterStderr.cpp

TestLogWriterStdio_LDADD                       = $(COMMON_LDADD)
TestLogWriterStdio_SOURCES                     = TestDriver.cpp               \
                                                 TestLogUtilitiesBasis.cpp    \
                                                 TestLogWriterStdio.cpp

TestLogWriterStdout_LDADD                      = $(COMMON_LDADD)
TestLogWriterStdout_SOURCES                    = TestDriver.cpp               \
                                                 TestLogUtilitiesBasis.cpp    \
                                                 TestLogWriterStdout.cpp

TestLogWriterSyslog_LDADD                      = $(COMMON_LDADD)
TestLogWriterSyslog_SOURCES                    = TestDriver.cpp               \
                                                 TestLogUtilitiesBasis.cpp    \
                                                 TestLogWriterSyslog.cpp

if LOGUTILITIES_BUILD_COVERAGE
CLEANFILES                                     = $(wildcard *.gcda *.gcno *.info)

if LOGUTILITIES_BUILD_COVERAGE_REPORTS
# The bundle should positively be qualified with the absolute build
# path. Otherwise, VPATH will get auto-prefixed to it if there is
# already such a directory in the non-colocated source tree.

LOGUTILITIES_COVERAGE_BUNDLE                           = ${abs_builddir}/${PACKAGE}${NL_COVERAGE_BUNDLE_SUFFIX}
LOGUTILITIES_COVERAGE_INFO                             = ${LOGUTILITIES_COVERAGE_BUNDLE}/${PACKAGE}${NL_COVERAGE_INFO_SUFFIX}

$(LOGUTILITIES_COVERAGE_BUNDLE):
	$(call create-directory)

# Generate the coverage report, filtering out platform and system
# directories and this test directory.

INCLUDE_PATHS    := $(subst -I,,$(sort $(BOOST_CPPFLAGS) $(CPPUNIT_CPPFLAGS)))
INCLUDE_PATTERNS := $(if $(INCLUDE_PATHS),$(addsuffix *,$(INCLUDE_PATHS)),)
XCODE_PATH       := $(shell xcode-select -p)
XCODE_PATTERN    := $(if $(XCODE_PATH),$(addsuffix *,$(XCODE_PATH)),)

$(LOGUTILITIES_COVERAGE_INFO): check-local | $(LOGUTILITIES_COVERAGE_BUNDLE)
	$(call generate-coverage-report-with-filter,${top_builddir},${INCLUDE_PATTERNS} ${XCODE_PATTERN} *${subdir}*)

coverage-local: $(LOGUTILITIES_COVERAGE_INFO)

clean-local: clean-local-coverage

.PHONY: clean-local-coverage
clean-local-coverage:
	-$(AM_V_at)rm -rf $(LOGUTILITIES_COVERAGE_BUNDLE)
endif # LOGUTILITIES_BUILD_COVERAGE_REPORTS
endif # LOGUTILITIES_BUILD_COVERAGE
endif # LOGUTILITIES_BUILD_TESTS

include $(abs_top_nlbuild_autotools_dir)/automake/post.am
