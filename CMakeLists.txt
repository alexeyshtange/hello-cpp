
cmake_minimum_required(VERSION 3.20)

project(HelloCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_library(hello_lib src/hello.cpp)

target_include_directories(hello_lib PUBLIC include)

add_executable(hello src/main.cpp)
target_link_libraries(hello PRIVATE hello_lib)

enable_testing()

add_executable(hello_test tests/hello_test.cpp)
target_link_libraries(hello_test PRIVATE hello_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(hello_test)
