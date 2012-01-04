include_directories(${CMAKE_SOURCE_DIR}/src/include)

add_subdirectory(lib)

add_executable(gl
    main.c
)

set_target_properties(gl PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMMON_RUNTIME_OUTPUT_DIRECTORY}")
install_programs(/bin FILES program)
