# Algorithms
implementation of algorithms, data structures, and coding challenge solutions for educational purposes.

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=moamenhredeen_algorithms&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=moamenhredeen_algorithms) [![Bugs](https://sonarcloud.io/api/project_badges/measure?project=moamenhredeen_algorithms&metric=bugs)](https://sonarcloud.io/summary/new_code?id=moamenhredeen_algorithms) [![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=moamenhredeen_algorithms&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=moamenhredeen_algorithms) [![Coverage](https://sonarcloud.io/api/project_badges/measure?project=moamenhredeen_algorithms&metric=coverage)](https://sonarcloud.io/summary/new_code?id=moamenhredeen_algorithms)

## Algorithms
- [x] insertion sort


## Data Structures
- [x] [Stack](./src/ds/stack.c)
- [x] [Linked List](./src/ds/linked_list.c)
- [x] [Linked Queue](./src/ds/linked_queue.c)
- [x] [Linked Stack](./src/ds/linked_stack.c)


## LeetCode 
- [x] [Two Sum](./src/leetcode/two_sum.c)
- [x] [Length of longest substring without repeating characteres](./src/leetcode/length_of_longest_substring.c)
- [x] [Daily temperatures](./src/leetcode/daily_temperatures.c)
- [x] [Rotate a List](./src/leetcode/rotate_list.c)
- [x] [ZigZag conversion](./src/leetcode/zigzag_conversion.c)

## Advent of Code
- [ ] 2025

## Development Setup

### Prerequisites
- CMake 3.20+
- GCC or Clang
- lcov (for coverage reports)
- clang-format (for formatting)
- clang-tidy (for static analysis)

### Git Hooks
Enable the pre-commit hook (format check) by running:
```bash
git config core.hooksPath .githooks
```

### Formatting
```bash
# Format all source files
clang-format -i src/**/*.c include/**/*.h test/**/*.c
```

### Build and Test
```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

Debug builds include AddressSanitizer and UndefinedBehaviorSanitizer.

### Code Coverage
```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Coverage -DENABLE_COVERAGE=ON
cmake --build build
cmake --build build --target coverage
```
The HTML report is generated at `build/coverage_html/index.html`.

### Static Analysis
```bash
run-clang-tidy -p build src/
```
