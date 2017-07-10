cmake_minimum_required(VERSION 3.7)
project(SocketPlay VERSION 0.1 LANGUAGES CXX)

if (${CMAKE_VERSION} VERSION_GREATER 3.8)
    set(CMAKE_CXX_STANDARD 17)
endif()

# Boost static and multithreaded
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS program_options)

set(SOURCE_FILES source/main.cpp source/Program.cpp include/Program.h source/ProgramOptionsParser.cpp include/ProgramOptionsParser.h include/ProgramMode.h include/Windows/ComHelper.h source/Windows/ComHelper.cpp include/Logger.h include/Windows/AudioSource.h include/Windows/detail/AudioSourceImpl.h include/Windows/AudioPlayerWindows.h source/Windows/AudioPlayerWindows.cpp include/AudioPlayer.h)
add_executable(SocketPlay ${SOURCE_FILES})

if (${CMAKE_VERSION} VERSION_LESS 3.8)
    target_compile_options(SocketPlay PUBLIC -std=c++1z)
endif ()

target_include_directories(SocketPlay SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(SocketPlay PRIVATE include)
target_link_libraries(SocketPlay ${Boost_LIBRARIES})

target_compile_options(SocketPlay PUBLIC -Wall -Werror -Wpedantic)
target_compile_options(SocketPlay PUBLIC -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused
        -Woverloaded-virtual -Wconversion -Wsign-conversion -Wmisleading-indentation)
target_compile_options(SocketPlay PUBLIC -Wno-error=unused-variable -Wno-error=sign-conversion)