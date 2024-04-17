cmake_minimum_required(VERSION 3.27)
project(ml_with_abstention)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(ml_with_abstention src/main.cxx)
target_include_directories(ml_with_abstention PUBLIC include)

add_executable(test-conjunction test/conjunction.cxx)
target_include_directories(test-conjunction PUBLIC include)
add_test(test-conjunction test/conjunction.cxx)

add_executable(test-dnf test/dnf.cxx)
target_include_directories(test-dnf PUBLIC include)
add_test(test-dnf test/dnf.cxx)
