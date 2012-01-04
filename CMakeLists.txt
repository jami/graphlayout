# Name the project
PROJECT(GraphLayout)

# -------------------------

# A warning appeared because minimum version must be
# explicited.
# The warning told me to add this :
cmake_minimum_required(VERSION 2.6)

# A warning appeared because cmake must look for cppunit.
# The warning told me to add this :
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET(COMMON_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
SET(COMMON_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs")

# build type
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_VERBOSE_MAKEFILE OFF)

if(NOT WIN32)
  set(COMPILE_FLAGS "-g -ansi -pedantic -Wall -Werror")
endif(NOT WIN32)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")

link_libraries (
)

include_directories(
)

# -------------------------
# Set data mounting node
# if (DEFINED DATAPATH)
#   add_definitions(-DDATAPATH=${DATAPATH})
# endif (DEFINED DATAPATH)


CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/include/config.h)

add_subdirectory(src)
add_subdirectory(tests)
