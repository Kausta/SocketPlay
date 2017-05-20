// ProgramOptions.cpp
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#include <sstream>
#include <boost/program_options.hpp>
#include "ProgramOptionsParser.h"

namespace po = boost::program_options;

socketplay::ProgramOptionsParser::ProgramOptionsParser()
    : general_options_("General Options"),
      stream_options_("Streaming Options"),
      play_options_("Playing Options") {
  // Add general options
  general_options_.add_options()
      ("help,h", "Shows this help message.")
      ("version,v", "Shows version info.")
      ("mode,m", po::value<std::string>(), "Application mode\n Possible options: stream, play");

  // Options specific for streaming and playing modes
  stream_options_.add_options()
      ("source,s", po::value<std::string>(), "Source file to stream");
  play_options_.add_options();

  // Helper for parsing and generating help message
  all_options_.add(general_options_)
      .add(stream_options_)
      .add(play_options_);

  // Generate the help message from all options once
  std::stringstream ss;
  ss << all_options_;
  help_message_ = ss.str();
}

void socketplay::ProgramOptionsParser::parse_command_line(int argc, const char *const *argv) {
  po::store(po::parse_command_line(argc, argv, all_options_), variables_map_);
  po::notify(variables_map_);
}
