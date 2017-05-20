// ProgramOptions.h
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_PROGRAMOPTIONSPARSER_H
#define SOCKETPLAY_PROGRAMOPTIONSPARSER_H

#include <vector>
#include <string>
#include <memory>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

namespace socketplay {
/**
 * Helper for parsing command line options, uses boost::program_options
 */
class ProgramOptionsParser {
 public:
  ///Default constructor for Program Options Parser
  ProgramOptionsParser();
  /**
   * Parse options from given command line arguments
   * @param argc Argument Count
   * @param argv Arguments
   */
  void parse_command_line(int argc, const char *const *argv);
  // TODO: Add parser for config file

  /// Variables map parsed from program options
  const po::variables_map &variables_map() const { return variables_map_; }

  /// Checks whether an options exists
  bool has(const std::string &variable) const { return variables_map_.count(variable) != 0; }
  /**
   * Helper to get variable from variables map and convert to required type
   * @pre The variable should exist and be of type T
   * @tparam T Type of the requested variable
   * @param variable Variable to get from the map
   * @return Const ref of type T to given variable from options map
   */
  template<typename T>
  const T &get(const std::string &variable) const { return variables_map_[variable].as<T>(); }
  /**
   * Helper to get variable from variables map if it exists and convert to required type,
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

  /// Returns the generated help message
  const std::string &help_message() const { return help_message_; }
 private:
  po::options_description general_options_;
  po::options_description stream_options_;
  po::options_description play_options_;
  po::options_description all_options_;

  po::variables_map variables_map_;

  std::string help_message_;
};
}

#endif //SOCKETPLAY_PROGRAMOPTIONS_H
