// ProgramOptions.cpp
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#include <sstream>
#include <boost/program_options.hpp>
#include <Logger.h>
#include "ProgramOptionsParser.h"

using namespace socketplay;
namespace po = boost::program_options;

ProgramOptionsParser::ProgramOptionsParser(std::vector<std::string>&& arguments)
    : general_options_("General Options"),
      stream_options_("Streaming Options"),
      stream_file_options_("File Streaming Options"),
      play_options_("Playing Options"),
      arguments_(std::move(arguments)) {
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

  // Parse and store arguments in initiation
  // Can call specific method after that depending on the mode
  auto parsed = po::command_line_parser(arguments_)
      .options(general_options_)
      .positional(positional_options_)
      .allow_unregistered()
      .run();
  po::store(parsed, variables_map_);

  mode_ = [&](){
    if(has("help"))
      return ProgramMode::HELP;
    if(has("version"))
      return ProgramMode::VERSION;
    auto const& mode = get_checked<std::string>("mode", "Mode argument is required!");
    if(mode == "stream")
      return ProgramMode::STREAM;
    if(mode == "stream-file")
      return ProgramMode::STREAM_FILE;
    if(mode == "play")
      return ProgramMode::PLAY;
    throw std::runtime_error("Unrecognized mode!");
  }();
  unrecognized_ = po::collect_unrecognized(parsed.options, po::include_positional);
}

StreamOptions ProgramOptionsParser::parse_stream_options() {
  assert(mode_ == ProgramMode::STREAM);

  po::store(po::basic_command_line_parser(unrecognized_).options(stream_options_).run(), variables_map_);
  po::notify(variables_map_);

  return StreamOptions {
      get_checked<unsigned short>("port", "Port is required for stream mode!")
  };
}

StreamFileOptions ProgramOptionsParser::parse_stream_file_options() {
  assert(mode_ == ProgramMode::STREAM_FILE);

  po::store(po::basic_command_line_parser(unrecognized_).options(stream_file_options_).run(), variables_map_);
  po::notify(variables_map_);

  return StreamFileOptions {
      get_checked<std::string>("source", "Source file is required for stream-file mode!"),
      get_checked<unsigned short>("port", "Port is required for stream file mode!")
  };
}

PlayOptions ProgramOptionsParser::parse_play_options() {
  assert(mode_ == ProgramMode::PLAY);

  po::store(po::basic_command_line_parser(unrecognized_).options(play_options_).run(), variables_map_);
  po::notify(variables_map_);

  return PlayOptions {
      get_checked<std::string>("address", "Target address is required for play mode!"),
      get_checked<unsigned short>("port", "Target port is required for play mode!")
  };
}
