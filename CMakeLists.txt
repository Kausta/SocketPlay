cmake_minimum_required(VERSION 3.8)
project(SocketPlay)

# Global parameters
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_STANDARD 17)

# Extra parameters
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

# Include boost
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(SocketPlay ${SOURCE_FILES})