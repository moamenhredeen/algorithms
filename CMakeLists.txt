cmake_minimum_required(VERSION 3.20)
project(algorithms VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Wpedantic -Wno-overlength-strings)

include_directories(include)

# -------------------------------- sanitizers -------------------------------

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

# -------------------------------- code coverage --------------------------------

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
option(ENABLE_COVERAGE "Enable code coverage" OFF)

if(ENABLE_COVERAGE)
    include(CodeCoverage)
    enable_coverage()
endif()

# -------------------------------- dependencies --------------------------------

include(FetchContent)
FetchContent_Declare(
        unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
        GIT_TAG v2.6.0
)
FetchContent_MakeAvailable(unity)

# -------------------------------- libraries --------------------------------

add_library(algorithms_lib STATIC
    src/sorting/insertion_sort.c
)

add_library(ds_lib STATIC
    src/ds/linked_list.c
    src/ds/stack.c
    src/ds/linked_stack.c
    src/ds/linked_queue.c
    src/ds/binary_tree.c
)

add_library(leetcode STATIC
        src/leetcode/two_sum.c
        src/leetcode/length_of_longest_substring.c
        src/leetcode/add_two_numbers.c
        src/leetcode/zigzag_conversion.c
        src/leetcode/daily_temperatures.c
        src/leetcode/rotate_list.c
)
target_link_libraries(leetcode PRIVATE ds_lib)

# -------------------------------- tests --------------------------------

enable_testing()

function(add_unit_test pattern)
    file(GLOB test_sources ${pattern})
    foreach(source ${test_sources})
        get_filename_component(name ${source} NAME_WE)
        add_executable(${name} ${source})
        target_link_libraries(${name} PRIVATE unity ${ARGN})
        add_test(NAME ${name} COMMAND ${name})
    endforeach()
endfunction()

add_unit_test(test/sorting/*_test.c algorithms_lib)
add_unit_test(test/ds/*_test.c ds_lib)
add_unit_test(test/leetcode/*_test.c leetcode ds_lib algorithms_lib)

# -------------------------------- coverage targets --------------------------------

if(ENABLE_COVERAGE)
    setup_target_for_coverage_lcov(
        NAME coverage
        TEST_COMMAND ctest
        EXCLUDE '*/test/*' '*/build/*' '*/_deps/*'
    )

    message(STATUS "Coverage target available: make coverage")
endif()
