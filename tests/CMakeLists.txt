include_directories(${CMAKE_SOURCE_DIR}/src/include)

add_executable(graphlayouttest
    graphlayouttest.c
    testframework.c
)

set_target_properties(graphlayouttest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMMON_RUNTIME_OUTPUT_DIRECTORY}")

