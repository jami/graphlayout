# Name the project
PROJECT(GraphLayout)

# -------------------------

# A warning appeared because minimum version must be
# explicited.
# The warning told me to add this :
cmake_minimum_required( VERSION 2.6 )

if( COMMAND cmake_policy )
    cmake_policy( SET CMP0011 NEW )
endif( COMMAND cmake_policy )

set( COMMON_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin" )
set( COMMON_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs" )

# build type
set( CMAKE_BUILD_TYPE Debug )
set( CMAKE_VERBOSE_MAKEFILE ON )
# test path
SET( TESTDATAPATH "${CMAKE_CURRENT_BINARY_DIR}/testdata/" )

if(NOT WIN32)
    set(COMPILE_FLAGS "-g -ansi -pedantic -Wall -Werror")
endif(NOT WIN32)

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/" )

#requires gtk2.6
find_package( GTK2 2.6 REQUIRED gtk )

#require libxml2
find_package( LibXml2 REQUIRED )

set(CORELIBS ${LIBXML2_LIBRARIES} ${GTK2_LIBRARIES} graphlayout )
set(COREFLAGS ${LIBXML2_INCLUDE_DIRS} ${GTK2_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/include" )

link_libraries( ${CORELIBS} )
include_directories( ${COREFLAGS} "/usr/include/libxml2" )

# -------------------------
# Set data mounting node
# if (DEFINED DATAPATH)
#   add_definitions(-DDATAPATH=${DATAPATH})
# endif (DEFINED DATAPATH)


CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/include/config.h)

add_subdirectory(src)
add_subdirectory(tests)
