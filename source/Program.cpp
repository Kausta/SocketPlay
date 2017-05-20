// Program.cpp
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#include <iostream>
#include "Program.h"
#include "ProgramOptionsParser.h"
#include "ProgramOptions.h"

using namespace socketplay;

Program::Program() = default;

void Program::run(int argc, const char *const *argv) {
  // Parse command line options and return if the program should end (help, version, etc.)
  ProgramOptionsParser options_parser{};
  options_parser.parse_command_line(argc, argv);
  // TODO: Get options_parser from config file

  ProgramOptions options{options_parser};
  auto mode = options.mode();
  // Show help info and return
  if (mode == ProgramMode::HELP) {
    std::cout << "SocketPlay\n";
    std::cout << options_parser.help_message();
    return;
  }
  // Show version info and return
  if (mode == ProgramMode::VERSION) {
    std::cout << "SocketPlay\n";
    std::cout << "Version 0.1a\n";
    return;
  }
  if (mode == ProgramMode::STREAM) {
    std::cout << "Running in stream mode.\n";
    std::cout << "Streaming from " << options.source_file() << '\n';
    // TODO: Implement streaming mode
    // Streaming mode is less of interest for now as playing mode is required
    // to play audio from another device
  }
  if (mode == ProgramMode::PLAY) {
    std::cout << "Running in play mode.\n";
    std::cout << "Target: " << options.target_address() << ":" << options.target_port() << '\n';
  }
}


