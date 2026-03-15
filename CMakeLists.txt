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

    # Setup coverage targets after all tests are defined
    # This will be called at the end of the file
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

add_library(mylib STATIC src/mylib/stack.c)

add_library(algorithms_lib STATIC src/sorting/insertion_sort.c)

add_library(ds_lib STATIC src/ds/linked_list.c)

add_library(leetcode STATIC
        src/leetcode/two_sum.c
        src/leetcode/length_of_longest_substring.c
        src/leetcode/add_two_numbers.c
        src/leetcode/zigzag_conversion.c
        src/leetcode/daily_temperatures.c
        src/leetcode/rotate_list.c
)
target_link_libraries(leetcode PRIVATE mylib)

# -------------------------------- tests --------------------------------

enable_testing()

function(add_unit_test name source)
    add_executable(${name} ${source})
    target_link_libraries(${name} PRIVATE unity ${ARGN})
    add_test(NAME ${name} COMMAND ${name})
endfunction()

# mylib tests
add_unit_test(stack_test test/mylib/stack_test.c mylib)
target_include_directories(stack_test PRIVATE include/mylib)

# algorithms tests
add_unit_test(insertion_sort_test test/sorting/insertion_sort_test.c algorithms_lib)

# data structures tests
add_unit_test(linked_list_test test/ds/linked_list_test.c ds_lib)

# leetcode tests
add_unit_test(daily_temperatures_test test/leetcode/daily_temperatures_test.c leetcode mylib algorithms_lib)
add_unit_test(rotate_list_test test/leetcode/rotate_list_test.c leetcode mylib algorithms_lib)

# TODO: fix tests
# add_unit_test(two_sum_test test/leetcode/two_sum_test.c leetcode mylib algorithms_lib)
# add_unit_test(length_of_longest_substring_test test/leetcode/length_of_longest_substring_test.c leetcode mylib algorithms_lib)
# add_unit_test(add_two_numbers_test test/leetcode/add_two_numbers_test.c leetcode mylib algorithms_lib)
# add_unit_test(zigzag_conversion_test test/leetcode/zigzag_conversion_test.c leetcode mylib algorithms_lib)

# -------------------------------- coverage targets --------------------------------

if(ENABLE_COVERAGE)
    setup_target_for_coverage_lcov(
        NAME coverage
        TEST_COMMAND ctest
        EXCLUDE '*/test/*' '*/build/*' '*/_deps/*'
    )

    message(STATUS "Coverage target available: make coverage")
endif()
