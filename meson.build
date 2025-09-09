project(
    'algorithms', 'c',
    version : '1.0.0',
    default_options : [
        'warning_level=3', 'c_std=c89'
    ]
)

lib_args = ['-DBUILDING_MESON_LIBRARY']
incdir = include_directories('include')
algorithms_library = static_library(
    'algorithms',
    sources: [
        'src/sorting/insertion_sort.c'
    ],
    include_directories : incdir,
    install : true,
    c_args : lib_args
)

# tests
insertion_sort_test = executable(
    'insertion_sort_test',
    'test/sorting/insertion_sort_test.c',
    link_with : algorithms_library,
    include_directories: incdir
)
test('insertion sort test', insertion_sort_test)