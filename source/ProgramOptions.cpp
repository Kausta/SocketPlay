// ProgramOptions.cpp
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//
#include "ProgramOptionsParser.h"
#include "ProgramOptions.h"

using namespace socketplay;

ProgramOptions::ProgramOptions(const ProgramOptionsParser &parser) {
  if (parser.has("help")) {
    mode_ = ProgramMode::HELP;
    return;
  }
  if (parser.has("version")) {
    mode_ = ProgramMode::VERSION;
    return;
  }

  // Check whether the mode is specified
  // Mode can only be stream or play
  // -m=stream can give =stream so check ( same for play )
  // Then parse appropriate options
  auto const &mode_string = parser.get_checked<std::string>("mode", "Mode not specified!");
  if (mode_string == "stream" || mode_string == "=stream") {
    mode_ = ProgramMode::STREAM;
    parse_stream_options_(parser);
  } else if (mode_string == "play" || mode_string == "=play") {
    mode_ = ProgramMode::PLAY;
    parse_play_options_(parser);
  } else {
    throw std::runtime_error("Unknown mode!\nMode can only be 'stream' or 'play'.");
  }
}
void ProgramOptions::parse_stream_options_(const socketplay::ProgramOptionsParser &parser) {
  source_file_ = parser.get_checked<std::string>("source", "Source file is required for stream mode!");
}
void ProgramOptions::parse_play_options_(const socketplay::ProgramOptionsParser &parser) {
  target_address_ = parser.get_checked<std::string>("address", "Target address is required for play mode!");
  target_port_ = parser.get_checked<std::string>("port", "Target port is required for play mode!");
}
