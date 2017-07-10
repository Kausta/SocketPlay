// main.cpp
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <stdexcept>
#include <iostream>
#include <comdef.h>
#include "Program.h"
#include "ProgramOptionsParser.h"

int main(int argc, char *argv[]) {
  try {
    // Options are [1, argc-1)
    socketplay::ProgramOptionsParser parser{std::vector<std::string>{argv+1, argv+argc}};

    // Initialize program with given arguments
    // May not initialize if either help or version ?
    //  - However, constructor should be light given different run functions in same class
    socketplay::Program program{};

    switch(parser.mode()) {
      case socketplay::ProgramMode::HELP:
        std::cout << "SocketPlay\n";
        std::cout << parser.help_message();
        break;
      case socketplay::ProgramMode::VERSION:
        std::cout << "SocketPlay\n";
        std::cout << "Version 0.1a\n";
        break;
      case socketplay::ProgramMode::STREAM:
        program.run_stream_mode(parser.parse_stream_options());
        break;
      case socketplay::ProgramMode::STREAM_FILE:
        program.run_stream_file_mode(parser.parse_stream_file_options());
        break;
      case socketplay::ProgramMode::PLAY:
        program.run_play_mode(parser.parse_play_options());
        break;
    }

    return EXIT_SUCCESS;
  } catch (const std::runtime_error &err) {
    // Unhandled exception -> Means error and break
    std::cerr << "Error: " << err.what() << '\n';
  } catch (const std::logic_error &err) {
    // Also report logic errors
    // This contains program_options errors
    std::cerr << "Error: " << err.what() << '\n';
  } catch (const _com_error& err){
    std::cerr << "Com Error: " << err.ErrorMessage() << '\n';
  }
  return EXIT_FAILURE;
}