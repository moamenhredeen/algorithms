project(
    'algorithms', 'c',
    version : '1.0.0',
    default_options : [
        'warning_level=3',
        'c_std=c99'
    ]
)

add_project_arguments(['-std=c99', '-Wno-overlength-strings'], language : 'c')
lib_args = ['-DBUILDING_MESON_LIBRARY']
incdir = include_directories('include')

# -------------------------------- mylib --------------------------------

mylib = static_library(
    'mylib',
    sources: [
        'src/mylib/stack.c',
    ],
    include_directories : incdir,
    install : true,
    c_args : lib_args
)

# algorithms tests
mylib_tests = {
    'stack_test': 'test/mylib/stack_test.c'
}
foreach name, source : mylib_tests
    test(
        name,
        executable(
            name,
            source,
            link_with : mylib,
            include_directories: include_directories('include/mylib')
        ),
        suite: 'mylib'
    )
endforeach

# -------------------------------- algorithms --------------------------------

algorithms_library = static_library(
    'algorithms',
    sources: [
        'src/sorting/insertion_sort.c',
    ],
    include_directories : incdir,
    install : true,
    c_args : lib_args
)

# algorithms tests
tests = {
    'insertion_sort_test': 'test/sorting/insertion_sort_test.c'
}
foreach name, source : tests
    test(
        name,
        executable(
            name,
            source,
            link_with : algorithms_library,
            include_directories: incdir
        ),
        suite: 'algorithms'
    )
endforeach

# -------------------------------- leetcode --------------------------------

leetcode_library = static_library(
    'leetcode',
    sources: [
        'src/leetcode/two_sum.c',
        'src/leetcode/length_of_longest_substring.c',
        'src/leetcode/add_two_numbers.c',
        'src/leetcode/zigzag_conversion.c',
        'src/leetcode/daily_temperatures.c',
        'src/leetcode/rotate_list.c',
    ],
    include_directories : incdir,
    link_with: [mylib],
    c_args : lib_args
)

leetcode_tests = {
# TODO: fix tests
#    'two_sum_test': 'test/leetcode/two_sum_test.c',
#    'length_of_longest_substring_test': 'test/leetcode/length_of_longest_substring_test.c',
#    'add_two_numbers_test': 'test/leetcode/add_two_numbers_test.c',
#    'zigzag_conversion_test': 'test/leetcode/zigzag_conversion_test.c',
    'daily_temperatures_test': 'test/leetcode/daily_temperatures_test.c',
    'rotate_list_test': 'test/leetcode/rotate_list_test.c',
}
foreach name, source : leetcode_tests
    test(
        name,
        executable(
            name,
            source,
            link_with : [
                mylib,
                algorithms_library,
                leetcode_library
            ],
            include_directories: incdir
        ),
        suite: 'leetcode'
    )
endforeach

