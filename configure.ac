#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#
#    Copyright (c) 2021-2024 Nuovation System Designs, LLC. All rights reserved.
#    Copyright 2016-2018 Nest Labs Inc. All Rights Reserved.
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
#      This file is the GNU autoconf input source file for
#      Nuovations Logging Utilities Library/Framework.
#

#
# Declare autoconf version requirements
#
AC_PREREQ([2.68])

#
# Initialize autoconf for the package
#
AC_INIT([LogUtilities],
        m4_esyscmd([third_party/nlbuild-autotools/repo/scripts/mkversion -b `cat .default-version` .]),
        [],
        [LogUtilities],
        [https://github.com/nuovations/LogUtilities/])

# Tell the rest of the build system the absolute path where the
# nlbuild-autotools repository is rooted at.

AC_SUBST(nlbuild_autotools_stem,[third_party/nlbuild-autotools/repo])
AC_SUBST(abs_top_nlbuild_autotools_dir,[\${abs_top_srcdir}/\${nlbuild_autotools_stem}])

#
# LogUtilities interface current, revision, and age versions.
#
# Maintainters: Please manage these fields as follows:
#
#   Interfaces removed:    CURRENT++, AGE = 0, REVISION = 0
#   Interfaces added:      CURRENT++, AGE++,   REVISION = 0
#   No interfaces changed:                     REVISION++
#
#
AC_SUBST(LOGUTILITIES_VERSION_CURRENT,  [1])
AC_SUBST(LOGUTILITIES_VERSION_AGE,      [0])
AC_SUBST(LOGUTILITIES_VERSION_REVISION, [0])
AC_SUBST(LOGUTILITIES_VERSION_INFO,     [${LOGUTILITIES_VERSION_CURRENT}:${LOGUTILITIES_VERSION_REVISION}:${LIBLOGUTILITIES_VERSION_AGE}])

#
# Check the sanity of the source directory by checking for the
# presence of a key watch file
#
AC_CONFIG_SRCDIR([include/LogUtilities/LogUtilities.hpp])

#
# Tell autoconf where to find auxilliary build tools (e.g. config.guess,
# install-sh, missing, etc.)
#
AC_CONFIG_AUX_DIR([third_party/nlbuild-autotools/repo/third_party/autoconf])

#
# Tell autoconf where to find auxilliary M4 macros
#
AC_CONFIG_MACRO_DIRS([third_party/nlbuild-autotools/repo/third_party/autoconf/m4 third_party/nlbuild-autotools/repo/autoconf/m4])

#
# Tell autoconf what file the package is using to aggregate C preprocessor
# defines.
#
AC_CONFIG_HEADERS([include/LogUtilities/LogUtilitiesConfig.h])

#
# Guards against multiple inclusion of the LogUtilities/LogUtilitiesConfig.h
#

AH_TOP([#ifndef LOGUTILITIES_LOGUTILITIESCONFIG_H
#define LOGUTILITIES_LOGUTILITIESCONFIG_H])

AH_BOTTOM([#endif // LOGUTILITIES_LOGUTILITIESCONFIG_H])

#
# Figure out what the canonical build, host and target tuples are.
#
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

#
# Mac OS X / Darwin ends up putting some versioning cruft on the end of its
# tuple that we don't care about in this script. Create "clean" variables
# devoid of it.
#

NL_FILTERED_CANONICAL_BUILD
NL_FILTERED_CANONICAL_HOST
NL_FILTERED_CANONICAL_TARGET

#
# Configure automake with the desired options, indicating that this is not
# a native GNU package, that we want "silent" build rules, that we want
# objects built in the same subdirectory as their source rather than collapsed
# together at the top-level directory, that we want support for the
# PAX format for 'make dist', and that we do not want emission of
# 'PACKAGE' and 'VERSION' since AC_INIT already emits 'PACKAGE_NAME'
# and 'PACKAGE_VERSION'.
#
# Disable silent build rules by either passing --disable-silent-rules to
# configure or passing V=1 to make
#
AM_INIT_AUTOMAKE([1.14 foreign silent-rules subdir-objects tar-pax no-define])

#
# Silent build rules requires at least automake-1.11. Employ
# techniques for not breaking earlier versions of automake.
#
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AM_SILENT_RULES([yes])

#
# Disable maintainer mode to enable the package to automatically rebuild
# configure, Makefile.in, etc. when the files on which they depend change (for
# example, configure.ac, Makefile.am, etc).
#
# For those that do not desire this behavior, run configure with
# `--enable-maintainer-mode` and run the top-level `bootstrap` script manually.
#
AM_MAINTAINER_MODE([disable])

#
# Checks for build host programs
#

# If we are cross-compiling and we are on an embedded target that
# doesn't support independent, standalone executables, then all
# compiler tests that attempt to create an executable will fail. In
# such circumstances, set AC_NO_EXECUTABLES (see http://sourceware.org/
# ml/newlib/2006/msg00353.html).

AC_MSG_CHECKING([whether to disable executable checking])
if test "$cross_compiling" = yes; then
    AC_NO_EXECUTABLES
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no])
fi

# Passing -Werror to GCC-based or -compatible compilers breaks some
# autoconf tests (see
# http://lists.gnu.org/archive/html/autoconf-patches/2008-09/msg00014.html).
#
# If -Werror has been passed transform it into -Wno-error. We'll
# transform it back later with NL_RESTORE_WERROR.

NL_SAVE_WERROR

# Check for compilers.
#
# These should be checked BEFORE we check for and, implicitly,
# initialize libtool such that libtool knows what languages it has to
# work with.

AC_PROG_CPP
AC_PROG_CPP_WERROR

AC_PROG_CC
AC_PROG_CC_C_O

AC_PROG_CXXCPP

AC_PROG_CXX
AC_PROG_CXX_C_O

# Check for other compiler toolchain tools.

AC_CHECK_TOOL(AR, ar)
AC_CHECK_TOOL(RANLIB, ranlib)
AC_CHECK_TOOL(OBJCOPY, objcopy)
AC_CHECK_TOOL(STRIP, strip)

# Check for other host tools.

AC_PROG_EGREP
AC_PROG_INSTALL
AC_PROG_LN_S

AC_PATH_PROG(CLANG_FORMAT, clang-format)
AC_PATH_PROG(CMP, cmp)
AC_PATH_PROG(PERL, perl)

#
# Checks for specific compiler characteristics
#

#
# Common compiler flags we would like to have.
#
#   -Wall                        CC, CXX
#   -Wconversion                 CC, CXX
#   -Wextra                      CC, CXX
#   -Wheader-hygiene             CC, CXX
#   -Wshadow                     CC, CXX
#   -Wunused                     CC, CXX
#

PROSPECTIVE_CFLAGS="-Wall -Wconversion -Wextra -Wheader-hygiene -Wshadow -Wunused"
PROSPECTIVE_CXXFLAGS=""

# Check whether the C++ compiler supports C++11. If it is supported,
# enable it. Otherwise, proceed without error or warning.

AX_CXX_COMPILE_STDCXX_11([], [optional])

AX_CHECK_COMPILER_OPTIONS([C],   ${PROSPECTIVE_CFLAGS})
AX_CHECK_COMPILER_OPTIONS([C++], ${PROSPECTIVE_CFLAGS} ${PROSPECTIVE_CXXFLAGS})

# Check for and initialize libtool

LT_INIT

#
# Debug instances
#
AC_MSG_NOTICE([checking whether to build debug instances])

# Debug

NL_ENABLE_DEBUG([no])

AM_CONDITIONAL([LOGUTILITIES_BUILD_DEBUG], [test "${nl_cv_build_debug}" = "yes"])

#
# Code coverage and compiler optimization
#

# Coverage

NL_ENABLE_COVERAGE([no])

AM_CONDITIONAL([LOGUTILITIES_BUILD_COVERAGE], [test "${nl_cv_build_coverage}" = "yes"])

NL_ENABLE_COVERAGE_REPORTS([auto])

AM_CONDITIONAL([LOGUTILITIES_BUILD_COVERAGE_REPORTS], [test "${nl_cv_build_coverage_reports}" = "yes"])

# Optimization

NL_ENABLE_OPTIMIZATION([yes])

AM_CONDITIONAL([LOGUTILITIES_BUILD_OPTIMIZED], [test "${nl_cv_build_optimized}" = "yes"])

#
# Treat Compiler Warnings as Errors
#
NL_ENABLE_WERROR([yes])

#
# Tests
#
AC_MSG_NOTICE([checking whether to build tests])

# Tests

NL_ENABLE_TESTS([yes])

AM_CONDITIONAL([LOGUTILITIES_BUILD_TESTS], [test "${nl_cv_build_tests}" = "yes"])

#
# Documentation
#

# Determine whether or not documentation (via Doxygen) should be built
# or not, with 'auto' as the default and establish a default support
# value for GraphViz 'dot' support.

NL_ENABLE_DOCS([auto],[NO])

AM_CONDITIONAL(LOGUTILITIES_BUILD_DOCS, [test "${nl_cv_build_docs}" = "yes"])

#
# Checks for libraries and packages.
#
# At minimum, the following packages are optional, depending on
# configuration:
#
#   * Boost
#   * CppUnit
#
AC_MSG_NOTICE([checking required package dependencies])

# Check if the build host has pkg-config

AC_PATH_PROG([PKG_CONFIG],[pkg-config])

#
# Boost
#

NL_WITH_REQUIRED_EXTERNAL_PACKAGE([Boost],
[BOOST],
[boost],
[],
[
    # Check for required Boost (C++) headers.

    AC_LANG_PUSH([C++])

        AC_CHECK_HEADERS([boost/next_prior.hpp] [boost/shared_ptr.hpp],
            [],
            [
                AC_MSG_ERROR(The Boost header "$ac_header" is required but cannot be found.)
            ]
            )

    AC_LANG_POP
]
)

#
# CppUnit
#

if test "${nl_cv_build_tests}" = "yes"; then

    NL_WITH_REQUIRED_EXTERNAL_PACKAGE([CppUnit],
    [CPPUNIT],
    [cppunit],
    [-lcppunit],
    [
        # Check for required Boost (C++) headers.

        AC_LANG_PUSH([C++])

            AC_CHECK_HEADERS([cppunit/BriefTestProgressListener.h] [cppunit/CompilerOutputter.h] [cppunit/TestAssert.h] [cppunit/TestResult.h] [cppunit/TestResultCollector.h] [cppunit/extensions/HelperMacros.h] [cppunit/extensions/TestFactoryRegistry.h] [cppunit/ui/text/TestRunner.h],
                [],
                [
                    AC_MSG_ERROR(The CppUnit header "$ac_header" is required but cannot be found.)
                ]
                )

        AC_LANG_POP
    ]
    )

fi

# Add any Boost CPPFLAGS, LDFLAGS, and LIBS

CPPFLAGS="${CPPFLAGS} ${BOOST_CPPFLAGS}"
LIBS="${LIBS} ${BOOST_LIBS}"
LDFLAGS="${LDFLAGS} ${BOOST_LDFLAGS}"


# Add any code coverage CPPFLAGS and LIBS

CPPFLAGS="${CPPFLAGS} ${NL_COVERAGE_CPPFLAGS}"
LIBS="${LIBS} ${NL_COVERAGE_LIBS}"
LDFLAGS="${LDFLAGS} ${NL_COVERAGE_LDFLAGS}"

# At this point, we can restore the compiler flags to whatever the
# user passed in, now that we're clear of any -Werror issues by
# transforming -Wno-error back to -Werror.

NL_RESTORE_WERROR

# Coding Style
#
# Establish what tool to use and what arguments to pass for the
# pretty and pretty-check targets.

AC_SUBST(PRETTY, ["\${CLANG_FORMAT}"])
AC_SUBST(PRETTY_ARGS, ["\$(shell cat \${abs_top_srcdir}/build/clang-format/clang-format-pretty.options)"])

AC_SUBST(PRETTY_CHECK, ["\${PERL} \${abs_top_srcdir}/third_party/cstyle/repo/cstyle.pl"])
AC_SUBST(PRETTY_CHECK_ARGS, ["\$(shell cat \${abs_top_srcdir}/build/cstyle/cstyle.options)"])

#
# Identify the various makefiles and auto-generated files for the package
#
AC_CONFIG_FILES([
Makefile
third_party/Makefile
include/Makefile
src/Makefile
tests/Makefile
doc/Makefile
])

#
# Generate the auto-generated files for the package
#
AC_OUTPUT

#
# Summarize the package configuration
#

AC_MSG_NOTICE([

  Configuration Summary
  ---------------------
  Package                                   : ${PACKAGE_NAME}
  Version                                   : ${PACKAGE_VERSION}
  Interface                                 : ${LOGUTILITIES_VERSION_INFO//:/.}
  Build system                              : ${build}
  Host system                               : ${host}
  Target system                             : ${target}
  Target architecture                       : ${target_cpu}
  Target OS                                 : ${target_os}
  Cross compiling                           : ${cross_compiling}
  Build shared libraries                    : ${enable_shared}
  Build static libraries                    : ${enable_static}
  Build debug libraries                     : ${nl_cv_build_debug}
  Build optimized libraries                 : ${nl_cv_build_optimized}
  Build coverage libraries                  : ${nl_cv_build_coverage}
  Build coverage reports                    : ${nl_cv_build_coverage_reports}
  Lcov                                      : ${LCOV:--}
  Genhtml                                   : ${GENHTML:--}
  Build tests                               : ${nl_cv_build_tests}
  Prefix                                    : ${prefix}
  Shadow directory program                  : ${LNDIR}
  Documentation support                     : ${nl_cv_build_docs}
  Doxygen                                   : ${DOXYGEN:--}
  GraphViz dot                              : ${DOT:--}
  PERL                                      : ${PERL:--}
  clang-format                              : ${CLANG_FORMAT:--}
  Boost compile flags                       : ${BOOST_CPPFLAGS:--}
  Boost link flags                          : ${BOOST_LDFLAGS:--}
  Boost link libraries                      : ${BOOST_LIBS:--}
  CppUnit compile flags                     : ${CPPUNIT_CPPFLAGS:--}
  CppUnit link flags                        : ${CPPUNIT_LDFLAGS:--}
  CppUnit link libraries                    : ${CPPUNIT_LIBS:--}
  C Preprocessor                            : ${CPP}
  C Compiler                                : ${CC}
  C++ Preprocessor                          : ${CXXCPP}
  C++ Compiler                              : ${CXX}
  Archiver                                  : ${AR}
  Archive Indexer                           : ${RANLIB}
  Symbol Stripper                           : ${STRIP}
  Object Copier                             : ${OBJCOPY}
  C Preprocessor flags                      : ${CPPFLAGS:--}
  C Compile flags                           : ${CFLAGS:--}
  C++ Compile flags                         : ${CXXFLAGS:--}
  Link flags                                : ${LDFLAGS:--}
  Link libraries                            : ${LIBS}

])
