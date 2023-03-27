cmake_minimum_required(VERSION 3.0)

project(console-client)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.74.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(cli cli/main.cpp)

target_link_libraries(cli ${Boost_LIBRARIES})


