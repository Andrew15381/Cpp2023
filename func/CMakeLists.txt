cmake_minimum_required(VERSION 3.24)
project(matkib)

enable_testing()

set(CMAKE_CXX_STANDARD 17)

#source
set(SOURCE
        main.cpp)

add_executable(func ${SOURCE})

target_include_directories(func PRIVATE lib)

#test
set(TEST_SOURCE
        test.cpp)

add_executable(func_test ${TEST_SOURCE})

target_link_libraries(func_test PRIVATE
        gtest
        pthread)

target_include_directories(func_test PRIVATE lib)

add_test(func_tests func_test)