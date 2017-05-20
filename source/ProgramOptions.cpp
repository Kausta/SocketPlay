// ProgramOptions.cpp
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//
#include "ProgramOptionsParser.h"
#include "ProgramOptions.h"

socketplay::ProgramOptions::ProgramOptions(const ProgramOptionsParser &parser) {
  if (parser.has("help")) {
    mode_ = ProgramMode::HELP;
    return;
  }
  if (parser.has("version")) {
    mode_ = ProgramMode::VERSION;
    return;
  }
  // Check whether the mode is specified
  if (!parser.has("mode")) {
    throw std::runtime_error("Mode not specified!");
  }
  // Mode can only be stream or play
  // -m=stream can give =stream so check ( same for play )
  auto const &mode_string = parser.get<std::string>("mode");
  if (mode_string == "stream" || mode_string == "=stream") {
    mode_ = ProgramMode::STREAM;
    parse_stream_options_(parser);
  } else if (mode_string == "play" || mode_string == "=play") {
    mode_ = ProgramMode::PLAY;
  } else {
    throw std::runtime_error("Unknown mode!\nMode can only be 'stream' or 'play'.");
  }
}
void socketplay::ProgramOptions::parse_stream_options_(const socketplay::ProgramOptionsParser &parser) {
  if (!parser.has("source")) {
    throw std::runtime_error("Source file is required for stream mode!");
  }
  source_file_ = parser.get<std::string>("source");
}
