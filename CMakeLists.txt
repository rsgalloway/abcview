##-*****************************************************************************
##
## Copyright (c) 2009-2016,
##  Sony Pictures Imageworks Inc. and
##  Industrial Light & Magic, a division of Lucasfilm Entertainment Company Ltd.
##
## All rights reserved.
##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions are
## met:
## *       Redistributions of source code must retain the above copyright
## notice, this list of conditions and the following disclaimer.
## *       Redistributions in binary form must reproduce the above
## copyright notice, this list of conditions and the following disclaimer
## in the documentation and/or other materials provided with the
## distribution.
## *       Neither the name of Industrial Light & Magic nor the names of
## its contributors may be used to endorse or promote products derived
## from this software without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
## "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
## LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
## A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
## OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
## SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
## LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
## DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
## THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
## OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
##-*****************************************************************************

PROJECT(AbcView)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Declare the project version
SET(PROJECT_VERSION_MAJOR "1")
SET(PROJECT_VERSION_MINOR "1")
SET(PROJECT_VERSION_PATCH "0")
SET(PROJECT_VERSION
     ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
SET(VERSION ${PROJECT_VERSION})

# ------------------------------------------------------------------------------
# OPTIONS (set with -D<option>=<value>)
# ------------------------------------------------------------------------------

OPTION(USE_PYTHON "Include PyAbcOpenGL and PyQt app" OFF)
OPTION(USE_SHARED_LIBS "Build shared libraries" ON)
OPTION(ABCVIEW_GLEW_LINK_STATIC "GLEW is a static library" OFF)
OPTION(ILMBASE_LINK_STATIC "IlmBase is a static library" OFF)
OPTION(USE_STATIC_BOOST "Build with static Boost libs" OFF)

# Set static/dynamic build options
SET(LIB_TYPE STATIC)
SET(RUNTIME_INSTALL_DIR lib)
SET(LIBRARY_INSTALL_DIR lib)
SET(ARCHIVE_INSTALL_DIR lib)
IF (USE_SHARED_LIBS)
    SET(LIB_TYPE SHARED)
    SET(ARCHIVE_INSTALL_DIR lib)
    IF (WIN32)
        ADD_DEFINITIONS(-DABCVIEW_DLL)
    ENDIF()
ENDIF()

# Cmake system specific flags
SET(WINDOWS FALSE)
IF ("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    SET(WINDOWS TRUE)
ENDIF()

SET(DARWIN FALSE)
IF ("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
    SET(DARWIN TRUE)
    # suppress rpath warning
    IF (POLICY CMP0042)
        CMAKE_POLICY(SET CMP0042 OLD)
    ENDIF()
ENDIF()

SET(LINUX FALSE)
IF ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    SET(LINUX TRUE)
ENDIF()

# TODO figure out how to do this for Windows
INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
IF (COMPILER_SUPPORTS_CXX1X)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSEIF (COMPILER_SUPPORTS_CXX0X)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ENDIF()

# Set visibility for GNU compilers
IF (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
ENDIF()

# Set some debug vs opt flags
IF ("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    ADD_DEFINITIONS(-DDEBUG=1 -UNDEBUG)
    IF (NOT WINDOWS)
        ADD_DEFINITIONS(-Wall -Werror -Wextra -Wno-unused-parameter)
    ENDIF()
ELSEIF ("${CMAKE_BUILD_TYPE}" MATCHES "Release")
    ADD_DEFINITIONS(-DNDEBUG=1 -UDEBUG)
    IF (NOT WINDOWS)
        ADD_DEFINITIONS(-O3)
    ENDIF()
ENDIF()

IF (NOT ${WINDOWS})
    SET(EXTERNAL_MATH_LIBS "-lm")
ELSE()
    SET(EXTERNAL_MATH_LIBS "")
ENDIF()

IF (${WINDOWS})
    ADD_DEFINITIONS(-DPLATFORM_WINDOWS -DPLATFORM=WINDOWS)
    IF (NOT ILMBASE_LINK_STATIC)
        ADD_DEFINITIONS(-DOPENEXR_DLL)
    ENDIF()
    IF (ABCVIEW_GLEW_LINK_STATIC)
        ADD_DEFINITIONS(-DGLEW_STATIC)
    ENDIF()
ELSEIF (${DARWIN})
    #ADD_DEFINITIONS(-DPLATFORM_DARWIN -DPLATFORM=DARWIN "-arch x86_64")
    ADD_DEFINITIONS(-DPLATFORM_DARWIN -DPLATFORM=DARWIN)
ELSE()
    ADD_DEFINITIONS(-DPLATFORM_LINUX -DPLATFORM=LINUX)
ENDIF()

# ------------------------------------------------------------------------------
# INSTALLATION
# ------------------------------------------------------------------------------

IF (DEFINED ENV{ABCVIEW_INSTALL_PREFIX})
    SET(CMAKE_INSTALL_PREFIX
        $ENV{ABCVIEW_INSTALL_PREFIX}/abcview-${VERSION})
ENDIF()

# Tell me what my install location would be
MESSAGE(STATUS "make install dir: ${CMAKE_INSTALL_PREFIX}")

# check in the source directory
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/Modules)

# ------------------------------------------------------------------------------
# TESTS
# ------------------------------------------------------------------------------

# Globally enable testing
ENABLE_TESTING()
IF (BUILD_TESTING)
    SET(BUILDNAME "${BUILDNAME}" CACHE STRING "Name of build on the dashboard")
    MARK_AS_ADVANCED(BUILDNAME)
ENDIF(BUILD_TESTING)

IF (UNIX AND NOT WINDOWS)
    FIND_PROGRAM(CMAKE_UNAME uname /bin /usr/bin /usr/local/bin )
    IF (CMAKE_UNAME)
        EXEC_PROGRAM(uname ARGS -m OUTPUT_VARIABLE CMAKE_SYSTEM_PROCESSOR)
        SET(CMAKE_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR} CACHE INTERNAL
"processor type (i386 and x86_64)")
        IF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
            ADD_DEFINITIONS(-fPIC)
        ENDIF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    ENDIF(CMAKE_UNAME)
ENDIF(UNIX AND NOT WINDOWS)

IF (DARWIN)
    ADD_DEFINITIONS(-fPIC)
ENDIF()

# ------------------------------------------------------------------------------
# DEPENDENCIES
# ------------------------------------------------------------------------------

FIND_PACKAGE(Threads REQUIRED)

# Alembic
FIND_PACKAGE(Alembic REQUIRED)
MESSAGE(STATUS "ALEMBIC_LIB: ${ALEMBIC_LIB}")
MESSAGE(STATUS "ALEMBIC_INCLUDE_PATH: ${ALEMBIC_INCLUDE_PATH}")
INCLUDE_DIRECTORIES(${ALEMBIC_INCLUDE_PATH})

# IlmBase
INCLUDE("./cmake/AbcViewIlmBase.cmake")
INCLUDE_DIRECTORIES(${ILMBASE_INCLUDE_DIRECTORY})

# Python
IF (USE_PYTHON)
    INCLUDE("./cmake/AbcViewBoost.cmake")
    INCLUDE("./cmake/AbcViewPython.cmake")
    INCLUDE("./cmake/AbcViewPyIlmBase.cmake")
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
ENDIF()

# OpenGL
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
IF (${WINDOWS})
    SET(ABCVIEW_GL_LIBS
        ${GLEW_LIBRARY}
        ${GLUT_LIBRARY}
        ${OPENGL_LIBRARIES}
    )
    INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR})
    INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})
ELSEIF (${DARWIN})
    SET(ABCVIEW_GL_LIBS
        ${GLEW_LIBRARY}
        ${GLUT_LIBRARY}
        "-framework OpenGL"
    )
ELSE()
    SET(ABCVIEW_GL_LIBS
        ${GLEW_LIBRARY}
        ${GLUT_LIBRARY}
        ${OPENGL_LIBRARIES}
    )
ENDIF()
MESSAGE(STATUS "OpenGL Libraries: ${ABCVIEW_GL_LIBS}")

# ------------------------------------------------------------------------------
# BUILD LIBRARIES
# ------------------------------------------------------------------------------

SET(CORE_LIBS
    ${ALEMBIC_LIB}
    ${ILMBASE_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTERNAL_MATH_LIBS}
)

ADD_SUBDIRECTORY(lib)
SET(ABCOPENGL_DIR "${PROJECT_SOURCE_DIR}/lib")
MESSAGE(STATUS "ABCOPENGL_DIR: ${ABCOPENGL_DIR}")
INCLUDE_DIRECTORIES("${ABCOPENGL_DIR}" "${PROJECT_BINARY_DIR}/lib")

# ------------------------------------------------------------------------------
# BUILD PYTHON
# ------------------------------------------------------------------------------

IF (USE_PYTHON)
   ADD_SUBDIRECTORY(python)
ENDIF()

# ------------------------------------------------------------------------------
# BUILD BINARIES
# ------------------------------------------------------------------------------

ADD_SUBDIRECTORY(bin)

# ------------------------------------------------------------------------------

SET(_config_msg "\n   * Alembic Configuration          ===")
MACRO(info_cfg_option
    _setting)
    SET(_msg "   * ${_setting}")
    STRING(LENGTH "${_msg}" _len)
    WHILE("36" GREATER "${_len}")
        SET(_msg "${_msg} ")
        MATH(EXPR _len "${_len} + 1")
    ENDWHILE()
    SET(_config_msg "${_config_msg}\n${_msg}${${_setting}}")
ENDMACRO()
