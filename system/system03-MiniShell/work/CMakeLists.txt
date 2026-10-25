cmake_minimum_required(VERSION 3.16)
project(minishell_basic_work LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(minishell-basic src/main.cpp)
set_target_properties(minishell-basic PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
if(MSVC)
    target_compile_options(minishell-basic PRIVATE /W4)
else()
    target_compile_options(minishell-basic PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
foreach(EXAMPLE_NUMBER RANGE 1 12)
    add_test(
        NAME example${EXAMPLE_NUMBER}
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:minishell-basic>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/example${EXAMPLE_NUMBER}.in
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/example${EXAMPLE_NUMBER}.out
            -DACTUAL=${CMAKE_CURRENT_BINARY_DIR}/example${EXAMPLE_NUMBER}.actual
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_example.cmake
    )
    set_tests_properties(example${EXAMPLE_NUMBER} PROPERTIES TIMEOUT 5)
endforeach()
