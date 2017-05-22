cmake_minimum_required(VERSION 3.7)
project(SocketPlay VERSION 0.1 LANGUAGES CXX)

# Global parameters
add_definitions(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic)
if (${CMAKE_VERSION} VERSION_GREATER 3.8)
    set(CMAKE_CXX_STANDARD 17)
else ()
    add_definitions(-std=c++1z)
endif ()

# From Jason Turner Best Practices
add_definitions(-Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wmisleading-indentation)

# Extra parameters (Unused for now)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}") // -O0 -g -DDEBUG
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}") // -O3 -DNDEBUG
#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}") // -O0 -g

# Boost static and multithreaded
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

# Include boost
find_package(Boost REQUIRED COMPONENTS program_options)
# System so that it doesn't warn for everything in Boost ( with out extended warnings )
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

include_directories(include)
set(SOURCE_FILES source/main.cpp source/Program.cpp include/Program.h source/ProgramOptionsParser.cpp include/ProgramOptionsParser.h include/ProgramMode.h)
add_executable(SocketPlay ${SOURCE_FILES})
target_link_libraries(SocketPlay ${Boost_LIBRARIES})