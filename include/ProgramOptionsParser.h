// ProgramOptions.h
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_PROGRAMOPTIONSPARSER_H
#define SOCKETPLAY_PROGRAMOPTIONSPARSER_H

#include <vector>
#include <string>
#include <memory>
#include <tuple>

#include <boost/program_options.hpp>
#include "ProgramMode.h"

namespace socketplay {
/**
 * @brief Helper for parsing command line options, uses boost::program_options
 */
class ProgramOptionsParser {
 public:
  /**
   * Initiates parser for command line arguments
   * @param arguments Command Line Arguments
   */
  explicit ProgramOptionsParser(std::vector<std::string>&& arguments);

  /// Parser for stream options, checks whether the mode is true
  StreamOptions parse_stream_options();

  /// Parser for stream file options, checks whether the mode is true
  StreamFileOptions parse_stream_file_options();

  /// Parser for play options, checks whether the mode is true
  PlayOptions parse_play_options();

  // TODO: Add parser for config file

  /// Variables map parsed from program options
  const boost::program_options::variables_map &variables_map() const { return variables_map_; }

  /// Checks whether an options exists
  bool has(const std::string &variable) const { return variables_map_.count(variable) != 0; }
  /**
   * @brief Helper to get variable from variables map and convert to required type
   * @pre The variable should exist and be of type T
   * @tparam T Type of the requested variable
   * @param variable Variable to get from the map
   * @return Const ref of type T to given variable from options map
   */
  template<typename T>
  const T &get(const std::string &variable) const { return variables_map_[variable].as<T>(); }
  /**
   * @brief Helper to get variable from variables map if it exists and convert to required type,
   * throws otherwise
   * @tparam T Type of the requested variable
   * @tparam Error Type of error to throw, defaults to std::runtime_error
   * @param variable Variable to get from the map
   * @param error Error message to throw if the variable doesnt exist, defaults to ""
   * @throws Error if the variable doesn't exist
   * @return Const ref of type T to given variable from options map
   */
  template<typename T, typename Error = std::runtime_error>
  const T &get_checked(const std::string &variable, const std::string &error = "") const {
    if (!has(variable))
      throw Error(error);
    return variables_map_[variable].as<T>();
  }
  /**
   * Gets specified mode
   * @return Mode got from arguments
   */
  ProgramMode mode() const { return mode_; }
  /// Returns the generated help message
  const std::string &help_message() const { return help_message_; }
 private:
  boost::program_options::options_description general_options_;
  boost::program_options::positional_options_description positional_options_;
  boost::program_options::options_description stream_options_;
  boost::program_options::options_description stream_file_options_;
  boost::program_options::options_description play_options_;
  boost::program_options::options_description all_options_;

  boost::program_options::variables_map variables_map_;

  std::string help_message_;

  std::vector<std::string> arguments_;
  std::vector<std::string> unrecognized_;
  ProgramMode mode_;
};
}

#endif //SOCKETPLAY_PROGRAMOPTIONS_H
