include_directories(${CMAKE_SOURCE_DIR}/src/include)

add_executable(graphlayout 
    main.c
)

set_target_properties(graphlayout PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMMON_RUNTIME_OUTPUT_DIRECTORY}")

install_programs(/bin FILES program)
