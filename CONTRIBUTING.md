# Contributing to SocketPlay

Thank you for coming and reading this, as contributions are 
highly welcome and required at this stage of the project.

As the project is yet small and feature-wise incomplete, 
a plan is required to help anyone wanting to contribute.

## Installation

First clone the repository from
> https://github.com/Kausta/SocketPlay.git

### Building

Cmake 3.8 and a compiler supporting C++17 is preferred and set in [CMakeLists](CMakeLists.txt).

Boost is required for program_options.

Tested with GCC 7.1, CMake 3.8 and Boost 1.64.0.

Built out of source with debug, release  and release with debug info configurations.

## Project Plan

[ ] Command Line Arguments
  [x] Basic Mode Configuration, Help, Version Info
  [ ] Extended Streaming and Playing Arguments
[ ] Streaming Mode
  [ ] File Streaming (TCP ?)
  [ ] Audio Redirection From Stream (UDP)
    [ ] Windows: Planned to use WASAPI
    [ ] Linux: Planned to use alsa
[ ] Playing Mode
  [ ] OpenAL is planned, but subject due to change
  
## Coding Styles and Conventions

For style, it is possible to use formatters. 
Currently, the project is designed according to Google styles.

---

For naming conventions, classes are CamelCase, namespaces are lowercase, and methods and variables are snake_case.
Class privates end with _.

---

Socket Play is an open source project and welcomes all contributions. Thank you.

Caner Korkmaz ( info@canerkorkmaz.com )