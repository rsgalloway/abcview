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

IF(DEFINED USE_PYTHON AND NOT USE_PYTHON)
    MESSAGE(STATUS "Skipping finding PyIlmBase and PyImath")
ELSE()
    MESSAGE(STATUS "About to start finding PyIlmBase and PyImath")
    IF(NOT DEFINED PYILMBASE_ROOT)
        IF (${CMAKE_HOST_UNIX})
            IF(${DARWIN})
              # TODO: set to default install path when shipping out
              SET(PYILMBASE_ROOT NOTFOUND)
            ELSE()
              # TODO: set to default install path when shipping out
              SET(PYILMBASE_ROOT "/usr/local/pyilmbase/")
            ENDIF()
        ELSE()
            IF (${WINDOWS})
              # TODO: set to 32-bit or 64-bit path
              SET(PYILMBASE_ROOT "C:/Program Files (x86)/pyilmbase/")
            ELSE()
              SET(PYILMBASE_ROOT NOTFOUND)
            ENDIF()
        ENDIF()
    ELSE()
      SET(PYILMBASE_ROOT ${PYILMBASE_ROOT})
    ENDIF()

    SET(LIBRARY_PATHS
        ${PYILMBASE_ROOT}/lib
        ${PYILMBASE_MODULE_DIRECTORY}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/lib
        /usr/lib
        /sw/lib
        /opt/local/lib
        /opt/csw/lib
        /opt/lib
        /usr/freeware/lib64
   )

    IF(DEFINED PYILMBASE_LIBRARY_DIR)
        SET(LIBRARY_PATHS ${PYILMBASE_LIBRARY_DIR} ${LIBRARY_PATHS})
    ENDIF()

    SET(INCLUDE_PATHS
        ${PYILMBASE_ROOT}/include/OpenEXR/
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/include/OpenEXR/
        /usr/local/include
        /usr/include
        /usr/include/OpenEXR
        /sw/include # Fink
        /opt/local/include # DarwinPorts
        /opt/csw/include # Blastwave
        /opt/include
        /usr/freeware/include
   )

    FIND_PATH(PYILMBASE_INCLUDE_DIRECTORY PyImath.h
              PATHS
              ${INCLUDE_PATHS}
              DOC "The directory where PyImath.h resides")

    IF(NOT DEFINED PYILMBASE_PYIMATH_LIB)
        FIND_LIBRARY(PYILMBASE_PYIMATH_LIB PyImath
                     PATHS
                     ${LIBRARY_PATHS}
                     DOC "The PyImath library")
    ENDIF()

    IF(NOT DEFINED PYILMBASE_PYIMATH_MODULE)
        FIND_LIBRARY(PYILMBASE_PYIMATH_MODULE imathmodule.so
                     PATHS
                     ${LIBRARY_PATHS}
                     DOC "The PyImath library")
    ENDIF()

    SET(PYILMBASE_FOUND TRUE)

    IF (${PYILMBASE_PYIMATH_LIB} STREQUAL "PYILMBASE_PYIMATH_LIB-NOTFOUND")
        MESSAGE(STATUS "pyilmbase libraries (PyImath) not found, required for python support")
        SET(PYILMBASE_FOUND FALSE)
    ENDIF()

    IF (${PYILMBASE_INCLUDE_DIRECTORY} STREQUAL "PYILMBASE_INCLUDE_DIRECTORY-NOTFOUND")
        MESSAGE(STATUS "pyilmbase header files not found, required for python support")
        SET(PYILMBASE_FOUND FALSE)
    ENDIF()

    MESSAGE(STATUS "PYILMBASE INCLUDE PATH: ${PYILMBASE_INCLUDE_DIRECTORY}")
    MESSAGE(STATUS "PYIMATH LIB: ${PYILMBASE_PYIMATH_LIB}")
    MESSAGE(STATUS "PYIMATH MODULE: ${PYILMBASE_PYIMATH_MODULE}")

    SET(PYILMBASE_LIBS
        ${PYILMBASE_PYIMATH_LIB}
    )

ENDIF()
