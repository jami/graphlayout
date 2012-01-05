include_directories(${CMAKE_SOURCE_DIR}/src/include)

add_library(graphlayout SHARED
    commandline.c
    document.c
    graph.c
)

SET_TARGET_PROPERTIES(graphlayout PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${COMMON_LIBRARY_OUTPUT_DIRECTORY}")

# make sure the library gets installed
install_targets(/lib graphlayout)