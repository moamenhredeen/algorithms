project(
    'algorithms', 'c',
    version : '1.0.0',
    default_options : [
        'warning_level=3', 'c_std=c89'
    ]
)

lib_args = ['-DBUILDING_MESON_LIBRARY']
incdir = include_directories('include')

# -------------------------------- algorithms --------------------------------

algorithms_library = static_library(
    'algorithms',
    sources: [
        'src/sorting/insertion_sort.c'
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
        'src/leetcode/two_sum.c'
    ],
    include_directories : incdir,
    c_args : lib_args
)

leetcode_tests = {
    'two_sum_test': 'test/leetcode/two_sum_test.c'
}
foreach name, source : leetcode_tests
    test(
        name,
        executable(
            name,
            source,
            link_with : [
                algorithms_library,
                leetcode_library
            ],
            include_directories: incdir
        ),
        suite: 'leetcode'
    )
endforeach

