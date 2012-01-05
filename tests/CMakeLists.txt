include_directories(${CMAKE_SOURCE_DIR}/src/include)

add_executable(gltest
    graphlayouttest.c
    testframework.c
    graphtest.c
)

set_target_properties(gltest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMMON_RUNTIME_OUTPUT_DIRECTORY}")

