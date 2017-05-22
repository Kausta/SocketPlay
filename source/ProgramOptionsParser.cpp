// ProgramOptions.cpp
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#include <sstream>
#include <boost/program_options.hpp>
#include "ProgramOptionsParser.h"

using namespace socketplay;
namespace po = boost::program_options;

ProgramOptionsParser::ProgramOptionsParser()
    : general_options_("General Options"),
      stream_options_("Streaming Options"),
      stream_file_options_("File Streaming Options"),
      play_options_("Playing Options") {
  // Add general options
  general_options_.add_options()
      ("help,h", "Shows this help message.")
      ("version,v", "Shows version info.")
      ("mode,m",
       po::value<std::string>(),
       "Application mode\n Possible options: stream, stream-file, play")
      ("command-args,c", po::value<std::vector<std::string>>(), "Arguments for the command");

  positional_options_.add("mode", 1);
  positional_options_.add("command-args", -1);

  // Options specific for streaming and playing modes
  stream_options_.add_options()
      ("port,p", po::value<unsigned short>(), "Port");
  stream_file_options_.add_options()
      ("source,s", po::value<std::string>(), "Source file to stream")
      ("port,p", po::value<unsigned short>(), "Port");
  play_options_.add_options()
      ("address,a", po::value<std::string>(), "Target Address")
      ("port,p", po::value<unsigned short>(), "Target Port");

  // Helper for parsing and generating help message
  all_options_.add(general_options_)
      .add(stream_options_)
      .add(stream_file_options_)
      .add(play_options_);

  // Generate the help message from all options once
  std::stringstream ss;
  ss << all_options_;
  help_message_ = ss.str();
}

std::tuple<ProgramMode, OptionsContainer> ProgramOptionsParser::parse_command_line(int argc, const char *const *argv) {
  auto parsed = po::basic_command_line_parser(argc, argv)
      .options(general_options_)
      .positional(positional_options_)
      .allow_unregistered()
      .run();
  po::store(parsed, variables_map_);

  if (has("help"))
    return {ProgramMode::HELP, {}};
  if (has("version"))
    return {ProgramMode::VERSION, {}};

  auto const &mode = get_checked<std::string>("mode", "Mode argument is required!");
  auto options = po::collect_unrecognized(parsed.options, po::include_positional);
  // Erase the positional mode
  options.erase(options.begin());
  if (mode == "stream") {
    po::store(po::basic_command_line_parser(options).options(stream_options_).run(), variables_map_);
    po::notify(variables_map_);

    return {ProgramMode::STREAM, StreamOptions{
        get_checked<unsigned short>("port", "Port is required for stream mode!")
    }};
  }
  if (mode == "stream-file") {
    po::store(po::basic_command_line_parser(options).options(stream_file_options_).run(), variables_map_);
    po::notify(variables_map_);
    return {ProgramMode::STREAM_FILE, StreamFileOptions{
        get_checked<std::string>("source", "Source file is required for stream-file mode!"),
        get_checked<unsigned short>("port", "Port is required for stream mode!")
    }};
  }
  if (mode == "play") {
    po::store(po::basic_command_line_parser(options).options(play_options_).run(), variables_map_);
    po::notify(variables_map_);
    return {ProgramMode::PLAY, PlayOptions{
        get_checked<std::string>("address", "Target address is required for play mode!"),
        get_checked<unsigned short>("port", "Target port is required for play mode!")
    }};
  }

  throw std::runtime_error("Unrecognized mode!");
}
