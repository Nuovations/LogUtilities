[![Build Status][LogUtilities-travis-svg]][LogUtilities-travis]
[![Coverage Status][LogUtilities-codecov-svg]][LogUtilities-codecov]

[LogUtilities-travis]: https://travis-ci.com/Nuovations/LogUtilities
[LogUtilities-travis-svg]: https://travis-ci.com/Nuovations/LogUtilities.svg?branch=main
[LogUtilities-codecov]: https://codecov.io/gh/Nuovations/LogUtilities
[LogUtilities-codecov-svg]: https://codecov.io/gh/Nuovations/LogUtilities/branch/main/graph/badge.svg

Nuovations Log Utilities
========================

# Introduction

Nuovations Log Utilities provides a toolkit for logging unstructured
messages portably to one or more output destinations as well as
related debug and development utilities built atop of that toolkit.

All too often when building software, there is a need for different
logging contexts and output destinations. Sometimes, software is run
interactively and there is a desire to log to standard error or
standard output. Other times, software is run in the background and
there is a desire to log to syslog or some other platform-specific
facility. Other times, there is a desire to do both or neither. Other
times, there is a need to create a build that elides some or all log
messages entirely, for space-savings or other reasons.

Nuovations Log Utilities provides a means to make these goals easily
achievable and their approach uniform and consistent.

# Getting Started with Log Utilities

## Building Log Utilities

If you are not using a prebuilt distribution of Log Utilities,
building Log Utilities should be a straightforward, two- or three-step
process. If you are building from the main branch, start with:

    % ./bootstrap

If you are building from the main branch, a release branch, or a
distribution package, continue (main branch) or start with:

    % ./configure
    % make

The first `bootstrap` step creates the `configure` script and
`Makefile.in` files from `configure.ac` and `Makefile.am` respectively
and only needs to be done once unless those input files have changed.

The second `configure` step generates `Makefile` files from
`Makefile.in` files and only needs to be done once unless those input
files have changed.

Although not strictly necessary, the additional step of sanity
checking the build results is recommended:

    % make check

### Dependencies

In addition to depending on the C and C++ Standard Libraries and the
C++ Standard Template Library (STL), Log Utilities depends on:

  * Boost
  * CppUnit

However, CppUnit is only required when building and running the Log
Utilities unit test suite.

If you want to modify or otherwise maintain the Log Utilities build
system, see "Maintaining Log Utilities" below for more information.

## Installing Log Utilities

To install Log Utilities for your use simply invoke:

    % make install

to install Log Utilities in the location indicated by the --prefix
`configure` option (default "/usr/local"). If you intended an
arbitrarily relocatable Log Utilities installation and passed
`--prefix=/` to `configure`, then you might use DESTDIR to, for
example install Log Utilities in your user directory:

    % make DESTIDIR="${HOME}" install

## Maintaining Log Utilities

If you want to maintain, enhance, extend, or otherwise modify Log
Utilities, it is likely you will need to change its build system,
based on GNU autotools, in some circumstances.

After any change to the Log Utilities build system, including any
*Makefile.am* files or the *configure.ac* file, you must run the
`bootstrap` or `bootstrap-configure` (which runs both `bootstrap` and
`configure` in one shot) script to update the build system.

### Dependencies

Due to its leverage of GNU autotools, if you want to modify or
otherwise maintain the Log Utilities build system, the following
additional packages are required and are invoked by `bootstrap`:

  * autoconf
  * automake
  * libtool

#### Linux

On Debian-based Linux distributions such as Ubuntu, these dependencies
can be satisfied with the following:

    % sudo apt-get install autoconf automake libtool

#### Mac OS X

On Mac OS X, these dependencies can be installed and satisfied using
[Brew](https://brew.sh/):

    % brew install autoconf automake libtool

# Interact

There are numerous avenues for Log Utilities support:

  * Bugs and feature requests — [submit to the Issue Tracker](https://github.com/Nuovations/LogUtilities/issues)

# Versioning

Log Utilities follows the [Semantic Versioning guidelines](http://semver.org/)
for release cycle transparency and to maintain backwards compatibility.

# License

Log Utilities is released under the [Apache License, Version 2.0 license](https://opensource.org/licenses/Apache-2.0).
See the `LICENSE` file for more information.
