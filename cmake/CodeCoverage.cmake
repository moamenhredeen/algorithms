# Code Coverage Configuration
#
# This module provides functions to enable code coverage reporting
# Usage:
#   1. Include this file in your CMakeLists.txt
#   2. Call enable_coverage() to add coverage build type
#   3. Call setup_target_for_coverage_lcov() to create coverage targets

# Check for coverage tools
find_program(GCOV_PATH gcov)
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)


# Function to enable coverage flags
function(enable_coverage)
    if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        # Add Coverage build type
        set(CMAKE_C_FLAGS_COVERAGE
                "-O0 -g --coverage -fprofile-arcs -ftest-coverage"
                CACHE STRING "Flags used by C compiler during coverage builds." FORCE)

        set(CMAKE_EXE_LINKER_FLAGS_COVERAGE
                "--coverage"
                CACHE STRING "Flags used for linking binaries during coverage builds." FORCE)

        set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
                "--coverage"
                CACHE STRING "Flags used by shared libraries during coverage builds." FORCE)

        mark_as_advanced(
                CMAKE_C_FLAGS_COVERAGE
                CMAKE_EXE_LINKER_FLAGS_COVERAGE
                CMAKE_SHARED_LINKER_FLAGS_COVERAGE)

        if (NOT CMAKE_BUILD_TYPE STREQUAL "Coverage")
            message(STATUS "Code coverage enabled. Build with -DCMAKE_BUILD_TYPE=Coverage")
        endif ()
    else ()
        message(WARNING "Code coverage requires GCC or Clang compiler")
    endif ()
endfunction()

# Function to setup coverage target using lcov
function(setup_target_for_coverage_lcov)
    set(options NONE)
    set(oneValueArgs NAME BASE_DIRECTORY)
    set(multiValueArgs EXCLUDE TEST_COMMAND)
    cmake_parse_arguments(Coverage "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT LCOV_PATH)
        message(FATAL_ERROR "lcov not found! Install lcov for coverage reports")
    endif ()

    if (NOT GENHTML_PATH)
        message(FATAL_ERROR "genhtml not found! Install lcov for HTML reports")
    endif ()

    # Set default values
    if (NOT Coverage_BASE_DIRECTORY)
        set(Coverage_BASE_DIRECTORY ${PROJECT_SOURCE_DIR})
    endif ()

    if (NOT Coverage_NAME)
        set(Coverage_NAME coverage)
    endif ()

    if (NOT Coverage_TEST_COMMAND)
        set(Coverage_TEST_COMMAND ${CMAKE_CTEST_COMMAND})
    endif ()

    # Setup target
    add_custom_target(${Coverage_NAME}
            # Clean previous coverage data
            COMMAND ${LCOV_PATH} --directory . --zerocounters

            # Run tests
            COMMAND ${Coverage_TEST_COMMAND}

            # Capture coverage data
            COMMAND ${LCOV_PATH} --directory . --capture --output-file ${Coverage_NAME}.info

            # Filter out system headers and test files
            COMMAND ${LCOV_PATH} --remove ${Coverage_NAME}.info
            '*/test/*'
            '*/include/*'
            ${Coverage_EXCLUDE}
            --output-file ${Coverage_NAME}.filtered.info
            --ignore-errors unused

            # Generate HTML report
            COMMAND ${GENHTML_PATH} -o ${Coverage_NAME}_html ${Coverage_NAME}.filtered.info

            # Display summary
            COMMAND ${LCOV_PATH} --list ${Coverage_NAME}.filtered.info

            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating code coverage report"
    )

    # Show info where to find the report
    add_custom_command(TARGET ${Coverage_NAME} POST_BUILD
            COMMAND ;
            COMMENT "Coverage report generated in ${CMAKE_BINARY_DIR}/${Coverage_NAME}_html/index.html"
    )
endfunction()

