cmake_minimum_required(VERSION 3.8)
project(SocketPlay)

# Global parameters
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_STANDARD 17)

# Extra parameters
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

# Boost static and multithreaded
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

# Include boost
find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include)
set(SOURCE_FILES source/main.cpp source/Program.cpp include/Program.h source/ProgramOptionsParser.cpp include/ProgramOptionsParser.h source/ProgramOptions.cpp include/ProgramOptions.h include/ProgramMode.h)
add_executable(SocketPlay ${SOURCE_FILES})
target_link_libraries(SocketPlay ${Boost_LIBRARIES})