# Michael Aaron Safyan (michaelsafyan@gmail.com). Copyright (C) 2009. Simplified BSD License.
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#
# This CMake package creates a Doxygen documentation target.
#

FIND_PACKAGE (Doxygen)
IF (DOXYGEN_FOUND)
    IF (EXISTS ${PROJECT_SOURCE_DIR}/Doxyfile)
        ADD_CUSTOM_TARGET(
            doxygen
            ${DOXYGEN_EXECUTABLE} Doxyfile
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Generating doxygen project documentation." VERBATIM
        )
        ADD_CUSTOM_TARGET(
            documentation
            ${DOXYGEN_EXECUTABLE} Doxyfile
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Generating doxygen project documentation." VERBATIM
        )
        ADD_CUSTOM_TARGET(
            docs
            ${DOXYGEN_EXECUTABLE} Doxyfile
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Generating doxygen project documentation." VERBATIM
        )
    ELSE (EXISTS ${PROJECT_SOURCE_DIR}/Doxyfile)
        ADD_CUSTOM_TARGET(doxygen COMMENT "Doxyfile not found. Please generate a doxygen configuration file to use this target." VERBATIM)
        ADD_CUSTOM_TARGET(documentation COMMENT "Doxyfile not found. Please generate a doxygen configuration file to use this target." VERBATIM)
        ADD_CUSTOM_TARGET(docs COMMENT "Doxyfile not found. Please generate a doxygen configuration file to use this target." VERBATIM)
    ENDIF (EXISTS ${PROJECT_SOURCE_DIR}/Doxyfile)
ELSE (DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(doxygen COMMENT "Doxygen not found. Please install doxygen to use this target." VERBATIM)
    ADD_CUSTOM_TARGET(documentation COMMENT "Doxygen not found. Please install doxygen to use this target." VERBATIM)
    ADD_CUSTOM_TARGET(docs COMMENT "Doxygen not found. Please install doxygen to use this target." VERBATIM)
ENDIF (DOXYGEN_FOUND)
